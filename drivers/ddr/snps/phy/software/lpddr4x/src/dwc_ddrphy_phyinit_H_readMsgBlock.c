/** \file
 *  \addtogroup SrcFunc
 *  @{
 */
#include "dwc_ddrphy_phyinit.h"

/** \brief Read the Training Firmware Message Block results
 *
 * The procedure is as follows:
 *
 * -# Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
 * -# Read the Firmware Message Block to obtain the results from the training.
 * The user customizable function dwc_ddrphy_phyinit_userCustom_H_readMsgBlock()
 * is called for the user to read any specific results from training.
 * -# Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1.
 * -# If training is required at another frequency, repeat the operations starting at step (E)
 *
 * \return void
 */
void dwc_ddrphy_phyinit_H_readMsgBlock (int Train2D) {
    
    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_H_readMsgBlock]";

    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("//\n");
    dwc_ddrphy_phyinit_cmnt ("// (H) Read the Message Block results\n");
    dwc_ddrphy_phyinit_cmnt ("// \n");
    dwc_ddrphy_phyinit_cmnt ("// The procedure is as follows:\n");
    dwc_ddrphy_phyinit_cmnt ("// \n");
    dwc_ddrphy_phyinit_cmnt ("//##############################################################\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt (" 1. Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.\n");
    dwc_ddrphy_phyinit_userCustom_io_write16((tAPBONLY | csr_MicroContMuxSel_ADDR), 0x0);

    dwc_ddrphy_phyinit_cmnt ("\n");
    dwc_ddrphy_phyinit_cmnt (" 2. Read the Firmware Message Block to obtain the results from the training \n");

    dwc_ddrphy_phyinit_userCustom_H_readMsgBlock(Train2D);

    dwc_ddrphy_phyinit_cmnt (" 3. If training is required at another frequency, repeat the operations starting at step (E). \n");
    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_H_readMsgBlock()\n", printf_header);
}
/** @} */
