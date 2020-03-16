/** \file
 * \brief calculates messageBlock header based on user_input_basic and user_input_advanced.
 */

#include <stdlib.h>
#include "dwc_ddrphy_phyinit.h"

/**
 *  \addtogroup SrcFunc
 *  @{
 */

/** \brief reads PhyInit inputs structures and sets relevant message bloc
 * parameters.
 *
 * This function sets Message Block parameters based on user_input_basic and
 * user_input_advanced. Parameters are only set if not programed by
 * dwc_ddrphy_phyinit_userCustom_overrideUserInput() or
 * dwc_ddrphy_phyinit_setDefault(). user changes in these files takes precedence
 * over this function call.
 *
 * MessageBlock fields set ::
 *
 *  - DramType
 *  - Pstate
 *  - DRAMFreq
 *  - PllBypassEn
 *  - DfiFreqRatio
 *  - PhyOdtImpedance
 *  - PhyDrvImpedance
 *  - BPZNResVal
 *
 * \return void
 */
void dwc_ddrphy_phyinit_calcMb (phyinit_config_t* phyctx) {

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    pUserInputAdvanced = pUserInputAdvanced; // to avoid warning in case it would not be used
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    int Train2D = pRuntimeConfig->Train2D;

    PMU_SMB_LPDDR5_1D_t* mb1D = phyctx->mb_LPDDR5_1D;
    PMU_SMB_LPDDR5_2D_t* mb2D = phyctx->mb_LPDDR5_2D;

    char *printf_header;
    printf_header = "[dwc_ddrphy_phyinit_calcMb]";

    dwc_ddrphy_phyinit_cmnt("%s Start of dwc_ddrphy_phyinit_calcMb()\n", printf_header);

    if (pUserInputBasic->NumPStates == 2) pUserInputBasic->CfgPStates = 0x3;
    int NumCh =  pUserInputBasic->NumCh;
    int NumDbyte = NumCh * pUserInputBasic->NumDbytesPerCh ;
    int nad0 = pUserInputBasic->NumActiveDbyteDfi0;
    int nad1 = pUserInputBasic->NumActiveDbyteDfi1;

    // a few checks to make sure valid programing.
    if ( nad0 < 0 || nad1 < 0 || (nad0 + nad1 <= 0) || (nad0 == 0 && NumCh == 1) || NumDbyte <= 0) {
      dwc_ddrphy_phyinit_assert(0,"%s NumActiveDbyteDfi0, NumActiveDbyteDfi0, NumByte out of range.\n",printf_header);
      }

    if ( (nad0 + nad1) > NumDbyte) {
      dwc_ddrphy_phyinit_assert(0,"%s NumActiveDbyteDfi0+NumActiveDbyteDfi1 is larger than NumDbyteDfi0\n",printf_header);
      }

    if (NumCh==1 && nad1 != 0) {
      dwc_ddrphy_phyinit_assert(0,"%s NumCh==1 but NumActiveDbyteDfi1 != 0\n",printf_header);
      }

    if (pUserInputBasic->NumRank_dfi1!=0 && pUserInputBasic->NumRank_dfi1 != pUserInputBasic->NumRank_dfi0 ) {
      dwc_ddrphy_phyinit_assert(0,"%s In a two channel system, PHY does not support different number of DQ's across ranks. NumRank_dfi0 must equal NumRank_dfi1 if NumRank_df1 !=0.\n",printf_header);
      }


    uint8_t myps;

    // 1D message block defaults
    pRuntimeConfig->Train2D = 0;
    for (myps=0; myps<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; myps++) {
        if ((pUserInputBasic->CfgPStates & 0x1<<myps) == 0) continue;
      if (pUserInputBasic->DramDataWidth == 8 && mb1D[myps].X8Mode == 0x0) {
        dwc_ddrphy_phyinit_assert(0,"%s LPDDR DramDataWidth == 8 but no X8 devices programmed in mb1D[%d].X8Mode!\n",printf_header,myps);
      }


    //  dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"Pstate",myps);
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"DRAMFreq",pUserInputBasic->Frequency[myps] * (pUserInputBasic->DfiFreqRatio[myps]*2) * 2);
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PllBypassEn",pUserInputBasic->PllBypass[myps]);
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"DfiFreqRatio",(0==pUserInputBasic->DfiFreqRatio[myps]) ? 0x1 : ((1==pUserInputBasic->DfiFreqRatio[myps]) ? 0x2 : 0x4));
    if (pUserInputBasic->HardMacroVer == 4 )  { //HardMacroE
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyOdtImpedance",0);
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyDrvImpedance",0);
    } else {
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyOdtImpedance",0);
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyDrvImpedance",0);
    }
      dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"BPZNResVal",0);

      //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"EnabledDQsChA",nad0*8);
      //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"CsPresentChA",(2==pUserInputBasic->NumRank_dfi0) ? 0x3 : pUserInputBasic->NumRank_dfi0);
      //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"EnabledDQsChB",nad1*8);
      //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"CsPresentChB",(2==pUserInputBasic->NumRank_dfi1) ? 0x3 : pUserInputBasic->NumRank_dfi1);
      if ((mb1D[myps].EnabledDQsChA == 0 && NumCh == 1) || (mb1D[myps].EnabledDQsChA == 0 && mb1D[myps].EnabledDQsChB == 0 && NumCh == 2))
      dwc_ddrphy_phyinit_assert(0,"%s NumActiveDbyteDfi0, NumActiveDbyteDfi0, NumByte out of range.\n",printf_header);
    } // myps
    pRuntimeConfig->Train2D = Train2D;

    // 2D message block defaults
    pRuntimeConfig->Train2D = 1;
    if (Train2D) {
    for (myps=0; myps<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; myps++) {
        if ((pUserInputBasic->CfgPStates & 0x1<<myps) == 0) continue;
      if (pUserInputBasic->DramDataWidth == 8 && mb2D[myps].X8Mode == 0x0) {
        dwc_ddrphy_phyinit_assert(0,"%s LPDDR DramDataWidth == 8 but no X8 devices programmed in mb2D[%d].X8Mode!\n",printf_header,myps);
      }


    //    dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"Pstate",myps);
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"DRAMFreq",pUserInputBasic->Frequency[myps] * (pUserInputBasic->DfiFreqRatio[myps]*2) * 2);
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PllBypassEn",pUserInputBasic->PllBypass[myps]);
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"DfiFreqRatio",(0==pUserInputBasic->DfiFreqRatio[myps]) ? 0x1 : ((1==pUserInputBasic->DfiFreqRatio[myps]) ? 0x2 : 0x4));
    if (pUserInputBasic->HardMacroVer == 4 )  { //HardMacroE
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyOdtImpedance",0);
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyDrvImpedance",0);
    } else {
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyOdtImpedance",0);
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"PhyDrvImpedance",0);
    }
        dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"BPZNResVal",0);

        //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"EnabledDQsChA",nad0*8);
        //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"CsPresentChA",(2==pUserInputBasic->NumRank_dfi0) ? 0x3 : pUserInputBasic->NumRank_dfi0);
        //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"EnabledDQsChB",nad1*8);
        //dwc_ddrphy_phyinit_softSetMb(phyctx, myps,"CsPresentChB",(2==pUserInputBasic->NumRank_dfi1) ? 0x3 : pUserInputBasic->NumRank_dfi1);
        if ((mb2D[myps].EnabledDQsChA == 0 && NumCh == 1) || (mb2D[myps].EnabledDQsChA == 0 && mb2D[myps].EnabledDQsChB == 0 && NumCh == 2))
        dwc_ddrphy_phyinit_assert(0,"%s NumActiveDbyteDfi0, NumActiveDbyteDfi0, NumByte out of range.\n",printf_header);
      } // myps
    } // Train2D
    pRuntimeConfig->Train2D = Train2D;

    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_calcMb()\n", printf_header);
}
/** @} */
