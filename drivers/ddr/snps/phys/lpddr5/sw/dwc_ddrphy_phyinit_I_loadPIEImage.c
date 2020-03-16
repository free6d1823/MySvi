/** \file
 * \brief implements Step I of initialization sequence
 *
 * This file contains the implementation of dwc_ddrphy_phyinit_I_initPhyConfig
 * function.
 *
 *  \addtogroup SrcFunc
 *  @{
 */
#include "dwc_ddrphy_phyinit.h"

int acsmClkRatio = 0 ;
uint16_t acsmInstPtr = 0;
/** \brief Loads registers after training
 *
 * This function programs the PHY Initialization Engine (PIE) instructions and
 * the associated registers.
 *
 * \return void
 *
 * Detailed list of registers programmed by this function:
 */
void dwc_ddrphy_phyinit_I_loadPIEImage (phyinit_config_t* phyctx) {

    //user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    //user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;

    uint8_t prog_csr  = (pRuntimeConfig->initCtrl & 0x1) >> 0;
    uint8_t skip_pie  = (pRuntimeConfig->initCtrl & 0x10) >> 4;
    uint16_t regData;

    char *printf_header;
    printf_header = " [phyinit_I_loadPIEImage]";

    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_I_loadPIEImage() %d\n", printf_header,prog_csr);

    if (skip_pie)
      {
        dwc_ddrphy_phyinit_cmnt ("%s skip_pie flag set. Skipping dwc_ddrphy_phyinit_I_loadPIEImagePsLoop\n", printf_header);
        return;
      }


    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt (" (I) Load PHY Init Engine Image \n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("Load the PHY Initialization Engine memory with the provided initialization sequence.\n");
    dwc_ddrphy_phyinit_cmnt ("See PhyInit App Note for detailed description and function usage\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt (" For LPDDR3/LPDDR4/LPDDR5, this sequence will include the necessary retraining code.\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("\n");

    // reset the acsm instruction Ptr.
    acsmInstPtr = 0;

    dwc_ddrphy_phyinit_cmnt (" Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0. \n");
    dwc_ddrphy_phyinit_cmnt (" This allows the memory controller unrestricted access to the configuration CSRs. \n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x0);

    dwc_ddrphy_phyinit_cmnt ("%s Programming PIE Production Code\n", printf_header);

    dwc_ddrphy_phyinit_LoadPieProdCode(phyctx);

    /**
     * - Registers: PieCfgVec and PieInitVecSel
     *   - Program PIE initialization start vector
     */

    dwc_ddrphy_phyinit_io_write16((tDRTUB | csr_PieInitVecSel_ADDR), 0x5061);
    dwc_ddrphy_phyinit_io_write16((tDRTUB | csr_PieVecCfg_ADDR),     0xbedc);

    dwc_ddrphy_phyinit_PieFlags(phyctx, prog_csr);

    /**
     * - Registers: FspSkipList
     *   - Program encoding that don't update FspState
     */
    regData = 0x17 | (0x1f <<5);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_FspSkipList_ADDR), regData);

    /**
     * Program Training Hardware Registers for mission mode retraining
     * and DRAM drift compensation algorithm.
     *
     */
    dwc_ddrphy_phyinit_cmnt ("%s Programing Training Hardware Registers for mission mode retraining\n", printf_header);
    if (prog_csr == 0) {
        dwc_ddrphy_phyinit_cmnt ("%s Enabling Phy Master Interface for DRAM drift compensation\n", printf_header);
        dwc_ddrphy_phyinit_ProgPPT(phyctx);
    }

    regData = csr_HwtCs0Val0_MASK;
    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    if ( pUserInputBasic->NumRank_dfi0 == 2) regData |= csr_HwtCs1Val0_MASK;

    if ( pUserInputBasic->NumCh > 1)
      {
        regData |= csr_HwtCs0Val1_MASK;
        if ( pUserInputBasic->NumRank_dfi1 == 2) regData |= csr_HwtCs1Val1_MASK;
      }

    dwc_ddrphy_phyinit_io_write16((c0 | tMASTER | csr_HwtControlVal_ADDR), regData);

    /// - ACSMOuterLoopRepeatCnt
    dwc_ddrphy_phyinit_io_write16((c0 | tMASTER | csr_ACSMOuterLoopRepeatCnt_ADDR), 0xd);

    /// - FspState
    dwc_ddrphy_phyinit_io_write16((c0 | tMASTER | csr_FspState_ADDR), 0xffff);

    /// - Register:
    //       - ZCalReset
    //       - ZCalRun
    ///   - Prepare the calibration controller for mission mode.
    ///     Turn on calibration and hold idle until dfi_init_start is asserted sequence is triggered.
    dwc_ddrphy_phyinit_cmnt ("%s Turn on calibration and hold idle until dfi_init_start is asserted sequence is triggered.\n", printf_header);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalReset to 0x%x\n", printf_header, 0x1);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalRun to 0x%x\n", printf_header, 0x1);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_ZCalReset_ADDR), 0x1);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_ZCalRun_ADDR), 0x1);


   /**
    * At the end of this function, PHY Clk gating register UcclkHclkEnables is
    * set for mission mode.  Additionally APB access is Isolated by setting
    * MicroContMuxSel.
    */
    dwc_ddrphy_phyinit_cmnt ("%s Disabling Ucclk (PMU)\n", printf_header);
    dwc_ddrphy_phyinit_userCustom_io_write16((tDRTUB | csr_UcclkHclkEnables_ADDR), csr_HclkEn_MASK);

    dwc_ddrphy_phyinit_cmnt ("%s Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. \n", printf_header);
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x1);

    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_I_loadPIEImage()\n", printf_header);

}

/** \brief Loads registers after training
 *
 * This is a helper function to program PPT registers.It is called by dwc_ddrphy_phyinit_I_loloadPIEImage().
 *
 * \return void
 *int
 * Detailed list of registers programmed by this function:
 */
void dwc_ddrphy_phyinit_ProgPPT(phyinit_config_t* phyctx) {

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;

    //char *printf_header;
    //printf_header     = "// [phyinit_I_loadPIEImage]";
    uint16_t regData;


    /// - Register: DtsmGoodBar
    ///   - Dependencies: NumDbyte
    int NumDbyte = pUserInputBasic->NumCh * pUserInputBasic->NumDbytesPerCh ;
    unsigned int c_addr;
    unsigned int byte;
    for (byte=0; byte < NumDbyte ; byte++) { // for each chiplet
        c_addr = byte*c1;
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_DtsmGoodBar_ADDR), 0x1); // [15:0] good_bar;

        regData=(csr_DtsmStaticCmpr_MASK | csr_DtsmStaticCmprVal_MASK);

    /// - Register: DtsmByteCtrl1, DtsmErrBar
    ///   - Fields:
    ///     - DtsmStaticCmpr
    ///     - DtsmStaticCmprVal
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_DtsmByteCtrl1_ADDR), regData);
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_DtsmErrBar_ADDR), 0x1); // [15:0] bad_bar;

    /// - Register: TrainingParam
    ///   - Fields:
    ///     - EnDynRateReduction
    ///     - RollIntoCoarse
    ///     - IncDecRate
        regData = (csr_EnDynRateReduction_MASK | csr_RollIntoCoarse_MASK| (0x3 << csr_IncDecRate_LSB));
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_TrainingParam_ADDR), regData);

    /// - Register: PptRxEnEvnt
    ///   - Fields:
    ///     - TrainEnRxEn
    ///   - Dependencies:
    ///     - user_input_advanced.DisableRetraining
    ///     - user_input_advanced.EnRxDqsTracking
        regData = 0;

        if (pUserInputAdvanced->DisableRetraining == 0) {

            // Only allow TrainEnRxEn if EnRxDqsTracking is not enabled
            uint8_t tracking = 0;
            for(int pstate=0 ; pstate<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE ; pstate++) {
                
                if ((pUserInputBasic->CfgPStates & (0x1<<pstate)) == 0) continue;

                if (pUserInputAdvanced->EnRxDqsTracking[pstate] != 0) {
                    tracking = 1;
                    break;
                }
            }

            if (tracking == 0) {
                regData |= csr_TrainEnRxEn_MASK;
            }
        }
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_PptRxEnEvnt_ADDR), regData);

    /// - Register: DtsmLaneCtrl0
    ///   - Fields:
    ///     - DtsmEnb
        regData=(0x1 << csr_DtsmEnb_LSB );
        dwc_ddrphy_phyinit_io_write16((c_addr | i0 | tDBYTE | csr_DtsmLaneCtrl0_ADDR), regData);

    } // for byte


}

/** \brief Programs PIE group disable flags.
 *
 * This is a helper function to program PIE Group Flag registers.It is called by dwc_ddrphy_phyinit_I_loloadPIEImage().
 *
 * \return void
 *
 * Detailed list of registers programmed by this function:
 */
void dwc_ddrphy_phyinit_PieFlags(phyinit_config_t* phyctx, int prog_csr) {

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;

    char *printf_header;
    printf_header = " [phyinit_I_loadPIEImage]";
    uint16_t regData;

    /**
     * - Registers: Seq0BDisableFlag0 Seq0BDisableFlag1 Seq0BDisableFlag2
     *   Seq0BDisableFlag3 Seq0BDisableFlag4 Seq0BDisableFlag5
     *   - Program PIE Instruction Disable Flags
     *   - Dependencies:
     *     - user_input_advanced.DisableRetraining
     *     - prog_csr
     *     - user_input_basic.Frequency
     */
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag0_ADDR), 0x0000);
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag1_ADDR), 0x0177);
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag2_ADDR), 0x0060);
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag3_ADDR), 0x7910);
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag4_ADDR), 0x3156);
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag5_ADDR), 0xCFBD);

    int freqThreshold = pUserInputBasic->DfiFreqRatio[0] == 1 ? 166 : 83;
    if(prog_csr==1 || pUserInputAdvanced->DisableRetraining || pUserInputBasic->Frequency[0] < freqThreshold) {
        dwc_ddrphy_phyinit_cmnt ("%s Disabling PMI & DRAM drift compensation. (prog_csr=%d, DisableRetraining=%d, Frequency[0]=%d) \n",
                printf_header, prog_csr, pUserInputAdvanced->DisableRetraining, pUserInputBasic->Frequency[0]);
        dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag6_ADDR), 0xffff);
    } else {
        dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag6_ADDR), 0x2860);
    }

    regData = ( pUserInputBasic->NumPStates < 3) ? 0xffff : 0x0110;
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag7_ADDR), regData);

    regData =  ( pUserInputBasic->NumPStates < 3) ? 0x110 : 0xffff;
    dwc_ddrphy_phyinit_io_write16((tINITENG | csr_Seq0BDisableFlag8_ADDR), regData);
  } // End of dwc_ddrphy_phyinit_PieFlags


/** \brief helper function to write MR instructions
 *
 * This is a helper function to program ACSM runtime instructions.
 *
 * \return void
 *
 * Detailed list of registers programmed by this function:
 */
void dwc_ddrphy_mr_inst(uint8_t mrNum,  //!< Which MR number to write to
                        uint8_t mrVal,  //!< Data of the MR to write
                        uint8_t mrCs,     //!< drives the cs pins
                        uint16_t dly
                         )
{
    char *printf_header;
    printf_header = " [dwc_ddrphy_mr_inst]";

    //dwc_ddrphy_phyinit_cmnt ("%s mrNum %d \n", printf_header,mrNum);
    //dwc_ddrphy_phyinit_cmnt ("%s mrVal %d \n", printf_header, mrVal);
    //dwc_ddrphy_phyinit_cmnt ("%s mrCs %d \n", printf_header, mrCs);
    //dwc_ddrphy_phyinit_cmnt ("%s dly %d \n", printf_header, dly);
    uint16_t addr[2];
    uint16_t p[4];
    uint16_t cs[2];

    p[0]= 0x58; // MRW-1
    p[1]= mrNum; // MA[6:0]
    p[2]= 0x8 | (mrVal & 0x80) >> 1; // MRW-2 + OP7
    p[3]= mrVal & 0x7F; // OP[6:even0]

    addr[0]  = (p[1] & 0x7F) << 7 | (p[0] & 0x7F);
    addr[1]  = (p[3] & 0x7F) << 7 | (p[2] & 0x7F);

    cs[0]= mrCs&0x3;
    cs[1]= mrCs&0x3;

    //dwc_ddrphy_phyinit_cmnt ("%s test2\n", printf_header);
    uint16_t acsm_addr = acsmInstPtr;
    uint16_t ac_instr[8]= {0};
#define ACSM_ADDR_MASK      0x3fff
#define ACSM_CS_MASK        0x3
    // even
    ac_instr[0] = ((cs[0] & ACSM_CS_MASK) << 14) | (addr[0] & ACSM_ADDR_MASK) ;
    ac_instr[1] = 0;
    ac_instr[2] = 0;
    ac_instr[3] = 0;

    // odd
    ac_instr[4] = ((cs[1] & ACSM_CS_MASK) << 14) | (addr[1] & ACSM_ADDR_MASK) ;
    ac_instr[5] = 0;
    ac_instr[6] = 0;
    ac_instr[7] = 0;
    //dwc_ddrphy_phyinit_cmnt ("%s test3\n", printf_header);
    uint16_t x;
    for (x=0;x<8;x++)
     {
       //dwc_ddrphy_phyinit_cmnt("%s addr=0x%x\n",printf_header, acsm_addr);
       //dwc_ddrphy_phyinit_cmnt("%s addr=0x%x\n",printf_header,  x);
       //dwc_ddrphy_phyinit_cmnt("%s dat=0x%x\n",printf_header,ac_instr[x]);
       dwc_ddrphy_phyinit_io_write16((acsm_addr | 0x41000) + x,ac_instr[x]);
     }
    dwc_ddrphy_phyinit_cmnt("%s dly = %d\n",printf_header, dly);
    int cnt = dly >> 1;
    for (x=8;x<16;x++)
      {
        if (x==11 && dly>2)
          {
            dwc_ddrphy_phyinit_io_write16((acsm_addr | 0x41000) + x, (cnt&0x07)<<12 | 0xb00);
          }
        else if (x==15)
          {
            dwc_ddrphy_phyinit_io_write16((acsm_addr | 0x41000) + x, (cnt&0xf8)<<7);
          }
        else
          {
            dwc_ddrphy_phyinit_io_write16((acsm_addr | 0x41000) + x,0);
          }
      }

    //dwc_ddrphy_phyinit_cmnt ("%s test6\n", printf_header);
    acsmInstPtr += 16;
    return ;
}
/** \brief returns the slowest tck among all pstates
 */
/*
uint32_t getFastestCk(phyinit_config_t* phyctx)
{
    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    uint32_t ret=0;
    uint32_t maxFreq=10000;
    for (int i=0;i<=(pUserInputBasic->NumPStates);i++)
      {
        maxFreq = (pUserInputBasic->Frequency[i] > maxFreq ) ? pUserInputBasic->Frequency[i] : maxFreq ;
      }
    ret = 1000000/maxFreq;
    return ret;
}*/
/** \brief Programs required initialization registers after trianing firmware execution.
*/
void dwc_ddrphy_phyinit_I_loadPIEImagePsLoop (phyinit_config_t* phyctx) {

    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_I_loadPIEImagePsLoop]";
    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_I_loadPIEImagePsLoop() \n", printf_header);

    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    uint8_t skip_pie  = (pRuntimeConfig->initCtrl & 0x10) >> 4;

    if (skip_pie)
      {
        dwc_ddrphy_phyinit_cmnt ("%s skip_pie flag set. Skipping dwc_ddrphy_phyinit_I_loadPIEImagePsLoop\n", printf_header);
        return;
      }

    dwc_ddrphy_phyinit_regInterface(setGroup,0,0);

    //dwc_ddrphy_phyinit_cmnt ("%s test1\n", printf_header);
    /// - Program ACSM runtime MRW instructions.
    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    uint32_t pstate  = pRuntimeConfig->curPState;
    PMU_SMB_LPDDR5_1D_t* mb1D = phyctx->mb_LPDDR5_1D;

    uint32_t p_addr   = pUserInputBasic->NumPStates <3 ? pstate << 20 : p0;
    uint8_t  NumDbyte = pUserInputBasic->NumCh * pUserInputBasic->NumDbytesPerCh ;

    uint8_t byte;
    uint32_t c_addr;

    if (pUserInputBasic->NumPStates > 2) acsmInstPtr=0;
    uint16_t start = (pUserInputBasic->NumPStates < 3) ? acsmInstPtr/4 : 0;
    uint8_t trgtPs = (pUserInputBasic->NumPStates < 3 && pstate==1) ? 0 :
                     (pUserInputBasic->NumPStates < 3 && pstate==0) ? 1 :  pstate;
    uint8_t cs = (pUserInputBasic->NumRank == 2) ? 0xf : 0x5; // for 2CK commands
    uint16_t tck_ps = 1000000/pUserInputBasic->Frequency[pstate];//getSlowestCK(phyctx);
    uint16_t dly = 10000/tck_ps + 1; // 10ns in counts
    if (dly>2) dly -= 2;
    if (dly<3) dly = 3;

    if (dly > 100)
        dwc_ddrphy_phyinit_assert(0,"%s Unexpected dly value. dly=%d\n", printf_header, dly);

    //dwc_ddrphy_phyinit_cmnt ("%s test2\n", printf_header);
    dwc_ddrphy_phyinit_cmnt ("%s MR1=0x%x\n", printf_header, mb1D[trgtPs].MR1_A0);
    dwc_ddrphy_mr_inst(19,mb1D[trgtPs].MR19_A0,cs,dly); // 
    dwc_ddrphy_mr_inst(18,mb1D[trgtPs].MR18_A0,cs,dly);
    dwc_ddrphy_mr_inst( 1,mb1D[trgtPs].MR1_A0,cs,dly);
    dwc_ddrphy_mr_inst( 2,mb1D[trgtPs].MR2_A0,cs,dly);
    dwc_ddrphy_mr_inst( 3,mb1D[trgtPs].MR3_A0,cs,dly);
    dwc_ddrphy_mr_inst(10,mb1D[trgtPs].MR10_A0,cs,dly);
    dwc_ddrphy_mr_inst(11,mb1D[trgtPs].MR11_A0,cs,dly);
    dwc_ddrphy_mr_inst(17,mb1D[trgtPs].MR17_A0,cs,dly);
    dwc_ddrphy_mr_inst(20,mb1D[trgtPs].MR20_A0,cs,dly);
    dwc_ddrphy_mr_inst(22,mb1D[trgtPs].MR22_A0,cs,dly);
    dwc_ddrphy_mr_inst(30,mb1D[trgtPs].MR30_A0,cs,dly);
    dwc_ddrphy_mr_inst(41,mb1D[trgtPs].MR41_A0,cs,dly);

    // DFE bring-up
    dwc_ddrphy_mr_inst(24,mb1D[trgtPs].MR24_A0,cs,dly);

    //dwc_ddrphy_phyinit_cmnt ("%s test3\n", printf_header);
    uint32_t p = (pUserInputBasic->NumPStates < 3 && pstate ==1 ) ? p1 : p0;
    dwc_ddrphy_phyinit_io_write16 ((p | tMASTER | csr_ACSMStartAddr_ADDR), start);
    dwc_ddrphy_phyinit_io_write16 ((p | tMASTER | csr_ACSMStopAddr_ADDR),  (acsmInstPtr/4)-1 );

    /*
     * - Program ACSMWckFreeRunMode
     *   - Dependencies:
     *     - mb1D[pstate].MR18_A0
     */
    uint16_t regData = (mb1D[pstate].MR18_A0 & 0x10) ? 0x1 : 0x0;
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming ACSMWckFreeRunMode to 0x%x\n", printf_header, pstate, regData);
    dwc_ddrphy_phyinit_io_write16((p | tMASTER | csr_ACSMWckFreeRunMode_ADDR), regData);

    /*
     * - Program ACSMRptCntDbl
     *   - Dependencies:
     *     - user_input_basic.Frequency[]
     */
    uint16_t CKR = mb1D[pstate].MR18_A0 & 0x80 >> 7;
    regData = (CKR == 0x0 ) ? 0x1 : 0x0;
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming ACSMRptCntDbl to 0x%x\n", printf_header, pstate, regData);
    // currently unused.
    dwc_ddrphy_phyinit_io_write16 ((p | tINITENG | csr_Seq0BGPR2_ADDR ), regData);
    dwc_ddrphy_phyinit_regInterface(setGroup,0,2);

    /*
     * - Program ACSMRptCntOverride
     *   - Dependencies:
     *     - user_input_basic.Frequency[]
     */
    dwc_ddrphy_phyinit_io_write16 ((p | tMASTER | csr_ACSMRptCntOverride_ADDR), dly>>1);

    /// - RxReplicaCtl04
    uint16_t RxReplicaTrackEn = (pUserInputAdvanced->RxClkTrackEn[pstate] == 1) ? 1: 0;
    uint16_t RxReplicaCtl = (RxReplicaTrackEn << csr_RxReplicaTrackEn_LSB)
                          | (               0 << csr_RxReplicaLongCal_LSB) // switch to short cal during mission mode
                          | (               1 << csr_RxReplicaStride_LSB);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming RxReplicaCtl04 to 0x%x\n", printf_header, pstate, RxReplicaCtl);
    p_addr = p_addr;

    for (byte=0; byte<NumDbyte; byte++) {
        c_addr = c1 * byte;
        dwc_ddrphy_phyinit_io_write16((p | c_addr | tDBYTE | csr_RxReplicaCtl04_ADDR), RxReplicaCtl);
    }

    return;
  }// End of  dwc_ddrphy_phyinit_I_loadPIEImage (phyinit_config_t* phyctx) {
/** @} */
