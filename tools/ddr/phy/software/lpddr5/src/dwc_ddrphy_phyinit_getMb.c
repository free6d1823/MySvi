/** \file */

#include <string.h>
#include "dwc_ddrphy_phyinit.h"


/**  \addtogroup SrcFunc
 *   @{
 */

/** @brief API to read the messageBlock structure in PhyInit.
 *
 *  This function can be used to read training firmware 1D/2D messageBlock fields
 *  for a given PState in the PhyInit Data structure.  As an example, to read MsgMsic to 0x4 for PState 3,
 *  for 1D Training :
 *  @code{.c}
 *  dwc_ddrphy_phyinit_setMB(3, "MsgMisc", 0x4, 0);
 *  @endcode
 *
 *  \note This functions doesn't read the DMEM address in SRAM. It returns
 *  what is programed in the PhyInit messageBlock structure which is used
 *  to write to the SRAM once dwc_ddrphy_phyinit_F_loadDMEM() is called in
 *  dwc_ddrphy_phyinit_sequence().
 *
 * @param[in]   phyctx  PhyInit context
 * @param[in]   ps      integer between 0-3. Specifies the PState for which the
 * messageBlock field should be set.
 * @param[in]   field   A string representing the messageBlock field to be
 * programed. refer to the messageBlock data structure for definition of fields
 * applicable to each protocol.
 * @param[in]   Train2D determined if the field should be set on 2D or 1D
 * messageBlock.
 * @return field value on success. Returns following values based on
 * error:
 * - -1 : messageBlock field specified by the input \c field string is not
 * found in the messageBlock data structure.
 * - -2 : when DramType does not support 2D training but a 2D training field is
 * programmed.
 * - -3 : Train2D inputs is neither 1 or 0.
 */
int dwc_ddrphy_phyinit_getMb (phyinit_config_t* phyctx, int ps, char *field) {

    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    int Train2D = pRuntimeConfig->Train2D;

    PMU_SMB_LPDDR5_1D_t*   mb_LPDDR5_1D = phyctx->mb_LPDDR5_1D;
    PMU_SMB_LPDDR5_2D_t* mb_LPDDR5_2D = phyctx->mb_LPDDR5_2D;

    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_setMb]";

      if (Train2D == 0) {
          if ( strcmp(field, "Reserved00") == 0)
              return mb_LPDDR5_1D[ps].Reserved00;
          else if ( strcmp(field, "MsgMisc") == 0)
              return mb_LPDDR5_1D[ps].MsgMisc;
          else if ( strcmp(field, "Pstate") == 0)
              return mb_LPDDR5_1D[ps].Pstate;
          else if ( strcmp(field, "PllBypassEn") == 0)
              return mb_LPDDR5_1D[ps].PllBypassEn;
          else if ( strcmp(field, "DRAMFreq") == 0)
              return mb_LPDDR5_1D[ps].DRAMFreq;
          else if ( strcmp(field, "DfiFreqRatio") == 0)
              return mb_LPDDR5_1D[ps].DfiFreqRatio;
          else if ( strcmp(field, "BPZNResVal") == 0)
              return mb_LPDDR5_1D[ps].BPZNResVal;
          else if ( strcmp(field, "PhyOdtImpedance") == 0)
              return mb_LPDDR5_1D[ps].PhyOdtImpedance;
          else if ( strcmp(field, "PhyDrvImpedance") == 0)
              return mb_LPDDR5_1D[ps].PhyDrvImpedance;
          else if ( strcmp(field, "PhyVref") == 0)
              return mb_LPDDR5_1D[ps].PhyVref;
          else if ( strcmp(field, "Lp4Misc") == 0)
              return mb_LPDDR5_1D[ps].Lp4Misc;
          else if ( strcmp(field, "Reserved0E") == 0)
              return mb_LPDDR5_1D[ps].Reserved0E;
          else if ( strcmp(field, "SequenceCtrl") == 0)
              return mb_LPDDR5_1D[ps].SequenceCtrl;
          else if ( strcmp(field, "HdtCtrl") == 0)
              return mb_LPDDR5_1D[ps].HdtCtrl;
          else if ( strcmp(field, "Reserved13") == 0)
              return mb_LPDDR5_1D[ps].Reserved13;
          else if ( strcmp(field, "Reserved14") == 0)
              return mb_LPDDR5_1D[ps].Reserved14;
          else if ( strcmp(field, "Reserved15") == 0)
              return mb_LPDDR5_1D[ps].Reserved15;
          else if ( strcmp(field, "DFIMRLMargin") == 0)
              return mb_LPDDR5_1D[ps].DFIMRLMargin;
          else if ( strcmp(field, "Reserved17") == 0)
              return mb_LPDDR5_1D[ps].Reserved17;
          else if ( strcmp(field, "Reserved18") == 0)
              return mb_LPDDR5_1D[ps].Reserved18;
          else if ( strcmp(field, "Lp4Quickboot") == 0)
              return mb_LPDDR5_1D[ps].Lp4Quickboot;
          else if ( strcmp(field, "Reserved1A") == 0)
              return mb_LPDDR5_1D[ps].Reserved1A;
          else if ( strcmp(field, "CATrainOpt") == 0)
              return mb_LPDDR5_1D[ps].CATrainOpt;
          else if ( strcmp(field, "X8Mode") == 0)
              return mb_LPDDR5_1D[ps].X8Mode;
          else if ( strcmp(field, "Reserved1F") == 0)
              return mb_LPDDR5_1D[ps].Reserved1F;
          else if ( strcmp(field, "PhyConfigOverride") == 0)
              return mb_LPDDR5_1D[ps].PhyConfigOverride;
          else if ( strcmp(field, "EnabledDQsChA") == 0)
              return mb_LPDDR5_1D[ps].EnabledDQsChA;
          else if ( strcmp(field, "CsPresentChA") == 0)
              return mb_LPDDR5_1D[ps].CsPresentChA;
          else if ( strcmp(field, "CATerminatingRankChA") == 0)
              return mb_LPDDR5_1D[ps].CATerminatingRankChA;
          else if ( strcmp(field, "EnabledDQsChB") == 0)
              return mb_LPDDR5_1D[ps].EnabledDQsChB;
          else if ( strcmp(field, "CsPresentChB") == 0)
              return mb_LPDDR5_1D[ps].CsPresentChB;
          else if ( strcmp(field, "CATerminatingRankChB") == 0)
              return mb_LPDDR5_1D[ps].CATerminatingRankChB;
          else if ( strcmp(field, "MR1_A0") == 0)
              return mb_LPDDR5_1D[ps].MR1_A0;
          else if ( strcmp(field, "MR1_A1") == 0)
              return mb_LPDDR5_1D[ps].MR1_A1;
          else if ( strcmp(field, "MR1_B0") == 0)
              return mb_LPDDR5_1D[ps].MR1_B0;
          else if ( strcmp(field, "MR1_B1") == 0)
              return mb_LPDDR5_1D[ps].MR1_B1;
          else if ( strcmp(field, "MR2_A0") == 0)
              return mb_LPDDR5_1D[ps].MR2_A0;
          else if ( strcmp(field, "MR2_A1") == 0)
              return mb_LPDDR5_1D[ps].MR2_A1;
          else if ( strcmp(field, "MR2_B0") == 0)
              return mb_LPDDR5_1D[ps].MR2_B0;
          else if ( strcmp(field, "MR2_B1") == 0)
              return mb_LPDDR5_1D[ps].MR2_B1;
          else if ( strcmp(field, "MR3_A0") == 0)
              return mb_LPDDR5_1D[ps].MR3_A0;
          else if ( strcmp(field, "MR3_A1") == 0)
              return mb_LPDDR5_1D[ps].MR3_A1;
          else if ( strcmp(field, "MR3_B0") == 0)
              return mb_LPDDR5_1D[ps].MR3_B0;
          else if ( strcmp(field, "MR3_B1") == 0)
              return mb_LPDDR5_1D[ps].MR3_B1;
          else if ( strcmp(field, "MR10_A0") == 0)
              return mb_LPDDR5_1D[ps].MR10_A0;
          else if ( strcmp(field, "MR10_A1") == 0)
              return mb_LPDDR5_1D[ps].MR10_A1;
          else if ( strcmp(field, "MR10_B0") == 0)
              return mb_LPDDR5_1D[ps].MR10_B0;
          else if ( strcmp(field, "MR10_B1") == 0)
              return mb_LPDDR5_1D[ps].MR10_B1;
          else if ( strcmp(field, "MR11_A0") == 0)
              return mb_LPDDR5_1D[ps].MR11_A0;
          else if ( strcmp(field, "MR11_A1") == 0)
              return mb_LPDDR5_1D[ps].MR11_A1;
          else if ( strcmp(field, "MR11_B0") == 0)
              return mb_LPDDR5_1D[ps].MR11_B0;
          else if ( strcmp(field, "MR11_B1") == 0)
              return mb_LPDDR5_1D[ps].MR11_B1;
          else if ( strcmp(field, "MR12_A0") == 0)
              return mb_LPDDR5_1D[ps].MR12_A0;
          else if ( strcmp(field, "MR12_A1") == 0)
              return mb_LPDDR5_1D[ps].MR12_A1;
          else if ( strcmp(field, "MR12_B0") == 0)
              return mb_LPDDR5_1D[ps].MR12_B0;
          else if ( strcmp(field, "MR12_B1") == 0)
              return mb_LPDDR5_1D[ps].MR12_B1;
          else if ( strcmp(field, "MR13_A0") == 0)
              return mb_LPDDR5_1D[ps].MR13_A0;
          else if ( strcmp(field, "MR13_A1") == 0)
              return mb_LPDDR5_1D[ps].MR13_A1;
          else if ( strcmp(field, "MR13_B0") == 0)
              return mb_LPDDR5_1D[ps].MR13_B0;
          else if ( strcmp(field, "MR13_B1") == 0)
              return mb_LPDDR5_1D[ps].MR13_B1;
          else if ( strcmp(field, "MR14_A0") == 0)
              return mb_LPDDR5_1D[ps].MR14_A0;
          else if ( strcmp(field, "MR14_A1") == 0)
              return mb_LPDDR5_1D[ps].MR14_A1;
          else if ( strcmp(field, "MR14_B0") == 0)
              return mb_LPDDR5_1D[ps].MR14_B0;
          else if ( strcmp(field, "MR14_B1") == 0)
              return mb_LPDDR5_1D[ps].MR14_B1;
          else if ( strcmp(field, "MR15_A0") == 0)
              return mb_LPDDR5_1D[ps].MR15_A0;
          else if ( strcmp(field, "MR15_A1") == 0)
              return mb_LPDDR5_1D[ps].MR15_A1;
          else if ( strcmp(field, "MR15_B0") == 0)
              return mb_LPDDR5_1D[ps].MR15_B0;
          else if ( strcmp(field, "MR15_B1") == 0)
              return mb_LPDDR5_1D[ps].MR15_B1;
          else if ( strcmp(field, "MR16_A0") == 0)
              return mb_LPDDR5_1D[ps].MR16_A0;
          else if ( strcmp(field, "MR16_A1") == 0)
              return mb_LPDDR5_1D[ps].MR16_A1;
          else if ( strcmp(field, "MR16_B0") == 0)
              return mb_LPDDR5_1D[ps].MR16_B0;
          else if ( strcmp(field, "MR16_B1") == 0)
              return mb_LPDDR5_1D[ps].MR16_B1;
          else if ( strcmp(field, "MR17_A0") == 0)
              return mb_LPDDR5_1D[ps].MR17_A0;
          else if ( strcmp(field, "MR17_A1") == 0)
              return mb_LPDDR5_1D[ps].MR17_A1;
          else if ( strcmp(field, "MR17_B0") == 0)
              return mb_LPDDR5_1D[ps].MR17_B0;
          else if ( strcmp(field, "MR17_B1") == 0)
              return mb_LPDDR5_1D[ps].MR17_B1;
          else if ( strcmp(field, "MR18_A0") == 0)
              return mb_LPDDR5_1D[ps].MR18_A0;
          else if ( strcmp(field, "MR18_A1") == 0)
              return mb_LPDDR5_1D[ps].MR18_A1;
          else if ( strcmp(field, "MR18_B0") == 0)
              return mb_LPDDR5_1D[ps].MR18_B0;
          else if ( strcmp(field, "MR18_B1") == 0)
              return mb_LPDDR5_1D[ps].MR18_B1;
          else if ( strcmp(field, "MR19_A0") == 0)
              return mb_LPDDR5_1D[ps].MR19_A0;
          else if ( strcmp(field, "MR19_A1") == 0)
              return mb_LPDDR5_1D[ps].MR19_A1;
          else if ( strcmp(field, "MR19_B0") == 0)
              return mb_LPDDR5_1D[ps].MR19_B0;
          else if ( strcmp(field, "MR19_B1") == 0)
              return mb_LPDDR5_1D[ps].MR19_B1;
          else if ( strcmp(field, "MR20_A0") == 0)
              return mb_LPDDR5_1D[ps].MR20_A0;
          else if ( strcmp(field, "MR20_A1") == 0)
              return mb_LPDDR5_1D[ps].MR20_A1;
          else if ( strcmp(field, "MR20_B0") == 0)
              return mb_LPDDR5_1D[ps].MR20_B0;
          else if ( strcmp(field, "MR20_B1") == 0)
              return mb_LPDDR5_1D[ps].MR20_B1;
          else if ( strcmp(field, "MR21_A0") == 0)
              return mb_LPDDR5_1D[ps].MR21_A0;
          else if ( strcmp(field, "MR21_A1") == 0)
              return mb_LPDDR5_1D[ps].MR21_A1;
          else if ( strcmp(field, "MR21_B0") == 0)
              return mb_LPDDR5_1D[ps].MR21_B0;
          else if ( strcmp(field, "MR21_B1") == 0)
              return mb_LPDDR5_1D[ps].MR21_B1;
          else if ( strcmp(field, "MR22_A0") == 0)
              return mb_LPDDR5_1D[ps].MR22_A0;
          else if ( strcmp(field, "MR22_A1") == 0)
              return mb_LPDDR5_1D[ps].MR22_A1;
          else if ( strcmp(field, "MR22_B0") == 0)
              return mb_LPDDR5_1D[ps].MR22_B0;
          else if ( strcmp(field, "MR22_B1") == 0)
              return mb_LPDDR5_1D[ps].MR22_B1;
          else if ( strcmp(field, "MR24_A0") == 0)
              return mb_LPDDR5_1D[ps].MR24_A0;
          else if ( strcmp(field, "MR24_A1") == 0)
              return mb_LPDDR5_1D[ps].MR24_A1;
          else if ( strcmp(field, "MR24_B0") == 0)
              return mb_LPDDR5_1D[ps].MR24_B0;
          else if ( strcmp(field, "MR24_B1") == 0)
              return mb_LPDDR5_1D[ps].MR24_B1;
          else if ( strcmp(field, "MR25_A0") == 0)
              return mb_LPDDR5_1D[ps].MR25_A0;
          else if ( strcmp(field, "MR25_A1") == 0)
              return mb_LPDDR5_1D[ps].MR25_A1;
          else if ( strcmp(field, "MR25_B0") == 0)
              return mb_LPDDR5_1D[ps].MR25_B0;
          else if ( strcmp(field, "MR25_B1") == 0)
              return mb_LPDDR5_1D[ps].MR25_B1;
          else if ( strcmp(field, "MR26_A0") == 0)
              return mb_LPDDR5_1D[ps].MR26_A0;
          else if ( strcmp(field, "MR26_A1") == 0)
              return mb_LPDDR5_1D[ps].MR26_A1;
          else if ( strcmp(field, "MR26_B0") == 0)
              return mb_LPDDR5_1D[ps].MR26_B0;
          else if ( strcmp(field, "MR26_B1") == 0)
              return mb_LPDDR5_1D[ps].MR26_B1;
          else if ( strcmp(field, "MR27_A0") == 0)
              return mb_LPDDR5_1D[ps].MR27_A0;
          else if ( strcmp(field, "MR27_A1") == 0)
              return mb_LPDDR5_1D[ps].MR27_A1;
          else if ( strcmp(field, "MR27_B0") == 0)
              return mb_LPDDR5_1D[ps].MR27_B0;
          else if ( strcmp(field, "MR27_B1") == 0)
              return mb_LPDDR5_1D[ps].MR27_B1;
          else if ( strcmp(field, "MR28_A0") == 0)
              return mb_LPDDR5_1D[ps].MR28_A0;
          else if ( strcmp(field, "MR28_A1") == 0)
              return mb_LPDDR5_1D[ps].MR28_A1;
          else if ( strcmp(field, "MR28_B0") == 0)
              return mb_LPDDR5_1D[ps].MR28_B0;
          else if ( strcmp(field, "MR28_B1") == 0)
              return mb_LPDDR5_1D[ps].MR28_B1;
          else if ( strcmp(field, "MR30_A0") == 0)
              return mb_LPDDR5_1D[ps].MR30_A0;
          else if ( strcmp(field, "MR30_A1") == 0)
              return mb_LPDDR5_1D[ps].MR30_A1;
          else if ( strcmp(field, "MR30_B0") == 0)
              return mb_LPDDR5_1D[ps].MR30_B0;
          else if ( strcmp(field, "MR30_B1") == 0)
              return mb_LPDDR5_1D[ps].MR30_B1;
          else if ( strcmp(field, "MR31_A0") == 0)
              return mb_LPDDR5_1D[ps].MR31_A0;
          else if ( strcmp(field, "MR31_A1") == 0)
              return mb_LPDDR5_1D[ps].MR31_A1;
          else if ( strcmp(field, "MR31_B0") == 0)
              return mb_LPDDR5_1D[ps].MR31_B0;
          else if ( strcmp(field, "MR31_B1") == 0)
              return mb_LPDDR5_1D[ps].MR31_B1;
          else if ( strcmp(field, "MR32_A0") == 0)
              return mb_LPDDR5_1D[ps].MR32_A0;
          else if ( strcmp(field, "MR32_A1") == 0)
              return mb_LPDDR5_1D[ps].MR32_A1;
          else if ( strcmp(field, "MR32_B0") == 0)
              return mb_LPDDR5_1D[ps].MR32_B0;
          else if ( strcmp(field, "MR32_B1") == 0)
              return mb_LPDDR5_1D[ps].MR32_B1;
          else if ( strcmp(field, "MR33_A0") == 0)
              return mb_LPDDR5_1D[ps].MR33_A0;
          else if ( strcmp(field, "MR33_A1") == 0)
              return mb_LPDDR5_1D[ps].MR33_A1;
          else if ( strcmp(field, "MR33_B0") == 0)
              return mb_LPDDR5_1D[ps].MR33_B0;
          else if ( strcmp(field, "MR33_B1") == 0)
              return mb_LPDDR5_1D[ps].MR33_B1;
          else if ( strcmp(field, "MR34_A0") == 0)
              return mb_LPDDR5_1D[ps].MR34_A0;
          else if ( strcmp(field, "MR34_A1") == 0)
              return mb_LPDDR5_1D[ps].MR34_A1;
          else if ( strcmp(field, "MR34_B0") == 0)
              return mb_LPDDR5_1D[ps].MR34_B0;
          else if ( strcmp(field, "MR34_B1") == 0)
              return mb_LPDDR5_1D[ps].MR34_B1;
          else if ( strcmp(field, "MR37_A0") == 0)
              return mb_LPDDR5_1D[ps].MR37_A0;
          else if ( strcmp(field, "MR37_A1") == 0)
              return mb_LPDDR5_1D[ps].MR37_A1;
          else if ( strcmp(field, "MR37_B0") == 0)
              return mb_LPDDR5_1D[ps].MR37_B0;
          else if ( strcmp(field, "MR37_B1") == 0)
              return mb_LPDDR5_1D[ps].MR37_B1;
          else if ( strcmp(field, "MR40_A0") == 0)
              return mb_LPDDR5_1D[ps].MR40_A0;
          else if ( strcmp(field, "MR40_A1") == 0)
              return mb_LPDDR5_1D[ps].MR40_A1;
          else if ( strcmp(field, "MR40_B0") == 0)
              return mb_LPDDR5_1D[ps].MR40_B0;
          else if ( strcmp(field, "MR40_B1") == 0)
              return mb_LPDDR5_1D[ps].MR40_B1;
          else if ( strcmp(field, "MR41_A0") == 0)
              return mb_LPDDR5_1D[ps].MR41_A0;
          else if ( strcmp(field, "MR41_A1") == 0)
              return mb_LPDDR5_1D[ps].MR41_A1;
          else if ( strcmp(field, "MR41_B0") == 0)
              return mb_LPDDR5_1D[ps].MR41_B0;
          else if ( strcmp(field, "MR41_B1") == 0)
              return mb_LPDDR5_1D[ps].MR41_B1;
          else if ( strcmp(field, "Disable2D") == 0)
              return mb_LPDDR5_1D[ps].Disable2D;
          else if ( strcmp(field, "VrefSamples") == 0)
              return mb_LPDDR5_1D[ps].VrefSamples;
          else if ( strcmp(field, "RdWrPatternA") == 0)
              return mb_LPDDR5_1D[ps].RdWrPatternA;
          else if ( strcmp(field, "RdWrPatternB") == 0)
              return mb_LPDDR5_1D[ps].RdWrPatternB;
          else if ( strcmp(field, "RdWrInvertA") == 0)
              return mb_LPDDR5_1D[ps].RdWrInvertA;
          else if ( strcmp(field, "RdWrInvertB") == 0)
              return mb_LPDDR5_1D[ps].RdWrInvertB;
          else {
              dwc_ddrphy_phyinit_assert(0,"%s unknown messageBlock field name '%s', Train2D=%d\n", printf_header, field,Train2D);
              return -1;
          }
      }
      else if (Train2D == 1) {
              if ( strcmp(field, "Reserved00") == 0)
                return  mb_LPDDR5_2D[ps].Reserved00;
              else if ( strcmp(field, "MsgMisc") == 0)
                return  mb_LPDDR5_2D[ps].MsgMisc;
              else if ( strcmp(field, "Pstate") == 0)
                return  mb_LPDDR5_2D[ps].Pstate;
              else if ( strcmp(field, "PllBypassEn") == 0)
                return  mb_LPDDR5_2D[ps].PllBypassEn;
              else if ( strcmp(field, "DRAMFreq") == 0)
                return  mb_LPDDR5_2D[ps].DRAMFreq;
              else if ( strcmp(field, "DfiFreqRatio") == 0)
                return  mb_LPDDR5_2D[ps].DfiFreqRatio;
              else if ( strcmp(field, "BPZNResVal") == 0)
                return  mb_LPDDR5_2D[ps].BPZNResVal;
              else if ( strcmp(field, "PhyOdtImpedance") == 0)
                return  mb_LPDDR5_2D[ps].PhyOdtImpedance;
              else if ( strcmp(field, "PhyDrvImpedance") == 0)
                return  mb_LPDDR5_2D[ps].PhyDrvImpedance;
              else if ( strcmp(field, "PhyVref") == 0)
                return  mb_LPDDR5_2D[ps].PhyVref;
              else if ( strcmp(field, "Lp4Misc") == 0)
                return  mb_LPDDR5_2D[ps].Lp4Misc;
              else if ( strcmp(field, "Reserved0E") == 0)
                return  mb_LPDDR5_2D[ps].Reserved0E;
              else if ( strcmp(field, "SequenceCtrl") == 0)
                return  mb_LPDDR5_2D[ps].SequenceCtrl;
              else if ( strcmp(field, "HdtCtrl") == 0)
                return  mb_LPDDR5_2D[ps].HdtCtrl;
              else if ( strcmp(field, "Reserved13") == 0)
                return  mb_LPDDR5_2D[ps].Reserved13;
              else if ( strcmp(field, "Reserved14") == 0)
                return  mb_LPDDR5_2D[ps].Reserved14;
              else if ( strcmp(field, "Reserved15") == 0)
                return  mb_LPDDR5_2D[ps].Reserved15;
              else if ( strcmp(field, "DFIMRLMargin") == 0)
                return  mb_LPDDR5_2D[ps].DFIMRLMargin;
              else if ( strcmp(field, "Reserved17") == 0)
                return  mb_LPDDR5_2D[ps].Reserved17;
              else if ( strcmp(field, "Reserved18") == 0)
                return  mb_LPDDR5_2D[ps].Reserved18;
              else if ( strcmp(field, "Reserved1A") == 0)
                return  mb_LPDDR5_2D[ps].Reserved1A;
              else if ( strcmp(field, "CATrainOpt") == 0)
                return  mb_LPDDR5_2D[ps].CATrainOpt;
              else if ( strcmp(field, "X8Mode") == 0)
                return  mb_LPDDR5_2D[ps].X8Mode;
              else if ( strcmp(field, "RX2D_TrainOpt") == 0)
                return  mb_LPDDR5_2D[ps].RX2D_TrainOpt;
              else if ( strcmp(field, "TX2D_TrainOpt") == 0)
                return  mb_LPDDR5_2D[ps].TX2D_TrainOpt;
              else if ( strcmp(field, "Reserved1F") == 0)
                return  mb_LPDDR5_2D[ps].Reserved1F;
              else if ( strcmp(field, "Delay_Weight2D") == 0)
                return  mb_LPDDR5_2D[ps].Delay_Weight2D;
              else if ( strcmp(field, "Voltage_Weight2D") == 0)
                return  mb_LPDDR5_2D[ps].Voltage_Weight2D;
              else if ( strcmp(field, "PhyConfigOverride") == 0)
                return  mb_LPDDR5_2D[ps].PhyConfigOverride;
              else if ( strcmp(field, "EnabledDQsChA") == 0)
                return  mb_LPDDR5_2D[ps].EnabledDQsChA;
              else if ( strcmp(field, "CsPresentChA") == 0)
                return  mb_LPDDR5_2D[ps].CsPresentChA;
              else if ( strcmp(field, "CATerminatingRankChA") == 0)
                return  mb_LPDDR5_2D[ps].CATerminatingRankChA;
              else if ( strcmp(field, "EnabledDQsChB") == 0)
                return  mb_LPDDR5_2D[ps].EnabledDQsChB;
              else if ( strcmp(field, "CsPresentChB") == 0)
                return  mb_LPDDR5_2D[ps].CsPresentChB;
              else if ( strcmp(field, "CATerminatingRankChB") == 0)
                return  mb_LPDDR5_2D[ps].CATerminatingRankChB;
              else if ( strcmp(field, "MR1_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR1_A0;
              else if ( strcmp(field, "MR1_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR1_A1;
              else if ( strcmp(field, "MR1_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR1_B0;
              else if ( strcmp(field, "MR1_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR1_B1;
              else if ( strcmp(field, "MR2_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR2_A0;
              else if ( strcmp(field, "MR2_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR2_A1;
              else if ( strcmp(field, "MR2_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR2_B0;
              else if ( strcmp(field, "MR2_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR2_B1;
              else if ( strcmp(field, "MR3_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR3_A0;
              else if ( strcmp(field, "MR3_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR3_A1;
              else if ( strcmp(field, "MR3_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR3_B0;
              else if ( strcmp(field, "MR3_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR3_B1;
              else if ( strcmp(field, "MR10_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR10_A0;
              else if ( strcmp(field, "MR10_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR10_A1;
              else if ( strcmp(field, "MR10_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR10_B0;
              else if ( strcmp(field, "MR10_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR10_B1;
              else if ( strcmp(field, "MR11_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR11_A0;
              else if ( strcmp(field, "MR11_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR11_A1;
              else if ( strcmp(field, "MR11_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR11_B0;
              else if ( strcmp(field, "MR11_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR11_B1;
              else if ( strcmp(field, "MR12_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR12_A0;
              else if ( strcmp(field, "MR12_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR12_A1;
              else if ( strcmp(field, "MR12_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR12_B0;
              else if ( strcmp(field, "MR12_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR12_B1;
              else if ( strcmp(field, "MR13_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR13_A0;
              else if ( strcmp(field, "MR13_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR13_A1;
              else if ( strcmp(field, "MR13_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR13_B0;
              else if ( strcmp(field, "MR13_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR13_B1;
              else if ( strcmp(field, "MR14_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR14_A0;
              else if ( strcmp(field, "MR14_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR14_A1;
              else if ( strcmp(field, "MR14_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR14_B0;
              else if ( strcmp(field, "MR14_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR14_B1;
              else if ( strcmp(field, "MR15_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR15_A0;
              else if ( strcmp(field, "MR15_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR15_A1;
              else if ( strcmp(field, "MR15_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR15_B0;
              else if ( strcmp(field, "MR15_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR15_B1;
              else if ( strcmp(field, "MR16_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR16_A0;
              else if ( strcmp(field, "MR16_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR16_A1;
              else if ( strcmp(field, "MR16_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR16_B0;
              else if ( strcmp(field, "MR16_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR16_B1;
              else if ( strcmp(field, "MR17_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR17_A0;
              else if ( strcmp(field, "MR17_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR17_A1;
              else if ( strcmp(field, "MR17_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR17_B0;
              else if ( strcmp(field, "MR17_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR17_B1;
              else if ( strcmp(field, "MR18_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR18_A0;
              else if ( strcmp(field, "MR18_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR18_A1;
              else if ( strcmp(field, "MR18_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR18_B0;
              else if ( strcmp(field, "MR18_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR18_B1;
              else if ( strcmp(field, "MR19_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR19_A0;
              else if ( strcmp(field, "MR19_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR19_A1;
              else if ( strcmp(field, "MR19_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR19_B0;
              else if ( strcmp(field, "MR19_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR19_B1;
              else if ( strcmp(field, "MR20_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR20_A0;
              else if ( strcmp(field, "MR20_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR20_A1;
              else if ( strcmp(field, "MR20_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR20_B0;
              else if ( strcmp(field, "MR20_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR20_B1;
              else if ( strcmp(field, "MR21_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR21_A0;
              else if ( strcmp(field, "MR21_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR21_A1;
              else if ( strcmp(field, "MR21_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR21_B0;
              else if ( strcmp(field, "MR21_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR21_B1;
              else if ( strcmp(field, "MR22_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR22_A0;
              else if ( strcmp(field, "MR22_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR22_A1;
              else if ( strcmp(field, "MR22_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR22_B0;
              else if ( strcmp(field, "MR22_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR22_B1;
              else if ( strcmp(field, "MR24_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR24_A0;
              else if ( strcmp(field, "MR24_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR24_A1;
              else if ( strcmp(field, "MR24_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR24_B0;
              else if ( strcmp(field, "MR24_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR24_B1;
              else if ( strcmp(field, "MR25_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR25_A0;
              else if ( strcmp(field, "MR25_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR25_A1;
              else if ( strcmp(field, "MR25_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR25_B0;
              else if ( strcmp(field, "MR25_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR25_B1;
              else if ( strcmp(field, "MR26_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR26_A0;
              else if ( strcmp(field, "MR26_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR26_A1;
              else if ( strcmp(field, "MR26_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR26_B0;
              else if ( strcmp(field, "MR26_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR26_B1;
              else if ( strcmp(field, "MR27_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR27_A0;
              else if ( strcmp(field, "MR27_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR27_A1;
              else if ( strcmp(field, "MR27_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR27_B0;
              else if ( strcmp(field, "MR27_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR27_B1;
              else if ( strcmp(field, "MR28_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR28_A0;
              else if ( strcmp(field, "MR28_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR28_A1;
              else if ( strcmp(field, "MR28_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR28_B0;
              else if ( strcmp(field, "MR28_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR28_B1;
              else if ( strcmp(field, "MR30_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR30_A0;
              else if ( strcmp(field, "MR30_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR30_A1;
              else if ( strcmp(field, "MR30_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR30_B0;
              else if ( strcmp(field, "MR30_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR30_B1;
              else if ( strcmp(field, "MR31_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR31_A0;
              else if ( strcmp(field, "MR31_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR31_A1;
              else if ( strcmp(field, "MR31_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR31_B0;
              else if ( strcmp(field, "MR31_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR31_B1;
              else if ( strcmp(field, "MR32_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR32_A0;
              else if ( strcmp(field, "MR32_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR32_A1;
              else if ( strcmp(field, "MR32_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR32_B0;
              else if ( strcmp(field, "MR32_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR32_B1;
              else if ( strcmp(field, "MR33_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR33_A0;
              else if ( strcmp(field, "MR33_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR33_A1;
              else if ( strcmp(field, "MR33_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR33_B0;
              else if ( strcmp(field, "MR33_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR33_B1;
              else if ( strcmp(field, "MR34_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR34_A0;
              else if ( strcmp(field, "MR34_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR34_A1;
              else if ( strcmp(field, "MR34_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR34_B0;
              else if ( strcmp(field, "MR34_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR34_B1;
              else if ( strcmp(field, "MR37_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR37_A0;
              else if ( strcmp(field, "MR37_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR37_A1;
              else if ( strcmp(field, "MR37_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR37_B0;
              else if ( strcmp(field, "MR37_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR37_B1;
              else if ( strcmp(field, "MR40_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR40_A0;
              else if ( strcmp(field, "MR40_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR40_A1;
              else if ( strcmp(field, "MR40_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR40_B0;
              else if ( strcmp(field, "MR40_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR40_B1;
              else if ( strcmp(field, "MR41_A0") == 0)
                return  mb_LPDDR5_2D[ps].MR41_A0;
              else if ( strcmp(field, "MR41_A1") == 0)
                return  mb_LPDDR5_2D[ps].MR41_A1;
              else if ( strcmp(field, "MR41_B0") == 0)
                return  mb_LPDDR5_2D[ps].MR41_B0;
              else if ( strcmp(field, "MR41_B1") == 0)
                return  mb_LPDDR5_2D[ps].MR41_B1;
              else if ( strcmp(field, "Disable2D") == 0)
                return  mb_LPDDR5_2D[ps].Disable2D;
              else if ( strcmp(field, "VrefSamples") == 0)
                return  mb_LPDDR5_2D[ps].VrefSamples;
              else if ( strcmp(field, "RdWrPatternA") == 0)
                return  mb_LPDDR5_2D[ps].RdWrPatternA;
              else if ( strcmp(field, "RdWrPatternB") == 0)
                return  mb_LPDDR5_2D[ps].RdWrPatternB;
              else if ( strcmp(field, "RdWrInvertA") == 0)
                return  mb_LPDDR5_2D[ps].RdWrInvertA;
              else if ( strcmp(field, "RdWrInvertB") == 0)
                return  mb_LPDDR5_2D[ps].RdWrInvertB;
      }
      else {
          dwc_ddrphy_phyinit_assert(0,"%s invalid value for Train2D=%d\n", printf_header, Train2D);
          return -3;
      }

      return 0;
}
/** @} */
