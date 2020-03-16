/** \file
 *  \addtogroup SrcFunc
 *  @{
 */
#include <stdlib.h>
#include <stdio.h>
#include "dwc_ddrphy_phyinit.h"

/** \brief This function loads the training firmware IMEM image into the SRAM.
 *
 *  This function reads the incv files form the firmware package to generate a
 *  set of apb writes to load IMEM image into the SRAM. The exact steps in this
 *  function are as follows:
 *
 *  -# Ensure DRAM is in reset.
 *  -# Load the microcontroller memory with the provided training firmware
 *  -# Initialize the firmware mailbox structures to be able to communicate with
 *  the firmware (see "Mailbox facility for firmware" in the "DesignWare Cores
 *  DDR PHY Training Application Note".
 *
 *  Only loads IMEM image when currently not loaded in SRAM.
 * \return void
 */
void dwc_ddrphy_phyinit_D_loadIMEM (phyinit_config_t* phyctx) {

  //runtime_config_t* pRuntimeConfig = &phyctx->runtimeConfig;
  //int Train2D = pRuntimeConfig->Train2D;

  char *printf_header;
  printf_header = " [dwc_ddrphy_phyinit_D_loadIMEM]";

  dwc_ddrphy_phyinit_cmnt ("%s Start of dwc_ddrphy_phyinit_D_loadIMEM\n", printf_header);

  int addr, mem_offset=0;
  int mem[IMEM_SIZE];
  return_offset_lastaddr_t return_type = return_offset;

  // initialize the dmem structure
  for (addr=0;addr<IMEM_SIZE;addr++) mem[addr]=0;

  // Read the IMEM INCV file into the array
  mem_offset = dwc_ddrphy_phyinit_storeIncvFile (IMEM_INCV_FILENAME, mem, return_type);

  // Write local imem array
  dwc_ddrphy_phyinit_WriteOutMem(mem, mem_offset, IMEM_SIZE);

  //dwc_ddrphy_phyinit_cmnt("%s WriteImem: COMPLETED\n", printf_header);
  fflush(stdout);

  // Set variable to know what IMEM is loaded.
  //pRuntimeConfig->curIMEM=Train2D;

  dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_D_loadIMEM()\n", printf_header);

}
/** @} */
