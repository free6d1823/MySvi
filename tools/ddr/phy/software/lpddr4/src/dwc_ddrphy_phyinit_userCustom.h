
/** \file
 * \brief structures and enumeration definitions
 */
#include <stdint.h>
/*! \def DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE
	\brief Max number of allowed PStates for this product.
 */
#define DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE 15
#include <dwc_ddrphy_phyinit_struct.h>

//-------------------------------------------------------------
// Defines for Firmware Images
// - point to IMEM/DMEM incv files,
// - indicate IMEM/DMEM size (bytes)
//-------------------------------------------------------------
/*! \def FW_FILES_LOC
	\brief set the location of training firmware uncompressed path.

	PhyInit will use this path to load the imem and dmem incv files of the
    firmware image.
 */
/*! \def IMEM_INCV_FILENAME
	\brief firmware instruction memory (imem) filename for 1D training
 */
/*! \def DMEM_INCV_FILENAME
	\brief firmware instruction memory (imem) filename for 1D training.
 */
/*! \def IMEM_SIZE
	\brief max size of instruction memory.
 */
/*! \def DMEM_SIZE
	\brief max size of data memory.
 */
/*! \def DMEM_ST_ADDR
	\brief start of DMEM address in memory.
 */
#ifndef FW_FILES_LOC
#define FW_FILES_LOC "./fw"
#endif
#define IMEM_INCV_FILENAME               FW_FILES_LOC"/lpddr4/lpddr4_pmu_train_imem.incv"
#define DMEM_INCV_FILENAME               FW_FILES_LOC"/lpddr4/lpddr4_pmu_train_dmem.incv"

/*! \def IMEM_INCV_FILENAME_2D
	\brief firmware instruction memory (imem) filename for 2D training
 */
/*! \def DMEM_INCV_FILENAME_2D
	\brief firmware instruction memory (dmem) filename for 2D training.
 */
#define IMEM_INCV_FILENAME_2D            FW_FILES_LOC"/lpddr4_2d/lpddr4_2d_pmu_train_imem.incv"
#define DMEM_INCV_FILENAME_2D            FW_FILES_LOC"/lpddr4_2d/lpddr4_2d_pmu_train_dmem.incv"


#define IMEM_SIZE 65536
#define DMEM_SIZE 32768
#define DMEM_ST_ADDR 0x58000

///> Added for multiple PHY interface.
#ifndef DWC_DDRPHY_NUM_PHY
#define DWC_DDRPHY_NUM_PHY (1)
#endif
//-------------------------------------------------------------
// Defines for SR Firmware Images
// - point to IMEM incv files,
// - indicate IMEM size (bytes)
//-------------------------------------------------------------
/*! \def SR_FW_FILES_LOC
	\brief location of optional retention save restore firmware image.
 */
/*! \def SR_IMEM_SIZE
	\brief max IMEM size of retention save/restore firmware.
 */
/*! \def SR_IMEM_INCV_FILENAME
	\brief file name of retention save/restore IMEM image.
 */
#ifndef SR_FW_FILES_LOC
#define SR_FW_FILES_LOC FW_FILES_LOC"/save_restore"
#endif

#define SR_IMEM_SIZE 16384
#define SR_IMEM_INCV_FILENAME       SR_FW_FILES_LOC"/dwc_ddrphy_io_retention_save_restore_imem.incv"

// Message Block Structure Definitions.
#include "mnPmuSramMsgBlock_lpddr4.h"
#include "mnPmuSramMsgBlock_lpddr4_2d.h"


//------------------
// Type definitions
//------------------

/// A structure used to SRAM memory address space.
typedef enum {return_offset, return_lastaddr} return_offset_lastaddr_t;

/// enumeration of instructions for PhyInit Register Interface
typedef enum {
  startTrack,       ///< start register tracking
  stopTrack,        ///< stop register tracking
  saveRegs,         ///< save(read) tracked register values
  restoreRegs,      ///< restore (write) saved register values
  dumpRegs,         ///< write register address,value pairs to file
  importRegs,       ///< import register address,value pairs to file
  setGroup,         ///< change DMA register group
  startPsLoop,      ///< signals start of PState loop in Sequence
  stopPsLoop,       ///< signals stop PState loop in Sequence
  endPsLoop,        ///< Signals End of the Ps Loop to the register IF.
  resumePsLoop      ///< Signals to resume DMA writes after stopPsLoop.
} regInstr;

/// enumeration of user input fields of PhyInit
typedef enum {

  // pRuntimeConfig Fields:
  _skip_train_, // 0
  _initCtrl_, // 1
  _Train2D_, // 2
  _curD_, // 3
  _debug_, // 4
  _RetEn_, // 5
  _curPState_, // 6

  // pUserInputAdvanced Fields:
  _WDQSExt_, // 7
  _PhyMstrCtrlMode_0_, // 8
  _PhyMstrCtrlMode_1_, // 9
  _PhyMstrCtrlMode_2_, // 10
  _PhyMstrCtrlMode_3_, // 11
  _PhyMstrCtrlMode_4_, // 12
  _PhyMstrCtrlMode_5_, // 13
  _PhyMstrCtrlMode_6_, // 14
  _PhyMstrCtrlMode_7_, // 15
  _PhyMstrCtrlMode_8_, // 16
  _PhyMstrCtrlMode_9_, // 17
  _PhyMstrCtrlMode_10_, // 18
  _PhyMstrCtrlMode_11_, // 19
  _PhyMstrCtrlMode_12_, // 20
  _PhyMstrCtrlMode_13_, // 21
  _PhyMstrCtrlMode_14_, // 22
  _TxSlewFallDqs_0_, // 23
  _TxSlewFallDqs_1_, // 24
  _TxSlewFallDqs_2_, // 25
  _TxSlewFallDqs_3_, // 26
  _TxSlewFallDqs_4_, // 27
  _TxSlewFallDqs_5_, // 28
  _TxSlewFallDqs_6_, // 29
  _TxSlewFallDqs_7_, // 30
  _TxSlewFallDqs_8_, // 31
  _TxSlewFallDqs_9_, // 32
  _TxSlewFallDqs_10_, // 33
  _TxSlewFallDqs_11_, // 34
  _TxSlewFallDqs_12_, // 35
  _TxSlewFallDqs_13_, // 36
  _TxSlewFallDqs_14_, // 37
  _TxImpedanceDq_0_, // 38
  _TxImpedanceDq_1_, // 39
  _TxImpedanceDq_2_, // 40
  _TxImpedanceDq_3_, // 41
  _TxImpedanceDq_4_, // 42
  _TxImpedanceDq_5_, // 43
  _TxImpedanceDq_6_, // 44
  _TxImpedanceDq_7_, // 45
  _TxImpedanceDq_8_, // 46
  _TxImpedanceDq_9_, // 47
  _TxImpedanceDq_10_, // 48
  _TxImpedanceDq_11_, // 49
  _TxImpedanceDq_12_, // 50
  _TxImpedanceDq_13_, // 51
  _TxImpedanceDq_14_, // 52
  _TxSlewRiseCK_0_, // 53
  _TxSlewRiseCK_1_, // 54
  _TxSlewRiseCK_2_, // 55
  _TxSlewRiseCK_3_, // 56
  _TxSlewRiseCK_4_, // 57
  _TxSlewRiseCK_5_, // 58
  _TxSlewRiseCK_6_, // 59
  _TxSlewRiseCK_7_, // 60
  _TxSlewRiseCK_8_, // 61
  _TxSlewRiseCK_9_, // 62
  _TxSlewRiseCK_10_, // 63
  _TxSlewRiseCK_11_, // 64
  _TxSlewRiseCK_12_, // 65
  _TxSlewRiseCK_13_, // 66
  _TxSlewRiseCK_14_, // 67
  _OdtImpedanceCk_0_, // 68
  _OdtImpedanceCk_1_, // 69
  _OdtImpedanceCk_2_, // 70
  _OdtImpedanceCk_3_, // 71
  _OdtImpedanceCk_4_, // 72
  _OdtImpedanceCk_5_, // 73
  _OdtImpedanceCk_6_, // 74
  _OdtImpedanceCk_7_, // 75
  _OdtImpedanceCk_8_, // 76
  _OdtImpedanceCk_9_, // 77
  _OdtImpedanceCk_10_, // 78
  _OdtImpedanceCk_11_, // 79
  _OdtImpedanceCk_12_, // 80
  _OdtImpedanceCk_13_, // 81
  _OdtImpedanceCk_14_, // 82
  _RxVrefKickbackNoiseCancellation_0_, // 83
  _RxVrefKickbackNoiseCancellation_1_, // 84
  _RxVrefKickbackNoiseCancellation_2_, // 85
  _RxVrefKickbackNoiseCancellation_3_, // 86
  _RxVrefKickbackNoiseCancellation_4_, // 87
  _RxVrefKickbackNoiseCancellation_5_, // 88
  _RxVrefKickbackNoiseCancellation_6_, // 89
  _RxVrefKickbackNoiseCancellation_7_, // 90
  _RxVrefKickbackNoiseCancellation_8_, // 91
  _RxVrefKickbackNoiseCancellation_9_, // 92
  _RxVrefKickbackNoiseCancellation_10_, // 93
  _RxVrefKickbackNoiseCancellation_11_, // 94
  _RxVrefKickbackNoiseCancellation_12_, // 95
  _RxVrefKickbackNoiseCancellation_13_, // 96
  _RxVrefKickbackNoiseCancellation_14_, // 97
  _RxModeBoostVDD_0_, // 98
  _RxModeBoostVDD_1_, // 99
  _RxModeBoostVDD_2_, // 100
  _RxModeBoostVDD_3_, // 101
  _RxModeBoostVDD_4_, // 102
  _RxModeBoostVDD_5_, // 103
  _RxModeBoostVDD_6_, // 104
  _RxModeBoostVDD_7_, // 105
  _RxModeBoostVDD_8_, // 106
  _RxModeBoostVDD_9_, // 107
  _RxModeBoostVDD_10_, // 108
  _RxModeBoostVDD_11_, // 109
  _RxModeBoostVDD_12_, // 110
  _RxModeBoostVDD_13_, // 111
  _RxModeBoostVDD_14_, // 112
  _TxSlewRiseDq_0_, // 113
  _TxSlewRiseDq_1_, // 114
  _TxSlewRiseDq_2_, // 115
  _TxSlewRiseDq_3_, // 116
  _TxSlewRiseDq_4_, // 117
  _TxSlewRiseDq_5_, // 118
  _TxSlewRiseDq_6_, // 119
  _TxSlewRiseDq_7_, // 120
  _TxSlewRiseDq_8_, // 121
  _TxSlewRiseDq_9_, // 122
  _TxSlewRiseDq_10_, // 123
  _TxSlewRiseDq_11_, // 124
  _TxSlewRiseDq_12_, // 125
  _TxSlewRiseDq_13_, // 126
  _TxSlewRiseDq_14_, // 127
  _PhyMstrTrainInterval_0_, // 128
  _PhyMstrTrainInterval_1_, // 129
  _PhyMstrTrainInterval_2_, // 130
  _PhyMstrTrainInterval_3_, // 131
  _PhyMstrTrainInterval_4_, // 132
  _PhyMstrTrainInterval_5_, // 133
  _PhyMstrTrainInterval_6_, // 134
  _PhyMstrTrainInterval_7_, // 135
  _PhyMstrTrainInterval_8_, // 136
  _PhyMstrTrainInterval_9_, // 137
  _PhyMstrTrainInterval_10_, // 138
  _PhyMstrTrainInterval_11_, // 139
  _PhyMstrTrainInterval_12_, // 140
  _PhyMstrTrainInterval_13_, // 141
  _PhyMstrTrainInterval_14_, // 142
  _OdtImpedanceCs_0_, // 143
  _OdtImpedanceCs_1_, // 144
  _OdtImpedanceCs_2_, // 145
  _OdtImpedanceCs_3_, // 146
  _OdtImpedanceCs_4_, // 147
  _OdtImpedanceCs_5_, // 148
  _OdtImpedanceCs_6_, // 149
  _OdtImpedanceCs_7_, // 150
  _OdtImpedanceCs_8_, // 151
  _OdtImpedanceCs_9_, // 152
  _OdtImpedanceCs_10_, // 153
  _OdtImpedanceCs_11_, // 154
  _OdtImpedanceCs_12_, // 155
  _OdtImpedanceCs_13_, // 156
  _OdtImpedanceCs_14_, // 157
  _RxClkTrackEn_0_, // 158
  _RxClkTrackEn_1_, // 159
  _RxClkTrackEn_2_, // 160
  _RxClkTrackEn_3_, // 161
  _RxClkTrackEn_4_, // 162
  _RxClkTrackEn_5_, // 163
  _RxClkTrackEn_6_, // 164
  _RxClkTrackEn_7_, // 165
  _RxClkTrackEn_8_, // 166
  _RxClkTrackEn_9_, // 167
  _RxClkTrackEn_10_, // 168
  _RxClkTrackEn_11_, // 169
  _RxClkTrackEn_12_, // 170
  _RxClkTrackEn_13_, // 171
  _RxClkTrackEn_14_, // 172
  _TxSlewFallCK_0_, // 173
  _TxSlewFallCK_1_, // 174
  _TxSlewFallCK_2_, // 175
  _TxSlewFallCK_3_, // 176
  _TxSlewFallCK_4_, // 177
  _TxSlewFallCK_5_, // 178
  _TxSlewFallCK_6_, // 179
  _TxSlewFallCK_7_, // 180
  _TxSlewFallCK_8_, // 181
  _TxSlewFallCK_9_, // 182
  _TxSlewFallCK_10_, // 183
  _TxSlewFallCK_11_, // 184
  _TxSlewFallCK_12_, // 185
  _TxSlewFallCK_13_, // 186
  _TxSlewFallCK_14_, // 187
  _TxSlewFallCS_0_, // 188
  _TxSlewFallCS_1_, // 189
  _TxSlewFallCS_2_, // 190
  _TxSlewFallCS_3_, // 191
  _TxSlewFallCS_4_, // 192
  _TxSlewFallCS_5_, // 193
  _TxSlewFallCS_6_, // 194
  _TxSlewFallCS_7_, // 195
  _TxSlewFallCS_8_, // 196
  _TxSlewFallCS_9_, // 197
  _TxSlewFallCS_10_, // 198
  _TxSlewFallCS_11_, // 199
  _TxSlewFallCS_12_, // 200
  _TxSlewFallCS_13_, // 201
  _TxSlewFallCS_14_, // 202
  _CkDisVal_0_, // 203
  _CkDisVal_1_, // 204
  _CkDisVal_2_, // 205
  _CkDisVal_3_, // 206
  _CkDisVal_4_, // 207
  _CkDisVal_5_, // 208
  _CkDisVal_6_, // 209
  _CkDisVal_7_, // 210
  _CkDisVal_8_, // 211
  _CkDisVal_9_, // 212
  _CkDisVal_10_, // 213
  _CkDisVal_11_, // 214
  _CkDisVal_12_, // 215
  _CkDisVal_13_, // 216
  _CkDisVal_14_, // 217
  _DisableUnusedAddrLns_, // 218
  _TxSlewRiseDqs_0_, // 219
  _TxSlewRiseDqs_1_, // 220
  _TxSlewRiseDqs_2_, // 221
  _TxSlewRiseDqs_3_, // 222
  _TxSlewRiseDqs_4_, // 223
  _TxSlewRiseDqs_5_, // 224
  _TxSlewRiseDqs_6_, // 225
  _TxSlewRiseDqs_7_, // 226
  _TxSlewRiseDqs_8_, // 227
  _TxSlewRiseDqs_9_, // 228
  _TxSlewRiseDqs_10_, // 229
  _TxSlewRiseDqs_11_, // 230
  _TxSlewRiseDqs_12_, // 231
  _TxSlewRiseDqs_13_, // 232
  _TxSlewRiseDqs_14_, // 233
  _OdtImpedanceDqs_0_, // 234
  _OdtImpedanceDqs_1_, // 235
  _OdtImpedanceDqs_2_, // 236
  _OdtImpedanceDqs_3_, // 237
  _OdtImpedanceDqs_4_, // 238
  _OdtImpedanceDqs_5_, // 239
  _OdtImpedanceDqs_6_, // 240
  _OdtImpedanceDqs_7_, // 241
  _OdtImpedanceDqs_8_, // 242
  _OdtImpedanceDqs_9_, // 243
  _OdtImpedanceDqs_10_, // 244
  _OdtImpedanceDqs_11_, // 245
  _OdtImpedanceDqs_12_, // 246
  _OdtImpedanceDqs_13_, // 247
  _OdtImpedanceDqs_14_, // 248
  _DqsOscRunTimeSel_0_, // 249
  _DqsOscRunTimeSel_1_, // 250
  _DqsOscRunTimeSel_2_, // 251
  _DqsOscRunTimeSel_3_, // 252
  _DqsOscRunTimeSel_4_, // 253
  _DqsOscRunTimeSel_5_, // 254
  _DqsOscRunTimeSel_6_, // 255
  _DqsOscRunTimeSel_7_, // 256
  _DqsOscRunTimeSel_8_, // 257
  _DqsOscRunTimeSel_9_, // 258
  _DqsOscRunTimeSel_10_, // 259
  _DqsOscRunTimeSel_11_, // 260
  _DqsOscRunTimeSel_12_, // 261
  _DqsOscRunTimeSel_13_, // 262
  _DqsOscRunTimeSel_14_, // 263
  _TxSlewRiseCS_0_, // 264
  _TxSlewRiseCS_1_, // 265
  _TxSlewRiseCS_2_, // 266
  _TxSlewRiseCS_3_, // 267
  _TxSlewRiseCS_4_, // 268
  _TxSlewRiseCS_5_, // 269
  _TxSlewRiseCS_6_, // 270
  _TxSlewRiseCS_7_, // 271
  _TxSlewRiseCS_8_, // 272
  _TxSlewRiseCS_9_, // 273
  _TxSlewRiseCS_10_, // 274
  _TxSlewRiseCS_11_, // 275
  _TxSlewRiseCS_12_, // 276
  _TxSlewRiseCS_13_, // 277
  _TxSlewRiseCS_14_, // 278
  _TxImpedanceCk_0_, // 279
  _TxImpedanceCk_1_, // 280
  _TxImpedanceCk_2_, // 281
  _TxImpedanceCk_3_, // 282
  _TxImpedanceCk_4_, // 283
  _TxImpedanceCk_5_, // 284
  _TxImpedanceCk_6_, // 285
  _TxImpedanceCk_7_, // 286
  _TxImpedanceCk_8_, // 287
  _TxImpedanceCk_9_, // 288
  _TxImpedanceCk_10_, // 289
  _TxImpedanceCk_11_, // 290
  _TxImpedanceCk_12_, // 291
  _TxImpedanceCk_13_, // 292
  _TxImpedanceCk_14_, // 293
  _PhyMstrMaxReqToAck_0_, // 294
  _PhyMstrMaxReqToAck_1_, // 295
  _PhyMstrMaxReqToAck_2_, // 296
  _PhyMstrMaxReqToAck_3_, // 297
  _PhyMstrMaxReqToAck_4_, // 298
  _PhyMstrMaxReqToAck_5_, // 299
  _PhyMstrMaxReqToAck_6_, // 300
  _PhyMstrMaxReqToAck_7_, // 301
  _PhyMstrMaxReqToAck_8_, // 302
  _PhyMstrMaxReqToAck_9_, // 303
  _PhyMstrMaxReqToAck_10_, // 304
  _PhyMstrMaxReqToAck_11_, // 305
  _PhyMstrMaxReqToAck_12_, // 306
  _PhyMstrMaxReqToAck_13_, // 307
  _PhyMstrMaxReqToAck_14_, // 308
  _CalOnce_, // 309
  _TxImpedanceCKE_0_, // 310
  _TxImpedanceCKE_1_, // 311
  _TxImpedanceCKE_2_, // 312
  _TxImpedanceCKE_3_, // 313
  _TxImpedanceCKE_4_, // 314
  _TxImpedanceCKE_5_, // 315
  _TxImpedanceCKE_6_, // 316
  _TxImpedanceCKE_7_, // 317
  _TxImpedanceCKE_8_, // 318
  _TxImpedanceCKE_9_, // 319
  _TxImpedanceCKE_10_, // 320
  _TxImpedanceCKE_11_, // 321
  _TxImpedanceCKE_12_, // 322
  _TxImpedanceCKE_13_, // 323
  _TxImpedanceCKE_14_, // 324
  _RxDqsTrackingThreshold_0_, // 325
  _RxDqsTrackingThreshold_1_, // 326
  _RxDqsTrackingThreshold_2_, // 327
  _RxDqsTrackingThreshold_3_, // 328
  _RxDqsTrackingThreshold_4_, // 329
  _RxDqsTrackingThreshold_5_, // 330
  _RxDqsTrackingThreshold_6_, // 331
  _RxDqsTrackingThreshold_7_, // 332
  _RxDqsTrackingThreshold_8_, // 333
  _RxDqsTrackingThreshold_9_, // 334
  _RxDqsTrackingThreshold_10_, // 335
  _RxDqsTrackingThreshold_11_, // 336
  _RxDqsTrackingThreshold_12_, // 337
  _RxDqsTrackingThreshold_13_, // 338
  _RxDqsTrackingThreshold_14_, // 339
  _DisablePmuEcc_, // 340
  _TxSlewRiseCA_0_, // 341
  _TxSlewRiseCA_1_, // 342
  _TxSlewRiseCA_2_, // 343
  _TxSlewRiseCA_3_, // 344
  _TxSlewRiseCA_4_, // 345
  _TxSlewRiseCA_5_, // 346
  _TxSlewRiseCA_6_, // 347
  _TxSlewRiseCA_7_, // 348
  _TxSlewRiseCA_8_, // 349
  _TxSlewRiseCA_9_, // 350
  _TxSlewRiseCA_10_, // 351
  _TxSlewRiseCA_11_, // 352
  _TxSlewRiseCA_12_, // 353
  _TxSlewRiseCA_13_, // 354
  _TxSlewRiseCA_14_, // 355
  _RxClkTrackWaitUI_, // 356
  _ExtCalResVal_, // 357
  _OdtImpedanceDq_0_, // 358
  _OdtImpedanceDq_1_, // 359
  _OdtImpedanceDq_2_, // 360
  _OdtImpedanceDq_3_, // 361
  _OdtImpedanceDq_4_, // 362
  _OdtImpedanceDq_5_, // 363
  _OdtImpedanceDq_6_, // 364
  _OdtImpedanceDq_7_, // 365
  _OdtImpedanceDq_8_, // 366
  _OdtImpedanceDq_9_, // 367
  _OdtImpedanceDq_10_, // 368
  _OdtImpedanceDq_11_, // 369
  _OdtImpedanceDq_12_, // 370
  _OdtImpedanceDq_13_, // 371
  _OdtImpedanceDq_14_, // 372
  _TxSlewFallCA_0_, // 373
  _TxSlewFallCA_1_, // 374
  _TxSlewFallCA_2_, // 375
  _TxSlewFallCA_3_, // 376
  _TxSlewFallCA_4_, // 377
  _TxSlewFallCA_5_, // 378
  _TxSlewFallCA_6_, // 379
  _TxSlewFallCA_7_, // 380
  _TxSlewFallCA_8_, // 381
  _TxSlewFallCA_9_, // 382
  _TxSlewFallCA_10_, // 383
  _TxSlewFallCA_11_, // 384
  _TxSlewFallCA_12_, // 385
  _TxSlewFallCA_13_, // 386
  _TxSlewFallCA_14_, // 387
  _DramByteSwap_, // 388
  _RxBiasCurrentControlRxReplica_0_, // 389
  _RxBiasCurrentControlRxReplica_1_, // 390
  _RxBiasCurrentControlRxReplica_2_, // 391
  _RxBiasCurrentControlRxReplica_3_, // 392
  _RxBiasCurrentControlRxReplica_4_, // 393
  _RxBiasCurrentControlRxReplica_5_, // 394
  _RxBiasCurrentControlRxReplica_6_, // 395
  _RxBiasCurrentControlRxReplica_7_, // 396
  _RxBiasCurrentControlRxReplica_8_, // 397
  _RxBiasCurrentControlRxReplica_9_, // 398
  _RxBiasCurrentControlRxReplica_10_, // 399
  _RxBiasCurrentControlRxReplica_11_, // 400
  _RxBiasCurrentControlRxReplica_12_, // 401
  _RxBiasCurrentControlRxReplica_13_, // 402
  _RxBiasCurrentControlRxReplica_14_, // 403
  _OnlyRestoreNonPsRegs_, // 404
  _DisablePhyUpdate_, // 405
  _CalImpedanceCurrentAdjustment_, // 406
  _RxVrefDACEnable_0_, // 407
  _RxVrefDACEnable_1_, // 408
  _RxVrefDACEnable_2_, // 409
  _RxVrefDACEnable_3_, // 410
  _RxVrefDACEnable_4_, // 411
  _RxVrefDACEnable_5_, // 412
  _RxVrefDACEnable_6_, // 413
  _RxVrefDACEnable_7_, // 414
  _RxVrefDACEnable_8_, // 415
  _RxVrefDACEnable_9_, // 416
  _RxVrefDACEnable_10_, // 417
  _RxVrefDACEnable_11_, // 418
  _RxVrefDACEnable_12_, // 419
  _RxVrefDACEnable_13_, // 420
  _RxVrefDACEnable_14_, // 421
  _PsDmaRamSize_, // 422
  _TxImpedanceDqs_0_, // 423
  _TxImpedanceDqs_1_, // 424
  _TxImpedanceDqs_2_, // 425
  _TxImpedanceDqs_3_, // 426
  _TxImpedanceDqs_4_, // 427
  _TxImpedanceDqs_5_, // 428
  _TxImpedanceDqs_6_, // 429
  _TxImpedanceDqs_7_, // 430
  _TxImpedanceDqs_8_, // 431
  _TxImpedanceDqs_9_, // 432
  _TxImpedanceDqs_10_, // 433
  _TxImpedanceDqs_11_, // 434
  _TxImpedanceDqs_12_, // 435
  _TxImpedanceDqs_13_, // 436
  _TxImpedanceDqs_14_, // 437
  _PmuClockDiv_, // 438
  _TxImpedanceDTO_0_, // 439
  _TxImpedanceDTO_1_, // 440
  _TxImpedanceDTO_2_, // 441
  _TxImpedanceDTO_3_, // 442
  _TxImpedanceDTO_4_, // 443
  _TxImpedanceDTO_5_, // 444
  _TxImpedanceDTO_6_, // 445
  _TxImpedanceDTO_7_, // 446
  _TxImpedanceDTO_8_, // 447
  _TxImpedanceDTO_9_, // 448
  _TxImpedanceDTO_10_, // 449
  _TxImpedanceDTO_11_, // 450
  _TxImpedanceDTO_12_, // 451
  _TxImpedanceDTO_13_, // 452
  _TxImpedanceDTO_14_, // 453
  _EnRxDqsTracking_0_, // 454
  _EnRxDqsTracking_1_, // 455
  _EnRxDqsTracking_2_, // 456
  _EnRxDqsTracking_3_, // 457
  _EnRxDqsTracking_4_, // 458
  _EnRxDqsTracking_5_, // 459
  _EnRxDqsTracking_6_, // 460
  _EnRxDqsTracking_7_, // 461
  _EnRxDqsTracking_8_, // 462
  _EnRxDqsTracking_9_, // 463
  _EnRxDqsTracking_10_, // 464
  _EnRxDqsTracking_11_, // 465
  _EnRxDqsTracking_12_, // 466
  _EnRxDqsTracking_13_, // 467
  _EnRxDqsTracking_14_, // 468
  _OdtImpedanceCa_0_, // 469
  _OdtImpedanceCa_1_, // 470
  _OdtImpedanceCa_2_, // 471
  _OdtImpedanceCa_3_, // 472
  _OdtImpedanceCa_4_, // 473
  _OdtImpedanceCa_5_, // 474
  _OdtImpedanceCa_6_, // 475
  _OdtImpedanceCa_7_, // 476
  _OdtImpedanceCa_8_, // 477
  _OdtImpedanceCa_9_, // 478
  _OdtImpedanceCa_10_, // 479
  _OdtImpedanceCa_11_, // 480
  _OdtImpedanceCa_12_, // 481
  _OdtImpedanceCa_13_, // 482
  _OdtImpedanceCa_14_, // 483
  _DisableRetraining_, // 484
  _TxImpedanceAc_0_, // 485
  _TxImpedanceAc_1_, // 486
  _TxImpedanceAc_2_, // 487
  _TxImpedanceAc_3_, // 488
  _TxImpedanceAc_4_, // 489
  _TxImpedanceAc_5_, // 490
  _TxImpedanceAc_6_, // 491
  _TxImpedanceAc_7_, // 492
  _TxImpedanceAc_8_, // 493
  _TxImpedanceAc_9_, // 494
  _TxImpedanceAc_10_, // 495
  _TxImpedanceAc_11_, // 496
  _TxImpedanceAc_12_, // 497
  _TxImpedanceAc_13_, // 498
  _TxImpedanceAc_14_, // 499
  _RxBiasCurrentControlCk_0_, // 500
  _RxBiasCurrentControlCk_1_, // 501
  _RxBiasCurrentControlCk_2_, // 502
  _RxBiasCurrentControlCk_3_, // 503
  _RxBiasCurrentControlCk_4_, // 504
  _RxBiasCurrentControlCk_5_, // 505
  _RxBiasCurrentControlCk_6_, // 506
  _RxBiasCurrentControlCk_7_, // 507
  _RxBiasCurrentControlCk_8_, // 508
  _RxBiasCurrentControlCk_9_, // 509
  _RxBiasCurrentControlCk_10_, // 510
  _RxBiasCurrentControlCk_11_, // 511
  _RxBiasCurrentControlCk_12_, // 512
  _RxBiasCurrentControlCk_13_, // 513
  _RxBiasCurrentControlCk_14_, // 514
  _CalInterval_, // 515
  _RxClkTrackWait_, // 516
  _TrainSequenceCtrl_, // 517
  _DisableFspOp_, // 518
  _TxSlewFallDq_0_, // 519
  _TxSlewFallDq_1_, // 520
  _TxSlewFallDq_2_, // 521
  _TxSlewFallDq_3_, // 522
  _TxSlewFallDq_4_, // 523
  _TxSlewFallDq_5_, // 524
  _TxSlewFallDq_6_, // 525
  _TxSlewFallDq_7_, // 526
  _TxSlewFallDq_8_, // 527
  _TxSlewFallDq_9_, // 528
  _TxSlewFallDq_10_, // 529
  _TxSlewFallDq_11_, // 530
  _TxSlewFallDq_12_, // 531
  _TxSlewFallDq_13_, // 532
  _TxSlewFallDq_14_, // 533
  _RxBiasCurrentControlDqs_0_, // 534
  _RxBiasCurrentControlDqs_1_, // 535
  _RxBiasCurrentControlDqs_2_, // 536
  _RxBiasCurrentControlDqs_3_, // 537
  _RxBiasCurrentControlDqs_4_, // 538
  _RxBiasCurrentControlDqs_5_, // 539
  _RxBiasCurrentControlDqs_6_, // 540
  _RxBiasCurrentControlDqs_7_, // 541
  _RxBiasCurrentControlDqs_8_, // 542
  _RxBiasCurrentControlDqs_9_, // 543
  _RxBiasCurrentControlDqs_10_, // 544
  _RxBiasCurrentControlDqs_11_, // 545
  _RxBiasCurrentControlDqs_12_, // 546
  _RxBiasCurrentControlDqs_13_, // 547
  _RxBiasCurrentControlDqs_14_, // 548

  // pUserInputBasic Fields:
  _CfgPStates_, // 549
  _NumRank_dfi0_, // 550
  _Lp4xMode_, // 551
  _NumCh_, // 552
  _DimmType_, // 553
  _DramType_, // 554
  _HardMacroVer_, // 555
  _Frequency_0_, // 556
  _Frequency_1_, // 557
  _Frequency_2_, // 558
  _Frequency_3_, // 559
  _Frequency_4_, // 560
  _Frequency_5_, // 561
  _Frequency_6_, // 562
  _Frequency_7_, // 563
  _Frequency_8_, // 564
  _Frequency_9_, // 565
  _Frequency_10_, // 566
  _Frequency_11_, // 567
  _Frequency_12_, // 568
  _Frequency_13_, // 569
  _Frequency_14_, // 570
  _NumActiveDbyteDfi1_, // 571
  _NumRank_, // 572
  _DramDataWidth_, // 573
  _FirstPState_, // 574
  _PllBypass_0_, // 575
  _PllBypass_1_, // 576
  _PllBypass_2_, // 577
  _PllBypass_3_, // 578
  _PllBypass_4_, // 579
  _PllBypass_5_, // 580
  _PllBypass_6_, // 581
  _PllBypass_7_, // 582
  _PllBypass_8_, // 583
  _PllBypass_9_, // 584
  _PllBypass_10_, // 585
  _PllBypass_11_, // 586
  _PllBypass_12_, // 587
  _PllBypass_13_, // 588
  _PllBypass_14_, // 589
  _DfiFreqRatio_0_, // 590
  _DfiFreqRatio_1_, // 591
  _DfiFreqRatio_2_, // 592
  _DfiFreqRatio_3_, // 593
  _DfiFreqRatio_4_, // 594
  _DfiFreqRatio_5_, // 595
  _DfiFreqRatio_6_, // 596
  _DfiFreqRatio_7_, // 597
  _DfiFreqRatio_8_, // 598
  _DfiFreqRatio_9_, // 599
  _DfiFreqRatio_10_, // 600
  _DfiFreqRatio_11_, // 601
  _DfiFreqRatio_12_, // 602
  _DfiFreqRatio_13_, // 603
  _DfiFreqRatio_14_, // 604
  _NumRank_dfi1_, // 605
  _NumDbytesPerCh_, // 606
  _NumPStates_, // 607
  _NumActiveDbyteDfi0_, // 608

  // pUserInputSim Fields:
  _PHY_tDQS2DQ_, // 609
  _tDQSCK_, // 610
  _tDQS2DQ_, // 611
} userInputFields;

/// data structure to store register address, value pairs
typedef struct Reg_Addr_Val {

  uint32_t Address; ///< register address
  uint16_t Value;   ///< register value
} Reg_Addr_Val_t;

/// A structure to store the sequence function runtime input variables.
typedef struct runtime_config {
  int Train2D;      ///< train2d input parameter

  uint8_t initCtrl; ///< Enable skipping certain initializations steps of for debug and simulation speedup.
                    ///< Bit   | Name        | Control Setting
                    ///< ----- | ----        | ---
                    ///<     0 | progCsrSkip | When bit is set progCsrSkipTrain() function is called to program PHY registers in lieu of training firmware.
                    ///<     1 | skip_fw     | When bit is set skip execution of training firmware entirely  including skipping imem and dmem loads.
                    ///<     2 | skip_imem   | When bit is set only skip imem load
                    ///<     3 | skip_dmem   | When bit is set only skip dmem load
                    ///<     4 | skip_pie    | When bit is set skip loading PIE image.
                    ///<     5 | devinit     | When bit is set forces SequenceCtrl in messageBlock to devinit

  int skip_train;   ///< skip_train input parameter

                    ///<  - if set to 0 firmware training is executed.
                    ///<  - if set to 1 training is skipped and registers are programed to work with
                    ///<    zero board delay.
                    ///<  - if set to 2 training is skipped but firmware is executed to
                    ///<    initialize the DRAM state while registers are programed to work with zero
                    ///<    board delay.

  int debug;        ///< print debug messages
  int RetEn;        ///< Retention Enable input parameter, instructs phyinit to \n
                    ///< issue register reads during initialization to retention registers.

  uint8_t curPState;///< Internal variable representing current PState of PhyInit as it loops through
                    ///< all PStates. used by various functions.

  int curD;         ///< Represents the Current dimension of Training 1D vs 2D.

} runtime_config_t;

/// PhyInit meta structure that holds other structures
typedef struct phyinit_config {

    /// PHY Identifier when using multiple PHY's
    int CurrentPhyInst;

    ///< Represent the value stored in Step C into the register with the same name.
    int PclkPtrInitVal[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    // === Global Struct Defines === //
    /// instance of runtime objects
    runtime_config_t             runtimeConfig;
    /// instance of useInputBasic
    user_input_basic_t           userInputBasic;
    /// instance of userInputAdvanced
    user_input_advanced_t        userInputAdvanced;
    /// instance of userInputSim
    user_input_sim_t             userInputSim;

    // === Firmware Message Block Structs === //
    /// 1D message block instance
    PMU_SMB_LPDDR4_1D_t        mb_LPDDR4_1D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    /// Shadow of 1D message block. Used by PhyInit to track user changes to the data structure.
    PMU_SMB_LPDDR4_1D_t        shdw_LPDDR4_1D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    /// 2D message block instance
    PMU_SMB_LPDDR4_2D_t        mb_LPDDR4_2D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    /// Shadow of 2D message block. Used by PhyInit to track user changes to the data structure.
    PMU_SMB_LPDDR4_2D_t        shdw_LPDDR4_2D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

} phyinit_config_t;

//-------------------------------
// Global variables - defined in dwc_ddrphy_phyinit_globals.c
//-------------------------------

/*! \def MAX_NUM_RET_REGS
 *  \brief default Max number of retention registers
 *
 * This define is only used by the PhyInit Register interface to define the max
 * amount of registered that can be saved. The user may increase this variable
 * as desired if a larger number of registers need to be restored.
*/
#define MAX_NUM_RET_REGS 6000

/**  Array of Address/value pairs used to store register values for the purpose
 * of retention restore.
 */
Reg_Addr_Val_t RetRegList[MAX_NUM_RET_REGS];

//-------------------------------------------------------------
// Fixed Function prototypes
//-------------------------------------------------------------
int dwc_ddrphy_phyinit_sequence(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_sequencePsLoop(phyinit_config_t* phyctx);
int dwc_ddrphy_phyinit_restore_sequence(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_C_initPhyConfig (phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_C_initPhyConfigPsLoop (phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_D_loadIMEM(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_progCsrSkipTrain(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_progCsrSkipTrainPsLoop(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_F_loadDMEM(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_G_execFW(void);
void dwc_ddrphy_phyinit_H_readMsgBlock(int Train2D);
void dwc_ddrphy_phyinit_I_loadPIEImage(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_I_loadPIEImagePsLoop (phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_assert(int Svrty, const char *fmt,...);
void dwc_ddrphy_phyinit_cmnt(const char *fmt,...);
void dwc_ddrphy_phyinit_print(const char *fmt,...);
void dwc_ddrphy_phyinit_print_dat(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_LoadPieProdCode(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_storeMsgBlk (void *msgBlkPtr,  int sizeOfMsgBlk, int mem[]);
void dwc_ddrphy_phyinit_setDefault (phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_calcMb(phyinit_config_t* phyctx);
int  dwc_ddrphy_phyinit_storeIncvFile (char * incv_file_name, int mem[], return_offset_lastaddr_t return_type);
void dwc_ddrphy_phyinit_storeMsgBlk (void *msgBlkPtr,  int size_of_msgBlk, int mem[]);
void dwc_ddrphy_phyinit_WriteOutMem (int mem[], int mem_offset, int mem_size);
int dwc_ddrphy_phyinit_IsDbyteDisabled(phyinit_config_t* phyctx, int DbyteNumber);
int dwc_ddrphy_phyinit_getUserInput (phyinit_config_t* phyctx, char *field);
int dwc_ddrphy_phyinit_getMb (phyinit_config_t* phyctx, int ps, char *field);
int dwc_ddrphy_phyinit_setUserInput_enum (phyinit_config_t* phyctx, userInputFields field, int value);
int dwc_ddrphy_phyinit_setUserInput (phyinit_config_t* phyctx, char *field, int value);
int dwc_ddrphy_phyinit_trackReg(uint32_t adr) ;
int dwc_ddrphy_phyinit_regInterface(regInstr myRegInstr, uint32_t adr, uint16_t dat);
void dwc_ddrphy_phyinit_chkInputs (phyinit_config_t* phyctx);

extern void dwc_ddrphy_phyinit_userCustom_overrideUserInput(phyinit_config_t* phyctx);
extern void dwc_ddrphy_phyinit_userCustom_A_bringupPower(void);
extern void dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy(void);
extern void dwc_ddrphy_phyinit_userCustom_customPreTrain(phyinit_config_t* phyctx);
extern void dwc_ddrphy_phyinit_userCustom_customPreTrainPsLoop(phyinit_config_t* phyctx, int pstate);
extern void dwc_ddrphy_phyinit_userCustom_customPostTrain(phyinit_config_t* phyctx);
extern void dwc_ddrphy_phyinit_userCustom_customPostTrainPsLoop(phyinit_config_t* phyctx, int pstate);
extern int dwc_ddrphy_phyinit_userCustom_E_setDfiClk(int dfi_frequency);
extern void dwc_ddrphy_phyinit_userCustom_G_waitFwDone(void);
extern void dwc_ddrphy_phyinit_userCustom_H_readMsgBlock(int Train2D);
extern void dwc_ddrphy_phyinit_userCustom_J_enterMissionMode(void);
extern void dwc_ddrphy_phyinit_userCustom_io_write16(uint32_t adr, uint16_t dat);
void dwc_ddrphy_phyinit_io_write16(uint32_t adr, uint16_t dat);
extern uint16_t dwc_ddrphy_phyinit_userCustom_io_read16(uint32_t adr);
extern void dwc_ddrphy_phyinit_userCustom_saveRetRegs(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_ProgPPT(phyinit_config_t* phyctx);
void dwc_ddrphy_phyinit_PieFlags(phyinit_config_t* phyctx, int prog_csr);
int dwc_ddrphy_phyinit_setReg(uint32_t adr, uint16_t dat);
void dwc_ddrphy_phyinit_initReg(phyinit_config_t* ptr);
void dwc_ddrphy_phyinit_writeDmaRow();

void dwc_ddrphy_phyinit_ps_sram_init();
void dwc_ddrphy_phyinit_ps_sram_free();
void dwc_ddrphy_phyinit_setRegChkr(uint16_t *dmaWords, uint16_t row);
void dwc_ddrphy_phyinit_check_ps_sram();

#include "dwc_ddrphy_csr_ALL_cdefines.h"

