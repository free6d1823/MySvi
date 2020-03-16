Release Notes - LPDDR54 PHY PHYINIT
------------------------------------------------------------------------------

The PHYINIT software is a utility intended to provide usability assistance and
guidance to customers for PHY initialization, in the form of overall procedure
and CSR writes/configurations. The PHYINIT is intended to be a supplement to
be used in conjunction with all PHY related documentation (PUB/PHY Databooks,
Application Notes, Stars on the Web, and others). The user must follow the
procedures and CSR writes/configurations as outlined in the documentation, and
must not solely rely on the PHYINIT utility to guarantee correct operation for
their configuration, platform, SoC and other implementation specific
considerations. 

------------------------------------------------------------------------------
Version A-2019.08-BETA
August 1, 2019

Preliminary Release:
(mandatory)

This version of PHY supports:

Enhancements:
-------------
- Manage PState SRAM usage based on the number of PStates used and on the PsDmaRamSize user input
- Change LPDDR5 Mode Register defaults to make them consistent with other defaults
- PIE writes PorControl CSR when entering LP3 to protect from reset_async
- PHY now waits for de-assertion of dfi_init_start for DFI retrain-only requests
- PHY now issues PDE command during frequency change (LPDDR5)
- Disable PMU clock during restore sequence after all reads are done (LPDDR5)
- Set tWCK2DQO and tWCK2DQI to non-zero default value (LPDDR5)

Bug fixes:
----------
- Fix programming of DxDfiClkDis and DxPClkDis for WCK and DMI lanes
- Fixes to enable S3 restore combined with 15-pstate mode
- Initialize FirstPState, PsDmaRamSize inputs in setDefault
- Fixes to input validation checking
- Remove programming of SingleEndedMode in Step C, handled by progCsrSkipTrain
- PHY will not issue MRW to MR28 during frequency change (LPDDR5)
- Fix retraining sequence to keep WCK toggling until CAS Sync OFF (LPDDR5)
- Update DFIMRL calculation to take into account AcPipeEn in progCsrSkipTrain (LPDDR5)

Input Changes:
--------------

User input field removed:
- DmiDbiEn

Changes to input data structures:
- FirstPState input moved from Advanced to Basic input set

Firmware MessageBlock changes:
- UseBroadcastMR removed
- VrefSamples added
- PhyConfigOverride removed (LPDDR4)
- ALT_RL and MAIN_RL added (LPDDR4)
- Several entries added for DFE and DCA (LPDDR5) 

Limitations:
------------
- User input EnRxDqsTracking is reserved for future use

Compiler Version:
-----------------
Compiler version used during the QA testing of this release.
- gcc 4.7.2
 
Minimum Required Versions
-------------------------
- PHY PUB:  1.02a
- Firmware: A-2019.08-BETA


------------------------------------------------------------------------------
Version A-2019.06-BETA
----------------------
June 20, 2019

Preliminary Release: (mandatory)

This version of PHY supports:
-----------------------------

Enhancements:
- LPDDR5 support for DRAM in Deep Sleep Mode on retention entry/exit
- LPDDR5 support for different configurations of NZQ (for tZQCAL)
- Support for memory controller to hand over DRAM in Self-Refresh for phymstr & DFI requests
- Provide P14 p-state transition from P[0..6] and P[7..13]
- Changes related to reset, protect reset pin during boot
- Fixed programming of CkDisVal
- Fixes related to RxClk tracking
- Fixes to some PHY-initiated commands
- Fixes to support DVFS-C and DVFS-Q (LPDDR5)
- Program RxStandbyExnt instead of using reset value

Input Changes:
- User input fields added:
    - MaxNumZQ (LPDDR5)
- Message block fields added:
    - Disable2d
    - LP4XMode (LPDDR4X)
    - X8Mode (LPDDR5)

Changes to input data structures:
- Change default values for tDQS2DQ and tDQSCK (for SkipTrain simulation only)

Limitations:
------------
- User input EnRxDqsTracking is reserved for future use
- Only support PS SRAM size of 1024

Compiler Version:
-----------------
Compiler version used during the QA testing of this release.
- gcc 4.7.2
 
Minimum Required Versions
-------------------------
- PHY PUB:  1.01a
- Firmware: A-2019.06-BETA


------------------------------------------------------------------------------
Version A-2019.04-BETA
----------------------
May 2, 2019

Preliminary Release: (mandatory)

This version of PHY supports:
-----------------------------

Enhancements:
- Added support for 15 PStates
- Added Support LPDDR5 WCK Free Running Mode with retraining
- Added Support LPDDR5 Strobe-less Read mode
- RxClk tracking and correction, now enabled by default
- Make sure HwtLpCsEnA and HwtLpCsEnB are programmed in LP5
- Simplified function arguments to use pointers to single global structure

Input Changes:
- User input fields added:
    - OdtImpedanceCa
    - OdtImpedanceCs
    - OdtImpedanceCk
    - EnWck2DqoTracking (LPDDR5), enable Snoop Interface
    - CfgPState
    - FirstPState
- User input fields removed:
    - PclkPtrInitVal
- Changes in input data structures:
    - DramByteSwap input changed from user_input_sim_t to user_input_advanced_t
    - OdtImpedanceDq defaults to 60 Ohms instead of 30

Limitations:
------------
- User input EnRxDqsTracking is reserved for future use
- Only support PS SRAM size of 1024

Compiler Version:
-----------------
Compiler version used during the QA testing of this release.
- gcc 4.7.2
 
Minimum Required Versions
-------------------------
- PHY PUB:  1.00a
- Firmware: A-2019.04-BETA


------------------------------------------------------------------------------
Version A-2019.02-BETA
----------------------
February 22, 2019

Preliminary Release: (recommended)

This version of PHY supports:
-----------------------------

General features:
- 2 Pstate PM Transition
- x8, x16 and mixed mode supported
- RXClk tracking is supported
- Single Ended Mode is supported
- Read DQS Tracking is supported
- ASST Feature is supported
- On the fly frequency ratio switching
- DFE feature is supported
- Periodic Phase Training Support added for LPDDR4
- Periodic Phase Training Support added in non-free running WCK mode for LPDDR5

PhyInit input changes
- User input fields added:
    - FirstPState
    - PmuClockDiv
- User input fields removed (use the LPDDR4 mode register settings instead):
    - Lp4PostambleExt
    - Lp4RL
    - Lp4WL
    - Lp4WLS
    - Lp4DbiRd
    - Lp4DbiWr
    - Lp4nWR

Limitations to PhyInit:
-----------------------
- Snoop feature is not supported by PhyInit
- LPDDR5 strobe-less read mode not supported by PhyInit
- LPDDR5 Periodic Phase Training does not support WCK Free Running mode

Compiler Version Used:
---------------------
Compiler version used during the QA testing of this release.
- gcc 4.7.2
 
Minimum Required Versions
-------------------------
- PHY PUB:  0.60a
- Firmware: A-2019.02-BETA


------------------------------------------------------------------------------
Version A-2018.12-BETA
----------------------
December 21, 2018

Preliminary Release: (recommended)

This version of PHY supports:
-----------------------------

General features:
- DFT features:
    - Bypass(flyover) feature is supported
    - LCDL linearity feature is supported
    - TRD feature for CSR write/read is supported
- PMU ECC error feature is supported
- PHY INTERRUPT feature is supported
- PHY board delay range support per PUB databook 
- DFI side-band feature:
    - LP data and LP ctrl is supported for both LP4/5
    - Ctrl/Phy update is supported for both LP4/5
    - Ctrlmsg/Pymst/PPT is supported for LP4 only
    - Snoop feature is supported for LP4 only
    - Pstate transition timing is not finalized yet
- DFI timing parameters: per databook (excluding Pstate transition timing)

LPDDR4: 
- Data rates: 50MT/s to 4267MT/s
- Dficlk and CK ratio as 2:1 and 4:1 are supported
- LPDDR4/4x X8, x16 and mixed mode are supported
- Bye-swap feature is used in x8 mode support
- LPDDR4x single-ended mode is supported, with the restriction that all Pstates must have the same setting
- WDQS extension is supported
- AC/DBYTE Swizzle is supported
- Periodic Phase Training is not supported

LPDDR5: 
- Data rates:  
    - CK:WCK 1:2 ratio: 48MT/s to 32000MT/s
    - CK:WCK 1:4 ratio: 176MT/s to 6400MT/s
- LPDDR5 x16 is supported
- LPDDR5 single-ended mode is supported, with the restriction that all Pstates must have the same setting
- AC/DBYTE Swizzle is supported
- WCK free running and WCK non-free running modes are supported
- RXClk tracking is not supported
- LPDDR5 x8 and mixed mode is not supported yet
- LPDDR5 strobe-less read mode is not supported yet 
- Periodic Phase Training is not supported

Special Notes
-----------
### Limitations and requirements related to frequency change:
The final LPDDR54 PHY will handle MR programming during Pstate change. The current release does not perform MR programming during Pstate change.
- Current LPDDR54 PHY sends MRW to transition FSP during Pstate transition (MR16).
- Memory controller needs to write other MRS affected by FSP-OP.
- Only 2 Pstates are supported (0 and 1).
- The memory controller must bring LPDDR54 PHY back to previous Pstate after S3 retention.

### MR programming requirement for SkipTrain()

This release supports 2 PStates. In mission mode the training firmware loads the MRs for the trained PSTATE in the DRAM.  
In SkipTrain simulation environment, this step is skipped and the MC/test must backdoor program the DRAM MRs as part of dwc_ddrphy_userCusom_customPost() if DisableFsp=0.   
The DRAM MRs that have FSP copies must be programmed such that FSP0 MRs match PS0 and FSP1 MRs match PS1.   
The following table provides the list of MRs that are replicated for each FSP and must be programmed:

Protocol | MRs to be programmed
---------| --------------------------------------
LPDDR4   | 1,2,3,11,12,14,22
LPDDR4X  | 1,2,3,11,12,14,22,21,51
LPDDR5	 | 1,2,3,10,11,12,14,15,17,18,19,20,30,41

Once the MRs are programmed, the PHY will issue MR13/MR16 writes during tinit_start and tinit_complete following FSP switching scheme in JEDEC.  
In future releases, the PHY will perform above MR programming and this backdoor MR programming will not be required.

Compiler Version Used:
---------------------
Compiler version used during the QA testing of this release.
- gcc 4.7.2
 
Minimum Required Versions
-------------------------
- PHY PUB:  0.50a
- Firmware: A-2018.12-BETA


-----------------------------------------------------------------------------------------------------------
Version A-2018.10-BETA
----------------------
November 8, 2018

Preliminary Release

This version of PHY Supports:
-----------------------------

- All LPDDR4 Transactions with all valid spacings.
- All LPDDR5 Transactions with all valid spacings.
- LPDDR5 support of all JEDEC supported clock ratios.
- LPDDR5 Support for Free Running and Non-Free Running Mode.
- DFI sidebands for LPDDR4 and LPDDR5 :
      - PHYUPD, CTRLUPD
      - DFI_LP
      - DFI_DRAM_CLK_DISABLE
- All the valid Read and Write Pre-amble and Post-amble configurations mentioned in the PUB Databook for LPDDR4 and LPDDR5.

Enhancements Done:
------------------

- LPDDR5 support added.

Minimum Required Versions
-------------------------

- PHY PUB:  0.40a
- Firmware: A-2018.10-BETA
