/** \file
 * \brief sets messageBlock variables
 * \addtogroup SrcFunc
 *  @{
 */
#include <string.h>
#include "dwc_ddrphy_phyinit.h"


/** @brief API to program the Message Block
 *
 *  This function can be used to program training firmware 1D/2D message block fields
 *  for a given PState.  as an example, to program MsgMsic to 0x4 for Pstate 3,
 *  for 1D Training :
 *  @code{.c}
 *  dwc_ddrphy_phyinit_setMB(3, "MsgMisc", 0x4, 0);
 *  @endcode
 *
 * refer to the messageBlock data structure for definition of feilds
 * applicable to each protocol.
 *
 * @param[in]   phyctx  PhyInit context
 * @param[in]   ps      integer between 0-3. Specifies the PState for which the
 * messageBlock field should be set.
 * @param[in]   field   A string representing the messageBlock field to be
 * programed.
 * @param[in]   value   filed value
 * @param[in]   Train2D determined if the field should be set on 2D or 1D
 * messageBlock.
 * @return 0 on success. On error  returns the following values based on
 * error:
 * - -1 : message block field specified by the input \c field string is not
 * found in the message block data structure.
 * - -2 : when DramType does not support 2D training but a 2D training field is
 * programmed.
 * - -3 : Train2D inputs is neither 1 or 0.
 */
int dwc_ddrphy_phyinit_setMb (phyinit_config_t* phyctx, int ps, char *field, int value) {

    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    int Train2D = pRuntimeConfig->Train2D;

    PMU_SMB_LPDDR5_1D_t*   mb_LPDDR5_1D = phyctx->mb_LPDDR5_1D;
    PMU_SMB_LPDDR5_1D_t* shdw_LPDDR5_1D = phyctx->shdw_LPDDR5_1D;
    PMU_SMB_LPDDR5_2D_t*   mb_LPDDR5_2D = phyctx->mb_LPDDR5_2D;
    PMU_SMB_LPDDR5_2D_t* shdw_LPDDR5_2D = phyctx->shdw_LPDDR5_2D;

    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_setMb]";

    if (Train2D == 0) {
      if ( strcmp(field, "Reserved00") == 0) {
        mb_LPDDR5_1D[ps].Reserved00 = value;
        shdw_LPDDR5_1D[ps].Reserved00 = 1;
      }
      else if ( strcmp(field, "MsgMisc") == 0) {
        mb_LPDDR5_1D[ps].MsgMisc = value;
        shdw_LPDDR5_1D[ps].MsgMisc = 1;
      }
      else if ( strcmp(field, "Pstate") == 0) {
        mb_LPDDR5_1D[ps].Pstate = value;
        shdw_LPDDR5_1D[ps].Pstate = 1;
      }
      else if ( strcmp(field, "PllBypassEn") == 0) {
        mb_LPDDR5_1D[ps].PllBypassEn = value;
        shdw_LPDDR5_1D[ps].PllBypassEn = 1;
      }
      else if ( strcmp(field, "DRAMFreq") == 0) {
        mb_LPDDR5_1D[ps].DRAMFreq = value;
        shdw_LPDDR5_1D[ps].DRAMFreq = 1;
      }
      else if ( strcmp(field, "DfiFreqRatio") == 0) {
        mb_LPDDR5_1D[ps].DfiFreqRatio = value;
        shdw_LPDDR5_1D[ps].DfiFreqRatio = 1;
      }
      else if ( strcmp(field, "BPZNResVal") == 0) {
        mb_LPDDR5_1D[ps].BPZNResVal = value;
        shdw_LPDDR5_1D[ps].BPZNResVal = 1;
      }
      else if ( strcmp(field, "PhyOdtImpedance") == 0) {
        mb_LPDDR5_1D[ps].PhyOdtImpedance = value;
        shdw_LPDDR5_1D[ps].PhyOdtImpedance = 1;
      }
      else if ( strcmp(field, "PhyDrvImpedance") == 0) {
        mb_LPDDR5_1D[ps].PhyDrvImpedance = value;
        shdw_LPDDR5_1D[ps].PhyDrvImpedance = 1;
      }
      else if ( strcmp(field, "PhyVref") == 0) {
        mb_LPDDR5_1D[ps].PhyVref = value;
        shdw_LPDDR5_1D[ps].PhyVref = 1;
      }
      else if ( strcmp(field, "Lp4Misc") == 0) {
        mb_LPDDR5_1D[ps].Lp4Misc = value;
        shdw_LPDDR5_1D[ps].Lp4Misc = 1;
      }
      else if ( strcmp(field, "Reserved0E") == 0) {
        mb_LPDDR5_1D[ps].Reserved0E = value;
        shdw_LPDDR5_1D[ps].Reserved0E = 1;
      }
      else if ( strcmp(field, "SequenceCtrl") == 0) {
        mb_LPDDR5_1D[ps].SequenceCtrl = value;
        shdw_LPDDR5_1D[ps].SequenceCtrl = 1;
      }
      else if ( strcmp(field, "HdtCtrl") == 0) {
        mb_LPDDR5_1D[ps].HdtCtrl = value;
        shdw_LPDDR5_1D[ps].HdtCtrl = 1;
      }
      else if ( strcmp(field, "Reserved13") == 0) {
        mb_LPDDR5_1D[ps].Reserved13 = value;
        shdw_LPDDR5_1D[ps].Reserved13 = 1;
      }
      else if ( strcmp(field, "Reserved14") == 0) {
        mb_LPDDR5_1D[ps].Reserved14 = value;
        shdw_LPDDR5_1D[ps].Reserved14 = 1;
      }
      else if ( strcmp(field, "Reserved15") == 0) {
        mb_LPDDR5_1D[ps].Reserved15 = value;
        shdw_LPDDR5_1D[ps].Reserved15 = 1;
      }
      else if ( strcmp(field, "DFIMRLMargin") == 0) {
        mb_LPDDR5_1D[ps].DFIMRLMargin = value;
        shdw_LPDDR5_1D[ps].DFIMRLMargin = 1;
      }
      else if ( strcmp(field, "Reserved17") == 0) {
        mb_LPDDR5_1D[ps].Reserved17 = value;
        shdw_LPDDR5_1D[ps].Reserved17 = 1;
      }
      else if ( strcmp(field, "Reserved18") == 0) {
        mb_LPDDR5_1D[ps].Reserved18 = value;
        shdw_LPDDR5_1D[ps].Reserved18 = 1;
      }
      else if ( strcmp(field, "Lp4Quickboot") == 0) {
        mb_LPDDR5_1D[ps].Lp4Quickboot = value;
        shdw_LPDDR5_1D[ps].Lp4Quickboot = 1;
      }
      else if ( strcmp(field, "Reserved1A") == 0) {
        mb_LPDDR5_1D[ps].Reserved1A = value;
        shdw_LPDDR5_1D[ps].Reserved1A = 1;
      }
      else if ( strcmp(field, "CATrainOpt") == 0) {
        mb_LPDDR5_1D[ps].CATrainOpt = value;
        shdw_LPDDR5_1D[ps].CATrainOpt = 1;
      }
      else if ( strcmp(field, "X8Mode") == 0) {
        mb_LPDDR5_1D[ps].X8Mode = value;
        shdw_LPDDR5_1D[ps].X8Mode = 1;
      }
      else if ( strcmp(field, "Reserved1F") == 0) {
        mb_LPDDR5_1D[ps].Reserved1F = value;
        shdw_LPDDR5_1D[ps].Reserved1F = 1;
      }
      else if ( strcmp(field, "PhyConfigOverride") == 0) {
        mb_LPDDR5_1D[ps].PhyConfigOverride = value;
        shdw_LPDDR5_1D[ps].PhyConfigOverride = 1;
      }
      else if ( strcmp(field, "EnabledDQsChA") == 0) {
        mb_LPDDR5_1D[ps].EnabledDQsChA = value;
        shdw_LPDDR5_1D[ps].EnabledDQsChA = 1;
      }
      else if ( strcmp(field, "CsPresentChA") == 0) {
        mb_LPDDR5_1D[ps].CsPresentChA = value;
        shdw_LPDDR5_1D[ps].CsPresentChA = 1;
      }
      else if ( strcmp(field, "CATerminatingRankChA") == 0) {
        mb_LPDDR5_1D[ps].CATerminatingRankChA = value;
        shdw_LPDDR5_1D[ps].CATerminatingRankChA = 1;
      }
      else if ( strcmp(field, "EnabledDQsChB") == 0) {
        mb_LPDDR5_1D[ps].EnabledDQsChB = value;
        shdw_LPDDR5_1D[ps].EnabledDQsChB = 1;
      }
      else if ( strcmp(field, "CsPresentChB") == 0) {
        mb_LPDDR5_1D[ps].CsPresentChB = value;
        shdw_LPDDR5_1D[ps].CsPresentChB = 1;
      }
      else if ( strcmp(field, "CATerminatingRankChB") == 0) {
        mb_LPDDR5_1D[ps].CATerminatingRankChB = value;
        shdw_LPDDR5_1D[ps].CATerminatingRankChB = 1;
      }
      else if ( strcmp(field, "MR1_A0") == 0) {
        mb_LPDDR5_1D[ps].MR1_A0 = value;
        shdw_LPDDR5_1D[ps].MR1_A0 = 1;
      }
      else if ( strcmp(field, "MR1_A1") == 0) {
        mb_LPDDR5_1D[ps].MR1_A1 = value;
        shdw_LPDDR5_1D[ps].MR1_A1 = 1;
      }
      else if ( strcmp(field, "MR1_B0") == 0) {
        mb_LPDDR5_1D[ps].MR1_B0 = value;
        shdw_LPDDR5_1D[ps].MR1_B0 = 1;
      }
      else if ( strcmp(field, "MR1_B1") == 0) {
        mb_LPDDR5_1D[ps].MR1_B1 = value;
        shdw_LPDDR5_1D[ps].MR1_B1 = 1;
      }
      else if ( strcmp(field, "MR2_A0") == 0) {
        mb_LPDDR5_1D[ps].MR2_A0 = value;
        shdw_LPDDR5_1D[ps].MR2_A0 = 1;
      }
      else if ( strcmp(field, "MR2_A1") == 0) {
        mb_LPDDR5_1D[ps].MR2_A1 = value;
        shdw_LPDDR5_1D[ps].MR2_A1 = 1;
      }
      else if ( strcmp(field, "MR2_B0") == 0) {
        mb_LPDDR5_1D[ps].MR2_B0 = value;
        shdw_LPDDR5_1D[ps].MR2_B0 = 1;
      }
      else if ( strcmp(field, "MR2_B1") == 0) {
        mb_LPDDR5_1D[ps].MR2_B1 = value;
        shdw_LPDDR5_1D[ps].MR2_B1 = 1;
      }
      else if ( strcmp(field, "MR3_A0") == 0) {
        mb_LPDDR5_1D[ps].MR3_A0 = value;
        shdw_LPDDR5_1D[ps].MR3_A0 = 1;
      }
      else if ( strcmp(field, "MR3_A1") == 0) {
        mb_LPDDR5_1D[ps].MR3_A1 = value;
        shdw_LPDDR5_1D[ps].MR3_A1 = 1;
      }
      else if ( strcmp(field, "MR3_B0") == 0) {
        mb_LPDDR5_1D[ps].MR3_B0 = value;
        shdw_LPDDR5_1D[ps].MR3_B0 = 1;
      }
      else if ( strcmp(field, "MR3_B1") == 0) {
        mb_LPDDR5_1D[ps].MR3_B1 = value;
        shdw_LPDDR5_1D[ps].MR3_B1 = 1;
      }
      else if ( strcmp(field, "MR10_A0") == 0) {
        mb_LPDDR5_1D[ps].MR10_A0 = value;
        shdw_LPDDR5_1D[ps].MR10_A0 = 1;
      }
      else if ( strcmp(field, "MR10_A1") == 0) {
        mb_LPDDR5_1D[ps].MR10_A1 = value;
        shdw_LPDDR5_1D[ps].MR10_A1 = 1;
      }
      else if ( strcmp(field, "MR10_B0") == 0) {
        mb_LPDDR5_1D[ps].MR10_B0 = value;
        shdw_LPDDR5_1D[ps].MR10_B0 = 1;
      }
      else if ( strcmp(field, "MR10_B1") == 0) {
        mb_LPDDR5_1D[ps].MR10_B1 = value;
        shdw_LPDDR5_1D[ps].MR10_B1 = 1;
      }
      else if ( strcmp(field, "MR11_A0") == 0) {
        mb_LPDDR5_1D[ps].MR11_A0 = value;
        shdw_LPDDR5_1D[ps].MR11_A0 = 1;
      }
      else if ( strcmp(field, "MR11_A1") == 0) {
        mb_LPDDR5_1D[ps].MR11_A1 = value;
        shdw_LPDDR5_1D[ps].MR11_A1 = 1;
      }
      else if ( strcmp(field, "MR11_B0") == 0) {
        mb_LPDDR5_1D[ps].MR11_B0 = value;
        shdw_LPDDR5_1D[ps].MR11_B0 = 1;
      }
      else if ( strcmp(field, "MR11_B1") == 0) {
        mb_LPDDR5_1D[ps].MR11_B1 = value;
        shdw_LPDDR5_1D[ps].MR11_B1 = 1;
      }
      else if ( strcmp(field, "MR12_A0") == 0) {
        mb_LPDDR5_1D[ps].MR12_A0 = value;
        shdw_LPDDR5_1D[ps].MR12_A0 = 1;
      }
      else if ( strcmp(field, "MR12_A1") == 0) {
        mb_LPDDR5_1D[ps].MR12_A1 = value;
        shdw_LPDDR5_1D[ps].MR12_A1 = 1;
      }
      else if ( strcmp(field, "MR12_B0") == 0) {
        mb_LPDDR5_1D[ps].MR12_B0 = value;
        shdw_LPDDR5_1D[ps].MR12_B0 = 1;
      }
      else if ( strcmp(field, "MR12_B1") == 0) {
        mb_LPDDR5_1D[ps].MR12_B1 = value;
        shdw_LPDDR5_1D[ps].MR12_B1 = 1;
      }
      else if ( strcmp(field, "MR13_A0") == 0) {
        mb_LPDDR5_1D[ps].MR13_A0 = value;
        shdw_LPDDR5_1D[ps].MR13_A0 = 1;
      }
      else if ( strcmp(field, "MR13_A1") == 0) {
        mb_LPDDR5_1D[ps].MR13_A1 = value;
        shdw_LPDDR5_1D[ps].MR13_A1 = 1;
      }
      else if ( strcmp(field, "MR13_B0") == 0) {
        mb_LPDDR5_1D[ps].MR13_B0 = value;
        shdw_LPDDR5_1D[ps].MR13_B0 = 1;
      }
      else if ( strcmp(field, "MR13_B1") == 0) {
        mb_LPDDR5_1D[ps].MR13_B1 = value;
        shdw_LPDDR5_1D[ps].MR13_B1 = 1;
      }
      else if ( strcmp(field, "MR14_A0") == 0) {
        mb_LPDDR5_1D[ps].MR14_A0 = value;
        shdw_LPDDR5_1D[ps].MR14_A0 = 1;
      }
      else if ( strcmp(field, "MR14_A1") == 0) {
        mb_LPDDR5_1D[ps].MR14_A1 = value;
        shdw_LPDDR5_1D[ps].MR14_A1 = 1;
      }
      else if ( strcmp(field, "MR14_B0") == 0) {
        mb_LPDDR5_1D[ps].MR14_B0 = value;
        shdw_LPDDR5_1D[ps].MR14_B0 = 1;
      }
      else if ( strcmp(field, "MR14_B1") == 0) {
        mb_LPDDR5_1D[ps].MR14_B1 = value;
        shdw_LPDDR5_1D[ps].MR14_B1 = 1;
      }
      else if ( strcmp(field, "MR15_A0") == 0) {
        mb_LPDDR5_1D[ps].MR15_A0 = value;
        shdw_LPDDR5_1D[ps].MR15_A0 = 1;
      }
      else if ( strcmp(field, "MR15_A1") == 0) {
        mb_LPDDR5_1D[ps].MR15_A1 = value;
        shdw_LPDDR5_1D[ps].MR15_A1 = 1;
      }
      else if ( strcmp(field, "MR15_B0") == 0) {
        mb_LPDDR5_1D[ps].MR15_B0 = value;
        shdw_LPDDR5_1D[ps].MR15_B0 = 1;
      }
      else if ( strcmp(field, "MR15_B1") == 0) {
        mb_LPDDR5_1D[ps].MR15_B1 = value;
        shdw_LPDDR5_1D[ps].MR15_B1 = 1;
      }
      else if ( strcmp(field, "MR16_A0") == 0) {
        mb_LPDDR5_1D[ps].MR16_A0 = value;
        shdw_LPDDR5_1D[ps].MR16_A0 = 1;
      }
      else if ( strcmp(field, "MR16_A1") == 0) {
        mb_LPDDR5_1D[ps].MR16_A1 = value;
        shdw_LPDDR5_1D[ps].MR16_A1 = 1;
      }
      else if ( strcmp(field, "MR16_B0") == 0) {
        mb_LPDDR5_1D[ps].MR16_B0 = value;
        shdw_LPDDR5_1D[ps].MR16_B0 = 1;
      }
      else if ( strcmp(field, "MR16_B1") == 0) {
        mb_LPDDR5_1D[ps].MR16_B1 = value;
        shdw_LPDDR5_1D[ps].MR16_B1 = 1;
      }
      else if ( strcmp(field, "MR17_A0") == 0) {
        mb_LPDDR5_1D[ps].MR17_A0 = value;
        shdw_LPDDR5_1D[ps].MR17_A0 = 1;
      }
      else if ( strcmp(field, "MR17_A1") == 0) {
        mb_LPDDR5_1D[ps].MR17_A1 = value;
        shdw_LPDDR5_1D[ps].MR17_A1 = 1;
      }
      else if ( strcmp(field, "MR17_B0") == 0) {
        mb_LPDDR5_1D[ps].MR17_B0 = value;
        shdw_LPDDR5_1D[ps].MR17_B0 = 1;
      }
      else if ( strcmp(field, "MR17_B1") == 0) {
        mb_LPDDR5_1D[ps].MR17_B1 = value;
        shdw_LPDDR5_1D[ps].MR17_B1 = 1;
      }
      else if ( strcmp(field, "MR18_A0") == 0) {
        mb_LPDDR5_1D[ps].MR18_A0 = value;
        shdw_LPDDR5_1D[ps].MR18_A0 = 1;
      }
      else if ( strcmp(field, "MR18_A1") == 0) {
        mb_LPDDR5_1D[ps].MR18_A1 = value;
        shdw_LPDDR5_1D[ps].MR18_A1 = 1;
      }
      else if ( strcmp(field, "MR18_B0") == 0) {
        mb_LPDDR5_1D[ps].MR18_B0 = value;
        shdw_LPDDR5_1D[ps].MR18_B0 = 1;
      }
      else if ( strcmp(field, "MR18_B1") == 0) {
        mb_LPDDR5_1D[ps].MR18_B1 = value;
        shdw_LPDDR5_1D[ps].MR18_B1 = 1;
      }
      else if ( strcmp(field, "MR19_A0") == 0) {
        mb_LPDDR5_1D[ps].MR19_A0 = value;
        shdw_LPDDR5_1D[ps].MR19_A0 = 1;
      }
      else if ( strcmp(field, "MR19_A1") == 0) {
        mb_LPDDR5_1D[ps].MR19_A1 = value;
        shdw_LPDDR5_1D[ps].MR19_A1 = 1;
      }
      else if ( strcmp(field, "MR19_B0") == 0) {
        mb_LPDDR5_1D[ps].MR19_B0 = value;
        shdw_LPDDR5_1D[ps].MR19_B0 = 1;
      }
      else if ( strcmp(field, "MR19_B1") == 0) {
        mb_LPDDR5_1D[ps].MR19_B1 = value;
        shdw_LPDDR5_1D[ps].MR19_B1 = 1;
      }
      else if ( strcmp(field, "MR20_A0") == 0) {
        mb_LPDDR5_1D[ps].MR20_A0 = value;
        shdw_LPDDR5_1D[ps].MR20_A0 = 1;
      }
      else if ( strcmp(field, "MR20_A1") == 0) {
        mb_LPDDR5_1D[ps].MR20_A1 = value;
        shdw_LPDDR5_1D[ps].MR20_A1 = 1;
      }
      else if ( strcmp(field, "MR20_B0") == 0) {
        mb_LPDDR5_1D[ps].MR20_B0 = value;
        shdw_LPDDR5_1D[ps].MR20_B0 = 1;
      }
      else if ( strcmp(field, "MR20_B1") == 0) {
        mb_LPDDR5_1D[ps].MR20_B1 = value;
        shdw_LPDDR5_1D[ps].MR20_B1 = 1;
      }
      else if ( strcmp(field, "MR21_A0") == 0) {
        mb_LPDDR5_1D[ps].MR21_A0 = value;
        shdw_LPDDR5_1D[ps].MR21_A0 = 1;
      }
      else if ( strcmp(field, "MR21_A1") == 0) {
        mb_LPDDR5_1D[ps].MR21_A1 = value;
        shdw_LPDDR5_1D[ps].MR21_A1 = 1;
      }
      else if ( strcmp(field, "MR21_B0") == 0) {
        mb_LPDDR5_1D[ps].MR21_B0 = value;
        shdw_LPDDR5_1D[ps].MR21_B0 = 1;
      }
      else if ( strcmp(field, "MR21_B1") == 0) {
        mb_LPDDR5_1D[ps].MR21_B1 = value;
        shdw_LPDDR5_1D[ps].MR21_B1 = 1;
      }
      else if ( strcmp(field, "MR22_A0") == 0) {
        mb_LPDDR5_1D[ps].MR22_A0 = value;
        shdw_LPDDR5_1D[ps].MR22_A0 = 1;
      }
      else if ( strcmp(field, "MR22_A1") == 0) {
        mb_LPDDR5_1D[ps].MR22_A1 = value;
        shdw_LPDDR5_1D[ps].MR22_A1 = 1;
      }
      else if ( strcmp(field, "MR22_B0") == 0) {
        mb_LPDDR5_1D[ps].MR22_B0 = value;
        shdw_LPDDR5_1D[ps].MR22_B0 = 1;
      }
      else if ( strcmp(field, "MR22_B1") == 0) {
        mb_LPDDR5_1D[ps].MR22_B1 = value;
        shdw_LPDDR5_1D[ps].MR22_B1 = 1;
      }
      else if ( strcmp(field, "MR24_A0") == 0) {
        mb_LPDDR5_1D[ps].MR24_A0 = value;
        shdw_LPDDR5_1D[ps].MR24_A0 = 1;
      }
      else if ( strcmp(field, "MR24_A1") == 0) {
        mb_LPDDR5_1D[ps].MR24_A1 = value;
        shdw_LPDDR5_1D[ps].MR24_A1 = 1;
      }
      else if ( strcmp(field, "MR24_B0") == 0) {
        mb_LPDDR5_1D[ps].MR24_B0 = value;
        shdw_LPDDR5_1D[ps].MR24_B0 = 1;
      }
      else if ( strcmp(field, "MR24_B1") == 0) {
        mb_LPDDR5_1D[ps].MR24_B1 = value;
        shdw_LPDDR5_1D[ps].MR24_B1 = 1;
      }
      else if ( strcmp(field, "MR25_A0") == 0) {
        mb_LPDDR5_1D[ps].MR25_A0 = value;
        shdw_LPDDR5_1D[ps].MR25_A0 = 1;
      }
      else if ( strcmp(field, "MR25_A1") == 0) {
        mb_LPDDR5_1D[ps].MR25_A1 = value;
        shdw_LPDDR5_1D[ps].MR25_A1 = 1;
      }
      else if ( strcmp(field, "MR25_B0") == 0) {
        mb_LPDDR5_1D[ps].MR25_B0 = value;
        shdw_LPDDR5_1D[ps].MR25_B0 = 1;
      }
      else if ( strcmp(field, "MR25_B1") == 0) {
        mb_LPDDR5_1D[ps].MR25_B1 = value;
        shdw_LPDDR5_1D[ps].MR25_B1 = 1;
      }
      else if ( strcmp(field, "MR26_A0") == 0) {
        mb_LPDDR5_1D[ps].MR26_A0 = value;
        shdw_LPDDR5_1D[ps].MR26_A0 = 1;
      }
      else if ( strcmp(field, "MR26_A1") == 0) {
        mb_LPDDR5_1D[ps].MR26_A1 = value;
        shdw_LPDDR5_1D[ps].MR26_A1 = 1;
      }
      else if ( strcmp(field, "MR26_B0") == 0) {
        mb_LPDDR5_1D[ps].MR26_B0 = value;
        shdw_LPDDR5_1D[ps].MR26_B0 = 1;
      }
      else if ( strcmp(field, "MR26_B1") == 0) {
        mb_LPDDR5_1D[ps].MR26_B1 = value;
        shdw_LPDDR5_1D[ps].MR26_B1 = 1;
      }
      else if ( strcmp(field, "MR27_A0") == 0) {
        mb_LPDDR5_1D[ps].MR27_A0 = value;
        shdw_LPDDR5_1D[ps].MR27_A0 = 1;
      }
      else if ( strcmp(field, "MR27_A1") == 0) {
        mb_LPDDR5_1D[ps].MR27_A1 = value;
        shdw_LPDDR5_1D[ps].MR27_A1 = 1;
      }
      else if ( strcmp(field, "MR27_B0") == 0) {
        mb_LPDDR5_1D[ps].MR27_B0 = value;
        shdw_LPDDR5_1D[ps].MR27_B0 = 1;
      }
      else if ( strcmp(field, "MR27_B1") == 0) {
        mb_LPDDR5_1D[ps].MR27_B1 = value;
        shdw_LPDDR5_1D[ps].MR27_B1 = 1;
      }
      else if ( strcmp(field, "MR28_A0") == 0) {
        mb_LPDDR5_1D[ps].MR28_A0 = value;
        shdw_LPDDR5_1D[ps].MR28_A0 = 1;
      }
      else if ( strcmp(field, "MR28_A1") == 0) {
        mb_LPDDR5_1D[ps].MR28_A1 = value;
        shdw_LPDDR5_1D[ps].MR28_A1 = 1;
      }
      else if ( strcmp(field, "MR28_B0") == 0) {
        mb_LPDDR5_1D[ps].MR28_B0 = value;
        shdw_LPDDR5_1D[ps].MR28_B0 = 1;
      }
      else if ( strcmp(field, "MR28_B1") == 0) {
        mb_LPDDR5_1D[ps].MR28_B1 = value;
        shdw_LPDDR5_1D[ps].MR28_B1 = 1;
      }
      else if ( strcmp(field, "MR30_A0") == 0) {
        mb_LPDDR5_1D[ps].MR30_A0 = value;
        shdw_LPDDR5_1D[ps].MR30_A0 = 1;
      }
      else if ( strcmp(field, "MR30_A1") == 0) {
        mb_LPDDR5_1D[ps].MR30_A1 = value;
        shdw_LPDDR5_1D[ps].MR30_A1 = 1;
      }
      else if ( strcmp(field, "MR30_B0") == 0) {
        mb_LPDDR5_1D[ps].MR30_B0 = value;
        shdw_LPDDR5_1D[ps].MR30_B0 = 1;
      }
      else if ( strcmp(field, "MR30_B1") == 0) {
        mb_LPDDR5_1D[ps].MR30_B1 = value;
        shdw_LPDDR5_1D[ps].MR30_B1 = 1;
      }
      else if ( strcmp(field, "MR31_A0") == 0) {
        mb_LPDDR5_1D[ps].MR31_A0 = value;
        shdw_LPDDR5_1D[ps].MR31_A0 = 1;
      }
      else if ( strcmp(field, "MR31_A1") == 0) {
        mb_LPDDR5_1D[ps].MR31_A1 = value;
        shdw_LPDDR5_1D[ps].MR31_A1 = 1;
      }
      else if ( strcmp(field, "MR31_B0") == 0) {
        mb_LPDDR5_1D[ps].MR31_B0 = value;
        shdw_LPDDR5_1D[ps].MR31_B0 = 1;
      }
      else if ( strcmp(field, "MR31_B1") == 0) {
        mb_LPDDR5_1D[ps].MR31_B1 = value;
        shdw_LPDDR5_1D[ps].MR31_B1 = 1;
      }
      else if ( strcmp(field, "MR32_A0") == 0) {
        mb_LPDDR5_1D[ps].MR32_A0 = value;
        shdw_LPDDR5_1D[ps].MR32_A0 = 1;
      }
      else if ( strcmp(field, "MR32_A1") == 0) {
        mb_LPDDR5_1D[ps].MR32_A1 = value;
        shdw_LPDDR5_1D[ps].MR32_A1 = 1;
      }
      else if ( strcmp(field, "MR32_B0") == 0) {
        mb_LPDDR5_1D[ps].MR32_B0 = value;
        shdw_LPDDR5_1D[ps].MR32_B0 = 1;
      }
      else if ( strcmp(field, "MR32_B1") == 0) {
        mb_LPDDR5_1D[ps].MR32_B1 = value;
        shdw_LPDDR5_1D[ps].MR32_B1 = 1;
      }
      else if ( strcmp(field, "MR33_A0") == 0) {
        mb_LPDDR5_1D[ps].MR33_A0 = value;
        shdw_LPDDR5_1D[ps].MR33_A0 = 1;
      }
      else if ( strcmp(field, "MR33_A1") == 0) {
        mb_LPDDR5_1D[ps].MR33_A1 = value;
        shdw_LPDDR5_1D[ps].MR33_A1 = 1;
      }
      else if ( strcmp(field, "MR33_B0") == 0) {
        mb_LPDDR5_1D[ps].MR33_B0 = value;
        shdw_LPDDR5_1D[ps].MR33_B0 = 1;
      }
      else if ( strcmp(field, "MR33_B1") == 0) {
        mb_LPDDR5_1D[ps].MR33_B1 = value;
        shdw_LPDDR5_1D[ps].MR33_B1 = 1;
      }
      else if ( strcmp(field, "MR34_A0") == 0) {
        mb_LPDDR5_1D[ps].MR34_A0 = value;
        shdw_LPDDR5_1D[ps].MR34_A0 = 1;
      }
      else if ( strcmp(field, "MR34_A1") == 0) {
        mb_LPDDR5_1D[ps].MR34_A1 = value;
        shdw_LPDDR5_1D[ps].MR34_A1 = 1;
      }
      else if ( strcmp(field, "MR34_B0") == 0) {
        mb_LPDDR5_1D[ps].MR34_B0 = value;
        shdw_LPDDR5_1D[ps].MR34_B0 = 1;
      }
      else if ( strcmp(field, "MR34_B1") == 0) {
        mb_LPDDR5_1D[ps].MR34_B1 = value;
        shdw_LPDDR5_1D[ps].MR34_B1 = 1;
      }
      else if ( strcmp(field, "MR37_A0") == 0) {
        mb_LPDDR5_1D[ps].MR37_A0 = value;
        shdw_LPDDR5_1D[ps].MR37_A0 = 1;
      }
      else if ( strcmp(field, "MR37_A1") == 0) {
        mb_LPDDR5_1D[ps].MR37_A1 = value;
        shdw_LPDDR5_1D[ps].MR37_A1 = 1;
      }
      else if ( strcmp(field, "MR37_B0") == 0) {
        mb_LPDDR5_1D[ps].MR37_B0 = value;
        shdw_LPDDR5_1D[ps].MR37_B0 = 1;
      }
      else if ( strcmp(field, "MR37_B1") == 0) {
        mb_LPDDR5_1D[ps].MR37_B1 = value;
        shdw_LPDDR5_1D[ps].MR37_B1 = 1;
      }
      else if ( strcmp(field, "MR40_A0") == 0) {
        mb_LPDDR5_1D[ps].MR40_A0 = value;
        shdw_LPDDR5_1D[ps].MR40_A0 = 1;
      }
      else if ( strcmp(field, "MR40_A1") == 0) {
        mb_LPDDR5_1D[ps].MR40_A1 = value;
        shdw_LPDDR5_1D[ps].MR40_A1 = 1;
      }
      else if ( strcmp(field, "MR40_B0") == 0) {
        mb_LPDDR5_1D[ps].MR40_B0 = value;
        shdw_LPDDR5_1D[ps].MR40_B0 = 1;
      }
      else if ( strcmp(field, "MR40_B1") == 0) {
        mb_LPDDR5_1D[ps].MR40_B1 = value;
        shdw_LPDDR5_1D[ps].MR40_B1 = 1;
      }
      else if ( strcmp(field, "MR41_A0") == 0) {
        mb_LPDDR5_1D[ps].MR41_A0 = value;
        shdw_LPDDR5_1D[ps].MR41_A0 = 1;
      }
      else if ( strcmp(field, "MR41_A1") == 0) {
        mb_LPDDR5_1D[ps].MR41_A1 = value;
        shdw_LPDDR5_1D[ps].MR41_A1 = 1;
      }
      else if ( strcmp(field, "MR41_B0") == 0) {
        mb_LPDDR5_1D[ps].MR41_B0 = value;
        shdw_LPDDR5_1D[ps].MR41_B0 = 1;
      }
      else if ( strcmp(field, "MR41_B1") == 0) {
        mb_LPDDR5_1D[ps].MR41_B1 = value;
        shdw_LPDDR5_1D[ps].MR41_B1 = 1;
      }
      else if ( strcmp(field, "Disable2D") == 0) {
        mb_LPDDR5_1D[ps].Disable2D = value;
        shdw_LPDDR5_1D[ps].Disable2D = 1;
      }
      else if ( strcmp(field, "VrefSamples") == 0) {
        mb_LPDDR5_1D[ps].VrefSamples = value;
        shdw_LPDDR5_1D[ps].VrefSamples = 1;
      }
      else if ( strcmp(field, "RdWrPatternA") == 0) {
        mb_LPDDR5_1D[ps].RdWrPatternA = value;
        shdw_LPDDR5_1D[ps].RdWrPatternA = 1;
      }
      else if ( strcmp(field, "RdWrPatternB") == 0) {
        mb_LPDDR5_1D[ps].RdWrPatternB = value;
        shdw_LPDDR5_1D[ps].RdWrPatternB = 1;
      }
      else if ( strcmp(field, "RdWrInvertA") == 0) {
        mb_LPDDR5_1D[ps].RdWrInvertA = value;
        shdw_LPDDR5_1D[ps].RdWrInvertA = 1;
      }
      else if ( strcmp(field, "RdWrInvertB") == 0) {
        mb_LPDDR5_1D[ps].RdWrInvertB = value;
        shdw_LPDDR5_1D[ps].RdWrInvertB = 1;
      }
      else {
          dwc_ddrphy_phyinit_assert(0,"%s unknown message block field name '%s', Train2D=%d\n", printf_header, field,Train2D);
          return -1;
      }
    }
    else if (Train2D == 1) {
      if ( strcmp(field, "Reserved00") == 0) {
        mb_LPDDR5_2D[ps].Reserved00 = value;
        shdw_LPDDR5_2D[ps].Reserved00 = 1;
      }
      else if ( strcmp(field, "MsgMisc") == 0) {
        mb_LPDDR5_2D[ps].MsgMisc = value;
        shdw_LPDDR5_2D[ps].MsgMisc = 1;
      }
      else if ( strcmp(field, "Pstate") == 0) {
        mb_LPDDR5_2D[ps].Pstate = value;
        shdw_LPDDR5_2D[ps].Pstate = 1;
      }
      else if ( strcmp(field, "PllBypassEn") == 0) {
        mb_LPDDR5_2D[ps].PllBypassEn = value;
        shdw_LPDDR5_2D[ps].PllBypassEn = 1;
      }
      else if ( strcmp(field, "DRAMFreq") == 0) {
        mb_LPDDR5_2D[ps].DRAMFreq = value;
        shdw_LPDDR5_2D[ps].DRAMFreq = 1;
      }
      else if ( strcmp(field, "DfiFreqRatio") == 0) {
        mb_LPDDR5_2D[ps].DfiFreqRatio = value;
        shdw_LPDDR5_2D[ps].DfiFreqRatio = 1;
      }
      else if ( strcmp(field, "BPZNResVal") == 0) {
        mb_LPDDR5_2D[ps].BPZNResVal = value;
        shdw_LPDDR5_2D[ps].BPZNResVal = 1;
      }
      else if ( strcmp(field, "PhyOdtImpedance") == 0) {
        mb_LPDDR5_2D[ps].PhyOdtImpedance = value;
        shdw_LPDDR5_2D[ps].PhyOdtImpedance = 1;
      }
      else if ( strcmp(field, "PhyDrvImpedance") == 0) {
        mb_LPDDR5_2D[ps].PhyDrvImpedance = value;
        shdw_LPDDR5_2D[ps].PhyDrvImpedance = 1;
      }
      else if ( strcmp(field, "PhyVref") == 0) {
        mb_LPDDR5_2D[ps].PhyVref = value;
        shdw_LPDDR5_2D[ps].PhyVref = 1;
      }
      else if ( strcmp(field, "Lp4Misc") == 0) {
        mb_LPDDR5_2D[ps].Lp4Misc = value;
        shdw_LPDDR5_2D[ps].Lp4Misc = 1;
      }
      else if ( strcmp(field, "Reserved0E") == 0) {
        mb_LPDDR5_2D[ps].Reserved0E = value;
        shdw_LPDDR5_2D[ps].Reserved0E = 1;
      }
      else if ( strcmp(field, "SequenceCtrl") == 0) {
        mb_LPDDR5_2D[ps].SequenceCtrl = value;
        shdw_LPDDR5_2D[ps].SequenceCtrl = 1;
      }
      else if ( strcmp(field, "HdtCtrl") == 0) {
        mb_LPDDR5_2D[ps].HdtCtrl = value;
        shdw_LPDDR5_2D[ps].HdtCtrl = 1;
      }
      else if ( strcmp(field, "Reserved13") == 0) {
        mb_LPDDR5_2D[ps].Reserved13 = value;
        shdw_LPDDR5_2D[ps].Reserved13 = 1;
      }
      else if ( strcmp(field, "Reserved14") == 0) {
        mb_LPDDR5_2D[ps].Reserved14 = value;
        shdw_LPDDR5_2D[ps].Reserved14 = 1;
      }
      else if ( strcmp(field, "Reserved15") == 0) {
        mb_LPDDR5_2D[ps].Reserved15 = value;
        shdw_LPDDR5_2D[ps].Reserved15 = 1;
      }
      else if ( strcmp(field, "DFIMRLMargin") == 0) {
        mb_LPDDR5_2D[ps].DFIMRLMargin = value;
        shdw_LPDDR5_2D[ps].DFIMRLMargin = 1;
      }
      else if ( strcmp(field, "Reserved17") == 0) {
        mb_LPDDR5_2D[ps].Reserved17 = value;
        shdw_LPDDR5_2D[ps].Reserved17 = 1;
      }
      else if ( strcmp(field, "Reserved18") == 0) {
        mb_LPDDR5_2D[ps].Reserved18 = value;
        shdw_LPDDR5_2D[ps].Reserved18 = 1;
      }
      else if ( strcmp(field, "Reserved1A") == 0) {
        mb_LPDDR5_2D[ps].Reserved1A = value;
        shdw_LPDDR5_2D[ps].Reserved1A = 1;
      }
      else if ( strcmp(field, "CATrainOpt") == 0) {
        mb_LPDDR5_2D[ps].CATrainOpt = value;
        shdw_LPDDR5_2D[ps].CATrainOpt = 1;
      }
      else if ( strcmp(field, "X8Mode") == 0) {
        mb_LPDDR5_2D[ps].X8Mode = value;
        shdw_LPDDR5_2D[ps].X8Mode = 1;
      }
      else if ( strcmp(field, "RX2D_TrainOpt") == 0) {
        mb_LPDDR5_2D[ps].RX2D_TrainOpt = value;
        shdw_LPDDR5_2D[ps].RX2D_TrainOpt = 1;
      }
      else if ( strcmp(field, "TX2D_TrainOpt") == 0) {
        mb_LPDDR5_2D[ps].TX2D_TrainOpt = value;
        shdw_LPDDR5_2D[ps].TX2D_TrainOpt = 1;
      }
      else if ( strcmp(field, "Reserved1F") == 0) {
        mb_LPDDR5_2D[ps].Reserved1F = value;
        shdw_LPDDR5_2D[ps].Reserved1F = 1;
      }
      else if ( strcmp(field, "Delay_Weight2D") == 0) {
        mb_LPDDR5_2D[ps].Delay_Weight2D = value;
        shdw_LPDDR5_2D[ps].Delay_Weight2D = 1;
      }
      else if ( strcmp(field, "Voltage_Weight2D") == 0) {
        mb_LPDDR5_2D[ps].Voltage_Weight2D = value;
        shdw_LPDDR5_2D[ps].Voltage_Weight2D = 1;
      }
      else if ( strcmp(field, "PhyConfigOverride") == 0) {
        mb_LPDDR5_2D[ps].PhyConfigOverride = value;
        shdw_LPDDR5_2D[ps].PhyConfigOverride = 1;
      }
      else if ( strcmp(field, "EnabledDQsChA") == 0) {
        mb_LPDDR5_2D[ps].EnabledDQsChA = value;
        shdw_LPDDR5_2D[ps].EnabledDQsChA = 1;
      }
      else if ( strcmp(field, "CsPresentChA") == 0) {
        mb_LPDDR5_2D[ps].CsPresentChA = value;
        shdw_LPDDR5_2D[ps].CsPresentChA = 1;
      }
      else if ( strcmp(field, "CATerminatingRankChA") == 0) {
        mb_LPDDR5_2D[ps].CATerminatingRankChA = value;
        shdw_LPDDR5_2D[ps].CATerminatingRankChA = 1;
      }
      else if ( strcmp(field, "EnabledDQsChB") == 0) {
        mb_LPDDR5_2D[ps].EnabledDQsChB = value;
        shdw_LPDDR5_2D[ps].EnabledDQsChB = 1;
      }
      else if ( strcmp(field, "CsPresentChB") == 0) {
        mb_LPDDR5_2D[ps].CsPresentChB = value;
        shdw_LPDDR5_2D[ps].CsPresentChB = 1;
      }
      else if ( strcmp(field, "CATerminatingRankChB") == 0) {
        mb_LPDDR5_2D[ps].CATerminatingRankChB = value;
        shdw_LPDDR5_2D[ps].CATerminatingRankChB = 1;
      }
      else if ( strcmp(field, "MR1_A0") == 0) {
        mb_LPDDR5_2D[ps].MR1_A0 = value;
        shdw_LPDDR5_2D[ps].MR1_A0 = 1;
      }
      else if ( strcmp(field, "MR1_A1") == 0) {
        mb_LPDDR5_2D[ps].MR1_A1 = value;
        shdw_LPDDR5_2D[ps].MR1_A1 = 1;
      }
      else if ( strcmp(field, "MR1_B0") == 0) {
        mb_LPDDR5_2D[ps].MR1_B0 = value;
        shdw_LPDDR5_2D[ps].MR1_B0 = 1;
      }
      else if ( strcmp(field, "MR1_B1") == 0) {
        mb_LPDDR5_2D[ps].MR1_B1 = value;
        shdw_LPDDR5_2D[ps].MR1_B1 = 1;
      }
      else if ( strcmp(field, "MR2_A0") == 0) {
        mb_LPDDR5_2D[ps].MR2_A0 = value;
        shdw_LPDDR5_2D[ps].MR2_A0 = 1;
      }
      else if ( strcmp(field, "MR2_A1") == 0) {
        mb_LPDDR5_2D[ps].MR2_A1 = value;
        shdw_LPDDR5_2D[ps].MR2_A1 = 1;
      }
      else if ( strcmp(field, "MR2_B0") == 0) {
        mb_LPDDR5_2D[ps].MR2_B0 = value;
        shdw_LPDDR5_2D[ps].MR2_B0 = 1;
      }
      else if ( strcmp(field, "MR2_B1") == 0) {
        mb_LPDDR5_2D[ps].MR2_B1 = value;
        shdw_LPDDR5_2D[ps].MR2_B1 = 1;
      }
      else if ( strcmp(field, "MR3_A0") == 0) {
        mb_LPDDR5_2D[ps].MR3_A0 = value;
        shdw_LPDDR5_2D[ps].MR3_A0 = 1;
      }
      else if ( strcmp(field, "MR3_A1") == 0) {
        mb_LPDDR5_2D[ps].MR3_A1 = value;
        shdw_LPDDR5_2D[ps].MR3_A1 = 1;
      }
      else if ( strcmp(field, "MR3_B0") == 0) {
        mb_LPDDR5_2D[ps].MR3_B0 = value;
        shdw_LPDDR5_2D[ps].MR3_B0 = 1;
      }
      else if ( strcmp(field, "MR3_B1") == 0) {
        mb_LPDDR5_2D[ps].MR3_B1 = value;
        shdw_LPDDR5_2D[ps].MR3_B1 = 1;
      }
      else if ( strcmp(field, "MR10_A0") == 0) {
        mb_LPDDR5_2D[ps].MR10_A0 = value;
        shdw_LPDDR5_2D[ps].MR10_A0 = 1;
      }
      else if ( strcmp(field, "MR10_A1") == 0) {
        mb_LPDDR5_2D[ps].MR10_A1 = value;
        shdw_LPDDR5_2D[ps].MR10_A1 = 1;
      }
      else if ( strcmp(field, "MR10_B0") == 0) {
        mb_LPDDR5_2D[ps].MR10_B0 = value;
        shdw_LPDDR5_2D[ps].MR10_B0 = 1;
      }
      else if ( strcmp(field, "MR10_B1") == 0) {
        mb_LPDDR5_2D[ps].MR10_B1 = value;
        shdw_LPDDR5_2D[ps].MR10_B1 = 1;
      }
      else if ( strcmp(field, "MR11_A0") == 0) {
        mb_LPDDR5_2D[ps].MR11_A0 = value;
        shdw_LPDDR5_2D[ps].MR11_A0 = 1;
      }
      else if ( strcmp(field, "MR11_A1") == 0) {
        mb_LPDDR5_2D[ps].MR11_A1 = value;
        shdw_LPDDR5_2D[ps].MR11_A1 = 1;
      }
      else if ( strcmp(field, "MR11_B0") == 0) {
        mb_LPDDR5_2D[ps].MR11_B0 = value;
        shdw_LPDDR5_2D[ps].MR11_B0 = 1;
      }
      else if ( strcmp(field, "MR11_B1") == 0) {
        mb_LPDDR5_2D[ps].MR11_B1 = value;
        shdw_LPDDR5_2D[ps].MR11_B1 = 1;
      }
      else if ( strcmp(field, "MR12_A0") == 0) {
        mb_LPDDR5_2D[ps].MR12_A0 = value;
        shdw_LPDDR5_2D[ps].MR12_A0 = 1;
      }
      else if ( strcmp(field, "MR12_A1") == 0) {
        mb_LPDDR5_2D[ps].MR12_A1 = value;
        shdw_LPDDR5_2D[ps].MR12_A1 = 1;
      }
      else if ( strcmp(field, "MR12_B0") == 0) {
        mb_LPDDR5_2D[ps].MR12_B0 = value;
        shdw_LPDDR5_2D[ps].MR12_B0 = 1;
      }
      else if ( strcmp(field, "MR12_B1") == 0) {
        mb_LPDDR5_2D[ps].MR12_B1 = value;
        shdw_LPDDR5_2D[ps].MR12_B1 = 1;
      }
      else if ( strcmp(field, "MR13_A0") == 0) {
        mb_LPDDR5_2D[ps].MR13_A0 = value;
        shdw_LPDDR5_2D[ps].MR13_A0 = 1;
      }
      else if ( strcmp(field, "MR13_A1") == 0) {
        mb_LPDDR5_2D[ps].MR13_A1 = value;
        shdw_LPDDR5_2D[ps].MR13_A1 = 1;
      }
      else if ( strcmp(field, "MR13_B0") == 0) {
        mb_LPDDR5_2D[ps].MR13_B0 = value;
        shdw_LPDDR5_2D[ps].MR13_B0 = 1;
      }
      else if ( strcmp(field, "MR13_B1") == 0) {
        mb_LPDDR5_2D[ps].MR13_B1 = value;
        shdw_LPDDR5_2D[ps].MR13_B1 = 1;
      }
      else if ( strcmp(field, "MR14_A0") == 0) {
        mb_LPDDR5_2D[ps].MR14_A0 = value;
        shdw_LPDDR5_2D[ps].MR14_A0 = 1;
      }
      else if ( strcmp(field, "MR14_A1") == 0) {
        mb_LPDDR5_2D[ps].MR14_A1 = value;
        shdw_LPDDR5_2D[ps].MR14_A1 = 1;
      }
      else if ( strcmp(field, "MR14_B0") == 0) {
        mb_LPDDR5_2D[ps].MR14_B0 = value;
        shdw_LPDDR5_2D[ps].MR14_B0 = 1;
      }
      else if ( strcmp(field, "MR14_B1") == 0) {
        mb_LPDDR5_2D[ps].MR14_B1 = value;
        shdw_LPDDR5_2D[ps].MR14_B1 = 1;
      }
      else if ( strcmp(field, "MR15_A0") == 0) {
        mb_LPDDR5_2D[ps].MR15_A0 = value;
        shdw_LPDDR5_2D[ps].MR15_A0 = 1;
      }
      else if ( strcmp(field, "MR15_A1") == 0) {
        mb_LPDDR5_2D[ps].MR15_A1 = value;
        shdw_LPDDR5_2D[ps].MR15_A1 = 1;
      }
      else if ( strcmp(field, "MR15_B0") == 0) {
        mb_LPDDR5_2D[ps].MR15_B0 = value;
        shdw_LPDDR5_2D[ps].MR15_B0 = 1;
      }
      else if ( strcmp(field, "MR15_B1") == 0) {
        mb_LPDDR5_2D[ps].MR15_B1 = value;
        shdw_LPDDR5_2D[ps].MR15_B1 = 1;
      }
      else if ( strcmp(field, "MR16_A0") == 0) {
        mb_LPDDR5_2D[ps].MR16_A0 = value;
        shdw_LPDDR5_2D[ps].MR16_A0 = 1;
      }
      else if ( strcmp(field, "MR16_A1") == 0) {
        mb_LPDDR5_2D[ps].MR16_A1 = value;
        shdw_LPDDR5_2D[ps].MR16_A1 = 1;
      }
      else if ( strcmp(field, "MR16_B0") == 0) {
        mb_LPDDR5_2D[ps].MR16_B0 = value;
        shdw_LPDDR5_2D[ps].MR16_B0 = 1;
      }
      else if ( strcmp(field, "MR16_B1") == 0) {
        mb_LPDDR5_2D[ps].MR16_B1 = value;
        shdw_LPDDR5_2D[ps].MR16_B1 = 1;
      }
      else if ( strcmp(field, "MR17_A0") == 0) {
        mb_LPDDR5_2D[ps].MR17_A0 = value;
        shdw_LPDDR5_2D[ps].MR17_A0 = 1;
      }
      else if ( strcmp(field, "MR17_A1") == 0) {
        mb_LPDDR5_2D[ps].MR17_A1 = value;
        shdw_LPDDR5_2D[ps].MR17_A1 = 1;
      }
      else if ( strcmp(field, "MR17_B0") == 0) {
        mb_LPDDR5_2D[ps].MR17_B0 = value;
        shdw_LPDDR5_2D[ps].MR17_B0 = 1;
      }
      else if ( strcmp(field, "MR17_B1") == 0) {
        mb_LPDDR5_2D[ps].MR17_B1 = value;
        shdw_LPDDR5_2D[ps].MR17_B1 = 1;
      }
      else if ( strcmp(field, "MR18_A0") == 0) {
        mb_LPDDR5_2D[ps].MR18_A0 = value;
        shdw_LPDDR5_2D[ps].MR18_A0 = 1;
      }
      else if ( strcmp(field, "MR18_A1") == 0) {
        mb_LPDDR5_2D[ps].MR18_A1 = value;
        shdw_LPDDR5_2D[ps].MR18_A1 = 1;
      }
      else if ( strcmp(field, "MR18_B0") == 0) {
        mb_LPDDR5_2D[ps].MR18_B0 = value;
        shdw_LPDDR5_2D[ps].MR18_B0 = 1;
      }
      else if ( strcmp(field, "MR18_B1") == 0) {
        mb_LPDDR5_2D[ps].MR18_B1 = value;
        shdw_LPDDR5_2D[ps].MR18_B1 = 1;
      }
      else if ( strcmp(field, "MR19_A0") == 0) {
        mb_LPDDR5_2D[ps].MR19_A0 = value;
        shdw_LPDDR5_2D[ps].MR19_A0 = 1;
      }
      else if ( strcmp(field, "MR19_A1") == 0) {
        mb_LPDDR5_2D[ps].MR19_A1 = value;
        shdw_LPDDR5_2D[ps].MR19_A1 = 1;
      }
      else if ( strcmp(field, "MR19_B0") == 0) {
        mb_LPDDR5_2D[ps].MR19_B0 = value;
        shdw_LPDDR5_2D[ps].MR19_B0 = 1;
      }
      else if ( strcmp(field, "MR19_B1") == 0) {
        mb_LPDDR5_2D[ps].MR19_B1 = value;
        shdw_LPDDR5_2D[ps].MR19_B1 = 1;
      }
      else if ( strcmp(field, "MR20_A0") == 0) {
        mb_LPDDR5_2D[ps].MR20_A0 = value;
        shdw_LPDDR5_2D[ps].MR20_A0 = 1;
      }
      else if ( strcmp(field, "MR20_A1") == 0) {
        mb_LPDDR5_2D[ps].MR20_A1 = value;
        shdw_LPDDR5_2D[ps].MR20_A1 = 1;
      }
      else if ( strcmp(field, "MR20_B0") == 0) {
        mb_LPDDR5_2D[ps].MR20_B0 = value;
        shdw_LPDDR5_2D[ps].MR20_B0 = 1;
      }
      else if ( strcmp(field, "MR20_B1") == 0) {
        mb_LPDDR5_2D[ps].MR20_B1 = value;
        shdw_LPDDR5_2D[ps].MR20_B1 = 1;
      }
      else if ( strcmp(field, "MR21_A0") == 0) {
        mb_LPDDR5_2D[ps].MR21_A0 = value;
        shdw_LPDDR5_2D[ps].MR21_A0 = 1;
      }
      else if ( strcmp(field, "MR21_A1") == 0) {
        mb_LPDDR5_2D[ps].MR21_A1 = value;
        shdw_LPDDR5_2D[ps].MR21_A1 = 1;
      }
      else if ( strcmp(field, "MR21_B0") == 0) {
        mb_LPDDR5_2D[ps].MR21_B0 = value;
        shdw_LPDDR5_2D[ps].MR21_B0 = 1;
      }
      else if ( strcmp(field, "MR21_B1") == 0) {
        mb_LPDDR5_2D[ps].MR21_B1 = value;
        shdw_LPDDR5_2D[ps].MR21_B1 = 1;
      }
      else if ( strcmp(field, "MR22_A0") == 0) {
        mb_LPDDR5_2D[ps].MR22_A0 = value;
        shdw_LPDDR5_2D[ps].MR22_A0 = 1;
      }
      else if ( strcmp(field, "MR22_A1") == 0) {
        mb_LPDDR5_2D[ps].MR22_A1 = value;
        shdw_LPDDR5_2D[ps].MR22_A1 = 1;
      }
      else if ( strcmp(field, "MR22_B0") == 0) {
        mb_LPDDR5_2D[ps].MR22_B0 = value;
        shdw_LPDDR5_2D[ps].MR22_B0 = 1;
      }
      else if ( strcmp(field, "MR22_B1") == 0) {
        mb_LPDDR5_2D[ps].MR22_B1 = value;
        shdw_LPDDR5_2D[ps].MR22_B1 = 1;
      }
      else if ( strcmp(field, "MR24_A0") == 0) {
        mb_LPDDR5_2D[ps].MR24_A0 = value;
        shdw_LPDDR5_2D[ps].MR24_A0 = 1;
      }
      else if ( strcmp(field, "MR24_A1") == 0) {
        mb_LPDDR5_2D[ps].MR24_A1 = value;
        shdw_LPDDR5_2D[ps].MR24_A1 = 1;
      }
      else if ( strcmp(field, "MR24_B0") == 0) {
        mb_LPDDR5_2D[ps].MR24_B0 = value;
        shdw_LPDDR5_2D[ps].MR24_B0 = 1;
      }
      else if ( strcmp(field, "MR24_B1") == 0) {
        mb_LPDDR5_2D[ps].MR24_B1 = value;
        shdw_LPDDR5_2D[ps].MR24_B1 = 1;
      }
      else if ( strcmp(field, "MR25_A0") == 0) {
        mb_LPDDR5_2D[ps].MR25_A0 = value;
        shdw_LPDDR5_2D[ps].MR25_A0 = 1;
      }
      else if ( strcmp(field, "MR25_A1") == 0) {
        mb_LPDDR5_2D[ps].MR25_A1 = value;
        shdw_LPDDR5_2D[ps].MR25_A1 = 1;
      }
      else if ( strcmp(field, "MR25_B0") == 0) {
        mb_LPDDR5_2D[ps].MR25_B0 = value;
        shdw_LPDDR5_2D[ps].MR25_B0 = 1;
      }
      else if ( strcmp(field, "MR25_B1") == 0) {
        mb_LPDDR5_2D[ps].MR25_B1 = value;
        shdw_LPDDR5_2D[ps].MR25_B1 = 1;
      }
      else if ( strcmp(field, "MR26_A0") == 0) {
        mb_LPDDR5_2D[ps].MR26_A0 = value;
        shdw_LPDDR5_2D[ps].MR26_A0 = 1;
      }
      else if ( strcmp(field, "MR26_A1") == 0) {
        mb_LPDDR5_2D[ps].MR26_A1 = value;
        shdw_LPDDR5_2D[ps].MR26_A1 = 1;
      }
      else if ( strcmp(field, "MR26_B0") == 0) {
        mb_LPDDR5_2D[ps].MR26_B0 = value;
        shdw_LPDDR5_2D[ps].MR26_B0 = 1;
      }
      else if ( strcmp(field, "MR26_B1") == 0) {
        mb_LPDDR5_2D[ps].MR26_B1 = value;
        shdw_LPDDR5_2D[ps].MR26_B1 = 1;
      }
      else if ( strcmp(field, "MR27_A0") == 0) {
        mb_LPDDR5_2D[ps].MR27_A0 = value;
        shdw_LPDDR5_2D[ps].MR27_A0 = 1;
      }
      else if ( strcmp(field, "MR27_A1") == 0) {
        mb_LPDDR5_2D[ps].MR27_A1 = value;
        shdw_LPDDR5_2D[ps].MR27_A1 = 1;
      }
      else if ( strcmp(field, "MR27_B0") == 0) {
        mb_LPDDR5_2D[ps].MR27_B0 = value;
        shdw_LPDDR5_2D[ps].MR27_B0 = 1;
      }
      else if ( strcmp(field, "MR27_B1") == 0) {
        mb_LPDDR5_2D[ps].MR27_B1 = value;
        shdw_LPDDR5_2D[ps].MR27_B1 = 1;
      }
      else if ( strcmp(field, "MR28_A0") == 0) {
        mb_LPDDR5_2D[ps].MR28_A0 = value;
        shdw_LPDDR5_2D[ps].MR28_A0 = 1;
      }
      else if ( strcmp(field, "MR28_A1") == 0) {
        mb_LPDDR5_2D[ps].MR28_A1 = value;
        shdw_LPDDR5_2D[ps].MR28_A1 = 1;
      }
      else if ( strcmp(field, "MR28_B0") == 0) {
        mb_LPDDR5_2D[ps].MR28_B0 = value;
        shdw_LPDDR5_2D[ps].MR28_B0 = 1;
      }
      else if ( strcmp(field, "MR28_B1") == 0) {
        mb_LPDDR5_2D[ps].MR28_B1 = value;
        shdw_LPDDR5_2D[ps].MR28_B1 = 1;
      }
      else if ( strcmp(field, "MR30_A0") == 0) {
        mb_LPDDR5_2D[ps].MR30_A0 = value;
        shdw_LPDDR5_2D[ps].MR30_A0 = 1;
      }
      else if ( strcmp(field, "MR30_A1") == 0) {
        mb_LPDDR5_2D[ps].MR30_A1 = value;
        shdw_LPDDR5_2D[ps].MR30_A1 = 1;
      }
      else if ( strcmp(field, "MR30_B0") == 0) {
        mb_LPDDR5_2D[ps].MR30_B0 = value;
        shdw_LPDDR5_2D[ps].MR30_B0 = 1;
      }
      else if ( strcmp(field, "MR30_B1") == 0) {
        mb_LPDDR5_2D[ps].MR30_B1 = value;
        shdw_LPDDR5_2D[ps].MR30_B1 = 1;
      }
      else if ( strcmp(field, "MR31_A0") == 0) {
        mb_LPDDR5_2D[ps].MR31_A0 = value;
        shdw_LPDDR5_2D[ps].MR31_A0 = 1;
      }
      else if ( strcmp(field, "MR31_A1") == 0) {
        mb_LPDDR5_2D[ps].MR31_A1 = value;
        shdw_LPDDR5_2D[ps].MR31_A1 = 1;
      }
      else if ( strcmp(field, "MR31_B0") == 0) {
        mb_LPDDR5_2D[ps].MR31_B0 = value;
        shdw_LPDDR5_2D[ps].MR31_B0 = 1;
      }
      else if ( strcmp(field, "MR31_B1") == 0) {
        mb_LPDDR5_2D[ps].MR31_B1 = value;
        shdw_LPDDR5_2D[ps].MR31_B1 = 1;
      }
      else if ( strcmp(field, "MR32_A0") == 0) {
        mb_LPDDR5_2D[ps].MR32_A0 = value;
        shdw_LPDDR5_2D[ps].MR32_A0 = 1;
      }
      else if ( strcmp(field, "MR32_A1") == 0) {
        mb_LPDDR5_2D[ps].MR32_A1 = value;
        shdw_LPDDR5_2D[ps].MR32_A1 = 1;
      }
      else if ( strcmp(field, "MR32_B0") == 0) {
        mb_LPDDR5_2D[ps].MR32_B0 = value;
        shdw_LPDDR5_2D[ps].MR32_B0 = 1;
      }
      else if ( strcmp(field, "MR32_B1") == 0) {
        mb_LPDDR5_2D[ps].MR32_B1 = value;
        shdw_LPDDR5_2D[ps].MR32_B1 = 1;
      }
      else if ( strcmp(field, "MR33_A0") == 0) {
        mb_LPDDR5_2D[ps].MR33_A0 = value;
        shdw_LPDDR5_2D[ps].MR33_A0 = 1;
      }
      else if ( strcmp(field, "MR33_A1") == 0) {
        mb_LPDDR5_2D[ps].MR33_A1 = value;
        shdw_LPDDR5_2D[ps].MR33_A1 = 1;
      }
      else if ( strcmp(field, "MR33_B0") == 0) {
        mb_LPDDR5_2D[ps].MR33_B0 = value;
        shdw_LPDDR5_2D[ps].MR33_B0 = 1;
      }
      else if ( strcmp(field, "MR33_B1") == 0) {
        mb_LPDDR5_2D[ps].MR33_B1 = value;
        shdw_LPDDR5_2D[ps].MR33_B1 = 1;
      }
      else if ( strcmp(field, "MR34_A0") == 0) {
        mb_LPDDR5_2D[ps].MR34_A0 = value;
        shdw_LPDDR5_2D[ps].MR34_A0 = 1;
      }
      else if ( strcmp(field, "MR34_A1") == 0) {
        mb_LPDDR5_2D[ps].MR34_A1 = value;
        shdw_LPDDR5_2D[ps].MR34_A1 = 1;
      }
      else if ( strcmp(field, "MR34_B0") == 0) {
        mb_LPDDR5_2D[ps].MR34_B0 = value;
        shdw_LPDDR5_2D[ps].MR34_B0 = 1;
      }
      else if ( strcmp(field, "MR34_B1") == 0) {
        mb_LPDDR5_2D[ps].MR34_B1 = value;
        shdw_LPDDR5_2D[ps].MR34_B1 = 1;
      }
      else if ( strcmp(field, "MR37_A0") == 0) {
        mb_LPDDR5_2D[ps].MR37_A0 = value;
        shdw_LPDDR5_2D[ps].MR37_A0 = 1;
      }
      else if ( strcmp(field, "MR37_A1") == 0) {
        mb_LPDDR5_2D[ps].MR37_A1 = value;
        shdw_LPDDR5_2D[ps].MR37_A1 = 1;
      }
      else if ( strcmp(field, "MR37_B0") == 0) {
        mb_LPDDR5_2D[ps].MR37_B0 = value;
        shdw_LPDDR5_2D[ps].MR37_B0 = 1;
      }
      else if ( strcmp(field, "MR37_B1") == 0) {
        mb_LPDDR5_2D[ps].MR37_B1 = value;
        shdw_LPDDR5_2D[ps].MR37_B1 = 1;
      }
      else if ( strcmp(field, "MR40_A0") == 0) {
        mb_LPDDR5_2D[ps].MR40_A0 = value;
        shdw_LPDDR5_2D[ps].MR40_A0 = 1;
      }
      else if ( strcmp(field, "MR40_A1") == 0) {
        mb_LPDDR5_2D[ps].MR40_A1 = value;
        shdw_LPDDR5_2D[ps].MR40_A1 = 1;
      }
      else if ( strcmp(field, "MR40_B0") == 0) {
        mb_LPDDR5_2D[ps].MR40_B0 = value;
        shdw_LPDDR5_2D[ps].MR40_B0 = 1;
      }
      else if ( strcmp(field, "MR40_B1") == 0) {
        mb_LPDDR5_2D[ps].MR40_B1 = value;
        shdw_LPDDR5_2D[ps].MR40_B1 = 1;
      }
      else if ( strcmp(field, "MR41_A0") == 0) {
        mb_LPDDR5_2D[ps].MR41_A0 = value;
        shdw_LPDDR5_2D[ps].MR41_A0 = 1;
      }
      else if ( strcmp(field, "MR41_A1") == 0) {
        mb_LPDDR5_2D[ps].MR41_A1 = value;
        shdw_LPDDR5_2D[ps].MR41_A1 = 1;
      }
      else if ( strcmp(field, "MR41_B0") == 0) {
        mb_LPDDR5_2D[ps].MR41_B0 = value;
        shdw_LPDDR5_2D[ps].MR41_B0 = 1;
      }
      else if ( strcmp(field, "MR41_B1") == 0) {
        mb_LPDDR5_2D[ps].MR41_B1 = value;
        shdw_LPDDR5_2D[ps].MR41_B1 = 1;
      }
      else if ( strcmp(field, "Disable2D") == 0) {
        mb_LPDDR5_2D[ps].Disable2D = value;
        shdw_LPDDR5_2D[ps].Disable2D = 1;
      }
      else if ( strcmp(field, "VrefSamples") == 0) {
        mb_LPDDR5_2D[ps].VrefSamples = value;
        shdw_LPDDR5_2D[ps].VrefSamples = 1;
      }
      else if ( strcmp(field, "RdWrPatternA") == 0) {
        mb_LPDDR5_2D[ps].RdWrPatternA = value;
        shdw_LPDDR5_2D[ps].RdWrPatternA = 1;
      }
      else if ( strcmp(field, "RdWrPatternB") == 0) {
        mb_LPDDR5_2D[ps].RdWrPatternB = value;
        shdw_LPDDR5_2D[ps].RdWrPatternB = 1;
      }
      else if ( strcmp(field, "RdWrInvertA") == 0) {
        mb_LPDDR5_2D[ps].RdWrInvertA = value;
        shdw_LPDDR5_2D[ps].RdWrInvertA = 1;
      }
      else if ( strcmp(field, "RdWrInvertB") == 0) {
        mb_LPDDR5_2D[ps].RdWrInvertB = value;
        shdw_LPDDR5_2D[ps].RdWrInvertB = 1;
      }
    }
    else {
      dwc_ddrphy_phyinit_assert(0,"%s invalid value for Train2D=%d\n", printf_header, Train2D);
      return -3;
    }

    dwc_ddrphy_phyinit_cmnt ("%s Setting mb_LPDDR5_%dD[%d].%s to 0x%x\n", printf_header, Train2D+1, ps, field, value);
    return 0;
}
/** @} */
