/** \file
 *  \brief function to implement step G of PUB databook initialization step.
 *  \addtogroup CustFunc
 **  @{
 */
#include "dwc_ddrphy_phyinit.h"

/** \brief Implements the mechanism to wait for completion of training firmware
 * execution.
 *
 * The purpose of user this function is to wait for firmware to finish training.
 * The user can either implement a counter to wait or implement the polling
 * mechanism described in the Training Firmware App Note section "Running the
 * Firmware".  The wait time is highly dependent on the training features
 * enabled via SequenceCtrl input to the message block.  See Training Firmware
 * App note for details. 
 *
 * The default behavior of this function is to print comments relating to this
 * process.  A function call of the same name will be printed in the output text
 * file.
 *
 * The user can choose to leave this function as is, or implement mechanism to
 * trigger mailbox poling event in simulation.

 * \return void
 */
extern void waitFwDone_sv();
void dwc_ddrphy_phyinit_userCustom_G_waitFwDone () {
 waitFwDone_sv();


    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_userCustom_G_waitFwDone]";

    dwc_ddrphy_phyinit_cmnt ("%s Wait for the training firmware to complete.  Implement timeout fucntion or follow the procedure in \"3.4 Running the firmware\" of the Training Firmware Application Note to poll the Mailbox message.\n", printf_header);

    dwc_ddrphy_phyinit_print ("dwc_ddrphy_phyinit_userCustom_G_waitFwDone ();\n\n");
    dwc_ddrphy_phyinit_cmnt ("%s End of dwc_ddrphy_phyinit_userCustom_G_waitFwDone()\n", printf_header);

}
/** @} */

