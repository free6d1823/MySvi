#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <target/delay.h>
#include <target/cmdline.h>

#define DEBUG

#ifdef DEBUG
#define log_debug(fmt, ...)	printf(fmt, ##__VA_ARGS__);
#else
#define log_debug(fmt, ...)
#endif

#define APCS_HPSS0_DBG_DEC_ADDR               0xff7e307000ULL
#define APCS_HPSSx_DBG_BASE(x)                (APCS_HPSS0_DBG_DEC_ADDR + (x*0x8000))
#define APCS_HPSSx_ATEST0_EN_ADDR(x)          (APCS_HPSSx_DBG_BASE(x) + 0x00000014)
#define APCS_HPSSx_ATEST1_EN_ADDR(x)          (APCS_HPSSx_DBG_BASE(x) + 0x00000018)
#define APCS_HPSSx_ATEST_CFG_ADDR(x)          (APCS_HPSSx_DBG_BASE(x) + 0x0000001c)

#define APCS_APR0_FLM_CTL_DEC_ADDR            0xff7e246800ULL
#define APCS_APRx_FLM_CTL_BASE(x)             (APCS_APR0_FLM_CTL_DEC_ADDR + (x*0x8000))
#define APCS_APRx_FLM_CTL(x)                  (APCS_APRx_FLM_CTL_BASE(x))
#define APCS_APRx_FLM_RAIL_NCL(x)             (APCS_APRx_FLM_CTL_BASE(x) + 0x00000004)
#define APCS_APRx_FLM_RAIL_PCL(x)             (APCS_APRx_FLM_CTL_BASE(x) + 0x00000008)
#define APCS_APRx_FLM_RAIL_LCT(x)             (APCS_APRx_FLM_CTL_BASE(x) + 0x0000000c)
#define APCS_APRx_FLM_INT_CFG(x)              (APCS_APRx_FLM_CTL_BASE(x) + 0x00000020)
#define APCS_APRx_FLM_INT_RPIT(x)             (APCS_APRx_FLM_CTL_BASE(x) + 0x00000024)
#define APCS_APRx_FLM_INT_IPIT(x)             (APCS_APRx_FLM_CTL_BASE(x) + 0x00000028)

#define APCS_APR0_FLM_STS_DEC_ADDR            0xff7e2c6800ULL
#define APCS_APRx_FLM_STS_BASE(x)             (APCS_APR0_FLM_STS_DEC_ADDR + (x*0x8000))
#define APCS_APRx_FLM_RAIL_IMEAS_SUM(x)       (APCS_APRx_FLM_STS_BASE(x) + 0x40)
#define APCS_APRx_FLM_APC0_CPU0_IMEAS(x)      (APCS_APRx_FLM_STS_BASE(x) + 0x4c)
#define APCS_APRx_FLM_APC0_CPU1_IMEAS(x)      (APCS_APRx_FLM_STS_BASE(x) + 0x50)
#define APCS_APRx_FLM_APC0_L2_IMEAS(x)        (APCS_APRx_FLM_STS_BASE(x) + 0x54)
#define APCS_APRx_FLM_APC1_CPU0_IMEAS(x)      (APCS_APRx_FLM_STS_BASE(x) + 0x58)
#define APCS_APRx_FLM_APC1_CPU1_IMEAS(x)      (APCS_APRx_FLM_STS_BASE(x) + 0x5c)
#define APCS_APRx_FLM_APC1_L2_IMEAS(x)        (APCS_APRx_FLM_STS_BASE(x) + 0x60)
#define APCS_APRx_FLM_APC2_CPU0_IMEAS(x)      (APCS_APRx_FLM_STS_BASE(x) + 0x64)
#define APCS_APRx_FLM_APC2_CPU1_IMEAS(x)      (APCS_APRx_FLM_STS_BASE(x) + 0x68)
#define APCS_APRx_FLM_APC2_L2_IMEAS(x)        (APCS_APRx_FLM_STS_BASE(x) + 0x6c)

#define APCS_HPSS0_CFG_DEC_ADDR               0xff7e287000ULL
#define APCS_HPSSx_CFG_BASE(x)                (APCS_HPSS0_CFG_DEC_ADDR + (x*0x8000))
#define APCS_HPSSx_LDO_CFG(x)                 (APCS_HPSSx_CFG_BASE(x) + 0xc0)
#define APCS_HPSSx_ODCM_CFG(x)                (APCS_HPSSx_CFG_BASE(x) + 0xc8)

#define APCS_APC0_CPU0_DBG_DEC_ADDR           0xff7e300000ULL
#define APCS_APC0_CPU0_ODCM_DEC_ADDR          0xff7e080000ULL
#define APCS_APC0_L2_ODCM_DEC_ADDR            0xff7e084000ULL

#define APCS_APC0_APC_PWR_GATE_DIAG           0xff7e304404ULL
#define APCS_APC0_L2_PWR_GATE_DIAG            0xff7e304004ULL

#define imeas_apc0_cpu0    0x0
#define imeas_apc0_cpu1    0x1
#define imeas_apc0_l2      0x2
#define imeas_apc1_cpu0    0x3
#define imeas_apc1_cpu1    0x4
#define imeas_apc1_l2      0x5
#define imeas_apc2_cpu0    0x6
#define imeas_apc2_cpu1    0x7
#define imeas_apc2_l2      0x8

#define QFPROM_RAW_CALIB_ROWS 15
#define QFPROM_CORR_CALIB_ROW14_MSB_ADDR      0xff0c700314ULL

#define CLUSTER_TO_HPSS(x)     (x/3)


enum atest {
    atest0 = 0,
    atest1
};

enum trim_data {
    ldo_vref_trim = 0,
    imeas_dac_top_trim,
    cpu0_imeas_bhs_trim,
    cpu0_imeas_ldo_trim,
    cpu1_imeas_bhs_trim,
    cpu1_imeas_ldo_trim,
    l2_imeas_bhs_trim,
    l2_imeas_ldo_trim
};

struct routing {
    int        pin;
    char       *pin_info;
    uint8_t    aen_bit;
    uint8_t    atst_cfg;
};

static struct routing routings_a0[] = {
    /* atest0_signal */
    {0,   "I_Vdd_ar_c0",                     0x4,   0x38},
    {1,   "I_percal_throttle_out_obs_apcpd", 0x4,   0x39},
    {2,   "I_Cpu0_ldo_vref_dtn",             0x4,   0x3a},
    {3,   "I_ext_vazref_dtn",                0x4,   0x3b},
    {4,   "I_Cpu0_imeas_ref_sense_dtn",      0x4,   0x3c},
    {5,   "I_Cpu0_imeas_ldo_casc_sense_dtn", 0x4,   0x3d},
    {6,   "I_Cpu0_imeas_bhs_casc_sense_dtn", 0x4,   0x3e},
    {7,   "I_Cpu0_imeas_imir_dtn",           0x4,   0x3f},
    {8,   "I_Vdd_ar_c1",                     0x4,   0x30},
    {9,   "I_Vdd_mx",                        0x4,   0x31},
    {10,  "I_Cpu1_ldo_vref_dtn",             0x4,   0x32},
    {11,  "I_ext_vazref_dtn",                0x4,   0x33},
    {12,  "I_Cpu1_imeas_ref_sense_dtn",      0x4,   0x34},
    {13,  "I_Cpu1_imeas_ldo_casc_sense_dtn", 0x4,   0x35},
    {14,  "I_Cpu1_imeas_bhs_casc_sense_dtn", 0x4,   0x36},
    {15,  "I_Cpu1_imeas_imir_dtn",           0x4,   0x37},
    {16,  "I_Vdd_aon",                       0x4,   0x28},
    {17,  "I_vdd_ar_l2_v0_sense_dtn",        0x4,   0x29},
    {18,  "I_L2_ldo_vref_dtn",               0x4,   0x2a},
    {19,  "I_ext_vazref_dtn",                0x4,   0x2b},
    {20,  "I_L2_imeas_ref_sense_dtn",        0x4,   0x2c},
    {21,  "I_L2_imeas_ldo_casc_sense_dtn",   0x4,   0x2d},
    {22,  "I_L2_imeas_bhs_casc_sense_dtn",   0x4,   0x2e},
    {23,  "I_L2_imeas_imir_dtn",             0x4,   0x2f},
    {24,  "I_cpu0_dac_top_dtn",              0x4,   0x20},
    {25,  "I_memcell_vmin_vref_out_dtn",     0x4,   0x18},
    {26,  "I_Resladder_top_dtn",             0x4,   0x10},
    {27,  "I_L2_dac_out_dtn",                0x4,   0x08},

    {28,  "0_Vdd_ar_c0",                     0x1,   0x00},
    {29,  "0_Vdd_cpu0",                      0x1,   0x01},
    {30,  "0_Cpu0_ldo_vref_dtn",             0x1,   0x02},
    {31,  "0_ext_vazref_dtn",                0x1,   0x03},
    {32,  "0_Cpu0_imeas_ref_sense_dtn",      0x1,   0x04},
    {33,  "0_Cpu0_imeas_ldo_casc_sense_dtn", 0x1,   0x05},
    {34,  "0_Cpu0_imeas_bhs_casc_sense_dtn", 0x1,   0x06},
    {35,  "0_Cpu0_imeas_imir_dtn",           0x1,   0x07},

    {36,  "0_Vdd_ar_c1",                     0x2,   0x00},
    {37,  "0_Vdd_cpu1",                      0x2,   0x01},
    {38,  "0_Cpu1_ldo_vref_dtn",             0x2,   0x02},
    {39,  "0_ext_vazref_dtn",                0x2,   0x03},
    {40,  "0_Cpu1_imeas_ref_sense_dtn",      0x2,   0x04},
    {41,  "0_Cpu1_imeas_ldo_casc_sense_dtn", 0x2,   0x05},
    {42,  "0_Cpu1_imeas_bhs_casc_sense_dtn", 0x2,   0x06},
    {43,  "0_Cpu1_imeas_imir_dtn",           0x2,   0x07},
};

static struct routing routings_a1[] = {
    /* atest1_signal */
    {0,   "I_vdd_ar_l2_v0_sense_dtn",        0x4,   0x00},
    {1,   "I_vdd_ar_l2_v1_sense_dtn",        0x4,   0x01},
    {2,   "I_Cpu0_ldo_vref_dtn",             0x4,   0x02},
    {3,   "I_ext_varef_dtn",                 0x4,   0x03},
    {4,   "I_Cpu0_imeas_ref_sense_dtn",      0x4,   0x04},
    {5,   "I_Cpu0_imeas_ldo_casc_sense_dtn", 0x4,   0x05},
    {6,   "I_Cpu0_imeas_bhs_casc_sense_dtn", 0x4,   0x06},
    {7,   "I_Cpu0_imeas_imir_dtn",           0x4,   0x07},

    {8,   "0_Vdd_ar_c0",                     0x1,   0x00},
    {9,   "0_Vdd_cpu0",                      0x1,   0x01},
    {10,  "0_Cpu0_ldo_vref_dtn",             0x1,   0x02},
    {11,  "0_ext_vazref_dtn",                0x1,   0x03},
    {12,  "0_Cpu0_imeas_ref_sense_dtn",      0x1,   0x04},
    {13,  "0_Cpu0_imeas_ldo_casc_sense_dtn", 0x1,   0x05},
    {14,  "0_Cpu0_imeas_bhs_casc_sense_dtn", 0x1,   0x06},
    {15,  "0_Cpu0_imeas_imir_dtn",           0x1,   0x07},

    {16,  "0_Vdd_ar_c1",                     0x2,   0x00},
    {17,  "0_Vdd_cpu1",                      0x2,   0x01},
    {18,  "0_Cpu1_ldo_vref_dtn",             0x2,   0x02},
    {19,  "0_ext_vazref_dtn",                0x2,   0x03},
    {20,  "0_Cpu1_imeas_ref_sense_dtn",      0x2,   0x04},
    {21,  "0_Cpu1_imeas_ldo_casc_sense_dtn", 0x2,   0x05},
    {22,  "0_Cpu1_imeas_bhs_casc_sense_dtn", 0x2,   0x06},
    {23,  "0_Cpu1_imeas_imir_dtn",           0x2,   0x07},
};


static uint64_t apcs_apc_avm_vtm_cfg[] = {
    0xff80540358,
    0xff81640358,
    0xff81540358,
    0xff80640358,
    0xff80740358,
    0xff81440358,
    0xff81340358,
    0xff80840358,
    0xff80940358,
    0xff81240358,
    0xff81140358,
    0xff80a40358,
    0xff80b40358,
    0xff81180358,
    0xff81280358,
    0xff80c40358,
    0xff80d40358,
    0xff81380358,
    0xff81480358,
    0xff80e40358,
    0xff80f40358,
    0xff81580358,
    0xff81680358,
    0xff81040358,
};

static int _atoi(char *v)
{
    int n = 0;
    while (*v != 0) {
        n = n*10 + (*v - '0');
        v++;
    }
    return n;
}

static void write_32(uint64_t addr, uint32_t value)
{
    log_debug("    write_32(0xff%x, 0x%x)\n", addr, value);

    *(volatile uint32_t*)addr = value;
    return;
}

static uint32_t read_32(uint64_t addr)
{
    log_debug("    read_32(0xff%x)\n", addr);

    return *(volatile uint32_t*)addr;

}

int do_routing(int argc, char * argv[])
{
    uint32_t  src;
    enum atest atst;
    struct routing *r;

    int       hpss=0, cluster=0;
    uint64_t  atst_en_addr, atst_cfg_addr;
    uint32_t  atst_en_value, atst_cfg_value;

    int i;

    if (argc != 4) {
        printf("invalid argc:%d\n", argc);
        return -1;
    }

    /* detect the atest arg */
    if (!strcmp(argv[1], "atst0")){
        atst = atest0;
        r = routings_a0;
    } else if (!strcmp(argv[1], "atst1")){
        atst = atest1;
        r = routings_a1;
    }else {
        printf("invalid atest:%s\n", argv[1]);
        return -1;
    }

    /* detect the source pin */
    src = _atoi(argv[2]);
    r = r + src;

    /* prepare hpss, atest_registers atest_values */
    cluster = _atoi(argv[3]);
    if (cluster > 23){
        printf("invalid cluster:%s\n", argv[3]);
        return -1;
    }

    hpss = CLUSTER_TO_HPSS(cluster);
    atst_en_value = (r->aen_bit) << (3 * (cluster % 3));
    atst_cfg_value = r->atst_cfg;

    if (atst == atest0)
        atst_en_addr = APCS_HPSSx_ATEST0_EN_ADDR(hpss);
    else
        atst_en_addr = APCS_HPSSx_ATEST1_EN_ADDR(hpss);

    atst_cfg_addr = APCS_HPSSx_ATEST_CFG_ADDR(hpss);

    /* update ATEST_EN and ATEST_CFG */
    write_32(atst_en_addr, atst_en_value);
    write_32(atst_cfg_addr, atst_cfg_value);

    printf("    routing %s -> ", r->pin_info);
    if (atst == atest0)
        printf("atet0\n");
    else
        printf("atet1\n");
    return 0;
}

int routing_man(int argc, char * argv[])
{
    int i;
    struct routing *r = routings_a0;

    printf("routing pin details\n");
    printf("atst0:\n");
    for (i = 0; i < sizeof(routings_a0)/sizeof(struct routing); i++) {
        printf("    %d  %s atst0\n", r[i].pin, r[i].pin_info);
    }

    r = routings_a1;
    printf("atst1:\n");
    for (i = 0; i < sizeof(routings_a1)/sizeof(struct routing); i++) {
        printf("    %d  %s atst1\n", i, r[i].pin_info);
    }
    return 0;
}

static void enable_flm(int hpss)
{

    write_32(APCS_APRx_FLM_CTL(hpss),      0x00002203);
    write_32(APCS_APRx_FLM_RAIL_NCL(hpss), 0x00001770);
    write_32(APCS_APRx_FLM_RAIL_PCL(hpss), 0x00001a90);
    write_32(APCS_APRx_FLM_RAIL_LCT(hpss), 0x00001518);
    write_32(APCS_APRx_FLM_INT_CFG(hpss),  0xc8420201);
    write_32(APCS_APRx_FLM_INT_RPIT(hpss), 0x00000780);
    write_32(APCS_APRx_FLM_INT_IPIT(hpss), 0x00005dc0);

}

static void enable_odcm_cpu(int cpu)
{
    int hpss = cpu / 6;
    int _cpu = cpu % 6;

    uint64_t odcm_en_addr = APCS_APC0_CPU0_ODCM_DEC_ADDR + hpss * 0x8000 + _cpu * 0x800;
    write_32(odcm_en_addr, 0x1);
}

static void enable_odcm_l2(int cluster)
{
    int hpss = cluster / 3;
    int _cluster = cluster % 3;

    uint64_t odcm_en_addr = APCS_APC0_L2_ODCM_DEC_ADDR + hpss * 0x8000 + _cluster * 0x800;
    write_32(odcm_en_addr, 0x1);
}

static void odcm_config(int hpss, int value)
{
    write_32(APCS_HPSSx_ODCM_CFG(hpss), value);
}

static void cpu_trim(int cpu, int code)
{
    int hpss = cpu / 6;
    int _cpu = cpu % 6;

    uint64_t pwr_gate_diag = APCS_APC0_CPU0_DBG_DEC_ADDR + 0x04 + hpss * 0x8000 + _cpu * 0x800;
    uint32_t v = (0x1UL << 31) | (code << 24) | (1 << 23) | (code << 16);

    write_32(pwr_gate_diag, v);
}

static int read_imeas(int hpss, uint32_t bits)
{
    uint32_t imeas = 0;

    imeas += (bits & (0x1 << imeas_apc0_cpu0)) ? read_32(APCS_APRx_FLM_APC0_CPU0_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc0_cpu1)) ? read_32(APCS_APRx_FLM_APC0_CPU1_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc0_l2)) ?   read_32(APCS_APRx_FLM_APC0_L2_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc1_cpu0)) ? read_32(APCS_APRx_FLM_APC1_CPU0_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc1_cpu1)) ? read_32(APCS_APRx_FLM_APC1_CPU1_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc1_l2)) ?   read_32(APCS_APRx_FLM_APC1_L2_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc2_cpu0)) ? read_32(APCS_APRx_FLM_APC2_CPU0_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc2_cpu1)) ? read_32(APCS_APRx_FLM_APC2_CPU1_IMEAS(hpss)) : 0;
    imeas += (bits & (0x1 << imeas_apc2_l2)) ?   read_32(APCS_APRx_FLM_APC2_L2_IMEAS(hpss)) : 0;

    return imeas;
}

static uint32_t Imeas_sum[9*1024]; // (6cpus + 3L2)/rail ,each 10 bit.
int do_odcm_read_imeas(int argc, char* argv[])
{
    uint32_t  hpss;

    if(argc != 3){
        printf("invalid argc: %d\n", argc);
        return -1;
    }

    if(!strcmp(argv[1], "read")){
        hpss = _atoi(argv[2]);
        uint32_t count = 0;

        uintptr_t FLM_RAIL_IMEAS_SUM = APCS_APRx_FLM_RAIL_IMEAS_SUM(hpss);

        /*sum imeas 30k times*/
        memset(Imeas_sum, 0, sizeof(Imeas_sum));

        for(count; count < 30 * 1000; count++){
            uint32_t value = *(volatile uint32_t*)FLM_RAIL_IMEAS_SUM;
            udelay(10);
            Imeas_sum[value]++;
        }

        count = 0;
        uint32_t max = 0;
        uint32_t aver = 0;
        uint32_t sum = 0;
        uint32_t value_current = 0;
        for(count; count < 9*1024; count++){
            if(Imeas_sum[count] == 0)
                continue;
            sum += count * Imeas_sum[count];
            if(Imeas_sum[count] >= max){
                max = Imeas_sum[count];
                value_current = count;
        }
    }
        aver = sum / (30 * 1000);
        log_debug("sum: %x:%d, aver: %x:%d ,aver_current: %d mA, maxTimeCurrent: %x:%d\n", sum,sum, aver,aver, aver*5, value_current,value_current);
    }
    else{
        printf("invalid arguments\n");
        return -1;
    }
    return 0;
}

int do_odcm_rsense(int argc, char* argv[])
{
    uint32_t  hpss;
    uint32_t cluster;
    uint32_t cpu;
    int i = 0;
    uint32_t count = 0;

    if(argc != 2){
        printf("invalid argc: %d\n", argc);
        return -1;
    }

    hpss = _atoi(argv[1]);
    cluster = hpss * 3;
    cpu = hpss * 6;
    char *cmd_odcm_read[] = {"odcm", "read", argv[1]};

    /* enable  per-cpu ODCM */
    for (i = cpu; i < cpu + 6; i++){
        enable_odcm_cpu(i);
    }

    /* enable L2 ODCM */
    for (i = cluster; i < cluster + 3; i++){
        enable_odcm_l2(i);
    }

    /* config odcm */
    odcm_config(hpss, 0x804214f7);
    enable_flm(hpss);

    do_odcm_read_imeas(3, cmd_odcm_read);
    return 0;
}


static uint32_t fuse[QFPROM_RAW_CALIB_ROWS*2];
char *trim_type[8] = {
                      "ldo_vref_trim",
                      "imeas_dac_top_trim",
                      "cpu0_imeas_bhs",
                      "cpu0_ldo_trim",
                      "cpu1_imeas_bhs",
                      "cpu1_ldo_trim",
                      "l2_imeas_bhs",
                      "l2_ldo_trim"
                      };

int do_trim_read(int argc, char* argv[])
{
    uint32_t v, shift;
    int cluster, start_bit, mod, index;
    enum trim_data e_trim;

    volatile uint32_t *p = (uint32_t*)QFPROM_CORR_CALIB_ROW14_MSB_ADDR;

    cluster = _atoi(argv[1]);
    e_trim = _atoi(argv[2]);

    /* retrieve the fuse data from HWIO_QFPROM_CORR_CALIB_ROW14_MSB_ADDR to HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR */
    for (int i = 0; i < QFPROM_RAW_CALIB_ROWS*2; i++) {
        fuse[i] = *p--;
    }

    start_bit = cluster * (8 * 5) + e_trim * 5;   // MSB
    index = start_bit / 32;
    mod = start_bit % 32;

    if (32-mod >= 5) {
        v = (fuse[index] << mod) >> (32 - 5);
        log_debug("sb=%d fuse[%d]=0x%x\n", mod, index, fuse[index]);
    } else {
        v = (fuse[index] << mod) >> mod;
        shift = 5 - (32 - mod);
        v = (v << shift) | (fuse[index+1] >> (32 - shift));

        log_debug("sb=%d fuse[%d]=0x%x fuse[%d]=0x%x\n", mod, index, fuse[index], index+1, fuse[index+1]);
    }
    printf("trim_type: %s, trimcode=0x%08x:%d\n",trim_type[e_trim], v, v);
    return 0;
}

int do_apc_trim(int argc, char* argv[])
{
    uint64_t pwr_gate_addr = 0;
    int hpss, cluster, _cluster;
    enum trim_data e_trim;
    uint32_t trim_code;

    cluster = _atoi(argv[1]);

    hpss = cluster / 3;
    _cluster = cluster %3;
    e_trim = _atoi(argv[2]);
    trim_code = _atoi(argv[3]);

    pwr_gate_addr = APCS_APC0_APC_PWR_GATE_DIAG + hpss * 0x8000 + _cluster * 0x800;
    uint32_t code0 = read_32(pwr_gate_addr);
    switch (e_trim) {
        case ldo_vref_trim:
            write_32(pwr_gate_addr, (code0 & (~0xffffUL)) | (0x1<<8) | trim_code);
            break;
        case imeas_dac_top_trim:
            write_32(pwr_gate_addr, (code0 & (~0xffff0000UL)) | (0x1<<24)|(trim_code<<16));
            break;
        default:
            break;
    }
    return 0;
}

MK_CMD(apctrim, do_apc_trim, "trim apc",
    "\n"
    " apctrim {cluster}\n"
    "         {0:ldo_vref_trim; 1:imeas_dac_top_trim;\n"
    "                     2,3: cpu0_imeas_bhs/ldo_trim\n"
    "                     4,5: cpu1_imeas_bhs/ldo_trim\n"
    "                     6,7: l2_imeas_bhs/ldo_trim}\n"
    "         {trimcode 5bits}\n"

);

MK_CMD(odcmtrim, do_odcm_rsense, "odcm trim",
    "\n"
    " odcmtrim {hpss} \n"
    "    -Initialize the hpss/rail  \n"
);

MK_CMD(odcm, do_odcm_read_imeas, "odcm read hpss",
    "\n"
    " odcm read {hpss} \n"
    "    -read FLM_RAIL_IMEAS_SUM \n"
);

MK_CMD(trimread, do_trim_read, "read trim code from fuse",
    "\n"
    " trimread {cluster}\n"
    "          {0:ldo_vref_trim;\n"
    "           1:imeas_dac_top_trim;\n"
    "           2,3: cpu0_imeas_bhs/ldo_trim\n"
    "           4,5: cpu1_imeas_bhs/ldo_trim\n"
    "           6,7: l2_imeas_bhs/ldo_trim}\n"
);

MK_CMD(routing, do_routing, "do routing",
    "routing [atst0|atst1] [signal] [cluster]\n"
    "    - routing_man to see details\n"
);

MK_CMD(routing_man, routing_man, "routing man",
    "print detail routing info\n"
);
