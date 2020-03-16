/** 
 * \file 
 * \brief loads the save/restore firmware.
 *
 *  \addtogroup SrcFunc
 *  @{
 */
#include <stdio.h>
#include "dwc_ddrphy_phyinit.h"

/** \brief Loads Save/Restore firmware IMEM and DMEM image
 *
 * This function is used when the Micro-Controller is used to Save/Restore PHY registers.
 * \return void
 */
void dwc_ddrphy_phyinit_load_SR_FW (void) {

  char *printf_header;
  printf_header = " [phyinit_SR_loading_FW_image]";

  dwc_ddrphy_phyinit_cmnt ("\n");
  dwc_ddrphy_phyinit_cmnt ("\n");
  dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
  dwc_ddrphy_phyinit_cmnt ("//\n");
  dwc_ddrphy_phyinit_cmnt ("// Loading Universal Resident Retention FW image \n");
  dwc_ddrphy_phyinit_cmnt ("// \n");
  dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
  dwc_ddrphy_phyinit_cmnt ("\n");
  dwc_ddrphy_phyinit_cmnt ("\n");

  int i;
  int imem[SR_IMEM_SIZE];
  int imem_offset=0;
  return_offset_lastaddr_t return_type = return_offset;

  // initialize the dmem structure
  for (i=0;i<SR_IMEM_SIZE;i++) imem[i]=0;

   dwc_ddrphy_phyinit_cmnt ("%s Start of loading Universal Resident Retention IMEM\n", printf_header );
   imem_offset = dwc_ddrphy_phyinit_storeIncvFile (SR_IMEM_INCV_FILENAME, imem, return_type);
   // Write local imem array
   dwc_ddrphy_phyinit_WriteOutMem(imem, imem_offset, SR_IMEM_SIZE); 
   //dwc_ddrphy_phyinit_print("WriteImem: COMPLETED\n");
   fflush(stdout);
   dwc_ddrphy_phyinit_cmnt ("%s End of loading Universal Resident Retention IMEM\n", printf_header); 



}  
/** @} */
