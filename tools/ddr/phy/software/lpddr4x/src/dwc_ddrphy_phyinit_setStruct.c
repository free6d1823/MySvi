/** \file
 * \brief API to set internal data structures to pre-programmed user structures.
 * \addtogroup SrcFunc
 * @{
 */

#include <stdlib.h>
#include <string.h>
#include "dwc_ddrphy_phyinit.h"

/** @brief API to program user_input_basic to pre-programmed structures
 *
 * The function copies the content of the pointed data structure into the
 * global structure used by PhyInit.
 *
 * @param[in] phyctx       PhyIinit context
 *
 * @param[in] structType   integer determines the type of input structure.
 *
 *  value | PhyInit Data Structure Type
 *  ----- | ----------------------------
 *      0 | user_input_basic
 *      1 | user_input_advanced
 *      2 | user_input_sim
 *      3 | runtime_config
 *
 * @param[in] userStruct pointer to PhyInit data structure of structType.

 * @returns EXIT_SUCCESS / EXIT_FAILURE
 */
int dwc_ddrphy_phyinit_setStruct (phyinit_config_t* phyctx, const void *userStruct, int structType) {

    user_input_basic_t*    pUserInputBasic    = &phyctx->userInputBasic;
    user_input_advanced_t* pUserInputAdvanced = &phyctx->userInputAdvanced;
    user_input_sim_t*      pUserInputSim      = &phyctx->userInputSim;
    runtime_config_t*      pRuntimeConfig     = &phyctx->runtimeConfig;

    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_setStrcut]";

    if ( userStruct == NULL ) dwc_ddrphy_phyinit_assert (0, "%s userStruct is NULL.", printf_header);
    if ( structType < 0 ) dwc_ddrphy_phyinit_assert (0, "%s structType < 0 is invalid", printf_header);
    if ( structType > 3 ) dwc_ddrphy_phyinit_assert (0, "%s structType > 3 is invalid", printf_header);

    switch (structType)
      {
        case 0 :
            memcpy ( (void *) pUserInputBasic, userStruct, sizeof (user_input_basic_t));
	        return EXIT_SUCCESS ;

        case 1 :
            memcpy ( (void *) pUserInputAdvanced, userStruct, sizeof (user_input_advanced_t));
	        return EXIT_SUCCESS ;

        case 2 :
            memcpy ( (void *) pUserInputSim, userStruct, sizeof (user_input_sim_t));
	        return EXIT_SUCCESS ;

        case 3 :
            memcpy ( (void *) pRuntimeConfig, userStruct, sizeof (runtime_config_t));
	        return EXIT_SUCCESS ;

        default :
            dwc_ddrphy_phyinit_assert (0, "%s structType < 0 is invalid", printf_header);
	        return EXIT_FAILURE ;
      }

}
/** @} */

/** @brief Internal function used for testing
 *
 */
void* dwc_ddrphy_phyinit_configAlloc(int skip_train, int Train2D, int debug)
{
    static phyinit_config_t phyConfig;
    phyConfig.runtimeConfig.skip_train = skip_train;
    phyConfig.runtimeConfig.Train2D    = Train2D;
    phyConfig.runtimeConfig.debug      = debug;
    return &phyConfig;
}

/** @brief Internal function used for testing
 *
 */
void dwc_ddrphy_phyinit_configFree(void* ptr)
{
}


