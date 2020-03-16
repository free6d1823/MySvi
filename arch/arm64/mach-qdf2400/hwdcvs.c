#include <target/delay.h>
#include <target/cmdline.h>
#include <target/hwdcvs.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define APC_TO_APR(apc)           ((apc) / 3)
#define APCS_APR0_ADDR(apr)       (APCS_APR0_DCVS_APR_REG_BASE + (apr) * 0x8000)
#define APCS_APR0_STS_ADDR(apr)   (APCS_APR0_APR_STS_REG_BASE + (apr) * 0x8000)
#define APCS_APC00_ADDR(apc)      (APCS_APC00_DCVS_APC_REG_BASE + ((apc) / 3) * 0x8000 + ((apc) % 3) * 0x800)

#define COMMON_OUTF(type, apc, reg, mask, val) \
    HWIO_##type##_##reg##_OUTM( \
        type##_ADDR(apc), \
        HWIO_##type##_##reg##_##mask##_BMSK, \
        val << HWIO_##type##_##reg##_##mask##_SHFT)
#define COMMON_IN(type, apc, reg) \
    HWIO_##type##_##reg##_IN(type##_ADDR(apc))

#define APR_OUTF(apr, reg, field, val)     COMMON_OUTF(APCS_APR0, apr, reg, field, val)
#define APR_STS_IN(apr, reg)               COMMON_IN(APCS_APR0_STS, apr, reg)


int hwdcvs_hal_set_apm_mode(hwdcvs_apm_mode_t apm_mode, uint32_t apr)
{
    uint32_t val;

    switch (apm_mode)
    {
        case HWDCVS_APM_MODE_MX:
            val = 0;
            break;
        case HWDCVS_APM_MODE_APC:
            val = 1;
            break;
        default:
            return HWDCVS_ERROR;
    }
    APR_OUTF(apr, APM_MODE, SW_PWR_MUX_APCC_SEL, val);

    return HWDCVS_SUCCESS;
}

int hwdcvs_hal_wait_for_apm_mode_switch(hwdcvs_apm_mode_t apm_mode, uint32_t apr)
{
    uint32_t mask = 0x1F;
    uint32_t val;

    switch (apm_mode)
    {
        case HWDCVS_APM_MODE_MX:
            val = 0;
            break;
        case HWDCVS_APM_MODE_APC:
            val = 3;
            break;
        default:
            return HWDCVS_ERROR;
    }

    // TODO: Determine appropriate timeout
    while ((APR_STS_IN(apr, APM_CTL_STS) & mask) != val)
    {
        udelay(1);
    }
    return HWDCVS_SUCCESS;
}



int hwdcvs_set_apm_mode(hwdcvs_apm_mode_t apm_mode)
{
    int status = HWDCVS_SUCCESS;
    int apr;

    for(apr = 0; apr < MAX_CPU_RAILS; apr++) {
        status |= hwdcvs_hal_set_apm_mode(apm_mode, apr);
        status |= hwdcvs_hal_wait_for_apm_mode_switch(apm_mode, apr);
    }
    return status;
}


int do_apm_switch(int argc, char * argv[])
{
    char *cmd = NULL;
    hwdcvs_apm_mode_t apm_mode;

    if(argc != 2)
        printf("--ERROR: The parameters not compatible \n");

      /*get the cmd*/
    if(NULL != argv[1])
        cmd = argv[1];
    else
       return false;

    if(strcmp(cmd, "-a") == 0) {
        apm_mode = HWDCVS_APM_MODE_APC;
        printf("Switch APM to APC rails \n");
    } else if(strcmp(cmd, "-m") == 0) {
        apm_mode = HWDCVS_APM_MODE_MX;
        printf("Switch APM to MX rails \n");
    } else
        printf("--ERROR: The parameters not compatible \n");

    hwdcvs_set_apm_mode(apm_mode);

    return 0;
}

MK_CMD(apm, do_apm_switch, "switch power supply",
     " apm -a \n"
    "    -switch to apc rail supply\n"
     " apm -m  \n"
    "    -switch to mx rail supply\n"
);
