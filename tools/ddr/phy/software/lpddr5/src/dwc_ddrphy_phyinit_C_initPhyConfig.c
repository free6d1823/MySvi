/** 
 * \file
 * \brief implements Step C of initialization sequence
 *
 * This file contains the implementation of dwc_ddrphy_phyinit_C_initPhyConfig
 * function.
 *
 * \addtogroup SrcFunc
 * @{
 */
#include <stdlib.h>
#include <math.h>
#include "dwc_ddrphy_phyinit.h"

/** \brief implements Step C of initialization sequence
 *
 * This function programs majority of PHY Non-Pstate configuration registers based
 * on data input into PhyInit data structures.
 * 
 * This function programs PHY configuration registers based on information
 * provided in the PhyInit data structures (userInputBasic, userInputAdvanced).
 * The user can overwrite the programming of this function by modifying
 * dwc_ddrphy_phyinit_userCustom_customPreTrain().  Please see
 * dwc_ddrphy_phyinit_struct.h for PhyInit data structure definition.
 *
 * \return void
 *
 * List of registers programmed by this function:
 */
void dwc_ddrphy_phyinit_C_initPhyConfig (phyinit_config_t* phyctx)
  {
    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    PMU_SMB_LPDDR5_1D_t* mb1D = phyctx->mb_LPDDR5_1D;

    char *printf_header;
    printf_header = " [phyinit_C_initPhyConfig]";

    dwc_ddrphy_phyinit_cmnt ("\n\n");
    dwc_ddrphy_phyinit_cmnt ("##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt (" Step (C) Initialize PHY Configuration \n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt (" Load the required PHY configuration registers for the appropriate mode and memory configuration\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n\n");

    int achn;
    int c_addr;
    int byte;
    
    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_C_initPhyConfig()\n", printf_header);

    // Initialize the register interface
    dwc_ddrphy_phyinit_initReg(phyctx);

    int NumDbyte = pUserInputBasic->NumCh * pUserInputBasic->NumDbytesPerCh ;
    int NumAchn  = pUserInputBasic->NumCh;

    /**
     * - Program PorControl::PwrOkDlyCtrl
     *   - Assert PwrOkDlyCtrl to enable the PwrOk_{VDD, VDDQ, VAA}, as part of power ramp-up
    */
    int PorControl;        
    dwc_ddrphy_phyinit_cmnt ("%s Programming PorControl::PwrOkDlyCtrl to 1'b1\n", printf_header);
    PorControl = 0x0001 << csr_PwrOkDlyCtrl_LSB;    
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_PorControl_ADDR), PorControl);

 
    /**
     * - Program DfiMode:
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.NumActiveDbyteDfi0 
     *     - user_input_basic.NumActiveDbyteDfi1 
     */
    uint16_t DfiMode=0x0;
    if (pUserInputBasic->NumActiveDbyteDfi0 !=0 ) DfiMode |= csr_Dfi0Enable_MASK;
    if (pUserInputBasic->NumActiveDbyteDfi1 !=0 ) DfiMode |= csr_Dfi1Enable_MASK;
    
    dwc_ddrphy_phyinit_cmnt ("%s Programming DfiMode to 0x%x\n", printf_header, DfiMode);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_DfiMode_ADDR), DfiMode);
    
    /**
     * - Program LP5Mode:
     *   - Dependencies:
     *     - user_input_basic.DramType
     */
    uint16_t isLP5Mode = 1;
    dwc_ddrphy_phyinit_cmnt ("%s Programming LP5Mode to 0x%x\n", printf_header, isLP5Mode);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_LP5Mode_ADDR), isLP5Mode);



    /**
     * - Program ZCalRZN:
     *   - Fields:
     *     - ZCalStrenCodePU
     *     - ZCalStrenCodePD
     *   - Dependencies:
     *     - user_input_advanced.ExtCalResVal
     */
    int ZCalRZN;
    int ZCalStrenCodePU;
    int ZCalStrenCodePD;
    
    switch ( pUserInputAdvanced->ExtCalResVal) 
      {
        case 120 : ZCalStrenCodePU = 0x8; break;
        case 60  : ZCalStrenCodePU = 0xc; break;
        case 40  : ZCalStrenCodePU = 0xe; break;
        case 30  : ZCalStrenCodePU = 0xf; break;
        case 0   : ZCalStrenCodePU = 0x0; break;
        default  : dwc_ddrphy_phyinit_assert(0, "%s invalid pUserInputAdvanced->ExtCalResVal=%d\n" , printf_header, pUserInputAdvanced->ExtCalResVal);
      }

    ZCalStrenCodePD = ZCalStrenCodePU;

    ZCalRZN = (ZCalStrenCodePD << csr_ZCalStrenCodePD_LSB) | (ZCalStrenCodePU << csr_ZCalStrenCodePU_LSB);
    
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalRZN::ZCalStrenCodePU to 0x%x\n", printf_header, ZCalStrenCodePU);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalRZN::ZCalStrenCodePD to 0x%x\n", printf_header, ZCalStrenCodePD);
    
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_ZCalRZN_ADDR), ZCalRZN);


   /**
     * - Program ZCalRate:
     *   - Fields:
     *     - ZCalInterval
     *     - ZCalOnce
     *   - Dependencies:
     *     - user_input_advanced.CalInterval
     *     - user_input_advanced.CalOnce
     */
    
    int ZCalRate;
    int ZCalInterval;
    int ZCalOnce;

    ZCalInterval = pUserInputAdvanced->CalInterval;
    ZCalOnce = pUserInputAdvanced->CalOnce;

    ZCalRate = (ZCalOnce << csr_ZCalOnce_LSB) | (ZCalInterval << csr_ZCalInterval_LSB);

    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalRate::ZCalInterval to 0x%x\n", printf_header, ZCalInterval);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalRate::ZCalOnce to 0x%x\n", printf_header, ZCalOnce);

    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_ZCalRate_ADDR), ZCalRate);


    /**
     * - Program ZCalCompVref
     *   - Fields: 
     *     - ZCalCompVrefDAC
     *     - ZCalDACRangeSel
     */
    uint16_t ZCalCompVrefDAC;
    uint16_t ZCalDACRangeSel;

    ZCalDACRangeSel = 0;
    ZCalCompVrefDAC = 0x26;

    uint16_t ZCalCompVref = (ZCalCompVrefDAC << csr_ZCalCompVrefDAC_LSB) | (ZCalDACRangeSel << csr_ZCalDACRangeSel_LSB);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalCompVref::ZCalCompVrefDAC to 0x%x\n", printf_header, ZCalCompVrefDAC);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalCompVref::ZCalDACRangeSel to 0x%x\n", printf_header, ZCalDACRangeSel);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_ZCalCompVref_ADDR), ZCalCompVref);


    /**
     * - Program VrefDacRefCtl
     *   - Fields: 
     *     - DacRefModeCtl
     *     - DacRefPwrDn
     */
    uint16_t DacRefModeCtl = 0;
    uint16_t DacRefPwrDn = 0;

    uint16_t VrefDacRefCtl = (DacRefPwrDn << csr_DacRefPwrDn_LSB) | (DacRefModeCtl << csr_DacRefModeCtl_LSB);
    dwc_ddrphy_phyinit_cmnt ("%s Programming VrefDacRefCtl::DacRefModeCtl to 0x%x\n", printf_header, DacRefModeCtl);
    dwc_ddrphy_phyinit_cmnt ("%s Programming VrefDacRefCtl::DacRefPwrDn to 0x%x\n", printf_header, DacRefPwrDn);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_VrefDacRefCtl_ADDR), VrefDacRefCtl);


    /**
     * - Program ZCalBaseCtrl
     *   - Fields:
     *     - ZCalBasePU
     *     - ZCalBasePD
     *     - ZCalTxModeCtl
     */
    uint16_t valZCalBasePU = 0x1;
    uint16_t valZCalBasePD = 0x1;
    uint16_t valTxModeCtl;
    uint16_t valWeakPullDown = 0x0;

    valTxModeCtl = (0x0 << 1);
    valTxModeCtl |= valWeakPullDown;

    uint16_t valZCalBaseCtrl = (valZCalBasePU << csr_ZCalBasePU_LSB)
                             | (valZCalBasePD << csr_ZCalBasePD_LSB)
                             | (valTxModeCtl << csr_ZCalTxModeCtl_LSB);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalBaseCtrl::ZCalBasePU to 0x%x\n", printf_header, valZCalBasePU);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalBaseCtrl::ZCalBasePD to 0x%x\n", printf_header, valZCalBasePD);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalBaseCtrl::ZCalTxModeCtl to 0x%x\n", printf_header, valTxModeCtl);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalBaseCtrl to 0x%x\n", printf_header, valZCalBaseCtrl);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_ZCalBaseCtrl_ADDR), valZCalBaseCtrl);


    /**
     * - Program ZCalCompCtrl
     *   - Fields:
     *     - ZCalCompGainCurrAdj
     *     - ZCalCompGainResAdj
     *   - Dependencies
     *     - user_input_advanced.CalImpedanceCurrentAdjustment
     */
    uint16_t valZCalCompGainCurrAdj = pUserInputAdvanced->CalImpedanceCurrentAdjustment;
    uint16_t valZCalCompGainResAdj = 0x0;

    uint16_t valZCalCompCtrl = (valZCalCompGainCurrAdj << csr_ZCalCompGainCurrAdj_LSB)
                             | (valZCalCompGainResAdj  << csr_ZCalCompGainResAdj_LSB);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalCompCtrl::ZCalCompGainCurrAdj to 0x%x\n", printf_header, valZCalCompGainCurrAdj);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalCompCtrl::ZCalCompGainResAdj to 0x%x\n", printf_header, valZCalCompGainResAdj);
    dwc_ddrphy_phyinit_cmnt ("%s Programming ZCalCompCtrl to 0x%x\n", printf_header, valZCalCompCtrl);
    dwc_ddrphy_phyinit_io_write16((tMASTER | csr_ZCalCompCtrl_ADDR), valZCalCompCtrl);

        

    /**
     * - Program DFIPHYUPD
     *   - Fields:
     *     - DFIPHYUPDRESP 
     *     - DFIPHYUPDCNT 
     *   - Dependencies:
     *     - user_input_advanced.DisablePhyUpdate
     */
    if (pUserInputAdvanced->DisablePhyUpdate != 0) {
        for (achn=0; achn<NumAchn; achn++) {
            c_addr = achn << 12;
            dwc_ddrphy_phyinit_io_write16((tAC | c_addr | csr_DFIPHYUPD_ADDR), 0);
        }
    }


    if ( pUserInputBasic->NumRank_dfi0 > pUserInputBasic->NumRank || 
         pUserInputBasic->NumRank_dfi1 > pUserInputBasic->NumRank ) {
 
        dwc_ddrphy_phyinit_assert(0, "%s Invalid user inputs: NumRank_dfi0 (%d) and NumRank_dfi1 (%d) cannot exceed NumRank (%d)\n", 
                printf_header, pUserInputBasic->NumRank_dfi0, pUserInputBasic->NumRank_dfi1, pUserInputBasic->NumRank);
    }


    /**
     * - Program DfiClkAcLnDis PClkAcLnDis, AcLnDisable (AC)
     * - Dependencies:
     *   - user_input_basic.NumCh
     *   - user_input_basic.NumRank_dfi0
     *   - user_input_basic.NumRank_dfi1
     */
    uint16_t data_ch0;
    uint16_t data_ch1;
    data_ch0 = 0x80; //(pUserInputBasic->NumRank == 2) ? (pUserInputBasic->NumRank_dfi0 == 1 ? 0x280 : 0x80) : /*0x280*/0x80;
    data_ch1 = 0x80; //(NumAchn == 2) ? (pUserInputBasic->NumRank_dfi1 == 1 ? 0x280 : 0x80) : /*0x7ff*/0x80;

    dwc_ddrphy_phyinit_cmnt ("%s Programming AC%d.DfiClkAcLnDis to 0x%x\n", printf_header, 0, data_ch0);
    dwc_ddrphy_phyinit_cmnt ("%s Programming AC%d.PClkAcLnDis to 0x%x\n",   printf_header, 0, data_ch0);
    dwc_ddrphy_phyinit_cmnt ("%s Programming AC%d.AcLnDisable to 0x%x\n",   printf_header, 0, data_ch0);
    dwc_ddrphy_phyinit_io_write16((c0 | tAC | csr_DfiClkAcLnDis_ADDR), data_ch0);
    dwc_ddrphy_phyinit_io_write16((c0 | tAC |   csr_PClkAcLnDis_ADDR), data_ch0);
    dwc_ddrphy_phyinit_io_write16((c0 | tAC |   csr_AcLnDisable_ADDR), data_ch0);

    if (NumAchn > 1) {
        dwc_ddrphy_phyinit_cmnt ("%s Programming AC%d.DfiClkAcLnDis to 0x%x\n", printf_header, 1, data_ch1);
        dwc_ddrphy_phyinit_cmnt ("%s Programming AC%d.PClkAcLnDis to 0x%x\n",   printf_header, 1, data_ch1);
        dwc_ddrphy_phyinit_cmnt ("%s Programming AC%d.AcLnDisable to 0x%x\n",   printf_header, 1, data_ch1);
        dwc_ddrphy_phyinit_io_write16((c1 | tAC | csr_DfiClkAcLnDis_ADDR), data_ch1);
        dwc_ddrphy_phyinit_io_write16((c1 | tAC |   csr_PClkAcLnDis_ADDR), data_ch1);
        dwc_ddrphy_phyinit_io_write16((c1 | tAC |   csr_AcLnDisable_ADDR), data_ch1);
    }


    /*
     * - Program UcclkHclkEnables (PMU and HWT clocks)
     *   - Dependencies:
     *     - user_input_advanced.PmuClockDiv
     */
    uint16_t pmuClkEnables = csr_HclkEn_MASK | csr_UcclkEn_MASK;
    if (pUserInputAdvanced->PmuClockDiv == 0) {
        pmuClkEnables |= (uint16_t)csr_UcclkFull_MASK;
    }
    dwc_ddrphy_phyinit_cmnt ("%s Programming UcclkHclkEnables to 0x%x\n", printf_header, pmuClkEnables);
    dwc_ddrphy_phyinit_io_write16((tDRTUB | csr_UcclkHclkEnables_ADDR), pmuClkEnables);

    /*
     * - Program ArcPmuEccCtl (PMU ECC)
     *   - Dependencies:
     *     - user_input_advanced.DisablePmuEcc
     */
    uint16_t disableEcc = pUserInputAdvanced->DisablePmuEcc;
    dwc_ddrphy_phyinit_cmnt ("%s Programming ArcPmuEccCtl to 0x%x\n", printf_header, disableEcc);
    dwc_ddrphy_phyinit_io_write16((tDRTUB | csr_ArcPmuEccCtl_ADDR), disableEcc);
    if (disableEcc == 1) {
        dwc_ddrphy_phyinit_cmnt ("%s Programming PhyInterruptEnable::PhyEccEn to 0x0\n", printf_header);
        dwc_ddrphy_phyinit_io_write16((tMASTER | csr_PhyInterruptEnable_ADDR), (0 << csr_PhyEccEn_LSB));
    }


    /**
     * - Program PptCtlStatic
     *   - Fields:
     *     - DOCByteSelTg0/1
     *     - PptEnRxEnBackOff
     *   - Dependencies:
     *     - DramType
     *     - DramDataWidth
     *     - DramByteSwap
     */
    uint16_t regData;

    for (byte=0; byte < NumDbyte ; byte++) { // Each Dbyte could have a different configuration.
      uint16_t PptEnRxEnBackOff = 0x2;
      uint16_t DOCByteTg0, DOCByteTg1;
      c_addr = byte*c1;
      if (pUserInputBasic->DramDataWidth==8) {

        // all ranks are bytemode
        if (mb1D[0].X8Mode == 0xf ) { DOCByteTg0 = 0x0; DOCByteTg1 = 0x0;}
        // no ranks are byte mode
        else if (mb1D[0].X8Mode == 0x0 && byte%2== 0) { DOCByteTg0 = 0x0; DOCByteTg1 = 0x0;}
        else if (mb1D[0].X8Mode == 0x0 && byte%2== 1) { DOCByteTg0 = 0x1; DOCByteTg1 = 0x1;}
        // rank0 is byte mode
        else if (mb1D[0].X8Mode == 0x5 && byte%2== 0) { DOCByteTg0 = 0x0; DOCByteTg1 = 0x0;}
        else if (mb1D[0].X8Mode == 0x5 && byte%2== 1) { DOCByteTg0 = 0x0; DOCByteTg1 = 0x1;}
        // rank1 is byte mode
        else if (mb1D[0].X8Mode == 0xa && byte%2== 0) { DOCByteTg0 = 0x0; DOCByteTg1 = 0x0;}
        else if (mb1D[0].X8Mode == 0xa && byte%2== 1) { DOCByteTg0 = 0x1; DOCByteTg1 = 0x0;}
        else {
          dwc_ddrphy_phyinit_assert(0, "%s Unexpected value for mb1D[p0].X8Mode == %d", printf_header, mb1D[0].X8Mode);
        }
      }else if (byte%2==0){
        DOCByteTg0 = 0x1 & (pUserInputAdvanced->DramByteSwap>>byte);
        DOCByteTg1 = 0x1 & (pUserInputAdvanced->DramByteSwap>>byte);
      }else{
        DOCByteTg0 = 0x1 & ~(pUserInputAdvanced->DramByteSwap>>byte);
        DOCByteTg1 = 0x1 & ~(pUserInputAdvanced->DramByteSwap>>byte);
      }

      uint8_t PptEnTg1;
      PptEnTg1 = ((pUserInputBasic->NumRank_dfi0 == 2) || (pUserInputBasic->NumRank_dfi1 == 2)) ? 0x1 : 0x0;
      regData = ( 0x1 << csr_PptEnDqs2DqTg0_LSB |
               PptEnTg1 << csr_PptEnDqs2DqTg1_LSB |
               0x1 << csr_PptEnRxEnDlyTg0_LSB |
               PptEnTg1 << csr_PptEnRxEnDlyTg1_LSB |
               PptEnRxEnBackOff << csr_PptEnRxEnBackOff_LSB |
               DOCByteTg0 << csr_DOCByteSelTg0_LSB | 
               DOCByteTg1 << csr_DOCByteSelTg1_LSB );

      uint8_t PptEnWck2DqoTg0 = 0x1;
      uint8_t PptEnWck2DqoTg1 = PptEnTg1;
      regData |= PptEnWck2DqoTg0 << csr_PptEnWck2DqoTg0_LSB
              |  PptEnWck2DqoTg1 << csr_PptEnWck2DqoTg1_LSB;

      dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_PptCtlStatic_ADDR), regData);
    }


    /**
     * - Program DbyteMiscMode
     *   - Fields:
     *     - DByteDisable
     *   - see function dwc_ddrphy_phyinit_IsDbyteDisabled() to determine
     *     which DBytes are turned off completely based on PHY configuration.
     *   - Dependencies:
     *     - user_input_basic.NumCh
     *     - user_input_basic.NumDbytesPerCh
     */
    for (byte=0;byte<NumDbyte;byte++) { // for each dbyte
        c_addr = byte*c1;

        if (dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte)) {
            dwc_ddrphy_phyinit_cmnt ("%s Programming DBYTE%d.DbyteMiscMode to disable Dbyte\n", printf_header, byte);
            dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_DbyteMiscMode_ADDR), 0x1 << csr_DByteDisable_LSB);
        }
    } // for each dbyte

    /*! @todo Needs documentation */
    for (byte=0;byte<NumDbyte;byte++) // for each dbyte
      { 
        c_addr = byte*c1;

       /**
        * - Program RxReplicaUIcalwait based on userInputAdvanced.RxClkTrackWait
        dwc_ddrphy_phyinit_cmnt ("%s Programming DBYTE%d.RxReplicaUIcalwait to %d\n", printf_header,d,pUserInputAdvanced->RxClkTrackWait);
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_RxReplicaUIcalwait_ADDR), pUserInputAdvanced->RxClkTrackWait); 
        */

       /**
        * - Program RxReplicanextcalwait based on userInputAdvanced.RxClkTrackWaitUI
        dwc_ddrphy_phyinit_cmnt ("%s Programming DBYTE%d.RxReplicanextcalwait to %d\n", printf_header,d,pUserInputAdvanced->RxClkTrackWaitUI);
        dwc_ddrphy_phyinit_io_write16((c_addr | tDBYTE | csr_RxReplicanextcalwait_ADDR), pUserInputAdvanced->RxClkTrackWaitUI); 
        */
      } // dbyte

    /**
     * - Program PsDmaRamSize 
     *   - Dependencies:
     *     - user_input_advanced.PsDmaRamSize

     */
    if ( pUserInputBasic->NumPStates > 2)
      {
        dwc_ddrphy_phyinit_io_write16(( tDRTUB | csr_PsDmaRamSize_ADDR), pUserInputAdvanced->PsDmaRamSize); 
      }

    /**
     * - Program DfiXlat based on Pll Bypass Input
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.PllBypass
     */
    dwc_ddrphy_phyinit_cmnt ("%s Programming DfiFreqXlat*\n", printf_header);

    uint8_t xlat[64] = {0x0};
    uint8_t idx;
    for (int ps=0;ps<DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE; ps++)
      {
        uint16_t freqThreshold = 83;
        uint16_t NoRDQS = ((mb1D[ps].MR20_A0 & 0x3) == 0x0);
        if ((pUserInputBasic->CfgPStates & (0x1<<ps)) == 0) continue;
        if (pUserInputBasic->NumPStates<3 && pUserInputBasic->DfiFreqRatio[ps]==1 ) 
          {
            // if 2PS and if 1:2, then need to map P0->P7 or P1->P8
            idx = 32 + ps;
          } 
        else
          {
            idx = (ps>6) ? 32+ps-7 : ps;
          }
        xlat[idx]    = (pUserInputBasic->Frequency[ps] < freqThreshold ) ? 0x6 : // force relock only+bypass on slow frequencies.
                       ((pUserInputBasic->PllBypass[ps]) ? 0x1 : 0x0); // determine bypass
        xlat[idx]    += (pUserInputBasic->Frequency[ps] >= freqThreshold && NoRDQS) ? 0x5 : 0x0; // force relock only if NoRDQS by adding 5.
        xlat[8+idx]  = 0x0; // RFU 
        xlat[16+idx] = (pUserInputBasic->Frequency[ps] < freqThreshold ) ? 0x6 : // force relock only+bypass on slow frequencies.
                       ((pUserInputBasic->PllBypass[ps]) ? 0x6 : 0x5); // determine bypass
        xlat[24+idx] = 0x2; // No Retrain, No Relock
      }
    xlat[ 7] = 0x6; // P14 force relock only+bypass on slow frequencies.
    xlat[15] = 0x8; // PPT triggered by PhyMstr
    xlat[23] = 0x4; // Retrain Only
    xlat[31] = 0xf; // Enter LP3
    xlat[39] = 0x6; // P14 force relock only+bypass on slow frequencies.
    xlat[47] = 0x8; // PPT triggered by PhyMstr
    xlat[55] = 0x4; // Retrain Only
    xlat[63] = 0xf; // Enter LP3

    uint16_t loopVector;
    for(loopVector=0; loopVector<16; loopVector++)
      {
        int xlatIdx = loopVector * 4;
        dwc_ddrphy_phyinit_cmnt ("%s Programming xlat[%d]=%d\n", printf_header, xlatIdx, xlat[xlatIdx]);
        dwc_ddrphy_phyinit_cmnt ("%s Programming xlat[%d]=%d\n", printf_header, xlatIdx+1, xlat[xlatIdx+1]);
        dwc_ddrphy_phyinit_cmnt ("%s Programming xlat[%d]=%d\n", printf_header, xlatIdx+2, xlat[xlatIdx+2]);
        dwc_ddrphy_phyinit_cmnt ("%s Programming xlat[%d]=%d\n", printf_header, xlatIdx+3, xlat[xlatIdx+3]);
        
        regData = (xlat[xlatIdx+3] << 12) | (xlat[xlatIdx+2] << 8) |  (xlat[xlatIdx+1] << 4) | (xlat[xlatIdx]) ; 
        if (regData == 0x0 ) continue;
        dwc_ddrphy_phyinit_io_write16((c0 | tDRTUB | (csr_DfiFreqXlat0_ADDR+loopVector)), regData); 
      }

    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_C_initPhyConfig()\n", printf_header);
  }
// End of dwc_ddrphy_phyinit_C_initPhyConfig()

/** \brief implements Step C in Pstate Loop of initialization sequence
 *
 * This function programs majority of PHY Pstate configuration registers based
 * on data input into PhyInit data structures.
 *
 * \return void
 *
 * List of registers programmed by this function:
 */
void dwc_ddrphy_phyinit_C_initPhyConfigPsLoop (phyinit_config_t* phyctx)
{
    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    PMU_SMB_LPDDR5_1D_t* mb1D = phyctx->mb_LPDDR5_1D;
  
    uint8_t  pstate   = pRuntimeConfig->curPState;
    uint32_t p_addr   = pUserInputBasic->NumPStates <3 ? pstate << 20 : p0;
    uint16_t freq     = pUserInputBasic->Frequency[pstate];
    uint16_t ratio    = 1 << pUserInputBasic->DfiFreqRatio[pstate];
    uint8_t  NumDbyte = pUserInputBasic->NumCh * pUserInputBasic->NumDbytesPerCh ;
    uint8_t  NumAchn  = pUserInputBasic->NumCh;
  
    char *printf_header;
    printf_header = " [phyinit_C_initPhyConfigPsLoop]";
  
    uint8_t lane;
    uint8_t byte;
    uint8_t achn;
    uint32_t r_addr;
    uint32_t c_addr;
    uint16_t regData;

    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_C_initPhyConfigPsLoop()\n", printf_header);

    /**
     * ### Following registers are saved as Group 1 ###
     */ 
    dwc_ddrphy_phyinit_regInterface(setGroup,0,1);

    /**
     *  - program csrPstate GPR in 2 PState case
     */

    regData = (pstate == 0 && pUserInputBasic->NumPStates <3) ? 0x1 : 0x0;
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BGPR2_ADDR ), regData);
  
    /**
     * - Program PLL configuration CSRs PllCtrl5 and PllCtrl6
     *   - Fields: 
     *     - PllVcoLowFreq
     *     - PllV2IMode
     *     - PllDivSe
     *     - PllX4Mode
     *   - Dependencies:
     *     - user_input_basic.Frequency
     *     - user_input_basic.DfiFreqRatio
     */
  
    // PLL default operation modes, with x4 or x8 ratio settings
    // Note: lookup frequency table(s) below use PllRefClk frequency x 4
  
    uint16_t pll_x8_mode = 0x1;
  
  
    // PLL reference input clock freq     89.4  , 106   , 130.25, 156.25, 178.8 , 212   , 260.5 , 312.5 , 357.6 , 424   , 521   , 625   , 675   , 822.5 
    uint16_t freq_list_x8_default[]   = { 358   , 424   , 521   , 625   , 715   , 848   , 1042  , 1250  , 1430  , 1696  , 2084  , 2500  , 2700  , 3290  };
    uint16_t pllDivSel_x8_default[]   = { 0x23  , 0x23  , 0x23  , 0x27  , 0x157 , 0x157 , 0x157 , 0x15b , 0x28b , 0x28b , 0x28b,  0x28f , 0x28f , 0x28f };
    uint16_t pllV2IMode_x8_default[]  = { 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x2   , 0x3   , 0x3   };
    uint16_t pllVcoLowF_x8_default[]  = { 0x3   , 0x2   , 0x1   , 0x0   , 0x3   , 0x2   , 0x1   , 0x0   , 0x3   , 0x2   , 0x1   , 0x0   , 0x2   , 0x1   };
    unsigned freq_list_len_x8_default = sizeof(freq_list_x8_default) / sizeof(freq_list_x8_default[0]);
  
  
    int lookupFreq; // The frequency table above uses PllRefClk frequency x 4
  
    uint16_t* pFreqList      = freq_list_x8_default;
    uint16_t* pPllDivSel     = pllDivSel_x8_default;
    uint16_t* pPllV2IMode    = pllV2IMode_x8_default;
    uint16_t* pPllVcoLowFreq = pllVcoLowF_x8_default;
    unsigned  freq_list_len  = freq_list_len_x8_default;
  
  
    // The frequency table above uses PllRefClk frequency x 4
    lookupFreq = freq << 2;
  
    if (freq > 800) {
        dwc_ddrphy_phyinit_assert(0, "%s specified frequency %d MHz is out of range (pUserInputBasic->Frequency, pstate=%d)\n" , printf_header, freq, pstate);
    }
  
  
    // default to max frequency settings
    uint16_t pllDivSel     = pPllDivSel[freq_list_len-1];
    uint16_t pllV2IMode    = pPllV2IMode[freq_list_len-1];
    uint16_t pllVcoLowFreq = pPllVcoLowFreq[freq_list_len-1];
  
    for (unsigned freq_i = 0 ; freq_i < freq_list_len ; freq_i++) {
        if (lookupFreq <= pFreqList[freq_i] ) {
            pllDivSel     = pPllDivSel[freq_i];
            pllV2IMode    = pPllV2IMode[freq_i];
            pllVcoLowFreq = pPllVcoLowFreq[freq_i];
            break;
        }
    }
    
    uint16_t pllCtrl5 = ( pllVcoLowFreq << csr_PllVcoLowFreq_LSB ) | ( pllV2IMode << csr_PllV2IMode_LSB ) | ( pllDivSel << csr_PllDivSel_LSB );
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming  PllDivSel to %x.\n", printf_header, pstate, freq, pllDivSel);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming  PllV2IMode to %x.\n", printf_header, pstate, freq, pllV2IMode);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming  PllVcoLowFreq to %x.\n", printf_header, pstate, freq, pllVcoLowFreq);
    dwc_ddrphy_phyinit_io_write16( (p_addr | tMASTER | csr_PllCtrl5_ADDR), pllCtrl5 );
    
    uint16_t pllCtrl6 = ( pll_x8_mode << csr_PllX4Mode_LSB );
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming  PllX4Mode to %x.\n", printf_header, pstate, freq, pll_x8_mode);
    dwc_ddrphy_phyinit_io_write16( (p_addr | tMASTER | csr_PllCtrl6_ADDR), pllCtrl6 );

    /**
     * - Registers: Seq0BDLY0, Seq0BDLY1, Seq0BDLY2, Seq0BDLY3, Seq0BDLY4, Seq0BDLY5, Seq0BDLY6, Seq0BDLY7
     *   - Program PIE instruction delays 
     *   - Dependencies:
     *     - user_input_basic.Frequency
     */
    // Need delays for 0.5us, 1us, 10us, and DLL Lock.
    uint16_t psCount[8];

    // Calculate the counts to obtain the correct delay for each frequency
    // Need to divide by 4 since the delay value are specified in units of
    // 4 clocks.
    uint32_t DfiFrq,dllLock;

    DfiFrq = freq;
    psCount[0] = (int)(( 0.5 * 0.25 * DfiFrq));
    psCount[1] = (int)(( 1.0 * 0.25 * DfiFrq));
    psCount[2] = (int)((10.0 * 0.25 * DfiFrq));

    if (DfiFrq>266) { dllLock=176; } 
    else if (DfiFrq<=266 && DfiFrq>200) { dllLock=132; } 
    else { dllLock=128; }

    if (pUserInputBasic->DfiFreqRatio[pstate]==0x2) dllLock *= 2;

    psCount[3] = (int)(0.25 * dllLock);
    psCount[4] = (int)(( 0.1 * 0.25 * DfiFrq)); 

    uint8_t RxReplicaShortRangeA = 16;
    uint8_t RxReplicaShortRangeB = 9;
    int16_t RxRepCalWait = 8 * RxReplicaShortRangeA + 40;
    RxRepCalWait -= (pUserInputBasic->NumRank ==1) ? 161: 305;
    RxRepCalWait -= (pUserInputBasic->DfiFreqRatio[pstate]==0x1) ? 14*pUserInputBasic->NumRank: 0;
    psCount[5] = (RxRepCalWait < 0) ? 0 : RxRepCalWait;

    int16_t OscWait = pUserInputBasic->DfiFreqRatio[pstate]==0x2 ? 180 : 145; 
    if (pUserInputBasic->NumRank ==1) OscWait += (pUserInputBasic->DfiFreqRatio[pstate]==0x2) ? 152: 168;
    OscWait -= 4; // 16 DFI clocks for RxClk LCDL update delay
    OscWait -= psCount[5];   // Subtrack the RxRepCalWait.
    psCount[6] = (OscWait < 0) ? 0 : OscWait;

    uint16_t nZQ = pUserInputBasic->MaxNumZQ;
    uint16_t tZQCal = 0;

    if (nZQ > 0 && nZQ <= 4) {
        tZQCal = (int)(( 1.5 * 0.25 * DfiFrq));
    } else if (nZQ <= 8) {
        tZQCal = (int)(( 3.0 * 0.25 * DfiFrq));
    } else if (nZQ <= 16) {
        tZQCal = (int)(( 6.0 * 0.25 * DfiFrq));
    } else {
        dwc_ddrphy_phyinit_assert(0, "%s invalid user input MaxNumZQ: %d\n" , printf_header, nZQ);
    }

    psCount[7] = tZQCal ; // tZQCAL4/8/16

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY0 to 0x%x\n", printf_header, pstate,  freq, psCount[0]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY0_ADDR), psCount[0]);
    
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY1 to 0x%x\n", printf_header, pstate,  freq, psCount[1]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY1_ADDR), psCount[1]);
    
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY2 to 0x%x\n", printf_header, pstate,  freq, psCount[2]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY2_ADDR), psCount[2]);
    
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY3 to 0x%x\n", printf_header, pstate,  freq, psCount[3]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY3_ADDR), psCount[3]);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY4 to 0x%x\n", printf_header, pstate,  freq, psCount[4]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY4_ADDR), psCount[4]);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY5 to 0x%x\n", printf_header, pstate,  freq, psCount[5]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY5_ADDR), psCount[5]);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY6 to 0x%x\n", printf_header, pstate,  freq, psCount[6]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY6_ADDR), psCount[6]);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d,  Memclk=%dMHz, Programming Seq0BDLY7 to 0x%x\n", printf_header, pstate,  freq, psCount[7]);
    dwc_ddrphy_phyinit_io_write16((p_addr | c0 | tINITENG | csr_Seq0BDLY7_ADDR), psCount[7]);


    
    /**
     * - Program PclkPtrInitVal:
     *   - The values programmed here assume ideal properties of DfiClk and Pclk including:
     *     - DfiClk skew
     *     - DfiClk jitter
     *     - DfiClk PVT variations
     *     - Pclk skew
     *     - Pclk jitter
     * 
     * The PclkPtrInitVal register controls the hase offset between read and write pointers of master command FIFO.
     * A small value my be prone to causing underflow and a large value will increase the PHY latency.
     * The units of this register are in UI. Please see PUB databook for detailed programming information.
     *
  
     */
  

    // We update the struct field here as the dwc_ddrphy_phyinit_progCsrSkipTrain() function
    // needs the value and would otherwise require a PHY read register implementation.
    phyctx->PclkPtrInitVal[pstate] = 2;

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PclkPtrInitVal to 0x%x\n", printf_header, pstate, freq, phyctx->PclkPtrInitVal[pstate]);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_PclkPtrInitVal_ADDR), phyctx->PclkPtrInitVal[pstate]);
  
    /**
     * - Program DfiFreqRatio, 
     *   - Dependencies:
     *     - user_input_basic.DfiFreqRatio
     */
    int DfiFreqRatio;
  
    DfiFreqRatio = pUserInputBasic->DfiFreqRatio[pstate];
    
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DfiFreqRatio to 0x%x\n", printf_header, pstate, freq, DfiFreqRatio);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DfiFreqRatio_ADDR), DfiFreqRatio);
  
    /**
     * ### Following registers are saved as Group 2 ###
     */ 
    dwc_ddrphy_phyinit_regInterface(setGroup,0,2);
  
  
    /**
     * - Program DbyteRxDqsModeCntrl:
     *   - RxPostambleMode
     *   - RxPreambleMode
     * - Program DqsPreambleControl:
     *   - Fields:
     *     - LP4PostambleExt  (Tx)
     *   - Dependencies:
     *      - user_input_basic.DramType
   
   
     * - Program RxDigStrbEn and DxDigStrobeMode for RDQS disabled mode (strobe-less read mode)
   
     */
    int DqsPreambleControl;
    int LP4PostambleExt=0;
    int WDQSEXTENSION=0;
    int RxPostambleMode=0;
    int RxPreambleMode=0;
    int LPDDR5RdqsEn=0;
    int LPDDR5RdqsPre=0;
    int LPDDR5RdqsPst=0;
    int DqPreOeExt=0;
    int DqPstOeExt=0;
    int DbyteRxDqsModeCntrl;
  
  
    // LPDDR5
    uint16_t pst = (mb1D[pstate].MR10_A0 & 0xC0) >> 6;
    WDQSEXTENSION           = pUserInputAdvanced->WDQSExt;
    LPDDR5RdqsEn            = 0x1;
    LPDDR5RdqsPre           = 0x1;  // JEDEC MR10.OP[5:4]=1 Static 2*tWCK, Toggle 2*tWCK
    LPDDR5RdqsPst           = pst;  // JEDEC MR10.OP[7:6]=1 2.5*tWCK or =2 4.5*tWCK

    uint16_t RxDigStrbEn = 0;
    uint16_t DxDigStrobeMode = 0;

    // Case where RDQS is disabled and data rate is equal or less than 1600 Mbps;
    if ( ((mb1D[pstate].MR20_A0 & 0x3) == 0x0) && (freq * ratio * 2 <= 1600) )  {
        LPDDR5RdqsEn = 0x0;
        RxPreambleMode = 0x1;
        RxPostambleMode = 0x1;
        RxDigStrbEn = 0x1;
        DxDigStrobeMode = 0x2;
    }

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming RxDigStrbEn to 0x%x\n", printf_header, pstate, freq, RxDigStrbEn);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DxDigStrobeMode to 0x%x\n", printf_header, pstate, freq, DxDigStrobeMode);

    for (byte=0; byte<NumDbyte; byte++) {
        c_addr = byte << 12;
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxDigStrbEn_ADDR), RxDigStrbEn);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_DxDigStrobeMode_ADDR), DxDigStrobeMode);
    }

    // DFE
    if ( (mb1D[pstate].MR24_A0 & 0x80) != 0) {
        DqPreOeExt = 1;
    }

  
  
    DqsPreambleControl = (WDQSEXTENSION   << csr_WDQSEXTENSION_LSB)
                       | (LP4PostambleExt << csr_LP4PostambleExt_LSB)
                       | (DqPreOeExt      << csr_DqPreOeExt_LSB)
                       | (DqPstOeExt      << csr_DqPstOeExt_LSB);
    
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DqsPreambleControl::LP4PostambleExt to 0x%x\n", printf_header, pstate, freq, LP4PostambleExt);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DqsPreambleControl::DqPreOeExt to 0x%x\n", printf_header, pstate, freq, DqPreOeExt);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DqsPreambleControl to 0x%x\n", printf_header, pstate, freq, DqsPreambleControl);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DqsPreambleControl_ADDR), DqsPreambleControl);
    
    DbyteRxDqsModeCntrl = (RxPreambleMode << csr_RxPreambleMode_LSB) | (RxPostambleMode << csr_RxPostambleMode_LSB)
                        | (LPDDR5RdqsEn   << csr_LPDDR5RdqsEn_LSB)   | (LPDDR5RdqsPre << csr_LPDDR5RdqsPre_LSB)    | (LPDDR5RdqsPst << csr_LPDDR5RdqsPst_LSB);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DbyteRxDqsModeCntrl::RxPreambleMode to 0x%x\n", printf_header, pstate, freq, RxPreambleMode);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DbyteRxDqsModeCntrl::RxPostambleMode to 0x%x\n", printf_header, pstate, freq, RxPostambleMode);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DbyteRxDqsModeCntrl::LPDDR5RdqsEn to 0x%x\n", printf_header, pstate, freq, LPDDR5RdqsEn);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DbyteRxDqsModeCntrl::LPDDR5RdqsPre to 0x%x\n", printf_header, pstate, freq, LPDDR5RdqsPre);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DbyteRxDqsModeCntrl::LPDDR5RdqsPst to 0x%x\n", printf_header, pstate, freq, LPDDR5RdqsPst);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DbyteRxDqsModeCntrl to 0x%x\n", printf_header, pstate, freq,DbyteRxDqsModeCntrl);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DbyteRxDqsModeCntrl_ADDR), DbyteRxDqsModeCntrl);
  
    /**
     * - Program RxModeCtlDIFF0, RxModeCtlDIFF1, RxModeCtlSE0 and RxModeCtlSE1
     */
    uint16_t csrRxModeCtlSE = ((pUserInputAdvanced->RxVrefDACEnable[pstate])                 << 1)
                            | ((pUserInputAdvanced->RxVrefKickbackNoiseCancellation[pstate]) << 0);
    uint16_t csrRxModeCtlDIFF = (pUserInputAdvanced->RxModeBoostVDD[pstate] == 1) ? 0x0 : 0x3;
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming csrRxModeCtlSE0 to 0x%x\n", printf_header, pstate, freq, csrRxModeCtlSE);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming csrRxModeCtlSE1 to 0x%x\n", printf_header, pstate, freq, csrRxModeCtlSE);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming csrRxModeCtlDIFF0 to 0x%x\n", printf_header, pstate, freq, csrRxModeCtlDIFF);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming csrRxModeCtlDIFF1 to 0x%x\n", printf_header, pstate, freq, csrRxModeCtlDIFF);
    
    for (achn=0; achn<NumAchn; achn++) {
        c_addr = achn << 12;
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC    | c_addr | csr_RxModeCtlSE0_ADDR), csrRxModeCtlSE);
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC    | c_addr | csr_RxModeCtlSE1_ADDR), csrRxModeCtlSE);
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC    | c_addr | csr_RxModeCtlDIFF0_ADDR), csrRxModeCtlDIFF);
    }
  
    for (byte=0; byte<NumDbyte; byte++) {
        c_addr = byte << 12;
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxModeCtlSE0_ADDR), csrRxModeCtlSE);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxModeCtlDIFF0_ADDR), csrRxModeCtlDIFF);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxModeCtlDIFF1_ADDR), csrRxModeCtlDIFF);
    }

    /**
     * - Program DxDfiClkDis and DxPClkDis
     *   - Dependencies:
     *     - user_input_basic.DramType
     */
    for (byte=0; byte<NumDbyte; byte++)  {
        c_addr = byte << 12;

        uint16_t DxDfiClkDis = 0x0;
        uint16_t DxPClkDis = 0x0;

        if (dwc_ddrphy_phyinit_IsDbyteDisabled(phyctx, byte)) {
            DxDfiClkDis = 0x7ff;
            DxPClkDis = 0x7ff;
        }

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE%d.DxPClkDis to 0x%x\n",   printf_header, pstate, freq, byte, DxPClkDis);  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE%d.DxDfiClkDis to 0x%x\n", printf_header, pstate, freq, byte, DxDfiClkDis);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_DxPClkDis_ADDR), DxPClkDis);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_DxDfiClkDis_ADDR), DxDfiClkDis);
    }

    /**
      * - Program ZCalClkInfo:
      *   - Fields:
      *     - ZCalDfiClkTicksPer1uS
      *   - Dependencies:
      *     - user_input_basic.NumPStates
  
      */
          
    int ZCalDfiClkTicksPer1uS[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    // Number of DfiClk cycles per 1us
  
    ZCalDfiClkTicksPer1uS[pstate] = freq;
  

    if (ZCalDfiClkTicksPer1uS[pstate] < 24) {
        ZCalDfiClkTicksPer1uS[pstate] = 24;  // Minimum value of ZCalDfiClkTicksPer1uS = 24
    }
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ZCalClkInfo::ZCalDfiClkTicksPer1uS to 0x%x\n", printf_header, pstate, freq, ZCalDfiClkTicksPer1uS[pstate]);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ZCalClkInfo_ADDR), ZCalDfiClkTicksPer1uS[pstate]);
  
    /**
     * - Program VrefDAC series of registers
     */
    uint16_t valVrefDAC;
  
    valVrefDAC = 0x35;
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC VrefDAC[0-3] to 0x%x\n", printf_header, pstate, freq, valVrefDAC);
  
    for (achn=0; achn<NumAchn; achn++) {
        c_addr = achn << 12;
  
  
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_AcVrefDAC0_ADDR), valVrefDAC);
  
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_AcVrefDAC1_ADDR), valVrefDAC);
  
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_AcVrefDAC2_ADDR), valVrefDAC);
  
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_AcVrefDAC3_ADDR), valVrefDAC);
  
    }
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE VrefDAC[0-3] to 0x%x\n", printf_header, pstate, freq, valVrefDAC);
  
    for (byte=0;byte<NumDbyte;byte++)  {
        c_addr = byte << 12;
  
        for (lane=0; lane<8; lane++) {
            r_addr = lane << 8;
  
            dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_VrefDAC0_ADDR), valVrefDAC);
  
            dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_VrefDAC1_ADDR), valVrefDAC);
  
            dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_VrefDAC2_ADDR), valVrefDAC);
  
            dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | r_addr | csr_VrefDAC3_ADDR), valVrefDAC);
  
        }
    }
  
    /**
     * - Program TxModeCtlSE0, TxModeCtlSE1, TxModeCtlDIFF0, TxModeCtlDIFF1
  
     */
    uint16_t valTxModeCtl;
    uint16_t valWeakPullDown = 0x0;
  
    valTxModeCtl = (0x0 << 1);
  
    valTxModeCtl |= valWeakPullDown;
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxModeCtlSE0 to 0x%x\n", printf_header, pstate, freq, valTxModeCtl);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxModeCtlSE1 to 0x%x\n", printf_header, pstate, freq, valTxModeCtl);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxModeCtlDIFF0 to 0x%x\n", printf_header, pstate, freq, valTxModeCtl);
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TxModeCtlDIFF1 to 0x%x\n", printf_header, pstate, freq, valTxModeCtl);
  
  
    for (achn=0; achn<NumAchn; achn++) {
      c_addr = achn << 12;
          
      // *** AC SE CA0-CA5 *** //
      dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_TxModeCtlSE0_ADDR), valTxModeCtl);
  
      // *** AC SE CA6 and CA7 *** //
      dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_TxModeCtlSE1_ADDR), valTxModeCtl);
  
      // *** AC DIFF CK *** //
      dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_TxModeCtlDIFF0_ADDR), valTxModeCtl);
    }
  
    for (byte=0;byte<NumDbyte;byte++)  {
        c_addr = byte << 12;
        
        // *** DBYTE SE DQ and DMI *** //
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxModeCtlSE0_ADDR), valTxModeCtl);
  
        // *** DBYTE DIFF DQS *** //
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxModeCtlDIFF0_ADDR), valTxModeCtl);
    
  
        // *** DBYTE DIFF WCK *** //
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxModeCtlDIFF1_ADDR), valTxModeCtl);
    
    }
  
    /**
     * - Program RxGainCurrAdjDIFF0
  
     *           and RxGainCurrAdjDIFF1
  
    *           and RxGainCurrAdjRxReplica
    *
    */
    uint16_t valRxGainCurrAdjCk = pUserInputAdvanced->RxBiasCurrentControlCk[pstate];
    uint16_t valRxGainCurrAdjDqs = pUserInputAdvanced->RxBiasCurrentControlDqs[pstate];
  
    uint16_t valRxGainCurrAdjWck = pUserInputAdvanced->RxBiasCurrentControlWck[pstate];
  
    uint16_t valRxGainCurrAdjR = pUserInputAdvanced->RxBiasCurrentControlRxReplica[pstate];
  
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC RxGainCurrAdjDIFF0 to 0x%x\n", printf_header, pstate, freq, valRxGainCurrAdjCk);
  
    for (achn=0; achn<NumAchn; achn++) {
        c_addr = achn << 12;
  
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_RxGainCurrAdjDIFF0_ADDR), valRxGainCurrAdjCk);
    }
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE RxGainCurrAdjRxReplica to 0x%x\n", printf_header, pstate, freq, valRxGainCurrAdjR);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE RxGainCurrAdjDIFF0 to 0x%x\n", printf_header, pstate, freq, valRxGainCurrAdjDqs);
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE RxGainCurrAdjDIFF1 to 0x%x\n", printf_header, pstate, freq, valRxGainCurrAdjWck);
  
  
    for (byte=0;byte<NumDbyte;byte++)  {
        c_addr = byte << 12;
  
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxGainCurrAdjDIFF0_ADDR), valRxGainCurrAdjDqs);
    
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxGainCurrAdjDIFF1_ADDR), valRxGainCurrAdjWck);
    
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_RxGainCurrAdjRxReplica_ADDR), valRxGainCurrAdjR);
    }

    /**
     * - Program CmdFifoWrModeMaster:
     *   - Dependencies:
     *     - user_input_basic.DfiFreqRatio
     */
    uint16_t CmdFifoWrModeMaster = 0x1 ;
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER| csr_CmdFifoWrModeMaster_ADDR), CmdFifoWrModeMaster);



    /**
     * - Program PclkDivCa0, PclkDivCa1, PclkDivDq0, PclkDivDq1
     *   - Dependencies:
     *   - user_input_basic.DfiFreqRatio
     *   - user_input_basic.NumCh
     *    - user_input_basic.DramType
     */
  
    uint16_t PclkDivCa0, PclkDivCa1;
    uint16_t PclkDivDq0, PclkDivDq1;
  
  
    if (DfiFreqRatio == 1) { // 1:2 Mode
        PclkDivCa0 = 0x2;
        PclkDivCa1 = 0x2;
        PclkDivDq0 = 0x2;
        PclkDivDq1 = 0x2;
    } else if (DfiFreqRatio == 2) { // 1:4 Mode
        PclkDivCa0 = 0x2;
        PclkDivCa1 = 0x2;
        PclkDivDq0 = 0x1;
        PclkDivDq1 = 0x1;
    }
  
    uint16_t PclkDivRatio = ( (PclkDivCa0 << csr_PclkDivCa0_LSB) & csr_PclkDivCa0_MASK )
                          | ( (PclkDivCa1 << csr_PclkDivCa1_LSB) & csr_PclkDivCa1_MASK )
                          | ( (PclkDivDq0 << csr_PclkDivDq0_LSB) & csr_PclkDivDq0_MASK )
                          | ( (PclkDivDq1 << csr_PclkDivDq1_LSB) & csr_PclkDivDq1_MASK );
    
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PclkDivRatio to 0x%x\n", printf_header, pstate, freq, PclkDivRatio);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER| csr_PclkDivRatio_ADDR), PclkDivRatio);
  
    /**
     * - Program CkDisVal
     *   - Fields:
     *     - CkDisVal
     *   - Dependencies:
     *     - user_input_advanced.CkDisVal
     */
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming CkDisVal:: to 0x%x\n", printf_header, pstate, freq, pUserInputAdvanced->CkDisVal[pstate]);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_CkDisVal_ADDR), (pUserInputAdvanced->CkDisVal[pstate]) << csr_CkDisVal_LSB);
    
   
   /**
    * - Program DMIPinPresent based on DramType and Read-DBI enable
    *   - Fields:
    *     - RdDbiEnabled
    *   - Dependencies:
    *     - user_input_basic.DramDataWidth
    *     - MR3_A0
    */
 
    uint16_t DMIPinPresent = ( (mb1D[pstate].MR3_A0  & 0x40) >> 6 & 1 )  // DBI-RD
                           | ( (mb1D[pstate].MR22_A0 & 0xC0) >> 6 & 1 ); // RECC
 

    
    
    
    
    
    
    
    
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DMIPinPresent::RdDbiEnabled to 0x%x\n", printf_header, pstate, freq, DMIPinPresent);
  
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DMIPinPresent_ADDR), DMIPinPresent);
  
    /**
     * - Program the TrackingModeCntrl CSR for Read DQS Tracking
     *   - Dependencies:
     *     - user_input_advanced.EnRxDqsTracking
     */  
 
    uint16_t EnWck2DqoSnoopTracking = pUserInputAdvanced->EnWck2DqoTracking[pstate] == 1 ? 1: 0;
    uint16_t Twck2dqoTrackingLimit = 0;  // no limit (default)
  
    uint16_t EnRxDqsTracking = pUserInputAdvanced->EnRxDqsTracking[pstate];
    uint16_t EnDqsSampNegRxEn = EnRxDqsTracking ? 1 : 0;
    uint16_t RxDqsTrackingThreshold = pUserInputAdvanced->RxDqsTrackingThreshold[pstate];
    uint16_t DqsOscRunTimeSel = pUserInputAdvanced->DqsOscRunTimeSel[pstate];
    uint16_t Tdqs2dqTrackingLimit = 0; // no limit (default)
  
    uint16_t TrackingModeCntrl = (EnWck2DqoSnoopTracking << csr_EnWck2DqoSnoopTracking_LSB)
        | (Twck2dqoTrackingLimit << csr_Twck2dqoTrackingLimit_LSB)
        | (EnRxDqsTracking << csr_EnRxDqsTracking_LSB)
        | (Tdqs2dqTrackingLimit << csr_Tdqs2dqTrackingLimit_LSB)
        | (DqsOscRunTimeSel << csr_DqsOscRunTimeSel_LSB)
        | (RxDqsTrackingThreshold << csr_RxDqsTrackingThreshold_LSB)
        | (EnDqsSampNegRxEn << csr_EnDqsSampNegRxEn_LSB);
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TrackingModeCntrl::EnRxDqsTracking to 0x%x\n", printf_header, pstate, freq, EnRxDqsTracking);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TrackingModeCntrl::EnDqsSampNegRxEn to 0x%x\n", printf_header, pstate, freq, EnDqsSampNegRxEn);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TrackingModeCntrl::RxDqsTrackingThreshold to 0x%x\n", printf_header, pstate, freq, RxDqsTrackingThreshold);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TrackingModeCntrl::DqsOscRunTimeSel to 0x%x\n", printf_header, pstate, freq, DqsOscRunTimeSel);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming TrackingModeCntrl to 0x%x\n", printf_header, pstate, freq, TrackingModeCntrl);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_TrackingModeCntrl_ADDR), TrackingModeCntrl);
  
    /** 
     * - Program  TxImpedanceSE0, TxImpedanceSE1
     *            TxImpedanceDIFF0T, TxImpedanceDIFF0C
     *            TxImpedanceDIFF1T, TxImpedanceDIFF1C
     *            TxImpedanceCMOS0,  TxImpedanceCMOS1
     *   - Dependencies: pUserInputAdvanced->TxImpedanceDq, 
     *                                       TxImpedanceAc, 
     *                                       TxImpedanceCk, 
     *                                       TxImpedanceDqs, 
     *                                       TxImpedanceWCK, 
     *                                       TxImpedanceCKE,
     *                                       TxImpedanceDTO
     */
    int TxImpedanceSE0;
    int TxStrenCodePUSE0;
    int TxStrenCodePDSE0;
  
    int TxImpedanceDIFF0;
    int TxStrenCodePUDIFF0;
    int TxStrenCodePDDIFF0;
  
    int TxImpedanceCMOS0;
    int TxStrenCodePUCMOS0;
    int TxStrenCodePDCMOS0;
  
    int TxImpedanceCMOS1;
    int TxStrenCodePUCMOS1;
    int TxStrenCodePDCMOS1;
  
  
    // ********* Start TX Impedance for DBYTE ********* //
    for (byte=0;byte<NumDbyte;byte++)  { // for each dbyte
        c_addr = byte*c1;
        
        // *** DBYTE SE *** //
        switch ( pUserInputAdvanced->TxImpedanceDq[pstate]) {
            case 120 : TxStrenCodePUSE0 = 0x8; break;
            case 60  : TxStrenCodePUSE0 = 0xc; break;
            case 40  : TxStrenCodePUSE0 = 0xe; break;
            case 30  : TxStrenCodePUSE0 = 0xf; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->TxImpedanceDq[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->TxImpedanceDq[pstate]);
        }
        TxStrenCodePDSE0 = TxStrenCodePUSE0;
  
  
        TxImpedanceSE0 = (TxStrenCodePUSE0 << csr_TxStrenCodePUSE0_LSB) | (TxStrenCodePDSE0 << csr_TxStrenCodePDSE0_LSB);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceSE0::TxStrenCodePUSE0 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUSE0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceSE0::TxStrenCodePDSE0 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDSE0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_TxImpedanceSE0_ADDR), TxImpedanceSE0);
  
        // *** DBYTE DQS *** //
        switch ( pUserInputAdvanced->TxImpedanceDqs[pstate]) {
            case 120 : TxStrenCodePUDIFF0 = 0x8; break;
            case 60  : TxStrenCodePUDIFF0 = 0xc; break;
            case 40  : TxStrenCodePUDIFF0 = 0xe; break;
            case 30  : TxStrenCodePUDIFF0 = 0xf; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->TxImpedanceDqs[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->TxImpedanceDqs[pstate]);
        }
        TxStrenCodePDDIFF0 = TxStrenCodePUDIFF0;
        
        TxImpedanceDIFF0 = (TxStrenCodePUDIFF0 << csr_TxStrenCodePUDIFF0T_LSB) | (TxStrenCodePDDIFF0 << csr_TxStrenCodePDDIFF0T_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF0T::TxStrenCodePUDIFF0T to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF0T::TxStrenCodePDDIFF0T to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_TxImpedanceDIFF0T_ADDR), TxImpedanceDIFF0);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF0C::TxStrenCodePUDIFF0C to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF0C::TxStrenCodePDDIFF0C to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_TxImpedanceDIFF0C_ADDR), TxImpedanceDIFF0);
  
  
        // *** DBYTE WCK *** //
        switch ( pUserInputAdvanced->TxImpedanceWCK[pstate]) {
            case 120 : TxStrenCodePUDIFF0 = 0x8; break;
            case 60  : TxStrenCodePUDIFF0 = 0xc; break;
            case 40  : TxStrenCodePUDIFF0 = 0xe; break;
            case 30  : TxStrenCodePUDIFF0 = 0xf; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->TxImpedanceWCK[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->TxImpedanceWCK[pstate]);
        }
        TxStrenCodePDDIFF0 = TxStrenCodePUDIFF0;
        
        TxImpedanceDIFF0 = (TxStrenCodePUDIFF0 << csr_TxStrenCodePUDIFF0T_LSB) | (TxStrenCodePDDIFF0 << csr_TxStrenCodePDDIFF0T_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF1T::TxStrenCodePUDIFF1T to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF1T::TxStrenCodePDDIFF1T to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_TxImpedanceDIFF1T_ADDR), TxImpedanceDIFF0);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF1C::TxStrenCodePUDIFF1C to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxImpedanceDIFF1C::TxStrenCodePDDIFF1C to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_TxImpedanceDIFF1C_ADDR), TxImpedanceDIFF0);
  
  
    } // foreach dbyte
    // ********* End TX Impedance for DBYTE ********* //
  
    // ********* Start TX Impedance for AC ********* //
    for (achn=0; achn<NumAchn; achn++) {  // for each AC Channel
        c_addr = achn << 12;
          
        // *** AC SE *** //
        switch ( pUserInputAdvanced->TxImpedanceAc[pstate]) {
            case 120 : TxStrenCodePUSE0 = 0x8; break;
            case 60  : TxStrenCodePUSE0 = 0xc; break;
            case 40  : TxStrenCodePUSE0 = 0xe; break;
            case 30  : TxStrenCodePUSE0 = 0xf; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->TxImpedanceAc[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->TxImpedanceAc[pstate]);
        }
        TxStrenCodePDSE0 = TxStrenCodePUSE0;
  
        TxImpedanceSE0 = (TxStrenCodePUSE0 << csr_TxStrenCodePUSE0_LSB) | (TxStrenCodePDSE0 << csr_TxStrenCodePDSE0_LSB);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceSE0::TxStrenCodePUSE0 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUSE0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceSE0::TxStrenCodePDSE0 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDSE0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_TxImpedanceSE0_ADDR), TxImpedanceSE0);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceSE1::TxStrenCodePUSE1 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUSE0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceSE1::TxStrenCodePDSE1 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDSE0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_TxImpedanceSE1_ADDR), TxImpedanceSE0);
  
        // *** AC CK *** //
        switch ( pUserInputAdvanced->TxImpedanceCk[pstate]) {
            case 120 : TxStrenCodePUDIFF0 = 0x8; break;
            case 60  : TxStrenCodePUDIFF0 = 0xc; break;
            case 40  : TxStrenCodePUDIFF0 = 0xe; break;
            case 30  : TxStrenCodePUDIFF0 = 0xf; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->TxImpedanceCk[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->TxImpedanceCk[pstate]);
        }
        TxStrenCodePDDIFF0 = TxStrenCodePUDIFF0;
  
        TxImpedanceDIFF0 = (TxStrenCodePUDIFF0 << csr_TxStrenCodePUDIFF0T_LSB) | (TxStrenCodePDDIFF0 << csr_TxStrenCodePDDIFF0T_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceDIFF0T::TxStrenCodePUDIFF0T to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceDIFF0T::TxStrenCodePDDIFF0T to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_TxImpedanceDIFF0T_ADDR), TxImpedanceDIFF0);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceDIFF0C::TxStrenCodePUDIFF0C to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceDIFF0C::TxStrenCodePDDIFF0C to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_TxImpedanceDIFF0C_ADDR), TxImpedanceDIFF0);
  
        // *** AC CKE *** //
        switch ( pUserInputAdvanced->TxImpedanceCKE[pstate]) {
            case 400 : TxStrenCodePUCMOS0 = 0x0; break;
            case 100 : TxStrenCodePUCMOS0 = 0x1; break;
            case 67  : TxStrenCodePUCMOS0 = 0x2; break;
            case 50  : TxStrenCodePUCMOS0 = 0x3; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->TxImpedanceCKE[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->TxImpedanceCKE[pstate]);
        }
        TxStrenCodePDCMOS0 = TxStrenCodePUCMOS0;
  
        TxImpedanceCMOS0 = (TxStrenCodePUCMOS0 << csr_TxStrenCodePUCMOS0_LSB) | (TxStrenCodePDCMOS0 << csr_TxStrenCodePDCMOS0_LSB);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceCMOS0::TxStrenCodePUCMOS0 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUCMOS0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceCMOS0::TxStrenCodePDCMOS0 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDCMOS0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_TxImpedanceCMOS0_ADDR), TxImpedanceCMOS0);
   
    } // foreach AC channel 
    // ********* End TX Impedance for AC ********* //
  
    // *** MASTER DTO *** //
    switch ( pUserInputAdvanced->TxImpedanceDTO[pstate]) {
        case 400 : TxStrenCodePUCMOS1 = 0x0; break;
        case 100 : TxStrenCodePUCMOS1 = 0x1; break;
        case 67  : TxStrenCodePUCMOS1 = 0x2; break;
        case 50  : TxStrenCodePUCMOS1 = 0x3; break;
        default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->TxImpedanceDTO[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->TxImpedanceDTO[pstate]);
    }
    TxStrenCodePDCMOS1 = TxStrenCodePUCMOS1;
  
    TxImpedanceCMOS1 = (TxStrenCodePUCMOS1 << csr_TxStrenCodePUCMOS1_LSB) | (TxStrenCodePDCMOS1 << csr_TxStrenCodePDCMOS1_LSB);
  
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceCMOS1::TxStrenCodePUCMOS1 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePUCMOS1);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxImpedanceCMOS1::TxStrenCodePDCMOS1 to 0x%x\n", printf_header, pstate, freq, TxStrenCodePDCMOS1);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_TxImpedanceCMOS1_ADDR), TxImpedanceCMOS1);
          
  
    /** 
     * - Program  OdtImpedanceSE0, OdtImpedanceSE1
     *            OdtImpedanceDIFF0T, OdtImpedanceDIFF0C
  
     *            OdtImpedanceDIFF1T, OdtImpedanceDIFF1C
  
     *
     *   - Dependencies 
     *     - UserInputAdvanced.OdtImpedanceDq
     *     - UserInputAdvanced.OdtImpedanceCa
     *     - UserInputAdvanced.OdtImpedanceCk
     *     - UserInputAdvanced.OdtImpedanceDqs
     *     - UserInputAdvanced.OdtImpedanceWCK
     *     - UserInputAdvanced.OdtImpedanceCs
     *     - mb1D[pstate].MR51_A0
     */
  
    // ********* Start ODT Impedance for DBYTE ********* //
    for (byte=0;byte<NumDbyte;byte++)  { // for each dbyte
        c_addr = byte*c1;
        
        int OdtImpedanceSE0 = 0;
        int OdtStrenCodePUSE0 = 0;
        int OdtStrenCodePDSE0 = 0;
  
        int OdtImpedanceDIFF0 = 0;
        int OdtStrenCodePUDIFF0 = 0;
        int OdtStrenCodePDDIFF0 = 0;
  
  
        int OdtImpedanceDIFF1 = 0;
        int OdtStrenCodePUDIFF1 = 0;
        int OdtStrenCodePDDIFF1 = 0;
  
        // *** DBYTE SE *** //
        switch ( pUserInputAdvanced->OdtImpedanceDq[pstate]) {
            case 120 : OdtStrenCodePDSE0 = 0x8; break;
            case 60  : OdtStrenCodePDSE0 = 0xc; break;
            case 40  : OdtStrenCodePDSE0 = 0xe; break;
            case 30  : OdtStrenCodePDSE0 = 0xf; break;
            case  0  : OdtStrenCodePDSE0 = 0x0; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->OdtImpedanceDq[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->OdtImpedanceDq[pstate]);
        }
  
        OdtImpedanceSE0 = (OdtStrenCodePUSE0 << csr_OdtStrenCodePUSE0_LSB) | (OdtStrenCodePDSE0 << csr_OdtStrenCodePDSE0_LSB);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceSE0::OdtStrenCodePUSE0 to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUSE0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceSE0::OdtStrenCodePDSE0 to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDSE0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_OdtImpedanceSE0_ADDR), OdtImpedanceSE0);
  
        // *** DBYTE DQS *** //
        switch ( pUserInputAdvanced->OdtImpedanceDqs[pstate]) {
            case 120 : OdtStrenCodePDDIFF0 = 0x8; break;
            case 60  : OdtStrenCodePDDIFF0 = 0xc; break;
            case 40  : OdtStrenCodePDDIFF0 = 0xe; break;
            case 30  : OdtStrenCodePDDIFF0 = 0xf; break;
            case  0  : OdtStrenCodePDDIFF0 = 0x0; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->OdtImpedanceDqs[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->OdtImpedanceDqs[pstate]);
        }
        
        OdtImpedanceDIFF0 = (OdtStrenCodePUDIFF0 << csr_OdtStrenCodePUDIFF0T_LSB) | (OdtStrenCodePDDIFF0 << csr_OdtStrenCodePDDIFF0T_LSB);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF0T::OdtStrenCodePUDIFF0T to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF0T::OdtStrenCodePDDIFF0T to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_OdtImpedanceDIFF0T_ADDR), OdtImpedanceDIFF0);

        OdtImpedanceDIFF0 = (OdtStrenCodePUDIFF0 << csr_OdtStrenCodePUDIFF0C_LSB) | (OdtStrenCodePDDIFF0 << csr_OdtStrenCodePDDIFF0C_LSB);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF0C::OdtStrenCodePUDIFF0C to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF0C::OdtStrenCodePDDIFF0C to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_OdtImpedanceDIFF0C_ADDR), OdtImpedanceDIFF0);
  
  
        // *** DBYTE WCK *** //
        switch ( pUserInputAdvanced->OdtImpedanceWCK[pstate]) {
            case 120 : OdtStrenCodePDDIFF1 = 0x8; break;
            case 60  : OdtStrenCodePDDIFF1 = 0xc; break;
            case 40  : OdtStrenCodePDDIFF1 = 0xe; break;
            case 30  : OdtStrenCodePDDIFF1 = 0xf; break;
            case  0  : OdtStrenCodePDDIFF1 = 0x0; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->OdtImpedanceWCK[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->OdtImpedanceWCK[pstate]);
        }
        
        OdtImpedanceDIFF1 = (OdtStrenCodePUDIFF1 << csr_OdtStrenCodePUDIFF1T_LSB) | (OdtStrenCodePDDIFF1 << csr_OdtStrenCodePDDIFF1T_LSB);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF1T::OdtStrenCodePUDIFF1T to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUDIFF1);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF1T::OdtStrenCodePDDIFF1T to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDDIFF1);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_OdtImpedanceDIFF1T_ADDR), OdtImpedanceDIFF1);
  
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF1C::OdtStrenCodePUDIFF1C to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUDIFF1);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE OdtImpedanceDIFF1C::OdtStrenCodePDDIFF1C to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDDIFF1);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_OdtImpedanceDIFF1C_ADDR), OdtImpedanceDIFF1);
  
  
    } // foreach dbyte
    // ********* End ODT Impedance for DBYTE ********* //

    // ********* Start ODT Impedance for AC ********* //
    for (achn=0; achn<NumAchn; achn++) {  // for each AC channel
        c_addr = achn*c1;

        int OdtImpedanceSE0 = 0;
        int OdtStrenCodePUSE0 = 0;
        int OdtStrenCodePDSE0 = 0;

        int OdtImpedanceSE1 = 0;
        int OdtStrenCodePUSE1 = 0;
        int OdtStrenCodePDSE1 = 0;

        int OdtImpedanceDIFF0 = 0;
        int OdtStrenCodePUDIFF0 = 0;
        int OdtStrenCodePDDIFF0 = 0;

        // *** AC SE *** //
        switch ( pUserInputAdvanced->OdtImpedanceCa[pstate]) {
            case 120 : OdtStrenCodePDSE0 = 0x8; break;
            case 60  : OdtStrenCodePDSE0 = 0xc; break;
            case 40  : OdtStrenCodePDSE0 = 0xe; break;
            case 30  : OdtStrenCodePDSE0 = 0xf; break;
            case  0  : OdtStrenCodePDSE0 = 0x0; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->OdtImpedanceCa[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->OdtImpedanceCa[pstate]);
        }

        OdtImpedanceSE0 = (OdtStrenCodePUSE0 << csr_OdtStrenCodePUSE0_LSB) | (OdtStrenCodePDSE0 << csr_OdtStrenCodePDSE0_LSB);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceSE0::OdtStrenCodePUSE0 to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUSE0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceSE0::OdtStrenCodePDSE0 to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDSE0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_OdtImpedanceSE0_ADDR), OdtImpedanceSE0);

  
        OdtStrenCodePUSE1 = OdtStrenCodePUSE0;
        OdtStrenCodePDSE1 = OdtStrenCodePDSE0;
        OdtImpedanceSE1 = (OdtStrenCodePUSE1 << csr_OdtStrenCodePUSE1_LSB) | (OdtStrenCodePDSE1 << csr_OdtStrenCodePDSE1_LSB);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceSE1::OdtStrenCodePUSE1 to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUSE1);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceSE1::OdtStrenCodePDSE1 to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDSE1);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_OdtImpedanceSE1_ADDR), OdtImpedanceSE1);

  
        // *** AC DIFF *** //
        switch ( pUserInputAdvanced->OdtImpedanceCk[pstate]) {
            case 120 : OdtStrenCodePDDIFF0 = 0x8; break;
            case 60  : OdtStrenCodePDDIFF0 = 0xc; break;
            case 40  : OdtStrenCodePDDIFF0 = 0xe; break;
            case 30  : OdtStrenCodePDDIFF0 = 0xf; break;
            case  0  : OdtStrenCodePDDIFF0 = 0x0; break;
            default  : dwc_ddrphy_phyinit_assert(0, "%s Invalid pUserInputAdvanced->OdtImpedanceCk[%d]=%d\n" , printf_header, pstate, pUserInputAdvanced->OdtImpedanceCk[pstate]);
        }
 
        OdtImpedanceDIFF0 = (OdtStrenCodePUDIFF0 << csr_OdtStrenCodePUDIFF0T_LSB) | (OdtStrenCodePDDIFF0 << csr_OdtStrenCodePDDIFF0T_LSB);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceDIFF0T::OdtStrenCodePUDIFF0T to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceDIFF0T::OdtStrenCodePDDIFF0T to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_OdtImpedanceDIFF0T_ADDR), OdtImpedanceDIFF0);
  
        OdtImpedanceDIFF0 = (OdtStrenCodePUDIFF0 << csr_OdtStrenCodePUDIFF0C_LSB) | (OdtStrenCodePDDIFF0 << csr_OdtStrenCodePDDIFF0C_LSB);

        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceDIFF0C::OdtStrenCodePUDIFF0C to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePUDIFF0);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC OdtImpedanceDIFF0C::OdtStrenCodePDDIFF0C to 0x%x\n", printf_header, pstate, freq, OdtStrenCodePDDIFF0);
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tAC | csr_OdtImpedanceDIFF0C_ADDR), OdtImpedanceDIFF0);
    }
    // ********* End ODT Impedance for AC ********* //


    /*
     * - Program Tx Slew Rate Control registers TxSlewSE0, TxSlewSE1, TxSlewDIFF0, TxSlewDIFF1
     *   - Dependencies: 
     *     - user_input_advanced.TxSlewRiseDq
     *     - user_input_advanced.TxSlewFallDq
     *     - user_input_advanced.TxSlewRiseDqs
     *     - user_input_advanced.TxSlewFallDqs
     *     - user_input_advanced.TxSlewRiseCA
     *     - user_input_advanced.TxSlewFallCA
  
     *     - user_input_advanced.TxSlewRiseCK
     *     - user_input_advanced.TxSlewFallCK
  
     *     - user_input_advanced.TxSlewRiseWCK
     *     - user_input_advanced.TxSlewFallWCK
  
     */
    uint16_t valTxSlewPU;
    uint16_t valTxSlewPD;
    uint16_t valTxSlew;
  
    for (achn=0; achn<NumAchn; achn++) {
        c_addr = achn << 12;
      
    
        // *** AC SE CA0-CA6 *** //
        valTxSlewPU = pUserInputAdvanced->TxSlewRiseCA[pstate];
        valTxSlewPD = pUserInputAdvanced->TxSlewFallCA[pstate];
        valTxSlew = (valTxSlewPU << csr_TxSlewPUSE0_LSB) | (valTxSlewPD << csr_TxSlewPDSE0_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewSE0::TxSlewPUSE0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPU);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewSE0::TxSlewPDSE0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPD);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewSE0 to 0x%x\n", printf_header, pstate, freq, valTxSlew);
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_TxSlewSE0_ADDR), valTxSlew);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewSE1::TxSlewPUSE1 to 0x%x\n", printf_header, pstate, freq, valTxSlewPU);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewSE1::TxSlewPDSE1 to 0x%x\n", printf_header, pstate, freq, valTxSlewPD);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewSE1 to 0x%x\n", printf_header, pstate, freq, valTxSlew);
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_TxSlewSE1_ADDR), valTxSlew);
    
    
        // *** AC DIFF CK *** //
        valTxSlewPU = pUserInputAdvanced->TxSlewRiseCK[pstate];
        valTxSlewPD = pUserInputAdvanced->TxSlewFallCK[pstate];
        valTxSlew = (valTxSlewPU << csr_TxSlewPUDIFF0_LSB) | (valTxSlewPD << csr_TxSlewPDDIFF0_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewDIFF0::TxSlewPUDIFF0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPU);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewDIFF0::TxSlewPDDIFF0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPD);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AC TxSlewDIFF0 to 0x%x\n", printf_header, pstate, freq, valTxSlew);
        dwc_ddrphy_phyinit_io_write16((p_addr | tAC | c_addr | csr_TxSlewDIFF0_ADDR), valTxSlew);
    } // achn
  
    for (byte=0;byte<NumDbyte;byte++)  {
        c_addr = byte << 12;
        
        // *** DBYTE SE DQ and DMI *** //
        valTxSlewPU = pUserInputAdvanced->TxSlewRiseDq[pstate];
        valTxSlewPD = pUserInputAdvanced->TxSlewFallDq[pstate];
        valTxSlew = (valTxSlewPU << csr_TxSlewPUSE0_LSB) | (valTxSlewPD << csr_TxSlewPDSE0_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewSE0::TxSlewPUSE0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPU);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewSE0::TxSlewPDSE0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPD);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewSE0 to 0x%x\n", printf_header, pstate, freq, valTxSlew);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxSlewSE0_ADDR), valTxSlew);
  
        // *** DBYTE DIFF DQS *** //
        valTxSlewPU = pUserInputAdvanced->TxSlewRiseDqs[pstate];
        valTxSlewPD = pUserInputAdvanced->TxSlewFallDqs[pstate];
        valTxSlew = (valTxSlewPU << csr_TxSlewPUDIFF0_LSB) | (valTxSlewPD << csr_TxSlewPDDIFF0_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewDIFF0::TxSlewPUDIFF0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPU);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewDIFF0::TxSlewPDDIFF0 to 0x%x\n", printf_header, pstate, freq, valTxSlewPD);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewDIFF0 to 0x%x\n", printf_header, pstate, freq, valTxSlew);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxSlewDIFF0_ADDR), valTxSlew);
    
  
        // *** DBYTE DIFF WCK *** //
        valTxSlewPU = pUserInputAdvanced->TxSlewRiseWCK[pstate];
        valTxSlewPD = pUserInputAdvanced->TxSlewFallWCK[pstate];
        valTxSlew = (valTxSlewPU << csr_TxSlewPUDIFF1_LSB) | (valTxSlewPD << csr_TxSlewPDDIFF1_LSB);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewDIFF1::TxSlewPUDIFF1 to 0x%x\n", printf_header, pstate, freq, valTxSlewPU);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewDIFF1::TxSlewPDDIFF1 to 0x%x\n", printf_header, pstate, freq, valTxSlewPD);
        dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DBYTE TxSlewDIFF1 to 0x%x\n", printf_header, pstate, freq, valTxSlew);
        dwc_ddrphy_phyinit_io_write16((p_addr | tDBYTE | c_addr | csr_TxSlewDIFF1_ADDR), valTxSlew);
    
    }


    /**
     *
     * - Program RxDiffSeDIFF0, RxDiffSeCtlDIFF0, RxDiffSeVrefDACEnDIFF0, RxDiffSeVrefDACDIFF0 if required.
  
    *   - mb1D[pstate].MR14_A0 
    *   - mb1D[pstate].MR15_A0 
    *   - mb1D[pstate].MR20_A0 
  
    *
    */
  
      for (byte=0;byte<NumDbyte;byte++)  { // for each dbyte
          c_addr = byte*c1;
          // Set the singleEndedModeRDQS variable based off the Mode Register input.
  
          uint16_t singleEndedModeRDQS = (mb1D[pstate].MR20_A0 & 0x3);
  
          uint16_t RxDiffSeCtlDIFF0 = 0x0;
          uint16_t RxDiffSeVrefDACEnDIFF0 = 0x0;
          uint16_t RxDiffSeVrefDACDIFF0 = 0x0;
  
          uint16_t mr;
          mr = ( byte%2==0 ) ? mb1D[pstate].MR14_A0  : mb1D[pstate].MR15_A0 ;
          RxDiffSeVrefDACDIFF0 = (int) (0.10 + 0.05*(mr & 0x7f)) * 128; 
  
          // Check if DQS is in Single-ended mode
          switch ( singleEndedModeRDQS ) {
              case 0  : break; // Strobless mode
              case 1  :  // DQS_t used
                        RxDiffSeCtlDIFF0 = 0x1;
                        RxDiffSeVrefDACEnDIFF0=0x1;
                        break;
              case 2  :  // differential
                        RxDiffSeCtlDIFF0 = 0x0;
                        RxDiffSeVrefDACEnDIFF0=0x0;
                        break;
              case 3  :  // DQS_c used
                        RxDiffSeCtlDIFF0 = 0x2;
                        RxDiffSeVrefDACEnDIFF0=0x1;
                        break;
              default : dwc_ddrphy_phyinit_assert(0, "%s Invalid singleEndedModeRDQS = %d, pstate = %d\n" , printf_header, singleEndedModeRDQS, pstate); 
          }
  
          uint16_t RxDiffSeDIFF0 = ( ((RxDiffSeCtlDIFF0 << csr_RxDiffSeCtlDIFF0_LSB) & csr_RxDiffSeCtlDIFF0_MASK) |
                                     ((RxDiffSeVrefDACEnDIFF0 << csr_RxDiffSeVrefDACEnDIFF0_LSB) & csr_RxDiffSeVrefDACEnDIFF0_MASK)
                                   );
  

          dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming DBYTE%d.RxDiffSeDIFF0::RxDiffSeCtlDIFF0 to 0x%x\n", printf_header, pstate, byte, RxDiffSeCtlDIFF0 );
          dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming DBYTE%d.RxDiffSeDIFF0::RxDiffSeVrefDACEnDIFF0 to 0x%x\n", printf_header, pstate, byte, RxDiffSeVrefDACEnDIFF0 );
          dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming DBYTE%d.RxDiffSeDIFF0 to 0x%x\n", printf_header, pstate, byte, RxDiffSeDIFF0);
          dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxDiffSeDIFF0_ADDR), RxDiffSeDIFF0);

          dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, DBYTE=%d Programming RxDiffSeVrefDACDIFF0 to 0x%x\n", printf_header, pstate, byte, RxDiffSeVrefDACDIFF0);
          dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxDiffSeVrefDACDIFF0_ADDR), RxDiffSeVrefDACDIFF0);

        } // dbyte
  
  
  
    /*
     * - Program WriteLinkEcc
     *   - Dependencies:
     *     - mb1D[pstate].MR22_A0
     */
    regData = ((mb1D[pstate].MR22_A0 & 0x30) == 0x10) ? 0x1 : 0x0;
    dwc_ddrphy_phyinit_cmnt ("%s Programming WriteLinkEcc to %d\n", printf_header, regData);
    for (byte=0;byte<NumDbyte;byte++) // for each dbyte
      { 
        c_addr = byte*c1;
        dwc_ddrphy_phyinit_io_write16((p_addr  | c_addr | tDBYTE | csr_EnableWriteLinkEcc_ADDR), regData); 
      }
  


     /**
     * - Program initial values for DllGainCtl, DxDllLockParam and AcDllLockParam
     *   and also RxReplicaDllGainCtl, RxReplicaDllLockParam.
     *
     */
    uint16_t AcDllGainIV=0x1;
    uint16_t AcDllGainTV=0xa;
    uint16_t DxDllGainIV=0x1;
    uint16_t DxDllGainTV=0xa;
    uint16_t RxDllGainIV=0x1;
    uint16_t RxDllGainTV=0xa;
    uint16_t wdDxDllLockParam=0x40;
    uint16_t wdAcDllLockParam=0x40;
    uint16_t RxRpDllLockParam=0x40;

    uint16_t wdDllGainCtl = (csr_AcDllGainTV_MASK  & (AcDllGainTV << csr_AcDllGainTV_LSB))
                          | (csr_AcDllGainIV_MASK  & (AcDllGainIV << csr_AcDllGainIV_LSB))
                          | (csr_DxDllGainTV_MASK  & (DxDllGainTV << csr_DxDllGainTV_LSB))
                          | (csr_DxDllGainIV_MASK  & (DxDllGainIV << csr_DxDllGainIV_LSB));

    uint16_t RxReplicaDllGainCtl = (csr_RxReplicaDllGainTV_MASK & (RxDllGainTV << csr_RxReplicaDllGainTV_LSB))
                                 | (csr_RxReplicaDllGainIV_MASK & (RxDllGainIV << csr_RxReplicaDllGainIV_LSB));

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming DllGainCtl to 0x%x\n", printf_header, pstate, wdDllGainCtl);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DllGainCtl_ADDR), wdDllGainCtl);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, DX Programming DxDllLockParam to 0x%x\n", printf_header, pstate, wdDxDllLockParam);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DxDllLockParam_ADDR), wdDxDllLockParam << csr_DxLcdlSeed0_LSB);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, AC Programming AcDllLockParam to 0x%x\n", printf_header, pstate, wdAcDllLockParam);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_AcDllLockParam_ADDR), wdAcDllLockParam << csr_AcLcdlSeed0_LSB);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming RxReplicaDllGainCtl to 0x%x\n", printf_header, pstate, RxReplicaDllGainCtl);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_RxReplicaDllGainCtl_ADDR), RxReplicaDllGainCtl);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, DX Programming RxReplicaDllLockParam to 0x%x\n", printf_header, pstate, RxRpDllLockParam);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_RxReplicaDllLockParam_ADDR), RxRpDllLockParam << csr_RxReplicaLcdlSeed_LSB);

  
    /**
     * - Registers: PPTTrainSetup and PPTTrainSetup2
     *   - Related to DFI PHY Master Interface (PMI). See Register description in PUB. 
     *   - Enable DFI PMI if training firmware was run
     *   - Fields:
     *     - PhyMstrTrainInterval
     *     - PhyMstrMaxReqToAck
     *     - PhyMstrFreqOverride
     *     - PhyMstrCtrlMode
     *   - Dependencies:
     *     - skip_training
     *     - user_input_basic.Frequency
     *     - user_input_advanced.PhyMstrTrainInterval
     *     - user_input_advanced.PhyMstrMaxReqToAck
     *     - user_input_advanced.PhyMstrCtrlMode
     */
    int freqThreshold = pUserInputBasic->DfiFreqRatio[pstate] == 1 ? 166 : 83;

    uint16_t PhyMstrFreqOverride; 
    uint16_t PPTTrainSetup;
    if(freq >= freqThreshold)
      {
        PPTTrainSetup = (pUserInputAdvanced->PhyMstrTrainInterval[pstate] << csr_PhyMstrTrainInterval_LSB) |
                        (pUserInputAdvanced->PhyMstrMaxReqToAck[pstate] << csr_PhyMstrMaxReqToAck_LSB) |
                        (pUserInputAdvanced->PhyMstrCtrlMode[pstate] << csr_PhyMstrCtrlMode_LSB);
       PhyMstrFreqOverride = 0xf;
      }
    else
      {
        PhyMstrFreqOverride=0x0; 
        PPTTrainSetup=0x0;
      } 
       
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PPTTrainSetup::PhyMstrTrainInterval to 0x%x\n",
           printf_header, pstate, freq,
           pUserInputAdvanced->PhyMstrTrainInterval[pstate]);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PPTTrainSetup::PhyMstrMaxReqToAck to 0x%x\n",
           printf_header, pstate, freq,
           pUserInputAdvanced->PhyMstrMaxReqToAck[pstate]);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PPTTrainSetup::PhyMstrCtrlMode to 0x%x\n",
           printf_header, pstate, freq,
           pUserInputAdvanced->PhyMstrCtrlMode[pstate]);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_PPTTrainSetup_ADDR), PPTTrainSetup);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming PPTTrainSetup2::PhyMstrFreqOverride to 0x%x\n",
           printf_header, pstate, freq, PhyMstrFreqOverride);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_PPTTrainSetup2_ADDR), PhyMstrFreqOverride);

    /**
     * - Register: RxTrainPattern8BitMode
     *   - Dependencies:
     *    - user_input_basic.DfiFreqRatio
     */
    for (byte=0; byte < NumDbyte ; byte++)
      { // for each chiplet
        c_addr = byte*c1;
        uint16_t RxTrnPtrn= (pUserInputBasic->DfiFreqRatio[pstate] == 0x2) ? 0x1 : 0x0;
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxTrainPattern8BitMode_ADDR), RxTrnPtrn);
      }


    /**
     * - Program RxReplicaRangeVal
     *   - Fields
     *     - RxReplicaShortCalRangeA
     *     - RxReplicaShortCalRangeB
     */
    uint16_t RxReplicaShortRange = ((RxReplicaShortRangeA << csr_RxReplicaShortCalRangeA_LSB) & csr_RxReplicaShortCalRangeA_MASK)
                                 | ((RxReplicaShortRangeB << csr_RxReplicaShortCalRangeB_LSB) & csr_RxReplicaShortCalRangeB_MASK);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming RxReplicaRangeVal 0x%x\n", printf_header, pstate, RxReplicaShortRange);

    for (byte=0; byte<NumDbyte; byte++) {
        c_addr = byte * c1;
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxReplicaRangeVal_ADDR), RxReplicaShortRange);
    }


     /**
     * - Program RxReplicaCtl04
     *   - Fields
     *     - RxReplicaTrackEn
     *     - RxReplicaLongCal
     *     - RxReplicaStride
     */
    uint16_t RxReplicaCtl = (0 << csr_RxReplicaTrackEn_LSB) // disable RxClk tracking before training
                          | (1 << csr_RxReplicaLongCal_LSB) // long cal during boot
                          | (1 << csr_RxReplicaStride_LSB);

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Programming RxReplicaCtl04 to 0x%x\n", printf_header, pstate, RxReplicaCtl);

    for (byte=0; byte<NumDbyte; byte++) {
        c_addr = c1 * byte;
        dwc_ddrphy_phyinit_io_write16((p_addr | c_addr | tDBYTE | csr_RxReplicaCtl04_ADDR), RxReplicaCtl);
    }

    // User input validation
    uint16_t RxReplicaTrackEn = (pUserInputAdvanced->RxClkTrackEn[pstate] == 1) ? 1: 0;
    int DisableRetraining = pUserInputAdvanced->DisableRetraining;

    if (freq <= freqThreshold && RxReplicaTrackEn == 1) {
        dwc_ddrphy_phyinit_assert(0, "%s Pstate=%d RxClk tracking cannot be enabled for low data rates, CK frequency = %d\n",printf_header, pstate, freq);
    }

    if (DisableRetraining != 0 && RxReplicaTrackEn == 1) {
        dwc_ddrphy_phyinit_assert(0, "%s Pstate=%d RxClk tracking cannot be enabled when retraining is disabled (DisableRetraining = %d)\n",printf_header, pstate, DisableRetraining);
    }

    if ((mb1D[pstate].MR20_A0 & 0x3) == 0x0 && RxReplicaTrackEn == 1) {
        dwc_ddrphy_phyinit_assert(0, "%s Pstate=%d RxClk tracking cannot be enabled in strobe-less read mode\n",printf_header, pstate);
    }

    /**
     * - Program WCK pulse registers for ACSM
     *      - ACSMWckWriteStaticLoPulse
     *      - ACSMWckWriteStaticHiPulse
     *      - ACSMWckWriteTogglePulse
     *      - ACSMWckWriteFastTogglePulse
     *      - ACSMWckReadStaticLoPulse
     *      - ACSMWckReadStaticHiPulse
     *      - ACSMWckReadTogglePulse
     *      - ACSMWckReadFastTogglePulse
     *      - ACSMWckFreqSwStaticLoPulse
     *      - ACSMWckFreqSwStaticHiPulse
     *      - ACSMWckFreqSwTogglePulse
     *      - ACSMWckFreqSwFastTogglePulse
     *   - Dependencies:
     *     - user_input_basic.Frequency
     *     - user_input_basic.DfiFreqRatio
     */
    const uint16_t RD_AC_FREQ_LOWER        = 0;
    const uint16_t RD_AC_FREQ_UPPER        = 1;
    const uint16_t RD_AC_RL_SETA           = 2;
    const uint16_t RD_AC_RL_SETB           = 3;
    const uint16_t RD_AC_RL_SETC           = 4;
    const uint16_t RD_AC_TWCKENL_RD_SETA   = 5;
    const uint16_t RD_AC_TWCKENL_RD_SETB   = 6;
    const uint16_t RD_AC_TWCKENL_RD_SETC   = 7;
    const uint16_t RD_AC_TWCKENL_RD_ECC_A  = 5;
    const uint16_t RD_AC_TWCKENL_RD_ECC_B  = 6;
    const uint16_t RD_AC_TWCKEPRE_STATIC   = 8;
    const uint16_t RD_AC_TWCKEPRE_TOGGLE_RD= 9;
    const uint16_t FS_AC_TWCKENL_FS        = 3;
    const uint16_t WR_AC_WL_SETA           = 2;
    const uint16_t WR_AC_WL_SETB           = 3;
    const uint16_t WR_AC_TWCKENL_WR_SETA   = 4;
    const uint16_t WR_AC_TWCKEPRE_TOGGLE_WR= 7;

    // DVFSC disabled, Read Link ECC disabled
    static const uint16_t WCK2CK_Sync_RD_lookup_A[2][12][11] = {
        {
            {  10, 133,6 ,6 ,6 ,0 ,0 ,0 ,1 ,6 ,7 },
            { 133, 267,8 ,8 ,8 ,0 ,0 ,0 ,2 ,7 ,9 },
            { 267, 400,10,10,12,1 ,1 ,3 ,2 ,8 ,10},
            { 400, 533,12,14,14,2 ,4 ,4 ,3 ,8 ,11},
            { 533, 688,16,16,18,3 ,3 ,5 ,4 ,10,14},
            { 688, 800,18,20,20,5 ,7 ,7 ,4 ,10,14}
        },
        {
            {   5,  67,3 ,3 ,3 ,0 ,0 ,0 ,1 ,3 ,4 },
            {  67, 133,4 ,4 ,4 ,0 ,0 ,0 ,1 ,4 ,5 },
            { 133, 200,5 ,5 ,6 ,1 ,1 ,2 ,1 ,4 ,5 },
            { 200, 267,6 ,7 ,7 ,1 ,2 ,2 ,2 ,4 ,6 },
            { 267, 344,8 ,8 ,9 ,2 ,2 ,3 ,2 ,5 ,7 },
            { 344, 400,9 ,10,10,3 ,4 ,4 ,2 ,5 ,7 },
            { 400, 467,10,11,12,3 ,4 ,5 ,3 ,5 ,8 },
            { 467, 533,12,13,14,4 ,5 ,6 ,3 ,6 ,9 },
            { 533, 600,13,14,15,5 ,6 ,7 ,3 ,6 ,9 },
            { 600, 688,15,16,17,6 ,7 ,8 ,4 ,6 ,10},
            { 688, 750,16,17,19,6 ,7 ,9 ,4 ,7 ,11},
            { 750, 800,17,18,20,7 ,8 ,10,4 ,7 ,11}
        }
    };

    // DVFSC enabled, Read Link ECC disabled
    static const uint16_t WCK2CK_Sync_RD_lookup_B[2][3][11] = {
        {
            {  10, 133,6 ,6 ,6 ,0 ,0 ,0 ,1 ,6 ,7 },
            { 133, 267,8 ,10,10,0 ,2 ,2 ,2 ,7 ,9 },
            { 267, 400,12,12,14,3 ,3 ,5 ,2 ,8 ,10}
        },
        {
            {   5,  67,3 ,3 ,3 ,0 ,0 ,0 ,1 ,3 ,4 },
            {  67, 133,4 ,5 ,5 ,0 ,1 ,1 ,1 ,4 ,5 },
            { 133, 200,6 ,6 ,7 ,2 ,2 ,3 ,1 ,4 ,5 }
        }
    };

    // DVFSC disabled, Read Link ECC enabled
    static const uint16_t WCK2CK_Sync_RD_lookup_C[1][6][11] = {
        {
            { 400, 467,12,13,0 ,5 ,6 ,0 ,3 ,5 ,8 },
            { 467, 533,13,14,0 ,5 ,6 ,0 ,3 ,6 ,9 },
            { 533, 600,15,16,0 ,7 ,8 ,0 ,3 ,6 ,9 },
            { 600, 688,17,18,0 ,8 ,9 ,0 ,4 ,6 ,10},
            { 688, 750,18,20,0 ,8 ,10,0 ,4 ,7 ,11},
            { 750, 800,19,21,0 ,9 ,11,0 ,4 ,7 ,11}
        }
    };

    static const uint16_t WCK2CK_Sync_WR_lookup[2][12][9] = {
        {
            {  10, 133,4 ,4 ,1,1,1,3,4},
            { 133, 267,4 ,6 ,0,2,2,3,5},
            { 267, 400,6 ,8 ,1,3,2,4,6},
            { 400, 533,8 ,10,2,4,3,4,7},
            { 533, 688,8 ,14,1,7,4,4,8},
            { 688, 800,10,16,3,9,4,4,8}
        },
        {
            {   5,  67,2,2 ,0,0 ,1,2,3},
            {  67, 133,2,3 ,0,1 ,1,2,3},
            { 133, 200,3,4 ,1,2 ,1,2,3},
            { 200, 267,4,5 ,1,2 ,2,2,4},
            { 267, 344,4,7 ,1,4 ,2,2,4},
            { 344, 400,5,8 ,2,5 ,2,2,4},
            { 400, 467,6,9 ,2,5 ,3,2,5},
            { 467, 533,6,11,2,7 ,3,2,5},
            { 533, 600,7,12,3,8 ,3,2,5},
            { 600, 688,8,14,3,9 ,4,2,6},
            { 688, 750,9,15,4,10,4,2,6},
            { 750, 800,9,16,4,11,4,2,6}
        }
    };

    static const uint16_t WCK2CK_Sync_FS_lookup[2][12][5] = 
    {
        {
            {  10, 133,0x0,0,1},
            { 133, 267,0x1,0,2},
            { 267, 400,0x2,1,2},
            { 400, 533,0x3,1,3},
            { 533, 688,0x4,1,4},
            { 688, 800,0x5,2,4}
        },
        {
            {   5,  67,0x0,0,1},
            {  67, 133,0x1,0,1},
            { 133, 200,0x2,1,1},
            { 200, 267,0x3,1,2},
            { 267, 344,0x4,1,2},
            { 344, 400,0x5,1,2},
            { 400, 467,0x6,1,3},
            { 467, 533,0x7,1,3},
            { 533, 600,0x8,2,3},
            { 600, 688,0x9,2,4},
            { 688, 750,0xa,2,4},
            { 750, 800,0xb,2,4}
        }
    };

    const uint16_t* WCK2CK_Sync_RD_lookup;
    uint16_t RD_AC_RL;
    uint16_t WR_AC_WL;
    uint16_t RD_AC_TWCKENL_RD;
    uint16_t tWCKPST;
    uint8_t ratioIndex;
    uint8_t numSpeeds;

    uint16_t BLdiv2 = 8 ;
    uint16_t readLatency = 3;
    uint16_t writeLatency = 3;
    uint16_t tWCKENL_WR = 0;
    uint16_t tWCKENL_RD = 0 ;
    uint16_t tWCKENL_FS = 0 ;
    uint16_t tWCKPRE_static = 2 ;
    uint16_t tWCKPRE_Toggle_WR = 3 ;
    uint16_t tWCKPRE_Toggle_RD = 6 ;
    uint16_t tWCKPRE_Toggle_FS = 3 ;

    uint8_t dvfsc = mb1D[pstate].MR19_A0 & 0x3;
    uint8_t readLinkEcc = (mb1D[pstate].MR22_A0 >> 6) & 0x3;
    uint8_t readDbi = (mb1D[pstate].MR3_A0 >> 6) & 1;
    uint8_t readCpy = (mb1D[pstate].MR21_A0 >> 5) & 1;
    uint8_t readEither = (readDbi | readCpy) & 1;
    uint8_t byteMode = (pUserInputBasic->DramDataWidth == 8) ? 1 : 0;

    if (dvfsc) {
        ratioIndex = ratio == 2 ? 0 : 1; 
        numSpeeds = 3;
        WCK2CK_Sync_RD_lookup = WCK2CK_Sync_RD_lookup_B[ratioIndex][0];
    } else if (readLinkEcc) {
        ratioIndex = 0;
        numSpeeds = 6;
        WCK2CK_Sync_RD_lookup = WCK2CK_Sync_RD_lookup_C[ratioIndex][0];
    } else {
        ratioIndex = ratio == 2 ? 0 : 1;
        numSpeeds = ratioIndex ? 12 : 6;
        WCK2CK_Sync_RD_lookup = WCK2CK_Sync_RD_lookup_A[ratioIndex][0];
    }

    if (readLinkEcc) {
        if (byteMode) {
            RD_AC_RL = RD_AC_RL_SETB;
            RD_AC_TWCKENL_RD = RD_AC_TWCKENL_RD_ECC_B;
        } else {
            RD_AC_RL = RD_AC_RL_SETA;
            RD_AC_TWCKENL_RD = RD_AC_TWCKENL_RD_ECC_A;
        }
    } else {
        switch (readEither + byteMode) {
            case 2:
                RD_AC_RL = RD_AC_RL_SETC;
                RD_AC_TWCKENL_RD = RD_AC_TWCKENL_RD_SETC;
                break;
            case 1:
                RD_AC_RL = RD_AC_RL_SETB;
                RD_AC_TWCKENL_RD = RD_AC_TWCKENL_RD_SETB;
                break;
            case 0:
            default:
                RD_AC_RL = RD_AC_RL_SETA;
                RD_AC_TWCKENL_RD = RD_AC_TWCKENL_RD_SETA;
        }
    }

    //Write Latency Set
    if((mb1D[pstate].MR3_A0 >> 5 ) & 1) {
      WR_AC_WL = WR_AC_WL_SETB;
    } else {
      WR_AC_WL = WR_AC_WL_SETA;
    }


    switch((mb1D[pstate].MR10_A0 >> 2) & 0x3) {
        case 2: // 6.5*tWCK
            tWCKPST = 6+1;
            break;
        case 1: // 4.5*tWCK
            tWCKPST = 4+1;
            break;
        case 0: // 2.5*tWCK (default)
        default:
            tWCKPST = 2+1;
    }

    uint16_t lowFreqBuffer = 0;

    // Read parameters
    for (int i = 0; i < numSpeeds; ++i) {
        if ( (freq)  > WCK2CK_Sync_RD_lookup[i*11 + RD_AC_FREQ_LOWER] &&
             (freq) <= WCK2CK_Sync_RD_lookup[i*11 + RD_AC_FREQ_UPPER] ) {

            if (freq <= 133 && ratio == 4) {
                lowFreqBuffer = 1; 
            } else if (freq <= 267 && ratio == 2) {
                lowFreqBuffer = 2;       
            } else if (freq <= 688 && freq >= 267 && ratio == 2) {
                lowFreqBuffer = 1; 
            } else {
                lowFreqBuffer = 0;
            }

            readLatency       = WCK2CK_Sync_RD_lookup[i*11 + RD_AC_RL] + lowFreqBuffer;
            tWCKENL_RD        = WCK2CK_Sync_RD_lookup[i*11 + RD_AC_TWCKENL_RD] + lowFreqBuffer;
            tWCKPRE_static    = WCK2CK_Sync_RD_lookup[i*11 + RD_AC_TWCKEPRE_STATIC];
            tWCKPRE_Toggle_RD = WCK2CK_Sync_RD_lookup[i*11 + RD_AC_TWCKEPRE_TOGGLE_RD];
            break;
        }
    }

    // Write and Fast Toggle parameters
    ratioIndex = ratio == 2 ? 0 : 1;
    numSpeeds = ratioIndex ? 12 : 6;
    for (int i = 0; i < numSpeeds; ++i) {
        if ( (freq)  > WCK2CK_Sync_WR_lookup[ratioIndex][i][RD_AC_FREQ_LOWER] &&
             (freq) <= WCK2CK_Sync_WR_lookup[ratioIndex][i][RD_AC_FREQ_UPPER] ) {

            writeLatency      = WCK2CK_Sync_WR_lookup[ratioIndex][i][WR_AC_WL] + lowFreqBuffer;
            tWCKENL_WR        = WCK2CK_Sync_WR_lookup[ratioIndex][i][WR_AC_TWCKENL_WR_SETA] + lowFreqBuffer;
            tWCKENL_FS        = WCK2CK_Sync_FS_lookup[ratioIndex][i][FS_AC_TWCKENL_FS] + lowFreqBuffer;
            tWCKPRE_Toggle_WR = WCK2CK_Sync_WR_lookup[ratioIndex][i][WR_AC_TWCKEPRE_TOGGLE_WR];
            tWCKPRE_Toggle_FS = WCK2CK_Sync_WR_lookup[ratioIndex][i][WR_AC_TWCKEPRE_TOGGLE_WR];
            break;
        }
    }

    uint16_t wrSdly   = (tWCKENL_WR*ratio)-4;
    uint16_t wrSwd    = tWCKPRE_static*ratio;
    uint16_t wrTGdly  = ((tWCKENL_WR+tWCKPRE_static)*ratio)-4;
    uint16_t wrTGwd   = 1*ratio;
    uint16_t wrFTGdly = ((tWCKENL_WR+tWCKPRE_static+1)*ratio)-4;
    uint16_t wrFTGwd  = ((tWCKPRE_Toggle_WR-1)*ratio)+BLdiv2+tWCKPST ;

    uint16_t rdSdly   = (tWCKENL_RD*ratio)-4;
    uint16_t rdSwd    = tWCKPRE_static*ratio;
    uint16_t rdTGdly  = ((tWCKENL_RD+tWCKPRE_static)*ratio)-4;
    uint16_t rdTGwd   = 1*ratio;
    uint16_t rdFTGdly = ((tWCKENL_RD+tWCKPRE_static+1)*ratio)-4;
    uint16_t rdFTGwd  = ((tWCKPRE_Toggle_RD-1)*ratio)+BLdiv2+tWCKPST ;

    uint16_t fsSdly   = (tWCKENL_FS*ratio)-4;
    uint16_t fsSwd    = tWCKPRE_static*ratio;
    uint16_t fsTGdly  = ((tWCKENL_FS+tWCKPRE_static)*ratio)-4;
    uint16_t fsTGwd   = 1*ratio;
    uint16_t fsFTGdly = ((tWCKENL_FS+tWCKPRE_static+1)*ratio)-4;
    uint16_t fsFTGwd  = ((tWCKPRE_Toggle_FS-1)*ratio)+BLdiv2+tWCKPST ;

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckWriteStaticLoPulse::ACSMWckWriteStaticLoWidth to 0x%x, "
            "ACSMWckWriteStaticLoPulse::ACSMWckWriteStaticLoDelay to 0x%x\n", printf_header, pstate, freq, wrSwd, wrSdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckWriteStaticHiPulse::ACSMWckWriteStaticHiWidth to 0x%x, "
            "ACSMWckWriteStaticHiPulse::ACSMWckWriteStaticHiDelay to 0x%x\n", printf_header, pstate, freq, wrSwd, wrSdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckWriteTogglePulse::ACSMWckWriteToggleWidth to 0x%x, "
            "ACSMWckWriteTogglePulse::ACSMWckWriteToggleDelay to 0x%x\n", printf_header, pstate, freq, wrTGwd, wrTGdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckWriteFastTogglePulse::ACSMWckWriteFastToggleWidth to 0x%x, "
            "ACSMWckWriteFastTogglePulse::ACSMWckWriteFastToggleDelay to 0x%x\n", printf_header, pstate, freq, wrFTGwd, wrFTGdly);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckWriteStaticLoPulse_ADDR   ), (wrSwd << csr_ACSMWckWriteStaticLoWidth_LSB)     | (wrSdly << csr_ACSMWckWriteStaticLoDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckWriteStaticHiPulse_ADDR   ), (wrSwd << csr_ACSMWckWriteStaticHiWidth_LSB)     | (wrSdly << csr_ACSMWckWriteStaticHiDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckWriteTogglePulse_ADDR     ), (wrTGwd << csr_ACSMWckWriteToggleWidth_LSB)      | (wrTGdly << csr_ACSMWckWriteToggleDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckWriteFastTogglePulse_ADDR ), (wrFTGwd << csr_ACSMWckWriteFastToggleWidth_LSB) | (wrFTGdly << csr_ACSMWckWriteFastToggleDelay_LSB));

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckReadStaticLoPulse::ACSMWckReadStaticLoWidth to 0x%x, "
            "ACSMWckReadStaticLoPulse::ACSMWckReadStaticLoDelay to 0x%x\n", printf_header, pstate, freq, rdSwd, rdSdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckReadStaticHiPulse::ACSMWckReadStaticHiWidth to 0x%x, "
            "ACSMWckReadStaticHiPulse::ACSMWckReadStaticHiDelay to 0x%x\n", printf_header, pstate, freq, rdSwd, rdSdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckReadTogglePulse::ACSMWckReadToggleWidth to 0x%x, "
            "ACSMWckReadTogglePulse::ACSMWckReadToggleDelay to 0x%x\n", printf_header, pstate, freq, rdTGwd, rdTGdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckReadFastTogglePulse::ACSMWckReadFastToggleWidth to 0x%x, "
            "ACSMWckReadFastTogglePulse::ACSMWckReadFastToggleDelay to 0x%x\n", printf_header, pstate, freq, rdFTGwd, rdFTGdly);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckReadStaticLoPulse_ADDR    ), (rdSwd << csr_ACSMWckReadStaticLoWidth_LSB)      | (rdSdly << csr_ACSMWckReadStaticLoDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckReadStaticHiPulse_ADDR    ), (rdSwd << csr_ACSMWckReadStaticHiWidth_LSB)      | (rdSdly << csr_ACSMWckReadStaticHiDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckReadTogglePulse_ADDR      ), (rdTGwd << csr_ACSMWckReadToggleWidth_LSB)       | (rdTGdly << csr_ACSMWckReadToggleDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckReadFastTogglePulse_ADDR  ), (rdFTGwd << csr_ACSMWckReadFastToggleWidth_LSB)  | (rdFTGdly << csr_ACSMWckReadFastToggleDelay_LSB));

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckFreqStaticLoPulse::ACSMWckFreqStaticLoWidth to 0x%x, "
            "ACSMWckFreqStaticLoPulse::ACSMWckFreqStaticLoDelay to 0x%x\n", printf_header, pstate, freq, fsSwd, fsSdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckFreqStaticHiPulse::ACSMWckFreqStaticHiWidth to 0x%x, "
            "ACSMWckFreqStaticHiPulse::ACSMWckFreqStaticHiDelay to 0x%x\n", printf_header, pstate, freq, fsSwd, fsSdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckFreqTogglePulse::ACSMWckFreqToggleWidth to 0x%x, "
            "ACSMWckFreqTogglePulse::ACSMWckFreqToggleDelay to 0x%x\n", printf_header, pstate, freq, fsTGwd, fsTGdly);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWckFreqFastTogglePulse::ACSMWckFreqFastToggleWidth to 0x%x, "
            "ACSMWckFreqFastTogglePulse::ACSMWckFreqFastToggleDelay to 0x%x\n", printf_header, pstate, freq, fsFTGwd, fsFTGdly);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckFreqSwStaticLoPulse_ADDR  ), (fsSwd << csr_ACSMWckFreqSwStaticLoWidth_LSB)    | (fsSdly << csr_ACSMWckFreqSwStaticLoDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckFreqSwStaticHiPulse_ADDR  ), (fsSwd << csr_ACSMWckFreqSwStaticHiWidth_LSB)    | (fsSdly << csr_ACSMWckFreqSwStaticHiDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckFreqSwTogglePulse_ADDR    ), (fsTGwd << csr_ACSMWckFreqSwToggleWidth_LSB)     | (fsTGdly << csr_ACSMWckFreqSwToggleDelay_LSB));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWckFreqSwFastTogglePulse_ADDR), (fsFTGwd << csr_ACSMWckFreqSwFastToggleWidth_LSB)| (fsFTGdly << csr_ACSMWckFreqSwFastToggleDelay_LSB));

    /**
     * - Program Rx pulse registers for ACSM
     */
    uint16_t rxPulseDly = (ratio * readLatency) - 5;
    uint16_t rxPulseWd = BLdiv2;

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMRxEnPulse::ACSMRxEnDelay to 0x%x, "
            "ACSMRxEnPulse::ACSMRxEnWidth to 0x%x\n", printf_header, pstate, freq, rxPulseDly, rxPulseWd);
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMRxValPulse::ACSMRxValDelay to 0x%x, "
            "ACSMRxValPulse::ACSMRxValWidth to 0x%x\n", printf_header, pstate, freq, rxPulseDly, rxPulseWd);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMRxEnPulse_ADDR),  ((rxPulseDly << csr_ACSMRxEnDelay_LSB)  & csr_ACSMRxEnDelay_MASK)  | ((rxPulseWd << csr_ACSMRxEnWidth_LSB)  & csr_ACSMRxEnWidth_MASK));
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMRxValPulse_ADDR), ((rxPulseDly << csr_ACSMRxValDelay_LSB) & csr_ACSMRxValDelay_MASK) | ((rxPulseWd << csr_ACSMRxValWidth_LSB) & csr_ACSMRxValWidth_MASK));

    if (pUserInputAdvanced->WDQSExt) {
        rxPulseDly -= 2;
        rxPulseWd += 2;
    }

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMRdcsPulse::ACSMRdcsDelay to 0x%x, "
            "ACSMRdcsPulse::ACSMRdcsWidth to 0x%x\n", printf_header, pstate, freq, rxPulseDly, rxPulseWd);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMRdcsPulse_ADDR), ((rxPulseDly << csr_ACSMRdcsDelay_LSB) & csr_ACSMRdcsDelay_MASK) | ((rxPulseWd << csr_ACSMRdcsWidth_LSB) & csr_ACSMRdcsWidth_MASK));

    uint16_t txPulseDly = (ratio * writeLatency) - 5;
    uint16_t txPulseWd = BLdiv2;

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMTxEnPulse::ACSMTxEnDelay to 0x%x, "
            "ACSMTxEnPulse::ACSMTxEnWidth to 0x%x\n", printf_header, pstate, freq, txPulseDly, txPulseWd);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMTxEnPulse_ADDR),  ((txPulseDly << csr_ACSMTxEnDelay_LSB)  & csr_ACSMTxEnDelay_MASK)  | ((txPulseWd << csr_ACSMTxEnWidth_LSB)  & csr_ACSMTxEnWidth_MASK));

    /**
     * - Program Tx pulse registers for ACSM
     */
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming ACSMWrcsPulse::ACSMWrcsDelay to 0x%x, "
            "ACSMWrcsPulse::ACSMWrcsWidth to 0x%x\n", printf_header, pstate, freq, txPulseDly, txPulseWd);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_ACSMWrcsPulse_ADDR), ((txPulseDly << csr_ACSMWrcsDelay_LSB) & csr_ACSMWrcsDelay_MASK) | ((txPulseWd << csr_ACSMWrcsWidth_LSB) & csr_ACSMWrcsWidth_MASK));

    /**
     * - Program AcPipeEn. 
     *   - Dependencies:
     *     - user_input_basic.Frequency
     *     - user_input_basic.DfiFreqRatio
     *
     */
    uint16_t AcPipeEn = ((pUserInputBasic->DfiFreqRatio[pstate] == 1) ? ((freq <= 267) ? 2 : ((freq <= 688) ? 1 : 0)) : ((freq <= 133) ? 1 : 0));
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming AcPipeEn to %d. DFI ratio is %d\n", printf_header, pstate, freq, AcPipeEn, pUserInputBasic->DfiFreqRatio[pstate]);
    dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_AcPipeEn_ADDR), AcPipeEn);

    uint16_t CtrlUpdReqDelay = 2;
    uint16_t PhyUpdAckDelay = 3;
    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DfiHandshakeDelays ", printf_header, pstate, freq);
    for (achn=0; achn<NumAchn; achn++) {
      c_addr = achn << 12;
      dwc_ddrphy_phyinit_io_write16((tAC | c_addr | csr_DfiHandshakeDelays_ADDR), ((PhyUpdAckDelay << csr_PhyUpdAckDelay_LSB) & csr_PhyUpdAckDelay_MASK) | ((CtrlUpdReqDelay << csr_CtrlUpdReqDelay_LSB) & csr_CtrlUpdReqDelay_MASK));
    }

    dwc_ddrphy_phyinit_cmnt ("%s Pstate=%d, Memclk=%dMHz, Programming DfiHandshakeDelays ", printf_header, pstate, freq);
    //dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DfiHandshakeDelays_ADDR), 0x2003);
   // dwc_ddrphy_phyinit_io_write16((p_addr | tMASTER | csr_DfiHandshakeDelays_ADDR), ((PhyUpdAckDelay << csr_PhyUpdAckDelay_LSB) & csr_PhyUpdAckDelay_MASK) | ((CtrlUpdReqDelay << csr_CtrlUpdReqDelay_LSB) & csr_CtrlUpdReqDelay_MASK));



    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_C_initPhyConfigPsLoop()\n", printf_header);

} // End of dwc_ddrphy_phyinit_C_initPhyConfigPsLoop()
/** @} */
