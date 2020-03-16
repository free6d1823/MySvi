
/** \file dwc_ddrphy_phyinit_struct.h 
 *  \brief This file defines the internal data structures used in PhyInit to store user configuration.
 *
 *  Please see \ref docref to obtain necessary information for program variables
 *  correctly for your PHY variant and process technology.
 */

/**  \addtogroup structDef
 *  @{
 */

/** Enumerator for DRAM Type */
typedef enum DramTypes { 
    DDR4,    /*!< DDR4 */
    DDR3,    /*!< DDR3 */
    LPDDR4,  /*!< LPDDR4 */
    LPDDR3,  /*!< LPDDR3 */
    LPDDR5   /*!< LPDDR5 */
} DramType_t;

/** Enumerator for DIMM Type */
typedef enum DimmTypes { 
    UDIMM,   /*!< UDIMM */
    SODIMM,  /*!< SODIMM */
    RDIMM,   /*!< RDIMM (DDR3/DDR4 only) */
    LRDIMM,  /*!< LRDIMM (DDR4 only) */
    NODIMM   /*!< No DIMM (Soldered-on) */
} DimmType_t;


/** \brief Structure for basic (mandatory) user inputs
 *  
 * The following basic data structure must be set and completed correctly so
 * that the PhyInit software package can accurately program PHY registers.
 */
typedef struct user_input_basic {

    DramType_t DramType;    ///< DRAM Module Type: 

                            ///< - must be set as hex
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | DDR4
                            ///<   0x1 | DDR3
                            ///<   0x2 | LPDDR4
                            ///<   0x3 | LPDDR3 
                            ///<   0x4 | LPDDR5 
                            
    DimmType_t DimmType;    ///< Choose the Dimm type from one of below: 

                            ///< - must be set as hex
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | UDIMM 
                            ///<   0x1 | SODIMM 
                            ///<   0x2 | RDIMM (DDR3/DDR4 only)
                            ///<   0x3 | LRDIMM (DDR4 only)
                            ///<   0x4 | No DIMM (Soldered-on)
                            
    int NumCh;              ///< Enter number of channels supported by PHY 
                        
                            ///< - Must be decimal integer. 
                            ///< - Must match RTL define DWC_DDRPHY_NUM_CHANNELS_1/DWC_DDRPHY_NUM_CHANNELS_2
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<     1 | DWC_DDRPHY_NUM_CHANNELS_1 defined in RTL
                            ///<     2 | DWC_DDRPHY_NUM_CHANNELS_2 defined in RTL

    int NumRank;            ///< Enter number of ranks supported by PHY RTL
                        
                            ///< - Must be decimal integer. 
                            ///< - Must match RTL define DWC_DDRPHY_NUM_RANKS_1/DWC_DDRPHY_NUM_RANKS_2
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<     1 | DWC_DDRPHY_NUM_RANKS_1 defined in RTL
                            ///<     2 | DWC_DDRPHY_NUM_RANKS_2 defined in RTL

    int NumDbytesPerCh;     ///< Enter number of Dbytes Per channel supported by PHY 
                        
                            ///< - Must be decimal integer. 
                            ///< - Must match RTL define DWC_DDRPHY_NUM_DBYTES_PER_CHANNEL_2/DWC_DDRPHY_NUM_DBYTES_PER_CHANNEL_4
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<     2 | DWC_DDRPHY_NUM_DBYTES_PER_CHANNEL_2 defined in RTL
                            ///<     4 | DWC_DDRPHY_NUM_DBYTES_PER_CHANNEL_4 defined in RTL

    int NumActiveDbyteDfi0; ///< Enter number of active dbytes to be controlled by dfi0

                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Must be decimal integer.
                            ///< - valid values must be from table below in accordance with other variables.
                            ///<
                            ///< Value | NumCh | NumDbytesPerCh | Description
                            ///< ----- | --- | --- | ---
                            ///<     2 |  1  |  2  | Single channel system, Dfi0 control Ch0
                            ///<     4 |  1  |  4  | Single channel system, Dfi0 control Ch0
                            ///<     2 |  2  |  2  | Dual Channel System Dfi0 controls Ch0, Dfi1 controls Ch1.
                            ///<     4 |  2  |  4  | Dual Channel System Dfi0 controls Ch0, Dfi1 controls Ch1.
                            ///<     4 |  2  |  2  | Dual Channel system, Dfi0 used to both Ch0,Ch1
                            ///<     8 |  2  |  4  | Dual Channel system, Dfi0 used to both Ch0,Ch1
                            

    int NumActiveDbyteDfi1; ///< Enter number of active dbytes to be controlled by dfi1

                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Must be decimal integer.
                            ///< - valid values must be from table below in accordance with other variables.

                            ///< Value | NumCh | NumDbytesPerCh | Description
                            ///< ----- | --- | --- | ---
                            ///<     0 |  *  |  *  | Dfi1 does not control any Channel 
                            ///<     2 |  2  |  2  | Dfi1 controls Ch1. 
                            ///<     4 |  2  |  4  | Dfi1 controls Ch1.
                            
    // suggest to change : NumActiveRrankDfi0 
    int NumRank_dfi0;       ///< Number of ranks in DFI0 channel
    
                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Must be decimal integer either 1 or 2.

    // suggest to change : NumActiveRrankDfi1 
    int NumRank_dfi1;       ///< Number of ranks in DFI1 channel 

                            ///< - See PUB databook section on supported PHY configurations for valid settings.
                            ///< - Must be decimal integer.
                            ///< - valid values must be from table below in accordance with other variables.
                            ///<        Value | NumCh | Description
                            ///<        ----- | ----- | ---
                            ///<            0 |  1    | Dfi1 does not control any Channel.
                            ///<            0 |  2    | Dfi1 does not control any Channel.
                            ///< NumRank_dfi0 |  2    | Number of active DQ bits (channels) across ranks must match. 

    int DramDataWidth;      ///< Width of the DRAM device.

                            ///< - Enter 8 or 16 depending on DRAM type according below table.
                            ///< - Must be decimal integer.
                            ///< - See PUB databook section "Supported System Configurations" for DRAM width options 
                            ///<   supported by your PHY product.
                            ///<
                            ///< Protocol | Valid Options | Default
                            ///< -------- | ------------- | ---
                            ///< LPDDR4   | 8,16          | 16
                            ///< LPDDR5   | 8,16          | 16
                            ///<
                            ///< \note For mixed x8 and x16 width devices, set variable to x8.
                            ///<

    int MaxNumZQ;           ///< Number of DRAM devices (die) sharing a ZQ resistor.

                            ///< - Must be decimal integer.
                            ///< - Specifies the maximum number of DRAM die within a package that can share a common 
                            ///<   external ZQ resistor. This value is used to derive the ZQ calibration time (tZQCAL).

    int NumPStates;         ///< Number of p-states used

                            ///< - Must be decimal integer.

    int CfgPStates;         ///< Defines Which Pstates are Valid

                            ///< - Each bit position defines if the corresponding PState slot is valid. 
                            ///< - used only when > 2Pstates are used.
                            ///< - Number of 1's must match NumPState entry.
                            ///< - Example: For 3 PStates used and mapped to Pstate 0,1 and 7,
                            ///<   CfgPStates = 0x83, 
                            ///<   NumPStates=3.

    /**
     * @brief This is the first PState on Cold Boot and Retention Exit.
     *
     * - In order to ensure correct state of DRAM, the initialization sequence needs to match the last 
     *   trained PState with the first PState entered in Step J, i.e. the first set of 
     *   dfi_frequency, dfi_freq_ratio and dfi_freq_fsp on cold boot must select this PState.
     * - Any valid PState can be specified.
     *
     *     Value | Description
     *     ----- | ------
     *       0x0 | PState 0 (defualt) 
     *   0x-0x14 | Corresponding PState. 
     */
    int FirstPState;

    int Frequency[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];      ///< the DRAM CK Frequency for each PState.

                            ///< - Must be decimal integer.
                            ///< - Frequency of CK_t in MHz round up to next highest integer.  Enter 334 for 333.333, etc.
                            ///< - Each array entry must represent the value for the index Pstate.
    
    int PllBypass[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];      ///< indicates if PLL should be in Bypass mode.

                            ///< - See PUB Databook section "PLL Bypass Mode" under "Clocking and Timing" for requirements.
                            ///< - At data rates below DDR333 rate PLL must be in Bypass Mode.
                            ///< - Must be set as hex.
                            ///< - Each array entry must represent the value for the indexed Pstate.
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x1 | Enabled
                            ///<   0x0 | Disabled
    
    int DfiFreqRatio[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];   ///< Selected Dfi Frequency ratio

                            ///< - Used to program the DfiFreqRatio register. This register controls how dfi_freq_ratio 
                            ///<   input pin should be driven inaccordance with DFI Spec.
                            ///< - For LPDDR4: this is the ratio between the DFI clock and the memory clock CK.
                            ///< - For LPDDR5: this is the ratio between the DFI Clock and WCK.
                            ///<   (The DFI Clock to CK clock is always a 1:1 ratio for LPDDR5.)
                            ///< - See PUB databook section "DfiClk" on details on how to set the value.
                            ///< - must be set as hex
                            ///< - Each array entry must represent the value for the index Pstate.
                            ///<
                            ///< Binary Value | Description
                            ///<        ----- | ------
                            ///<        2'b00 | 1:1 DFI Frequency Ratio (Not supported)
                            ///<        2'b01 | 1:2 DFI Frequency Ratio (default)
                            ///<        2'b10 | 1:4 DFI Frequency Ratio
    
    int HardMacroVer;       ///< Hard Macro Family version in use.

                            ///< - Please see technology specific PHY 
                            ///<   Databook for "Hard Macro Family" version.  The variable is
                            ///<   used to fine tune analog register value settings.
                            ///< - Must be decimal integer.
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0   | hardmacro family A
                            ///<   1   | hardmacro family B
                            ///<   2   | hardmacro family C
                            ///<   3   | hardmacro family D
                            ///<   4   | hardmacro family E


} user_input_basic_t;



/** \brief Structure for advanced (optional) user inputs
 *
 *  if user does not enter a value for these parameters, a default recommended or
 *  default value will be used
 */
typedef struct user_input_advanced {
    
    int ExtCalResVal;            ///< External Impedance calibration pull-down resistor value select.

                                 ///< - Indicates value of impedance calibration pull-down resistor connected to BP_ZN pin of the PHY.
                                 ///<   See Section "Impedance Calibrator" section in the PUB Databook for details
                                 ///<   on PHY impedance engine and the ZN requirements for the reference external
                                 ///<   resistor.
                                 ///< - must be integer in Ohms.
                                 ///< - Note setting a value of 0 tri-states the replica driver.
                                 ///< - Drop-down menu:
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<  120  | 120 ohm (default)
                                 ///<   60  |  60 ohm
                                 ///<   40  |  40 ohm
                                 ///<   30  |  30 ohm
                                 ///<   0   |  Tristate replica driver.

    int RxModeBoostVDD[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Controls the current for Rx differential I/Os according to boost/non-boost VDD.

                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | Default mode
                                 ///<   0x1 | Boost VDD mode

    int RxVrefKickbackNoiseCancellation[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Controls Vref Kickback noise cancellation for Rx single-ended I/Os

                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | Disable Vref kickback noise cancellation
                                 ///<   0x1 | Enable Vref kickback noise cancellation (default)

    int RxVrefDACEnable[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Controls Vref DAC for AC single-ended I/Os

                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | Disable Vref DAC
                                 ///<   0x1 | Enable Vref DAC (default)

    int RxBiasCurrentControlCk[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Controls the Receiver bias current control for CK lanes
                                
                                 ///< - Used for programming RxGainCurrAdjDIFF0 registers.
                                 ///< - Please Refer to Technology specific PHY DATABOOK for supported values.

    int RxBiasCurrentControlDqs[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Controls the Receiver bias current control for DQS lanes
                                
                                 ///< - Used for programming RxGainCurrAdjDIFF0 registers.
                                 ///< - Please Refer to Technology specific PHY DATABOOK for supported values.

    int RxBiasCurrentControlRxReplica[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Controls the Receiver bias current control for the DQS RxReplica circuits

                                 ///< - Used for programming RxGainCurrAdjDIFF1 registers.
                                 ///< - Please Refer to Technology specific PHY DATABOOK for supported values.

    int RxBiasCurrentControlWck[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Controls the Receiver bias current control for WCK

                                 ///< - Used for programming RxGainCurrAdjRxReplica registers.
                                 ///< - Please Refer to Technology specific PHY DATABOOK for supported values.

    int TxImpedanceDq[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Tx Drive Impedance for DQ bit slices in ohm 

                                 ///< - Does not apply to WCK_t/c, DQS_t/c
                                 ///< - Used for programming TxImpedanceSE0 and TxImpedanceSE1 registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: DQ, DQS outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer. 
                                 ///<
                                 ///< - Valid values are:
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<

    int TxImpedanceAc[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Tx Drive Impedance for AC bit slices in ohm 

                                 ///< - Does not apply to CKE(LP4), CS(LP5), CK_t/c
                                 ///< - Used for programming TxImpedanceSE0 and TxImpedanceSE1 registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: DQ, DQS outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer. 
                                 ///<
                                 ///< - Valid values are:
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<

    int TxImpedanceDqs[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Tx Drive Impedance for DQS_t/c in ohm 

                                 ///< - Used for programming TxImpedanceDIFF0T, TxImpedanceDIFF0Cregisters.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: address, command, CLK outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< - Valid values are:
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<

    int TxImpedanceCk[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Tx Drive Impedance for CK_t/c in ohm 

                                 ///< - Used for programming TxImpedanceDIFF0T, TxImpedanceDIFF0Cregisters.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: address, command, CLK outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< - Valid values are:
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<

    int TxImpedanceWCK[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Tx Drive Impedance for WCK_t/c  in ohm 

                                 ///< - Used for programming TxImpedanceDIFF1T, TxImpedanceDIFF1C.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: address, command, CLK outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< - Valid values are:
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<


    int TxImpedanceCKE[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Tx Drive Impedance for AC in ohm 

                                 ///< - Used for programming TxImpedanceCMOS0.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "Outpu drive pull-up/down Impedance: address, command, CLK outputs" in "Common DC Output Paremeters" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< - Valid values are:
                                 ///<   400 Ohms
                                 ///<   100  Ohms
                                 ///<   67  Ohms
                                 ///<   50  Ohms (Default)
                                 ///<

    int TxImpedanceDTO[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Tx Drive Impedance for DTO (Digital Test Output) in ohm 

                                 ///< - Used for programming TxImpedanceCMOS1.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< - Valid values are:
                                 ///<   400 Ohms
                                 ///<   100  Ohms
                                 ///<   67  Ohms
                                 ///<   50  Ohms (Default)
                                 ///<

    int OdtImpedanceDq[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< ODT Impedance for DQ bit slices in ohm 

                                 ///< - Does not apply to DQS_t/c
                                 ///< - Used for programming OdtImpedanceSE0 and OdtImpedanceSE1 registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "On-die termination (ODT) programmable resistances (Rtt)" in "DC Input Conditions" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer. 
                                 ///<
                                 ///< - Valid values are:
                                 ///<   0 (Hi-Z)
                                 ///<   120 Ohms
                                 ///<   60  Ohms (Default)
                                 ///<   40  Ohms
                                 ///<   30  Ohms
                                 ///<

    int OdtImpedanceDqs[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< ODT Impedance for DQS_t/c in ohm 

                                 ///< - Used for programming OdtImpedanceDIFF0T, OdtImpedanceDIFF0C registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "On-die termination (ODT) programmable resistances (Rtt)" in "DC Input Conditions" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PUB databook are supported.
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< - Valid values are:
                                 ///<   0 (Hi-Z)
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<

    int OdtImpedanceWCK[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< ODT Impedance for WCK_t/c in ohm 

                                 ///< - Used for programming OdtImpedanceDIFF1T, OdtImpedanceDIFF1C registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "On-die termination (ODT) programmable resistances (Rtt)" in "DC Input Conditions" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PUB databook are supported.
                                 ///< - Must be decimal integer.
                                 ///<
                                 ///< - Valid values are:
                                 ///<   0 (Hi-Z)
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<


    int OdtImpedanceCa[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< ODT Impedance for CA bit slices in ohm

                                 ///< - Used for programming OdtImpedanceSE0 (and OdtImpedanceSE1 for LPDDR5) registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "On-die termination (ODT) programmable resistances (Rtt)" in "DC Input Conditions" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer. 
                                 ///<
                                 ///< - Valid values are:
                                 ///<   0 (Hi-Z)
                                 ///<   120 Ohms
                                 ///<   60  Ohms (Default)
                                 ///<   40  Ohms
                                 ///<   30  Ohms
                                 ///<

    int OdtImpedanceCk[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< ODT Impedance for CK bit slices in ohm

                                 ///< - Used for programming OdtImpedanceDIFF0T, OdtImpedanceDIFF0C registers.
                                 ///< - See "Electrical Parameters" in PHY Databook for supported impedance
                                 ///<   range given your Hard Macro Family.  Set based on Typical values from
                                 ///<   "On-die termination (ODT) programmable resistances (Rtt)" in "DC Input Conditions" 
                                 ///<   table for each protocol. See table foot notes for more details.
                                 ///< - Based on SI Analysis and DRAM modules, select from supported values in the PHY Databook.
                                 ///<   Only values in the PHY databook are supported.
                                 ///< - Must be decimal integer. 
                                 ///<
                                 ///< - Valid values are:
                                 ///<   0 (Hi-Z)
                                 ///<   120 Ohms
                                 ///<   60  Ohms
                                 ///<   40  Ohms
                                 ///<   30  Ohms (Default)
                                 ///<

    int TxSlewRiseDq[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-up slew rate control for DQ and DMI
                                 
                                 ///< - Value specified here will be written to register TxSlewSE0.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.
                                   
    int TxSlewFallDq[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-down slew rate control for DQ and DMI
                                 
                                 ///< - Value specified here will be written to TxSlewSE0.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.
                                   
    int TxSlewRiseDqs[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-up slew rate control for DQS_t / DQS_c
                                 
                                 ///< - Value specified here will be written to register TxSlewDIFF0.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.
                                   
    int TxSlewFallDqs[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-down slew rate control for DQS_t / DQS_c
                                 
                                 ///< - Value specified here will be written to TxSlewDIFF0.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.

    int TxSlewRiseCA[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-up slew rate control for CA lanes
                                 
                                 ///< - Value specified here will be written to TxSlewSE0/1.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.

    int TxSlewFallCA[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-down slew rate control for CA lanes
                                 
                                 ///< - Value specified here will be written to TxSlewSE0/1.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.

    int TxSlewRiseCK[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-up slew rate control for CK
                                 
                                 ///< - Value specified here will be written to TxSlewDIFF0.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.
                                   
    int TxSlewFallCK[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-down slew rate control for CK
                                 
                                 ///< - Value specified here will be written to TxSlewDIFF0
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.

    int TxSlewRiseWCK[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Pull-up slew rate control for WCK
                                 
                                 ///< - Value specified here will be written to TxSlewDIFF1.
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.

    int TxSlewFallWCK[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];///< Pull-down slew rate control for WCK
                                 
                                 ///< - Value specified here will be written to TxSlewDIFF1
                                 ///<   See register description for more information.
                                 ///< - Only the default are currently recommended.

    int CkDisVal[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Determine behavior of CK pins when dfi_clk_disable is used.

                                 ///< - See register CkDisVal register description.
                                 ///< - must be set as hex. 
                                 ///< - value directly written to register.

    int DramByteSwap;            ///< DRAM Oscillator count source mapping.

                                 ///< - The PHY supports swapping of DRAM oscillator count values between paired DBytes for the purpose of tDQSDQ DRAM Drift Compensation(DDC).
                                 ///< - Each DByte has a register bit to control the source of the oscillator count value used to perform tDQSDQ Drift compensation.  
                                 ///<   The training firmware will not determine the DByte swap, it will rely on PptCtlStatic register to select oscillator count source.
                                 ///<   This input is used to program such CSR and is required depending on the configuration.
                                 ///< 
                                 ///< - The default hardware configuration is for odd Dbyte instance n to use oscillator count values from its paired Dbyte instance n-1.
                                 ///<   So Dbyte1 will use the oscillator count values from Dbyte0, Dbyte3 will use Dbyte2 and so on.  This is required for DRAM Data width =16.
                                 ///< - Each bit of this field corresponds to a DBYTE:
                                 ///<   - bit-0 = setting for DBYTE0
                                 ///<   - bit-1 = setting for DBYTE1
                                 ///<   - bit-2 = setting for DBYTE2
                                 ///<   - . . .
                                 ///<   - bit-n = setting for DBYTEn
                                 ///< - By setting the associated bit for each DByte to 1, PHY will use non-default source for count value.
                                 ///<   - for even Dbytes, non-default source is to use the odd pair count value.
                                 ///<   - for odd Dbytes, no-default source to use data received directly from the DRAM.
                                 ///< - Byte swapping must be the same across different ranks.
                                 ///< - must be set as hex
                                 ///< - default : 0x0
                                 ///< - if Byte mode devices are indicated via the X8Mode messageBlock parameter, this variable is ignored as PHY only supports 
                                 ///<   a limited configuration set based on Byte mode configuration..
                                 ///< 
                                 ///< Example: 
                                 ///<   DramByteSwap = 0x03 - Dbyte0: use count values from Dbyte1, Dbyte1 uses count values received directly received from DRAM.
                                 ///<   Rest of Dbytes have default source for DRAM oscilator count.
                                 ///<
 
    int PhyMstrTrainInterval[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Specifies how frequently dfi_phymstr_req is issued by PHY

                                 ///< - See PUB databook section "DFI Master Interface" and DFI 3.1 
                                 ///<   Spec + 4.0v2 Addendum for details of DFI PHY Master interface.
                                 ///< - Based on SI analysis determine how frequently DRAM drift compensation and
                                 ///<   re-training is required. 
                                 ///< - Determine if Memory controller supports DFI PHY Master Interface.
                                 ///< - Program based on desired setting for PPTTrainSetup.PhyMstrTrainInterval register.
                                 ///<   See register description in PUB Databook for translation table
                                 ///<   of values to MEMCLKs.  Example values provided in below table. 
                                 ///< - Only required in LPDDR3 and LPDDR4.
                                 ///< - default : 0xa
                                 ///< - Must be set as hex.
                                 ///< - Example :
                                 ///<
                                 ///< Example Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | to Disable PHY Master Interface 
                                 ///<   0x3 | PPT Train Interval = 2097152 MEMCLKs 
                                 ///<   0xa | PPT Train Interval = 268435456 MEMCLKs (default)

    int PhyMstrMaxReqToAck[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];  ///< Max time from dfi_phymstr_req asserted to dfi_phymstr_ack asserted

                                 ///< - Based on your Memory controller's(MC) specification determine how long the PHY
                                 ///<   should wait for the assertion of dfi_phymstr_ack once dfi_phymstr_req has 
                                 ///<   been issued by the PHY. If the MC does not ack the PHY's request, PHY may issue 
                                 ///<   dfi_error.
                                 ///< - See PUB databook section "DFI Master Interface" and DFI 3.1 
                                 ///<   Spec + 4.0v2 Addendum for details of DFI PHY Master interface.
                                 ///< - This value will be used to program PPTTrainSetup.PhyMstrMaxReqToAck register.
                                 ///<   See detailed register description in PUB Databook.
                                 ///< - default: 0x5
                                 ///< - Only required in LPDDR3 and LPDDR4.
                                 ///< - Must be set as hex.
                                 ///< - Example:
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | Disable PHY Master Interface
                                 ///<   0x3 | PPT Max. Req to Ack. = 2048 MEMCLKs
                                 ///<   0x5 | PPT Max. Req to Ack. = 8192 MEMCLKs (default)

    int PhyMstrCtrlMode[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< When this bit is set, a PHY Master transaction can be initiated only by a dfi_ctrlmsg transaction 

                                 ///< - Determine if Memory controller supports DFI PHY Master Interface.
                                 ///< - Program based on desired setting for PPTTrainSetup.PhyMstrCtrlMode register.
                                 ///< - (PPTTrainSetup[7:7])


    int WDQSExt;                 ///< Enable Write DQS Extension feature of PHY.  
    
                                 ///< - See App Note "DesignWare Cores LPDDR4 MultiPHY : WDQS Extension Application Note"
                                 ///< - Must be set as hex.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///<   0x0 | Disable Write DQS Extension feature. (default)
                                 ///<   0x1 | Enable Write DQS Extension feature.

    int CalInterval;             ///< Specifies the interval between successive calibrations, in mS.

                                 ///< - See PUB Databook section "Impedance Calibrator" to learn about PHY Impedance 
                                 ///<   calibration FSM. Based on feedback from SI analysis, determine desired 
                                 ///<   calibration interval for your System.  
                                 ///< - Program variable based on desired setting for CalRate.CalInterval register.
                                 ///<   See detailed register description in PUB Databook.
                                 ///< - must be set as hex
                                 ///< - Example values:
                                 ///< 
                                 ///< Value |  Calibration Interval (mS) 
                                 ///< ----- | ------
                                 ///<  0x0  | 0 (continuous) 
                                 ///<  0x3  | 1 
                                 ///<  0x4  | 2 
                                 ///<  0x8  | 10 
                           
    int CalOnce;                 ///< This setting changes the behavior of CalRun register.

                                 ///< - See PUB Databook section "Impedance Calibrator" to learn about PHY Impedance 
                                 ///<   calibration FSM. Based on feedback from SI analysis, determine desired 
                                 ///<   calibration interval for your System.  
                                 ///< - If you desire to manually trigger impedance calibration in mission mode set
                                 ///<   this variable to 1, and toggle CalRun in mission mode. See PUB Databook section
                                 ///<   "Impedance Calibration Engine Setup" and register description for CalRate.CalOnce.
                                 ///< - must be set as hex
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ------
                                 ///< 0x1   | The 0->1 transition of CSR CalRun causes a single iteration of the calibration sequence to occur.
                                 ///< 0x0   | Calibration will proceed at the rate determined by CalInterval. This field should only be changed while the calibrator is idle. ie before csr CalRun is set.
                    
    int CalImpedanceCurrentAdjustment; ///< Adjustment to bias current in the Impedance Calibration Control Circuit

                                 ///< - It is not recommended to change the default value of this parameter. 
 
    int TrainSequenceCtrl;       ///< Firmware Training Sequence Control

                                 ///< - This input is used to program SequenceCtrl in messageBlock.
                                 ///<   It controls the training stages executed by firmware.  
                                 ///<   Consult the training firmware App Note section "1D Training Steps" for details on training stages.
                                 ///< - For production silicon Synopsys recommends to use default value programmed by PhyInit.
                                 ///< - If running simulation for the first time, program value according to "Initial interactions with the firmware" section in Training firmware App Note.

    int DisableRetraining;       ///< Disable PHY DRAM Drift compensation re-training
                               
                                 ///< - Disable PHY re-training during DFI frequency change requests in LPDDR3/4.
                                 ///<   See Firmware Training App Note section "DRAM Drift Compensation" for details of steps in re-training.  
                                 ///< - The purpose of retraining is to compensate for drift in the DRAM. 
                                 ///<   Determine based on SI analysis and DRAM datasheet if retraining can be disabled.
                                 ///< - Only applied to LPDDR4/3.  No retraining is required in DDR4/3.
                                 ///< - must be set as hex
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///<   0x1 | Disable retraining 
                                 ///<   0x0 | Enable retraining 
                               
    int DisablePhyUpdate;        ///< Disable DFI PHY Update feature
                               
                                 ///< - Disable DFI PHY Update feature. When set PHY will not assert dfi0/1_phyupd_req.
                                 ///<   See DFI specification for DFI PHY update interface.  See PUB databook section 
                                 ///<   "PHY Update" for details of the DFI PHY update interface implementation.
                                 ///< - Only effects LPDDR4/3
                                 ///< - must be set as hex
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///<   0x1 | Disable DFI PHY Update
                                 ///<   0x0 | Enable DFI PHY Update


    // maybe use later
    int DisableUnusedAddrLns;    ///< Turn off or tristate Address Lanes when possible.
                                 ///<
                                 ///< - When enabled, PHY will tristate unused address lanes to save power when possible 
                                 ///<   by using Acx4AnibDis and AForceTriCont registers. 
                                 ///< - This feature is only implemented for the default PHY Address bump mapping and 
                                 ///<   Ranks must be populated in order. ie Rank1 cannot be used if Rank0 is unpopulated. 
                                 ///< - For alternative bump mapping follow the following guideline to achieve maximum power savings:
                                 ///<   - For each unused BP_A bump program AForceTriCont[4:0] bits based on register description.
                                 ///<   - if all lanes of an Anib are unused _AND_ ANIB is not the first or last instance
                                 ///<     set bit associated with the instance in Acs4AnibDis registers. see register
                                 ///<     description for details.
                                 ///< 
                                 ///< \note This feature is BETA and untested. Future PhyInit version will fully enable
                                 ///< this feature.
                                 ///<
                                 ///< Value | Description
                                 ///< ----- | ---  
                                 ///<   0x1 | Enable
                                 ///<   0x0 | Disable (default)

    int PmuClockDiv;        ///< Controls the frequency of the PMU clock

                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | Drive the PMU at full speed of the DfiClk
                            ///<   0x1 | Operate the PMU at half the DfiClk frequency (default)

    int DisablePmuEcc;      ///< disables PHY Microcontroller ECC

                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | ECC enabled (default)
                            ///<   0x1 | ECC disabled

 
    int DisableFspOp;       ///< Prevent the PHY from setting FSP-OP based on dfi_fsp input

                            ///< - LPDDR4: the PHY will set MR13.FSP-OP based on dfi_fsp input.
                            ///< - LPDDR5: the PHY will set MR16.FSP-OP based on dfi_fsp input.
                            ///<   Refer to frequency change section of PUB datatbook  
                            ///< - This behavior can be disabled if desired.
                            ///<  
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | FSP-OP enabled (default)
                            ///<   0x1 | FSP-OP disabled
    
    int RxClkTrackEn[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE]; ///< Enable PHY RxClk Drift Tracking

                            ///< - Refer to PUB databook for details of this PHY feature.
                            ///< - At data rates below DDR667 the RxClk tracking must be disabled.
                            ///<  
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | disabled
                            ///<   0x1 | enabled (default)

    int RxClkTrackWait; 	///< Time to wait between RxClk Drift Tracking runs.

                            ///< - value programmed directly in RxReplicanextcalwait register.
                            ///<   See register description for details for valid values to program.
                            ///< - must be programed as hex.

    int RxClkTrackWaitUI;   ///< Time to wait between RxClk LCDL UI calibrartion.

                            ///< - value programmed directly in RxReplicaUIcalwait register.
                            ///<   See register description for details for valid values to program.
                            ///< - must be programed as hex.

    int EnRxDqsTracking[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];  ///< Reserved for future use

                            ///<
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | disabled (default)

    int RxDqsTrackingThreshold[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];  ///< Read DQS Drift tracking threshold

                            ///< - The value specified here is programmed directly in the RxDqsTrackingThreshold register.
                            ///< - When tracking is enabled (EnRxDqsTracking = 1), this input is used to set the tracking threshold.
                            ///< - Supported settings are 3, 5 (default), 9, 15 and 31. Using the default value is recommended.
                            ///< Value | Setting
                            ///< ----- | -------
                            ///<     0 | threshold value of 3
                            ///<     1 | threshold value of 5 (default)
                            ///<     2 | threshold value of 9
                            ///<     3 | threshold value of 15
                            ///<     4 | threshold value of 31

    int DqsOscRunTimeSel[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];    ///< Informs the PHY of the DQS oscillator runtime configured in the DRAMs.

                            ///< Or the runtime used by the controller. That time must agree with the configuration of this CSR.
                            ///< - The value specified here is programmed directly in the DqsOscRunTimeSel register.
                            ///<  
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | Runtime of 256 memCK (legacy, for PHY-initiated tracking)
                            ///<   0x1 | Runtime of 512 memCK
                            ///<   0x2 | Runtime of 1024 memCK
                            ///<   0x3 | Runtime of 2048 memCK (default)
                            ///<   0x4 | Runtime of 4096 memCK
                            ///<   0x5 | Runtime of 8192 memCK

    int EnWck2DqoTracking[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];  ///< Enable Snoop Interface to modify the RxEn timing

                            ///< - The value specified here is programmed directly into the EnWck2DqoSnoopTracking register.
                            ///<
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | disabled (default)
                            ///<   0x1 | enabled

    int OnlyRestoreNonPsRegs;   ///< Restore only non-PStateable registers during retention save/restore process.
                            
                            ///< In order to speed up retention exit, the PState SRAM can be left powered on during retention.
                            ///< When this option is enabled, only no Psattable registers are included in the retention save/restore sequence. 
                            ///< Default : disabled.

    int PsDmaRamSize;       ///< Size of the PState SRAM
                    
                            ///< - See PUB Databook section on DMA and Description of csrPsDmaRamSize
                            ///< - Only used in NumPStates >2
                            ///< - Value must match PhyInit 
                            ///< Value | Description
                            ///< ----- | ------
                            ///<   0x0 | RAM is 4k deep; 256 entries per PState
                            ///<   0x1 | RAM is 8k deep; 512 entries per Pstate
                            ///<   0x2 | RAM is 16k deep; 1024 entries per Pstate (default)

 } user_input_advanced_t;


/** \brief Structure for user input simulation options (Optional)
 *
 * This structure can be programed with DRAM timing parameters for strict use
 * of the SkipTrain or SkipTrain + DevInit initialization method.  If executing
 * training firmware, this structure is not used.
 *
 */
typedef struct user_input_sim {

    int tWCK2CK;                 ///< Enter the value of tWCK2CK in ps

                                 ///< - must be set as decimal integer.
                                 ///< - for simulation only.
 
    int tWCK2DQI;                ///< Enter the value of tWCK2DQI for LPDDR5 dram in ps

                                 ///< - must be set as decimal integer.
                                 ///< - for simulation only.

    int tWCK2DQO;                ///< Enter the value of tWCK2DQO in ps

                                 ///< - must be set as decimal integer.
                                 ///< - for simulation only.

    int PHY_tDQS2DQ;             ///< This parameter represents the internal PHY tDQS2DQ (in ps).

                                 ///<- The delay value (ps) specified here is used in simulations when the training firmware is skipped, and 
                                 ///<   must match the delay from BP_DQS_T,_C in DIFF to _lcdl_rxclk in SE including the lcdl zerodelay.
                                 ///< - This delay must match what is programmed in the RTL logic model or annotated in gate level simulation.

} user_input_sim_t;
/** @} */
