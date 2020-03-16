/** 
 * \file
 * \brief End of Micro-Controller based Save/Restore function.
 *
 * This file contains the implementation of dwc_ddrphy_phyinit_SR_complete_function
 * function.
 *
 *  \addtogroup SrcFunc
 *  @{
 */
#include "dwc_ddrphy_phyinit.h"

/** \brief End of Micro-Controller based Save/Restore function.
 *
 * This function Halts the Micro Controller, Gate clocks in prepration for
 * mission mode during for the Micro Controller based Save/Restore sequence.
 *
 * \return void
 */
void dwc_ddrphy_phyinit_SR_complete_function(phyinit_config_t* phyctx) {

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
  
   char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_SR_complete_function]";

    dwc_ddrphy_phyinit_cmnt ("\n\n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("// 5.3 Initialize PHY Configuration \n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("// Optional step (SR) - Save Complete\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("// Required PHY registers saved to DMEM for later IO retention exit restore performed by firmware\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n\n");

    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_SR_complete_function()\n", printf_header);

    //##############################################################
    //
    /// To Halt Micro Controller after save operation completed
    // CSRs to program:
    //   MicroReset 
    //
    //##############################################################

    dwc_ddrphy_phyinit_cmnt ("// Halt Micro Controller. \n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroReset_ADDR), 0x1);

    //##############################################################
    //
    // To gain control of the APB bus
    // To gate the micro controller clock and/or training hardware clock accordingly
    // To isolate the APB bus access
    // CSRs to program:
    //   MicroContMuxSel UcclkHclkEnables  
    //
    //##############################################################

    dwc_ddrphy_phyinit_cmnt ("// Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0. \n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x0);

    // For DDR3 and DDR4, gate-off Ucclk and Hclk after training is done
    // LPDDR3 and LPDDR4 will need ACSM for PPT, and thus not gating Hclk (only gates Ucclk)
    if (pUserInputBasic->DramType ==  DDR4 || pUserInputBasic->DramType ==  DDR3) {
        dwc_ddrphy_phyinit_cmnt ("// Disabling Ucclk (PMU) and Hclk (training hardware)\n");
        dwc_ddrphy_phyinit_userCustom_io_write16((tDRTUB | csr_UcclkHclkEnables_ADDR), 0x0);
    } else {
        dwc_ddrphy_phyinit_cmnt ("// Disabling Ucclk (PMU)\n");
        dwc_ddrphy_phyinit_userCustom_io_write16((tDRTUB | csr_UcclkHclkEnables_ADDR), csr_HclkEn_MASK);
    }
    
    dwc_ddrphy_phyinit_cmnt ("// Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. \n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x1);


//##############################################################
//##############################################################
    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_SR_complete_function()\n", printf_header);
}
// End of dwc_ddrphy_phyinit_SR_complete_function()
/** @} */
