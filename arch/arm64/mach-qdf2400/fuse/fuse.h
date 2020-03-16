#ifndef VOLTAGE_PLAN_H
#define VOLTAGE_PLAN_H

#define GET_FUSE_VALUE(addr , mask, offset) ((__inpdw(addr) & (mask)) >> offset)

#define STEP_5000           5              //5mV steps
#define FF_MULTIPLIER_20M   20    //multiplier/* 20MHz units */
#define MAX_VER_NUM         3     //the max num of chip version (now: 1.0 1.1 2.0)

#define LOCAL               0
#define GLOBAL              1

#define MAX_ROM_PATCH_NUM   64
typedef enum
{
    FUSE_VOLT,
    FUSE_QUOT,
    FUSE_ROSEL,
    FUSE_VOLTOFFSET,
    FUSE_QUOTOFFSET,
    FUSE_AVMVINTH,
    FUSE_CPUBASEVOLT,
    FUSE_FREQ,
    FUSE_MAX,
} fuse_item_id;

typedef struct{
    char *name;
    voltplan_fuse* item_data;
}fuse_data_t;

void print_clock_setting_fuse(void);

#endif
