/**---------------------------------------------------------------------------
 * @file     emac_ephy_drv_qca_ar8031.c
 *
 * @brief    Implementation of EMAC external PHY driver for QCA AR8031
 *
 * Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include "boot_comdef.h"

#include "emac_framework.h"
#include "emac_ephy_drv_qca_ar8031.h"
#include "emac_platform.h"
#include "emac_drv.h"

/*----------------------------------------------------------------------------
 * Extern defines
 *--------------------------------------------------------------------------*/

extern EMAC_DRV drv[2];
extern uint8 ephyAddr[2];

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *--------------------------------------------------------------------------*/

#define EMAC_MDIO_MAX_WAIT         5   /* In milliseconds */
#define EMAC_QCA_MODE_MASK    0x800F   /* Mask for QCA EPHY mode */

/* QCA EPHY mode value for SGMII/Copper mode
   (see Register 0x1F,  bits [15] and [0:3] */
#define EMAC_QCA_MODE_SGMII  0x8001
#define EMAC_MII_REGS_CNT    32       /* Number of MII registers */

#define IN
#define OUT

#define EMACEphyRetryCount   100

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 *--------------------------------------------------------------------------*/

/**
 * @brief       Set EPHY speed
 *
 * @param[in]   phyAddr         External PHY address
 * @param[in]   speed           Speed in MB: 10/100/1000
 * @param[in]   isFullDuplex    Duplex mode. TRUE = Full, FALSE = Half
 * @param[in]   isAutoNeg       Auto neg enable/disable
 *
 * @return      TRUE if successful, else failed.
 */
static int Emac_EphySetSpeedQcaAR8031
(
 IN uint8   ephyIndex,
 IN uint8   phyAddr,
 IN uint32  speed,
 IN boolean isFullDuplex,
 IN boolean isAutoNeg
 )
{
  /* Note:
   * For 1000Mbps, using "forced" mode is not supported by the standard and
   * not functional with EPHY ASICs - that either fail or auto-neg anyway.
   * Therefore, enable auto-neg if 1000Mbps is required
   */
  if (1000 == speed) {
    isAutoNeg = TRUE;
  }

  if (FALSE == isAutoNeg) {
    uint16 valReg0  = 0;    /* Reg  0: Control Reg */

    valReg0 = 0x8000;       /* Reg0: SW reset */
    switch (speed) {
      case 10:
        valReg0  |= 0x0000; /* Reg0: force 10Mbps */
        break;
      case 100:
        valReg0  |= 0x2000; /* Reg0: force 100Mbps */
        break;
      case 1000: /* Note comment above about need of auto-neg */
        valReg0  |= 0x0040; /* Reg0: force 1000Mbps */
        break;
      default:
        EMAC_PRINT_1("Invalid speed %u\n", speed);
        return FALSE;   /* Failure */
    }

    /* Set duplex mode */
    if (TRUE == isFullDuplex) {
      valReg0 |= 0x0100; /* Mark full duplex */
    }

    /* Write Register 0 */
    if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  0, valReg0)) {
      return FALSE;   /* Failure */
    }

    /* Sleep after speed change */
    Emac_SleepMS(700);
  }
  else /* (TRUE == isAutoNeg) */ {
    uint16 valReg0  = 0;  /* Reg  0: Control Register */
    uint16 valReg4  = 0;  /* Reg  4: Auto-Neg Advertisement Register */
    uint16 valReg9  = 0;  /* Reg  9: 1000BASE-T Control Register */
    uint16 valReg20 = 0;

    /* Disable "SmartSpeed" - by default it is on.
     * See QCA data sheet, section 2.4.8
     */
    if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 20, &valReg20)) {
      return FALSE;   /* Failure */
    }
    valReg20 &= ~0x20;

    /* Reg0: SW reset, Auto-Neg, Restart Auto-Neg */
    valReg0 = 0x8000 | 0x1000 | 0x0200;

    /* Reg4: Selector Field mode = 802.3 */
    valReg4 = 0x1;

    valReg4 |= 0x0040;  /* Reg4: 10BASE-TX Full Duplex */
    valReg4 |= 0x0020;  /* Reg4: 10BASE-TX Half Duplex */
    valReg4 |= 0x0100;  /* Reg4: 100BASE-TX Full-Duplex */
    valReg4 |= 0x0080;  /* Reg4: 100BASE-TX Half-Duplex */
    valReg9 |= 0x0200;  /* Reg9: 1000BASE-T Full-Duplex, Auto MASTER/SLAVE config */

    if ((TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  4, valReg4)) ||
        (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  9, valReg9)) ||
        (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 20, valReg20)) ||
        (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  0, valReg0))) {
      return FALSE;   /* Failure */
    }

    uint32 retryCount = EMACEphyRetryCount;
    do {
      if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0, &valReg0)) {
        return FALSE;   /* Failure */
      }
      Emac_SleepMS(10);
    } while (valReg0 & 0x8000 && (retryCount--) > 0);

    if(retryCount == 0){
      return FALSE;
    }

    /* Sleep after speed change */
    Emac_SleepMS(20);
  }

  return TRUE;        /* Success */
}

/**
 * @brief       Set EPHY to MAC interface loopback mode
 *
 * @param[in]   phyAddr         External PHY address
 * @param[in]   speed           Speed in MB: 10/100/1000
 *
 * @return      TRUE if successful, else failed.
 */
static int Emac_EphySetMacIfaceLoopbackQcaAR8031
(
 IN uint8   ephyIndex,
 IN uint8   phyAddr,
 IN uint32  speed
 )
{
  uint16 value = 0;
  uint32 result = FALSE;

  /* Set the speed */
  if (TRUE != Emac_EphySetSpeedQcaAR8031(ephyIndex, phyAddr, speed, TRUE, FALSE)) {
    return FALSE;   /* Failure */
  }

  /* Turn on loopback for the requested speed */
  if (10 == speed) {
    value = 0x4100; /* Reg0=0x4100 (enable 10Mbps loopback) */
  }
  else if (100 == speed) {
    value = 0x6100; /* Reg0=0x6100 (enable 100Mbps loopback) */
  }
  else if (1000 == speed) {
    value = 0x4140; /* Reg0=0x4140 (enable 1000Mbps loopback) */
  }

  /* else: valid speed already checked by setSpeed API */
  result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0, value);
  if (TRUE == result) {
    EMAC_PRINT_0("EPHY MAC I/F loopback mode activated\n");
  }

  Emac_SleepMS(50);

  return result;
}

/**
 * @brief       Set EPHY to external stub loopback mode
 *
 * @param[in]   phyAddr   External PHY address
 * @param[in]   speed     Speed in MB: 10/100/1000
 *
 * @return      TRUE if successful, else failed.
 */
static int Emac_EphySetExtStubLoopbackQcaAR8031
(
 IN uint8   ephyIndex,
 IN uint8   phyAddr,
 IN uint32  speed
 )
{
  uint16 value = 0;
  uint32 result = FALSE;

  EMAC_PRINT_2("ExtStubLoopbackQcaAR8031(addr %d): speed %d\r\n", phyAddr, speed );

  /* For detailed procedure, see AR8031 data sheet section 2.5.2 */

  /* Step 1: set debug register bit 0xB[15] to 0 to disable hibernate
   *         (power saving) mode
   * Write debug offset address to 0x1D
   * Read/write the data from/to 0x1E
   */
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1D, 0xB)) {
    return FALSE;   /* Failure */
  }
  if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0x1E, &value)) {
    return FALSE;   /* Failure */
  }
  value &= ~(0x8000);
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1D, 0xB)) {
    return FALSE;   /* Failure */
  }
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1E, value)) {
    return FALSE;   /* Failure */
  }

  /* Step 2: set debug register bit 0x11[0] to 1 to enable external
   *         loopback
   */
  value = 0;
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1D, 0x11)) {
    return FALSE;   /* Failure */
  }
  if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0x1E, &value)) {
    return FALSE;   /* Failure */
  }
  value |= 0x0001;
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1D, 0x11)) {
    return FALSE;   /* Failure */
  }
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1E, value)) {
    return FALSE;   /* Failure */
  }

  /* Step 3: set register 0x0 to select loopback modes */
  if (10 == speed)    /* 10Mbps loopback */ {
    /* Reg0=0x8100 (force 10Mbps full-duplex + SW reset) */
    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0, 0x8100);
  }
  else if (100 == speed)    /* 100Mbps loopback */ {
    /* Reg0=0xA100 (force 100Mbps full-duplex + SW reset) */
    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0, 0xA100);
  }
  else if (1000 == speed)   /* 1000Mbps loopback */ {
    /* Reg0=0x8140 (force 1000Mbps full-duplex + SW reset) */
    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0, 0x8140);
  }
  else {
    EMAC_PRINT_1("Invalid speed %u\r\n", speed);
    result = FALSE;
  }

  if (TRUE == result) {
    EMAC_PRINT_0("EPHY STUB (External Cable) loopback mode activated\r\n");
  }

  return result;
}

/**
 * @brief       Set EPHY to copper line loopback mode
 *
 * @param[in]   phyAddr         External PHY address
 * @param[in]   speed           Speed in MB: 10/100/1000
 *
 * @return      TRUE if successful, else failed.
 */
static int Emac_EphySetLineLoopbackQcaAR8031
(
 IN uint8   ephyIndex,
 IN uint8   phyAddr,
 IN uint32  speed
)
{
  uint32 result = FALSE;
  uint16 value = 0xFFFF;

  /* Set the speed */
  if (TRUE != Emac_EphySetSpeedQcaAR8031(ephyIndex, phyAddr, speed, TRUE, FALSE)) {
    return FALSE;   /* Failure */
  }

  /* Disable interrupts (Reg18 = 0x0000) */
  result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 18, 0x0000);
  if (TRUE == result) {
    /* Set Remote PHY line loopback
     * See AR8031 data sheet section 2.5.3
     * Set MMD3 register bit 0x805A[0] to 1.
     */
    /* Step 1: Write 0x3 to register 0xD: 0xD = 0x0003
     *         (function = address; set the device address to MMD3)
     * Step 2: Write 0x805A to register 0xE: 0xE = 0x805A
     *         (set the register offset address)
     * Step 3: Write 0x4003 to register 0xD: 0xD=0x4003;
     *         (function = data; keep the device address) // keep REGISTER address ???
     * Step 4: Read register 0xE: 0xE == (data from register
     *         0x805A of MMD3)
     * Step 5: Prepare value to be written, set bit 0
     * Step 6: Write value to register 0xE: 0xE = 0x0001
     *         (write value to register 0x805A of MMD3)
     */
    if ((TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xD, 0x0003)) &&
        (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xE, 0x805A)) &&
        (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xD, 0x4003)) &&
        (TRUE == Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0xE, &value))) {
      value |= 0x0001;
      result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xE, value);
    }
  }

  if (TRUE == result) {
    EMAC_PRINT_0("EPHY LINE (Remote PHY) loopback mode activated\n");
  }

  return result;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 *--------------------------------------------------------------------------*/
/**
 * @brief       Initialize driver
 *
 * @param[in]   cfg    External PHY Driver configuration
 *
 * @return  TRUE if successful, else failed.
 */
int Emac_EphyInitQcaAR8031
(
  uint8 ephyIndex, 
  const EMAC_EPHY_CFG *cfg
)
{
  int result = FALSE;
  const uint8 phyAddr = ephyAddr[ephyIndex];
  uint16 value = 0;

  EMAC_PRINT_1("Init EPHY on address %u\r\n", phyAddr);

  /* Apply SW reset to clear possible settings before configuring */
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  0, 0x8000)) {
    return FALSE;   /* Failure */
  }

  uint32 retryCount = EMACEphyRetryCount;
  do {
    if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0, &value)) {
      return FALSE;   /* Failure */
    }
    Emac_SleepMS(10);
  } while (value & 0x8000 && (retryCount--) > 0);

  if (retryCount == 0) {
    return FALSE;
  }

  value = 0;

  /* Set debug register bit 0xB[15] to 0 to disable hibernate
   * (power saving) mode
   * Write debug offset address to 0x1D
   * Read/write the data from/to 0x1E
   */
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1D, 0xB)) {
    return FALSE;   /* Failure */
  }
  if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0x1E, &value)) {
    return FALSE;   /* Failure */
  }
  value &= ~(0x8000);
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1D, 0xB)) {
    return FALSE;   /* Failure */
  }
  if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1E, value)) {
    return FALSE;   /* Failure */
  }

  /* Write SGMII Control Register 1, MMD7, Offset: 0x8005 (Hex)
   * Set bit 15 (SERDES hibernation) to zero (disable)
   */
  /* Step 1: Write 0x7 to register 0xD: 0xD = 0x0007
   *         (function = address; set the device address to MMD7)
   * Step 2: Write 0x8005 to register 0xE: 0xE = 0x8005
   *         (set the register offset address)
   * Step 3: Write 0x4007 to register 0xD: 0xD=0x4007;
   *         (function = data; keep the device address) // keep REGISTER address ???
   * Step 4: Read register 0xE: 0xE == (data from register
   *         0x8005 of MMD7)
   * Step 5: Prepare value to be written, set bit 15
   * Step 6: Write value to register 0xE: 0xE = 0x0001
   *         (write value to register 0x8005 of MMD7)
   */
  if ((TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xD, 0x0007)) &&
      (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xE, 0x8005)) &&
      (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xD, 0x4007)) &&
      (TRUE == Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0xE, &value))) {
    value &= ~(0x8000);
    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0xE, value);
    if (TRUE != result) {
      return FALSE;   /* Failure */
    }
  }

  /*
   * Verify QCA EPHY is configured to SGMII/Copper mode. If not - set manually
   */
  if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0x1F, &value)) {
    return FALSE;   /* Failure */
  }
  if (EMAC_QCA_MODE_SGMII != (value & EMAC_QCA_MODE_MASK)) {
    EMAC_PRINT_1("QCA EPHY not set to SGMII/Copper mode (val=0x%04X)\r\n", value);

    /* Turn relevant bits for SGMII/Copper mode */
    EMAC_PRINT_0("Setting mode manually...\r\n");
    value |= EMAC_QCA_MODE_SGMII;
    if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0x1F, value)) {
      return FALSE;   /* Failure */
    }

    /* Verify correct value was set */
    value = 0;
    if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 0x1F, &value)) {
      return FALSE;   /* Failure */
    }
    if (EMAC_QCA_MODE_SGMII != (value & EMAC_QCA_MODE_MASK)) {
      EMAC_PRINT_1("Failed (val=0x%04X)\r\n", value);
      return FALSE;
    }

    EMAC_PRINT_0("Succeeded.\r\n");
  }

  /* Handle loopback modes */
  switch (cfg->modeLoopback) {
    case EMAC_LB_MAC:
    case EMAC_LB_PHY_DIG:
    case EMAC_LB_PHY_SERDES:
      /* No special handling needed, handle same as no loopback */
      /* FALL THROUGH */

    case EMAC_LB_NONE:
      /* Set the speed */
      result = Emac_EphySetSpeedQcaAR8031(
          ephyIndex, phyAddr, cfg->speed, cfg->isFullDuplex, cfg->isAutoNeg);
      break;

    case EMAC_LB_EPHY_MAC_IF:
      result = Emac_EphySetMacIfaceLoopbackQcaAR8031(
          ephyIndex, phyAddr, cfg->speed);
      break;

    case EMAC_LB_EPHY_EXT_STUB:
      result = Emac_EphySetExtStubLoopbackQcaAR8031(
          ephyIndex, phyAddr, cfg->speed);
      break;

    case EMAC_LB_EPHY_LINE:
      result = Emac_EphySetLineLoopbackQcaAR8031( 
          ephyIndex, phyAddr, cfg->speed);
      break;

    default:
      EMAC_PRINT_1("Invalid EPHY loopback mode %u\n", cfg->modeLoopback);
      result = FALSE;
      break;
  }

  return result;
}

/**
 * @brief       Cleanup driver
 */
void Emac_EphyCleanupQcaAR8031
(
  IN uint8 ephyIndex
)
{
  Emac_EphyHwReset(ephyIndex);
}

/**
 * @brief       Read an MII register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[out]  regData   Pointer to register data to be read
 *
 * @return  TRUE if successful, else failed
 */
int Emac_EphyReadMiiRegQcaAR8031
(
 IN uint8   ephyIndex,
 IN uint8   devAddr,
 IN uint8   regAddr,
 IN uint16 *regData
 )
{
  uint32 cnt;

  if (NULL == regData || ((ephyIndex != 0) && (ephyIndex != 1))) {
    EMAC_PRINT_0("NULL parameter\r\n");
    return FALSE;   /* Failure */
  }

  *regData = 0xFFFF;

  /* Set device address */
  if(ephyIndex == 0)
    HWIO_OUTF(EMAC_REG_PRE(PHY_STS), PHY_ADDR, devAddr);
  else
    HWIO_OUTF(EMAC_REG_PRE1(PHY_STS), PHY_ADDR, devAddr);

  Emac_SleepMS(1);

  /* Start read operation */
  if(ephyIndex == 0){
      HWIO_OUTF3(EMAC_REG_PRE(MDIO_CTRL),
          MDIO_RD_NWR, MDIO_REG_ADDR, MDIO_START,
          1,           regAddr,       1);
  }
  else{
      HWIO_OUTF3(EMAC_REG_PRE1(MDIO_CTRL),
          MDIO_RD_NWR, MDIO_REG_ADDR, MDIO_START,
          1,           regAddr,       1);
  }

  /* Wait until done. With slowest clock should take about 1.28ms */
  for (cnt = 0; cnt < EMAC_MDIO_MAX_WAIT; cnt++) {
    /* It takes few MDIO clock cycles for MDIO_BUSY to be set after MDIO
     * operation is started. With slow clock we might read zero MDIO_BUSY
     * and assume that operation is done before it even started, so allow
     * some delay before checking for the first time
     */
    Emac_SleepMS(1);

    if(ephyIndex == 0){
        if (0 == HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_BUSY)) {
          /* Done, read data */
          *regData = HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_DATA);
          return TRUE;       /* Success */
        }
    }
    else{
        if (0 == HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_BUSY)) {
          /* Done, read data */
          *regData = HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_DATA);
          return TRUE;       /* Success */
        }
    }
  }

  EMAC_PRINT_0("EPHY read failed, MDIO busy\r\n");

  return FALSE;   /* Failure */
}

/**
 * @brief       Write an external PHY register via MDIO
 *
 * @param[in]   devAddr   Device address
 * @param[in]   regAddr   Register address
 * @param[in]   regData   Register data to write
 *
 * @return  TRUE if successful, else failed
 */
int Emac_EphyWriteMiiRegQcaAR8031
(
 IN uint8  ephyIndex,
 IN uint8  devAddr,
 IN uint8  regAddr,
 IN uint16 regData
)
{
  uint32 cnt;

  if(ephyIndex != 0 && ephyIndex != 1){
      EMAC_PRINT_0("Invalid ephy index\r\n");
      return FALSE;  /* Failure */
  }

  if(ephyIndex == 0){
      /* Set device address */
      HWIO_OUTF(EMAC_REG_PRE(PHY_STS), PHY_ADDR, devAddr);
      HWIO_OUTF5(EMAC_REG_PRE(MDIO_CTRL),
          MDIO_MODE, MDIO_PR, MDIO_AP_EN, MDIO_CLK_SEL, SUP_PREAMBLE,
          0,         0,       0,          0,            1);
  }
  else{
      /* Set device address */
      HWIO_OUTF(EMAC_REG_PRE1(PHY_STS), PHY_ADDR, devAddr);
      HWIO_OUTF5(EMAC_REG_PRE1(MDIO_CTRL),
          MDIO_MODE, MDIO_PR, MDIO_AP_EN, MDIO_CLK_SEL, SUP_PREAMBLE,
          0,         0,       0,          0,            1);
  }

  Emac_SleepMS(1);

  /* Start write operation */
  if(ephyIndex == 0){
      HWIO_OUTF4(EMAC_REG_PRE(MDIO_CTRL),
          MDIO_RD_NWR, MDIO_REG_ADDR, MDIO_START, MDIO_DATA,
          0,           regAddr,       1,          regData);
  }
  else{
      HWIO_OUTF4(EMAC_REG_PRE1(MDIO_CTRL),
          MDIO_RD_NWR, MDIO_REG_ADDR, MDIO_START, MDIO_DATA,
          0,           regAddr,       1,          regData);
  }

  /* Wait until done. With slowest clock should take about 1.28ms */
  for (cnt = 0; cnt < EMAC_MDIO_MAX_WAIT; cnt++) {
    /* It takes few MDIO clock cycles for MDIO_BUSY to be set after MDIO
     * operation is started. With slow clock we might read zero MDIO_BUSY
     * and assume that operation is done before it even started, so allow
     * some delay before checking for the first time
     */
    Emac_SleepMS(1);
    if(ephyIndex == 0){
        if (0 == HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_BUSY)) {
          return TRUE;       /* Success */
        }
    }
    else{
        if (0 == HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_BUSY)) {
          return TRUE;       /* Success */
        }
    }
  }

  EMAC_PRINT_0("EPHY write failed, MDIO busy\r\n");

  return FALSE;   /* Failure */
}

/**
 * @brief       Get real-time link status
 *
 * @param[out]  isLinkUp  will be set to TRUE if link is up, FALSE otherwise
 *
 * @return      TRUE if successful, else failed
 */
int Emac_EphyIsLinkUpQcaAR8031
(
 IN uint8 ephyIndex,
 OUT boolean *isLinkUp
)
{
  uint16 valReg17 = 0;
  const uint8 phyAddr = ephyAddr[ephyIndex];

  if (NULL == isLinkUp) {
    EMAC_PRINT_0("NULL parameter\r\n");
    return FALSE;   /* Failure */
  }

  /* Read PHY-Specific Status Register 17 */
  if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 17, &valReg17)) {
    EMAC_PRINT_0("Failed to read PHY-Specific Status Register\r\n");
    *isLinkUp = FALSE;
    return FALSE;   /* Failure */
  }

  /* Check bit 10 for real-time link status */
  if (0 == (valReg17 & (1 << 10))) {
    *isLinkUp = FALSE;
  }
  else {
    *isLinkUp = TRUE;
  }

  return TRUE;       /* Success */
}

/**
 * @brief       Get duplex and speed from ephy
 *
 * @param[out]  speed             10/100/1000 Mbps
 * @param[out]  isFullDuplex      set TRUE if is full duplex
 *
 * @return      TRUE if successful, else failed
 */
int Emac_EphyGetSpeedAndDuplexQcaAR8031
(
 IN uint8 ephyIndex,
 OUT uint32  *speed,
 OUT boolean *isFullDuplex
)
{
  uint16 valReg17;
  const uint8 phyAddr = ephyAddr[ephyIndex];

  if (NULL == speed || NULL == isFullDuplex)
  {
    EMAC_PRINT_0("NULL parameter\r\n");
    return FALSE;   /* Failure */
  }

  if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 17, &valReg17))
  {
    return FALSE;   /* Failure */
  }

  /* Check bit 10 for real-time link status */
  if (0 == (valReg17 & (1 << 10)))
  {
    EMAC_PRINT_0("Link is down\r\n");
    return FALSE;   /* Failure */
  }

  /* Register 17 bit 11 is set if speed is resolved. The bit is set when
   *      * Auto-Negotiation is completed or Auto-Negotiation is disabled
   *           */
  if (0 == (valReg17 & (1 << 11)))
  {
    EMAC_PRINT_0("Link is up, but speed not resolved\r\n");
    return FALSE;   /* Failure */
  }

  /* Register 17 bits [14:15] mark the speed, both is resolved from
   *      * Auto-Negotiation or Auto-Negotiation is disabled
   *           */
  if (0x0000 == (valReg17 & 0xC000))      /* Bits [14:15] = '00' */
  {
    *speed = 10;
  }
  else if (0x4000 == (valReg17 & 0xC000)) /* Bits [14:15] = '01' */
  {
    *speed = 100;
  }
  else if (0x8000 == (valReg17 & 0xC000)) /* Bits [14:15] = '10' */
  {
    *speed = 1000;
  }
  else
  {
    EMAC_PRINT_0("Invalid speed register value\r\n");
    return FALSE;   /* Failure */
  }

  /* Register 17 bit 13 is set if full duplex */
  if (0 != (valReg17 & (1 << 13)))
  {
    *isFullDuplex = TRUE;
  }
  else
  {
    *isFullDuplex = FALSE;
  }

  return TRUE;       /* Success */
}

