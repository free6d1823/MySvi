typedef struct _PMU_SMB_LPDDR4_1D_t {
   uint8_t  Reserved00;       // Byte offset 0x00, CSR Addr 0x54000, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  MsgMisc;          // Byte offset 0x01, CSR Addr 0x54000, Direction=In
                              // Contains various global options for training.
                              // 
                              // Bit fields:
                              // 
                              // MsgMisc[0] MTESTEnable
                              //      0x1 = Pulse primary digital test output bump at the end of each major training stage. This enables observation of training stage completion by observing the digital test output.
                              //      0x0 = Do not pulse primary digital test output bump
                              // 
                              // MsgMisc[1] SimulationOnlyReset
                              //      0x1 = Verilog only simulation option to shorten duration of DRAM reset pulse length to 1ns. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use reset pulse length specifed by JEDEC standard
                              // 
                              // MsgMisc[2] SimulationOnlyTraining
                              //      0x1 = Verilog only simulation option to shorten the duration of the training steps by performing fewer iterations. 
                              //                Must never be set to 1 in silicon.
                              //      0x0 = Use standard training duration.
                              // 
                              // MsgMisc[3] Disable Boot Clock 
                              //      0x1 = Disable boot frequency clock when initializing DRAM. (not recommended)
                              //      0x0 = Use Boot Frequency Clock 
                              // 
                              // MsgMisc[4] Suppress streaming messages, including assertions, regardless of HdtCtrl setting.
                              //            Stage Completion messages, as well as training completion and error messages are
                              //            Still sent depending on HdtCtrl setting.
                              // 
                              // MsgMisc[7-5] RFU, must be zero
                              // 
                              // Notes: 
                              // 
                              // - SimulationOnlyReset and SimulationOnlyTraining can be used to speed up simulation run times, and must never be used in real silicon. Some VIPs may have checks on DRAM reset parameters that may need to be disabled when using SimulationOnlyReset.
   uint16_t PmuRevision;      // Byte offset 0x02, CSR Addr 0x54001, Direction=Out
                              // PMU firmware revision ID
                              // After training is run, this address will contain the revision ID of the firmware
   uint8_t  Pstate;           // Byte offset 0x04, CSR Addr 0x54002, Direction=In
                              // Must be set to the target Pstate to be trained 0 -15
                              //  Pstate [7] - when set will use 15 Pstate Mode DMA transfer
   uint8_t  PllBypassEn;      // Byte offset 0x05, CSR Addr 0x54002, Direction=In
                              // Set according to whether target Pstate uses PHY PLL bypass
                              //    0x0 = PHY PLL is enabled for target Pstate
                              //    0x1 = PHY PLL is bypassed for target Pstate
   uint16_t DRAMFreq;         // Byte offset 0x06, CSR Addr 0x54003, Direction=In
                              // DDR data rate for the target Pstate in units of MT/s.
                              // For example enter 0x0640 for DDR1600.
   uint8_t  DfiFreqRatio;     // Byte offset 0x08, CSR Addr 0x54004, Direction=In
                              // Frequency ratio betwen DfiCtlClk and SDRAM memclk.
                              //    0X2 = 1:2
                              //    0x4 = 1:4
   uint8_t  BPZNResVal ;      // Byte offset 0x09, CSR Addr 0x54004, Direction=In
                              // Move to Phyinit
   uint8_t  PhyOdtImpedance;  // Byte offset 0x0a, CSR Addr 0x54005, Direction=In
                              // Move to Phyinit
   uint8_t  PhyDrvImpedance;  // Byte offset 0x0b, CSR Addr 0x54005, Direction=In
                              // Move to Phyinit
   uint8_t  PhyVref;          // Byte offset 0x0c, CSR Addr 0x54006, Direction=In
                              // Move to Phyinit
   uint8_t  Lp4Misc;          // Byte offset 0x0d, CSR Addr 0x54006, Direction=In
                              // Rename to Misc
                              // Lp4 specific options for training.
                              // 
                              // Bit fields:
                              // 
                              // Lp4Misc[0] Enable dfi_reset_n
                              // 
                              // 0x0 = (Recommended) PHY internal registers control memreset during training, and also after training.
                              //  dfi_reset_n cannot control the PHY BP_MEMRESET_L pin.
                              // 
                              // 0x1 = Enables dfi_reset_n to control memreset after training.
                              //  PHY Internal registers control memreset during training only.
                              //  To ensure that no glitches occur on BP_MEMRESET at the end of training, 
                              //  The MC must drive dfi_reset_n=1'b1 _prior to starting training_
                              // 
                              // Lp4Misc[7-1] RFU, must be zero
   uint8_t  Reserved0E;       // Byte offset 0x0e, CSR Addr 0x54007, Direction=In
                              // Split these into multiple fields for more granularity
                              // Bit Field for enabling optional 2D training features that impact both Rx2D and Tx2D. 
                              // 
                              // Reserved0E[0:3]: bitTimeControl 
                              //     Input for increasing the number of data-comparisons 2D runs per (delay,voltage) point. Every time this input increases by 1, the number of 2D data comparisons is doubled. The 2D run time will increase proportionally to the number of bit times requested per point. 
                              //     0 = 288 bits per point (legacy behavior)
                              //     1 = 576 bits per point 
                              //     2 = 1.125 kilobits per point
                              //     . . .
                              //     15 = 9 megabits per point
                              // 
                              // Reserved0E[4]: Exhaustive2D
                              //     0 = 2D's optimization assumes the optimal trained point is near the 1D trained point (legacy behavior)
                              //     1 = 2D's optimization searches the entire passing region at the cost of run time. Recommended for optimal results any time the optimal trained point is expected to be near the edges of the eyes instead of near the 1D trained point. 
                              // 
                              // Reserved0E[5:7]: RFU, must be 0
   uint8_t  CsTestFail;       // Byte offset 0x0f, CSR Addr 0x54007, Direction=Out
                              // This field will be set if training fails on any rank.
                              //    0x0 = No failures
                              //    non-zero = one or more ranks failed training
   uint16_t SequenceCtrl;     // Byte offset 0x10, CSR Addr 0x54008, Direction=In
                              // Controls the training steps to be run. Each bit corresponds to a training step. 
                              // 
                              // If the bit is set to 1, the training step will run. 
                              // If the bit is set to 0, the training step will be skipped.
                              // 
                              // Training step to bit mapping:
                              //    SequenceCtrl[0] = Run DevInit - Device/phy initialization. Should always be set.
                              //    SequenceCtrl[1] = Run WrLvl - Write leveling
                              //    SequenceCtrl[2] = Run RxEn - Read gate training
                              //    SequenceCtrl[3] = RFU, must be zero
                              //    SequenceCtrl[4] = RFU, must be zero
                              //    SequenceCtrl[5] = Run RdDQS - read dqs training
                              //    SequenceCtrl[6] = Run WrDq - write dq training
                              //    SequenceCtrl[7] = RFU, must be zero
                              //    SequenceCtrl[8] = RFU, must be zero
                              //    SequenceCtrl[9] = Run MxRdLat - Max read latency training
                              //    SequenceCtrl[11-10] = RFU, must be zero
                              //    SequenceCtrl[12] = Run LPCA - CA Training
                              //    SequenceCtrl[15-13] = RFU, must be zero
   uint8_t  HdtCtrl;          // Byte offset 0x12, CSR Addr 0x54009, Direction=In
                              // To control the total number of debug messages, a verbosity subfield (HdtCtrl, Hardware Debug Trace Control) exists in the message block. Every message has a verbosity level associated with it, and as the HdtCtrl value is increased, less important s messages stop being sent through the mailboxes. The meanings of several major HdtCtrl thresholds are explained below:
                              // 
                              //    0x05 = Detailed debug messages (e.g. Eye delays)
                              //    0x0A = Coarse debug messages (e.g. rank information)
                              //    0xC8 = Stage completion
                              //    0xC9 = Assertion messages
                              //    0xFF = Firmware completion messages only
                              // 
                              // See Training App Note for more detailed information on what messages are included for each threshold.
                              // 
   uint8_t  Reserved13;       // Byte offset 0x13, CSR Addr 0x54009, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved14;       // Byte offset 0x14, CSR Addr 0x5400a, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved15;       // Byte offset 0x15, CSR Addr 0x5400a, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  DFIMRLMargin;     // Byte offset 0x16, CSR Addr 0x5400b, Direction=In
                              // Margin added to smallest passing trained DFI Max Read Latency value, in units of DFI clocks. Recommended to be >= 1. See the Training App Note for more details on the training process and the use of this value.
                              // 
                              // This margin must include the maximum positive drift expected in tDQSCK over the target temperature and voltage range of the users system.
   uint8_t  Reserved17;       // Byte offset 0x17, CSR Addr 0x5400b, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved18;       // Byte offset 0x18, CSR Addr 0x5400c, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Lp4Quickboot;     // Byte offset 0x19, CSR Addr 0x5400c, Direction=In
                              // Enable Quickboot.
   uint8_t  Reserved1A;       // Byte offset 0x1a, CSR Addr 0x5400d, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  CATrainOpt;       // Byte offset 0x1b, CSR Addr 0x5400d, Direction=In
                              // CA training option bit field
                              // [0] CA VREF Training
                              //        1 = Enable CA VREF Training
                              //        0 = Disable CA VREF Training
                              //       WARNING: CATrainOpt[0] must be set to the same value in 1D and 2D training. 
                              // [1-7] RFU must be zero
   uint8_t  X8Mode;           // Byte offset 0x1c, CSR Addr 0x5400e, Direction=In
                              // X8 mode configuration:
                              // 0x0 = x16 configuration for all devices
                              // 0xF =  x8 configuration for all devices
                              // All other values are RFU
   uint8_t  Reserved1D;    // Byte offset 0x1d, CSR Addr 0x5400e, Direction=N/A
                              
   uint8_t  Reserved1E;    // Byte offset 0x1e, CSR Addr 0x5400f, Direction=N/A
                              
   uint8_t  Reserved1F;       // Byte offset 0x1f, CSR Addr 0x5400f, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20;   // Byte offset 0x20, CSR Addr 0x54010, Direction=N/A
                              
   uint8_t  Reserved21; // Byte offset 0x21, CSR Addr 0x54010, Direction=N/A
                              
   uint8_t  Reserved22;       // Byte offset 0x22, CSR Addr 0x54011, Direction=In
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved23;       // Byte offset 0x23, CSR Addr 0x54011, Direction=
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  EnabledDQsChA;    // Byte offset 0x24, CSR Addr 0x54012, Direction=In
                              // Total number of DQ bits enabled in PHY Channel A
   uint8_t  CsPresentChA;     // Byte offset 0x25, CSR Addr 0x54012, Direction=In
                              // Indicates presence of DRAM at each chip select for PHY channel A.
                              // 
                              //  0x1 = CS0 is populated with DRAM
                              //  0x3 = CS0 and CS1 are populated with DRAM
                              // 
                              // All other encodings are illegal
                              //  
   int8_t   CDD_ChA_RR_1_0;   // Byte offset 0x26, CSR Addr 0x54013, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 0 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_RR_0_1;   // Byte offset 0x27, CSR Addr 0x54013, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 1 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_RW_1_1;   // Byte offset 0x28, CSR Addr 0x54014, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 1 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_RW_1_0;   // Byte offset 0x29, CSR Addr 0x54014, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 0 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_RW_0_1;   // Byte offset 0x2a, CSR Addr 0x54015, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 1 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_RW_0_0;   // Byte offset 0x2b, CSR Addr 0x54015, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs0 to cs 0 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_WR_1_1;   // Byte offset 0x2c, CSR Addr 0x54016, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 1 to cs 1 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_WR_1_0;   // Byte offset 0x2d, CSR Addr 0x54016, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 1 to cs 0 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_WR_0_1;   // Byte offset 0x2e, CSR Addr 0x54017, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 0 to cs 1 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_WR_0_0;   // Byte offset 0x2f, CSR Addr 0x54017, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 0 to cs 0 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_WW_1_0;   // Byte offset 0x30, CSR Addr 0x54018, Direction=Out
                              // This is a signed integer value.
                              // Write  to write critical delay difference from cs 1 to cs 0 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChA_WW_0_1;   // Byte offset 0x31, CSR Addr 0x54018, Direction=Out
                              // This is a signed integer value.
                              // Write  to write critical delay difference from cs 0 to cs 1 on Channel A
                              // See PUB Databook section 8.2 for details on use of CDD values.
   uint8_t  MR1_A0;           // Byte offset 0x32, CSR Addr 0x54019, Direction=In
                              // Value to be programmed in DRAM Mode Register 1 {Channel A, Rank 0}
   uint8_t  MR2_A0;           // Byte offset 0x33, CSR Addr 0x54019, Direction=In
                              // Value to be programmed in DRAM Mode Register 2 {Channel A, Rank 0}
   uint8_t  MR3_A0;           // Byte offset 0x34, CSR Addr 0x5401a, Direction=In
                              // Value to be programmed in DRAM Mode Register 3 {Channel A, Rank 0}
   uint8_t  MR4_A0;           // Byte offset 0x35, CSR Addr 0x5401a, Direction=In
                              // Value to be programmed in DRAM Mode Register 4 {Channel A, Rank 0}
   uint8_t  MR11_A0;          // Byte offset 0x36, CSR Addr 0x5401b, Direction=In
                              // Value to be programmed in DRAM Mode Register 11 {Channel A, Rank 0}
   uint8_t  MR12_A0;          // Byte offset 0x37, CSR Addr 0x5401b, Direction=In
                              // Value to be programmed in DRAM Mode Register 12 {Channel A, Rank 0}
   uint8_t  MR13_A0;          // Byte offset 0x38, CSR Addr 0x5401c, Direction=In
                              // Value to be programmed in DRAM Mode Register 13 {Channel A, Rank 0}
   uint8_t  MR14_A0;          // Byte offset 0x39, CSR Addr 0x5401c, Direction=In
                              // Value to be programmed in DRAM Mode Register 14 {Channel A, Rank 0}
   uint8_t  MR16_A0;          // Byte offset 0x3a, CSR Addr 0x5401d, Direction=In
                              // Value to be programmed in DRAM Mode Register 16 {Channel A, Rank 0}
   uint8_t  MR17_A0;          // Byte offset 0x3b, CSR Addr 0x5401d, Direction=In
                              // Value to be programmed in DRAM Mode Register 17 {Channel A, Rank 0}
   uint8_t  MR22_A0;          // Byte offset 0x3c, CSR Addr 0x5401e, Direction=In
                              // Value to be programmed in DRAM Mode Register 22 {Channel A, Rank 0}
   uint8_t  MR24_A0;          // Byte offset 0x3d, CSR Addr 0x5401e, Direction=In
                              // Value to be programmed in DRAM Mode Register 24 {Channel A, Rank 0}
   uint8_t  MR1_A1;           // Byte offset 0x3e, CSR Addr 0x5401f, Direction=In
                              // Value to be programmed in DRAM Mode Register 1 {Channel A, Rank 1}
   uint8_t  MR2_A1;           // Byte offset 0x3f, CSR Addr 0x5401f, Direction=In
                              // Value to be programmed in DRAM Mode Register 2 {Channel A, Rank 1}
   uint8_t  MR3_A1;           // Byte offset 0x40, CSR Addr 0x54020, Direction=In
                              // Value to be programmed in DRAM Mode Register 3 {Channel A, Rank 1}
   uint8_t  MR4_A1;           // Byte offset 0x41, CSR Addr 0x54020, Direction=In
                              // Value to be programmed in DRAM Mode Register 4 {Channel A, Rank 1}
   uint8_t  MR11_A1;          // Byte offset 0x42, CSR Addr 0x54021, Direction=In
                              // Value to be programmed in DRAM Mode Register 11 {Channel A, Rank 1}
   uint8_t  MR12_A1;          // Byte offset 0x43, CSR Addr 0x54021, Direction=In
                              // Value to be programmed in DRAM Mode Register 12 {Channel A, Rank 1}
   uint8_t  MR13_A1;          // Byte offset 0x44, CSR Addr 0x54022, Direction=In
                              // Value to be programmed in DRAM Mode Register 13 {Channel A, Rank 1}
   uint8_t  MR14_A1;          // Byte offset 0x45, CSR Addr 0x54022, Direction=In
                              // Value to be programmed in DRAM Mode Register 14 {Channel A, Rank 1}
   uint8_t  MR16_A1;          // Byte offset 0x46, CSR Addr 0x54023, Direction=In
                              // Value to be programmed in DRAM Mode Register 16 {Channel A, Rank 1}
   uint8_t  MR17_A1;          // Byte offset 0x47, CSR Addr 0x54023, Direction=In
                              // Value to be programmed in DRAM Mode Register 17 {Channel A, Rank 1}
   uint8_t  MR22_A1;          // Byte offset 0x48, CSR Addr 0x54024, Direction=In
                              // Value to be programmed in DRAM Mode Register 22 {Channel A, Rank 1}
   uint8_t  MR24_A1;          // Byte offset 0x49, CSR Addr 0x54024, Direction=In
                              // Value to be programmed in DRAM Mode Register 24 {Channel A, Rank 1}
   uint8_t  CATerminatingRankChA; // Byte offset 0x4a, CSR Addr 0x54025, Direction=In
                              // Terminating Rank for CA bus on Channel A
                              //    0x0 = Rank 0 is terminating rank
                              //    0x1 = Rank 1 is terminating rank
   uint8_t  Reserved4B; // Byte offset 0x4b, CSR Addr 0x54025, Direction=N/A
                              
   uint8_t  Reserved4C; // Byte offset 0x4c, CSR Addr 0x54026, Direction=N/A
                              
   uint8_t  Reserved4D; // Byte offset 0x4d, CSR Addr 0x54026, Direction=N/A
                              
   uint8_t  Reserved4E; // Byte offset 0x4e, CSR Addr 0x54027, Direction=N/A
                              
   uint8_t  Reserved4F; // Byte offset 0x4f, CSR Addr 0x54027, Direction=N/A
                              
   uint8_t  Reserved50; // Byte offset 0x50, CSR Addr 0x54028, Direction=N/A
                              
   uint8_t  Reserved51; // Byte offset 0x51, CSR Addr 0x54028, Direction=N/A
                              
   uint8_t  Reserved52; // Byte offset 0x52, CSR Addr 0x54029, Direction=N/A
                              
   uint8_t  Reserved53; // Byte offset 0x53, CSR Addr 0x54029, Direction=N/A
                              
   uint8_t  Reserved54; // Byte offset 0x54, CSR Addr 0x5402a, Direction=N/A
                              
   uint8_t  Reserved55; // Byte offset 0x55, CSR Addr 0x5402a, Direction=N/A
                              
   uint8_t  Reserved56; // Byte offset 0x56, CSR Addr 0x5402b, Direction=N/A
                              
   uint8_t  EnabledDQsChB;    // Byte offset 0x57, CSR Addr 0x5402b, Direction=In
                              // Total number of DQ bits enabled in PHY Channel B
   uint8_t  CsPresentChB;     // Byte offset 0x58, CSR Addr 0x5402c, Direction=In
                              // Indicates presence of DRAM at each chip select for PHY channel B.
                              // 
                              //    0x0 = No chip selects are populated with DRAM
                              //    0x1 = CS0 is populated with DRAM
                              //    0x3 = CS0 and CS1 are populated with DRAM
                              // 
                              // All other encodings are illegal
                              //  
   int8_t   CDD_ChB_RR_1_0;   // Byte offset 0x59, CSR Addr 0x5402c, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 1 to cs 0 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_RR_0_1;   // Byte offset 0x5a, CSR Addr 0x5402d, Direction=Out
                              // This is a signed integer value.
                              // Read to read critical delay difference from cs 0 to cs 1 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_RW_1_1;   // Byte offset 0x5b, CSR Addr 0x5402d, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 1 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_RW_1_0;   // Byte offset 0x5c, CSR Addr 0x5402e, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 1 to cs 0 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_RW_0_1;   // Byte offset 0x5d, CSR Addr 0x5402e, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs 0 to cs 1 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_RW_0_0;   // Byte offset 0x5e, CSR Addr 0x5402f, Direction=Out
                              // This is a signed integer value.
                              // Read to write critical delay difference from cs01 to cs 0 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_WR_1_1;   // Byte offset 0x5f, CSR Addr 0x5402f, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 1 to cs 1 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_WR_1_0;   // Byte offset 0x60, CSR Addr 0x54030, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 1 to cs 0 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_WR_0_1;   // Byte offset 0x61, CSR Addr 0x54030, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 0 to cs 1 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_WR_0_0;   // Byte offset 0x62, CSR Addr 0x54031, Direction=Out
                              // This is a signed integer value.
                              // Write  to read critical delay difference from cs 0 to cs 0 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_WW_1_0;   // Byte offset 0x63, CSR Addr 0x54031, Direction=Out
                              // This is a signed integer value.
                              // Write  to write critical delay difference from cs 1 to cs 0 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   int8_t   CDD_ChB_WW_0_1;   // Byte offset 0x64, CSR Addr 0x54032, Direction=Out
                              // This is a signed integer value.
                              // Write  to write critical delay difference from cs 0 to cs 1 on Channel B
                              // See PUB Databook section 8.2 for details on use of CDD values.
   uint8_t  MR1_B0;           // Byte offset 0x65, CSR Addr 0x54032, Direction=In
                              // Value to be programmed in DRAM Mode Register 1 {Channel B, Rank 0}
   uint8_t  MR2_B0;           // Byte offset 0x66, CSR Addr 0x54033, Direction=In
                              // Value to be programmed in DRAM Mode Register 2 {Channel B, Rank 0}
   uint8_t  MR3_B0;           // Byte offset 0x67, CSR Addr 0x54033, Direction=In
                              // Value to be programmed in DRAM Mode Register 3 {Channel B, Rank 0}
   uint8_t  MR4_B0;           // Byte offset 0x68, CSR Addr 0x54034, Direction=In
                              // Value to be programmed in DRAM Mode Register 4 {Channel B, Rank 0}
   uint8_t  MR11_B0;          // Byte offset 0x69, CSR Addr 0x54034, Direction=In
                              // Value to be programmed in DRAM Mode Register 11 {Channel B, Rank 0}
   uint8_t  MR12_B0;          // Byte offset 0x6a, CSR Addr 0x54035, Direction=In
                              // Value to be programmed in DRAM Mode Register 12 {Channel B, Rank 0}
   uint8_t  MR13_B0;          // Byte offset 0x6b, CSR Addr 0x54035, Direction=In
                              // Value to be programmed in DRAM Mode Register 13 {Channel B, Rank 0}
   uint8_t  MR14_B0;          // Byte offset 0x6c, CSR Addr 0x54036, Direction=In
                              // Value to be programmed in DRAM Mode Register 14 {Channel B, Rank 0}
   uint8_t  MR16_B0;          // Byte offset 0x6d, CSR Addr 0x54036, Direction=In
                              // Value to be programmed in DRAM Mode Register 16 {Channel B, Rank 0}
   uint8_t  MR17_B0;          // Byte offset 0x6e, CSR Addr 0x54037, Direction=In
                              // Value to be programmed in DRAM Mode Register 17 {Channel B, Rank 0}
   uint8_t  MR22_B0;          // Byte offset 0x6f, CSR Addr 0x54037, Direction=In
                              // Value to be programmed in DRAM Mode Register 22 {Channel B, Rank 0}
   uint8_t  MR24_B0;          // Byte offset 0x70, CSR Addr 0x54038, Direction=In
                              // Value to be programmed in DRAM Mode Register 24 {Channel B, Rank 0}
   uint8_t  MR1_B1;           // Byte offset 0x71, CSR Addr 0x54038, Direction=In
                              // Value to be programmed in DRAM Mode Register 1 {Channel B, Rank 1}
   uint8_t  MR2_B1;           // Byte offset 0x72, CSR Addr 0x54039, Direction=In
                              // Value to be programmed in DRAM Mode Register 2 {Channel B, Rank 1}
   uint8_t  MR3_B1;           // Byte offset 0x73, CSR Addr 0x54039, Direction=In
                              // Value to be programmed in DRAM Mode Register 3 {Channel B, Rank 1}
   uint8_t  MR4_B1;           // Byte offset 0x74, CSR Addr 0x5403a, Direction=In
                              // Value to be programmed in DRAM Mode Register 4 {Channel B, Rank 1}
   uint8_t  MR11_B1;          // Byte offset 0x75, CSR Addr 0x5403a, Direction=In
                              // Value to be programmed in DRAM Mode Register 11 {Channel B, Rank 1}
   uint8_t  MR12_B1;          // Byte offset 0x76, CSR Addr 0x5403b, Direction=In
                              // Value to be programmed in DRAM Mode Register 12 {Channel B, Rank 1}
   uint8_t  MR13_B1;          // Byte offset 0x77, CSR Addr 0x5403b, Direction=In
                              // Value to be programmed in DRAM Mode Register 13 {Channel B, Rank 1}
   uint8_t  MR14_B1;          // Byte offset 0x78, CSR Addr 0x5403c, Direction=In
                              // Value to be programmed in DRAM Mode Register 14 {Channel B, Rank 1}
   uint8_t  MR16_B1;          // Byte offset 0x79, CSR Addr 0x5403c, Direction=In
                              // Value to be programmed in DRAM Mode Register 16 {Channel B, Rank 1}
   uint8_t  MR17_B1;          // Byte offset 0x7a, CSR Addr 0x5403d, Direction=In
                              // Value to be programmed in DRAM Mode Register 17 {Channel B, Rank 1}
   uint8_t  MR22_B1;          // Byte offset 0x7b, CSR Addr 0x5403d, Direction=In
                              // Value to be programmed in DRAM Mode Register 22 {Channel B, Rank 1}
   uint8_t  MR24_B1;          // Byte offset 0x7c, CSR Addr 0x5403e, Direction=In
                              // Value to be programmed in DRAM Mode Register 24 {Channel B, Rank 1}
   uint8_t  CATerminatingRankChB; // Byte offset 0x7d, CSR Addr 0x5403e, Direction=In
                              // Terminating Rank for CA bus on Channel B
                              //    0x0 = Rank 0 is terminating rank
                              //    0x1 = Rank 1 is terminating rank
   uint8_t  Reserved7E; // Byte offset 0x7e, CSR Addr 0x5403f, Direction=N/A
                              
   uint8_t  Reserved7F; // Byte offset 0x7f, CSR Addr 0x5403f, Direction=N/A
                              
   uint8_t  Reserved80; // Byte offset 0x80, CSR Addr 0x54040, Direction=N/A
                              
   uint8_t  Reserved81; // Byte offset 0x81, CSR Addr 0x54040, Direction=N/A
                              
   uint8_t  Reserved82; // Byte offset 0x82, CSR Addr 0x54041, Direction=N/A
                              
   uint8_t  Reserved83; // Byte offset 0x83, CSR Addr 0x54041, Direction=N/A
                              
   uint8_t  Reserved84; // Byte offset 0x84, CSR Addr 0x54042, Direction=N/A
                              
   uint8_t  Reserved85; // Byte offset 0x85, CSR Addr 0x54042, Direction=N/A
                              
   uint8_t  Reserved86; // Byte offset 0x86, CSR Addr 0x54043, Direction=N/A
                              
   uint8_t  Reserved87; // Byte offset 0x87, CSR Addr 0x54043, Direction=N/A
                              
   uint8_t  Reserved88; // Byte offset 0x88, CSR Addr 0x54044, Direction=N/A
                              
   uint8_t  Reserved89; // Byte offset 0x89, CSR Addr 0x54044, Direction=N/A
                              
   uint8_t  MR21_A0;          // Byte offset 0x8a, CSR Addr 0x54045, Direction=In
                              // Value to be programmed in DRAM Mode Register 21 {Channel A, Rank 0}
   uint8_t  MR51_A0;          // Byte offset 0x8b, CSR Addr 0x54045, Direction=In
                              // Value to be programmed in DRAM Mode Register 51 {Channel A, Rank 0}
   uint8_t  MR21_A1;          // Byte offset 0x8c, CSR Addr 0x54046, Direction=In
                              // Value to be programmed in DRAM Mode Register 21 {Channel A, Rank 1}
   uint8_t  MR51_A1;          // Byte offset 0x8d, CSR Addr 0x54046, Direction=In
                              // Value to be programmed in DRAM Mode Register 51 {Channel A, Rank 1}
   uint8_t  MR21_B0;          // Byte offset 0x8e, CSR Addr 0x54047, Direction=In
                              // Value to be programmed in DRAM Mode Register 21 {Channel B, Rank 0}
   uint8_t  MR51_B0;          // Byte offset 0x8f, CSR Addr 0x54047, Direction=In
                              // Value to be programmed in DRAM Mode Register 51 {Channel B, Rank 0}
   uint8_t  MR21_B1;          // Byte offset 0x90, CSR Addr 0x54048, Direction=In
                              // Value to be programmed in DRAM Mode Register 21 {Channel B, Rank 1}
   uint8_t  MR51_B1;          // Byte offset 0x91, CSR Addr 0x54048, Direction=In
                              // Value to be programmed in DRAM Mode Register 51 {Channel B. Rank 1}
   uint8_t  LP4XMode;         // Byte offset 0x92, CSR Addr 0x54049, Direction=In
                              // Must be Set if DRAM supports LP4X
   uint8_t  Disable2D;        // Byte offset 0x93, CSR Addr 0x54049, Direction=In
                              // Set to disable 2D training
   uint8_t  VrefSamples;      // Byte offset 0x94, CSR Addr 0x5404a, Direction=In
                              // Number of vrefs to scan 
                              // 0 =  scan default vref
   uint8_t  ALT_RL;           // Byte offset 0x95, CSR Addr 0x5404a, Direction=In
                              // This is the alternate Read Latency for DBI off
   uint8_t  MAIN_RL;          // Byte offset 0x96, CSR Addr 0x5404b, Direction=In
                              // This is the main RL calculated by phyinit
   uint8_t  RdWrPatternA;     // Byte offset 0x97, CSR Addr 0x5404b, Direction=In
                              // Lower-byte read and write pattern for training 
                              // When set to 0 uses default patterns
   uint8_t  RdWrPatternB;     // Byte offset 0x98, CSR Addr 0x5404c, Direction=In
                              // Upper-byte read and write pattern for training 
                              // When set to 0 uses default patterns
   uint8_t  RdWrInvertA;      // Byte offset 0x99, CSR Addr 0x5404c, Direction=In
                              // Lower-byte per bit  invert for read and write pattern for training 
                              // When RdWrPatternA and RdWrPatternB = 0 this is unused
   uint8_t  RdWrInvertB;      // Byte offset 0x9a, CSR Addr 0x5404d, Direction=In
                              // Upper-byte per bit invert read and write pattern for training 
                              // When RdWrPatternA and RdWrPatternB = 0 this is unused
   uint8_t  Reserved9B;       // Byte offset 0x9b, CSR Addr 0x5404d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved9C;       // Byte offset 0x9c, CSR Addr 0x5404e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved9D;       // Byte offset 0x9d, CSR Addr 0x5404e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved9E;       // Byte offset 0x9e, CSR Addr 0x5404f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved9F;       // Byte offset 0x9f, CSR Addr 0x5404f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA0;       // Byte offset 0xa0, CSR Addr 0x54050, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA1;       // Byte offset 0xa1, CSR Addr 0x54050, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA2;       // Byte offset 0xa2, CSR Addr 0x54051, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA3;       // Byte offset 0xa3, CSR Addr 0x54051, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA4;       // Byte offset 0xa4, CSR Addr 0x54052, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA5;       // Byte offset 0xa5, CSR Addr 0x54052, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA6;       // Byte offset 0xa6, CSR Addr 0x54053, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA7;       // Byte offset 0xa7, CSR Addr 0x54053, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA8;       // Byte offset 0xa8, CSR Addr 0x54054, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedA9;       // Byte offset 0xa9, CSR Addr 0x54054, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedAA;       // Byte offset 0xaa, CSR Addr 0x54055, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedAB;       // Byte offset 0xab, CSR Addr 0x54055, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedAC;       // Byte offset 0xac, CSR Addr 0x54056, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedAD;       // Byte offset 0xad, CSR Addr 0x54056, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedAE;       // Byte offset 0xae, CSR Addr 0x54057, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedAF;       // Byte offset 0xaf, CSR Addr 0x54057, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB0;       // Byte offset 0xb0, CSR Addr 0x54058, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB1;       // Byte offset 0xb1, CSR Addr 0x54058, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB2;       // Byte offset 0xb2, CSR Addr 0x54059, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB3;       // Byte offset 0xb3, CSR Addr 0x54059, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB4;       // Byte offset 0xb4, CSR Addr 0x5405a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB5;       // Byte offset 0xb5, CSR Addr 0x5405a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB6;       // Byte offset 0xb6, CSR Addr 0x5405b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB7;       // Byte offset 0xb7, CSR Addr 0x5405b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB8;       // Byte offset 0xb8, CSR Addr 0x5405c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedB9;       // Byte offset 0xb9, CSR Addr 0x5405c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedBA;       // Byte offset 0xba, CSR Addr 0x5405d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedBB;       // Byte offset 0xbb, CSR Addr 0x5405d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedBC;       // Byte offset 0xbc, CSR Addr 0x5405e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedBD;       // Byte offset 0xbd, CSR Addr 0x5405e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedBE;       // Byte offset 0xbe, CSR Addr 0x5405f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedBF;       // Byte offset 0xbf, CSR Addr 0x5405f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC0;       // Byte offset 0xc0, CSR Addr 0x54060, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC1;       // Byte offset 0xc1, CSR Addr 0x54060, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC2;       // Byte offset 0xc2, CSR Addr 0x54061, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC3;       // Byte offset 0xc3, CSR Addr 0x54061, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC4;       // Byte offset 0xc4, CSR Addr 0x54062, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC5;       // Byte offset 0xc5, CSR Addr 0x54062, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC6;       // Byte offset 0xc6, CSR Addr 0x54063, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC7;       // Byte offset 0xc7, CSR Addr 0x54063, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC8;       // Byte offset 0xc8, CSR Addr 0x54064, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedC9;       // Byte offset 0xc9, CSR Addr 0x54064, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedCA;       // Byte offset 0xca, CSR Addr 0x54065, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedCB;       // Byte offset 0xcb, CSR Addr 0x54065, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedCC;       // Byte offset 0xcc, CSR Addr 0x54066, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedCD;       // Byte offset 0xcd, CSR Addr 0x54066, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedCE;       // Byte offset 0xce, CSR Addr 0x54067, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedCF;       // Byte offset 0xcf, CSR Addr 0x54067, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD0;       // Byte offset 0xd0, CSR Addr 0x54068, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD1;       // Byte offset 0xd1, CSR Addr 0x54068, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD2;       // Byte offset 0xd2, CSR Addr 0x54069, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD3;       // Byte offset 0xd3, CSR Addr 0x54069, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD4;       // Byte offset 0xd4, CSR Addr 0x5406a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD5;       // Byte offset 0xd5, CSR Addr 0x5406a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD6;       // Byte offset 0xd6, CSR Addr 0x5406b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD7;       // Byte offset 0xd7, CSR Addr 0x5406b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD8;       // Byte offset 0xd8, CSR Addr 0x5406c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedD9;       // Byte offset 0xd9, CSR Addr 0x5406c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedDA;       // Byte offset 0xda, CSR Addr 0x5406d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedDB;       // Byte offset 0xdb, CSR Addr 0x5406d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedDC;       // Byte offset 0xdc, CSR Addr 0x5406e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedDD;       // Byte offset 0xdd, CSR Addr 0x5406e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedDE;       // Byte offset 0xde, CSR Addr 0x5406f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedDF;       // Byte offset 0xdf, CSR Addr 0x5406f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE0;       // Byte offset 0xe0, CSR Addr 0x54070, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE1;       // Byte offset 0xe1, CSR Addr 0x54070, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE2;       // Byte offset 0xe2, CSR Addr 0x54071, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE3;       // Byte offset 0xe3, CSR Addr 0x54071, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE4;       // Byte offset 0xe4, CSR Addr 0x54072, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE5;       // Byte offset 0xe5, CSR Addr 0x54072, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE6;       // Byte offset 0xe6, CSR Addr 0x54073, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE7;       // Byte offset 0xe7, CSR Addr 0x54073, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE8;       // Byte offset 0xe8, CSR Addr 0x54074, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedE9;       // Byte offset 0xe9, CSR Addr 0x54074, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedEA;       // Byte offset 0xea, CSR Addr 0x54075, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedEB;       // Byte offset 0xeb, CSR Addr 0x54075, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedEC;       // Byte offset 0xec, CSR Addr 0x54076, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedED;       // Byte offset 0xed, CSR Addr 0x54076, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedEE;       // Byte offset 0xee, CSR Addr 0x54077, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedEF;       // Byte offset 0xef, CSR Addr 0x54077, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF0;       // Byte offset 0xf0, CSR Addr 0x54078, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF1;       // Byte offset 0xf1, CSR Addr 0x54078, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF2;       // Byte offset 0xf2, CSR Addr 0x54079, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF3;       // Byte offset 0xf3, CSR Addr 0x54079, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF4;       // Byte offset 0xf4, CSR Addr 0x5407a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF5;       // Byte offset 0xf5, CSR Addr 0x5407a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF6;       // Byte offset 0xf6, CSR Addr 0x5407b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF7;       // Byte offset 0xf7, CSR Addr 0x5407b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF8;       // Byte offset 0xf8, CSR Addr 0x5407c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedF9;       // Byte offset 0xf9, CSR Addr 0x5407c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedFA;       // Byte offset 0xfa, CSR Addr 0x5407d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedFB;       // Byte offset 0xfb, CSR Addr 0x5407d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedFC;       // Byte offset 0xfc, CSR Addr 0x5407e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedFD;       // Byte offset 0xfd, CSR Addr 0x5407e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedFE;       // Byte offset 0xfe, CSR Addr 0x5407f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  ReservedFF;       // Byte offset 0xff, CSR Addr 0x5407f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved100;      // Byte offset 0x100, CSR Addr 0x54080, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved101;      // Byte offset 0x101, CSR Addr 0x54080, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved102;      // Byte offset 0x102, CSR Addr 0x54081, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved103;      // Byte offset 0x103, CSR Addr 0x54081, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved104;      // Byte offset 0x104, CSR Addr 0x54082, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved105;      // Byte offset 0x105, CSR Addr 0x54082, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved106;      // Byte offset 0x106, CSR Addr 0x54083, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved107;      // Byte offset 0x107, CSR Addr 0x54083, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved108;      // Byte offset 0x108, CSR Addr 0x54084, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved109;      // Byte offset 0x109, CSR Addr 0x54084, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved10A;      // Byte offset 0x10a, CSR Addr 0x54085, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved10B;      // Byte offset 0x10b, CSR Addr 0x54085, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved10C;      // Byte offset 0x10c, CSR Addr 0x54086, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved10D;      // Byte offset 0x10d, CSR Addr 0x54086, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved10E;      // Byte offset 0x10e, CSR Addr 0x54087, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved10F;      // Byte offset 0x10f, CSR Addr 0x54087, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved110;      // Byte offset 0x110, CSR Addr 0x54088, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved111;      // Byte offset 0x111, CSR Addr 0x54088, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved112;      // Byte offset 0x112, CSR Addr 0x54089, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved113;      // Byte offset 0x113, CSR Addr 0x54089, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved114;      // Byte offset 0x114, CSR Addr 0x5408a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved115;      // Byte offset 0x115, CSR Addr 0x5408a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved116;      // Byte offset 0x116, CSR Addr 0x5408b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved117;      // Byte offset 0x117, CSR Addr 0x5408b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved118;      // Byte offset 0x118, CSR Addr 0x5408c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved119;      // Byte offset 0x119, CSR Addr 0x5408c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved11A;      // Byte offset 0x11a, CSR Addr 0x5408d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved11B;      // Byte offset 0x11b, CSR Addr 0x5408d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved11C;      // Byte offset 0x11c, CSR Addr 0x5408e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved11D;      // Byte offset 0x11d, CSR Addr 0x5408e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved11E;      // Byte offset 0x11e, CSR Addr 0x5408f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved11F;      // Byte offset 0x11f, CSR Addr 0x5408f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved120;      // Byte offset 0x120, CSR Addr 0x54090, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved121;      // Byte offset 0x121, CSR Addr 0x54090, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved122;      // Byte offset 0x122, CSR Addr 0x54091, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved123;      // Byte offset 0x123, CSR Addr 0x54091, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved124;      // Byte offset 0x124, CSR Addr 0x54092, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved125;      // Byte offset 0x125, CSR Addr 0x54092, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved126;      // Byte offset 0x126, CSR Addr 0x54093, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved127;      // Byte offset 0x127, CSR Addr 0x54093, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved128;      // Byte offset 0x128, CSR Addr 0x54094, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved129;      // Byte offset 0x129, CSR Addr 0x54094, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved12A;      // Byte offset 0x12a, CSR Addr 0x54095, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved12B;      // Byte offset 0x12b, CSR Addr 0x54095, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved12C;      // Byte offset 0x12c, CSR Addr 0x54096, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved12D;      // Byte offset 0x12d, CSR Addr 0x54096, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved12E;      // Byte offset 0x12e, CSR Addr 0x54097, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved12F;      // Byte offset 0x12f, CSR Addr 0x54097, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved130;      // Byte offset 0x130, CSR Addr 0x54098, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved131;      // Byte offset 0x131, CSR Addr 0x54098, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved132;      // Byte offset 0x132, CSR Addr 0x54099, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved133;      // Byte offset 0x133, CSR Addr 0x54099, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved134;      // Byte offset 0x134, CSR Addr 0x5409a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved135;      // Byte offset 0x135, CSR Addr 0x5409a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved136;      // Byte offset 0x136, CSR Addr 0x5409b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved137;      // Byte offset 0x137, CSR Addr 0x5409b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved138;      // Byte offset 0x138, CSR Addr 0x5409c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved139;      // Byte offset 0x139, CSR Addr 0x5409c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved13A;      // Byte offset 0x13a, CSR Addr 0x5409d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved13B;      // Byte offset 0x13b, CSR Addr 0x5409d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved13C;      // Byte offset 0x13c, CSR Addr 0x5409e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved13D;      // Byte offset 0x13d, CSR Addr 0x5409e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved13E;      // Byte offset 0x13e, CSR Addr 0x5409f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved13F;      // Byte offset 0x13f, CSR Addr 0x5409f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved140;      // Byte offset 0x140, CSR Addr 0x540a0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved141;      // Byte offset 0x141, CSR Addr 0x540a0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved142;      // Byte offset 0x142, CSR Addr 0x540a1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved143;      // Byte offset 0x143, CSR Addr 0x540a1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved144;      // Byte offset 0x144, CSR Addr 0x540a2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved145;      // Byte offset 0x145, CSR Addr 0x540a2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved146;      // Byte offset 0x146, CSR Addr 0x540a3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved147;      // Byte offset 0x147, CSR Addr 0x540a3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved148;      // Byte offset 0x148, CSR Addr 0x540a4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved149;      // Byte offset 0x149, CSR Addr 0x540a4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved14A;      // Byte offset 0x14a, CSR Addr 0x540a5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved14B;      // Byte offset 0x14b, CSR Addr 0x540a5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved14C;      // Byte offset 0x14c, CSR Addr 0x540a6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved14D;      // Byte offset 0x14d, CSR Addr 0x540a6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved14E;      // Byte offset 0x14e, CSR Addr 0x540a7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved14F;      // Byte offset 0x14f, CSR Addr 0x540a7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved150;      // Byte offset 0x150, CSR Addr 0x540a8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved151;      // Byte offset 0x151, CSR Addr 0x540a8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved152;      // Byte offset 0x152, CSR Addr 0x540a9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved153;      // Byte offset 0x153, CSR Addr 0x540a9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved154;      // Byte offset 0x154, CSR Addr 0x540aa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved155;      // Byte offset 0x155, CSR Addr 0x540aa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved156;      // Byte offset 0x156, CSR Addr 0x540ab, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved157;      // Byte offset 0x157, CSR Addr 0x540ab, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved158;      // Byte offset 0x158, CSR Addr 0x540ac, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved159;      // Byte offset 0x159, CSR Addr 0x540ac, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved15A;      // Byte offset 0x15a, CSR Addr 0x540ad, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved15B;      // Byte offset 0x15b, CSR Addr 0x540ad, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved15C;      // Byte offset 0x15c, CSR Addr 0x540ae, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved15D;      // Byte offset 0x15d, CSR Addr 0x540ae, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved15E;      // Byte offset 0x15e, CSR Addr 0x540af, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved15F;      // Byte offset 0x15f, CSR Addr 0x540af, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved160;      // Byte offset 0x160, CSR Addr 0x540b0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved161;      // Byte offset 0x161, CSR Addr 0x540b0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved162;      // Byte offset 0x162, CSR Addr 0x540b1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved163;      // Byte offset 0x163, CSR Addr 0x540b1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved164;      // Byte offset 0x164, CSR Addr 0x540b2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved165;      // Byte offset 0x165, CSR Addr 0x540b2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved166;      // Byte offset 0x166, CSR Addr 0x540b3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved167;      // Byte offset 0x167, CSR Addr 0x540b3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved168;      // Byte offset 0x168, CSR Addr 0x540b4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved169;      // Byte offset 0x169, CSR Addr 0x540b4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved16A;      // Byte offset 0x16a, CSR Addr 0x540b5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved16B;      // Byte offset 0x16b, CSR Addr 0x540b5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved16C;      // Byte offset 0x16c, CSR Addr 0x540b6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved16D;      // Byte offset 0x16d, CSR Addr 0x540b6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved16E;      // Byte offset 0x16e, CSR Addr 0x540b7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved16F;      // Byte offset 0x16f, CSR Addr 0x540b7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved170;      // Byte offset 0x170, CSR Addr 0x540b8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved171;      // Byte offset 0x171, CSR Addr 0x540b8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved172;      // Byte offset 0x172, CSR Addr 0x540b9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved173;      // Byte offset 0x173, CSR Addr 0x540b9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved174;      // Byte offset 0x174, CSR Addr 0x540ba, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved175;      // Byte offset 0x175, CSR Addr 0x540ba, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved176;      // Byte offset 0x176, CSR Addr 0x540bb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved177;      // Byte offset 0x177, CSR Addr 0x540bb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved178;      // Byte offset 0x178, CSR Addr 0x540bc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved179;      // Byte offset 0x179, CSR Addr 0x540bc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved17A;      // Byte offset 0x17a, CSR Addr 0x540bd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved17B;      // Byte offset 0x17b, CSR Addr 0x540bd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved17C;      // Byte offset 0x17c, CSR Addr 0x540be, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved17D;      // Byte offset 0x17d, CSR Addr 0x540be, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved17E;      // Byte offset 0x17e, CSR Addr 0x540bf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved17F;      // Byte offset 0x17f, CSR Addr 0x540bf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved180;      // Byte offset 0x180, CSR Addr 0x540c0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved181;      // Byte offset 0x181, CSR Addr 0x540c0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved182;      // Byte offset 0x182, CSR Addr 0x540c1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved183;      // Byte offset 0x183, CSR Addr 0x540c1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved184;      // Byte offset 0x184, CSR Addr 0x540c2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved185;      // Byte offset 0x185, CSR Addr 0x540c2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved186;      // Byte offset 0x186, CSR Addr 0x540c3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved187;      // Byte offset 0x187, CSR Addr 0x540c3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved188;      // Byte offset 0x188, CSR Addr 0x540c4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved189;      // Byte offset 0x189, CSR Addr 0x540c4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved18A;      // Byte offset 0x18a, CSR Addr 0x540c5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved18B;      // Byte offset 0x18b, CSR Addr 0x540c5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved18C;      // Byte offset 0x18c, CSR Addr 0x540c6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved18D;      // Byte offset 0x18d, CSR Addr 0x540c6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved18E;      // Byte offset 0x18e, CSR Addr 0x540c7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved18F;      // Byte offset 0x18f, CSR Addr 0x540c7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved190;      // Byte offset 0x190, CSR Addr 0x540c8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved191;      // Byte offset 0x191, CSR Addr 0x540c8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved192;      // Byte offset 0x192, CSR Addr 0x540c9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved193;      // Byte offset 0x193, CSR Addr 0x540c9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved194;      // Byte offset 0x194, CSR Addr 0x540ca, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved195;      // Byte offset 0x195, CSR Addr 0x540ca, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved196;      // Byte offset 0x196, CSR Addr 0x540cb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved197;      // Byte offset 0x197, CSR Addr 0x540cb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved198;      // Byte offset 0x198, CSR Addr 0x540cc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved199;      // Byte offset 0x199, CSR Addr 0x540cc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved19A;      // Byte offset 0x19a, CSR Addr 0x540cd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved19B;      // Byte offset 0x19b, CSR Addr 0x540cd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved19C;      // Byte offset 0x19c, CSR Addr 0x540ce, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved19D;      // Byte offset 0x19d, CSR Addr 0x540ce, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved19E;      // Byte offset 0x19e, CSR Addr 0x540cf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved19F;      // Byte offset 0x19f, CSR Addr 0x540cf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A0;      // Byte offset 0x1a0, CSR Addr 0x540d0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A1;      // Byte offset 0x1a1, CSR Addr 0x540d0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A2;      // Byte offset 0x1a2, CSR Addr 0x540d1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A3;      // Byte offset 0x1a3, CSR Addr 0x540d1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A4;      // Byte offset 0x1a4, CSR Addr 0x540d2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A5;      // Byte offset 0x1a5, CSR Addr 0x540d2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A6;      // Byte offset 0x1a6, CSR Addr 0x540d3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A7;      // Byte offset 0x1a7, CSR Addr 0x540d3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A8;      // Byte offset 0x1a8, CSR Addr 0x540d4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1A9;      // Byte offset 0x1a9, CSR Addr 0x540d4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1AA;      // Byte offset 0x1aa, CSR Addr 0x540d5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1AB;      // Byte offset 0x1ab, CSR Addr 0x540d5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1AC;      // Byte offset 0x1ac, CSR Addr 0x540d6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1AD;      // Byte offset 0x1ad, CSR Addr 0x540d6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1AE;      // Byte offset 0x1ae, CSR Addr 0x540d7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1AF;      // Byte offset 0x1af, CSR Addr 0x540d7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B0;      // Byte offset 0x1b0, CSR Addr 0x540d8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B1;      // Byte offset 0x1b1, CSR Addr 0x540d8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B2;      // Byte offset 0x1b2, CSR Addr 0x540d9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B3;      // Byte offset 0x1b3, CSR Addr 0x540d9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B4;      // Byte offset 0x1b4, CSR Addr 0x540da, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B5;      // Byte offset 0x1b5, CSR Addr 0x540da, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B6;      // Byte offset 0x1b6, CSR Addr 0x540db, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B7;      // Byte offset 0x1b7, CSR Addr 0x540db, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B8;      // Byte offset 0x1b8, CSR Addr 0x540dc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1B9;      // Byte offset 0x1b9, CSR Addr 0x540dc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1BA;      // Byte offset 0x1ba, CSR Addr 0x540dd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1BB;      // Byte offset 0x1bb, CSR Addr 0x540dd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1BC;      // Byte offset 0x1bc, CSR Addr 0x540de, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1BD;      // Byte offset 0x1bd, CSR Addr 0x540de, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1BE;      // Byte offset 0x1be, CSR Addr 0x540df, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1BF;      // Byte offset 0x1bf, CSR Addr 0x540df, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C0;      // Byte offset 0x1c0, CSR Addr 0x540e0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C1;      // Byte offset 0x1c1, CSR Addr 0x540e0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C2;      // Byte offset 0x1c2, CSR Addr 0x540e1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C3;      // Byte offset 0x1c3, CSR Addr 0x540e1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C4;      // Byte offset 0x1c4, CSR Addr 0x540e2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C5;      // Byte offset 0x1c5, CSR Addr 0x540e2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C6;      // Byte offset 0x1c6, CSR Addr 0x540e3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C7;      // Byte offset 0x1c7, CSR Addr 0x540e3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C8;      // Byte offset 0x1c8, CSR Addr 0x540e4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1C9;      // Byte offset 0x1c9, CSR Addr 0x540e4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1CA;      // Byte offset 0x1ca, CSR Addr 0x540e5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1CB;      // Byte offset 0x1cb, CSR Addr 0x540e5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1CC;      // Byte offset 0x1cc, CSR Addr 0x540e6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1CD;      // Byte offset 0x1cd, CSR Addr 0x540e6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1CE;      // Byte offset 0x1ce, CSR Addr 0x540e7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1CF;      // Byte offset 0x1cf, CSR Addr 0x540e7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D0;      // Byte offset 0x1d0, CSR Addr 0x540e8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D1;      // Byte offset 0x1d1, CSR Addr 0x540e8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D2;      // Byte offset 0x1d2, CSR Addr 0x540e9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D3;      // Byte offset 0x1d3, CSR Addr 0x540e9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D4;      // Byte offset 0x1d4, CSR Addr 0x540ea, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D5;      // Byte offset 0x1d5, CSR Addr 0x540ea, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D6;      // Byte offset 0x1d6, CSR Addr 0x540eb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D7;      // Byte offset 0x1d7, CSR Addr 0x540eb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D8;      // Byte offset 0x1d8, CSR Addr 0x540ec, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1D9;      // Byte offset 0x1d9, CSR Addr 0x540ec, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1DA;      // Byte offset 0x1da, CSR Addr 0x540ed, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1DB;      // Byte offset 0x1db, CSR Addr 0x540ed, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1DC;      // Byte offset 0x1dc, CSR Addr 0x540ee, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1DD;      // Byte offset 0x1dd, CSR Addr 0x540ee, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1DE;      // Byte offset 0x1de, CSR Addr 0x540ef, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1DF;      // Byte offset 0x1df, CSR Addr 0x540ef, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E0;      // Byte offset 0x1e0, CSR Addr 0x540f0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E1;      // Byte offset 0x1e1, CSR Addr 0x540f0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E2;      // Byte offset 0x1e2, CSR Addr 0x540f1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E3;      // Byte offset 0x1e3, CSR Addr 0x540f1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E4;      // Byte offset 0x1e4, CSR Addr 0x540f2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E5;      // Byte offset 0x1e5, CSR Addr 0x540f2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E6;      // Byte offset 0x1e6, CSR Addr 0x540f3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E7;      // Byte offset 0x1e7, CSR Addr 0x540f3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E8;      // Byte offset 0x1e8, CSR Addr 0x540f4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1E9;      // Byte offset 0x1e9, CSR Addr 0x540f4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1EA;      // Byte offset 0x1ea, CSR Addr 0x540f5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1EB;      // Byte offset 0x1eb, CSR Addr 0x540f5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1EC;      // Byte offset 0x1ec, CSR Addr 0x540f6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1ED;      // Byte offset 0x1ed, CSR Addr 0x540f6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1EE;      // Byte offset 0x1ee, CSR Addr 0x540f7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1EF;      // Byte offset 0x1ef, CSR Addr 0x540f7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F0;      // Byte offset 0x1f0, CSR Addr 0x540f8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F1;      // Byte offset 0x1f1, CSR Addr 0x540f8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F2;      // Byte offset 0x1f2, CSR Addr 0x540f9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F3;      // Byte offset 0x1f3, CSR Addr 0x540f9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F4;      // Byte offset 0x1f4, CSR Addr 0x540fa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F5;      // Byte offset 0x1f5, CSR Addr 0x540fa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F6;      // Byte offset 0x1f6, CSR Addr 0x540fb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F7;      // Byte offset 0x1f7, CSR Addr 0x540fb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F8;      // Byte offset 0x1f8, CSR Addr 0x540fc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1F9;      // Byte offset 0x1f9, CSR Addr 0x540fc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1FA;      // Byte offset 0x1fa, CSR Addr 0x540fd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1FB;      // Byte offset 0x1fb, CSR Addr 0x540fd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1FC;      // Byte offset 0x1fc, CSR Addr 0x540fe, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1FD;      // Byte offset 0x1fd, CSR Addr 0x540fe, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1FE;      // Byte offset 0x1fe, CSR Addr 0x540ff, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved1FF;      // Byte offset 0x1ff, CSR Addr 0x540ff, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved200;      // Byte offset 0x200, CSR Addr 0x54100, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved201;      // Byte offset 0x201, CSR Addr 0x54100, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved202;      // Byte offset 0x202, CSR Addr 0x54101, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved203;      // Byte offset 0x203, CSR Addr 0x54101, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved204;      // Byte offset 0x204, CSR Addr 0x54102, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved205;      // Byte offset 0x205, CSR Addr 0x54102, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved206;      // Byte offset 0x206, CSR Addr 0x54103, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved207;      // Byte offset 0x207, CSR Addr 0x54103, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved208;      // Byte offset 0x208, CSR Addr 0x54104, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved209;      // Byte offset 0x209, CSR Addr 0x54104, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20A;      // Byte offset 0x20a, CSR Addr 0x54105, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20B;      // Byte offset 0x20b, CSR Addr 0x54105, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20C;      // Byte offset 0x20c, CSR Addr 0x54106, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20D;      // Byte offset 0x20d, CSR Addr 0x54106, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20E;      // Byte offset 0x20e, CSR Addr 0x54107, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved20F;      // Byte offset 0x20f, CSR Addr 0x54107, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved210;      // Byte offset 0x210, CSR Addr 0x54108, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved211;      // Byte offset 0x211, CSR Addr 0x54108, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved212;      // Byte offset 0x212, CSR Addr 0x54109, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved213;      // Byte offset 0x213, CSR Addr 0x54109, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved214;      // Byte offset 0x214, CSR Addr 0x5410a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved215;      // Byte offset 0x215, CSR Addr 0x5410a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved216;      // Byte offset 0x216, CSR Addr 0x5410b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved217;      // Byte offset 0x217, CSR Addr 0x5410b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved218;      // Byte offset 0x218, CSR Addr 0x5410c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved219;      // Byte offset 0x219, CSR Addr 0x5410c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved21A;      // Byte offset 0x21a, CSR Addr 0x5410d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved21B;      // Byte offset 0x21b, CSR Addr 0x5410d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved21C;      // Byte offset 0x21c, CSR Addr 0x5410e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved21D;      // Byte offset 0x21d, CSR Addr 0x5410e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved21E;      // Byte offset 0x21e, CSR Addr 0x5410f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved21F;      // Byte offset 0x21f, CSR Addr 0x5410f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved220;      // Byte offset 0x220, CSR Addr 0x54110, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved221;      // Byte offset 0x221, CSR Addr 0x54110, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved222;      // Byte offset 0x222, CSR Addr 0x54111, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved223;      // Byte offset 0x223, CSR Addr 0x54111, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved224;      // Byte offset 0x224, CSR Addr 0x54112, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved225;      // Byte offset 0x225, CSR Addr 0x54112, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved226;      // Byte offset 0x226, CSR Addr 0x54113, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved227;      // Byte offset 0x227, CSR Addr 0x54113, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved228;      // Byte offset 0x228, CSR Addr 0x54114, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved229;      // Byte offset 0x229, CSR Addr 0x54114, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved22A;      // Byte offset 0x22a, CSR Addr 0x54115, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved22B;      // Byte offset 0x22b, CSR Addr 0x54115, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved22C;      // Byte offset 0x22c, CSR Addr 0x54116, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved22D;      // Byte offset 0x22d, CSR Addr 0x54116, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved22E;      // Byte offset 0x22e, CSR Addr 0x54117, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved22F;      // Byte offset 0x22f, CSR Addr 0x54117, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved230;      // Byte offset 0x230, CSR Addr 0x54118, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved231;      // Byte offset 0x231, CSR Addr 0x54118, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved232;      // Byte offset 0x232, CSR Addr 0x54119, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved233;      // Byte offset 0x233, CSR Addr 0x54119, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved234;      // Byte offset 0x234, CSR Addr 0x5411a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved235;      // Byte offset 0x235, CSR Addr 0x5411a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved236;      // Byte offset 0x236, CSR Addr 0x5411b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved237;      // Byte offset 0x237, CSR Addr 0x5411b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved238;      // Byte offset 0x238, CSR Addr 0x5411c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved239;      // Byte offset 0x239, CSR Addr 0x5411c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved23A;      // Byte offset 0x23a, CSR Addr 0x5411d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved23B;      // Byte offset 0x23b, CSR Addr 0x5411d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved23C;      // Byte offset 0x23c, CSR Addr 0x5411e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved23D;      // Byte offset 0x23d, CSR Addr 0x5411e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved23E;      // Byte offset 0x23e, CSR Addr 0x5411f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved23F;      // Byte offset 0x23f, CSR Addr 0x5411f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved240;      // Byte offset 0x240, CSR Addr 0x54120, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved241;      // Byte offset 0x241, CSR Addr 0x54120, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved242;      // Byte offset 0x242, CSR Addr 0x54121, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved243;      // Byte offset 0x243, CSR Addr 0x54121, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved244;      // Byte offset 0x244, CSR Addr 0x54122, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved245;      // Byte offset 0x245, CSR Addr 0x54122, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved246;      // Byte offset 0x246, CSR Addr 0x54123, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved247;      // Byte offset 0x247, CSR Addr 0x54123, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved248;      // Byte offset 0x248, CSR Addr 0x54124, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved249;      // Byte offset 0x249, CSR Addr 0x54124, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved24A;      // Byte offset 0x24a, CSR Addr 0x54125, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved24B;      // Byte offset 0x24b, CSR Addr 0x54125, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved24C;      // Byte offset 0x24c, CSR Addr 0x54126, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved24D;      // Byte offset 0x24d, CSR Addr 0x54126, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved24E;      // Byte offset 0x24e, CSR Addr 0x54127, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved24F;      // Byte offset 0x24f, CSR Addr 0x54127, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved250;      // Byte offset 0x250, CSR Addr 0x54128, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved251;      // Byte offset 0x251, CSR Addr 0x54128, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved252;      // Byte offset 0x252, CSR Addr 0x54129, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved253;      // Byte offset 0x253, CSR Addr 0x54129, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved254;      // Byte offset 0x254, CSR Addr 0x5412a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved255;      // Byte offset 0x255, CSR Addr 0x5412a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved256;      // Byte offset 0x256, CSR Addr 0x5412b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved257;      // Byte offset 0x257, CSR Addr 0x5412b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved258;      // Byte offset 0x258, CSR Addr 0x5412c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved259;      // Byte offset 0x259, CSR Addr 0x5412c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved25A;      // Byte offset 0x25a, CSR Addr 0x5412d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved25B;      // Byte offset 0x25b, CSR Addr 0x5412d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved25C;      // Byte offset 0x25c, CSR Addr 0x5412e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved25D;      // Byte offset 0x25d, CSR Addr 0x5412e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved25E;      // Byte offset 0x25e, CSR Addr 0x5412f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved25F;      // Byte offset 0x25f, CSR Addr 0x5412f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved260;      // Byte offset 0x260, CSR Addr 0x54130, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved261;      // Byte offset 0x261, CSR Addr 0x54130, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved262;      // Byte offset 0x262, CSR Addr 0x54131, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved263;      // Byte offset 0x263, CSR Addr 0x54131, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved264;      // Byte offset 0x264, CSR Addr 0x54132, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved265;      // Byte offset 0x265, CSR Addr 0x54132, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved266;      // Byte offset 0x266, CSR Addr 0x54133, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved267;      // Byte offset 0x267, CSR Addr 0x54133, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved268;      // Byte offset 0x268, CSR Addr 0x54134, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved269;      // Byte offset 0x269, CSR Addr 0x54134, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved26A;      // Byte offset 0x26a, CSR Addr 0x54135, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved26B;      // Byte offset 0x26b, CSR Addr 0x54135, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved26C;      // Byte offset 0x26c, CSR Addr 0x54136, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved26D;      // Byte offset 0x26d, CSR Addr 0x54136, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved26E;      // Byte offset 0x26e, CSR Addr 0x54137, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved26F;      // Byte offset 0x26f, CSR Addr 0x54137, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved270;      // Byte offset 0x270, CSR Addr 0x54138, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved271;      // Byte offset 0x271, CSR Addr 0x54138, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved272;      // Byte offset 0x272, CSR Addr 0x54139, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved273;      // Byte offset 0x273, CSR Addr 0x54139, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved274;      // Byte offset 0x274, CSR Addr 0x5413a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved275;      // Byte offset 0x275, CSR Addr 0x5413a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved276;      // Byte offset 0x276, CSR Addr 0x5413b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved277;      // Byte offset 0x277, CSR Addr 0x5413b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved278;      // Byte offset 0x278, CSR Addr 0x5413c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved279;      // Byte offset 0x279, CSR Addr 0x5413c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved27A;      // Byte offset 0x27a, CSR Addr 0x5413d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved27B;      // Byte offset 0x27b, CSR Addr 0x5413d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved27C;      // Byte offset 0x27c, CSR Addr 0x5413e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved27D;      // Byte offset 0x27d, CSR Addr 0x5413e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved27E;      // Byte offset 0x27e, CSR Addr 0x5413f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved27F;      // Byte offset 0x27f, CSR Addr 0x5413f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved280;      // Byte offset 0x280, CSR Addr 0x54140, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved281;      // Byte offset 0x281, CSR Addr 0x54140, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved282;      // Byte offset 0x282, CSR Addr 0x54141, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved283;      // Byte offset 0x283, CSR Addr 0x54141, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved284;      // Byte offset 0x284, CSR Addr 0x54142, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved285;      // Byte offset 0x285, CSR Addr 0x54142, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved286;      // Byte offset 0x286, CSR Addr 0x54143, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved287;      // Byte offset 0x287, CSR Addr 0x54143, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved288;      // Byte offset 0x288, CSR Addr 0x54144, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved289;      // Byte offset 0x289, CSR Addr 0x54144, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved28A;      // Byte offset 0x28a, CSR Addr 0x54145, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved28B;      // Byte offset 0x28b, CSR Addr 0x54145, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved28C;      // Byte offset 0x28c, CSR Addr 0x54146, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved28D;      // Byte offset 0x28d, CSR Addr 0x54146, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved28E;      // Byte offset 0x28e, CSR Addr 0x54147, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved28F;      // Byte offset 0x28f, CSR Addr 0x54147, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved290;      // Byte offset 0x290, CSR Addr 0x54148, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved291;      // Byte offset 0x291, CSR Addr 0x54148, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved292;      // Byte offset 0x292, CSR Addr 0x54149, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved293;      // Byte offset 0x293, CSR Addr 0x54149, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved294;      // Byte offset 0x294, CSR Addr 0x5414a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved295;      // Byte offset 0x295, CSR Addr 0x5414a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved296;      // Byte offset 0x296, CSR Addr 0x5414b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved297;      // Byte offset 0x297, CSR Addr 0x5414b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved298;      // Byte offset 0x298, CSR Addr 0x5414c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved299;      // Byte offset 0x299, CSR Addr 0x5414c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved29A;      // Byte offset 0x29a, CSR Addr 0x5414d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved29B;      // Byte offset 0x29b, CSR Addr 0x5414d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved29C;      // Byte offset 0x29c, CSR Addr 0x5414e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved29D;      // Byte offset 0x29d, CSR Addr 0x5414e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved29E;      // Byte offset 0x29e, CSR Addr 0x5414f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved29F;      // Byte offset 0x29f, CSR Addr 0x5414f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A0;      // Byte offset 0x2a0, CSR Addr 0x54150, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A1;      // Byte offset 0x2a1, CSR Addr 0x54150, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A2;      // Byte offset 0x2a2, CSR Addr 0x54151, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A3;      // Byte offset 0x2a3, CSR Addr 0x54151, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A4;      // Byte offset 0x2a4, CSR Addr 0x54152, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A5;      // Byte offset 0x2a5, CSR Addr 0x54152, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A6;      // Byte offset 0x2a6, CSR Addr 0x54153, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A7;      // Byte offset 0x2a7, CSR Addr 0x54153, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A8;      // Byte offset 0x2a8, CSR Addr 0x54154, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2A9;      // Byte offset 0x2a9, CSR Addr 0x54154, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2AA;      // Byte offset 0x2aa, CSR Addr 0x54155, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2AB;      // Byte offset 0x2ab, CSR Addr 0x54155, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2AC;      // Byte offset 0x2ac, CSR Addr 0x54156, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2AD;      // Byte offset 0x2ad, CSR Addr 0x54156, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2AE;      // Byte offset 0x2ae, CSR Addr 0x54157, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2AF;      // Byte offset 0x2af, CSR Addr 0x54157, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B0;      // Byte offset 0x2b0, CSR Addr 0x54158, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B1;      // Byte offset 0x2b1, CSR Addr 0x54158, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B2;      // Byte offset 0x2b2, CSR Addr 0x54159, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B3;      // Byte offset 0x2b3, CSR Addr 0x54159, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B4;      // Byte offset 0x2b4, CSR Addr 0x5415a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B5;      // Byte offset 0x2b5, CSR Addr 0x5415a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B6;      // Byte offset 0x2b6, CSR Addr 0x5415b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B7;      // Byte offset 0x2b7, CSR Addr 0x5415b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B8;      // Byte offset 0x2b8, CSR Addr 0x5415c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2B9;      // Byte offset 0x2b9, CSR Addr 0x5415c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2BA;      // Byte offset 0x2ba, CSR Addr 0x5415d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2BB;      // Byte offset 0x2bb, CSR Addr 0x5415d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2BC;      // Byte offset 0x2bc, CSR Addr 0x5415e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2BD;      // Byte offset 0x2bd, CSR Addr 0x5415e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2BE;      // Byte offset 0x2be, CSR Addr 0x5415f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2BF;      // Byte offset 0x2bf, CSR Addr 0x5415f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C0;      // Byte offset 0x2c0, CSR Addr 0x54160, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C1;      // Byte offset 0x2c1, CSR Addr 0x54160, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C2;      // Byte offset 0x2c2, CSR Addr 0x54161, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C3;      // Byte offset 0x2c3, CSR Addr 0x54161, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C4;      // Byte offset 0x2c4, CSR Addr 0x54162, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C5;      // Byte offset 0x2c5, CSR Addr 0x54162, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C6;      // Byte offset 0x2c6, CSR Addr 0x54163, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C7;      // Byte offset 0x2c7, CSR Addr 0x54163, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C8;      // Byte offset 0x2c8, CSR Addr 0x54164, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2C9;      // Byte offset 0x2c9, CSR Addr 0x54164, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2CA;      // Byte offset 0x2ca, CSR Addr 0x54165, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2CB;      // Byte offset 0x2cb, CSR Addr 0x54165, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2CC;      // Byte offset 0x2cc, CSR Addr 0x54166, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2CD;      // Byte offset 0x2cd, CSR Addr 0x54166, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2CE;      // Byte offset 0x2ce, CSR Addr 0x54167, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2CF;      // Byte offset 0x2cf, CSR Addr 0x54167, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D0;      // Byte offset 0x2d0, CSR Addr 0x54168, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D1;      // Byte offset 0x2d1, CSR Addr 0x54168, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D2;      // Byte offset 0x2d2, CSR Addr 0x54169, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D3;      // Byte offset 0x2d3, CSR Addr 0x54169, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D4;      // Byte offset 0x2d4, CSR Addr 0x5416a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D5;      // Byte offset 0x2d5, CSR Addr 0x5416a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D6;      // Byte offset 0x2d6, CSR Addr 0x5416b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D7;      // Byte offset 0x2d7, CSR Addr 0x5416b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D8;      // Byte offset 0x2d8, CSR Addr 0x5416c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2D9;      // Byte offset 0x2d9, CSR Addr 0x5416c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2DA;      // Byte offset 0x2da, CSR Addr 0x5416d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2DB;      // Byte offset 0x2db, CSR Addr 0x5416d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2DC;      // Byte offset 0x2dc, CSR Addr 0x5416e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2DD;      // Byte offset 0x2dd, CSR Addr 0x5416e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2DE;      // Byte offset 0x2de, CSR Addr 0x5416f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2DF;      // Byte offset 0x2df, CSR Addr 0x5416f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E0;      // Byte offset 0x2e0, CSR Addr 0x54170, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E1;      // Byte offset 0x2e1, CSR Addr 0x54170, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E2;      // Byte offset 0x2e2, CSR Addr 0x54171, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E3;      // Byte offset 0x2e3, CSR Addr 0x54171, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E4;      // Byte offset 0x2e4, CSR Addr 0x54172, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E5;      // Byte offset 0x2e5, CSR Addr 0x54172, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E6;      // Byte offset 0x2e6, CSR Addr 0x54173, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E7;      // Byte offset 0x2e7, CSR Addr 0x54173, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E8;      // Byte offset 0x2e8, CSR Addr 0x54174, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2E9;      // Byte offset 0x2e9, CSR Addr 0x54174, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2EA;      // Byte offset 0x2ea, CSR Addr 0x54175, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2EB;      // Byte offset 0x2eb, CSR Addr 0x54175, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2EC;      // Byte offset 0x2ec, CSR Addr 0x54176, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2ED;      // Byte offset 0x2ed, CSR Addr 0x54176, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2EE;      // Byte offset 0x2ee, CSR Addr 0x54177, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2EF;      // Byte offset 0x2ef, CSR Addr 0x54177, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F0;      // Byte offset 0x2f0, CSR Addr 0x54178, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F1;      // Byte offset 0x2f1, CSR Addr 0x54178, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F2;      // Byte offset 0x2f2, CSR Addr 0x54179, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F3;      // Byte offset 0x2f3, CSR Addr 0x54179, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F4;      // Byte offset 0x2f4, CSR Addr 0x5417a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F5;      // Byte offset 0x2f5, CSR Addr 0x5417a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F6;      // Byte offset 0x2f6, CSR Addr 0x5417b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F7;      // Byte offset 0x2f7, CSR Addr 0x5417b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F8;      // Byte offset 0x2f8, CSR Addr 0x5417c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2F9;      // Byte offset 0x2f9, CSR Addr 0x5417c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2FA;      // Byte offset 0x2fa, CSR Addr 0x5417d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2FB;      // Byte offset 0x2fb, CSR Addr 0x5417d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2FC;      // Byte offset 0x2fc, CSR Addr 0x5417e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2FD;      // Byte offset 0x2fd, CSR Addr 0x5417e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2FE;      // Byte offset 0x2fe, CSR Addr 0x5417f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved2FF;      // Byte offset 0x2ff, CSR Addr 0x5417f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved300;      // Byte offset 0x300, CSR Addr 0x54180, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved301;      // Byte offset 0x301, CSR Addr 0x54180, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved302;      // Byte offset 0x302, CSR Addr 0x54181, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved303;      // Byte offset 0x303, CSR Addr 0x54181, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved304;      // Byte offset 0x304, CSR Addr 0x54182, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved305;      // Byte offset 0x305, CSR Addr 0x54182, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved306;      // Byte offset 0x306, CSR Addr 0x54183, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved307;      // Byte offset 0x307, CSR Addr 0x54183, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved308;      // Byte offset 0x308, CSR Addr 0x54184, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved309;      // Byte offset 0x309, CSR Addr 0x54184, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved30A;      // Byte offset 0x30a, CSR Addr 0x54185, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved30B;      // Byte offset 0x30b, CSR Addr 0x54185, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved30C;      // Byte offset 0x30c, CSR Addr 0x54186, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved30D;      // Byte offset 0x30d, CSR Addr 0x54186, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved30E;      // Byte offset 0x30e, CSR Addr 0x54187, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved30F;      // Byte offset 0x30f, CSR Addr 0x54187, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved310;      // Byte offset 0x310, CSR Addr 0x54188, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved311;      // Byte offset 0x311, CSR Addr 0x54188, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved312;      // Byte offset 0x312, CSR Addr 0x54189, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved313;      // Byte offset 0x313, CSR Addr 0x54189, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved314;      // Byte offset 0x314, CSR Addr 0x5418a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved315;      // Byte offset 0x315, CSR Addr 0x5418a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved316;      // Byte offset 0x316, CSR Addr 0x5418b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved317;      // Byte offset 0x317, CSR Addr 0x5418b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved318;      // Byte offset 0x318, CSR Addr 0x5418c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved319;      // Byte offset 0x319, CSR Addr 0x5418c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved31A;      // Byte offset 0x31a, CSR Addr 0x5418d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved31B;      // Byte offset 0x31b, CSR Addr 0x5418d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved31C;      // Byte offset 0x31c, CSR Addr 0x5418e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved31D;      // Byte offset 0x31d, CSR Addr 0x5418e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved31E;      // Byte offset 0x31e, CSR Addr 0x5418f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved31F;      // Byte offset 0x31f, CSR Addr 0x5418f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved320;      // Byte offset 0x320, CSR Addr 0x54190, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved321;      // Byte offset 0x321, CSR Addr 0x54190, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved322;      // Byte offset 0x322, CSR Addr 0x54191, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved323;      // Byte offset 0x323, CSR Addr 0x54191, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved324;      // Byte offset 0x324, CSR Addr 0x54192, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved325;      // Byte offset 0x325, CSR Addr 0x54192, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved326;      // Byte offset 0x326, CSR Addr 0x54193, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved327;      // Byte offset 0x327, CSR Addr 0x54193, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved328;      // Byte offset 0x328, CSR Addr 0x54194, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved329;      // Byte offset 0x329, CSR Addr 0x54194, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved32A;      // Byte offset 0x32a, CSR Addr 0x54195, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved32B;      // Byte offset 0x32b, CSR Addr 0x54195, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved32C;      // Byte offset 0x32c, CSR Addr 0x54196, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved32D;      // Byte offset 0x32d, CSR Addr 0x54196, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved32E;      // Byte offset 0x32e, CSR Addr 0x54197, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved32F;      // Byte offset 0x32f, CSR Addr 0x54197, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved330;      // Byte offset 0x330, CSR Addr 0x54198, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved331;      // Byte offset 0x331, CSR Addr 0x54198, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved332;      // Byte offset 0x332, CSR Addr 0x54199, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved333;      // Byte offset 0x333, CSR Addr 0x54199, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved334;      // Byte offset 0x334, CSR Addr 0x5419a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved335;      // Byte offset 0x335, CSR Addr 0x5419a, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved336;      // Byte offset 0x336, CSR Addr 0x5419b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved337;      // Byte offset 0x337, CSR Addr 0x5419b, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved338;      // Byte offset 0x338, CSR Addr 0x5419c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved339;      // Byte offset 0x339, CSR Addr 0x5419c, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved33A;      // Byte offset 0x33a, CSR Addr 0x5419d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved33B;      // Byte offset 0x33b, CSR Addr 0x5419d, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved33C;      // Byte offset 0x33c, CSR Addr 0x5419e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved33D;      // Byte offset 0x33d, CSR Addr 0x5419e, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved33E;      // Byte offset 0x33e, CSR Addr 0x5419f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved33F;      // Byte offset 0x33f, CSR Addr 0x5419f, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved340;      // Byte offset 0x340, CSR Addr 0x541a0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved341;      // Byte offset 0x341, CSR Addr 0x541a0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved342;      // Byte offset 0x342, CSR Addr 0x541a1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved343;      // Byte offset 0x343, CSR Addr 0x541a1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved344;      // Byte offset 0x344, CSR Addr 0x541a2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved345;      // Byte offset 0x345, CSR Addr 0x541a2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved346;      // Byte offset 0x346, CSR Addr 0x541a3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved347;      // Byte offset 0x347, CSR Addr 0x541a3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved348;      // Byte offset 0x348, CSR Addr 0x541a4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved349;      // Byte offset 0x349, CSR Addr 0x541a4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved34A;      // Byte offset 0x34a, CSR Addr 0x541a5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved34B;      // Byte offset 0x34b, CSR Addr 0x541a5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved34C;      // Byte offset 0x34c, CSR Addr 0x541a6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved34D;      // Byte offset 0x34d, CSR Addr 0x541a6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved34E;      // Byte offset 0x34e, CSR Addr 0x541a7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved34F;      // Byte offset 0x34f, CSR Addr 0x541a7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved350;      // Byte offset 0x350, CSR Addr 0x541a8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved351;      // Byte offset 0x351, CSR Addr 0x541a8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved352;      // Byte offset 0x352, CSR Addr 0x541a9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved353;      // Byte offset 0x353, CSR Addr 0x541a9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved354;      // Byte offset 0x354, CSR Addr 0x541aa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved355;      // Byte offset 0x355, CSR Addr 0x541aa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved356;      // Byte offset 0x356, CSR Addr 0x541ab, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved357;      // Byte offset 0x357, CSR Addr 0x541ab, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved358;      // Byte offset 0x358, CSR Addr 0x541ac, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved359;      // Byte offset 0x359, CSR Addr 0x541ac, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved35A;      // Byte offset 0x35a, CSR Addr 0x541ad, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved35B;      // Byte offset 0x35b, CSR Addr 0x541ad, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved35C;      // Byte offset 0x35c, CSR Addr 0x541ae, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved35D;      // Byte offset 0x35d, CSR Addr 0x541ae, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved35E;      // Byte offset 0x35e, CSR Addr 0x541af, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved35F;      // Byte offset 0x35f, CSR Addr 0x541af, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved360;      // Byte offset 0x360, CSR Addr 0x541b0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved361;      // Byte offset 0x361, CSR Addr 0x541b0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved362;      // Byte offset 0x362, CSR Addr 0x541b1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved363;      // Byte offset 0x363, CSR Addr 0x541b1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved364;      // Byte offset 0x364, CSR Addr 0x541b2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved365;      // Byte offset 0x365, CSR Addr 0x541b2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved366;      // Byte offset 0x366, CSR Addr 0x541b3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved367;      // Byte offset 0x367, CSR Addr 0x541b3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved368;      // Byte offset 0x368, CSR Addr 0x541b4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved369;      // Byte offset 0x369, CSR Addr 0x541b4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved36A;      // Byte offset 0x36a, CSR Addr 0x541b5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved36B;      // Byte offset 0x36b, CSR Addr 0x541b5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved36C;      // Byte offset 0x36c, CSR Addr 0x541b6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved36D;      // Byte offset 0x36d, CSR Addr 0x541b6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved36E;      // Byte offset 0x36e, CSR Addr 0x541b7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved36F;      // Byte offset 0x36f, CSR Addr 0x541b7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved370;      // Byte offset 0x370, CSR Addr 0x541b8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved371;      // Byte offset 0x371, CSR Addr 0x541b8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved372;      // Byte offset 0x372, CSR Addr 0x541b9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved373;      // Byte offset 0x373, CSR Addr 0x541b9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved374;      // Byte offset 0x374, CSR Addr 0x541ba, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved375;      // Byte offset 0x375, CSR Addr 0x541ba, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved376;      // Byte offset 0x376, CSR Addr 0x541bb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved377;      // Byte offset 0x377, CSR Addr 0x541bb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved378;      // Byte offset 0x378, CSR Addr 0x541bc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved379;      // Byte offset 0x379, CSR Addr 0x541bc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved37A;      // Byte offset 0x37a, CSR Addr 0x541bd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved37B;      // Byte offset 0x37b, CSR Addr 0x541bd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved37C;      // Byte offset 0x37c, CSR Addr 0x541be, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved37D;      // Byte offset 0x37d, CSR Addr 0x541be, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved37E;      // Byte offset 0x37e, CSR Addr 0x541bf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved37F;      // Byte offset 0x37f, CSR Addr 0x541bf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved380;      // Byte offset 0x380, CSR Addr 0x541c0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved381;      // Byte offset 0x381, CSR Addr 0x541c0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved382;      // Byte offset 0x382, CSR Addr 0x541c1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved383;      // Byte offset 0x383, CSR Addr 0x541c1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved384;      // Byte offset 0x384, CSR Addr 0x541c2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved385;      // Byte offset 0x385, CSR Addr 0x541c2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved386;      // Byte offset 0x386, CSR Addr 0x541c3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved387;      // Byte offset 0x387, CSR Addr 0x541c3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved388;      // Byte offset 0x388, CSR Addr 0x541c4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved389;      // Byte offset 0x389, CSR Addr 0x541c4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved38A;      // Byte offset 0x38a, CSR Addr 0x541c5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved38B;      // Byte offset 0x38b, CSR Addr 0x541c5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved38C;      // Byte offset 0x38c, CSR Addr 0x541c6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved38D;      // Byte offset 0x38d, CSR Addr 0x541c6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved38E;      // Byte offset 0x38e, CSR Addr 0x541c7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved38F;      // Byte offset 0x38f, CSR Addr 0x541c7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved390;      // Byte offset 0x390, CSR Addr 0x541c8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved391;      // Byte offset 0x391, CSR Addr 0x541c8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved392;      // Byte offset 0x392, CSR Addr 0x541c9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved393;      // Byte offset 0x393, CSR Addr 0x541c9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved394;      // Byte offset 0x394, CSR Addr 0x541ca, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved395;      // Byte offset 0x395, CSR Addr 0x541ca, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved396;      // Byte offset 0x396, CSR Addr 0x541cb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved397;      // Byte offset 0x397, CSR Addr 0x541cb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved398;      // Byte offset 0x398, CSR Addr 0x541cc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved399;      // Byte offset 0x399, CSR Addr 0x541cc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved39A;      // Byte offset 0x39a, CSR Addr 0x541cd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved39B;      // Byte offset 0x39b, CSR Addr 0x541cd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved39C;      // Byte offset 0x39c, CSR Addr 0x541ce, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved39D;      // Byte offset 0x39d, CSR Addr 0x541ce, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved39E;      // Byte offset 0x39e, CSR Addr 0x541cf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved39F;      // Byte offset 0x39f, CSR Addr 0x541cf, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A0;      // Byte offset 0x3a0, CSR Addr 0x541d0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A1;      // Byte offset 0x3a1, CSR Addr 0x541d0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A2;      // Byte offset 0x3a2, CSR Addr 0x541d1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A3;      // Byte offset 0x3a3, CSR Addr 0x541d1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A4;      // Byte offset 0x3a4, CSR Addr 0x541d2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A5;      // Byte offset 0x3a5, CSR Addr 0x541d2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A6;      // Byte offset 0x3a6, CSR Addr 0x541d3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A7;      // Byte offset 0x3a7, CSR Addr 0x541d3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A8;      // Byte offset 0x3a8, CSR Addr 0x541d4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3A9;      // Byte offset 0x3a9, CSR Addr 0x541d4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3AA;      // Byte offset 0x3aa, CSR Addr 0x541d5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3AB;      // Byte offset 0x3ab, CSR Addr 0x541d5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3AC;      // Byte offset 0x3ac, CSR Addr 0x541d6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3AD;      // Byte offset 0x3ad, CSR Addr 0x541d6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3AE;      // Byte offset 0x3ae, CSR Addr 0x541d7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3AF;      // Byte offset 0x3af, CSR Addr 0x541d7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B0;      // Byte offset 0x3b0, CSR Addr 0x541d8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B1;      // Byte offset 0x3b1, CSR Addr 0x541d8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B2;      // Byte offset 0x3b2, CSR Addr 0x541d9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B3;      // Byte offset 0x3b3, CSR Addr 0x541d9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B4;      // Byte offset 0x3b4, CSR Addr 0x541da, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B5;      // Byte offset 0x3b5, CSR Addr 0x541da, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B6;      // Byte offset 0x3b6, CSR Addr 0x541db, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B7;      // Byte offset 0x3b7, CSR Addr 0x541db, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B8;      // Byte offset 0x3b8, CSR Addr 0x541dc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3B9;      // Byte offset 0x3b9, CSR Addr 0x541dc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3BA;      // Byte offset 0x3ba, CSR Addr 0x541dd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3BB;      // Byte offset 0x3bb, CSR Addr 0x541dd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3BC;      // Byte offset 0x3bc, CSR Addr 0x541de, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3BD;      // Byte offset 0x3bd, CSR Addr 0x541de, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3BE;      // Byte offset 0x3be, CSR Addr 0x541df, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3BF;      // Byte offset 0x3bf, CSR Addr 0x541df, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C0;      // Byte offset 0x3c0, CSR Addr 0x541e0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C1;      // Byte offset 0x3c1, CSR Addr 0x541e0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C2;      // Byte offset 0x3c2, CSR Addr 0x541e1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C3;      // Byte offset 0x3c3, CSR Addr 0x541e1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C4;      // Byte offset 0x3c4, CSR Addr 0x541e2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C5;      // Byte offset 0x3c5, CSR Addr 0x541e2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C6;      // Byte offset 0x3c6, CSR Addr 0x541e3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C7;      // Byte offset 0x3c7, CSR Addr 0x541e3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C8;      // Byte offset 0x3c8, CSR Addr 0x541e4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3C9;      // Byte offset 0x3c9, CSR Addr 0x541e4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3CA;      // Byte offset 0x3ca, CSR Addr 0x541e5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3CB;      // Byte offset 0x3cb, CSR Addr 0x541e5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3CC;      // Byte offset 0x3cc, CSR Addr 0x541e6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3CD;      // Byte offset 0x3cd, CSR Addr 0x541e6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3CE;      // Byte offset 0x3ce, CSR Addr 0x541e7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3CF;      // Byte offset 0x3cf, CSR Addr 0x541e7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D0;      // Byte offset 0x3d0, CSR Addr 0x541e8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D1;      // Byte offset 0x3d1, CSR Addr 0x541e8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D2;      // Byte offset 0x3d2, CSR Addr 0x541e9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D3;      // Byte offset 0x3d3, CSR Addr 0x541e9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D4;      // Byte offset 0x3d4, CSR Addr 0x541ea, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D5;      // Byte offset 0x3d5, CSR Addr 0x541ea, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D6;      // Byte offset 0x3d6, CSR Addr 0x541eb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D7;      // Byte offset 0x3d7, CSR Addr 0x541eb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D8;      // Byte offset 0x3d8, CSR Addr 0x541ec, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3D9;      // Byte offset 0x3d9, CSR Addr 0x541ec, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3DA;      // Byte offset 0x3da, CSR Addr 0x541ed, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3DB;      // Byte offset 0x3db, CSR Addr 0x541ed, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3DC;      // Byte offset 0x3dc, CSR Addr 0x541ee, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3DD;      // Byte offset 0x3dd, CSR Addr 0x541ee, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3DE;      // Byte offset 0x3de, CSR Addr 0x541ef, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3DF;      // Byte offset 0x3df, CSR Addr 0x541ef, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E0;      // Byte offset 0x3e0, CSR Addr 0x541f0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E1;      // Byte offset 0x3e1, CSR Addr 0x541f0, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E2;      // Byte offset 0x3e2, CSR Addr 0x541f1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E3;      // Byte offset 0x3e3, CSR Addr 0x541f1, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E4;      // Byte offset 0x3e4, CSR Addr 0x541f2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E5;      // Byte offset 0x3e5, CSR Addr 0x541f2, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E6;      // Byte offset 0x3e6, CSR Addr 0x541f3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E7;      // Byte offset 0x3e7, CSR Addr 0x541f3, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E8;      // Byte offset 0x3e8, CSR Addr 0x541f4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3E9;      // Byte offset 0x3e9, CSR Addr 0x541f4, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3EA;      // Byte offset 0x3ea, CSR Addr 0x541f5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3EB;      // Byte offset 0x3eb, CSR Addr 0x541f5, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3EC;      // Byte offset 0x3ec, CSR Addr 0x541f6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3ED;      // Byte offset 0x3ed, CSR Addr 0x541f6, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3EE;      // Byte offset 0x3ee, CSR Addr 0x541f7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3EF;      // Byte offset 0x3ef, CSR Addr 0x541f7, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F0;      // Byte offset 0x3f0, CSR Addr 0x541f8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F1;      // Byte offset 0x3f1, CSR Addr 0x541f8, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F2;      // Byte offset 0x3f2, CSR Addr 0x541f9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F3;      // Byte offset 0x3f3, CSR Addr 0x541f9, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F4;      // Byte offset 0x3f4, CSR Addr 0x541fa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F5;      // Byte offset 0x3f5, CSR Addr 0x541fa, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F6;      // Byte offset 0x3f6, CSR Addr 0x541fb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F7;      // Byte offset 0x3f7, CSR Addr 0x541fb, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F8;      // Byte offset 0x3f8, CSR Addr 0x541fc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3F9;      // Byte offset 0x3f9, CSR Addr 0x541fc, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3FA;      // Byte offset 0x3fa, CSR Addr 0x541fd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3FB;      // Byte offset 0x3fb, CSR Addr 0x541fd, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3FC;      // Byte offset 0x3fc, CSR Addr 0x541fe, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3FD;      // Byte offset 0x3fd, CSR Addr 0x541fe, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3FE;      // Byte offset 0x3fe, CSR Addr 0x541ff, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
   uint8_t  Reserved3FF;      // Byte offset 0x3ff, CSR Addr 0x541ff, Direction=N/A
                              // This field is reserved and must be programmed to 0x00.
} __attribute__ ((packed)) PMU_SMB_LPDDR4_1D_t;
