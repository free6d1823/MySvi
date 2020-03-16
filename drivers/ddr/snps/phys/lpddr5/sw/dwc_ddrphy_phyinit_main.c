#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "dwc_ddrphy_phyinit.h"

extern FILE *outFilePtr; // defined in the dwc_ddrphy_phyinit_globals.c
extern char *CmntStr; // defined in the dwc_ddrphy_phyinit_globals.c
extern char *ApbStr; // defined in the dwc_ddrphy_phyinit_globals.c

/** \file
 *  \brief main function for phyinit executable
 *  \addtogroup SrcFunc
 *  @{
 */

/** \brief main function of PhyInit standalone executable.
 *
 * Only used for the purpose of generating output.txt file. Parses input
 * arguments and makes a call to dwc_ddrphy_phyinit_sequence(for single PHY instance)
 *
 *  ### Required Arguments
 *
 *  - train2d <0|1>
 *    - if set to 0 only 1D training is executed in the sequence.
 *    - if set to 1 both 1D and 2D training is executed
 *    - ignored if skip_train !=0
 *
 *  - output filename
 *    - filename of the output txt file.
 *
 *  - skip_train <0|1|2>
 *    - if set to 0 firmware training is executed.
 *    - if set to 1 training is skipped and registers are programmed to work with
 *      zero board delay.
 *    - if set to 2 training is used to skip training but execute the firmware to
 *      initialize the DRAM state while registers are programmed to work with zero
 *      board delay.
 *
 *  #### Optional Arguments
 *
 *  - debug \<level\>
 *    - useful for generating additional print statements for debug purpose.
 *      Currently only level must be 0. default=0.
 *
 *  - comment_string
 *    - a custom comment string to place on non-system verilog compatible lines in
 *      the output txt files. default is an empty string.
 *
 *  - apb_string
 *    - a custom comment string to place on register write commands in
 *      the output txt files. default is an empty string.
 *
 *  - retention_exit
 *    - if set to 1 creates additional output_retention_exit.txt file with sequence for IO retention exit.
 *
 * Example: generating output txt file for 1D/2D training.
 * \code{.sh}
 * phyinit -train2d 1 -skip_train 0
 * \endcode
 *
 * @param argc number of input arguments.
 * @param argv char array of input arguments.
 */
int main2 (int argc, char *argv[]) {

    // Allocate configuration structure
    static phyinit_config_t phyConfig;

    char *printf_header;
    printf_header = " [dwc_ddrphy_phyinit_main]";

    int skip_train = -1;
    int train2d = -1;
    int debug = 0;
    int retExit = 0;
    int i;
    char *outFileName=NULL;

    char *Usage = "\
\n \
    phyinit executable \n \
\n \
    This executable will generate a txt file output with register write instructions\n \
    to initialize the Synopsys DWC_DDRPHY phy. \n \
    phyinit <required arguments> [options] \n \
\n \
    <required arguments> \n \
    -train2d <0|1> \n \
        if set to 0 only 1D training is executed in the sequence. \n \
        if set to 1 both 1D and 2D training is executed \n \
        ignored if skip_train !=0 \n \
\n \
    -output filename \n \
        filename of the output txt file.\n \
\n \
    -skip_train <0|1|2> \n \
        if set to 0 firmware training is executed.\n \
        if set to 1 training is skipped and registers are programmed to work with\n \
        zero board delay. \n \
        if set to 2 training is used to skip training but execute the firmware to\n \
        initialize the DRAM state while registers are programmed to work with zero\n \
        board delay. \n \
\n \
    [optional arguments] \n \
    -debug <level> \n \
        useful for generating additional print statements for debug purpose.\n \
        Currently only level must be 0.\n \
\n \
    -comment_string \n \
        a custom comment string to place on non-system verilog compatible lines in\n \
        the output txt files. default is an empty string.\n \
\n \
    -apb_string \n \
        a custom comment string to place on register write commands in\n \
        the output txt files. default is an empty string.\n \
\n \
    - retention_exit <0|1> \n \
        if set to 1 creates additional output_retention_exit.txt file with sequence for IO retention exit.  \n \
\n \
   Example:\n \
   phyinit -train2d 1 -skip_train 0 -debug 1\n \
";

    for (i = 1; i < argc; i=i+2) {
        if (strcmp("-skip_train", argv[i]) == 0) {
            skip_train = atoi(argv[i+1]);
        } else if (strcmp("-train2d", argv[i]) == 0) {
            train2d = atoi(argv[i+1]);
        } else if (strcmp("-debug", argv[i]) == 0) {
            debug = atoi(argv[i+1]);
        } else if (strcmp("-comment_string", argv[i]) == 0) {
            CmntStr = argv[i+1];
        } else if (strcmp("-apb_string", argv[i]) == 0) {
            ApbStr = argv[i+1];
        } else if (strcmp("-retention_exit", argv[i]) == 0) {
            retExit = atoi(argv[i+1]);
        } else if (strcmp("-output", argv[i]) == 0) {
            outFileName = argv[i+1];
        } else {
            dwc_ddrphy_phyinit_assert(0,"%s Unsupported argument %s is supplied.\n", printf_header, argv[i]);
        }
    }

    if (train2d != 0 && train2d != 1) {
        dwc_ddrphy_phyinit_assert (0,"%s train2d(%d) no set or invalid input. See usage.\n%s\n", printf_header, train2d, Usage);
    }
    if (skip_train != 0 && skip_train != 1 && skip_train != 2) {
        dwc_ddrphy_phyinit_assert (0,"%s skip_train(%d) no set or invalid input. See usage.\n%s\n", printf_header, skip_train, Usage);
    }
    if (outFileName == NULL) {
        dwc_ddrphy_phyinit_assert (0,"%s output file not specified. See usage.\n%s\n", printf_header, Usage);
    }

    if (CmntStr == NULL) {
        dwc_ddrphy_phyinit_assert (0,"%s Comments String is NULL. See usage.\n%s\n", printf_header, Usage);
    }

    if (ApbStr == NULL) {
        dwc_ddrphy_phyinit_assert (0,"%s abp_strings is NULL. See usage.\n%s\n", printf_header, Usage);
    }

    printf("%s Running with values of skip_train = %0d, train2d = %0d, debug = %0d output=%s\n", printf_header, skip_train, train2d, debug, outFileName);

    // registering function inputs
    phyConfig.runtimeConfig.skip_train = skip_train;
    phyConfig.runtimeConfig.Train2D    = train2d;
    phyConfig.runtimeConfig.debug      = debug;
    phyConfig.runtimeConfig.RetEn      = retExit;

    switch (phyConfig.runtimeConfig.skip_train)
      {
        case 0: phyConfig.runtimeConfig.initCtrl = 0x00; break;
        case 1: phyConfig.runtimeConfig.initCtrl = 0x0f; break;
        case 2: phyConfig.runtimeConfig.initCtrl = 0x21; break; // devinit+skiptrain
        case 3: phyConfig.runtimeConfig.initCtrl = 0x1f; break;
        default: phyConfig.runtimeConfig.initCtrl = 0;
      }
    /*
     * function calls to generate output files when only one PHY instance is present.
     */
    if (DWC_DDRPHY_NUM_PHY == 1)
      {
        // Open Txt output Stream
        if (debug==2)
          {
             printf("%s writing output to stdout \n\n", printf_header );
             outFilePtr = stdout;
          }
        else if ( (outFilePtr=fopen(outFileName, "w")) ==NULL )
          {
            dwc_ddrphy_phyinit_assert(0, "%s Error:  Can't open file for writing %s/\n\n", printf_header, outFileName);
          }
        else
          {
            printf("%s writing output file: %s\n\n", printf_header, outFileName);
          }

        dwc_ddrphy_phyinit_cmnt("%s Start of dwc_ddrphy_phyinit_main()\n",printf_header);

   	    // Execute phyinit sequence
        dwc_ddrphy_phyinit_sequence(&phyConfig);
        dwc_ddrphy_phyinit_cmnt("%s End of dwc_ddrphy_phyinit_main()\n",printf_header);

        fclose(outFilePtr);

        if  (retExit)
          {
            dwc_ddrphy_phyinit_cmnt("%s printing retention exit sequence txt files\n",printf_header);
            strcat(outFileName, "_retention_exit");
            // Open Txt output Stream
            if ( (outFilePtr=fopen(outFileName, "w")) ==NULL )
              {
                dwc_ddrphy_phyinit_assert(0, "%s Error:  Can't open file for writing %s/\n\n", printf_header, outFileName);
              }
            else
              {
                printf("%s writing output file: %s\n\n", printf_header, outFileName);
              }

            dwc_ddrphy_phyinit_cmnt("%s Start of dwc_ddrphy_phyinit_retention_sequence()\n",printf_header);

   	        // Execute PhyInit retention exit sequence
            dwc_ddrphy_phyinit_restore_sequence(&phyConfig);
            dwc_ddrphy_phyinit_cmnt("%s End of dwc_ddrphy_phyinit_retention_sequence()\n",printf_header);

            fclose(outFilePtr);
          }
      }
    else if (DWC_DDRPHY_NUM_PHY  < 5 && DWC_DDRPHY_NUM_PHY > 1)
      {
        printf("%s Start of multi sequence()\n",printf_header);
        // Multiple PHY instances.
        
        dwc_ddrphy_phyinit_assert(0, "%s This release of PhyInit does not support multiple PHY instances. Please contact Synopsys Support.\n");
        printf("%s End of dwc_ddrphy_phyinit_multi_sequence()\n",printf_header);
      }
    else
      {
        dwc_ddrphy_phyinit_assert(0,"%s invalid value for DWC_DDRPHY_NUM_PHY= %s\n",printf_header,DWC_DDRPHY_NUM_PHY);
        return EXIT_FAILURE;
      }

    fflush(stdout);
    return EXIT_SUCCESS;
}
/** @} */

