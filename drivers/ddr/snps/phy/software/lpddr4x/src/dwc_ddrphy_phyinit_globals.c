/** \file
 * \brief instantiates all the global structures.
 * \addtogroup SrcFunc
 * @{
 */

#include <stdio.h>
#include "dwc_ddrphy_phyinit.h"


/// stores input string from -comment_string
char* CmntStr       = ""; 
/// stores input string from -apb_string
char* ApbStr        = ""; 

// === Global variables  === //
/// File pointer for out txtfile
FILE *outFilePtr;

/// PHY Identifier when using multiple PHY's
int CurrentPhyInst;

#if DWC_DDRPHY_PHYINIT_GLOBAL_CTX == 1
/// PhyInit configuration context
phyinit_config_t phyConfig;
#endif


/** @} */
