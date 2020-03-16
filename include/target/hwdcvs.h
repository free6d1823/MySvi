#ifndef _HWDCVS_H
#define _HWDCVS_H
#include <asm/mach-qdf2400/hwdcvs_hwio.h>
#include <asm/mach/cpus.h>

typedef enum {
    HWDCVS_APM_MODE_MX,
    HWDCVS_APM_MODE_APC,
    HWDCVS_APM_NUM_MODES,
} hwdcvs_apm_mode_t;


#define  HWDCVS_SUCCESS                       0
#define  HWDCVS_ERROR                0x80000000
#define  HWDCVS_UNSUPPORTED_CLUSTER  0x80000001

int do_apm_switch(int argc, char * argv[]);

#endif
