#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <asm/mach/hal/msmhwiobase.h>
#include "voltage_plan_types.h"
#include "voltage_plan_target_defs.h"
#include "voltplan_defs.h"
#include "voltplan_fuses_hwio.h"

cpr_margin_cfg margins_1020 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 255, .openLoop = 0, .closedLoop = 0, .maxFloorToCeil = 0 },
                                  { .cprRevMin = 0, .cprRevMax = 255, .openLoop = 0, .closedLoop = 0, .maxFloorToCeil = 0 } }
};


voltplan_fuse_data fuses_10891708083 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW18_LSB, CPR9_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW40_LSB, REDUN_CPR9_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW18_LSB, CPR9_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW40_LSB, REDUN_CPR9_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW18_LSB, CPR9_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW40_LSB, REDUN_CPR9_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_LSB, CPR9_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


cpr_margin_cfg margins_510 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 255, .openLoop = 0, .closedLoop = 0, .maxFloorToCeil = 0 } }
};


voltplan_fuse_data fuses_17012423218 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_MSB, CPR9_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_MSB, REDUN_CPR9_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_MSB, CPR9_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_MSB, REDUN_CPR9_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_MSB, CPR9_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_MSB, REDUN_CPR9_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_MSB, CPR9_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_MSB, REDUN_CPR9_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_LSB, CPR9_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


uint32_t voltplan_get_mode_idx_0(voltplan_voltage_mode val)
{
    switch(val) {
        case VOLTPLAN_VOLTAGE_MODE_SVS: return 0;
        case VOLTPLAN_VOLTAGE_MODE_NOMINAL: return 1;
        default:
            break;
    }

    //VOLTPLAN_ASSERT( false );
    return 0;
}


voltplan_voltage_plan voltage_plan_4639643771 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10891708083, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_17012423218, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_fuse_data fuses_7691872669 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW6_LSB, CPR3_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW28_LSB, REDUN_CPR3_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW6_LSB, CPR3_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW28_LSB, REDUN_CPR3_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW6_LSB, CPR3_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW28_LSB, REDUN_CPR3_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_LSB, CPR3_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


voltplan_fuse_data fuses_14925791572 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_MSB, CPR3_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_MSB, REDUN_CPR3_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_MSB, CPR3_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_MSB, REDUN_CPR3_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_MSB, CPR3_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_MSB, REDUN_CPR3_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_MSB, CPR3_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_MSB, REDUN_CPR3_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_LSB, CPR3_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


voltplan_voltage_plan voltage_plan_3683076084 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_7691872669, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_14925791572, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_fuse_data fuses_10165410332 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW14_LSB, CPR7_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW36_LSB, REDUN_CPR7_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW14_LSB, CPR7_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW36_LSB, REDUN_CPR7_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW14_LSB, CPR7_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW36_LSB, REDUN_CPR7_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_LSB, CPR7_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


voltplan_fuse_data fuses_12378058365 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_MSB, CPR7_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_MSB, REDUN_CPR7_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_MSB, CPR7_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_MSB, REDUN_CPR7_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_MSB, CPR7_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_MSB, REDUN_CPR7_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_MSB, CPR7_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_MSB, REDUN_CPR7_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_LSB, CPR7_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


voltplan_fuse_data fuses_16583499693 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_LSB, CPR7_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_LSB, REDUN_CPR7_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_LSB, CPR7_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_LSB, REDUN_CPR7_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_LSB, CPR7_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_LSB, REDUN_CPR7_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW13_LSB, CPR7_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW35_LSB, REDUN_CPR7_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_LSB, CPR7_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_15131377378 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW14_MSB, CPR7_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW36_MSB, REDUN_CPR7_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW14_MSB, CPR7_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW36_MSB, REDUN_CPR7_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW14_MSB, CPR7_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW36_MSB, REDUN_CPR7_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW14_LSB, CPR7_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW36_LSB, REDUN_CPR7_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_LSB, CPR7_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


uint32_t voltplan_get_mode_idx_1(voltplan_voltage_mode val)
{
    switch(val) {
        case VOLTPLAN_VOLTAGE_MODE_SVS: return 0;
        case VOLTPLAN_VOLTAGE_MODE_NOMINAL: return 1;
        case VOLTPLAN_VOLTAGE_MODE_TURBO: return 2;
        case VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO: return 3;
        default:
            break;
    }

    //VOLTPLAN_ASSERT( false );
    return 0;
}


voltplan_voltage_plan voltage_plan_8689991612 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10165410332, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_12378058365, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_16583499693, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_15131377378, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

voltplan_fuse_data fuses_15189633350 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_MSB, CPR_CBF_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_MSB, REDUN_CPR_CBF_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_MSB, CPR_CBF_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_MSB, REDUN_CPR_CBF_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_MSB, CPR_CBF_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_MSB, REDUN_CPR_CBF_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_MSB, CPR_CBF_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_MSB, REDUN_CPR_CBF_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CBF_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CBF_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CBF_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CBF_FREQ_NOM) } } }
};


voltplan_fuse_data fuses_16129545983 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_LSB, CPR_CBF_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_LSB, REDUN_CPR_CBF_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_LSB, CPR_CBF_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_LSB, REDUN_CPR_CBF_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_LSB, CPR_CBF_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_LSB, REDUN_CPR_CBF_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW3_LSB, CPR_CBF_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW25_LSB, REDUN_CPR_CBF_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_MSB, CBF_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_MSB, REDUN_CBF_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CBF_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CBF_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_7651520375 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW4_MSB, CPR_CBF_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW26_MSB, REDUN_CPR_CBF_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW4_MSB, CPR_CBF_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW26_MSB, REDUN_CPR_CBF_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW4_MSB, CPR_CBF_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW26_MSB, REDUN_CPR_CBF_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW4_LSB, CPR_CBF_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW26_LSB, REDUN_CPR_CBF_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_MSB, CBF_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_MSB, REDUN_CBF_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CBF_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CBF_FREQ_TURBO_L2) } } }
};


uint32_t voltplan_get_mode_idx_2(voltplan_voltage_mode val)
{
    switch(val) {
        case VOLTPLAN_VOLTAGE_MODE_NOMINAL: return 0;
        case VOLTPLAN_VOLTAGE_MODE_TURBO: return 1;
        case VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO: return 2;
        default:
            break;
    }

    //VOLTPLAN_ASSERT( false );
    return 0;
}


voltplan_voltage_plan voltage_plan_6503273215 =
{
    .modesCount = 3,
    .idxLookupFunc = voltplan_get_mode_idx_2,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 930000, .freqDelta = 0, .fuses = &fuses_15189633350, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_16129545983, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1050000, .freqDelta = 400000, .fuses = &fuses_7651520375, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 4,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  930000, .floor =  635000, .freq =  600000},
                                                {.ceiling =  930000, .floor =  635000, .freq =  700000},
                                                {.ceiling =  930000, .floor =  635000, .freq =  800000},
                                                {.ceiling =  930000, .floor =  635000, .freq =  900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1000000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 1500000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 1600000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 1700000},
                                                {.ceiling = 1050000, .floor =  770000, .freq = 1800000},
                                                {.ceiling = 1050000, .floor =  770000, .freq = 1900000},
                                                {.ceiling = 1050000, .floor =  770000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  770000, .freq = 2100000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 16
}; 

voltplan_fuse_data fuses_15241934968 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW8_LSB, CPR4_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW30_LSB, REDUN_CPR4_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW8_LSB, CPR4_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW30_LSB, REDUN_CPR4_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW8_LSB, CPR4_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW30_LSB, REDUN_CPR4_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_MSB, CPR4_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


voltplan_fuse_data fuses_19012208272 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_MSB, CPR4_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_MSB, REDUN_CPR4_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_MSB, CPR4_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_MSB, REDUN_CPR4_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_MSB, CPR4_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_MSB, REDUN_CPR4_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_MSB, CPR4_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_MSB, REDUN_CPR4_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_MSB, CPR4_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


voltplan_voltage_plan voltage_plan_4835744991 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_15241934968, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_19012208272, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_fuse_data fuses_10446139619 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW12_LSB, CPR6_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW34_LSB, REDUN_CPR6_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW12_LSB, CPR6_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW34_LSB, REDUN_CPR6_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW12_LSB, CPR6_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW34_LSB, REDUN_CPR6_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_MSB, CPR6_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


voltplan_fuse_data fuses_14954374583 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_MSB, CPR6_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_MSB, REDUN_CPR6_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_MSB, CPR6_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_MSB, REDUN_CPR6_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_MSB, CPR6_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_MSB, REDUN_CPR6_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_MSB, CPR6_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_MSB, REDUN_CPR6_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_MSB, CPR6_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


voltplan_fuse_data fuses_17640971647 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_LSB, CPR6_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_LSB, REDUN_CPR6_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_LSB, CPR6_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_LSB, REDUN_CPR6_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_LSB, CPR6_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_LSB, REDUN_CPR6_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW11_LSB, CPR6_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW33_LSB, REDUN_CPR6_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_MSB, CPR6_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_16420217248 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW12_MSB, CPR6_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW34_MSB, REDUN_CPR6_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW12_MSB, CPR6_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW34_MSB, REDUN_CPR6_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW12_MSB, CPR6_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW34_MSB, REDUN_CPR6_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW12_LSB, CPR6_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW34_LSB, REDUN_CPR6_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_MSB, CPR6_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


voltplan_voltage_plan voltage_plan_10856524247 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_10446139619, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_14954374583, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_17640971647, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_16420217248, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

voltplan_fuse_data fuses_18853928244 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_LSB, CPR3_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_LSB, REDUN_CPR3_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_LSB, CPR3_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_LSB, REDUN_CPR3_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_LSB, CPR3_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_LSB, REDUN_CPR3_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW5_LSB, CPR3_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW27_LSB, REDUN_CPR3_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_LSB, CPR3_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_17536940537 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW6_MSB, CPR3_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW28_MSB, REDUN_CPR3_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW6_MSB, CPR3_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW28_MSB, REDUN_CPR3_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW6_MSB, CPR3_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW28_MSB, REDUN_CPR3_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW6_LSB, CPR3_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW28_LSB, REDUN_CPR3_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_LSB, CPR3_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


voltplan_voltage_plan voltage_plan_9296836644 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_7691872669, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_14925791572, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_18853928244, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_17536940537, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

voltplan_fuse_data fuses_17773310968 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_LSB, CPR4_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_LSB, REDUN_CPR4_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_LSB, CPR4_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_LSB, REDUN_CPR4_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_LSB, CPR4_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_LSB, REDUN_CPR4_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW7_LSB, CPR4_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW29_LSB, REDUN_CPR4_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_MSB, CPR4_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_12513430557 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW8_MSB, CPR4_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW30_MSB, REDUN_CPR4_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW8_MSB, CPR4_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW30_MSB, REDUN_CPR4_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW8_MSB, CPR4_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW30_MSB, REDUN_CPR4_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW8_LSB, CPR4_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW30_LSB, REDUN_CPR4_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW18_MSB, CPR4_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


voltplan_voltage_plan voltage_plan_10851571893 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_15241934968, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_19012208272, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_17773310968, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_12513430557, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

voltplan_fuse_data fuses_16991586018 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_LSB, CPR9_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_LSB, REDUN_CPR9_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_LSB, CPR9_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_LSB, REDUN_CPR9_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_LSB, CPR9_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_LSB, REDUN_CPR9_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW17_LSB, CPR9_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW39_LSB, REDUN_CPR9_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_LSB, CPR9_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_17405239531 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW18_MSB, CPR9_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW40_MSB, REDUN_CPR9_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW18_MSB, CPR9_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW40_MSB, REDUN_CPR9_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW18_MSB, CPR9_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW40_MSB, REDUN_CPR9_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW18_LSB, CPR9_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW40_LSB, REDUN_CPR9_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_LSB, CPR9_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


voltplan_voltage_plan voltage_plan_8405929341 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10891708083, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_17012423218, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_16991586018, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_17405239531, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

voltplan_fuse_data fuses_10081101813 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW20_LSB, CPR10_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW42_LSB, REDUN_CPR10_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW20_LSB, CPR10_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW42_LSB, REDUN_CPR10_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW20_LSB, CPR10_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW42_LSB, REDUN_CPR10_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_MSB, CPR10_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


voltplan_fuse_data fuses_12346183340 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_MSB, CPR10_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_MSB, REDUN_CPR10_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_MSB, CPR10_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_MSB, REDUN_CPR10_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_MSB, CPR10_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_MSB, REDUN_CPR10_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_MSB, CPR10_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_MSB, REDUN_CPR10_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_MSB, CPR10_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


voltplan_voltage_plan voltage_plan_4992398281 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10081101813, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_12346183340, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_fuse_data fuses_4410950342 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_MSB, CPR_VDS_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_MSB, REDUN_CPR_VDS_TARGET_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW19_MSB, CPR_VDS_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW24_MSB, REDUN_CPR_VDS_BASE_VOLT_SVS) } } },
    .cpuFreq = NULL
};


voltplan_fuse_data fuses_3713117158 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_MSB, CPR_VDS_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_MSB, REDUN_CPR_VDS_TARGET_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW19_MSB, CPR_VDS_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW24_MSB, REDUN_CPR_VDS_BASE_VOLT_NOM) } } },
    .cpuFreq = NULL
};


voltplan_fuse_data fuses_4201881090 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_MSB, CPR_VDS_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_MSB, REDUN_CPR_VDS_TARGET_VOLT_TURBO) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW19_MSB, CPR_VDS_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW24_MSB, REDUN_CPR_VDS_BASE_VOLT_TURBO) } } },
    .cpuFreq = NULL
};


voltplan_fuse_data fuses_6473088726 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_MSB, CPR_VDS_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_MSB, REDUN_CPR_VDS_TARGET_VOLT_TURBO_L2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW32_LSB, CPR_VDS_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW32_MSB, REDUN_CPR_VDS_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = NULL
};


voltplan_voltage_plan voltage_plan_10752356366 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 850000, .freqDelta = 0, .fuses = &fuses_4410950342, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 133000, .fuses = &fuses_3713117158, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // TURBO
        {.fref = 950000, .freqDelta = 134000, .fuses = &fuses_4201881090, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1000000, .freqDelta = 133000, .fuses = &fuses_6473088726, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  850000, .floor =  800000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  800000, .freq = 1333000},
                                                {.ceiling =  950000, .floor =  800000, .freq = 1467000},
                                                {.ceiling = 1000000, .floor =  800000, .freq = 1600000} },
    .allSubModesCount = 4
}; 

cpr_quotient_cfg quotients_13121448678 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1189 },
                                { .ro =  3, .quotient = 1322 },
                                { .ro =  4, .quotient = 1120 },
                                { .ro =  5, .quotient = 1220 },
                                { .ro =  6, .quotient =  783 },
                                { .ro =  7, .quotient =  902 } },
    .kvs = (uint32_t[]) { 221, 265, 213, 257, 207, 260 },
};


voltplan_fuse_data fuses_3484441922 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW0_MSB, CPR_MX_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW22_MSB, REDUN_CPR_MX_TARGET_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_MSB, CPR_MX_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_MSB, REDUN_CPR_MX_BASE_VOLT_NOM) } } },
    .cpuFreq = NULL
};


cpr_quotient_cfg quotients_10007411787 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1332 },
                                { .ro =  3, .quotient = 1465 },
                                { .ro =  4, .quotient = 1258 },
                                { .ro =  5, .quotient = 1356 },
                                { .ro =  6, .quotient =  910 },
                                { .ro =  7, .quotient = 1040 } },
    .kvs = (uint32_t[]) { 221, 265, 213, 257, 207, 260 },
};


voltplan_fuse_data fuses_3628910654 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW0_MSB, CPR_MX_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW22_MSB, REDUN_CPR_MX_TARGET_VOLT_TURBO) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW19_LSB, CPR_MX_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW24_LSB, REDUN_CPR_MX_BASE_VOLT_TURBO) } } },
    .cpuFreq = NULL
};


cpr_quotient_cfg quotients_8844675470 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1558 },
                                { .ro =  3, .quotient = 1679 },
                                { .ro =  4, .quotient = 1437 },
                                { .ro =  5, .quotient = 1554 },
                                { .ro =  6, .quotient = 1106 },
                                { .ro =  7, .quotient = 1238 } },
    .kvs = (uint32_t[]) { 221, 265, 213, 257, 207, 260 },
};


voltplan_fuse_data fuses_3662216750 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW0_MSB, CPR_MX_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW22_MSB, REDUN_CPR_MX_TARGET_VOLT_TURBO_L2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW19_LSB, CPR_MX_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW24_LSB, REDUN_CPR_MX_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = NULL
};


voltplan_voltage_plan voltage_plan_6452235778 =
{
    .modesCount = 3,
    .idxLookupFunc = voltplan_get_mode_idx_2,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 885000, .freqDelta = 0, .fuses = &fuses_3484441922, .quotients = &quotients_13121448678, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL },

        // TURBO
        {.fref = 950000, .freqDelta = 0, .fuses = &fuses_3628910654, .quotients = &quotients_10007411787, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 0, .fuses = &fuses_3662216750, .quotients = &quotients_8844675470, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  885000, .floor =  800000, .freq =       0},
                                                {.ceiling =  950000, .floor =  800000, .freq =       0},
                                                {.ceiling = 1055000, .floor =  800000, .freq =       0} },
    .allSubModesCount = 3
}; 

voltplan_fuse_data fuses_15940326352 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_LSB, CPR10_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_LSB, REDUN_CPR10_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_LSB, CPR10_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_LSB, REDUN_CPR10_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_LSB, CPR10_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_LSB, REDUN_CPR10_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW19_LSB, CPR10_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW41_LSB, REDUN_CPR10_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_MSB, CPR10_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_20234288641 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW20_MSB, CPR10_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW42_MSB, REDUN_CPR10_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW20_MSB, CPR10_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW42_MSB, REDUN_CPR10_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW20_MSB, CPR10_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW42_MSB, REDUN_CPR10_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW20_LSB, CPR10_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW42_LSB, REDUN_CPR10_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW21_MSB, CPR10_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


voltplan_voltage_plan voltage_plan_10202482800 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10081101813, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_12346183340, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_15940326352, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_20234288641, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

voltplan_fuse_data fuses_13310859207 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW16_LSB, CPR8_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW38_LSB, REDUN_CPR8_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW16_LSB, CPR8_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW38_LSB, REDUN_CPR8_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW16_LSB, CPR8_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW38_LSB, REDUN_CPR8_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_MSB, CPR8_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


voltplan_fuse_data fuses_13346258845 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_MSB, CPR8_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_MSB, REDUN_CPR8_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_MSB, CPR8_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_MSB, REDUN_CPR8_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_MSB, CPR8_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_MSB, REDUN_CPR8_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_MSB, CPR8_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_MSB, REDUN_CPR8_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_MSB, CPR8_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


voltplan_fuse_data fuses_16108318381 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_LSB, CPR8_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_LSB, REDUN_CPR8_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_LSB, CPR8_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_LSB, REDUN_CPR8_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_LSB, CPR8_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_LSB, REDUN_CPR8_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW15_LSB, CPR8_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW37_LSB, REDUN_CPR8_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_MSB, CPR8_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_15245481486 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW16_MSB, CPR8_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW38_MSB, REDUN_CPR8_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW16_MSB, CPR8_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW38_MSB, REDUN_CPR8_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW16_MSB, CPR8_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW38_MSB, REDUN_CPR8_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW16_LSB, CPR8_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW38_LSB, REDUN_CPR8_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW20_MSB, CPR8_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


voltplan_voltage_plan voltage_plan_11368049843 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_13310859207, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_13346258845, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_16108318381, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_15245481486, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

voltplan_fuse_data fuses_11894824496 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW10_LSB, CPR5_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW32_LSB, REDUN_CPR5_TARGET_VOLT_SVS) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW10_LSB, CPR5_QUOT_VMIN_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW32_LSB, REDUN_CPR5_QUOT_VMIN_SVS) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW10_LSB, CPR5_RO_SEL_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW32_LSB, REDUN_CPR5_RO_SEL_SVS) } } },
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_LSB, CPR5_AVM_VMIN_THRESH_SVS) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_SVS) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_SVS) } } }
};


voltplan_fuse_data fuses_17621622567 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_MSB, CPR5_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_MSB, REDUN_CPR5_TARGET_VOLT_NOM) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_MSB, CPR5_QUOT_VMIN_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_MSB, REDUN_CPR5_QUOT_VMIN_NOM) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_MSB, CPR5_RO_SEL_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_MSB, REDUN_CPR5_RO_SEL_NOM) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_MSB, CPR5_QUOT_OFFSET_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_MSB, REDUN_CPR5_QUOT_OFFSET_NOM) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_LSB, CPR5_AVM_VMIN_THRESH_NOM) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_MSB, CPU_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_MSB, REDUN_CPU_BASE_VOLT_NOM) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_NOM) } } }
};


voltplan_voltage_plan voltage_plan_6760797210 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_11894824496, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_17621622567, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_voltage_plan voltage_plan_3716739967 =
{
    .modesCount = 3,
    .idxLookupFunc = voltplan_get_mode_idx_2,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 830000, .freqDelta = 0, .fuses = &fuses_15189633350, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 950000, .freqDelta = 300000, .fuses = &fuses_16129545983, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 500000, .fuses = &fuses_7651520375, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 4,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  830000, .floor =  635000, .freq =  600000},
                                                {.ceiling =  830000, .floor =  635000, .freq =  700000},
                                                {.ceiling =  830000, .floor =  635000, .freq =  800000},
                                                {.ceiling =  830000, .floor =  635000, .freq =  900000},
                                                {.ceiling =  830000, .floor =  635000, .freq = 1000000},
                                                {.ceiling =  830000, .floor =  635000, .freq = 1100000},
                                                {.ceiling =  830000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  830000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  830000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  950000, .floor =  710000, .freq = 1500000},
                                                {.ceiling =  950000, .floor =  710000, .freq = 1600000},
                                                {.ceiling =  950000, .floor =  710000, .freq = 1700000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 1800000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 1900000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2000000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2100000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 16
}; 

voltplan_voltage_plan voltage_plan_6740294550 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10165410332, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_12378058365, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_fuse_data fuses_18379326175 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_LSB, CPR5_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_LSB, REDUN_CPR5_TARGET_VOLT_TURBO) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_LSB, CPR5_QUOT_VMIN_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_LSB, REDUN_CPR5_QUOT_VMIN_TURBO) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_LSB, CPR5_RO_SEL_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_LSB, REDUN_CPR5_RO_SEL_TURBO) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW9_LSB, CPR5_QUOT_OFFSET_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW31_LSB, REDUN_CPR5_QUOT_OFFSET_TURBO) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_LSB, CPR5_AVM_VMIN_THRESH_TURBO) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW16_MSB, CPU_FREQ_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW21_MSB, REDUN_CPU_FREQ_TURBO) } } }
};


voltplan_fuse_data fuses_15545634456 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW10_MSB, CPR5_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW32_MSB, REDUN_CPR5_TARGET_VOLT_TURBO_L2) } } },
    .quot       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW10_MSB, CPR5_QUOT_VMIN_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW32_MSB, REDUN_CPR5_QUOT_VMIN_TURBO_L2) } } },
    .rosel      = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW10_MSB, CPR5_RO_SEL_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW32_MSB, REDUN_CPR5_RO_SEL_TURBO_L2) } } },
    .quotOffset = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW10_LSB, CPR5_QUOT_OFFSET_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW32_LSB, REDUN_CPR5_QUOT_OFFSET_TURBO_L2) } } },
    .voltOffset = NULL,
    .avmVminTh = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW19_LSB, CPR5_AVM_VMIN_THRESH_TURBO_L2) }, .redun_count = 0, .redun_data = (struct raw_fuse_data[]) {  } } },
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW18_LSB, CPU_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW23_LSB, REDUN_CPU_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW17_LSB, CPU_FREQ_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW22_LSB, REDUN_CPU_FREQ_TURBO_L2) } } }
};


voltplan_voltage_plan voltage_plan_11191877087 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_11894824496, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_17621622567, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_18379326175, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_15545634456, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

cpr_quotient_cfg quotients_10075471405 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  821 },
                                { .ro =  7, .quotient =  948 },
                                { .ro = 11, .quotient = 1546 },
                                { .ro = 12, .quotient = 1030 } },
    .kvs = (uint32_t[]) { 207, 260, 287, 269 },
};


cpr_quotient_cfg quotients_10788676127 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  960 },
                                { .ro =  7, .quotient = 1095 },
                                { .ro = 11, .quotient = 1711 },
                                { .ro = 12, .quotient = 1186 } },
    .kvs = (uint32_t[]) { 207, 260, 287, 269 },
};


cpr_quotient_cfg quotients_9672705664 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient = 1173 },
                                { .ro =  7, .quotient = 1301 },
                                { .ro = 11, .quotient = 1951 },
                                { .ro = 12, .quotient = 1461 } },
    .kvs = (uint32_t[]) { 207, 260, 287, 269 },
};


voltplan_voltage_plan voltage_plan_7152984173 =
{
    .modesCount = 3,
    .idxLookupFunc = voltplan_get_mode_idx_2,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 985000, .freqDelta = 0, .fuses = &fuses_3484441922, .quotients = &quotients_10075471405, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 0, .fuses = &fuses_3628910654, .quotients = &quotients_10788676127, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1050000, .freqDelta = 0, .fuses = &fuses_3662216750, .quotients = &quotients_9672705664, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  985000, .floor =  800000, .freq =       0},
                                                {.ceiling = 1050000, .floor =  800000, .freq =       0},
                                                {.ceiling = 1050000, .floor =  800000, .freq =       0} },
    .allSubModesCount = 3
}; 

voltplan_voltage_plan voltage_plan_7365669226 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_10081101813, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_12346183340, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_15940326352, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_20234288641, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

voltplan_voltage_plan voltage_plan_2767815732 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 950000, .freqDelta = 0, .fuses = &fuses_4410950342, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // NOMINAL
        {.fref = 1000000, .freqDelta = 133000, .fuses = &fuses_3713117158, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  950000, .floor =  800000, .freq = 1200000},
                                                {.ceiling = 1000000, .floor =  800000, .freq = 1333000} },
    .allSubModesCount = 2
}; 

uint32_t voltplan_get_mode_idx_3(voltplan_voltage_mode val)
{
    switch(val) {
        case VOLTPLAN_VOLTAGE_MODE_NOMINAL: return 0;
        default:
            break;
    }

    //VOLTPLAN_ASSERT( false );
    return 0;
}


voltplan_voltage_plan voltage_plan_3450773249 =
{
    .modesCount = 1,
    .idxLookupFunc = voltplan_get_mode_idx_3,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 985000, .freqDelta = 0, .fuses = &fuses_3484441922, .quotients = &quotients_10075471405, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  985000, .floor =  800000, .freq =       0} },
    .allSubModesCount = 1
}; 

voltplan_voltage_plan voltage_plan_8382445072 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10446139619, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_14954374583, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 300000, .fuses = &fuses_17640971647, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1155000, .freqDelta = 300000, .fuses = &fuses_16420217248, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2100000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1050000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2400000},
                                                {.ceiling = 1155000, .floor =  770000, .freq = 2500000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 20
}; 

cpr_quotient_cfg quotients_2660012447 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  6, .quotient =  670 },
                                { .ro =  7, .quotient =  785 },
                                { .ro = 11, .quotient = 1332 },
                                { .ro = 12, .quotient =  854 } },
    .kvs = (uint32_t[]) { 207, 260, 287, 269 },
};


voltplan_fuse_data fuses_3481467573 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW0_LSB, CPR_DIG_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW22_LSB, REDUN_CPR_DIG_TARGET_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW19_LSB, CPR_DIG_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW24_LSB, REDUN_CPR_DIG_BASE_VOLT_NOM) } } },
    .cpuFreq = NULL
};


voltplan_fuse_data fuses_4535037833 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW0_LSB, CPR_DIG_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW22_LSB, REDUN_CPR_DIG_TARGET_VOLT_TURBO) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW19_LSB, CPR_DIG_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW24_LSB, REDUN_CPR_DIG_BASE_VOLT_TURBO) } } },
    .cpuFreq = NULL
};


uint32_t voltplan_get_mode_idx_4(voltplan_voltage_mode val)
{
    switch(val) {
        case VOLTPLAN_VOLTAGE_MODE_NOMINAL: return 0;
        case VOLTPLAN_VOLTAGE_MODE_TURBO: return 1;
        default:
            break;
    }

    //VOLTPLAN_ASSERT( false );
    return 0;
}


voltplan_voltage_plan voltage_plan_5792387507 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_4,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 930000, .freqDelta = 0, .fuses = &fuses_3481467573, .quotients = &quotients_2660012447, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL },

        // TURBO
        {.fref = 1050000, .freqDelta = 0, .fuses = &fuses_4535037833, .quotients = &quotients_10788676127, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  930000, .floor =  635000, .freq =       0},
                                                {.ceiling = 1050000, .floor =  710000, .freq =       0} },
    .allSubModesCount = 2
}; 

voltplan_voltage_plan voltage_plan_4506624176 =
{
    .modesCount = 1,
    .idxLookupFunc = voltplan_get_mode_idx_3,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 950000, .freqDelta = 0, .fuses = &fuses_4410950342, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 1000000, .freqDelta = 133000, .fuses = &fuses_3713117158, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  950000, .floor =  800000, .freq = 1200000},
                                                {.ceiling = 1000000, .floor =  800000, .freq = 1333000} },
    .allSubModesCount = 2
}; 

voltplan_voltage_plan voltage_plan_1509827796 =
{
    .modesCount = 1,
    .idxLookupFunc = voltplan_get_mode_idx_3,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 930000, .freqDelta = 0, .fuses = &fuses_15189633350, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  930000, .floor =  635000, .freq =  600000},
                                                {.ceiling =  930000, .floor =  635000, .freq =  700000},
                                                {.ceiling =  930000, .floor =  635000, .freq =  800000},
                                                {.ceiling =  930000, .floor =  635000, .freq =  900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1000000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 9
}; 

voltplan_fuse_data fuses_5741412930 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_LSB, CPR_VDN_TARGET_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_LSB, REDUN_CPR_VDN_TARGET_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW20_LSB, CPR_VDN_BASE_VOLT_SVS) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW25_LSB, REDUN_CPR_VDN_BASE_VOLT_SVS) } } },
    .cpuFreq = NULL
};


voltplan_fuse_data fuses_2966292714 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_LSB, CPR_VDN_TARGET_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_LSB, REDUN_CPR_VDN_TARGET_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW20_LSB, CPR_VDN_BASE_VOLT_NOM) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW25_LSB, REDUN_CPR_VDN_BASE_VOLT_NOM) } } },
    .cpuFreq = NULL
};


voltplan_fuse_data fuses_447629238 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_LSB, CPR_VDN_TARGET_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_LSB, REDUN_CPR_VDN_TARGET_VOLT_TURBO) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW20_LSB, CPR_VDN_BASE_VOLT_TURBO) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW25_LSB, REDUN_CPR_VDN_BASE_VOLT_TURBO) } } },
    .cpuFreq = NULL
};


voltplan_fuse_data fuses_3982896697 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW1_LSB, CPR_VDN_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW23_LSB, REDUN_CPR_VDN_TARGET_VOLT_TURBO_L2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW32_LSB, CPR_VDN_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW32_MSB, REDUN_CPR_VDN_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = NULL
};


voltplan_voltage_plan voltage_plan_5951229396 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 850000, .freqDelta = 0, .fuses = &fuses_5741412930, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 133000, .fuses = &fuses_2966292714, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // TURBO
        {.fref = 950000, .freqDelta = 134000, .fuses = &fuses_447629238, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1000000, .freqDelta = 133000, .fuses = &fuses_3982896697, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  850000, .floor =  800000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  800000, .freq = 1333000},
                                                {.ceiling =  950000, .floor =  800000, .freq = 1467000},
                                                {.ceiling = 1000000, .floor =  800000, .freq = 1600000} },
    .allSubModesCount = 4
}; 

voltplan_voltage_plan voltage_plan_6560610630 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_10891708083, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_17012423218, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_16991586018, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_17405239531, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

voltplan_voltage_plan voltage_plan_9473157461 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_7691872669, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_14925791572, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_18853928244, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_17536940537, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

voltplan_voltage_plan voltage_plan_8028151592 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_15241934968, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_19012208272, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_17773310968, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_12513430557, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

voltplan_voltage_plan voltage_plan_3743342607 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_10446139619, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_14954374583, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_voltage_plan voltage_plan_6693682228 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 950000, .freqDelta = 0, .fuses = &fuses_5741412930, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL },

        // NOMINAL
        {.fref = 1000000, .freqDelta = 133000, .fuses = &fuses_2966292714, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  950000, .floor =  800000, .freq = 1200000},
                                                {.ceiling = 1000000, .floor =  800000, .freq = 1333000} },
    .allSubModesCount = 2
}; 

voltplan_voltage_plan voltage_plan_10463564286 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_13310859207, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_13346258845, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_16108318381, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_15245481486, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

voltplan_voltage_plan voltage_plan_9706657993 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_11894824496, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_17621622567, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_18379326175, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_15545634456, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

uint32_t voltplan_get_mode_idx_5(voltplan_voltage_mode val)
{
    switch(val) {
        case VOLTPLAN_VOLTAGE_MODE_TURBO: return 0;
        default:
            break;
    }

    //VOLTPLAN_ASSERT( false );
    return 0;
}


voltplan_voltage_plan voltage_plan_4935658649 =
{
    .modesCount = 1,
    .idxLookupFunc = voltplan_get_mode_idx_5,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_TURBO },
    .minMode = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 930000, .freqDelta = 0, .fuses = &fuses_3481467573, .quotients = &quotients_2660012447, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL } },
    .modes = (struct voltplan_voltage_data[]) { 
        // TURBO
        {.fref = 1050000, .freqDelta = 0, .fuses = &fuses_4535037833, .quotients = &quotients_10788676127, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  930000, .floor =  635000, .freq =       0},
                                                {.ceiling = 1050000, .floor =  710000, .freq =       0} },
    .allSubModesCount = 2
}; 

voltplan_voltage_plan voltage_plan_6511742535 =
{
    .modesCount = 2,
    .idxLookupFunc = voltplan_get_mode_idx_0,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 790000, .freqDelta = 0, .fuses = &fuses_13310859207, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 930000, .freqDelta = 900000, .fuses = &fuses_13346258845, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 9,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  790000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  790000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  790000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  930000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 15
}; 

voltplan_voltage_plan voltage_plan_12403822687 =
{
    .modesCount = 4,
    .idxLookupFunc = voltplan_get_mode_idx_1,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_SVS,
                                             VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 690000, .freqDelta = 0, .fuses = &fuses_10165410332, .quotients = NULL, .margins = &margins_1020,
         .subModesCount = 6,
         .subModes = NULL },

        // NOMINAL
        {.fref = 900000, .freqDelta = 1000000, .fuses = &fuses_12378058365, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 10,
         .subModes = NULL },

        // TURBO
        {.fref = 1000000, .freqDelta = 300000, .fuses = &fuses_16583499693, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 3,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 300000, .fuses = &fuses_15131377378, .quotients = NULL, .margins = &margins_510,
         .subModesCount = 2,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  690000, .floor =  565000, .freq =  600000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  700000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  800000},
                                                {.ceiling =  690000, .floor =  565000, .freq =  900000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1000000},
                                                {.ceiling =  690000, .floor =  565000, .freq = 1100000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1200000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1300000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1400000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1500000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1600000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1700000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1800000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 1900000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2000000},
                                                {.ceiling =  900000, .floor =  635000, .freq = 2100000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2200000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2300000},
                                                {.ceiling = 1000000, .floor =  710000, .freq = 2400000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2500000},
                                                {.ceiling = 1055000, .floor =  770000, .freq = 2600000},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0},
                                                {.ceiling =       0, .floor =       0, .freq =       0} },
    .allSubModesCount = 21
}; 

cpr_quotient_cfg quotients_9142953006 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1057 },
                                { .ro =  3, .quotient = 1188 },
                                { .ro =  4, .quotient =  993 },
                                { .ro =  5, .quotient = 1096 },
                                { .ro =  6, .quotient =  669 },
                                { .ro =  7, .quotient =  776 } },
    .kvs = (uint32_t[]) { 221, 265, 213, 257, 207, 260 },
};


voltplan_fuse_data fuses_2498818192 =
{
    .volt       = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW0_LSB, CPR_DIG_TARGET_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_CPR_ROW22_LSB, REDUN_CPR_DIG_TARGET_VOLT_TURBO_L2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
    .avmVminTh = NULL,
    .cpuBaseVolt = (voltplan_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW32_LSB, CPR_DIG_BASE_VOLT_TURBO_L2) }, .redun_count = 1, .redun_data = (struct raw_fuse_data[]) { VOLTPLAN_FUSE_MAPPING(QFPROM_CORR_SPARE_REG27_ROW32_MSB, REDUN_CPR_DIG_BASE_VOLT_TURBO_L2) } } },
    .cpuFreq = NULL
};


voltplan_voltage_plan voltage_plan_6756626941 =
{
    .modesCount = 3,
    .idxLookupFunc = voltplan_get_mode_idx_2,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL,
                                             VOLTPLAN_VOLTAGE_MODE_TURBO,
                                             VOLTPLAN_VOLTAGE_MODE_SUPER_TURBO },
    .minMode = NULL,
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 830000, .freqDelta = 0, .fuses = &fuses_3481467573, .quotients = &quotients_9142953006, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL },

        // TURBO
        {.fref = 950000, .freqDelta = 0, .fuses = &fuses_4535037833, .quotients = &quotients_10007411787, .margins = &margins_510,
         .subModesCount = 1,
         .subModes = NULL },

        // SUPER_TURBO
        {.fref = 1055000, .freqDelta = 0, .fuses = &fuses_2498818192, .quotients = &quotients_8844675470, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  830000, .floor =  635000, .freq =       0},
                                                {.ceiling =  950000, .floor =  710000, .freq =       0},
                                                {.ceiling = 1055000, .floor =  770000, .freq =       0} },
    .allSubModesCount = 3
}; 

voltplan_voltage_plan voltage_plan_4087701680 =
{
    .modesCount = 1,
    .idxLookupFunc = voltplan_get_mode_idx_3,
    .supportedModes = (voltplan_voltage_mode[]) { VOLTPLAN_VOLTAGE_MODE_NOMINAL },
    .minMode = (struct voltplan_voltage_data[]) { 
        // SVS
        {.fref = 950000, .freqDelta = 0, .fuses = &fuses_5741412930, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .modes = (struct voltplan_voltage_data[]) { 
        // NOMINAL
        {.fref = 1000000, .freqDelta = 133000, .fuses = &fuses_2966292714, .quotients = NULL, .margins = NULL,
         .subModesCount = 1,
         .subModes = NULL } },
    .allSubModes = (struct voltplan_freq_data[]) { {.ceiling =  950000, .floor =  800000, .freq = 1200000},
                                                {.ceiling = 1000000, .floor =  800000, .freq = 1333000} },
    .allSubModesCount = 2
}; 

static voltplan_versioned_voltage_plan voltplan_rail_cx_vvp = {
    .rail    = VOLTPLAN_RAIL_CX,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_5792387507
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_4935658649
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6756626941
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_cbf_vvp = {
    .rail    = VOLTPLAN_RAIL_CBF,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6503273215
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_3716739967
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_1509827796
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_vdn_vvp = {
    .rail    = VOLTPLAN_RAIL_VDN,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_5951229396
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6693682228
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_4087701680
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_apr5_vvp = {
    .rail    = VOLTPLAN_RAIL_APR5,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_11368049843
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_10463564286
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6511742535
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_mx_vvp = {
    .rail    = VOLTPLAN_RAIL_MX,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6452235778
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_7152984173
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_3450773249
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_apr1_vvp = {
    .rail    = VOLTPLAN_RAIL_APR1,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_4835744991
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_10851571893
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_8028151592
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_apr0_vvp = {
    .rail    = VOLTPLAN_RAIL_APR0,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_3683076084
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_9296836644
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_9473157461
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_apr3_vvp = {
    .rail    = VOLTPLAN_RAIL_APR3,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_10856524247
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_8382445072
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_3743342607
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_apr2_vvp = {
    .rail    = VOLTPLAN_RAIL_APR2,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6760797210
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_11191877087
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_9706657993
        },
 },
    .count = 3
};


static voltplan_versioned_voltage_plan voltplan_rail_vds_vvp = {
    .rail    = VOLTPLAN_RAIL_VDS,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_10752356366
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_2767815732
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_4506624176
        },
 },
    .count = 3
};

static voltplan_versioned_voltage_plan voltplan_rail_apr4_vvp = {
    .rail    = VOLTPLAN_RAIL_APR4,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_8689991612
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6740294550
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_12403822687
        },
 },
    .count = 3
};

static voltplan_versioned_voltage_plan voltplan_rail_apr7_vvp = {
    .rail    = VOLTPLAN_RAIL_APR7,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_4992398281
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_10202482800
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_7365669226
        },
 },
    .count = 3
};

static voltplan_versioned_voltage_plan voltplan_rail_apr6_vvp = {
    .rail    = VOLTPLAN_RAIL_APR6,
    .list = (struct voltage_plan_list[]) { 
        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CHIPINFO_VERSION(1,0), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_4639643771
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CHIPINFO_VERSION(1,1), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_8405929341
        },

        {
            .version = { VOLTPLAN_FOUNDRY_ANY, VOLTPLAN_CHIPINFO_VERSION(2,0), VOLTPLAN_CHIPINFO_VERSION(2,255), VOLTPLAN_CPRREV(0) },
            .cfg  = &voltage_plan_6560610630
        },
 },
    .count = 3
};

voltplan_versioned_voltage_plan* voltplan_get_versioned_voltage_plan(voltplan_domain_id railId)
{
    switch(railId)
    {
        case VOLTPLAN_RAIL_CX: return &voltplan_rail_cx_vvp;
        case VOLTPLAN_RAIL_CBF: return &voltplan_rail_cbf_vvp;
        case VOLTPLAN_RAIL_VDN: return &voltplan_rail_vdn_vvp;
        case VOLTPLAN_RAIL_APR5: return &voltplan_rail_apr5_vvp;
        case VOLTPLAN_RAIL_MX: return &voltplan_rail_mx_vvp;
        case VOLTPLAN_RAIL_APR1: return &voltplan_rail_apr1_vvp;
        case VOLTPLAN_RAIL_APR0: return &voltplan_rail_apr0_vvp;
        case VOLTPLAN_RAIL_APR3: return &voltplan_rail_apr3_vvp;
        case VOLTPLAN_RAIL_APR2: return &voltplan_rail_apr2_vvp;
        case VOLTPLAN_RAIL_VDS: return &voltplan_rail_vds_vvp;
        case VOLTPLAN_RAIL_APR4: return &voltplan_rail_apr4_vvp;
        case VOLTPLAN_RAIL_APR7: return &voltplan_rail_apr7_vvp;
        case VOLTPLAN_RAIL_APR6: return &voltplan_rail_apr6_vvp;
        default:
            break;
    }
    return NULL;
}

voltplan_fuse tdp = {
    .count = 1,
    .data = (struct raw_fuse_data[]) {  { HWIO_QFPROM_CORR_CPR_ROW21_MSB_ADDR, HWIO_QFPROM_CORR_CPR_ROW21_MSB_CPR_LOCAL_RC_SHFT, HWIO_QFPROM_CORR_CPR_ROW21_MSB_CPR_LOCAL_RC_BMSK } },
};

voltplan_fuse iddq_vdda_510 = {
    .count = 1,
    .data = (struct raw_fuse_data[]) { { HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDA_DDR510_WS1_SHFT, HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDA_DDR510_WS1_BMSK }}};

voltplan_fuse iddq_vdda_423 = {
    .count = 1,
    .data  = (struct raw_fuse_data[]) { { HWIO_QFPROM_RAW_PTE_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW1_MSB_IDDQ_VDDA_DDR423_WS1_SHFT, HWIO_QFPROM_RAW_PTE_ROW1_MSB_IDDQ_VDDA_DDR423_WS1_BMSK}}
};

voltplan_fuse iddq_cx = {
    .count = 1,
    .data = (struct raw_fuse_data[]) { { HWIO_QFPROM_RAW_PTE_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW1_LSB_IDDQ_CX_WS1_SHFT, HWIO_QFPROM_RAW_PTE_ROW1_LSB_IDDQ_CX_WS1_BMSK } } 
};

voltplan_fuse iddq_vddq_510 = {
    .count = 1,
    .data = (struct raw_fuse_data[]) { { HWIO_QFPROM_RAW_PTE_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_MSB_IDDQ_VDDQ_DDR510_WS1_SHFT, HWIO_QFPROM_RAW_PTE_ROW2_MSB_IDDQ_VDDQ_DDR510_WS1_BMSK }}
};

voltplan_fuse iddq_vddq_423 = {
    .count = 1,
    .data = (struct raw_fuse_data[]) { { HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDQ_DDR423_WS1_SHFT, HWIO_QFPROM_RAW_PTE_ROW2_LSB_IDDQ_VDDQ_DDR423_WS1_BMSK }}};
