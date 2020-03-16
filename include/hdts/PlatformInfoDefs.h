#ifndef PLATFORMINFODEFS_H
#define PLATFORMINFODEFS_H

/**
  @file PlatformInfo.c

  Public definitions for the PlatformInfo driver.
*/
/*
  ====================================================================

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2013-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ====================================================================


  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include <Uefi.h>
#include "com_dtypes.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

/**
  @addtogroup platform_info
  @{
*/

/**
 * Generate a platform version number.
 *
 * This macro generates the platform version number from the specified
 * major and minor numbers. For example, version 1.2 is represented by
 * @code DALPLATORMINFO_VERSION(1,2) @endcode
 *
*/
#define DALPLATFORMINFO_VERSION(major, minor)  (((major) << 4) | (minor))


/**
  Target type of the device on which the platform is running.
 */
typedef enum
{
  DALPLATFORMINFO_TYPE_UNKNOWN      = 0x00,  /**< Unknown target device. */
  DALPLATFORMINFO_TYPE_RUMI         = 0x0F,  /**< Target is on RUMI. */
  DALPLATFORMINFO_TYPE_VIRTIO       = 0x10,  /**< Target is on VIRTIO. */
  DALPLATFORMINFO_TYPE_CRB          = 0x1A,  /**< Target is a CRB device. */
  DALPLATFORMINFO_TYPE_SDP          = 0x1B,  /**< Target is a SDP device. */

  DALPLATFORMINFO_NUM_TYPES, /**< Number of known targets (including unknown). */
  /** @cond */
  DALPLATFORMINFO_TYPE_8BITS        = 0x7F
  /** @endcond */
} DalPlatformInfoPlatformType;


/**
 * Keys to get data out of the CDT.
 */
typedef enum
{
  DALPLATFORMINFO_KEY_UNKNOWN       = 0x00,
  DALPLATFORMINFO_KEY_DDR_FREQ      = 0x01,
  DALPLATFORMINFO_KEY_GFX_FREQ      = 0x02,
  DALPLATFORMINFO_KEY_CAMERA_FREQ   = 0x03,
  DALPLATFORMINFO_KEY_REVISION      = 0x04,
  DALPLATFORMINFO_KEY_CUST          = 0x05,

  DALPLATFORMINFO_NUM_KEYS          = 0x06,

  /** @cond */
  DALPLATFORMINFO_KEY_32BITS  = 0x7FFFFFFF
  /** @endcond */
} DalPlatformInfoKeyType;


/**
  @brief Stores the target platform, the platform version, and the
  platform subtype.
 */
typedef struct
{
  DalPlatformInfoPlatformType     platform;   /**< Type of the current target. */
  uint32                          version;    /**< Version of the platform in use. */
  uint32                          subtype;    /**< Sub-type of the platform. */
  uint32                          revision;   /**< Revision of the platform. */
} DalPlatformInfoPlatformInfoType;


/**
  Format of the DalPlatformInfoSMemType structure. Minor revision ticks
  are backwards compatible.
 */
#define DALPLATFORMINFO_SMEM_FORMAT DALPLATFORMINFO_VERSION(0, 11)


/**
  Length of the build ID buffer in DalPlatformInfoSMemType.
 */
#define DALPLATFORMINFO_SMEM_BUILD_ID_LENGTH 32


/**
  Maximum number of PMIC devices in DalPlatformInfoSMemType.
 */
#define DALPLATFORMINFO_SMEM_MAX_PMIC_DEVICES 3


/**
  @brief SMEM structure for PMIC information.
*/
typedef struct DalPlatformInfoSMemPMICType
{
  uint32         nPMICModel;       /**< PMIC device model type, for Badger matches the revision id subtype */
  uint32         nPMICVersion;     /**< PMIC version, same format as Platform version */
} DalPlatformInfoSMemPMICType;


/**
  @brief Structure for the shared memory location which is used to store
  platform, chip, build, and pmic information.
 */
typedef struct
{
  uint32                          nFormat;          /**< Format of the structure. */
  uint32                          eChipId;          /**< Chip ID. */
  uint32                          nChipVersion;     /**< Chip version. */
  char                            aBuildId[DALPLATFORMINFO_SMEM_BUILD_ID_LENGTH];
                                                    /**< Build ID. */
  uint32                          nRawChipId;       /**< Raw chip ID. */
  uint32                          nRawChipVersion;  /**< Raw chip version. */
  DalPlatformInfoPlatformType     ePlatformType;    /**< Platform type. */
  uint32                          nPlatformVersion; /**< Platform version. */
  uint32                          nRevision;        /**< Platform revision. */
  uint32                          nPlatformSubtype; /**< Platform subtype. */
  DalPlatformInfoSMemPMICType     aPMICInfo[DALPLATFORMINFO_SMEM_MAX_PMIC_DEVICES];
                                                    /**< DEPRECATED. May not contain the full
                                                         list. Use array at nPMICArrayOffset instead. */
  uint32                          nFoundryId;       /**< Chip foundry ID. */
  uint32                          nChipSerial;      /**< Chip serial number. */
  uint32                          nNumPMICs;        /**< Number of PMICs in array. */
  uint32                          nPMICArrayOffset; /**< Offset from base of structure to
                                                         array of DalPlatformInfoSMemPMICType. */
  UINT32                          nDramSizeMB;
} DalPlatformInfoSMemType;

EFI_STATUS PlatformInfo_Init(VOID);

/** @} */ /* end_addtogroup platform_info */

#endif
