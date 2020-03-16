
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
#define IMEM_INCV_FILENAME               FW_FILES_LOC"/lpddr5/lpddr5_pmu_train_imem.incv"
#define DMEM_INCV_FILENAME               FW_FILES_LOC"/lpddr5/lpddr5_pmu_train_dmem.incv"

/*! \def IMEM_INCV_FILENAME_2D
	\brief firmware instruction memory (imem) filename for 2D training
 */
/*! \def DMEM_INCV_FILENAME_2D
	\brief firmware instruction memory (dmem) filename for 2D training.
 */
#define IMEM_INCV_FILENAME_2D            FW_FILES_LOC"/lpddr5_2d/lpddr5_2d_pmu_train_imem.incv"
#define DMEM_INCV_FILENAME_2D            FW_FILES_LOC"/lpddr5_2d/lpddr5_2d_pmu_train_dmem.incv"


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
#include "mnPmuSramMsgBlock_lpddr5.h"
#include "mnPmuSramMsgBlock_lpddr5_2d.h"


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
  _PhyMstrMaxReqToAck_0_, // 7
  _PhyMstrMaxReqToAck_1_, // 8
  _PhyMstrMaxReqToAck_2_, // 9
  _PhyMstrMaxReqToAck_3_, // 10
  _PhyMstrMaxReqToAck_4_, // 11
  _PhyMstrMaxReqToAck_5_, // 12
  _PhyMstrMaxReqToAck_6_, // 13
  _PhyMstrMaxReqToAck_7_, // 14
  _PhyMstrMaxReqToAck_8_, // 15
  _PhyMstrMaxReqToAck_9_, // 16
  _PhyMstrMaxReqToAck_10_, // 17
  _PhyMstrMaxReqToAck_11_, // 18
  _PhyMstrMaxReqToAck_12_, // 19
  _PhyMstrMaxReqToAck_13_, // 20
  _PhyMstrMaxReqToAck_14_, // 21
  _PhyMstrTrainInterval_0_, // 22
  _PhyMstrTrainInterval_1_, // 23
  _PhyMstrTrainInterval_2_, // 24
  _PhyMstrTrainInterval_3_, // 25
  _PhyMstrTrainInterval_4_, // 26
  _PhyMstrTrainInterval_5_, // 27
  _PhyMstrTrainInterval_6_, // 28
  _PhyMstrTrainInterval_7_, // 29
  _PhyMstrTrainInterval_8_, // 30
  _PhyMstrTrainInterval_9_, // 31
  _PhyMstrTrainInterval_10_, // 32
  _PhyMstrTrainInterval_11_, // 33
  _PhyMstrTrainInterval_12_, // 34
  _PhyMstrTrainInterval_13_, // 35
  _PhyMstrTrainInterval_14_, // 36
  _TxSlewFallDq_0_, // 37
  _TxSlewFallDq_1_, // 38
  _TxSlewFallDq_2_, // 39
  _TxSlewFallDq_3_, // 40
  _TxSlewFallDq_4_, // 41
  _TxSlewFallDq_5_, // 42
  _TxSlewFallDq_6_, // 43
  _TxSlewFallDq_7_, // 44
  _TxSlewFallDq_8_, // 45
  _TxSlewFallDq_9_, // 46
  _TxSlewFallDq_10_, // 47
  _TxSlewFallDq_11_, // 48
  _TxSlewFallDq_12_, // 49
  _TxSlewFallDq_13_, // 50
  _TxSlewFallDq_14_, // 51
  _RxBiasCurrentControlWck_0_, // 52
  _RxBiasCurrentControlWck_1_, // 53
  _RxBiasCurrentControlWck_2_, // 54
  _RxBiasCurrentControlWck_3_, // 55
  _RxBiasCurrentControlWck_4_, // 56
  _RxBiasCurrentControlWck_5_, // 57
  _RxBiasCurrentControlWck_6_, // 58
  _RxBiasCurrentControlWck_7_, // 59
  _RxBiasCurrentControlWck_8_, // 60
  _RxBiasCurrentControlWck_9_, // 61
  _RxBiasCurrentControlWck_10_, // 62
  _RxBiasCurrentControlWck_11_, // 63
  _RxBiasCurrentControlWck_12_, // 64
  _RxBiasCurrentControlWck_13_, // 65
  _RxBiasCurrentControlWck_14_, // 66
  _TxSlewRiseCK_0_, // 67
  _TxSlewRiseCK_1_, // 68
  _TxSlewRiseCK_2_, // 69
  _TxSlewRiseCK_3_, // 70
  _TxSlewRiseCK_4_, // 71
  _TxSlewRiseCK_5_, // 72
  _TxSlewRiseCK_6_, // 73
  _TxSlewRiseCK_7_, // 74
  _TxSlewRiseCK_8_, // 75
  _TxSlewRiseCK_9_, // 76
  _TxSlewRiseCK_10_, // 77
  _TxSlewRiseCK_11_, // 78
  _TxSlewRiseCK_12_, // 79
  _TxSlewRiseCK_13_, // 80
  _TxSlewRiseCK_14_, // 81
  _OdtImpedanceWCK_0_, // 82
  _OdtImpedanceWCK_1_, // 83
  _OdtImpedanceWCK_2_, // 84
  _OdtImpedanceWCK_3_, // 85
  _OdtImpedanceWCK_4_, // 86
  _OdtImpedanceWCK_5_, // 87
  _OdtImpedanceWCK_6_, // 88
  _OdtImpedanceWCK_7_, // 89
  _OdtImpedanceWCK_8_, // 90
  _OdtImpedanceWCK_9_, // 91
  _OdtImpedanceWCK_10_, // 92
  _OdtImpedanceWCK_11_, // 93
  _OdtImpedanceWCK_12_, // 94
  _OdtImpedanceWCK_13_, // 95
  _OdtImpedanceWCK_14_, // 96
  _RxVrefKickbackNoiseCancellation_0_, // 97
  _RxVrefKickbackNoiseCancellation_1_, // 98
  _RxVrefKickbackNoiseCancellation_2_, // 99
  _RxVrefKickbackNoiseCancellation_3_, // 100
  _RxVrefKickbackNoiseCancellation_4_, // 101
  _RxVrefKickbackNoiseCancellation_5_, // 102
  _RxVrefKickbackNoiseCancellation_6_, // 103
  _RxVrefKickbackNoiseCancellation_7_, // 104
  _RxVrefKickbackNoiseCancellation_8_, // 105
  _RxVrefKickbackNoiseCancellation_9_, // 106
  _RxVrefKickbackNoiseCancellation_10_, // 107
  _RxVrefKickbackNoiseCancellation_11_, // 108
  _RxVrefKickbackNoiseCancellation_12_, // 109
  _RxVrefKickbackNoiseCancellation_13_, // 110
  _RxVrefKickbackNoiseCancellation_14_, // 111
  _RxModeBoostVDD_0_, // 112
  _RxModeBoostVDD_1_, // 113
  _RxModeBoostVDD_2_, // 114
  _RxModeBoostVDD_3_, // 115
  _RxModeBoostVDD_4_, // 116
  _RxModeBoostVDD_5_, // 117
  _RxModeBoostVDD_6_, // 118
  _RxModeBoostVDD_7_, // 119
  _RxModeBoostVDD_8_, // 120
  _RxModeBoostVDD_9_, // 121
  _RxModeBoostVDD_10_, // 122
  _RxModeBoostVDD_11_, // 123
  _RxModeBoostVDD_12_, // 124
  _RxModeBoostVDD_13_, // 125
  _RxModeBoostVDD_14_, // 126
  _OdtImpedanceCa_0_, // 127
  _OdtImpedanceCa_1_, // 128
  _OdtImpedanceCa_2_, // 129
  _OdtImpedanceCa_3_, // 130
  _OdtImpedanceCa_4_, // 131
  _OdtImpedanceCa_5_, // 132
  _OdtImpedanceCa_6_, // 133
  _OdtImpedanceCa_7_, // 134
  _OdtImpedanceCa_8_, // 135
  _OdtImpedanceCa_9_, // 136
  _OdtImpedanceCa_10_, // 137
  _OdtImpedanceCa_11_, // 138
  _OdtImpedanceCa_12_, // 139
  _OdtImpedanceCa_13_, // 140
  _OdtImpedanceCa_14_, // 141
  _CkDisVal_0_, // 142
  _CkDisVal_1_, // 143
  _CkDisVal_2_, // 144
  _CkDisVal_3_, // 145
  _CkDisVal_4_, // 146
  _CkDisVal_5_, // 147
  _CkDisVal_6_, // 148
  _CkDisVal_7_, // 149
  _CkDisVal_8_, // 150
  _CkDisVal_9_, // 151
  _CkDisVal_10_, // 152
  _CkDisVal_11_, // 153
  _CkDisVal_12_, // 154
  _CkDisVal_13_, // 155
  _CkDisVal_14_, // 156
  _OdtImpedanceDqs_0_, // 157
  _OdtImpedanceDqs_1_, // 158
  _OdtImpedanceDqs_2_, // 159
  _OdtImpedanceDqs_3_, // 160
  _OdtImpedanceDqs_4_, // 161
  _OdtImpedanceDqs_5_, // 162
  _OdtImpedanceDqs_6_, // 163
  _OdtImpedanceDqs_7_, // 164
  _OdtImpedanceDqs_8_, // 165
  _OdtImpedanceDqs_9_, // 166
  _OdtImpedanceDqs_10_, // 167
  _OdtImpedanceDqs_11_, // 168
  _OdtImpedanceDqs_12_, // 169
  _OdtImpedanceDqs_13_, // 170
  _OdtImpedanceDqs_14_, // 171
  _DisablePmuEcc_, // 172
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
  _TxSlewFallCA_0_, // 188
  _TxSlewFallCA_1_, // 189
  _TxSlewFallCA_2_, // 190
  _TxSlewFallCA_3_, // 191
  _TxSlewFallCA_4_, // 192
  _TxSlewFallCA_5_, // 193
  _TxSlewFallCA_6_, // 194
  _TxSlewFallCA_7_, // 195
  _TxSlewFallCA_8_, // 196
  _TxSlewFallCA_9_, // 197
  _TxSlewFallCA_10_, // 198
  _TxSlewFallCA_11_, // 199
  _TxSlewFallCA_12_, // 200
  _TxSlewFallCA_13_, // 201
  _TxSlewFallCA_14_, // 202
  _TxSlewRiseWCK_0_, // 203
  _TxSlewRiseWCK_1_, // 204
  _TxSlewRiseWCK_2_, // 205
  _TxSlewRiseWCK_3_, // 206
  _TxSlewRiseWCK_4_, // 207
  _TxSlewRiseWCK_5_, // 208
  _TxSlewRiseWCK_6_, // 209
  _TxSlewRiseWCK_7_, // 210
  _TxSlewRiseWCK_8_, // 211
  _TxSlewRiseWCK_9_, // 212
  _TxSlewRiseWCK_10_, // 213
  _TxSlewRiseWCK_11_, // 214
  _TxSlewRiseWCK_12_, // 215
  _TxSlewRiseWCK_13_, // 216
  _TxSlewRiseWCK_14_, // 217
  _DisableRetraining_, // 218
  _TxSlewRiseDq_0_, // 219
  _TxSlewRiseDq_1_, // 220
  _TxSlewRiseDq_2_, // 221
  _TxSlewRiseDq_3_, // 222
  _TxSlewRiseDq_4_, // 223
  _TxSlewRiseDq_5_, // 224
  _TxSlewRiseDq_6_, // 225
  _TxSlewRiseDq_7_, // 226
  _TxSlewRiseDq_8_, // 227
  _TxSlewRiseDq_9_, // 228
  _TxSlewRiseDq_10_, // 229
  _TxSlewRiseDq_11_, // 230
  _TxSlewRiseDq_12_, // 231
  _TxSlewRiseDq_13_, // 232
  _TxSlewRiseDq_14_, // 233
  _TxImpedanceDTO_0_, // 234
  _TxImpedanceDTO_1_, // 235
  _TxImpedanceDTO_2_, // 236
  _TxImpedanceDTO_3_, // 237
  _TxImpedanceDTO_4_, // 238
  _TxImpedanceDTO_5_, // 239
  _TxImpedanceDTO_6_, // 240
  _TxImpedanceDTO_7_, // 241
  _TxImpedanceDTO_8_, // 242
  _TxImpedanceDTO_9_, // 243
  _TxImpedanceDTO_10_, // 244
  _TxImpedanceDTO_11_, // 245
  _TxImpedanceDTO_12_, // 246
  _TxImpedanceDTO_13_, // 247
  _TxImpedanceDTO_14_, // 248
  _EnRxDqsTracking_0_, // 249
  _EnRxDqsTracking_1_, // 250
  _EnRxDqsTracking_2_, // 251
  _EnRxDqsTracking_3_, // 252
  _EnRxDqsTracking_4_, // 253
  _EnRxDqsTracking_5_, // 254
  _EnRxDqsTracking_6_, // 255
  _EnRxDqsTracking_7_, // 256
  _EnRxDqsTracking_8_, // 257
  _EnRxDqsTracking_9_, // 258
  _EnRxDqsTracking_10_, // 259
  _EnRxDqsTracking_11_, // 260
  _EnRxDqsTracking_12_, // 261
  _EnRxDqsTracking_13_, // 262
  _EnRxDqsTracking_14_, // 263
  _TxSlewRiseCA_0_, // 264
  _TxSlewRiseCA_1_, // 265
  _TxSlewRiseCA_2_, // 266
  _TxSlewRiseCA_3_, // 267
  _TxSlewRiseCA_4_, // 268
  _TxSlewRiseCA_5_, // 269
  _TxSlewRiseCA_6_, // 270
  _TxSlewRiseCA_7_, // 271
  _TxSlewRiseCA_8_, // 272
  _TxSlewRiseCA_9_, // 273
  _TxSlewRiseCA_10_, // 274
  _TxSlewRiseCA_11_, // 275
  _TxSlewRiseCA_12_, // 276
  _TxSlewRiseCA_13_, // 277
  _TxSlewRiseCA_14_, // 278
  _TxImpedanceDqs_0_, // 279
  _TxImpedanceDqs_1_, // 280
  _TxImpedanceDqs_2_, // 281
  _TxImpedanceDqs_3_, // 282
  _TxImpedanceDqs_4_, // 283
  _TxImpedanceDqs_5_, // 284
  _TxImpedanceDqs_6_, // 285
  _TxImpedanceDqs_7_, // 286
  _TxImpedanceDqs_8_, // 287
  _TxImpedanceDqs_9_, // 288
  _TxImpedanceDqs_10_, // 289
  _TxImpedanceDqs_11_, // 290
  _TxImpedanceDqs_12_, // 291
  _TxImpedanceDqs_13_, // 292
  _TxImpedanceDqs_14_, // 293
  _DramByteSwap_, // 294
  _WDQSExt_, // 295
  _TxImpedanceCk_0_, // 296
  _TxImpedanceCk_1_, // 297
  _TxImpedanceCk_2_, // 298
  _TxImpedanceCk_3_, // 299
  _TxImpedanceCk_4_, // 300
  _TxImpedanceCk_5_, // 301
  _TxImpedanceCk_6_, // 302
  _TxImpedanceCk_7_, // 303
  _TxImpedanceCk_8_, // 304
  _TxImpedanceCk_9_, // 305
  _TxImpedanceCk_10_, // 306
  _TxImpedanceCk_11_, // 307
  _TxImpedanceCk_12_, // 308
  _TxImpedanceCk_13_, // 309
  _TxImpedanceCk_14_, // 310
  _OnlyRestoreNonPsRegs_, // 311
  _RxClkTrackWaitUI_, // 312
  _DisableUnusedAddrLns_, // 313
  _TxSlewRiseDqs_0_, // 314
  _TxSlewRiseDqs_1_, // 315
  _TxSlewRiseDqs_2_, // 316
  _TxSlewRiseDqs_3_, // 317
  _TxSlewRiseDqs_4_, // 318
  _TxSlewRiseDqs_5_, // 319
  _TxSlewRiseDqs_6_, // 320
  _TxSlewRiseDqs_7_, // 321
  _TxSlewRiseDqs_8_, // 322
  _TxSlewRiseDqs_9_, // 323
  _TxSlewRiseDqs_10_, // 324
  _TxSlewRiseDqs_11_, // 325
  _TxSlewRiseDqs_12_, // 326
  _TxSlewRiseDqs_13_, // 327
  _TxSlewRiseDqs_14_, // 328
  _RxClkTrackEn_0_, // 329
  _RxClkTrackEn_1_, // 330
  _RxClkTrackEn_2_, // 331
  _RxClkTrackEn_3_, // 332
  _RxClkTrackEn_4_, // 333
  _RxClkTrackEn_5_, // 334
  _RxClkTrackEn_6_, // 335
  _RxClkTrackEn_7_, // 336
  _RxClkTrackEn_8_, // 337
  _RxClkTrackEn_9_, // 338
  _RxClkTrackEn_10_, // 339
  _RxClkTrackEn_11_, // 340
  _RxClkTrackEn_12_, // 341
  _RxClkTrackEn_13_, // 342
  _RxClkTrackEn_14_, // 343
  _ExtCalResVal_, // 344
  _TxImpedanceCKE_0_, // 345
  _TxImpedanceCKE_1_, // 346
  _TxImpedanceCKE_2_, // 347
  _TxImpedanceCKE_3_, // 348
  _TxImpedanceCKE_4_, // 349
  _TxImpedanceCKE_5_, // 350
  _TxImpedanceCKE_6_, // 351
  _TxImpedanceCKE_7_, // 352
  _TxImpedanceCKE_8_, // 353
  _TxImpedanceCKE_9_, // 354
  _TxImpedanceCKE_10_, // 355
  _TxImpedanceCKE_11_, // 356
  _TxImpedanceCKE_12_, // 357
  _TxImpedanceCKE_13_, // 358
  _TxImpedanceCKE_14_, // 359
  _TxSlewFallDqs_0_, // 360
  _TxSlewFallDqs_1_, // 361
  _TxSlewFallDqs_2_, // 362
  _TxSlewFallDqs_3_, // 363
  _TxSlewFallDqs_4_, // 364
  _TxSlewFallDqs_5_, // 365
  _TxSlewFallDqs_6_, // 366
  _TxSlewFallDqs_7_, // 367
  _TxSlewFallDqs_8_, // 368
  _TxSlewFallDqs_9_, // 369
  _TxSlewFallDqs_10_, // 370
  _TxSlewFallDqs_11_, // 371
  _TxSlewFallDqs_12_, // 372
  _TxSlewFallDqs_13_, // 373
  _TxSlewFallDqs_14_, // 374
  _TxSlewFallWCK_0_, // 375
  _TxSlewFallWCK_1_, // 376
  _TxSlewFallWCK_2_, // 377
  _TxSlewFallWCK_3_, // 378
  _TxSlewFallWCK_4_, // 379
  _TxSlewFallWCK_5_, // 380
  _TxSlewFallWCK_6_, // 381
  _TxSlewFallWCK_7_, // 382
  _TxSlewFallWCK_8_, // 383
  _TxSlewFallWCK_9_, // 384
  _TxSlewFallWCK_10_, // 385
  _TxSlewFallWCK_11_, // 386
  _TxSlewFallWCK_12_, // 387
  _TxSlewFallWCK_13_, // 388
  _TxSlewFallWCK_14_, // 389
  _RxBiasCurrentControlRxReplica_0_, // 390
  _RxBiasCurrentControlRxReplica_1_, // 391
  _RxBiasCurrentControlRxReplica_2_, // 392
  _RxBiasCurrentControlRxReplica_3_, // 393
  _RxBiasCurrentControlRxReplica_4_, // 394
  _RxBiasCurrentControlRxReplica_5_, // 395
  _RxBiasCurrentControlRxReplica_6_, // 396
  _RxBiasCurrentControlRxReplica_7_, // 397
  _RxBiasCurrentControlRxReplica_8_, // 398
  _RxBiasCurrentControlRxReplica_9_, // 399
  _RxBiasCurrentControlRxReplica_10_, // 400
  _RxBiasCurrentControlRxReplica_11_, // 401
  _RxBiasCurrentControlRxReplica_12_, // 402
  _RxBiasCurrentControlRxReplica_13_, // 403
  _RxBiasCurrentControlRxReplica_14_, // 404
  _RxDqsTrackingThreshold_0_, // 405
  _RxDqsTrackingThreshold_1_, // 406
  _RxDqsTrackingThreshold_2_, // 407
  _RxDqsTrackingThreshold_3_, // 408
  _RxDqsTrackingThreshold_4_, // 409
  _RxDqsTrackingThreshold_5_, // 410
  _RxDqsTrackingThreshold_6_, // 411
  _RxDqsTrackingThreshold_7_, // 412
  _RxDqsTrackingThreshold_8_, // 413
  _RxDqsTrackingThreshold_9_, // 414
  _RxDqsTrackingThreshold_10_, // 415
  _RxDqsTrackingThreshold_11_, // 416
  _RxDqsTrackingThreshold_12_, // 417
  _RxDqsTrackingThreshold_13_, // 418
  _RxDqsTrackingThreshold_14_, // 419
  _TrainSequenceCtrl_, // 420
  _CalInterval_, // 421
  _RxVrefDACEnable_0_, // 422
  _RxVrefDACEnable_1_, // 423
  _RxVrefDACEnable_2_, // 424
  _RxVrefDACEnable_3_, // 425
  _RxVrefDACEnable_4_, // 426
  _RxVrefDACEnable_5_, // 427
  _RxVrefDACEnable_6_, // 428
  _RxVrefDACEnable_7_, // 429
  _RxVrefDACEnable_8_, // 430
  _RxVrefDACEnable_9_, // 431
  _RxVrefDACEnable_10_, // 432
  _RxVrefDACEnable_11_, // 433
  _RxVrefDACEnable_12_, // 434
  _RxVrefDACEnable_13_, // 435
  _RxVrefDACEnable_14_, // 436
  _DqsOscRunTimeSel_0_, // 437
  _DqsOscRunTimeSel_1_, // 438
  _DqsOscRunTimeSel_2_, // 439
  _DqsOscRunTimeSel_3_, // 440
  _DqsOscRunTimeSel_4_, // 441
  _DqsOscRunTimeSel_5_, // 442
  _DqsOscRunTimeSel_6_, // 443
  _DqsOscRunTimeSel_7_, // 444
  _DqsOscRunTimeSel_8_, // 445
  _DqsOscRunTimeSel_9_, // 446
  _DqsOscRunTimeSel_10_, // 447
  _DqsOscRunTimeSel_11_, // 448
  _DqsOscRunTimeSel_12_, // 449
  _DqsOscRunTimeSel_13_, // 450
  _DqsOscRunTimeSel_14_, // 451
  _TxImpedanceAc_0_, // 452
  _TxImpedanceAc_1_, // 453
  _TxImpedanceAc_2_, // 454
  _TxImpedanceAc_3_, // 455
  _TxImpedanceAc_4_, // 456
  _TxImpedanceAc_5_, // 457
  _TxImpedanceAc_6_, // 458
  _TxImpedanceAc_7_, // 459
  _TxImpedanceAc_8_, // 460
  _TxImpedanceAc_9_, // 461
  _TxImpedanceAc_10_, // 462
  _TxImpedanceAc_11_, // 463
  _TxImpedanceAc_12_, // 464
  _TxImpedanceAc_13_, // 465
  _TxImpedanceAc_14_, // 466
  _DisablePhyUpdate_, // 467
  _TxImpedanceWCK_0_, // 468
  _TxImpedanceWCK_1_, // 469
  _TxImpedanceWCK_2_, // 470
  _TxImpedanceWCK_3_, // 471
  _TxImpedanceWCK_4_, // 472
  _TxImpedanceWCK_5_, // 473
  _TxImpedanceWCK_6_, // 474
  _TxImpedanceWCK_7_, // 475
  _TxImpedanceWCK_8_, // 476
  _TxImpedanceWCK_9_, // 477
  _TxImpedanceWCK_10_, // 478
  _TxImpedanceWCK_11_, // 479
  _TxImpedanceWCK_12_, // 480
  _TxImpedanceWCK_13_, // 481
  _TxImpedanceWCK_14_, // 482
  _RxClkTrackWait_, // 483
  _OdtImpedanceDq_0_, // 484
  _OdtImpedanceDq_1_, // 485
  _OdtImpedanceDq_2_, // 486
  _OdtImpedanceDq_3_, // 487
  _OdtImpedanceDq_4_, // 488
  _OdtImpedanceDq_5_, // 489
  _OdtImpedanceDq_6_, // 490
  _OdtImpedanceDq_7_, // 491
  _OdtImpedanceDq_8_, // 492
  _OdtImpedanceDq_9_, // 493
  _OdtImpedanceDq_10_, // 494
  _OdtImpedanceDq_11_, // 495
  _OdtImpedanceDq_12_, // 496
  _OdtImpedanceDq_13_, // 497
  _OdtImpedanceDq_14_, // 498
  _EnWck2DqoTracking_0_, // 499
  _EnWck2DqoTracking_1_, // 500
  _EnWck2DqoTracking_2_, // 501
  _EnWck2DqoTracking_3_, // 502
  _EnWck2DqoTracking_4_, // 503
  _EnWck2DqoTracking_5_, // 504
  _EnWck2DqoTracking_6_, // 505
  _EnWck2DqoTracking_7_, // 506
  _EnWck2DqoTracking_8_, // 507
  _EnWck2DqoTracking_9_, // 508
  _EnWck2DqoTracking_10_, // 509
  _EnWck2DqoTracking_11_, // 510
  _EnWck2DqoTracking_12_, // 511
  _EnWck2DqoTracking_13_, // 512
  _EnWck2DqoTracking_14_, // 513
  _CalImpedanceCurrentAdjustment_, // 514
  _TxImpedanceDq_0_, // 515
  _TxImpedanceDq_1_, // 516
  _TxImpedanceDq_2_, // 517
  _TxImpedanceDq_3_, // 518
  _TxImpedanceDq_4_, // 519
  _TxImpedanceDq_5_, // 520
  _TxImpedanceDq_6_, // 521
  _TxImpedanceDq_7_, // 522
  _TxImpedanceDq_8_, // 523
  _TxImpedanceDq_9_, // 524
  _TxImpedanceDq_10_, // 525
  _TxImpedanceDq_11_, // 526
  _TxImpedanceDq_12_, // 527
  _TxImpedanceDq_13_, // 528
  _TxImpedanceDq_14_, // 529
  _RxBiasCurrentControlCk_0_, // 530
  _RxBiasCurrentControlCk_1_, // 531
  _RxBiasCurrentControlCk_2_, // 532
  _RxBiasCurrentControlCk_3_, // 533
  _RxBiasCurrentControlCk_4_, // 534
  _RxBiasCurrentControlCk_5_, // 535
  _RxBiasCurrentControlCk_6_, // 536
  _RxBiasCurrentControlCk_7_, // 537
  _RxBiasCurrentControlCk_8_, // 538
  _RxBiasCurrentControlCk_9_, // 539
  _RxBiasCurrentControlCk_10_, // 540
  _RxBiasCurrentControlCk_11_, // 541
  _RxBiasCurrentControlCk_12_, // 542
  _RxBiasCurrentControlCk_13_, // 543
  _RxBiasCurrentControlCk_14_, // 544
  _PhyMstrCtrlMode_0_, // 545
  _PhyMstrCtrlMode_1_, // 546
  _PhyMstrCtrlMode_2_, // 547
  _PhyMstrCtrlMode_3_, // 548
  _PhyMstrCtrlMode_4_, // 549
  _PhyMstrCtrlMode_5_, // 550
  _PhyMstrCtrlMode_6_, // 551
  _PhyMstrCtrlMode_7_, // 552
  _PhyMstrCtrlMode_8_, // 553
  _PhyMstrCtrlMode_9_, // 554
  _PhyMstrCtrlMode_10_, // 555
  _PhyMstrCtrlMode_11_, // 556
  _PhyMstrCtrlMode_12_, // 557
  _PhyMstrCtrlMode_13_, // 558
  _PhyMstrCtrlMode_14_, // 559
  _DisableFspOp_, // 560
  _CalOnce_, // 561
  _PmuClockDiv_, // 562
  _OdtImpedanceCk_0_, // 563
  _OdtImpedanceCk_1_, // 564
  _OdtImpedanceCk_2_, // 565
  _OdtImpedanceCk_3_, // 566
  _OdtImpedanceCk_4_, // 567
  _OdtImpedanceCk_5_, // 568
  _OdtImpedanceCk_6_, // 569
  _OdtImpedanceCk_7_, // 570
  _OdtImpedanceCk_8_, // 571
  _OdtImpedanceCk_9_, // 572
  _OdtImpedanceCk_10_, // 573
  _OdtImpedanceCk_11_, // 574
  _OdtImpedanceCk_12_, // 575
  _OdtImpedanceCk_13_, // 576
  _OdtImpedanceCk_14_, // 577
  _PsDmaRamSize_, // 578
  _RxBiasCurrentControlDqs_0_, // 579
  _RxBiasCurrentControlDqs_1_, // 580
  _RxBiasCurrentControlDqs_2_, // 581
  _RxBiasCurrentControlDqs_3_, // 582
  _RxBiasCurrentControlDqs_4_, // 583
  _RxBiasCurrentControlDqs_5_, // 584
  _RxBiasCurrentControlDqs_6_, // 585
  _RxBiasCurrentControlDqs_7_, // 586
  _RxBiasCurrentControlDqs_8_, // 587
  _RxBiasCurrentControlDqs_9_, // 588
  _RxBiasCurrentControlDqs_10_, // 589
  _RxBiasCurrentControlDqs_11_, // 590
  _RxBiasCurrentControlDqs_12_, // 591
  _RxBiasCurrentControlDqs_13_, // 592
  _RxBiasCurrentControlDqs_14_, // 593

  // pUserInputBasic Fields:
  _NumPStates_, // 594
  _NumRank_dfi0_, // 595
  _HardMacroVer_, // 596
  _NumCh_, // 597
  _DimmType_, // 598
  _DramType_, // 599
  _DfiFreqRatio_0_, // 600
  _DfiFreqRatio_1_, // 601
  _DfiFreqRatio_2_, // 602
  _DfiFreqRatio_3_, // 603
  _DfiFreqRatio_4_, // 604
  _DfiFreqRatio_5_, // 605
  _DfiFreqRatio_6_, // 606
  _DfiFreqRatio_7_, // 607
  _DfiFreqRatio_8_, // 608
  _DfiFreqRatio_9_, // 609
  _DfiFreqRatio_10_, // 610
  _DfiFreqRatio_11_, // 611
  _DfiFreqRatio_12_, // 612
  _DfiFreqRatio_13_, // 613
  _DfiFreqRatio_14_, // 614
  _FirstPState_, // 615
  _NumActiveDbyteDfi1_, // 616
  _NumRank_, // 617
  _DramDataWidth_, // 618
  _CfgPStates_, // 619
  _Frequency_0_, // 620
  _Frequency_1_, // 621
  _Frequency_2_, // 622
  _Frequency_3_, // 623
  _Frequency_4_, // 624
  _Frequency_5_, // 625
  _Frequency_6_, // 626
  _Frequency_7_, // 627
  _Frequency_8_, // 628
  _Frequency_9_, // 629
  _Frequency_10_, // 630
  _Frequency_11_, // 631
  _Frequency_12_, // 632
  _Frequency_13_, // 633
  _Frequency_14_, // 634
  _PllBypass_0_, // 635
  _PllBypass_1_, // 636
  _PllBypass_2_, // 637
  _PllBypass_3_, // 638
  _PllBypass_4_, // 639
  _PllBypass_5_, // 640
  _PllBypass_6_, // 641
  _PllBypass_7_, // 642
  _PllBypass_8_, // 643
  _PllBypass_9_, // 644
  _PllBypass_10_, // 645
  _PllBypass_11_, // 646
  _PllBypass_12_, // 647
  _PllBypass_13_, // 648
  _PllBypass_14_, // 649
  _NumRank_dfi1_, // 650
  _NumDbytesPerCh_, // 651
  _MaxNumZQ_, // 652
  _NumActiveDbyteDfi0_, // 653

  // pUserInputSim Fields:
  _tWCK2DQO_, // 654
  _tWCK2DQI_, // 655
  _tWCK2CK_, // 656
  _PHY_tDQS2DQ_, // 657
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
    PMU_SMB_LPDDR5_1D_t        mb_LPDDR5_1D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    /// Shadow of 1D message block. Used by PhyInit to track user changes to the data structure.
    PMU_SMB_LPDDR5_1D_t        shdw_LPDDR5_1D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

    /// 2D message block instance
    PMU_SMB_LPDDR5_2D_t        mb_LPDDR5_2D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];
    /// Shadow of 2D message block. Used by PhyInit to track user changes to the data structure.
    PMU_SMB_LPDDR5_2D_t        shdw_LPDDR5_2D[DWC_DDRPHY_PHYINIT_MAX_NUM_PSTATE];

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

