#include <stdio.h>
#include "voltage_plan_types.h"
#include "voltage_plan_target_defs.h"
#include "voltplan_defs.h"
#include "fuse.h"
#include <asm/mach/chipinfo.h>
#include <asm/mach/hal/msmhwiobase.h>
#include "voltplan_fuses_hwio.h"
#include <asm/mach/cpus.h>
#include <target/cmdline.h>
#include <asm/mach/chipinfo.h>
#include <asm/mach/tsens/tsens_fuse.h>

#define I_POS( object_ptr, item_type, item_num ) \
	(item_type)((void *)object_ptr + sizeof(item_type) * item_num);

#define CHIPINFO_VERSION(major, minor)	(((major) << 16) | (minor))
#define EXTRACT_FUSE_VAL(val, fuse) (((val) & HWIO_##fuse##_BMSK) >> HWIO_##fuse##_SHFT)

char *rail_name[13] = {"RAIL_MX", "RAIL_CX", "RAIL_VDN", "RAIL_VDS", "RAIL_APR0", "RAIL_APR1", "RAIL_APR2", "RAIL_APR3", "RAIL_APR4", "RAIL_APR5", "RAIL_APR6", "RAIL_APR7","RAIL_CBF"};

typedef struct {
    unsigned int OvrEn : 1;
    unsigned int OvrInvEn : 1;
    unsigned int OvrDcaEn : 1;
    unsigned int OvrTdlSel : 1;
    unsigned int OvrMuxSel : 4;
    unsigned char OvrDcaVal[24];
} clock_fuse_setting;


/* base_addr: the start addr
 * len		: the leng of the once read ---4bytes/8bytes
 * num		: the number of data to be printed */
static void print_raw_data(uint64_t base_addr, uint8_t len, uint8_t num)
{
	uint16_t line_max_num = 0;
	uint64_t data = 0;
	volatile uint32_t *addr_32;
	volatile uint64_t *addr_64;
	uint8_t i = 0;

	switch (len) {
		case 4:
			line_max_num = 8;
			break;
		case 8:
			line_max_num  = 4;
			break;
	}
	for (i = 0; i < num; i++ ) {
		if((i % line_max_num) == 0) {
			if(i != 0)
				printf("\n");
			printf("%0lx:", base_addr);
		}
		switch (len) {
			case 4:
			   // data = *((volatile uint32_t *)(base_addr));
				printf(" 0x%08lx ",*((volatile uint32_t *)(base_addr)));
				break;
			case 8:
				//data = *((volatile uint64_t *)(base_addr));
				printf(" 0x%016lx ",*((volatile uint64_t *)(base_addr)));
				break;
		}
		base_addr += len;
	}
	printf("\n");
}

int get_fuse_value(uintptr_t addr ,uint32_t mask, uint32_t offset, int is_signed)
{
	int raw_value, value;
	raw_value = (VOLTPLAN_HWIO_IN_MASK(addr, mask) >> offset);
	value = raw_value;

	if (is_signed) {
		uint32_t number_of_bits_we_care_about = 0;
		uint32_t mask_for_counting = mask >> offset;
		uint32_t value_mask = 0;
		int signed_flag = 0;

		while (mask_for_counting) {
			number_of_bits_we_care_about++;
			mask_for_counting = mask_for_counting >> 1;
		}
		//get the mask without signed bit.
		value_mask = (1 << (number_of_bits_we_care_about - 1)) - 1;
		//get the value without signed bit.
		value = raw_value & value_mask;
		//get the value of the signed bit
		signed_flag = raw_value & (1 << (number_of_bits_we_care_about - 1));

		if (signed_flag)
		   value = -value;
	}
	return value;
}

void decode_voltplan_fuse(voltplan_fuse *fuse, int is_signed)
{
	int count = fuse[0].count;
	int redun_count = fuse[0].redun_count;
	int value;

	if (count) {
		value = get_fuse_value(fuse[0].data[0].address, fuse[0].data[0].mask, fuse[0].data[0].offset, is_signed);
		printf("| %-04d ", value);
	}
	if (redun_count) {
		value = get_fuse_value(fuse[0].redun_data[0].address, fuse[0].redun_data[0].mask, fuse[0].redun_data[0].offset, is_signed);
		printf("%-4d", value);
	} else
		printf("NULL");
}

int32_t cal_ceiling(voltplan_fuse *base_fuse, voltplan_fuse *volt_fuse, int volt_size)
{
	int base_volt = 0;
	int volt = 0;

	if (base_fuse[0].count)
		base_volt = (VOLTPLAN_HWIO_IN_MASK(base_fuse[0].data[0].address, base_fuse[0].data[0].mask) >> base_fuse[0].data[0].offset);

	if (volt_fuse[0].count)
		volt = get_fuse_value(volt_fuse[0].data[0].address, volt_fuse[0].data[0].mask, volt_fuse[0].data[0].offset, 1);

	return (base_volt * STEP_5000 + volt * volt_size);	//5mV steps
}

uint32_t cal_freq_to_M(voltplan_fuse	* freq_fuse)
{
	int freq = 0;

	if (freq_fuse[0].count)
		freq = (VOLTPLAN_HWIO_IN_MASK(freq_fuse[0].data[0].address, freq_fuse[0].data[0].mask) >> freq_fuse[0].data[0].offset);

	return (freq * FF_MULTIPLIER_20M);	 //20M
}

void print_fuse_per_mode(voltplan_fuse_data *fuse_data, int is_global)
{
	fuse_item_id i = FUSE_VOLT;
	uint32_t base_volt = 0;
	uint32_t freq = 0;
	int is_signed = 0;
	int volt_size;

	voltplan_fuse* fuse_item[8] =
	{
		fuse_data->volt,
		fuse_data->quot,
		fuse_data->rosel,
		fuse_data->voltOffset,
		fuse_data->quotOffset,
		fuse_data->avmVminTh,
		fuse_data->cpuBaseVolt,
		fuse_data->cpuFreq
	  };

	 for (i = FUSE_VOLT; i < FUSE_MAX; i++) {
		if(NULL == fuse_item[i] ) {
			printf("|   NULL   ");
		} else {
			is_signed = (i == FUSE_VOLT) ? 1 : 0;
			decode_voltplan_fuse(fuse_item[i], is_signed);
		}
	}

	volt_size = (is_global ? 15: 5);

	base_volt =  cal_ceiling(fuse_item[FUSE_CPUBASEVOLT], fuse_item[FUSE_VOLT], volt_size);
	printf("|  %-6d ", base_volt);

	if(NULL == fuse_item[FUSE_FREQ])
	   printf("|   NULL  ", base_volt);
	else {
	   freq = cal_freq_to_M(fuse_item[FUSE_FREQ]);
	   printf("|  %-6d ", freq);
	}
	printf("|\n");
}

#if 0
void print_fuse_data(voltplan_fuse_data *fuse_data)
{
	int i = 0;
	fuse_data_t fuse_item[8] =
	 {
		{"volt", fuse_data->volt},
		{"quot", fuse_data->quot},
		{"rosel", fuse_data->rosel},
		{"voltOffset", fuse_data->voltOffset},
		{"quotOffset", fuse_data->quotOffset},
		{"avmVminTh", fuse_data->avmVminTh},
		{"cpuBaseVolt", fuse_data->cpuBaseVolt},
		{"cpuFreq", fuse_data->cpuFreq}
	  };

	for (i =0; i < 8; i++) {
		if (i == 4)
			printf("\n");
		if (fuse_item[i].item_data) {
			printf("%-12s:", fuse_item[i].name);
			decode_voltplan_fuse(fuse_item[i].item_data);
		} else
			printf("%-12s: NULL    ", fuse_item[i].name);
	}
}
#endif

static void read_clock_setting_fuse(clock_fuse_setting *fuse_setting)
{
     uint32_t fuse_val;

    /* Global settings */
    fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW33_LSB));   //HWIO_QFPROM_CORR_SPARE_REG27_ROW33_LSB_ADDR
    fuse_setting->OvrEn = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_EN);
    fuse_setting->OvrInvEn = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_INV_EN);
    fuse_setting->OvrDcaEn = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_DCA_EN);
    fuse_setting->OvrTdlSel = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_TDL_SEL);
    fuse_setting->OvrMuxSel = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC_CLK_CFG_OVR_MUX_SEL);

    /* Per APC settings */
    fuse_setting->OvrDcaVal[0] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC00_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[1] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC01_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[2] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_LSB_APC02_CLK_CFG_OVR_DCA_VAL);
    fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW33_MSB));
    fuse_setting->OvrDcaVal[3] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC03_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[4] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC04_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[5] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC05_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[6] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW33_MSB_APC06_CLK_CFG_OVR_DCA_VAL);
    fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW34_LSB));
    fuse_setting->OvrDcaVal[7] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC07_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[8] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC08_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[9] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC09_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[10] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC10_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[11] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC11_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[12] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_LSB_APC12_CLK_CFG_OVR_DCA_VAL);
    fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW34_MSB));
    fuse_setting->OvrDcaVal[13] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC13_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[14] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC14_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[15] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC15_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[16] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW34_MSB_APC16_CLK_CFG_OVR_DCA_VAL);
    fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW35_LSB));
    fuse_setting->OvrDcaVal[17] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC17_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[18] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC18_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[19] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC19_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[20] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC20_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[21] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC21_CLK_CFG_OVR_DCA_VAL);
    fuse_setting->OvrDcaVal[22] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW35_LSB_APC22_CLK_CFG_OVR_DCA_VAL);
    fuse_val = inp32(HWIO_ADDR(QFPROM_CORR_SPARE_REG27_ROW35_MSB));
    fuse_setting->OvrDcaVal[23] = EXTRACT_FUSE_VAL(fuse_val, QFPROM_CORR_SPARE_REG27_ROW35_MSB_APC23_CLK_CFG_OVR_DCA_VAL);
}


static void print_data(clock_fuse_setting *fuse)
{
    int i;

    printf("--------------------Clock settings---------------------------------------------------\n");
    printf("|   OvrEn  | OvrInvEn | OvrDcaEn | OvrTdlSel| OvrMuxSel|\n");
    printf("|%5d     |%5d     |%5d     |%5d     |%5d     |\n",fuse->OvrEn, fuse->OvrInvEn, fuse->OvrDcaEn, fuse->OvrTdlSel, fuse->OvrMuxSel);
    printf("-----------------------OvrDcaVal----------------------------------------------------\n");

    for(i = 0; i < 12; ++i) {
        printf("| cl%02d ", i);
    }
    printf("|\n");
    for(i = 0; i < 12; ++i) {
        printf("| 0x%02x ", fuse->OvrDcaVal[i]);
    }
    printf("|\n------------------------------------------------------------------------------------\n");

    for(i = 12; i < 24; ++i) {
        printf("| cl%02d ", i);
    }
    printf("|\n");
    for(i = 12; i < 24; ++i) {
        printf("| 0x%02x ", fuse->OvrDcaVal[i]);
    }
    printf("|\n");
    printf("------------------------------------------------------------------------------------------\n");
}

void print_clock_setting_fuse()
{
    clock_fuse_setting clock_setting;
    read_clock_setting_fuse(&clock_setting);
    print_data(&clock_setting);
}

static uint64_t get_macaddr(uint8_t id)
{
	uint32_t mac_msb,mac_lsb;
	uint64_t mac_addr;

	switch (id) {
		case 0:
			mac_msb = HWIO_INF(QFPROM_CORR_SPARE_REG29_ROW0_MSB, EMAC_0_MAC_ADDRESS_MSB);
			mac_lsb = HWIO_INF(QFPROM_CORR_SPARE_REG29_ROW0_LSB, EMAC_0_MAC_ADDRESS_LSB);
			break;

		case 1:
			mac_msb = HWIO_INF(QFPROM_CORR_SPARE_REG29_ROW1_MSB, EMAC_1_MAC_ADDRESS_MSB);
			mac_lsb = HWIO_INF(QFPROM_CORR_SPARE_REG29_ROW1_LSB, EMAC_1_MAC_ADDRESS_LSB);
			break;
	}
	mac_addr = mac_msb;
	mac_addr = (mac_addr << 32)| mac_lsb;
	return mac_addr;
}

void print_r29_macaddr()
{
	uint64_t raw_mac_addr;
	uint8_t mac_addr[6];
	uint8_t i;

	printf("==========================Region29 EMAC========================\n");
	for(i = 0; i < 2; i++) {
		raw_mac_addr = get_macaddr(i);
		mac_addr[0] = (raw_mac_addr >> 40) & 0xFF;
		mac_addr[1] = (raw_mac_addr >> 32) & 0xFF;
		mac_addr[2] = (raw_mac_addr >> 24) & 0xFF;
		mac_addr[3] = (raw_mac_addr >> 16) & 0xFF;
		mac_addr[4] = (raw_mac_addr >> 8) & 0xFF;
		mac_addr[5] = raw_mac_addr & 0xFF;

		printf("MAC%d Addr: %02x-%02x-%02x-%02x-%02x-%02x \n", i, mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
	}
	printf("--------------------------------------------------------\n");
}

static uint32_t get_wafer_id()
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW0_LSB_WAFER_ID_BMSK) >> HWIO_QFPROM_CORR_PTE_ROW0_LSB_WAFER_ID_SHFT);
}

static uint32_t get_die_x()
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW0_LSB_DIE_X_BMSK) >> HWIO_QFPROM_CORR_PTE_ROW0_LSB_DIE_X_SHFT);
}

static uint32_t get_die_y()
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW0_LSB_DIE_Y_BMSK) >> HWIO_QFPROM_CORR_PTE_ROW0_LSB_DIE_Y_SHFT);
}

static int get_tdp(void)
{
	int tdp;
	//read redundancy fuse firstly.
	tdp = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW25_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW25_LSB_REDUN_TDP_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW25_LSB_REDUN_TDP_SHFT);

	if(!tdp) {
		tdp = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW20_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW20_LSB_TDP_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW20_LSB_TDP_SHFT);
	}
	return tdp;
}

static int get_iddq_vdda_510(void)
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDA_DDR510_WS1_BMSK) >> HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDA_DDR510_WS1_SHFT);
}

static int get_iddq_vdda_423(void)
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_RAW_PTE_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW1_MSB_IDDQ_VDDA_DDR423_WS1_BMSK) >> HWIO_QFPROM_RAW_PTE_ROW1_MSB_IDDQ_VDDA_DDR423_WS1_SHFT);
}

static int get_iddq_cx(void)
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_RAW_PTE_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW1_LSB_IDDQ_CX_WS1_BMSK) >> HWIO_QFPROM_RAW_PTE_ROW1_LSB_IDDQ_CX_WS1_SHFT);
}

static int get_iddq_vddq_510(void)
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_RAW_PTE_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_MSB_IDDQ_VDDQ_DDR510_WS1_BMSK) >> HWIO_QFPROM_RAW_PTE_ROW2_MSB_IDDQ_VDDQ_DDR510_WS1_SHFT);
}

static int get_iddq_vddq_423(void)
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDQ_DDR423_WS1_BMSK) >> HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDQ_DDR423_WS1_SHFT);
}

void print_iddq(void)
{
	printf("IDDQ:\n");
	printf("| vdda510 |%5d | vdda423 |%5d | vddq510 |%5d | vddq423 |%5d | cx |%5d |\n",
			get_iddq_vdda_510(),
			get_iddq_vdda_423(),
			get_iddq_vddq_510(),
			get_iddq_vddq_423(),
			get_iddq_cx());
}

static uint16_t get_cbf_fmax(void)
{
	uint16_t cbf_fmax;

	cbf_fmax = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CBF_FMAX_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CBF_FMAX_SHFT) * 20;

	if(!cbf_fmax) {
		cbf_fmax = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CBF_FMAX_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CBF_FMAX_SHFT) * 20;
	}
	return cbf_fmax;
}

static uint16_t get_cbf_fbase(void)
{
	uint16_t cbf_fbase;

	cbf_fbase = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_ADDR , HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CBF_FBASE_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CBF_FBASE_SHFT) * 20;

	if (!cbf_fbase) {
		cbf_fbase = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_ADDR , HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CBF_FBASE_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CBF_FBASE_SHFT) * 20;
	}
	return cbf_fbase;
}

static uint16_t get_cpu_fmax(void)
{
	uint16_t cpu_fmax;

	cpu_fmax = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_ADDR , HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CPU_FMAX_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CPU_FMAX_SHFT) * 20;

	if(!cpu_fmax)
		cpu_fmax = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CPU_FMAX_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CPU_FMAX_SHFT) * 20;
	return cpu_fmax;
}

static uint16_t get_cpu_fbase(void)
{
	uint16_t cpu_fbase;

	cpu_fbase = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_ADDR , HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CPU_FBASE_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW21_LSB_REDUN_CPU_FBASE_SHFT) * 20;

	if(!cpu_fbase)
		cpu_fbase = (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_ADDR, HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CPU_FBASE_BMSK) >> HWIO_QFPROM_CORR_SPARE_REG27_ROW16_LSB_CBF_FBASE_SHFT) * 20;
	return cpu_fbase;
}

/*Print the Fbase Fmax TDP value*/
void print_fmax_fbase_tdp()
{
	printf("| CBF_FMX |%5d | CBF_FBASE |%5d | CPU_FMAX |%5d | CPU_FBASE |%5d | TDP | %5d |\n",
			get_cbf_fmax(),
			get_cbf_fbase(),
			get_cpu_fmax(),
			get_cpu_fbase(),
			get_tdp());
	printf("---------------------------------------------------------------------------------------\n");
}

static int get_avm_rc()
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_CALIB_ROW22_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW22_LSB_AVM_RC_BMSK) >> HWIO_QFPROM_CORR_CALIB_ROW22_LSB_AVM_RC_SHFT);
}

static int get_ldo_rc()
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_CALIB_ROW22_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW22_LSB_LDO_RC_BMSK) >> HWIO_QFPROM_CORR_CALIB_ROW22_LSB_LDO_RC_SHFT);
}

static int get_odcm_rc()
{
	return (VOLTPLAN_HWIO_IN_MASK(HWIO_QFPROM_CORR_CALIB_ROW22_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW22_LSB_ODCM_RC_BMSK) >> HWIO_QFPROM_CORR_CALIB_ROW22_LSB_ODCM_RC_SHFT);
}

void print_r20_rom_patch()
{
	uint32_t rom_addr = 0;
	uint32_t low_data;
	uint32_t patch_data = 0;
	bool patch_en = 0;
        int n;

	printf("======Region20 ROM PATCH======\n");
	printf("| item |  Addr	| Patch Data |\n");

	for(n = 0; n < MAX_ROM_PATCH_NUM; n++) {
		patch_en = HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INMI(n, HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_EN_BMSK) >> HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_EN_SHFT;
		if(patch_en) {
			rom_addr = HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INMI(n,HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_ADDR_BMSK) >> HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_ADDR_SHFT;
			patch_data = HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INMI(n, HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_DATA1_BMSK) >> HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_DATA1_SHFT;
			low_data = HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INMI(n, HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_DATA0_BMSK) >> HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_DATA0_SHFT;
			patch_data = (patch_data << 16) | low_data;

			printf("|  %02d  | 0x%04x | 0x%08x |\n", n, rom_addr, patch_data);
		}
	}
	printf("------------------------------\n");
}

void print_cailb_item(void)
{
	printf("| LDO_RC |%3d | AVM_RC |%3d | ODCM_RC |%3d | SW_REDUN_SEL | 0x%x |\n",
			get_ldo_rc(),
			get_avm_rc(),
			get_odcm_rc(),
			HWIO_QFPROM_CORR_CALIB_ROW22_MSB_INM(HWIO_QFPROM_CORR_CALIB_ROW22_MSB_SW_CAL_REDUN_SEL_BMSK));
}

void print_partial_goods()
{
   printf("CPU PARTIAL GOODS: %016lx \n", get_cpu_mask());
   printf("L3 PARTIAL GOODS:  %016lx \n", get_llc_mask());
}

void print_wafer_info()
{
	printf("-WAFER INFO:\n");
	printf("|FOUNDRY ID | 0x%x |WAFER ID | 0x%x | LACTION(X,Y) | (%d , %d) |\n",
			get_foundryid(),
			get_wafer_id(),
			get_die_x(),
			get_die_y());
}

static void print_r1_jtagid()
{
	uint8_t feature_id = 0;
	uint32_t jtag_id_12_31 = 0;

	jtag_id_12_31  = HWIO_QFPROM_CORR_JTAG_ID_LSB_INM(HWIO_QFPROM_CORR_JTAG_ID_LSB_JTAG_ID_BMSK) >> HWIO_QFPROM_CORR_JTAG_ID_LSB_JTAG_ID_SHFT;
	feature_id = HWIO_QFPROM_CORR_JTAG_ID_LSB_INM(HWIO_QFPROM_CORR_JTAG_ID_LSB_FEATURE_ID_BMSK) >> HWIO_QFPROM_CORR_JTAG_ID_LSB_FEATURE_ID_SHFT;

	printf("=================Region1 JTAG_ID=============\n");
	printf("| feature_id | 0x%x | jtag_id_12_31 | 0x%x |\n", feature_id, jtag_id_12_31);
	printf("-----------------------------------------------\n");
}

static void print_r2_rd_wr_perm()
{
	uint32_t rd_data,wr_data;
	uint8_t i =0;

	rd_data = HWIO_QFPROM_CORR_RD_WR_PERM_LSB_IN;
	wr_data = HWIO_QFPROM_CORR_RD_WR_PERM_MSB_IN;

	printf("=============================================Region2 RD_WR PERM=============================================\n");
	printf("| Region |");
	for(i = 0; i < 32; i++) {
		printf(" %02d", i);
	}
	printf(" |\n");
	printf("| RD PRM |");
	for(i = 0; i < 32; i++) {
		printf("  %d", (rd_data >> i) & 0x1);
	}
	printf(" |\n");
	printf("| WR PRM |");
	for(i = 0; i < 32; i++) {
		printf("  %d", (wr_data >> i) & 0x1);
	}
	printf(" |\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
}


static void print_r3_fec_en()
{
	uint32_t fec_data = 0;
	uint32_t i = 0;

	fec_data = HWIO_QFPROM_CORR_FEC_EN_LSB_IN;
	printf("==================================================Region3 FEC EN==========================================\n");
	printf("| Region |");
	for(i = 0; i < 32; i++) {
		printf(" %02d", i);
	}
	printf(" |\n");
	printf("| FEC EN |");
	for(i = 0; i < 32; i++) {
		printf("  %d", (fec_data >> i) & 0x1);
	}
	printf(" |\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
}

static void print_r7_serial_num()
{
	uint32_t serial_num = 0;
	uint16_t chip_id = 0;

	serial_num = get_serialnum();
	chip_id = HWIO_QFPROM_CORR_SERIAL_NUM_MSB_INM(HWIO_QFPROM_CORR_SERIAL_NUM_MSB_CHIP_ID_BMSK);

	printf("==============Region7 SERIAL NUM==============\n");
	printf("| SERIAL_NUM | 0x%x | CHIP_ID | 0x%x |\n\n", serial_num, chip_id);
}

static void print_r8_oem_config()
{
	printf("===================Region8 OEM CONFIG==================\n");
	volatile uint64_t *oem_config_row0_addr = (volatile uint64_t *)(0x000000ff0c7041b0);
	volatile uint64_t *oem_config_row1_addr = (volatile uint64_t *)(0x000000ff0c7041b8);

	printf("OEM_CONFIG_ROW0 	@ 0x%lx = 0x%016lx\n" ,oem_config_row0_addr, (uint64_t)(*oem_config_row0_addr));
	printf("OEM_CONFIG_ROW1 	@ 0x%lx = 0x%016lx\n" ,oem_config_row1_addr, (uint64_t)(*oem_config_row1_addr));
	printf("-------------------------------------------------------\n");
}

static void print_r9_feature_config()
{
	volatile uint64_t *feature_config_row0_addr = (volatile uint64_t *)(0x000000ff0c7041c0);
	volatile uint64_t *feature_config_row1_addr = (volatile uint64_t *)(0x000000ff0c7041c8);
	volatile uint64_t *feature_config_row2_addr = (volatile uint64_t *)(0x000000ff0c7041d0);
	volatile uint64_t *feature_config_row3_addr = (volatile uint64_t *)(0x000000ff0c7041d8);

	printf("===================Region9 FEATURE CONFIG==============\n");
	printf("FEATURE_CONFIG_ROW0 @ 0x%lx = 0x%016lx\n" ,feature_config_row0_addr, (uint64_t)(*feature_config_row0_addr));
	printf("FEATURE_CONFIG_ROW1 @ 0x%lx = 0x%016lx\n" ,feature_config_row1_addr, (uint64_t)(*feature_config_row1_addr));
	printf("FEATURE_CONFIG_ROW2 @ 0x%lx = 0x%016lx\n" ,feature_config_row2_addr, (uint64_t)(*feature_config_row2_addr));
	printf("FEATURE_CONFIG_ROW3 @ 0x%lx = 0x%016lx\n" ,feature_config_row3_addr, (uint64_t)(*feature_config_row3_addr));
	printf("-------------------------------------------------------\n");
}

static void print_r10_usb_pid_vid()
{
	uint16_t pid0, pid1, vid;

	pid0 = HWIO_QFPROM_CORR_USB_VID_PID_LSB_INM(HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID0_BMSK) >> HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID0_SHFT;
	pid1 = HWIO_QFPROM_CORR_USB_VID_PID_LSB_INM(HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID1_BMSK) >> HWIO_QFPROM_CORR_USB_VID_PID_LSB_PID1_SHFT;
	vid = HWIO_QFPROM_CORR_USB_VID_PID_MSB_INM(HWIO_QFPROM_CORR_USB_VID_PID_MSB_VID_BMSK) >> HWIO_QFPROM_CORR_USB_VID_PID_MSB_VID_SHFT;

	printf("===================Region10 USB PID VID=============\n");
	printf("| PID0 | 0x%04x | PID1 | 0x%04x | VID | 0x%04x |\n", pid0, pid1, vid);
	printf("----------------------------------------------------\n");

}

static void print_r11_debug_key()
{
	uint32_t key0, key1;

	key0 = HWIO_QFPROM_CORR_DEBUG_KEY_LSB_IN;
	key1 = HWIO_QFPROM_CORR_DEBUG_KEY_MSB_IN;

	printf("=============Region11 DEBUG KEY==========\n");
	printf("| KEY0 | 0x%08x | KEY1 | 0x%08x |\n", key0, key1);
	printf("-----------------------------------------\n");
}

static void print_r12_mem_acc()
{
	printf("================Region12 MEM ACCSEL===============\n");
	print_raw_data(HWIO_QFPROM_CORR_MEM_ACCEL_ROW0_LSB_ADDR, 8, 2);
	printf("--------------------------------------------------\n");
}

static void print_r14_calib()
{
	printf("=======================================Region14 CALIB===================================\n");
	print_cailb_item();
	printf("----------------------------------------------------------------------------------------\n");
	print_raw_data(HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR, 8, 30);
	printf("----------------------------------------------------------------------------------------\n");
}

static void print_r15_pte()
{
	printf("========================================Region15 PTE====================================\n");
	print_wafer_info();
	print_iddq();
	printf("-----------------------------------------------------------------------------------------\n");
	print_raw_data(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, 8, 17);
	printf("-----------------------------------------------------------------------------------------\n");
}

static void print_r17_tsens()
{
	printf("================================Region17 TSENS=============================\n");
	tsens_fuses();
}

/*useed for the region that only print the raw data
 *region_id: the id of the region(1-31)
 *name	   : the decription at the headline
 *addr	   : the star addr of the target region
 *num	   : the num of data to be printed */
static void print_target_region_raw(uint8_t region_id, char *name, uint64_t addr, uint16_t num)
{
	printf("=================================Region%02d %s=====================================\n",region_id, name);
	print_raw_data(addr, 8, num);
	printf("----------------------------------------------------------------------------------------\n");
}

static void print_r27_tdp()
{
	printf("===================================Region27 TDP========================================\n");
	print_fmax_fbase_tdp();
	print_clock_setting_fuse();
	print_raw_data(HWIO_QFPROM_CORR_SPARE_REG27_ROW0_LSB_ADDR, 8, 55);
	printf("--------------------------------------------------------------------------------------\n");
}

static void get_fuse()
{
	voltplan_domain_id rail_id;
	voltplan_versioned_voltage_plan *vvp = NULL;
	voltplan_voltage_plan *vp;
	voltplan_fuse_data *fuse;

	int i,j;
	int domain_id = 0;
	int chipver = 0;
	int max,min;
	uint32_t serial_num = 0;
	uint16_t product_code = 0;
	uint32_t foundryid = 0;
	uint8_t generation, feature, bin;
	int is_global = LOCAL;
	uint32_t wafer_id = 0;

	check_chip_family();
	generation = get_generation();
	feature = get_feature();
	bin = get_bin();
	chipver = get_version();
	serial_num = get_serialnum();
	foundryid = get_foundryid();

	//lOG:Print the chip info
	printf("Serial Num :  0x%x \n", serial_num);
	printf("Chip Version: %d.%d \n", chipver >> 16 , chipver & 0xffff);
	printf("Foundryid:	  0x%x \n", foundryid);
	printf("Chip ID:	  0x%04x @FUSE_SERIAL_MSB\n", HWIO_QFPROM_CORR_SERIAL_NUM_MSB_INM(HWIO_QFPROM_CORR_SERIAL_NUM_MSB_CHIP_ID_BMSK) >> HWIO_QFPROM_CORR_SERIAL_NUM_MSB_CHIP_ID_SHFT);
	print_product_code();

	get_raw_chip_info();

	print_partial_goods();

	print_r1_jtagid();
	print_r2_rd_wr_perm();
	print_r3_fec_en();
	print_target_region_raw(5, "PARTIAL GOOD", HWIO_QFPROM_RAW_PARTIAL_GOOD_ROW0_LSB_ADDR, 6);
	print_r7_serial_num();
	print_r8_oem_config();
	print_r9_feature_config();
	print_r10_usb_pid_vid();
	print_r11_debug_key();
	print_r12_mem_acc();
	print_r14_calib();
	print_r15_pte();
	print_r17_tsens();
	print_r20_rom_patch();
	print_target_region_raw(21, "PRIKEY DEV", HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(0), 5);
	print_target_region_raw(22, "SECKEY DEV", HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(0), 5);
	print_target_region_raw(23, "OEM_PK_HASH", HWIO_QFPROM_CORR_OEM_PK_HASH_ROWn_LSB_ADDR(0), 5);
	print_target_region_raw(24, "OEM_SEC BOOT", HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(0), 4);
	print_target_region_raw(25, "QC_SEC BOOT", HWIO_QFPROM_CORR_QC_SEC_BOOT_ROWn_LSB_ADDR(0), 4);
	print_r27_tdp();
	print_r29_macaddr();

	for (rail_id = VOLTPLAN_RAIL_MX; rail_id < VOLTPLAN_RAIL_MAX; ++rail_id) {
		int count = 0 ;

		is_global = ((rail_id < VOLTPLAN_RAIL_MISC_MAX ) ? GLOBAL : LOCAL);

		vvp = voltplan_get_versioned_voltage_plan( rail_id );
		if (NULL == vvp)
			continue;
		for (j = 0; j < MAX_VER_NUM; j++) {
			max = vvp->list[j].version.max;
			min = vvp->list[j].version.min;
			get_cpu_fbase();
			if ((vvp->list[j].version.min <= chipver) && (chipver <= vvp->list[j].version.max) ) {
				vp = vvp->list[j].cfg;
				break;
			}
		}
		count = vp->modesCount;
		printf("_____________________________________________________________________________________________________________\n");
		printf("---------------------------------------Domain %s------------------------------------------------------\n", rail_name[domain_id]);
		printf("|   volt   |   quot   |   rosel  |  voltOf  |  quotOf  | avmVminTh| BaseVolt | cpuFreq	| ceiling | freq(M) |\n");

		for(i = 0; i < count; i++){
			fuse = vp->modes[i].fuses;
			print_fuse_per_mode(fuse, is_global);
		}
		domain_id ++;
	}
	printf("_____________________________________________________________________________________________________________\n");
}

int do_get_fuse(int argc, char * argv[])
{
	get_fuse();
	return 0;
}

MK_CMD(getfuse, do_get_fuse, "print command description/usage",
    " getfuse \n"
    "    -get the fuse data\n"
);
