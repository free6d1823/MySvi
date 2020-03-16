#include <std/stdlib.h>
#include <std/stdio.h>
#include <std/string.h>
#include <target/delay.h>
#include <target/timer.h>
#include <target/cmdline.h>
#include <errno.h>
#include "designware_i2c.h"

#define I2C_NUM 8
#define I2C_HOST_ADDR(n)	(0x55250000 + 0x10000 * n)

struct i2c_regs *i2c_bases[I2C_NUM];

void i2c_print(uint8_t *buff, size_t BufferSize)
{
    int i;

    printf("   ");
    for (i = 0; i < 16; i++)
        printf("  %X", i);
    printf("\n");
    for (i = 0; i < BufferSize; i++)
    {
        if (0 == (i & 0xf)) {
            if(i) printf("\n");
            printf("%02X:", i);
        }
        printf(" %02X", buff[i]);
    }

    printf("\n");
}


static void dw_i2c_enable(struct i2c_regs *i2c_base, bool enable)
{
	u32 ena = enable ? IC_ENABLE_0B : 0;
	int timeout = 100;

	do {
		writel(ena, &i2c_base->ic_enable);
		if ((readl(&i2c_base->ic_enable_status) & IC_ENABLE_0B) == ena)
			return;

		/*
		 * Wait 10 times the signaling period of the highest I2C
		 * transfer supported by the driver (for 400KHz this is
		 * 25us) as described in the DesignWare I2C databook.
		 */
		udelay(25);
	} while (timeout--);

	printf("timeout in %sabling I2C adapter\n", enable ? "en" : "dis");
}


/*
 * i2c_setaddress - Sets the target slave address
 * @i2c_addr:	target i2c address
 *
 * Sets the target slave address.
 */
static void i2c_setaddress(struct i2c_regs *i2c_base, unsigned int i2c_addr)
{
	/* Disable i2c */
	dw_i2c_enable(i2c_base, false);

	writel(i2c_addr, &i2c_base->ic_tar);

	/* Enable i2c */
	dw_i2c_enable(i2c_base, true);
}

/*
 * i2c_flush_rxfifo - Flushes the i2c RX FIFO
 *
 * Flushes the i2c RX FIFO
 */
static void i2c_flush_rxfifo(struct i2c_regs *i2c_base)
{
	while (readl(&i2c_base->ic_status) & IC_STATUS_RFNE)
		readl(&i2c_base->ic_cmd_data);
}


/*
 * i2c_wait_for_bb - Waits for bus busy
 *
 * Waits for bus busy
 */
static int i2c_wait_for_bb(struct i2c_regs *i2c_base)
{
	unsigned long start_time_bb = get_timer(0);

	while ((readl(&i2c_base->ic_status) & IC_STATUS_MA) ||
	       !(readl(&i2c_base->ic_status) & IC_STATUS_TFE)) {

		/* Evaluate timeout */
		if (get_timer(start_time_bb) > (unsigned long)(I2C_BYTE_TO_BB))
			return 1;
	}

	return 0;
}


static int i2c_xfer_init(struct i2c_regs *i2c_base, int chip, uint addr,
			 int alen)
{
	if (i2c_wait_for_bb(i2c_base))
		return 1;

	i2c_setaddress(i2c_base, chip);
	while (alen) {
		alen--;
		/* high byte address going out first */
		writel((addr >> (alen * 8)) & 0xff,
		       &i2c_base->ic_cmd_data);
	}
	return 0;
}

static int i2c_xfer_finish(struct i2c_regs *i2c_base)
{
	ulong start_stop_det = get_timer(0);

	while (1) {
		if ((readl(&i2c_base->ic_raw_intr_stat) & IC_STOP_DET)) {
			readl(&i2c_base->ic_clr_stop_det);
			break;
		} else if (get_timer(start_stop_det) > I2C_STOPDET_TO) {
			break;
		}
	}

	if (i2c_wait_for_bb(i2c_base)) {
		printf("Timed out waiting for bus\n");
		return 1;
	}

	i2c_flush_rxfifo(i2c_base);

	return 0;
}


static int dw_i2c_read(struct i2c_regs *i2c_base, int dev, uint addr,
			 int alen, int *buffer, int len)
{
	unsigned long start_time_rx;
	unsigned int active = 0;

#ifdef CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW
	/*
	 * EEPROM chips that implement "address overflow" are ones
	 * like Catalyst 24WC04/08/16 which has 9/10/11 bits of
	 * address and the extra bits end up in the "chip address"
	 * bit slots. This makes a 24WC08 (1Kbyte) chip look like
	 * four 256 byte chips.
	 *
	 * Note that we consider the length of the address field to
	 * still be one byte because the extra address bits are
	 * hidden in the chip address.
	 */
	dev |= ((addr >> (alen * 8)) & CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW);
	addr &= ~(CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW << (alen * 8));

	debug("%s: fix addr_overflow: dev %02x addr %02x\n", __func__, dev,
	      addr);
#endif

	if (i2c_xfer_init(i2c_base, dev, addr, alen))
		return 1;

	start_time_rx = get_timer(0);
	while (len) {
		if (!active) {
			/*
			 * Avoid writing to ic_cmd_data multiple times
			 * in case this loop spins too quickly and the
			 * ic_status RFNE bit isn't set after the first
			 * write. Subsequent writes to ic_cmd_data can
			 * trigger spurious i2c transfer.
			 */
			if (len == 1)
				writel(IC_CMD | IC_STOP, &i2c_base->ic_cmd_data);
			else
				writel(IC_CMD, &i2c_base->ic_cmd_data);
			active = 1;
		}

		if (readl(&i2c_base->ic_status) & IC_STATUS_RFNE) {
			*buffer++ = (int)readl(&i2c_base->ic_cmd_data);
			len--;
			start_time_rx = get_timer(0);
			active = 0;
		} else if (get_timer(start_time_rx) > I2C_BYTE_TO) {
			return 1;
		}
	}

	return i2c_xfer_finish(i2c_base);
}

static int dw_i2c_write(struct i2c_regs *i2c_base,int dev, uint addr,
			  int alen, int *buffer, int len)
{
	int nb = len;
	unsigned long start_time_tx;

#ifdef CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW
	/*
	 * EEPROM chips that implement "address overflow" are ones
	 * like Catalyst 24WC04/08/16 which has 9/10/11 bits of
	 * address and the extra bits end up in the "chip address"
	 * bit slots. This makes a 24WC08 (1Kbyte) chip look like
	 * four 256 byte chips.
	 *
	 * Note that we consider the length of the address field to
	 * still be one byte because the extra address bits are
	 * hidden in the chip address.
	 */
	dev |= ((addr >> (alen * 8)) & CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW);
	addr &= ~(CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW << (alen * 8));

	debug("%s: fix addr_overflow: dev %02x addr %02x\n", __func__, dev,
	      addr);
#endif

	if (i2c_xfer_init(i2c_base, dev, addr, alen))
		return 1;

	start_time_tx = get_timer(0);
	while (len) {
		if (readl(&i2c_base->ic_status) & IC_STATUS_TFNF) {
			if (--len == 0) {
				writel(*buffer | IC_STOP,
				       &i2c_base->ic_cmd_data);
			} else {
				writel(*buffer, &i2c_base->ic_cmd_data);
			}
			buffer++;
			start_time_tx = get_timer(0);

		} else if (get_timer(start_time_tx) > (nb * I2C_BYTE_TO)) {
				printf("Timed out. i2c write Failed\n");
				return 1;
		}
	}

	return i2c_xfer_finish(i2c_base);
}

static int dw_i2c_init(struct i2c_regs *i2c_base){
	/* Disable i2c */
	dw_i2c_enable(i2c_base, false);

	writel(IC_CON_SD | IC_CON_RE | IC_CON_SPD_FS | IC_CON_MM,
	       &i2c_base->ic_con);
	writel(IC_RX_TL, &i2c_base->ic_rx_tl);
	writel(IC_TX_TL, &i2c_base->ic_tx_tl);
	writel(IC_STOP_DET, &i2c_base->ic_intr_mask);
	/* Enable i2c */
	dw_i2c_enable(i2c_base, true);
	return 0;
}


/* dw_i2c_probe - Probe the i2c chip */
static int dw_i2c_probe(struct i2c_regs *i2c_base, int dev)
{
	u32 tmp;
	int ret;

	/*
	 * Try to read the first location of the chip.
	 */
	ret = dw_i2c_read(i2c_base, dev, 0, 1, (int *)&tmp, 1);
	if (ret)
		dw_i2c_init(i2c_base);

	return ret;
}

static int gindex;

int i2c_init(int index){

	for(int i=0; i<8; i++){
		i2c_bases[i] = (struct i2c_regs *)(long)(I2C_HOST_ADDR(i));
	}
	gindex = index;
	return  dw_i2c_init(i2c_bases[gindex]);

}

int i2c_read(int dev, uint addr, int *buffer, int len){
	return dw_i2c_read(i2c_bases[gindex], dev, addr, 1, buffer, len);
}

int i2c_write(int dev, uint addr, int *buffer, int len){
	return dw_i2c_write(i2c_bases[gindex], dev, addr, 1, buffer, len);
}

int i2c_probe(int dev){
	return dw_i2c_probe(i2c_bases[gindex], dev);
}

int cmd_i2c(int argc, char **argv){

	int ret = 0;
	uint8_t buff[256] = {0};
	void *buffer = buff;
	size_t BufferSize = 256;

	if (argc < 2)
		return -EUSAGE;

	if (!strcmp("init", argv[1])) {
		int index = strtoul(argv[2], NULL, 0);
		if ((index > -1) && (index < 8)){
			ret = i2c_init(index);
			if (!ret){
				printf("Init i2c %d success", index);
			}else{
				printf("Init i2c %d fail.", index);
			}
		}else{
			printf("Please check your i2c host controller index, 0~8 is vaild.");
		}
	}

	if (!strcmp("probe", argv[1])) {

		if (argc < 3)
			return -EUSAGE;

		if (!strcmp("all", argv[2])){
			int addr;
            for (addr = 0; addr < 128; addr++) {
                ret = i2c_probe(addr);
                if (!ret) {
                    buff[addr] = addr;
                }
            }
            printf("i2c device: \n");
            i2c_print(buff,128);
		}else{
			uint slave_addr;
			slave_addr = strtoul(argv[2], NULL, 0);
			ret = i2c_probe(slave_addr);
			if (!ret){
				printf("Find i2c device: 0x%X", slave_addr);
			}else{
				printf("Not find i2c device: 0x%X", slave_addr);
			}
		}
	}

	if (!strcmp("read", argv[1])) {

		if (argc < 4)
			return -EUSAGE;

		uint slave_addr;
		uint comm;
		int len;

		slave_addr = strtoul(argv[2], NULL, 0);
		comm = strtoul(argv[3], NULL, 0);

		if (argc == 4){
			len = BufferSize;
		}else{
			len = strtoul(argv[4], NULL, 0);
		}

		ret = i2c_read(slave_addr, comm, buffer, len);
		if (!ret){
			printf("i2c read 0x%X data: \n", comm);
			i2c_print(buffer, len);
		}else{
			printf("I2C read error");
		}
	}

	if (!strcmp("write", argv[1])) {

		if (argc < 5)
			return -EUSAGE;

		int slave_addr;
		uint comm;
		int len;
		int i;

		len = argc - 4;
		for (i = 0; i < len; i++){
			buff[i] = strtoul(argv[i+4], NULL, 0);
		}
		slave_addr = strtoul(argv[2], NULL, 0);
		comm = strtoul(argv[3], NULL, 0);

 		ret = i2c_write(slave_addr, comm, buffer, len);
		if (!ret) {
			printf("i2c write register 0x%X \n", comm);
		}else {
			printf("I2C write error: 0x%X\n", comm);
		}
	}

	return ret;

}

MK_CMD(i2c, cmd_i2c, "Designware I2C cmd",
	" i2c init index \n"
	"		-the index of i2c controller initialization. \n"
	" i2c probe all\n"
	"		-detect all of slave device. \n"
	" i2c probe slave_addr \n"
	"		-detect slave device. \n"
	" i2c read slave_addr comm \n"
	"		-Read 256 values from comm. \n"
	" i2c read slave_addr comm len \n"
	"		-Read [len] values from comm. \n"
	" i2c write slave_addr comm [value1] [value2] ... \n"
	"		-Write values to comm. \n"

);


