/** \file
 *  \addtogroup SrcFunc
 *  @{
 */
#include "dwc_ddrphy_phyinit.h"

/** \brief this function implements the flow of PhyInit software to initialize the PHY.
 *
 * The execution sequence follows the overview figure provided in the PhyInit App Note.
 *
 * \returns 0 on completion of the sequence, EXIT_FAILURE on error.
 * \callgraph
 */
int dwc_ddrphy_phyinit_sequence(phyinit_config_t* phyctx) {

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    int debug = pRuntimeConfig->debug;

    int pstate;
    int prevPState;
    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_sequence]";

    dwc_ddrphy_phyinit_cmnt("%s Start of dwc_ddrphy_phyinit_sequence()\n", printf_header);
    // registering function inputs
    //pRuntimeConfig->curIMEM    = 0xffff; // Reset state of IMEM in PhyInit
    pRuntimeConfig->curPState  = 0; // Reset state of IMEM in PhyInit

    // Initialize structures
    dwc_ddrphy_phyinit_initStruct(phyctx);

    // Enter user input
    dwc_ddrphy_phyinit_setDefault(phyctx);

    // User-editable function to override any user input set in dwc_ddrphy_phyinit_enterUserInput()
    dwc_ddrphy_phyinit_userCustom_overrideUserInput(phyctx);

    // Re-calculate Firmware Message Block input based on final user input
    dwc_ddrphy_phyinit_calcMb(phyctx);

    // check basic inputs
    dwc_ddrphy_phyinit_chkInputs(phyctx);

    // Printing values of user input
    if (debug != 0)
        dwc_ddrphy_phyinit_print_dat(phyctx);

    // (A) Bring up VDD, VDDQ, and VAA
    dwc_ddrphy_phyinit_userCustom_A_bringupPower();

    // (B) Start Clocks and Reset the PHY
    dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy();

    // (C) Initialize PHY Configuration
    dwc_ddrphy_phyinit_C_initPhyConfig (phyctx);

    // Customize any register write desired; This can include any CSR not covered by PhyInit or if
    // user wish to override values calculated in step C
    dwc_ddrphy_phyinit_userCustom_customPreTrain (phyctx);

    // Stop retention register tracking for training firmware related registers
    // Pstate Loop registers will be tracked in DMA
    dwc_ddrphy_phyinit_regInterface(stopTrack,0,0);

    dwc_ddrphy_phyinit_cmnt("%s initCtrl = %d\n", printf_header, pRuntimeConfig->initCtrl );
    // Load Training Firmware image
    uint8_t skip_imem = (pRuntimeConfig->initCtrl & 0x04) >> 2;
    if (!skip_imem)
      {
        dwc_ddrphy_phyinit_D_loadIMEM(phyctx);
      }

    // Train all Pstates except FirstPstate.
    prevPState = pRuntimeConfig->curPState;
    for (pstate=0; pstate<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; pstate++)
      {
        if (pstate == pUserInputBasic->FirstPState) continue;
        else if ((pUserInputBasic->CfgPStates & (0x1<<pstate)) == 0) continue;
        else {
          pRuntimeConfig->curPState = pstate;
          dwc_ddrphy_phyinit_sequencePsLoop(phyctx);
        }
      } // pstate

    // Train First PState last.
    dwc_ddrphy_phyinit_cmnt ("%s Training first mission mode PState\n", printf_header);
    pRuntimeConfig->curPState = pUserInputBasic->FirstPState;
    dwc_ddrphy_phyinit_sequencePsLoop(phyctx);
    pRuntimeConfig->curPState = prevPState;

    // Start retention register tracking for training firmware related registers
    dwc_ddrphy_phyinit_regInterface(startTrack,0,0);

    // (I) Load PHY Init Engine Image / non-Pstate
    dwc_ddrphy_phyinit_I_loadPIEImage(phyctx);

    // Customize any CSR write desired to override values programmed by firmware or dwc_ddrphy_phyinit_I_loadPIEImage()
    // Non-Pstate only.
    dwc_ddrphy_phyinit_userCustom_customPostTrain (phyctx);

    if (pRuntimeConfig->RetEn)
      {
        // Save value of tracked registers for retention restore sequence.
        dwc_ddrphy_phyinit_userCustom_saveRetRegs(phyctx);
      }

#ifdef DWC_DDRPHY_PHYINIT_PS_SRAM_CHKR
    // Check ps sram content if > 2 PStates are used.
    if (pUserInputBasic->NumPStates >2) dwc_ddrphy_phyinit_check_ps_sram();
#endif
    // (J) Initialize the PHY to Mission Mode through DFI Initialization
    dwc_ddrphy_phyinit_userCustom_J_enterMissionMode();


    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_sequence()\n", printf_header);

    return 0;
}

/** \brief this function implements the PState Loop portion of initialization sequence.
 *
 * \returns void
 * \callgraph
 */
void dwc_ddrphy_phyinit_sequencePsLoop(phyinit_config_t* phyctx)
  {
    //user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    uint8_t pstate = pRuntimeConfig->curPState;

    PMU_SMB_LPDDR4_1D_t* mb1D = phyctx->mb_LPDDR4_1D;

    //char *printf_header;
    //printf_header = " [dwc_ddrphy_phyinit_sequencePsLoop]";

    uint8_t prog_csr      = (pRuntimeConfig->initCtrl & 0x01) >> 0;
    uint8_t skip_fw       = (pRuntimeConfig->initCtrl & 0x02) >> 1;
    //uint8_t skip_imem     = (pRuntimeConfig->initCtrl & 0x04) >> 2;
    //uint8_t skip_dmem     = (pRuntimeConfig->initCtrl & 0x08) >> 3;
    uint8_t devinit       = (pRuntimeConfig->initCtrl & 0x20) >> 5;

    // Indicate the start of the Pstate Loop to register interface
    dwc_ddrphy_phyinit_regInterface(startPsLoop,0,0);

    // Pstatable Step C
    dwc_ddrphy_phyinit_C_initPhyConfigPsLoop(phyctx);

    // customPre Pstatable
    dwc_ddrphy_phyinit_userCustom_customPreTrainPsLoop(phyctx, pstate);

    if (prog_csr)
      {
        dwc_ddrphy_phyinit_regInterface(stopPsLoop,0,0);

        // Skip running training firmware entirely
        dwc_ddrphy_phyinit_progCsrSkipTrain(phyctx);

        // set Register group to 3 for Firmware trained results.
        dwc_ddrphy_phyinit_regInterface(resumePsLoop,0,0);
        dwc_ddrphy_phyinit_regInterface(setGroup,0,3);

        // Skip running training firmware entirely
        dwc_ddrphy_phyinit_progCsrSkipTrainPsLoop(phyctx);

        // 2D execution should be turned off since progSkipTrain will do the programming
        pRuntimeConfig->Train2D = 0;

        // revert to group 2 for the rest of registers
        dwc_ddrphy_phyinit_regInterface(setGroup,0,2);
      }

    // Training firmware will populate the DMA on its own
    dwc_ddrphy_phyinit_regInterface(stopPsLoop,0,0);

    if (devinit)
      {
        // Only execute training firmware to initialize the DRAM and
        // skip all training steps.
        pRuntimeConfig->curD = 0;
        // Set sequence Ctrl to 0x1 to only do device initialization.
        mb1D[pstate].SequenceCtrl = 0x1;
      }

    if (!skip_fw)
      {
       
        pRuntimeConfig->curD = 0; // 1D

        // (E) Set the PHY input clocks to the desired frequency
        dwc_ddrphy_phyinit_userCustom_E_setDfiClk( pstate );
        // Note: this routine implies other items such as DfiFreqRatio, DfiCtlClk are also set properly.
        // Because the clocks are controlled in the SOC, external to the software and PHY, this step intended to be
        // replaced by the user with the necessary SOC operations to achieve the new input frequency to the PHY.

        // (F) Write the Message Block parameters for the training firmware
        dwc_ddrphy_phyinit_F_loadDMEM(phyctx);

        // (G) Execute the Training Firmware
        dwc_ddrphy_phyinit_G_execFW();

        // (H) Read the Message Block results
        dwc_ddrphy_phyinit_H_readMsgBlock(0);

       // Now optionally perform 2D training for protocols that allow it
       if (pRuntimeConfig->Train2D == 1)
         {
           pRuntimeConfig->curD = 1; // 2D

           // 2D-F, cont.  Write the Message Block parameters for the training firmware
           dwc_ddrphy_phyinit_F_loadDMEM(phyctx);

           // 2D-G Execute the Training Firmware
           dwc_ddrphy_phyinit_G_execFW();

           // 2D-H Read the Message Block results
           dwc_ddrphy_phyinit_H_readMsgBlock(1);
         } // 2D
      } // ! skipfw
    else
      {
        // @todo: function entry point for customer to do backdoor DRAM init.
      }

    //dwc_ddrphy_phyinit_cmnt(" debug 1\n" );

    dwc_ddrphy_phyinit_regInterface(resumePsLoop,0,0);

    //printf("End of fw Exec \n");
    // (I) Load PHY Init Engine Image / Pstate
    dwc_ddrphy_phyinit_I_loadPIEImagePsLoop(phyctx);

    // custom post pstate
    dwc_ddrphy_phyinit_userCustom_customPostTrainPsLoop(phyctx, pstate);

    // DMA Copy
    dwc_ddrphy_phyinit_regInterface(endPsLoop,0,0);
  }
/** @} */
