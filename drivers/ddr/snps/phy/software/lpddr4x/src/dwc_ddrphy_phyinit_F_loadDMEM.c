/** \file
 *  \addtogroup SrcFunc
 *  @{
 */
#include <stdlib.h>
#include <stdio.h>
#include "dwc_ddrphy_phyinit.h"

/** \brief This function loads the training firmware DMEM image and write the
 *  Message Block parameters for the training firmware into the SRAM.
 *
 *  This function performs the following tasks:
 *
 *  -# Load the firmware DMEM segment to initialize the data structures from the
 *  DMEM incv file provided in the training firmware package.
 *  -# Write the Firmware Message Block with the required contents detailing the training parameters.
 *
 * \return void
 */
void dwc_ddrphy_phyinit_F_loadDMEM (phyinit_config_t* phyctx) {

    runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
    uint8_t pstate = pRuntimeConfig->curPState;
    uint8_t Train2D = pRuntimeConfig->curD;

    user_input_basic_t* pUserInputBasic = &phyctx->userInputBasic;

    char *printf_header;
    if (Train2D)
        printf_header = " [phyinit_F_loadDMEM, 2D]";
    else
        printf_header = " [phyinit_F_loadDMEM, 1D]";

    dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_F_loadDMEM (pstate=%d, Train2D=%d)\n", printf_header, pstate, Train2D);

    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("// (F) Load the %dD DMEM image and write the %dD Message Block parameters for the training firmware \n", Train2D+1, Train2D+1);
    dwc_ddrphy_phyinit_cmnt ("// \n");
    dwc_ddrphy_phyinit_cmnt ("// See PhyInit App Note for detailed description and function usage\n");
    dwc_ddrphy_phyinit_cmnt ("// \n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n");

    // set a pointer to the message block.
    PMU_SMB_LPDDR4X_1D_t *msgBlkPtr;

    if (Train2D == 1) {
      msgBlkPtr = (PMU_SMB_LPDDR4X_1D_t *)& phyctx->mb_LPDDR4X_2D[pstate];
    } else {
      msgBlkPtr = &phyctx->mb_LPDDR4X_1D[pstate];
    }
    // Some basic checks on MessgeBlock
    if ( msgBlkPtr->EnabledDQsChA %8 != 0 || msgBlkPtr->EnabledDQsChB %8 != 0 )
      {
      dwc_ddrphy_phyinit_assert(0,"%s Lp3/Lp4 - Number of Dq's Enabled per Channel much be multipe of 8\n",printf_header);
      }
    if (( msgBlkPtr->EnabledDQsChA > 8*(pUserInputBasic->NumActiveDbyteDfi0)) ||
        ( msgBlkPtr->EnabledDQsChB > 8*(pUserInputBasic->NumActiveDbyteDfi1)) ||
        ( msgBlkPtr->EnabledDQsChA == 0 && msgBlkPtr->EnabledDQsChB == 0)
       )
      {
      dwc_ddrphy_phyinit_assert(0,"%s EnabledDqsChA/B are not set correctly./1\n",printf_header);
      }

  int addr, mem_offset=0, sizeOfMsgBlk;
  int mem[DMEM_SIZE];
  return_offset_lastaddr_t return_type = return_lastaddr;

  // initialize the dmem structure
  for (addr=0;addr<DMEM_SIZE;addr++) mem[addr]=0;

  if (Train2D == 1) { 	// 2-D
      mem_offset = dwc_ddrphy_phyinit_storeIncvFile (DMEM_INCV_FILENAME_2D, mem, return_type);
      sizeOfMsgBlk = sizeof(PMU_SMB_LPDDR4X_2D_t);
    }
  else
    { 				   // 1-D
      mem_offset = dwc_ddrphy_phyinit_storeIncvFile (DMEM_INCV_FILENAME, mem, return_type);
      sizeOfMsgBlk = sizeof(PMU_SMB_LPDDR4X_1D_t);
    }
  dwc_ddrphy_phyinit_storeMsgBlk(msgBlkPtr, sizeOfMsgBlk, mem);

  // Write local dmem array
  if(0==(mem_offset%1)){//Always write an even number of words so no 32bit quantity is uninitialized
    mem_offset++;
  }
  dwc_ddrphy_phyinit_cmnt (" 1.	Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.\n");
  dwc_ddrphy_phyinit_cmnt ("       This allows the memory controller unrestricted access to the configuration CSRs. \n");
  dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x0);

  dwc_ddrphy_phyinit_cmnt (" 2.	write out DMEM.\n");
  dwc_ddrphy_phyinit_WriteOutMem(mem, DMEM_ST_ADDR, (mem_offset-DMEM_ST_ADDR));

  dwc_ddrphy_phyinit_cmnt (" 3.	Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. \n");
  dwc_ddrphy_phyinit_cmnt ("      This allows the firmware unrestricted access to the configuration CSRs. \n");
  dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x1);

  dwc_ddrphy_phyinit_cmnt("%s End of dwc_ddrphy_phyinit_F_loadDMEM()\n", printf_header);

}
/** @} */
