/** \file
 *  \addtogroup SrcFunc
 *  @{
 */
#include <math.h>
#include <stdlib.h>
#include "dwc_ddrphy_phyinit.h"

/** \brief This function programs registers that are normally set by training
 * firmware.
 *
 * This function is used in lieu of running 1D or 1D+2D training steps. PhyInit
 * calls this function when skip_train = 1 (SkipTrain) or 2 (DevInit). When
 * skip_train=1, PhyInit does not execute training firmware and this function is
 * called instead to program PHY registers according to DRAM timing parameters
 * specified in userInputSim data structure.  See documentation of
 * dwc_ddrphy_phyinit_struct.h file details of timing parameters available in
 * skip training.  When skip_train=2 is selected, PhyInit executes training
 * firmware with SequenceCtrl set in the training firmware message block to only
 * perform DRAM device initialization. This function is then called to program
 * PHY timing registers in lieu of running training.
 *
 * \warning dwc_ddrphy_phyinit_progCsrSkipTrain() only supports zero board
 * delay model.  If system board delays are set or randomized, full 1D or 1D/2D
 * initialization flow must be executed.
 *
 * This function replaces these steps in the PHY Initialization sequence:
 *
 *  - (E) Set the PHY input clocks to the desired frequency
 *  - (F) Write the Message Block parameters for the training firmware
 *  - (G) Execute the Training Firmware
 *  - (H) Read the Message Block results
 *
 * \returns \c void
 */
void dwc_ddrphy_phyinit_progCsrSkipTrain (phyinit_config_t* phyctx)
  {
    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;

    char *printf_header = "[dwc_ddrphy_phyinit_progCsrSkipTrain]";
    int NumDbyte = pUserInputBasic->NumCh * pUserInputBasic->NumDbytesPerCh ;
    int byte;
    int c_addr;

    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_progCsrSkipTrain()\n", printf_header);

   /**
    * - Program PllCtrl3
    *
    */
    uint16_t force_cal = 1;
    uint16_t maxrange = 0x1f;

    uint16_t pllctrl3 = (force_cal << csr_PllForceCal_LSB) | (maxrange << csr_PllMaxRange_LSB);

    dwc_ddrphy_phyinit_cmnt ("%s Programming PllCtrl3::PllForceCal to 0x%x\n", printf_header, force_cal);
    dwc_ddrphy_phyinit_cmnt ("%s Programming PllCtrl3::PllMaxRange to 0x%x\n", printf_header, maxrange);
    dwc_ddrphy_phyinit_cmnt ("%s Programming PllCtrl3 to 0x%x\n", printf_header, pllctrl3);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_PllCtrl3_ADDR), pllctrl3);

    /**
     * - Program RxReplicaUICalWait
     */
    uint16_t rxUICalWait = 156;
    dwc_ddrphy_phyinit_cmnt ("%s RxReplica Programming RxReplicaUICalWait to 0x%x\n", printf_header, rxUICalWait);
    for (byte=0; byte<NumDbyte; byte++)
      {
        c_addr = byte * c1;
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_RxReplicaUICalWait_ADDR), rxUICalWait);
      }

    /**
     * - Program RxClkCntl:
     *   - Fields
     *     - EnRxClkCor
     *     - EnRxClkCorAnytime
     *     - ShortCalRangeSel
     */
    uint16_t RxClkCntl = csr_EnRxClkCor_MASK; // EnRxClkCorAnytime=0, ShortCalRangeSel=0
    dwc_ddrphy_phyinit_cmnt ("%s Programming RxClkCntl to 0x%x\n", printf_header, RxClkCntl);

    for (byte=0; byte<NumDbyte; byte++)
      {
        c_addr = byte * c1;
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_RxClkCntl_ADDR), RxClkCntl);
      }

    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_progCsrSkipTrain()\n", printf_header);
  }
// End of dwc_ddrphy_phyinit_progCsrSkipTrain()

void dwc_ddrphy_phyinit_progCsrSkipTrainPsLoop (phyinit_config_t* phyctx) {

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    user_input_sim_t* pUserInputSim = &phyctx->userInputSim;
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    //uint8_t prog_csr = (pRuntimeConfig->initCtrl & 0x01) >> 0;
    uint8_t devinit = (pRuntimeConfig->initCtrl & 0x20) >> 5;

    PMU_SMB_LPDDR4X_1D_t* mb1D = phyctx->mb_LPDDR4X_1D;

    char *printf_header;
    printf_header = "[dwc_ddrphy_phyinit_progCsrSkipTrainPsLoop]";

    dwc_ddrphy_phyinit_print ("\n\n");
    dwc_ddrphy_phyinit_cmnt ("/**\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("// Training firmware is *NOT* executed. This function replaces these steps\n");
    dwc_ddrphy_phyinit_cmnt ("// in the PHY Initialization sequence:\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("//  (E) Set the PHY input clocks to the desired frequency \n");
    dwc_ddrphy_phyinit_cmnt ("//  (F) Write the Message Block parameters for the training firmware \n");
    dwc_ddrphy_phyinit_cmnt ("//  (G) Execute the Training Firmware \n");
    dwc_ddrphy_phyinit_cmnt ("//  (H) Read the Message Block results\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("/**\n");
    dwc_ddrphy_phyinit_print ("\n\n");

    uint32_t pstate  = pRuntimeConfig->curPState;
    uint32_t p_addr  = pUserInputBasic->NumPStates <3 ? pstate << 20 : p0;

    int byte;
    int c_addr;
    int lane;
    int r_addr;

    float UIps;
    float dficlk_period;

    int tSTAOFF[4];
    int tPDM[4];
    int tCASL_add[4];

    int NumDbyte = pUserInputBasic->NumCh * pUserInputBasic->NumDbytesPerCh ;

    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_progCsrSkipTrainPsLoop()\n", printf_header);

    // Calculate total number of timing groups (ranks)
    int NumRank_total;
    NumRank_total = pUserInputBasic->NumRank_dfi0 + pUserInputBasic->NumRank_dfi1 * (pUserInputBasic->NumCh-1);
    dwc_ddrphy_phyinit_cmnt ("%s NumRank_total = %d\n", printf_header, NumRank_total);

    /**
     *
     * set tSTAOFF and tPDM
     *
     */

        UIps = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6 * 0.5;

    
        // LPDDR3 or LPDDR4
         tSTAOFF[pstate] = 0;
         tPDM[pstate]    = 0;
    

         // If tDPM > tSTAOFF, push out read/write by 1 Memclk
         if (tPDM[pstate] > tSTAOFF[pstate]) tCASL_add[pstate] = 2 * UIps;
         else                      tCASL_add[pstate] = 0;


    /**
     *
     * Program DFIMRL per P-state according to this formula:
     *
     *         DFIMRL = ceiling( (tCtrlDelay + PHY_Tx_Insertion_Dly + PHY_Rx_Insertion_Dly + PHY_Rx_Fifo_dly + tDQSCK + tSTAOFF) / dficlk_period)
     *
     * All terms in above equation specified in ps
     * tDQSCK - determine from memory model
     * tSTAOFF - determine from memory model if Dimm type is RDIMM or LRDIMM, otherwise
     * PHY_Tx_Insertion_Dly = 111ps
     * PHY_Rx_Insertion_Dly = 111ps
     * PHY_Rx_Fifo_Dly      = 200ps + 4UI
     * tCtrlDelay is a function of PclkPtrInitVal
     *
     */
    int DFIMRL;
    float DFIMRL_adjustment;
    int PHY_Tx_Insertion_Dly = 111;
    int PHY_Rx_Insertion_Dly = 111;
    int PHY_Rx_Fifo_Dly;
    float tctrl_delay_in_memck;
    float tctrl_delay_adjusted;
    float tctrl_delay_in_ps;
    float tctrl_added_dly;
    int tctrl_div;
    float tck_ps;
    float DFIMRL_in_ps;
    float DFIMRL_in_dficlk;
    int AcPipeEn = 0;

    // Set DFIMRL per p-state


        tck_ps = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6;
        UIps = tck_ps * 0.5;
        dficlk_period = UIps * (pUserInputBasic->DfiFreqRatio[pstate] == 0x1 ? 4 : 8);
        PHY_Rx_Fifo_Dly = 200 + ceil(dficlk_period);

        if (pUserInputBasic->DfiFreqRatio[pstate] == 0x1) {
            tctrl_added_dly = 3.5;
            tctrl_div = (pUserInputBasic->Frequency[pstate] < 1600) ? 4 : 2; // PLL in x4 mode for higher freq
        } else {
            tctrl_added_dly = 5.5;
            tctrl_div = 2;
        }
        tctrl_delay_in_memck = ((phyctx->PclkPtrInitVal[pstate] + 1.0) / tctrl_div ) + tctrl_added_dly;
        tctrl_delay_in_ps = tctrl_delay_in_memck * tck_ps;
        tctrl_delay_adjusted = ceil(tctrl_delay_in_ps - dficlk_period);

        DFIMRL_in_ps = tctrl_delay_adjusted + PHY_Tx_Insertion_Dly + PHY_Rx_Insertion_Dly + PHY_Rx_Fifo_Dly + pUserInputSim->tDQSCK   + pUserInputSim->PHY_tDQS2DQ + tSTAOFF[pstate] + tCASL_add[pstate] + tPDM[pstate];
        DFIMRL_in_dficlk = DFIMRL_in_ps / dficlk_period;
        DFIMRL_adjustment = pUserInputBasic->DfiFreqRatio[pstate] == 0x1 ? -0.5 : -1.25;
        DFIMRL = ceil(DFIMRL_in_dficlk + DFIMRL_adjustment) + AcPipeEn + mb1D[pstate].DFIMRLMargin;

        dwc_ddrphy_phyinit_cmnt ("%s DRAM protocol          = %s\n", printf_header, "LPDDR4");
        dwc_ddrphy_phyinit_cmnt ("%s DFI ratio              = %s\n", printf_header, pUserInputBasic->DfiFreqRatio[pstate] == 0x1 ? "1:2" : "1:4");
        dwc_ddrphy_phyinit_cmnt ("%s CK freq (MHz)          = %d\n", printf_header, pUserInputBasic->Frequency[pstate]);
        dwc_ddrphy_phyinit_cmnt ("%s tCK (ps)               = %f\n", printf_header, tck_ps);
        dwc_ddrphy_phyinit_cmnt ("%s DQ UI (ps)             = %f\n", printf_header, UIps);
        dwc_ddrphy_phyinit_cmnt ("%s DFIClk period (ps)     = %f\n", printf_header, dficlk_period);
        dwc_ddrphy_phyinit_cmnt ("%s PHY_Rx_Fifo_Dly        = %d\n", printf_header, PHY_Rx_Fifo_Dly);
        dwc_ddrphy_phyinit_cmnt ("%s PHY_Tx_Insertion_Dly   = %d\n", printf_header, PHY_Tx_Insertion_Dly);
        dwc_ddrphy_phyinit_cmnt ("%s PHY_Rx_Insertion_Dly   = %d\n", printf_header, PHY_Rx_Insertion_Dly);
        dwc_ddrphy_phyinit_cmnt ("%s PclkPtrInitVal         = %d\n", printf_header, phyctx->PclkPtrInitVal[pstate]);
        dwc_ddrphy_phyinit_cmnt ("%s tCtrl delay (in CK)    = %f\n", printf_header, tctrl_delay_in_memck);
        dwc_ddrphy_phyinit_cmnt ("%s tCtrl delay (ps)       = %f\n", printf_header, tctrl_delay_in_ps);
        dwc_ddrphy_phyinit_cmnt ("%s tCtrl delay, adjusted  = %f\n", printf_header, tctrl_delay_adjusted);
        dwc_ddrphy_phyinit_cmnt ("%s tDQSCK (ps)            = %d\n", printf_header, pUserInputSim->tDQSCK);
        dwc_ddrphy_phyinit_cmnt ("%s PHY_tDQS2DQ (ps)       = %d\n", printf_header, pUserInputSim->PHY_tDQS2DQ);
        dwc_ddrphy_phyinit_cmnt ("%s DFIMRL (ps)            = %f\n", printf_header, DFIMRL_in_ps);
        dwc_ddrphy_phyinit_cmnt ("%s DFIMRL (in DFIClk)     = %f\n", printf_header, DFIMRL_in_dficlk);
        dwc_ddrphy_phyinit_cmnt ("%s DFIMRL margin          = %d\n", printf_header, mb1D[pstate].DFIMRLMargin);
        dwc_ddrphy_phyinit_cmnt ("%s DFIMRL ratio adjustment= %f\n", printf_header, DFIMRL_adjustment);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming HwtMRL to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], DFIMRL);

        //dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | cbrd | csr_DFIMRL_ADDR), DFIMRL);
        for (byte=0; byte<NumDbyte; byte++) {
            c_addr = byte << 12;
            dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_DFIMRL_ADDR), DFIMRL);
        }

        dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_HwtMRL_ADDR), DFIMRL);



    /**
     *
     * Program TxWckDlyTg0/1/2/3[9:0] per P-State:
     *
     * For other dimm types, leave TxWckDlyTg*[9:0] at default 0x200
     *
     *      num_timingroup = NumRank_dfi0 + NumRank_dfi1 * (NumCh-1);
     *
     *
     */
    int TxWckDly[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    int TxWckDlyTg_10to6;  // Coarse delay - 1UI per increment
    int TxWckDlyTg_5to0;  // Fine delay - 1/64UI per increment


    int TxWckDlyTg_coarse_default;
    int TxWckDlyTg_fine_default;

    //dwc_ddrphy_phyinit_cmnt ("1st DfiFreqRatio = %x  TxWckDlyTg_coarse_default=%d \n", pUserInputBasic->DfiFreqRatio[pstate], TxWckDlyTg_coarse_default);

    //
    //TxWckDlyTg_coarse_default = 8;
    //TxWckDlyTg_fine_default = 0;
    //dwc_ddrphy_phyinit_cmnt ("2nd DfiFreqRatio = %x  TxWckDlyTg_coarse_default=%d \n", pUserInputBasic->DfiFreqRatio[pstate], TxWckDlyTg_coarse_default);

    // Set per p-state
      TxWckDlyTg_coarse_default = ((pUserInputBasic->DfiFreqRatio[pstate] == 0x1) ? 4 : 8);
      TxWckDlyTg_fine_default = 0;

      UIps = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6 * 0.5;

      TxWckDlyTg_10to6 = TxWckDlyTg_coarse_default;
      TxWckDlyTg_5to0 = TxWckDlyTg_fine_default;


      TxWckDly[pstate] = (TxWckDlyTg_10to6 << 6) | TxWckDlyTg_5to0;


        if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxWckDlyTg0 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxWckDly[pstate]);
        if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxWckDlyTg1 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxWckDly[pstate]);
        if (0x0) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxWckDlyTg2 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxWckDly[pstate]);
        if (0x0) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxWckDlyTg3 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxWckDly[pstate]);

        for (byte=0; byte<NumDbyte; byte++) {
            c_addr = byte << 12;
            if ( !dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte) ) {
                if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxWckDlyTg0_ADDR), TxWckDly[pstate]);
                if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxWckDlyTg1_ADDR), TxWckDly[pstate]);
            }
        }

   /**
    *
    * Program TxDqsDlyTg0/1/2/3[9:0] per P-State:
    *
    * If Dimm Type is RDIMM or LRDIMM, program as follow:
    *
    *         TxDqsDlyTg*[9:6] = floor( (4*UI + tSTAOFF) / UI)
    *         TxDqsDlyTg*[5:0] = ceiling( (tSTAOFF%UI / UI) * 64)
    *
    * tSTAOFF and UI expressed in ps
    *
    * For HMD and LPDDR4X and MEMCLK <= 533 mhz:
    *    TxDqsDlyTg*[9:6] = 0x5
    *
    * For other dimm types, leave TDqsDlyTg*[9:0] at default 0x100
    *
    * ppp_0001_cccc_uuuu_1101_0000
    *
    * if DDR3 or DDR4
    *      num_timingroup = NumRank_dfi0;
    * else
    *      num_timingroup = NumRank_dfi0 + NumRank_dfi1 * (NumCh-1);
    *
    *
    */
    int TxDqsDly[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    int TxDqsDlyTg_9to6;  // Coarse delay - 1UI per increment
    int TxDqsDlyTg_5to0;  // Fine delay - 1/64UI per increment

    int TxDqsDlyTg_coarse_default = 4;
    int TxDqsDlyTg_fine_default = 0;

    // Set per p-state

        UIps = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6 * 0.5;

        TxDqsDlyTg_5to0 = ceil( fmodf((TxDqsDlyTg_fine_default*UIps/64 + tSTAOFF[pstate] + tCASL_add[pstate] - tPDM[pstate]), UIps) / UIps * 64);
        TxDqsDlyTg_9to6 = floor( (TxDqsDlyTg_coarse_default * UIps + tSTAOFF[pstate] + tCASL_add[pstate] - tPDM[pstate]) / UIps);

        // Bit-5 of LCDL is no longer used, so bumping bit-5 of fine_dly up to coarse_dly
        if (TxDqsDlyTg_5to0 >= 64) {
            TxDqsDlyTg_9to6 = TxDqsDlyTg_9to6 + 1;
            TxDqsDlyTg_5to0 = TxDqsDlyTg_5to0 - 64;
        }








        TxDqsDly[pstate] = (TxDqsDlyTg_9to6 << 6) | TxDqsDlyTg_5to0;


      
        if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqsDlyTg0 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqsDly[pstate]);
        if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqsDlyTg1 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqsDly[pstate]);
        if (0x0) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqsDlyTg2 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqsDly[pstate]);
        if (0x0) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqsDlyTg3 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqsDly[pstate]);
      

        for (byte=0; byte<NumDbyte; byte++) {
            c_addr = byte << 12;
            if ( !dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte) ) {
              
                if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxDqsDlyTg0_ADDR), TxDqsDly[pstate]);
                if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxDqsDlyTg1_ADDR), TxDqsDly[pstate]);
              
            }
        }

    /**
     *
     * Program TxDqDlyTg0/1/2/3[8:0] per P-state:
     *
     * TxDqDlyTg0/1/2/3 - leave at default 16'h0010 for LPDDR3
     *
     * LPDDR4
     *     TxDqDlyTg*[8:6] = floor( (TxDqsDlyTg*[5:0]*UI/64 + tDQS2DQ + 0.5UI) / UI)
     *     TxDqDlyTg*[5:0] = ceil( ((TxDqsDlyTg*[5:0]*UI/64 + tDQS2DQ + 0.5UI)%UI / UI) * 64 )
     *
     * LPDDR5  - Note in LP5 UI needs to be used of WCK  which is one eight of CK.
     *     TxDqDlyTg*[8:6] = floor( (TxDqsDlyTg*[5:0]*UI/64 + tWCK2DQI + 0.125UI) / 0.25UI)
     *     TxDqDlyTg*[5:0] = ceil( ((TxDqsDlyTg*[5:0]*UI/64 + tWCK2DQI + 0.125UI)%0.125UI / 0.25UI) * 64 )
     *
     */
    int TxDqDly[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    int TxDqDly_8to6;  // Coarse delay - 1UI per increment
    int TxDqDly_5to0;  // Fine delay - 1/64UI per increment

    // Set per p-state
    UIps = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6 * 0.5;
        TxDqsDlyTg_5to0 = TxDqsDly[pstate] & 0x3f;
        TxDqDly_8to6 = floor( (TxDqsDlyTg_5to0*UIps/64 + pUserInputSim->tDQS2DQ + UIps/2) / UIps );
        TxDqDly_5to0 = ceil( (fmodf((TxDqsDlyTg_5to0*UIps/64 + pUserInputSim->tDQS2DQ + UIps/2), UIps) / UIps) * 64 );
       // Bit-5 of LCDL is no longer used, so bumping bit-5 of fine_dly up to coarse_dly
        if (TxDqDly_5to0 >= 64) {
            TxDqDly_8to6 = TxDqDly_8to6 + 1;
            TxDqDly_5to0 = TxDqDly_5to0 - 64;
        }



	TxDqDly[pstate] = (TxDqDly_8to6 << 6) | TxDqDly_5to0;


        //dwc_ddrphy_phyinit_cmnt ("Memclk=%dMHz, UIps=%f TxWckDlyTg_5to0=%d  tWCK2DQI=%d TxDqDly[pstate] = %x, Here UI 1st \n", pUserInputBasic->Frequency[pstate], UIps, TxWckDlyTg_5to0, pUserInputSim->tWCK2DQI, TxDqDly[pstate]);

       
        if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqDlyTg0 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqDly[pstate]);
        if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqDlyTg1 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqDly[pstate]);
        if (0x0) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqDlyTg2 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqDly[pstate]);
        if (0x0) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxDqDlyTg3 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], TxDqDly[pstate]);
      

      //dwc_ddrphy_phyinit_cmnt ("Memclk=%dMHz, UIps=%f TxWckDlyTg_5to0=%d  tWCK2DQI=%d TxDqDly[pstate] = %x, Here UI 2nd \n", pUserInputBasic->Frequency[pstate], UIps, TxWckDlyTg_5to0, pUserInputSim->tWCK2DQI, TxDqDly[pstate]);


        for (byte=0; byte<NumDbyte; byte++) {
            c_addr = byte << 12;
            for (lane=0; lane < 9; lane++) {
                r_addr = lane << 8;
                if ( !dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte) ) {
                  
                    if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_TxDqDlyTg0_ADDR), TxDqDly[pstate]);
                    if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_TxDqDlyTg1_ADDR), TxDqDly[pstate]);
                    //if (0x0) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_TxDqDlyTg2_ADDR), TxDqDly[pstate]);
                    //if (0x0) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_TxDqDlyTg3_ADDR), TxDqDly[pstate]);
                  
                }
            }
        }


    /**
     *
     * Program RxEnDly0/1/2/3[10:0] per P-State:
     * Program RxEnDly0/1[10:0] per P-State:  ONLY 2 P-State in lpddr54
     *
     *         RxEnDly[10:6] = floor( (4*UI + tDQSCK + tSTAOFF) / UI)
     *         RxEnDly[5:0]  = ceil( ((tDQSCK + tSTAOFF) % UI) * 64 )
     *
     * tDQSCK, tSTAOFF and UI expressed in ps
     * tSTAOFF is 0 if dimm type is not RDIMM nor LRDIMM
     *
     */
    float UIps_RX;

    int RxEnDly[2];
    int RxClk2UIDly_csr[2]; // csr format

    int RxEnDly_10to6;  // Coarse delay - 1UI per increment
    int RxEnDly_5to0;  // Fine delay - 1/64UI per increment

    int RxEnDly_coarse_default;
    int RxEnDly_fine_default = 0;
    float RxEnDly_offset = 0.0;  // 0 offset is 1UI before the first DQS


    int phyrd_tdqs2dq_ps = pUserInputSim->PHY_tDQS2DQ;
    int phyrd_tdqs2dq_UiFractionUnits;  // a UI fraction unit is 1/64th of a UI

    int RxClkDly_coarse_default = 2;
    int RxClkDly_fine_default   = 32;  // csr default, 0.5UI if 1/64 precision
                                       // the above 0.5UI is how we say to position the RxClk in the middle of the UI.
    int RxClkDly_UiFractionUnits_default = RxClkDly_coarse_default*64 + RxClkDly_fine_default;

    int RxClkDly_UiFractionUnits;      // a UI fraction unit is 1/64th of a UI
    int RxClkDly_coarse;
    int RxClkDly_fine;

        UIps_RX = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6 * 0.5;
        float FineStepPs = UIps_RX/64.0; // fine steps in ps
        RxEnDly_coarse_default = 3;
        float totPs =  (64*RxEnDly_coarse_default*FineStepPs + RxEnDly_fine_default*FineStepPs +pUserInputSim->tDQSCK + tSTAOFF[pstate] + tCASL_add[pstate] + tPDM[pstate] + RxEnDly_offset);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, pUserInputSim->tDQSCK =%d tSTAOFF=%d tCASL_add=%d tPDM=%d RxEnDly_offset=%f\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], pUserInputSim->tDQSCK,  tSTAOFF[pstate], tCASL_add[pstate],tPDM[pstate],RxEnDly_offset );
        float totFineStep = totPs / FineStepPs;
        RxEnDly_10to6 = totFineStep / 64.0;
        RxEnDly_5to0  = fmod (totFineStep , 64.0);
        if (RxEnDly_5to0 >= 64) {
            RxEnDly_10to6 = RxEnDly_10to6 + 1;
            RxEnDly_5to0 = RxEnDly_5to0 - 64;
            if(RxEnDly_10to6 >= 32) RxEnDly_10to6 = 31;
        }
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, UIps_RX=%f Programming RxEnDly_10to6=%d, Rxendly_5to0=%d\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], UIps_RX, RxEnDly_10to6, RxEnDly_5to0);


        RxEnDly[pstate] = (RxEnDly_10to6 << 6) | RxEnDly_5to0;

        phyrd_tdqs2dq_UiFractionUnits = (phyrd_tdqs2dq_ps * 64)/UIps_RX;
        RxClkDly_UiFractionUnits      = RxClkDly_UiFractionUnits_default - phyrd_tdqs2dq_UiFractionUnits;
        RxClkDly_coarse               = (RxClkDly_UiFractionUnits/64);
        RxClkDly_fine                 =  RxClkDly_UiFractionUnits - (RxClkDly_coarse*64);

        // Borrow one coarse delay into fine delay so RxClk tracking has margin for comepnsation
        // RxClkDly_fine lower than 16 fine delay needs to be checked if its enough
        if(RxClkDly_fine < 16 && RxClkDly_coarse > 0 ){
          RxClkDly_fine += 64;
          RxClkDly_coarse -= 1;
        }

        RxClk2UIDly_csr[pstate]       = (RxClkDly_coarse << 7) | RxClkDly_fine;
/*
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, setting phyrd_tdqs2dq_ps              to %d\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], phyrd_tdqs2dq_ps             );
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, setting phyrd_tdqs2dq_UiFractionUnits to %d\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], phyrd_tdqs2dq_UiFractionUnits);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, setting RxClkDly_UiFractionUnits      to %d\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], RxClkDly_UiFractionUnits     );
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, setting RxClkDly_coarse               to %d\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], RxClkDly_coarse              );
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, setting RxClkDly_fine                 to %d\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], RxClkDly_fine                );
*/
        if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming RxClkT2UIDlyTg0 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], RxClk2UIDly_csr[pstate]);
        if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming RxClkT2UIDlyTg1 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], RxClk2UIDly_csr[pstate]);
        if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming RxClkC2UIDlyTg0 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], RxClk2UIDly_csr[pstate]);
        if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming RxClkC2UIDlyTg1 to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], RxClk2UIDly_csr[pstate]);

        for (byte=0; byte<NumDbyte; byte++) {
            c_addr = byte << 12;
            if ( !dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte) ) {
                if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxEnDlyTg0_ADDR), RxEnDly[pstate]);
                if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxEnDlyTg1_ADDR), RxEnDly[pstate]);
            }
            for (lane=0; lane < 9; lane++) {
                r_addr = lane << 8;
                if ( !dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte) ) {
                    if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_RxClkT2UIDlyTg0_ADDR ), RxClk2UIDly_csr[pstate]);
                    if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_RxClkT2UIDlyTg1_ADDR ), RxClk2UIDly_csr[pstate]);
                    if (((mb1D[pstate].CsPresentChA & 0x1) >> 0) | ((mb1D[pstate].CsPresentChB & 0x1) >> 0)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_RxClkC2UIDlyTg0_ADDR),  RxClk2UIDly_csr[pstate]);
                    if (((mb1D[pstate].CsPresentChA & 0x2) >> 1) | ((mb1D[pstate].CsPresentChB & 0x2) >> 1)) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_RxClkC2UIDlyTg1_ADDR),  RxClk2UIDly_csr[pstate]);

                } // if ( !dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte) )
            } // lane
        } // c_addr


    /**
     *
     * Program RxDigStrbDly0/1[10:0] per P-State:
     *
     *         RxDigStrbDly[10:6] = ?
     *         RxDigStrbDly[5:0]  = ?
     *
     */






    uint16_t regData;
    /**
     *
     * Programming Seq0BGPR1/2/3 for LPDDR3 and LPDDR4
     *
     */
    int extraDly;

        extraDly=3; // LPDDR4


        int rl=0,wl=0; // computed read/write latencies.
        uint16_t mr_wls, mr_dbi_rd, mr_rl, mr_wl ; // extracted field from MR.
        mr_rl     = (mb1D[pstate].MR2_A0 & 0x07) >> 0;// RL[2:0]
        mr_wl     = (mb1D[pstate].MR2_A0 & 0x38) >> 3;// WL[5:3]
        mr_wls    = (mb1D[pstate].MR2_A0 & 0x40) >> 6;// WLS
        mr_dbi_rd = (mb1D[pstate].MR3_A0 & 0x40) >> 6;// DBI-RD
        dwc_ddrphy_phyinit_cmnt ("%s pstate=%d, mr_rl=%d mr_wl=%d mr_wls=%d mr_dbi_rd=%d \n", printf_header,pstate,mr_rl,mr_wl,mr_wls,mr_dbi_rd);
        switch (mr_dbi_rd<<3 | mr_rl ) {
            // DBI-RD Disabled
            case  0: rl =  6; break;
            case  1: rl = 10; break;
            case  2: rl = pUserInputBasic->DramDataWidth == 8 ? 16 : 14; break;
            case  3: rl = pUserInputBasic->DramDataWidth == 8 ? 22 : 20; break;
            case  4: rl = pUserInputBasic->DramDataWidth == 8 ? 26 : 24; break;
            case  5: rl = pUserInputBasic->DramDataWidth == 8 ? 32 : 28; break;
            case  6: rl = pUserInputBasic->DramDataWidth == 8 ? 36 : 32; break;
            case  7: rl = pUserInputBasic->DramDataWidth == 8 ? 40 : 36; break;
            // DBI-RD Enabled
            case  8: rl =  6; break;
            case  9: rl = 12; break;
            case 10: rl = pUserInputBasic->DramDataWidth == 8 ? 18 : 16; break;
            case 11: rl = pUserInputBasic->DramDataWidth == 8 ? 24 : 22; break;
            case 12: rl = pUserInputBasic->DramDataWidth == 8 ? 30 : 28; break;
            case 13: rl = pUserInputBasic->DramDataWidth == 8 ? 36 : 32; break;
            case 14: rl = pUserInputBasic->DramDataWidth == 8 ? 40 : 36; break;
            case 15: rl = pUserInputBasic->DramDataWidth == 8 ? 44 : 40; break;
            default:rl =  6;
        }
        switch (mr_wls<<3|mr_wl) {
            // DBI-RD Disabled
            case  0: wl =  4; break;
            case  1: wl =  6; break;
            case  2: wl =  8; break;
            case  3: wl = 10; break;
            case  4: wl = 12; break;
            case  5: wl = 14; break;
            case  6: wl = 16; break;
            case  7: wl = 18; break;
            // DBI-RD Enabled
            case  8: wl =  4; break;
            case  9: wl =  8; break;
            case 10: wl = 12; break;
            case 11: wl = 18; break;
            case 12: wl = 22; break;
            case 13: wl = 26; break;
            case 14: wl = 30; break;
            case 15: wl = 34; break;
            default: wl =  4;
        }
    

        // for ACSM
        regData=((rl-5+extraDly) << csr_ACSMRxEnDelay_LSB) | (0x8 << csr_ACSMRxEnWidth_LSB) ;
        dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tMASTER | csr_ACSMRxEnPulse_ADDR), regData);

        regData=((rl-5+extraDly) << csr_ACSMRxValDelay_LSB) | (0x8 << csr_ACSMRxValWidth_LSB) ;
        dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tMASTER | csr_ACSMRxValPulse_ADDR), regData);

	  if ((pUserInputBasic->DfiFreqRatio[pstate] == 0x1)&& (pUserInputBasic->Frequency[pstate] > 800))  {
	    regData=((wl-7+extraDly) << csr_ACSMTxEnDelay_LSB) | (0x1 << csr_ACSMTxEnWidth_LSB) ;
	  } else {
	    regData=((wl-5+extraDly) << csr_ACSMTxEnDelay_LSB) | (0x1 << csr_ACSMTxEnWidth_LSB) ;
	  }
        dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tMASTER | csr_ACSMTxEnPulse_ADDR), regData);
	  if ((pUserInputBasic->DfiFreqRatio[pstate] == 0x1)&& (pUserInputBasic->Frequency[pstate] > 800))  {
        regData=((wl-7+extraDly) << csr_ACSMWrcsDelay_LSB) | (0x1 << csr_ACSMWrcsWidth_LSB) ;
	  } else {
        regData=((wl-5+extraDly) << csr_ACSMWrcsDelay_LSB) | (0x1 << csr_ACSMWrcsWidth_LSB) ;
	  }
        dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tMASTER | csr_ACSMWrcsPulse_ADDR), regData);

        regData=(pUserInputAdvanced->WDQSExt) ?
                ((rl-5+extraDly-2) << csr_ACSMRdcsDelay_LSB) | (0xa << csr_ACSMRdcsWidth_LSB) :
                ((rl-5+extraDly) << csr_ACSMRdcsDelay_LSB) | (0x8 << csr_ACSMRdcsWidth_LSB) ;
        dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tMASTER | csr_ACSMRdcsPulse_ADDR), regData);

    /**
     *
     * Program HwtLpCsEnA and HwtLpCsEnB based on number of ranks per channel
     * Applicable only for LPDDR3 and LPDDR4.  These CSRs have no effect
     * for DDR3/4
     *
     * CSRs to program:
     *      HwtLpCsEnA
     *      HwtLpCsEnB
     *
     * User input dependencies:
     *      DramType
     *      NumCh
     *      NumRank_dfi0
     *      NumRank_dfi1
     *
     */
    int HwtLpCsEnA;
    int HwtLpCsEnB;

    // Channel A - 1'b01 if signal-rank, 2'b11 if dual-rank
    HwtLpCsEnA = pUserInputBasic->NumRank_dfi0 | 0x1;
    dwc_ddrphy_phyinit_cmnt ("%s Programming HwtLpCsEnA to 0x%x\n", printf_header, HwtLpCsEnA);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_HwtLpCsEnA_ADDR), HwtLpCsEnA);

    // Channel B - 1'b01 if signal-rank, 2'b11 if dual-rank
    // if DFI1 exists but disabled, NumRank_dfi0 is used to program CsEnB
    if (pUserInputBasic->NumCh == 2 && pUserInputBasic->NumActiveDbyteDfi1 == 0) {
        HwtLpCsEnB = pUserInputBasic->NumRank_dfi0 | 0x1;
        dwc_ddrphy_phyinit_cmnt ("%s Programming HwtLpCsEnB to 0x%x\n", printf_header, HwtLpCsEnB);
        dwc_ddrphy_phyinit_io_write16((tMASTER | csr_HwtLpCsEnB_ADDR), HwtLpCsEnB);
    } else if (pUserInputBasic->NumCh == 2 && pUserInputBasic->NumActiveDbyteDfi1 > 0) {
        HwtLpCsEnB = pUserInputBasic->NumRank_dfi1 | 0x1;
        dwc_ddrphy_phyinit_cmnt ("%s Programming HwtLpCsEnB to 0x%x\n", printf_header, HwtLpCsEnB);
        dwc_ddrphy_phyinit_io_write16((tMASTER | csr_HwtLpCsEnB_ADDR), HwtLpCsEnB);
    } else { // Disable Channel B
        HwtLpCsEnB = 0x0;
        dwc_ddrphy_phyinit_cmnt ("%s Programming HwtLpCsEnB to 0x%x\n", printf_header, HwtLpCsEnB);
        dwc_ddrphy_phyinit_io_write16((tMASTER | csr_HwtLpCsEnB_ADDR), HwtLpCsEnB);
    }


    /**
     * - Program PptDqsCntInvTrnTg0 and PptDqsCntInvTrnTg1
     *   - LPDDR4: Calculated based on DRAM tDQS2DQ and Frequency
     *   - LPDDR5: Calculated based on DRAM tWCK2DQI and Frequency
     * - Program PptWck2DqoCntInvTrnTg0 and PptWck2DqoCntInvTrnTg1 (LPDDR5 only)
     *   - Calculated based on DRAM tWCK2DQO and Frequency
     * - User input dependencies (LPDDR4):
     *   - user_input_sim_t.tDQS2DQ
     * - User input dependencies (LPDDR5):
     *   - user_input_sim_t.tWCK2DQI
     *   - user_input_sim_t.tWCK2DQO
     *   - user_input_basic_t.Frequency
     *
     * - Generic formula:
     *
     *          value = 65536 * (specified_usersim_delay_rank<rank>_chan<chan> * 2) / (2 * 2048 * UIps_int)
     *
     */
        int rank;
        int PptDqsCntInvTrn[2];

        UIps = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6 * 0.5;

        // Set per timing group
        for (rank=0; rank<NumRank_total; rank++) {

            if (rank > 1) break; // only Tg0 and Tg1 registers exist

            PptDqsCntInvTrn[rank] = ceil (65536 * (pUserInputSim->tDQS2DQ * 4) / (2 * 2048 * UIps) );
            dwc_ddrphy_phyinit_cmnt ("%s pUserInputSim->tDQS2DQ: %d\n", printf_header, pUserInputSim->tDQS2DQ);
            dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PptDqsCntInvTrnTg%d to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], rank, PptDqsCntInvTrn[rank]);

        } // rank

        for (byte=0; byte<NumDbyte; byte++) {
            c_addr = byte << 12;
            for (rank=0; rank<NumRank_total; rank++) {
                if (rank == 0)      dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_PptDqsCntInvTrnTg0_ADDR), PptDqsCntInvTrn[rank]);
                else if (rank == 1) dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_PptDqsCntInvTrnTg1_ADDR), PptDqsCntInvTrn[rank]);
            }
        } // byte


    /**
     *
     * - Program HwtCtrl based on dram type
     *
     *   - CSRs to program:
     *     - HwtCAMode.HwtLp3CAMode
     *     - HwtCAMode.HwtD4CAMode
     *     - HwtCAMode.HwtLp4CAMode
     *     - HwtCAMode.HwtD4AltCAMode
     *     - HwtCAMode.HwtCsInvert
     *     - HwtCAMode.HwtDBIInvert
     *
     * - Dependencies
     *   - userInputBasic.DramType
     *
     */
    int HwtCtrl;
    int HwtDBIInvert = 0;

    HwtDBIInvert = 1;

    HwtCtrl = (HwtDBIInvert << csr_HwtDBIInvert_LSB);

    dwc_ddrphy_phyinit_cmnt ("%s Programming HwtCtrl to 0x%x\n", printf_header, HwtCtrl);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_HwtCtrl_ADDR), HwtCtrl);



    /**
     *
     * Program DllGainCtl and AcDllLockParam based on Frequency
     *
     */
    int lcdlSeed;
    int wdAcDllLockParam;
    int AcDllGainIV;
    int AcDllGainTV;
    int wdDxDllLockParam;
    int DxDllGainIV;
    int DxDllGainTV;
    int wdDllGainCtl;
    // nominal stepsize, in units of tenths of a ps,
    // if nominal=2.3ps use 23
    int stepsize_x10=32;

    int AcFreq = pUserInputBasic->Frequency[pstate];



                         AcDllGainIV=0x00; AcDllGainTV=0x02;
    if(AcFreq >=  332) { AcDllGainIV=0x01; AcDllGainTV=0x03; }
    if(AcFreq >=  532) { AcDllGainIV=0x02; AcDllGainTV=0x04; }
    if(AcFreq >=  800) { AcDllGainIV=0x03; AcDllGainTV=0x05; }
    if(AcFreq >= 1200) { AcDllGainIV=0x03; AcDllGainTV=0x05; }
    if(AcFreq >= 1800) { AcDllGainIV=0x03; AcDllGainTV=0x06; }
    if(AcFreq >= 2200) { AcDllGainIV=0x03; AcDllGainTV=0x07; }


    uint16_t AcSeed= (1000000 * 10 *100) /(2*AcFreq * stepsize_x10 * 100); // *100/105 is to bias the seed low

    if(AcSeed > 511)  AcSeed = 511;
    if(AcSeed < 8     )  AcSeed = 8;

    wdAcDllLockParam = (csr_AcLcdlSeed0_MASK & (AcSeed << csr_AcLcdlSeed0_LSB));

    int DxFreq = pUserInputBasic->Frequency[pstate];

                         DxDllGainIV=0x00; DxDllGainTV=0x02;
    if(DxFreq >=  332) { DxDllGainIV=0x01; DxDllGainTV=0x03; }
    if(DxFreq >=  532) { DxDllGainIV=0x02; DxDllGainTV=0x04; }
    if(DxFreq >=  800) { DxDllGainIV=0x03; DxDllGainTV=0x05; }
    if(DxFreq >= 1200) { DxDllGainIV=0x03; DxDllGainTV=0x05; }
    if(DxFreq >= 1800) { DxDllGainIV=0x03; DxDllGainTV=0x06; }
    if(DxFreq >= 2200) { DxDllGainIV=0x03; DxDllGainTV=0x07; }

    uint16_t DxSeed= (1000000 * 10 *100) /(2*DxFreq * stepsize_x10 * 100); // *100/105 is to bias the seed low

    if(DxSeed > 511)  DxSeed = 511;
    if(DxSeed < 8     )  DxSeed = 8;

    wdDxDllLockParam = (csr_DxLcdlSeed0_MASK & (DxSeed << csr_DxLcdlSeed0_LSB));

    wdDllGainCtl = (csr_AcDllGainTV_MASK  & (AcDllGainTV << csr_AcDllGainTV_LSB)) | (csr_AcDllGainIV_MASK  & (AcDllGainIV << csr_AcDllGainIV_LSB)) |
                   (csr_DxDllGainTV_MASK  & (DxDllGainTV << csr_DxDllGainTV_LSB)) | (csr_DxDllGainIV_MASK  & (DxDllGainIV << csr_DxDllGainIV_LSB));

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, AcFreq=%dMHz, AC Programming DllGainCtl::AcDllGainIV=0x%x, AcDllGainTV=0x%x\n", printf_header, pstate, AcFreq, AcDllGainIV, AcDllGainTV);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, DxFreq=%dMHz, DX Programming DllGainCtl::DxDllGainIV=0x%x, DxDllGainTV=0x%x\n", printf_header, pstate, DxFreq, DxDllGainIV, DxDllGainTV);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, DX Programming DllGainCtl to 0x%x\n", printf_header, pstate, wdDllGainCtl);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DllGainCtl_ADDR), wdDllGainCtl);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, AC Programming AcDllLockParam::AcLcdlSeed0 to %d \n", printf_header, pstate, AcFreq, AcSeed);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, AC Programming AcDllLockParam to 0x%x\n", printf_header, pstate, AcFreq, wdAcDllLockParam);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_AcDllLockParam_ADDR), wdAcDllLockParam);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, DxFreq=%dMHz, DX Programming DxDllLockParam::DxLcdlSeed0 to %d \n", printf_header, pstate, DxFreq, DxSeed);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, DxFreq=%dMHz, DX Programming DxDllLockParam to 0x%x\n", printf_header, pstate, DxFreq, wdDxDllLockParam);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DxDllLockParam_ADDR), wdDxDllLockParam);

   /**
    * - Program PllCtrl3 and PllDacValIn:
    *   Set PllForceCal to 1 and PllDacValIn to some arbitrary value
    *
    */
    uint16_t dacval_in = 0x10;

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PllDacValIn to 0x%x\n", printf_header, pstate, pUserInputBasic->Frequency[pstate], dacval_in);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_PllDacValIn_ADDR), (dacval_in << csr_PllDacValIn_LSB));

    /**
     * - Program RxReplicaDllLockParam:
     *   - Dependencies:
     *     - user_input_basic.Frequency
     *     - user_input_basic.DfiFreqRatio (LPDDR5 only)
     * - Program RxReplicaDllGainCtl:
     *   - Fields:
     *     - RxReplicaDllGainIV
     *     - RxReplicaDllGainTV
     *     - wdRxReplicaDllGainCtl
     */

    uint8_t RxReplicaDllGainIV;
    uint8_t RxReplicaDllGainTV;
    uint16_t wdRxReplicaDllGainCtl;
    uint16_t wdRxReplicaDllLockParam;

        uint16_t dataClkFreq = pUserInputBasic->Frequency[pstate];

                                  RxReplicaDllGainIV=0x00; RxReplicaDllGainTV=0x02;
        if(dataClkFreq >=  332) { RxReplicaDllGainIV=0x01; RxReplicaDllGainTV=0x03; }
        if(dataClkFreq >=  532) { RxReplicaDllGainIV=0x02; RxReplicaDllGainTV=0x04; }
        if(dataClkFreq >=  800) { RxReplicaDllGainIV=0x03; RxReplicaDllGainTV=0x05; }
        if(dataClkFreq >= 1200) { RxReplicaDllGainIV=0x03; RxReplicaDllGainTV=0x05; }
        if(dataClkFreq >= 1800) { RxReplicaDllGainIV=0x03; RxReplicaDllGainTV=0x06; }
        if(dataClkFreq >= 2200) { RxReplicaDllGainIV=0x03; RxReplicaDllGainTV=0x07; }

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, RxReplica Programming RxReplicaDllGainCtl::RxReplicaDllGainIV=0x%x, RxReplicaDllGainTV=0x%x\n", printf_header, pstate, RxReplicaDllGainIV, RxReplicaDllGainTV);

        lcdlSeed= (1000000 * 10 *100) /(2*dataClkFreq * stepsize_x10 * 100); // *100/105 is to bias the seed low

        if(lcdlSeed > 511)  lcdlSeed = 511;
        if(lcdlSeed < 8  )  lcdlSeed = 8;

        wdRxReplicaDllLockParam = (csr_RxReplicaLcdlSeed_MASK & (lcdlSeed << csr_RxReplicaLcdlSeed_LSB));

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, RxReplica Programming RxReplicaDllLockParam::RxReplicaLcdlSeed to %d \n", printf_header, pstate, lcdlSeed);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, RxReplica Programming RxReplicaDllLockParam to 0x%x\n", printf_header, pstate, wdRxReplicaDllLockParam);
        dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_RxReplicaDllLockParam_ADDR), wdRxReplicaDllLockParam);

        wdRxReplicaDllGainCtl = (csr_RxReplicaDllGainTV_MASK & (RxReplicaDllGainTV << csr_RxReplicaDllGainTV_LSB)) |
                                (csr_RxReplicaDllGainIV_MASK & (RxReplicaDllGainIV << csr_RxReplicaDllGainIV_LSB));

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, RxReplica Programming RxReplicaDllGainCtl to 0x%x\n", printf_header, pstate, wdRxReplicaDllGainCtl);
        dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_RxReplicaDllGainCtl_ADDR), wdRxReplicaDllGainCtl);

        /**
         * - Program RxReplicaPathPhaseCsrs<i>
         *   - Fields:
         *     - wdRxReplicaPathPhase
         *     - RxReplicaPathPhaseCsrs
         *   - Dependencies:
         *     - user_input_sim.tPHY_tDQS2DQ
         */

        uint16_t wdRxReplicaPathPhase[5] = {0};
        uint16_t RxReplicaPathPhaseCsrs[] = {csr_RxReplicaPathPhase0_ADDR,
                                             csr_RxReplicaPathPhase1_ADDR,
                                             csr_RxReplicaPathPhase2_ADDR,
                                             csr_RxReplicaPathPhase3_ADDR,
                                             csr_RxReplicaPathPhase4_ADDR};

        UIps = (1.0 / pUserInputBasic->Frequency[pstate]) * 1E6 * 0.5;
        for (byte=0; byte<NumDbyte; byte++)
          {
            c_addr = byte << 12;
            for ( uint8_t phase = 0; phase<5; phase++)
              {
                wdRxReplicaPathPhase[phase] = (((phase*UIps - phyrd_tdqs2dq_ps)/(stepsize_x10*0.1)) < 1 ) ? 0x0 :
                                              (((phase*UIps - phyrd_tdqs2dq_ps)/(stepsize_x10*0.1)) > 0x1ff ) ? 0x1ff :
                                               ((phase*UIps - phyrd_tdqs2dq_ps)/(stepsize_x10*0.1));

                dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming DBYTE%d.RxReplicaPathPhase%d to 0x%x\n", printf_header, pstate, byte, phase, wdRxReplicaPathPhase[phase]);
                dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | RxReplicaPathPhaseCsrs[phase]), wdRxReplicaPathPhase[phase]);
              }
          }

        /**
         * - Program RxReplicaCtl01::RxReplicaSelPathPhase
         */
        uint16_t RxRepPhSel = (wdRxReplicaPathPhase[0] > (lcdlSeed/2)) ? 0x0 :
                              (wdRxReplicaPathPhase[1] > (lcdlSeed/2)) ? 0x1 :
                              (wdRxReplicaPathPhase[2] > (lcdlSeed/2)) ? 0x2 :
                              (wdRxReplicaPathPhase[3] > (lcdlSeed/2)) ? 0x3 : 0x4;

        regData = ( RxRepPhSel << csr_RxReplicaSelPathPhase_LSB );
            for (byte=0; byte<NumDbyte; byte++)
              {
                c_addr = byte << 12;
                dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming DBYTE%d.RxReplicaCtl01::RxReplicaSelPathPhase to 0x%x\n", printf_header, pstate, byte, regData);
                dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxReplicaCtl01_ADDR), regData);
              }

        /**
        * - Program RxReplicaCtl03
        */
        for (byte=0; byte<NumDbyte; byte++)
          {
            float lcdlSeed_f = lcdlSeed;
            float trainedRepilcaUI_f = wdRxReplicaPathPhase[RxRepPhSel];
            c_addr = byte << 12;
            regData = (trainedRepilcaUI_f/lcdlSeed_f)*64;
            dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming DBYTE%d.RxReplicaCtl03 to 0x%x\n", printf_header, pstate, byte, regData);
            dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxReplicaCtl03_ADDR), regData);

        /**
         * - Program RxReplicaCtl04:
         *   - Fields
         *     - RxReplicaTrackEn
         *     - RxReplicaLongCal
         *     - RxReplicaStride
         *   - Dependencies:
         *     - user_input_advanced.RxClkTrackEn
         */
            uint16_t RxReplicaTrackEn = (pUserInputAdvanced->RxClkTrackEn[pstate] == 1) ? 1: 0;
            uint16_t RxReplicaCtl = (RxReplicaTrackEn << csr_RxReplicaTrackEn_LSB)
                      | (               1 << csr_RxReplicaLongCal_LSB) // long cal during boot
                      | (               1 << csr_RxReplicaStride_LSB);

            dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming  DBYTE%d.RxReplicaCtl04 to 0x%x\n", printf_header, pstate, byte, RxReplicaCtl);

            dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxReplicaCtl04_ADDR), RxReplicaCtl);
          }


    if (!devinit) {
        /**
         *
         * Program SingleEndedMode based on user input
         *
         */
        uint16_t semCK   = 0;
        uint16_t semWDQS = 0;
        uint16_t semWCK  = 0;
      
        // Set the singleEndedMode variable based off the Mode Register input.
      
        uint16_t singleEndedModeCK   = (mb1D[pstate].MR51_A0 & 0x8) >> 3;
        uint16_t singleEndedModeWDQS = (mb1D[pstate].MR51_A0 & 0x4) >> 2;
      
      
        switch ( singleEndedModeCK ) {
            case 0  : break;
            case 1  : semCK = 1; break;
            default : dwc_ddrphy_phyinit_assert(0, "%s Invalid singleEndedModeCK = %d, pstate = %d\n" , printf_header, singleEndedModeCK, pstate); 
        }
      
        switch ( singleEndedModeWDQS ) {
            case 0  : break;
            case 1  : semWDQS = 1; break;
            default : dwc_ddrphy_phyinit_assert(0, "%s Invalid singleEndedModeWDQS = %d, pstate = %d\n" , printf_header, singleEndedModeWDQS, pstate); 
        }
      
      
      
        if (pUserInputBasic->Lp4xMode == 0 && ( singleEndedModeWDQS || singleEndedModeCK ))
          dwc_ddrphy_phyinit_assert(0, "%s inconsistent PHY programming.  singleEndedMode is used for Pstate %d, but Lp4xMode!=0x1.\n" , printf_header, pstate); 
      
        uint16_t singleEndedMode = ( (semCK   << csr_SingleEndedCK_LSB)  & csr_SingleEndedCK_MASK  )
                                 | ( (semWDQS << csr_SingleEndedDQS_LSB) & csr_SingleEndedDQS_MASK )
                                 | ( (semWCK  << csr_SingleEndedWCK_LSB) & csr_SingleEndedWCK_MASK );
      
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming SingleEndedMode::SingleEndedCK to 0x%x\n", printf_header, pstate, semCK);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming SingleEndedMode::SingleEndedDQS to 0x%x\n", printf_header, pstate, semWDQS);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming SingleEndedMode::SingleEndedWCK to 0x%x\n", printf_header, pstate, semWCK);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming SingleEndedMode to 0x%x\n", printf_header, pstate, singleEndedMode);
        dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_SingleEndedMode_ADDR), singleEndedMode);
    }

    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_progCsrSkipTrainPsLoop()\n", printf_header);
}
// End of dwc_ddrphy_phyinit_progCsrSkipTrainPsLoop()

/** @} */