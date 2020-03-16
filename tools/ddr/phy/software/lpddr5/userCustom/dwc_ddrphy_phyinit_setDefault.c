
/** \file
 * \brief used to set PhyInit inputs statically by the user
 */
#include <string.h>
#include "dwc_ddrphy_phyinit.h"

/**
 *  \addtogroup CustFunc
 *  @{
 */

/** @brief  This function provides a default configuration of PHY.
 *
 * This function provides a default configuration of PHY. To change the default
 * configuration, the user can edit this file directly or use the
 * dwc_ddrphy_phyinit_userCustom_overrideUserInput() function. The default
 * values selected below only represent a general case and may not be correct
 * for every use case.
 *
 * @return Void
 */
void dwc_ddrphy_phyinit_setDefault (phyinit_config_t* phyctx  /**< phyctx phyinit context */) {

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    user_input_sim_t* pUserInputSim = &phyctx->userInputSim;

    PMU_SMB_LPDDR5_1D_t* mb1D = phyctx->mb_LPDDR5_1D;
    PMU_SMB_LPDDR5_2D_t* mb2D = phyctx->mb_LPDDR5_2D;

    char *printf_header;
    printf_header = "// [dwc_ddrphy_phyinit_setDefault]";

    dwc_ddrphy_phyinit_print ("%s Start of dwc_ddrphy_phyinit_setDefault()\n", printf_header);


    // ##############################################################
    // userInputBasic - Basic Inputs the user must provide values
    // for detailed descriptions of each field see src/dwc_ddrphy_phyinit_struct.h
    // ##############################################################
    pUserInputBasic->DramType                 = LPDDR5;
    pUserInputBasic->DimmType                 = UDIMM;
    pUserInputBasic->HardMacroVer             = 3; //default: HardMacro family D

    pUserInputBasic->NumDbytesPerCh           = 0x0002;
    pUserInputBasic->NumCh                    = 0x0002;
    pUserInputBasic->NumRank                  = 0x0001;
    pUserInputBasic->NumActiveDbyteDfi0       = 0x0002;
    pUserInputBasic->NumActiveDbyteDfi1       = 0x0002;
    pUserInputBasic->NumRank_dfi0             = 0x0001; // 2 ranks each controlled by dfi0 and dfi1 correspondingly.
    pUserInputBasic->NumRank_dfi1             = 0x0001; //
    pUserInputBasic->NumPStates               = 0x0001; // 1 Pstate
    pUserInputBasic->CfgPStates               = 0x0001; // 1 Pstate
    pUserInputBasic->FirstPState              = 0x0000;
    pUserInputBasic->DramDataWidth            = 0x0010; //x16
    pUserInputBasic->MaxNumZQ                 = 0x0004;

    pUserInputBasic->Frequency[0]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[0]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[0]      = 0x2;
    pUserInputBasic->Frequency[1]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[1]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[1]      = 0x2;
    pUserInputBasic->Frequency[2]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[2]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[2]      = 0x2;
    pUserInputBasic->Frequency[3]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[3]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[3]      = 0x2;
    pUserInputBasic->Frequency[4]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[4]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[4]      = 0x2;
    pUserInputBasic->Frequency[5]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[5]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[5]      = 0x2;
    pUserInputBasic->Frequency[6]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[6]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[6]      = 0x2;
    pUserInputBasic->Frequency[7]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[7]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[7]      = 0x1;
    pUserInputBasic->Frequency[8]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[8]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[8]      = 0x1;
    pUserInputBasic->Frequency[9]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[9]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[9]      = 0x1;
    pUserInputBasic->Frequency[10]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[10]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[10]      = 0x1;
    pUserInputBasic->Frequency[11]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[11]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[11]      = 0x1;
    pUserInputBasic->Frequency[12]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[12]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[12]      = 0x1;
    pUserInputBasic->Frequency[13]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[13]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[13]      = 0x1;
    pUserInputBasic->Frequency[14]         = 400; // 3200Mbps
    pUserInputBasic->PllBypass[14]         = 0x0000;
    pUserInputBasic->DfiFreqRatio[14]      = 0x1;


    // ##############################################################
    // userInputAdvnaced (Optional)
    // Default values will be used if no input provided
    // ##############################################################

    pUserInputAdvanced->PsDmaRamSize            = 2;

    pUserInputAdvanced->DramByteSwap            = 0x0;
    pUserInputAdvanced->ExtCalResVal            = 120; // 120 Ohm

    // Pstate 0 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[0]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[0]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[0]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[0]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[0]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[0]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[0]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[0]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[0]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[0]        = 0x0;
    pUserInputAdvanced->CkDisVal[0]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[0]        = 30;
    pUserInputAdvanced->TxImpedanceAc[0]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[0]       = 30;
    pUserInputAdvanced->TxImpedanceCk[0]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[0]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[0]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[0]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[0]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[0]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[0]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[0]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[0]       = 30;

    // Pstate 1 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[1]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[1]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[1]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[1]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[1]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[1]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[1]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[1]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[1]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[1]        = 0x0;
    pUserInputAdvanced->CkDisVal[1]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[1]        = 30;
    pUserInputAdvanced->TxImpedanceAc[1]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[1]       = 30;
    pUserInputAdvanced->TxImpedanceCk[1]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[1]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[1]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[1]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[1]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[1]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[1]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[1]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[1]       = 30;

    // Pstate 2 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[2]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[2]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[2]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[2]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[2]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[2]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[2]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[2]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[2]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[2]        = 0x0;
    pUserInputAdvanced->CkDisVal[2]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[2]        = 30;
    pUserInputAdvanced->TxImpedanceAc[2]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[2]       = 30;
    pUserInputAdvanced->TxImpedanceCk[2]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[2]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[2]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[2]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[2]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[2]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[2]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[2]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[2]       = 30;

    // Pstate 3 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[3]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[3]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[3]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[3]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[3]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[3]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[3]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[3]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[3]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[3]        = 0x0;
    pUserInputAdvanced->CkDisVal[3]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[3]        = 30;
    pUserInputAdvanced->TxImpedanceAc[3]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[3]       = 30;
    pUserInputAdvanced->TxImpedanceCk[3]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[3]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[3]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[3]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[3]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[3]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[3]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[3]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[3]       = 30;

    // Pstate 4 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[4]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[4]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[4]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[4]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[4]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[4]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[4]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[4]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[4]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[4]        = 0x0;
    pUserInputAdvanced->CkDisVal[4]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[4]        = 30;
    pUserInputAdvanced->TxImpedanceAc[4]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[4]       = 30;
    pUserInputAdvanced->TxImpedanceCk[4]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[4]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[4]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[4]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[4]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[4]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[4]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[4]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[4]       = 30;

    // Pstate 5 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[5]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[5]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[5]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[5]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[5]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[5]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[5]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[5]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[5]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[5]        = 0x0;
    pUserInputAdvanced->CkDisVal[5]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[5]        = 30;
    pUserInputAdvanced->TxImpedanceAc[5]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[5]       = 30;
    pUserInputAdvanced->TxImpedanceCk[5]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[5]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[5]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[5]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[5]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[5]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[5]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[5]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[5]       = 30;

    // Pstate 6 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[6]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[6]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[6]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[6]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[6]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[6]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[6]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[6]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[6]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[6]        = 0x0;
    pUserInputAdvanced->CkDisVal[6]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[6]        = 30;
    pUserInputAdvanced->TxImpedanceAc[6]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[6]       = 30;
    pUserInputAdvanced->TxImpedanceCk[6]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[6]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[6]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[6]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[6]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[6]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[6]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[6]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[6]       = 30;

    // Pstate 7 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[7]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[7]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[7]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[7]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[7]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[7]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[7]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[7]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[7]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[7]        = 0x0;
    pUserInputAdvanced->CkDisVal[7]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[7]        = 30;
    pUserInputAdvanced->TxImpedanceAc[7]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[7]       = 30;
    pUserInputAdvanced->TxImpedanceCk[7]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[7]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[7]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[7]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[7]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[7]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[7]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[7]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[7]       = 30;

    // Pstate 8 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[8]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[8]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[8]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[8]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[8]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[8]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[8]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[8]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[8]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[8]        = 0x0;
    pUserInputAdvanced->CkDisVal[8]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[8]        = 30;
    pUserInputAdvanced->TxImpedanceAc[8]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[8]       = 30;
    pUserInputAdvanced->TxImpedanceCk[8]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[8]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[8]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[8]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[8]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[8]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[8]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[8]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[8]       = 30;

    // Pstate 9 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[9]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[9]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[9]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[9]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[9]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[9]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[9]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[9]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[9]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[9]        = 0x0;
    pUserInputAdvanced->CkDisVal[9]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[9]        = 30;
    pUserInputAdvanced->TxImpedanceAc[9]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[9]       = 30;
    pUserInputAdvanced->TxImpedanceCk[9]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[9]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[9]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[9]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[9]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[9]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[9]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[9]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[9]       = 30;

    // Pstate 10 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[10]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[10]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[10]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[10]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[10]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[10]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[10]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[10]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[10]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[10]        = 0x0;
    pUserInputAdvanced->CkDisVal[10]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[10]        = 30;
    pUserInputAdvanced->TxImpedanceAc[10]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[10]       = 30;
    pUserInputAdvanced->TxImpedanceCk[10]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[10]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[10]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[10]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[10]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[10]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[10]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[10]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[10]       = 30;

    // Pstate 11 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[11]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[11]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[11]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[11]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[11]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[11]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[11]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[11]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[11]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[11]        = 0x0;
    pUserInputAdvanced->CkDisVal[11]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[11]        = 30;
    pUserInputAdvanced->TxImpedanceAc[11]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[11]       = 30;
    pUserInputAdvanced->TxImpedanceCk[11]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[11]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[11]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[11]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[11]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[11]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[11]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[11]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[11]       = 30;

    // Pstate 12 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[12]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[12]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[12]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[12]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[12]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[12]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[12]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[12]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[12]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[12]        = 0x0;
    pUserInputAdvanced->CkDisVal[12]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[12]        = 30;
    pUserInputAdvanced->TxImpedanceAc[12]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[12]       = 30;
    pUserInputAdvanced->TxImpedanceCk[12]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[12]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[12]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[12]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[12]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[12]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[12]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[12]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[12]       = 30;

    // Pstate 13 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[13]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[13]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[13]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[13]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[13]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[13]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[13]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[13]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[13]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[13]        = 0x0;
    pUserInputAdvanced->CkDisVal[13]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[13]        = 30;
    pUserInputAdvanced->TxImpedanceAc[13]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[13]       = 30;
    pUserInputAdvanced->TxImpedanceCk[13]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[13]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[13]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[13]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[13]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[13]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[13]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[13]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[13]       = 30;

    // Pstate 14 - Analog Settings
    pUserInputAdvanced->TxSlewRiseDq[14]         = 0x0;
    pUserInputAdvanced->TxSlewFallDq[14]         = 0x0;
    pUserInputAdvanced->TxSlewRiseDqs[14]        = 0x0;
    pUserInputAdvanced->TxSlewFallDqs[14]        = 0x0;
    pUserInputAdvanced->TxSlewRiseCA[14]         = 0x0;
    pUserInputAdvanced->TxSlewFallCA[14]         = 0x0;
    pUserInputAdvanced->TxSlewRiseCK[14]         = 0x0;
    pUserInputAdvanced->TxSlewFallCK[14]         = 0x0;
    pUserInputAdvanced->TxSlewRiseWCK[14]        = 0x0;
    pUserInputAdvanced->TxSlewFallWCK[14]        = 0x0;
    pUserInputAdvanced->CkDisVal[14]             = 0x0000;
    pUserInputAdvanced->TxImpedanceDq[14]        = 30;
    pUserInputAdvanced->TxImpedanceAc[14]        = 30;
    pUserInputAdvanced->TxImpedanceDqs[14]       = 30;
    pUserInputAdvanced->TxImpedanceCk[14]        = 30;
    pUserInputAdvanced->TxImpedanceCKE[14]       = 50;
    pUserInputAdvanced->TxImpedanceDTO[14]       = 50;
    pUserInputAdvanced->TxImpedanceWCK[14]       = 30;
    pUserInputAdvanced->OdtImpedanceWCK[14]      = 30;
    pUserInputAdvanced->OdtImpedanceDq[14]       = 60;
    pUserInputAdvanced->OdtImpedanceDqs[14]      = 30;
    pUserInputAdvanced->OdtImpedanceCa[14]       = 60;
    pUserInputAdvanced->OdtImpedanceCk[14]       = 30;


    pUserInputAdvanced->DisableRetraining       = 0x0;

    pUserInputAdvanced->DisableFspOp            = 0x0;


    pUserInputAdvanced->CalInterval             = 0x0009;
    pUserInputAdvanced->CalOnce                 = 0x0000;
    pUserInputAdvanced->CalImpedanceCurrentAdjustment = 0x0000;

    pUserInputAdvanced->PmuClockDiv             = 0x1;
    pUserInputAdvanced->DisablePmuEcc           = 0x0;


    pUserInputAdvanced->WDQSExt                 = 0x0000;

    for (int pstate = 0; pstate < DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; pstate++) {
        pUserInputAdvanced->PhyMstrTrainInterval[pstate]  = 0x000a;
        pUserInputAdvanced->PhyMstrMaxReqToAck[pstate]    = 0x0005;
        pUserInputAdvanced->PhyMstrCtrlMode[pstate]       = 0x0001;
        pUserInputAdvanced->RxClkTrackEn[pstate]          = 1;
        pUserInputAdvanced->EnRxDqsTracking[pstate]       = 0;
        pUserInputAdvanced->RxDqsTrackingThreshold[pstate]= 0x1;
        pUserInputAdvanced->DqsOscRunTimeSel[pstate]      = 0x3;
        pUserInputAdvanced->EnWck2DqoTracking[pstate]     = 0;
    }

    pUserInputAdvanced->DisablePhyUpdate         = 0x0000;
    for (int pstate=0; pstate<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE;pstate++) {
       pUserInputAdvanced->RxModeBoostVDD[pstate]      = 0;
       pUserInputAdvanced->RxVrefDACEnable[pstate]     = 1;
       pUserInputAdvanced->RxVrefKickbackNoiseCancellation[pstate] = 1;
       pUserInputAdvanced->RxBiasCurrentControlWck[pstate] = 0x5;
    }
    pUserInputAdvanced->OnlyRestoreNonPsRegs = (pUserInputBasic->NumPStates >2) ? 1 : 0;

    // ##############################################################
    // Basic Message Block Variables
    // ##############################################################

    uint8_t myps;

    // ##############################################################
    // These are typically invariant across Pstate
    // ##############################################################
    uint8_t MsgMisc              = 0x06; //For fast simulation
    uint8_t Reserved00           = 0x0;  // Set Reserved00[7]   = 1 (If using T28 attenuated receivers)
                                         // Set Reserved00[6:0] = 0 (Reserved; must be programmed to 0)

    uint8_t HdtCtrl              = 0xff;
    uint8_t PhyVref              = 0x14;
    uint8_t DFIMRLMargin         = 0x02;
    // ##############################################################
    // These typically change across Pstate
    // ##############################################################

    uint16_t SequenceCtrl[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];


    uint8_t mr1[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr2[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr3[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr10[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr11[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr13[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr14[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr15[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr16[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr17[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr18[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr19[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr20[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr21[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr22[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr28[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    uint8_t mr41[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    for (int pstate = 0; pstate < DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; pstate++) {
      SequenceCtrl[pstate] = 0x131f; // Training steps to run in PState 0
    }



    // 2D Training firmware Variables
    uint8_t  SequenceCtrl2D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    for (int pstate = 0; pstate < DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; pstate++) {
        SequenceCtrl2D[pstate] = 0x0061; // 2D Training Sequince. 2DTX, 2DRX, DevInit
    }

    // ##############################################################
    // These are per-pstate Control Words for RCD
    // Please enter the correct values for your configuration
    // ##############################################################


    // ##############################################################
    // 95% of users will not need to edit below
    // ##############################################################

    // MR bit packing for LPDDR5
    for ( myps = 0; myps < DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE ; myps++) {
        mr1[myps] =
            ( (0x0                                       << 3) & 0x08) | // CK mode
            ( (0x5                                       << 4) & 0xF0) ; // WL

        mr2[myps] =
            ( (0x5                                       << 0) & 0x0F) | // RL and nRTP
            ( (0x0                                       << 4) & 0xF0) ; // nWR

        mr3[myps] =
            ( (0x6                                       << 0) & 0x07) | // PDDS
            ( (0x1                                       << 3) & 0x18) | // BK/BG
            ( (0x0                                       << 5) & 0x20) | // WLS
            ( (0x0                                       << 6) & 0x40) | // DBI-RD
            ( (0x0                                       << 7) & 0x80) ; // DBI-WR

        mr10[myps] =
            ( (0x0                                       << 0) & 0x01) | // RPST Mode
            ( (0x1                                       << 2) & 0x0C) | // WCK PST
            ( (0x1                                       << 4) & 0x30) | // RDQS PRE
            ( (0x1                                       << 6) & 0xC0) ; // RDQS PST

        mr11[myps] =
            ( (0x4                                       << 0) & 0x07) | // DQ ODT
            ( (0x6                                       << 4) & 0x70) ; // CA ODT

        mr13[myps] =
            ( (0x0                                       << 0) & 0x03) | // Thermal Offset
            ( (0x0                                       << 2) & 0x04) | // VRO
            ( (0x0                                       << 4) & 0x20) | // DMD
            ( (0x0                                       << 4) & 0x40) | // CBT Mode
            ( (0x0                                       << 6) & 0x80) ; // Dual VDD2

        mr14[myps] =
            ( (0x50                                      << 0) & 0x7F) | // VREF DQ 7:0
            ( (0x0                                       << 7) & 0x80) ; // VDLC

        mr15[myps] =
            ( (0x50                                      << 0) & 0x7F) ; // VREF DQ 15:8

        mr16[myps] =
            ( (0x0                                       << 0) & 0x03) | // FSP-WR
            ( (0x0                                       << 2) & 0x04) | // FSP-OP
            ( (0x0                                       << 4) & 0x20) | // CBT
            ( (0x0                                       << 4) & 0x40) | // VRCG
            ( (0x0                                       << 6) & 0x80) ; // CBT-Phase

        mr17[myps] =
            ( (0x0                                       << 0) & 0x07) | // SOC ODT
            ( (0x1                                       << 3) & 0x08) | // ODTD-CK
            ( (0x1                                       << 5) & 0x20) | // ODTD-CA
            ( (0x0                                       << 6) & 0x40) | // x8ODTD Lower
            ( (0x0                                       << 7) & 0x80) ; // x8ODTD Upper

        mr18[myps] =
            ( (0x0                                       << 0) & 0x07) | // WCK ODT
            ( (0x0                                       << 3) & 0x08) | // WCK FM
            ( (0x0                                       << 4) & 0x10) | // WCK ON
            ( (0x0                                       << 6) & 0x40) | // WCK2CK Leveling
            ( (0x0                                       << 7) & 0x80) ; // CKR

        mr19[myps] =
            ( (0x0                                       << 0) & 0x03) | // DVFSC
            ( (0x0                                       << 2) & 0xC0) ; // DVFSQ

        mr20[myps] =
            ( (0x2                                       << 0) & 0x03) | // RDQS
            ( (0x0                                       << 2) & 0x0C) | // WCK mode
            ( (0x0                                       << 4) & 0x10) | // MRWDU
            ( (0x0                                       << 5) & 0x20) | // MRWDL
            ( (0x0                                       << 6) & 0x40) | // RDC DMI mode
            ( (0x0                                       << 7) & 0x80) ; // RDC DQ mode

        mr21[myps] =
            ( (0x0                                       << 4) & 0x10) | // WDCFE
            ( (0x0                                       << 5) & 0x20) | // RDCFE
            ( (0x0                                       << 6) & 0x40) ; // WXFE

        mr22[myps] =
            ( (0x0                                       << 4) & 0x30) | // WECC
            ( (0x0                                       << 6) & 0xC0) ; // RECC

        mr28[myps] =
            ( (0x0                                       << 0) & 0x01) | // ZQ Reset
            ( (0x0                                       << 1) & 0x02) | // ZQ Stop
            ( (0x1                                       << 2) & 0x0C) | // ZQ Interval
            ( (0x0                                       << 5) & 0x20) ; // ZQ Mode

        mr41[myps] =
            ( (0x0                                       << 4) & 0x10) | // PPRE
            ( (0x3                                       << 5) & 0xE0) ; // NT DQ ODT
    }




    // 1D message block defaults
    for (myps=0; myps<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; myps++) {
      mb1D[myps].Pstate               = (pUserInputBasic->NumPStates>2)<<7 | myps;
      mb1D[myps].SequenceCtrl         = SequenceCtrl[myps];
      mb1D[myps].HdtCtrl              = HdtCtrl;
      mb1D[myps].MsgMisc              = MsgMisc;
      mb1D[myps].Reserved00           = Reserved00;
      mb1D[myps].DFIMRLMargin         = DFIMRLMargin;
      mb1D[myps].PhyVref              = PhyVref;

      mb1D[myps].Disable2D            = 0x0000;

      mb1D[myps].EnabledDQsChA        = pUserInputBasic->NumActiveDbyteDfi0 * 8;
      mb1D[myps].CsPresentChA         = (2==pUserInputBasic->NumRank_dfi0) ? 0x3 : pUserInputBasic->NumRank_dfi0;
      mb1D[myps].EnabledDQsChB        = pUserInputBasic->NumActiveDbyteDfi1 * 8;
      mb1D[myps].CsPresentChB         = (2==pUserInputBasic->NumRank_dfi1) ? 0x3 : pUserInputBasic->NumRank_dfi1;

      mb1D[myps].X8Mode               = 0x0000;

      mb1D[myps].MR1_A0               = mr1[myps];
      mb1D[myps].MR1_A1               = mr1[myps];
      mb1D[myps].MR1_B0               = mr1[myps];
      mb1D[myps].MR1_B1               = mr1[myps];
      mb1D[myps].MR2_A0               = mr2[myps];
      mb1D[myps].MR2_A1               = mr2[myps];
      mb1D[myps].MR2_B0               = mr2[myps];
      mb1D[myps].MR2_B1               = mr2[myps];
      mb1D[myps].MR3_A0               = mr3[myps];
      mb1D[myps].MR3_A1               = mr3[myps];
      mb1D[myps].MR3_B0               = mr3[myps];
      mb1D[myps].MR3_B1               = mr3[myps];
      mb1D[myps].MR10_A0              = mr10[myps];
      mb1D[myps].MR10_A1              = mr10[myps];
      mb1D[myps].MR10_B0              = mr10[myps];
      mb1D[myps].MR10_B1              = mr10[myps];
      mb1D[myps].MR11_A0              = mr11[myps];
      mb1D[myps].MR11_A1              = mr11[myps];
      mb1D[myps].MR11_B0              = mr11[myps];
      mb1D[myps].MR11_B1              = mr11[myps];
      mb1D[myps].MR13_A0              = mr13[myps];
      mb1D[myps].MR13_A1              = mr13[myps];
      mb1D[myps].MR13_B0              = mr13[myps];
      mb1D[myps].MR13_B1              = mr13[myps];
      mb1D[myps].MR14_A0              = mr14[myps];
      mb1D[myps].MR14_A1              = mr14[myps];
      mb1D[myps].MR14_B0              = mr14[myps];
      mb1D[myps].MR14_B1              = mr14[myps];
      mb1D[myps].MR15_A0              = mr15[myps];
      mb1D[myps].MR15_A1              = mr15[myps];
      mb1D[myps].MR15_B0              = mr15[myps];
      mb1D[myps].MR15_B1              = mr15[myps];
      mb1D[myps].MR16_A0              = mr16[myps];
      mb1D[myps].MR16_A1              = mr16[myps];
      mb1D[myps].MR16_B0              = mr16[myps];
      mb1D[myps].MR16_B1              = mr16[myps];
      mb1D[myps].MR17_A0              = mr17[myps];
      mb1D[myps].MR17_A1              = mr17[myps];
      mb1D[myps].MR17_B0              = mr17[myps];
      mb1D[myps].MR17_B1              = mr17[myps];
      mb1D[myps].MR18_A0              = mr18[myps];
      mb1D[myps].MR18_A1              = mr18[myps];
      mb1D[myps].MR18_B0              = mr18[myps];
      mb1D[myps].MR18_B1              = mr18[myps];
      mb1D[myps].MR19_A0              = mr19[myps];
      mb1D[myps].MR19_A1              = mr19[myps];
      mb1D[myps].MR19_B0              = mr19[myps];
      mb1D[myps].MR19_B1              = mr19[myps];
      mb1D[myps].MR20_A0              = mr20[myps];
      mb1D[myps].MR20_A1              = mr20[myps];
      mb1D[myps].MR20_B0              = mr20[myps];
      mb1D[myps].MR20_B1              = mr20[myps];
      mb1D[myps].MR21_A0              = mr21[myps];
      mb1D[myps].MR21_A1              = mr21[myps];
      mb1D[myps].MR21_B0              = mr21[myps];
      mb1D[myps].MR21_B1              = mr21[myps];
      mb1D[myps].MR22_A0              = mr22[myps];
      mb1D[myps].MR22_A1              = mr22[myps];
      mb1D[myps].MR22_B0              = mr22[myps];
      mb1D[myps].MR22_B1              = mr22[myps];
      mb1D[myps].MR28_A0              = mr28[myps];
      mb1D[myps].MR28_A1              = mr28[myps];
      mb1D[myps].MR28_B0              = mr28[myps];
      mb1D[myps].MR28_B1              = mr28[myps];
      mb1D[myps].MR41_A0              = mr41[myps];
      mb1D[myps].MR41_A1              = mr41[myps];
      mb1D[myps].MR41_B0              = mr41[myps];
      mb1D[myps].MR41_B1              = mr41[myps];


      } // myps

    // 2D message block defaults
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    if (pRuntimeConfig->Train2D) {
    for (myps=0; myps<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; myps++) {
        mb2D[myps].Pstate               = (pUserInputBasic->NumPStates>2)<<7 | myps;
        mb2D[myps].SequenceCtrl         = SequenceCtrl2D[myps];
        mb2D[myps].HdtCtrl              = HdtCtrl;
        mb2D[myps].MsgMisc              = MsgMisc;
        mb2D[myps].Reserved00           = Reserved00;
        mb2D[myps].DFIMRLMargin         = DFIMRLMargin;
        mb2D[myps].PhyVref              = PhyVref;

        mb2D[myps].Disable2D            = 0x0000;

        mb2D[myps].EnabledDQsChA        = pUserInputBasic->NumActiveDbyteDfi0 * 8;
        mb2D[myps].CsPresentChA         = (2==pUserInputBasic->NumRank_dfi0) ? 0x3 : pUserInputBasic->NumRank_dfi0;
        mb2D[myps].EnabledDQsChB        = pUserInputBasic->NumActiveDbyteDfi1 * 8;
        mb2D[myps].CsPresentChB         = (2==pUserInputBasic->NumRank_dfi1) ? 0x3 : pUserInputBasic->NumRank_dfi1;

        mb2D[myps].X8Mode               = 0x0000;

        mb2D[myps].MR1_A0               = mr1[myps];
        mb2D[myps].MR1_A1               = mr1[myps];
        mb2D[myps].MR1_B0               = mr1[myps];
        mb2D[myps].MR1_B1               = mr1[myps];
        mb2D[myps].MR2_A0               = mr2[myps];
        mb2D[myps].MR2_A1               = mr2[myps];
        mb2D[myps].MR2_B0               = mr2[myps];
        mb2D[myps].MR2_B1               = mr2[myps];
        mb2D[myps].MR3_A0               = mr3[myps];
        mb2D[myps].MR3_A1               = mr3[myps];
        mb2D[myps].MR3_B0               = mr3[myps];
        mb2D[myps].MR3_B1               = mr3[myps];
        mb2D[myps].MR10_A0              = mr10[myps];
        mb2D[myps].MR10_A1              = mr10[myps];
        mb2D[myps].MR10_B0              = mr10[myps];
        mb2D[myps].MR10_B1              = mr10[myps];
        mb2D[myps].MR11_A0              = mr11[myps];
        mb2D[myps].MR11_A1              = mr11[myps];
        mb2D[myps].MR11_B0              = mr11[myps];
        mb2D[myps].MR11_B1              = mr11[myps];
        mb2D[myps].MR13_A0              = mr13[myps];
        mb2D[myps].MR13_A1              = mr13[myps];
        mb2D[myps].MR13_B0              = mr13[myps];
        mb2D[myps].MR13_B1              = mr13[myps];
        mb2D[myps].MR14_A0              = mr14[myps];
        mb2D[myps].MR14_A1              = mr14[myps];
        mb2D[myps].MR14_B0              = mr14[myps];
        mb2D[myps].MR14_B1              = mr14[myps];
        mb2D[myps].MR15_A0              = mr15[myps];
        mb2D[myps].MR15_A1              = mr15[myps];
        mb2D[myps].MR15_B0              = mr15[myps];
        mb2D[myps].MR15_B1              = mr15[myps];
        mb2D[myps].MR16_A0              = mr16[myps];
        mb2D[myps].MR16_A1              = mr16[myps];
        mb2D[myps].MR16_B0              = mr16[myps];
        mb2D[myps].MR16_B1              = mr16[myps];
        mb2D[myps].MR17_A0              = mr17[myps];
        mb2D[myps].MR17_A1              = mr17[myps];
        mb2D[myps].MR17_B0              = mr17[myps];
        mb2D[myps].MR17_B1              = mr17[myps];
        mb2D[myps].MR18_A0              = mr18[myps];
        mb2D[myps].MR18_A1              = mr18[myps];
        mb2D[myps].MR18_B0              = mr18[myps];
        mb2D[myps].MR18_B1              = mr18[myps];
        mb2D[myps].MR19_A0              = mr19[myps];
        mb2D[myps].MR19_A1              = mr19[myps];
        mb2D[myps].MR19_B0              = mr19[myps];
        mb2D[myps].MR19_B1              = mr19[myps];
        mb2D[myps].MR20_A0              = mr20[myps];
        mb2D[myps].MR20_A1              = mr20[myps];
        mb2D[myps].MR20_B0              = mr20[myps];
        mb2D[myps].MR20_B1              = mr20[myps];
        mb2D[myps].MR21_A0              = mr21[myps];
        mb2D[myps].MR21_A1              = mr21[myps];
        mb2D[myps].MR21_B0              = mr21[myps];
        mb2D[myps].MR21_B1              = mr21[myps];
        mb2D[myps].MR22_A0              = mr22[myps];
        mb2D[myps].MR22_A1              = mr22[myps];
        mb2D[myps].MR22_B0              = mr22[myps];
        mb2D[myps].MR22_B1              = mr22[myps];
        mb2D[myps].MR28_A0              = mr28[myps];
        mb2D[myps].MR28_A1              = mr28[myps];
        mb2D[myps].MR28_B0              = mr28[myps];
        mb2D[myps].MR28_B1              = mr28[myps];
        mb2D[myps].MR41_A0              = mr41[myps];
        mb2D[myps].MR41_A1              = mr41[myps];
        mb2D[myps].MR41_B0              = mr41[myps];
        mb2D[myps].MR41_B1              = mr41[myps];


        mb2D[myps].RX2D_TrainOpt        = 0x00; // DFE off, Voltage Step Size=1 DAC setting, LCDL Delay Step Size=1 LCDL delay between checked values.
        mb2D[myps].TX2D_TrainOpt        = 0x00; // FFE off, Voltage Step Size=1 DAC setting, LCDL Delay Step Size=1 LCDL delay between checked values.
        mb2D[myps].Delay_Weight2D       = 0x20; // Evenly weigh Delay vs Voltage
        mb2D[myps].Voltage_Weight2D     = 0x80;
      } // myps
    } // Train2D

    // ##############################################################
    // userInputSim - Dram/Dimm Timing Parameters the user must
    // provide value if applicable
    // ##############################################################
    pUserInputSim->tWCK2DQO                   = 1000;
    pUserInputSim->tWCK2DQI                   = 500;
    pUserInputSim->tWCK2CK                    = 0;

    // ##############################################################
    // Set to be compatible with maximum design frequency
    // ##############################################################
    pUserInputSim->PHY_tDQS2DQ                = 312;  // 2*UImin , =312 if LPDDR4-6400 is max design frequency, not to be confused with dram tdqs2dq

    dwc_ddrphy_phyinit_print ("%s End of dwc_ddrphy_phyinit_setDefault()\n", printf_header);
}
/** @} */
