/** \file
 *  \addtogroup SrcFunc
 *  @{
 */
#include "dwc_ddrphy_phyinit.h"

/** \brief Execute the Training Firmware 
 *
 * The training firmware is executed with the following procedure:
 *
 * -# Reset the firmware microcontroller by writing the MicroReset register to
 * set the StallToMicro and ResetToMicro fields to 1 (all other fields should be
 * zero). Then rewrite the registers so that only the StallToMicro remains set
 * (all other fields should be zero).
 * -# Begin execution of the training firmware by setting the MicroReset
 * register to 4'b0000.
 * -# Wait for the training firmware to complete by following the procedure in
 * "uCtrl Initialization and Mailbox Messaging" implemented in
 * dwc_ddrphy_phyinit_userCustom_G_waitFwDone() function.
 * -# Halt the microcontroller.
 * 
 * \return void
 */
void dwc_ddrphy_phyinit_G_execFW () {
    
    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_G_execFW]";

    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("// (G) Execute the Training Firmware \n");
    dwc_ddrphy_phyinit_cmnt ("// \n");
    dwc_ddrphy_phyinit_cmnt ("// See PhyInit App Note for detailed description and function usage\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("// 1.  Reset the firmware microcontroller by writing the MicroReset CSR to set the StallToMicro and \n");
    dwc_ddrphy_phyinit_cmnt ("//     ResetToMicro fields to 1 (all other fields should be zero). \n");
    dwc_ddrphy_phyinit_cmnt ("//     Then rewrite the CSR so that only the StallToMicro remains set (all other fields should be zero). \n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x1);
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroReset_ADDR), csr_ResetToMicro_MASK|csr_StallToMicro_MASK);
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroReset_ADDR), csr_StallToMicro_MASK);

    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("// 2. Begin execution of the training firmware by setting the MicroReset CSR to 4\'b0000. \n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroReset_ADDR), 0x0);

    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("// 3.   Wait for the training firmware to complete by following the procedure in \"uCtrl Initialization and Mailbox Messaging\" \n");
    dwc_ddrphy_phyinit_userCustom_G_waitFwDone();

    dwc_ddrphy_phyinit_cmnt ("// 4.   Halt the microcontroller.\" \n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroReset_ADDR), csr_StallToMicro_MASK);

    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_G_execFW ()\n", printf_header);

}
/** @} */
