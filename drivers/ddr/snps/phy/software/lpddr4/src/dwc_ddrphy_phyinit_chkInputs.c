/** \file 
 * \brief calculates messageBlock header based on user_input_basic and user_input_advanced.
 */

#include <stdlib.h>
#include "dwc_ddrphy_phyinit.h"

/**
 *  \addtogroup SrcFunc
 *  @{
 */


/** \brief check's users invalid programming.
 * 
 * This function does some general checking on user configuration for invalid combinations of 
 * settings.
 * 
 * \return void
 */
void dwc_ddrphy_phyinit_chkInputs (phyinit_config_t* phyctx)
  {
    char *printf_header;
    printf_header = "//[dwc_ddrphy_phyinit_chkInputs]";
    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;

    uint8_t pstate;
    for (pstate=0; pstate<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE && pUserInputBasic->NumPStates>2 && pstate < DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; pstate++)
      {
        if (pUserInputBasic->DfiFreqRatio[pstate] != 2 && pstate<7)
            dwc_ddrphy_phyinit_assert(0,"%s DfiFreqRatio[%d]=%d. Pstates < 7 must have DfiFreqRatio=2.\n", printf_header, pstate, pUserInputBasic->DfiFreqRatio[pstate]);

        if (pUserInputBasic->DfiFreqRatio[pstate] != 1 && pstate>=7)
            dwc_ddrphy_phyinit_assert(0,"%s DfiFreqRatio[%d]=%d. 7 <= Pstates < 14 must have DfiFreqRatio=1.\n", printf_header, pstate, pUserInputBasic->DfiFreqRatio[pstate]);
      }
    //for (pstate=7; pstate<14 && pstate < DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE && pUserInputBasic->NumPStates>2; pstate++)
    //  {
    //    if (pUserInputBasic->PllBypass[pstate] != pUserInputBasic->PllBypass[pstate-7])
    //        dwc_ddrphy_phyinit_assert(0,"%s pUserInputBasic->PllBypass[%d] != pUserInputBasic->PllBypass[%d]. Sister PStates must have the same PllBypass Setting.\n", printf_header, pstate,pstate-7);
    //  }
    uint16_t val = pUserInputBasic->CfgPStates;
    uint16_t count=0;
    for (pstate=0; pstate<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; pstate++)
      {
        count += (val&0x1) ? 1:0;
        val = val >> 1;
      }
    if ( count != pUserInputBasic->NumPStates) 
    dwc_ddrphy_phyinit_assert(0,"%s count of 1's in CfgPState(=%d) must match NumPStates(=%d) .\n", printf_header,count,pUserInputBasic->NumPStates);

    uint8_t skip_train = (pRuntimeConfig->initCtrl & 0x02) >> 1;
    uint8_t skip_imem  = (pRuntimeConfig->initCtrl & 0x04) >> 2;
    uint8_t skip_dmem  = (pRuntimeConfig->initCtrl & 0x08) >> 3;
    if (skip_train && ((!skip_imem) || (!skip_dmem)))
      {
        dwc_ddrphy_phyinit_assert(1,"%s  if skip_train ==1 then its optimal to set skip_imem and skip_dmem\n", printf_header);
      }
    
  }
/** @} */
