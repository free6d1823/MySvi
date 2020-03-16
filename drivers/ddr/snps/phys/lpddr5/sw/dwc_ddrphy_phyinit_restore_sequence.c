/** \file
 *  \addtogroup SrcFunc
 *  @{
 */

#include "dwc_ddrphy_phyinit.h"

/** \brief This function implements the register restore portion of S3/IO
 * retention sequence.
 *
 * \note This function requires the runtime_config.Reten=1 to enable PhyInit exit retention feature.  This variable can be set as in 
 * \returns 0 on completion of the sequence, EXIT_FAILURE on error.
 */
int dwc_ddrphy_phyinit_restore_sequence (phyinit_config_t* phyctx) {

  runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
  user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;

  char *printf_header;
  printf_header = "[dwc_ddrphy_phyinit_restore_sequence]";
  

  if (!pRuntimeConfig->RetEn)
    {
      dwc_ddrphy_phyinit_assert(0,"%s retention restore sequence function is called but register save process was not executed during initialization sequence (pRuntimeConfig->RetEn != 0)\n",printf_header);
    }

 
  dwc_ddrphy_phyinit_cmnt("%s Start of dwc_ddrphy_phyinit_restore_sequence",printf_header);
  
  ///   Before you call this functions perform the following:
  ///  --------------------------------------------------------------------------
  ///  -# Bring up VDD, VDDQ should already be up
  ///  -# Since the CKE* and MEMRESET pin state must be protected, special care 
  ///    must be taken to ensure that the following signals
  ///     - atpg_mode = 1'b0
  ///     - PwrOkIn = 1'b0
  /// 
  ///  -# The {BypassModeEn*, WRSTN} signals may be defined at VDD power-on, but 
  ///    must be driven to ZERO at least 10ns prior to the asserting edge of 
  ///    PwrOkIn.
  ///   
  ///  -# Start Clocks and Reset the PHY 
  ///    This step is identical to dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy() 
  ///  
  dwc_ddrphy_phyinit_cmnt("\n");
  dwc_ddrphy_phyinit_cmnt("   Before you call this functions perform the following:\n");
  dwc_ddrphy_phyinit_cmnt("  --------------------------------------------------------------------------\n");
  dwc_ddrphy_phyinit_cmnt("  -# Bring up VDD, VDDQ should already be up\n");
  dwc_ddrphy_phyinit_cmnt("  -# Since the CKE* and MEMRESET pin state must be protected, special care \n");
  dwc_ddrphy_phyinit_cmnt("    must be taken to ensure that the following signals\n");
  dwc_ddrphy_phyinit_cmnt("     - atpg_mode = 1'b0\n");
  dwc_ddrphy_phyinit_cmnt("     - PwrOkIn = 1'b0\n");
  dwc_ddrphy_phyinit_cmnt(" \n");
  dwc_ddrphy_phyinit_cmnt("  -# The {BypassModeEn*, WRSTN} signals may be defined at VDD power-on, but \n");
  dwc_ddrphy_phyinit_cmnt("    must be driven to ZERO at least 10ns prior to the asserting edge of \n");
  dwc_ddrphy_phyinit_cmnt("    PwrOkIn.\n");
  dwc_ddrphy_phyinit_cmnt("   \n");
  dwc_ddrphy_phyinit_cmnt("  -# Start Clocks and Reset the PHY \n");
  dwc_ddrphy_phyinit_cmnt("    This step is identical to dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy() \n");
  dwc_ddrphy_phyinit_cmnt("  ");

  /// This function performs the following in sequence
  /// --------------------------------------------------------------------------

  /// -# Write the MicroContMuxSel CSR to 0x0 to allow access to the internal CSRs
  dwc_ddrphy_phyinit_cmnt("%s Write the MicroContMuxSel CSR to 0x0 to allow access to the internal CSRs\n",printf_header);
  dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x0);

  /// -# Write the UcclkHclkEnables CSR to enable all the clocks so the reads can complete
  uint16_t pmuClkEnables = csr_HclkEn_MASK | csr_UcclkEn_MASK;
  if (pUserInputAdvanced->PmuClockDiv == 0) {
    pmuClkEnables |= (uint16_t)csr_UcclkFull_MASK;
  }
  dwc_ddrphy_phyinit_cmnt("%s Write the UcclkHclkEnables CSR to 0x%x to enable all the clocks so the reads can complete\n",printf_header,pmuClkEnables);
  dwc_ddrphy_phyinit_userCustom_io_write16((tDRTUB | csr_UcclkHclkEnables_ADDR), pmuClkEnables);

  /// -# Assert ZCalReset to force impedance calibration FSM to idle.
  ///    de-asserted as part of dfi_init_start/complete handshake 
  ///    by the PIE when DfiClk is valid.
  dwc_ddrphy_phyinit_userCustom_io_write16((tMASTER | csr_ZCalReset_ADDR), 0x1);

  /// -# Issue register writes to restore registers values.
  dwc_ddrphy_phyinit_cmnt(" Issue register writes to restore registers values.\n"); 
  dwc_ddrphy_phyinit_cmnt(" --------------------------------------------------\n"); 
  dwc_ddrphy_phyinit_cmnt(" - IMPORTANT - \n"); 
  dwc_ddrphy_phyinit_cmnt(" - The register values printed in this txt file are always 0x0. The \n"); 
  dwc_ddrphy_phyinit_cmnt(" - user must replace them with actual registers values from the save sequence. The \n"); 
  dwc_ddrphy_phyinit_cmnt(" - save sequence can be found in the output.txt file associated with the particular init sequence.\n");
  dwc_ddrphy_phyinit_cmnt(" - The save sequence issues APB read commands to read and save register values.\n"); 
  dwc_ddrphy_phyinit_cmnt(" - refer to the init sequence output file for details.\n"); 
  dwc_ddrphy_phyinit_cmnt(" --------------------------------------------------------------------------------\n"); 
  dwc_ddrphy_phyinit_regInterface(restoreRegs,0,0);

  /// -# Write the UcclkHclkEnables CSR to disable the appropriate clocks after all reads done.
  dwc_ddrphy_phyinit_cmnt("%s Write the UcclkHclkEnables CSR to disable the appropriate clocks after all reads done.\n",printf_header);
  dwc_ddrphy_phyinit_cmnt ("Disabling Ucclk (PMU)\n");
  dwc_ddrphy_phyinit_userCustom_io_write16((tDRTUB | csr_UcclkHclkEnables_ADDR), csr_HclkEn_MASK);

  /// -# Write the MicroContMuxSel CSR to 0x1 to isolate the internal CSRs during mission mode
  dwc_ddrphy_phyinit_cmnt ("%s Write the MicroContMuxSel CSR to 0x1 to isolate the internal CSRs during mission mode\n",printf_header);
  dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x1);
  
  ///  After Function Call 
  ///  --------------------------------------------------------------------------
  ///  To complete the Retention Exit sequence:
  /// 
  ///  -# Initialize the PHY to Mission Mode through DFI Initialization
  ///    You may use the same sequence implemented in
  ///    dwc_ddrphy_phyinit_userCustom_J_enterMissionMode()
  ///  
  dwc_ddrphy_phyinit_cmnt("\n");
  dwc_ddrphy_phyinit_cmnt("  After Function Call \n");
  dwc_ddrphy_phyinit_cmnt("  --------------------------------------------------------------------------\n");
  dwc_ddrphy_phyinit_cmnt("  To complete the Retention Exit sequence:\n");
  dwc_ddrphy_phyinit_cmnt(" \n");
  dwc_ddrphy_phyinit_cmnt("  -# Initialize the PHY to Mission Mode through DFI Initialization\n");
  dwc_ddrphy_phyinit_cmnt("    You may use the same sequence implemented in\n");
  dwc_ddrphy_phyinit_cmnt("    dwc_ddrphy_phyinit_userCustom_J_enterMissionMode()\n");
  dwc_ddrphy_phyinit_cmnt("  \n");
  dwc_ddrphy_phyinit_cmnt("%s End of dwc_ddrphy_phyinit_restore_sequence\n",printf_header);
  return 0;
}
/** @} */
