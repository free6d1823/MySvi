/**---------------------------------------------------------------------------
 * @file     emac_ephy_drv_marvell_88e1111.c
 *
 * @brief    Implementation of EMAC external PHY driver for Marvell 88E1111
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/

#include "boot_comdef.h"
#include "emac_ephy_drv_marvell_88e1111.h"
#include "emac_drv.h"
#include "emac_ephy.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *--------------------------------------------------------------------------*/

#define EMAC_MDIO_MAX_WAIT        5    /**< In milliseconds */
#define EMAC_MII_REGS_CNT         32   /**< Number of MII registers */
#define EMAC_TEST_MODES_CNT       4    /**< Number of possible test modes */
#define EMAC_TEST_MODE_ARR_SIZE   32   /**< Array size for test mode init sequence */

extern uint8 ephyAddr[2];

/*----------------------------------------------------------------------------
 * Type Declarations
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 *--------------------------------------------------------------------------*/

/**
  set Led behavior
 */
int EmacEphySetLedBehavior (
    uint8 ephyIndex,
    uint8   phyAddr
)
{
  int result = FALSE;
  uint16 ValueReg16 = 0;

  /* Change LEDs behaviors as hardware designed */
  result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 22, 0x3);
  if(!result)
    return result;

  result = Emac_EphyReadMiiReg(ephyIndex, phyAddr, 16, &ValueReg16);
  if(!result)
    return result;

  result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 16, 0x0177);
  if(!result)
    return result;

  result = Emac_EphyReadMiiReg(ephyIndex, phyAddr, 16, &ValueReg16);
  if(!result)
    return result;

  result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 22, 0x0);

  return result;
}

/*
 * @brief       Set EPHY speed
 *
 * @param[in]   phyAddr         External PHY address
 * @param[in]   speed           Speed in MB: 10/100/1000
 * @param[in]   isFullDuplex    Duplex mode. TRUE = Full, FALSE = Half
 * @param[in]   isAutoNeg       Auto neg enable/disable
 *
 * @return  TRUE if successful, else failed.
 */
int emac_ephy_setSpeed_marvell_88e1111
(
    uint8   ephyIndex,
    uint8   phyAddr,
    uint32  speed,
    boolean isFullDuplex,
    boolean isAutoNeg
)
{
    /* Note:
     * For 1000Mbps, using "forced" mode is not supported by the standard and
     * not functional with EPHY ASICs - that either fail or auto-neg anyway.
     * Therefore, enable auto-neg if 1000Mbps is required
     */
    if (1000 == speed)
    {
        isAutoNeg = TRUE;
    }

    if (FALSE == isAutoNeg)
    {
        uint16 valReg0  = 0; /* Reg  0: Control Reg */
        uint16 valReg20 = 0; /* Reg 20: Extended PHY Specific Control Reg */

        /* Read Reg 20 and mask bits 6:4 */
        if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 20, &valReg20))
        {
            return FALSE;   /* Failure */
        }
        valReg20 &= ~0x70;

        valReg0 = 0x8000;       /* Reg0: SW reset */
        switch (speed)
        {
        case 10:
            valReg20 |= 0x0;    /* Reg20.6:4='000': MAC i/f clk for 10Mbps */
            valReg0  |= 0x0000; /* Reg0: force 10Mbps */
            break;
        case 100:
            valReg20 |= 0x10;   /* Reg20.6:4='001': MAC i/f clk for 100Mbps */
            valReg0  |= 0x2000; /* Reg0: force 100Mbps */
            break;
        case 1000: /* Note comment above about need of auto-neg */
            valReg20 |= 0x30;   /* Reg20.6:4='011': MAC i/f clk for 1000Mbps */
            valReg0  |= 0x0040; /* Reg0: force 1000Mbps */
            break;
        default:
            EMAC_PRINT_1("Invalid speed %u\r\n", speed);
            return FALSE;   /* Failure */
        }

        /* Set duplex mode */
        if (TRUE == isFullDuplex)
        {
            valReg0 |= 0x0100; /* Mark full duplex */
        }

        if ((TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 20, valReg20)) ||
            (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  0, valReg0 )))
        {
            return FALSE;   /* Failure */
        }

        /* Sleep after speed change (see release notes section 4.32) */
        // TODO: per the above section, probably not needed for 1000Mbps?
        Emac_SleepMS(700);
    }
    else /* (TRUE == isAutoNeg) */
    {
        uint16 valReg0  = 0;  /* Reg  0: Control Register */
        uint16 valReg4  = 0;  /* Reg  4: Auto-Neg Advertisement Register */
        uint16 valReg9  = 0;  /* Reg  9: 1000BASE-T Control Register */
        uint16 valReg20 = 0;

        /* Disable "Downshift Feature" to make sure - though by default it is OFF.
         * See Marvell data sheet, section 2.13
         */
        if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 20, &valReg20))
        {
            return FALSE;   /* Failure */
        }
        valReg20 &= ~0x0100;

        /* Reg0: SW reset, Auto-Neg, Restart Auto-Neg */
        valReg0 = 0x8000 | 0x1000 | 0x0200;

        /* Reg4: Selector Field mode = 802.3 */
        valReg4 = 0x1;

        valReg4 |= 0x0040; /* Reg4: 10BASE-TX Full Duplex */
        valReg4 |= 0x0020; /* Reg4: 10BASE-TX Half Duplex */
        valReg4 |= 0x0100; /* Reg4: 100BASE-TX Full-Duplex */
        valReg4 |= 0x0080; /* Reg4: 100BASE-TX Half-Duplex */

        //if (TRUE == isFlowControl)
        //{
        //    /* Reg4: Asymmetric Pause, Pause */
        //    valReg4 |= 0x0800 | 0x0400;
        //}

        switch (speed)
        {
        case 10:
            if (TRUE == isFullDuplex)
            {
                valReg4 |= 0x0040;  /* Reg4: 10BASE-TX Full Duplex */
            }
            else
            {
                valReg4 |= 0x0020;  /* Reg4: 10BASE-TX Half Duplex */
            }
            break;
        case 100:
            if (TRUE == isFullDuplex)
            {
                valReg4 |= 0x0100;  /* Reg4: 100BASE-TX Full-Duplex */
            }
            else
            {
                valReg4 |= 0x0080;  /* Reg4: 100BASE-TX Half-Duplex */
            }
            break;
        case 1000:
            if (TRUE == isFullDuplex)
            {
                /* Reg9: 1000BASE-T Full-Duplex, Auto MASTER/SLAVE config */
                valReg9 |= 0x0200;
            }
            else
            {
                EMAC_PRINT_0("Setting 1000Mbps Half-Duplex not supported\r\n");
                return FALSE;   /* Failure */
            }
            break;
        default:
            EMAC_PRINT_1("Invalid speed %u\r\n", speed);
            return FALSE;   /* Failure */
        }

        if ((TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  4, valReg4)) ||
            (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  9, valReg9)) ||
            (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 20, valReg20)) ||
            (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  0, valReg0)))
        {
            return FALSE;   /* Failure */
        }

        /* Sleep after speed change - needed ? */
        Emac_SleepMS(700);
    }

    return TRUE;        /* Success */
}

/**
 * @brief       Set EPHY to MAC interface loopback mode
 *
 * @param[in]   phyAddr         External PHY address
 * @param[in]   speed           Speed in MB: 10/100/1000
 *
 * @return  TRUE if successful, else failed.
 */
static int emac_ephy_setMacIfaceLoopback_marvell_88e1111
(
    uint8   ephyIndex,
    uint8   phyAddr,
    uint32  speed
)
{
    uint16 value = 0;
    uint32 result = FALSE;

    // TODO: Implement the following, do not rely on config pins
    /* Loopback Sequence
     * (see Marvell release notes section 4.30)
     *
     * Step 0:
     *    Set Sleep mode (energy detect) off (set 16.9:8 = '00' plus soft reset)
     *    (Default setting after HW reset)
     *    Set Auto-Media detect off (27.15 = '1' plus soft reset)
     *    (Default setting after HW reset)
     *    Disable MDI/MDIX Auto-crossover (set 16.6:5 = '00' plus soft reset)
     *    (Default setting after HW reset)
     */

    // TODO: should set full-duplex and no auto-neg (currently defaults) - ?
    /* Set the speed */
    // TODO: is this needed?
    if (TRUE != emac_ephy_setSpeed_marvell_88e1111(
                                                ephyIndex, phyAddr, speed, TRUE, FALSE))
    {
        return FALSE;   /* Failure */
    }

    /* Disable interrupts (Reg18 = 0x0000) see release notes section 5.2 */
    if (TRUE != Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 18, 0x0000))
    {
        return FALSE;   /* Failure */
    }

    /* Turn on loopback for the requested speed */
    if (10 == speed)
    {
        value = 0x4100; /* Reg0=0x4100 (enable 10Mbps loopback) */
    }
    else if (100 == speed)
    {
        value = 0x6100; /* Reg0=0x6100 (enable 100Mbps loopback) */
    }
    else if (1000 == speed)
    {
        value = 0x4140; /* Reg0=0x4140 (enable 1000Mbps loopback) */
    }

    /* else: valid speed already checked by setSpeed API */
    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 0, value);

    if (TRUE == result)
    {
        EMAC_PRINT_0("EPHY MAC I/F loopback mode activated\r\n");
    }

    Emac_SleepMS(50);  // TODO: verify if needed

    return result;
}

/**
 * @brief       Set EPHY to external stub loopback mode
 *
 * @param[in]   phyAddr         External PHY address
 * @param[in]   speed           Speed in MB: 10/100/1000
 *
 * @return  TRUE if successful, else failed.
 */
static int emac_ephy_setExtStubLoopback_marvell_88e1111
(
    uint8   ephyIndex,
    uint8   phyAddr,
    uint32  speed
)
{
    uint32 result = FALSE;
    uint16 ValueReg;

    /* See Marvell release notes section 4.30 */
    // TODO: must set full-duplex and no auto-neg (currently defaults)
    // TODO: must disable Auto MDI-X?
    /* Set the speed */
    if (TRUE != emac_ephy_setSpeed_marvell_88e1111(ephyIndex, phyAddr, speed, TRUE, FALSE))
    {
        return FALSE;   /* Failure */
    }

    Emac_SleepMS(50);  // TODO: verify if needed

    /* Disable interrupts (Reg18 = 0x0000) see release notes section 5.2 */
    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 18, 0x0000);

    /* For 10/100Mbps we're done. 1000Mbps need special handling
     * (see Marvell data sheet section 2.14.3)
     */
    if ((TRUE == result) && (1000 == speed))
    {
        /* Read PHY Identifier 2 to get the model number
         * if bits 9:4 is 011101, then the PHY chip is 88E1514
         * if bits 9:4 is 001100, then the PHY chip is 88E1111
        */
        result = Emac_EphyReadMiiReg(ephyIndex, phyAddr, 3, &ValueReg);
        if(TRUE != result)
        {
            return result;
        }

        result = FALSE;

        ValueReg = ValueReg >> 4;
        ValueReg &= 0x3F;
        if(ValueReg == 0x1D) // 88E1514
        {
            if(TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 22, 6)) //change page to 6
            {
                /* for 1000BASE-T mode, page6 register18 bit3 must be set to 1 */
                if(TRUE == Emac_EphyReadMiiReg(0, phyAddr, 18, &ValueReg))
                {
                    ValueReg |= 0x8; //set bit 3 to 1, enable stub test
                    if(TRUE == Emac_EphyWriteMiiReg(0, phyAddr, 18, ValueReg))
                    {
                        if(TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 22, 0)) //change page to 0
                            result = TRUE;
                    }
                }
            }
        }
        else if(ValueReg == 0x0C) // 88E1111
        {
            /* Register 9.12:11 = '11' (force Master, e.g. reg9: 0x1B00)
             * Register 0.15 = '1' (e.g. reg: 0x9140, to perform soft reset)
             */
            if ((TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  9, 0x1B00)) &&
                (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr,  0, 0x9140)) )
            {
                uint16 value = 0;
                Emac_SleepMS(50); /* Sleep after soft reset */

                // TODO: Implement read-modify-write API with setMask and clearMask

                /* Register 29 = 0x0007 (points to page 7 of Register 30) */
                if (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 29, 0x0007))
                {
                    /* Register 30.3 = '1' */
                    if (TRUE == Emac_EphyReadMiiReg(ephyIndex, phyAddr, 30, &value))
                    {
                        value |= 0x0008;
                        if (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 30, value))
                        {
                            /* Register 29 = 0x0010 (points to page 16 of Register 30) */
                            if (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 29, 0x0010))
                            {
                                /* Register 30.1 = '1' */
                                if (TRUE == Emac_EphyReadMiiReg(ephyIndex, phyAddr, 30, &value))
                                {
                                    value |= 0x0002;
                                    if (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 30, value))
                                    {
                                        /* Register 29 = 0x0012 (points to page 18 of Register 30) */
                                        if (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 29, 0x0012))
                                        {
                                            /* Register 30.0 = '1' */
                                            if (TRUE == Emac_EphyReadMiiReg(ephyIndex, phyAddr, 30, &value))
                                            {
                                                value |= 0x0001;
                                                if (TRUE == Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 30, value))
                                                {
                                                    result = TRUE;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else // not supported phy
        {
            EMAC_PRINT_0("!!! Not an supported External PHY Chip\r\n");
            return FALSE;
        }
    }

    if (TRUE == result)
    {
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
 * @return  TRUE if successful, else failed.
 */
static int emac_ephy_setLineLoopback_marvell_88e1111
(
    uint8   ephyIndex,
    uint8   phyAddr,
    uint32  speed
)
{
    uint32 result = FALSE;

    /* See Marvell release notes section 4.30 */
    // TODO: must set full-duplex and no auto-neg (currently defaults)

    /* Set the speed */
    if (TRUE != emac_ephy_setSpeed_marvell_88e1111(
                                               ephyIndex, phyAddr, speed, TRUE, FALSE))
    {
        return FALSE;   /* Failure */
    }

    /* Disable interrupts (Reg18 = 0x0000) see release notes section 5.2 */
    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 18, 0x0000);
    if (TRUE == result)
    {
        /* Set copper line loopback, see Marvell data sheet section 2.14.2. */
        result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 20, 0x4000);
    }

    if (TRUE == result)
    {
        EMAC_PRINT_0("EPHY LINE (Remote PHY) loopback mode activated\r\n");
    }

    return result;
}


/* SGMII to Copper*/
int EmacSetSgmiiToCopperMarvell88E1514 (
    uint8 ephyIndex,
    uint8   phyAddr
)
{
    uint16 ValueReg20 = 0;
    uint32 result = FALSE;

    result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 22, 0x12); //change page to 18
    if (TRUE == result)
    {
        if (TRUE == Emac_EphyReadMiiReg(ephyIndex, phyAddr, 20, &ValueReg20))
        {
            /* Set SGMII to Copper, page 18, reg 20 bit0~2 001 */
            ValueReg20 &= ~0x0006; //set bit 1 and bit 2 to 0
            ValueReg20 |= 0x1; //set bit 0 to 1
            result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 20, ValueReg20);
            Emac_SleepMS(10);

            Emac_EphyReadMiiReg(ephyIndex, phyAddr, 20, &ValueReg20);
            ValueReg20 |= 0x8000; //set bit 15 to 1; reset
            result = Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 20, ValueReg20);
            Emac_SleepMS(10);
        }

        Emac_EphyWriteMiiReg(ephyIndex, phyAddr, 22, 0); //set page to 0
    }

    return result;
}


/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 *--------------------------------------------------------------------------*/

int emac_ephy_init_marvell_88e1111(uint8 ephyIndex, const EMAC_EPHY_CFG *cfg)
{
    int result = FALSE;
    uint8 phyAddr = ephyAddr[ephyIndex];
    uint16 ValueReg;

    result = Emac_EphyReadMiiReg(ephyIndex, phyAddr, 3, &ValueReg);
    if(!result)
    {
        return result;
    }

    ValueReg = ValueReg >> 4;
    ValueReg &= 0x3F;
    if(ValueReg == 0x1D) // 88E1514
    {
        result = EmacEphySetLedBehavior(ephyIndex, phyAddr);
        if(!result)
            return result;

        result = EmacSetSgmiiToCopperMarvell88E1514(ephyIndex, phyAddr);
        if (!result)
            return result;
    }

    /* Handle loopback modes */
    switch (cfg->modeLoopback)
    {
    case EMAC_LB_MAC:
    case EMAC_LB_PHY_DIG:
    case EMAC_LB_PHY_SERDES:
        /* No special handling needed, handle same as no loopback */
        /* FALL THROUGH */
    case EMAC_LB_NONE:
        /* See Marvell release notes section 4.30 */
        /* Set the speed */
        result = emac_ephy_setSpeed_marvell_88e1111(
                         ephyIndex, phyAddr, cfg->speed, cfg->isFullDuplex, cfg->isAutoNeg);
        break;

    case EMAC_LB_EPHY_MAC_IF:
        result = emac_ephy_setMacIfaceLoopback_marvell_88e1111(
                                                      ephyIndex, phyAddr, cfg->speed);
        break;

    case EMAC_LB_EPHY_EXT_STUB:
        result = emac_ephy_setExtStubLoopback_marvell_88e1111(
                                                      ephyIndex, phyAddr, cfg->speed);
        break;

    case EMAC_LB_EPHY_LINE:
        result = emac_ephy_setLineLoopback_marvell_88e1111(
                                                      ephyIndex, phyAddr, cfg->speed);
        break;

    default:
        EMAC_PRINT_1("Invalid EPHY loopback mode %u\r\n", cfg->modeLoopback);
        result = FALSE;
        break;
    }

    return result;
}

/**
 * @brief       Cleanup driver
 */
void emac_ephy_cleanup_marvell_88e1111(uint8 ephyIndex)
{
    Emac_EphyHwReset(ephyIndex);
}

int Emac_EphyReadMiiReg_marvell_88e1111
(
    uint8   ephyIndex,
    uint8   devAddr,
    uint8   regAddr,
    uint16 *regData
)
{
    uint32 cnt;

    if (NULL == regData)
    {
        EMAC_PRINT_0("NULL parameter\r\n");
        return FALSE;   /* Failure */
    }

    *regData = 0xFFFF;

    /* Set device address */
    if(ephyIndex == 0){
        HWIO_OUTF(EMAC_REG_PRE(PHY_STS), PHY_ADDR, devAddr);
    }
    else{
        HWIO_OUTF(EMAC_REG_PRE1(PHY_STS), PHY_ADDR, devAddr);
    }

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
    for (cnt = 0; cnt < EMAC_MDIO_MAX_WAIT; cnt++){
        /* It takes few MDIO clock cycles for MDIO_BUSY to be set after MDIO
         * operation is started. With slow clock we might read zero MDIO_BUSY
         * and assume that operation is done before it even started, so allow
         * some delay before checking for the first time
         */
        Emac_SleepMS(1);
        if(ephyIndex == 0){
            if (0 == HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_BUSY)){
                /* Done, read data */
                *regData = HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_DATA);
                return TRUE;       /* Success */
            }
        }
        else{
            if (0 == HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_BUSY)){
                /* Done, read data */
                *regData = HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_DATA);
                return TRUE;       /* Success */
            }
        }
    }

    EMAC_PRINT_0("EPHY read failed, MDIO busy\r\n");

    return FALSE;   /* Failure */
}

int Emac_EphyWriteMiiReg_marvell_88e1111
(
    uint8  ephyIndex,
    uint8  devAddr,
    uint8  regAddr,
    uint16 regData
)
{
    uint32 cnt;

    /* Set device address */
    if(ephyIndex == 0){
        HWIO_OUTF(EMAC_REG_PRE(PHY_STS), PHY_ADDR, devAddr);
        // TODO: move to EPHY init
        HWIO_OUTF5(EMAC_REG_PRE(MDIO_CTRL),
                   MDIO_MODE, MDIO_PR, MDIO_AP_EN, MDIO_CLK_SEL, SUP_PREAMBLE,
                   0,         0,       0,          0,            1);
    }
    else{
        HWIO_OUTF(EMAC_REG_PRE(PHY_STS), PHY_ADDR, devAddr);
        // TODO: move to EPHY init
        HWIO_OUTF5(EMAC_REG_PRE(MDIO_CTRL),
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
    for (cnt = 0; cnt < EMAC_MDIO_MAX_WAIT; cnt++)
    {
        /* It takes few MDIO clock cycles for MDIO_BUSY to be set after MDIO
         * operation is started. With slow clock we might read zero MDIO_BUSY
         * and assume that operation is done before it even started, so allow
         * some delay before checking for the first time
         */
        Emac_SleepMS(1);
        if(ephyIndex == 0){
            if (0 == HWIO_INF(EMAC_REG_PRE(MDIO_CTRL), MDIO_BUSY)){
                return TRUE;       /* Success */
            }
        }
        else{
            if (0 == HWIO_INF(EMAC_REG_PRE1(MDIO_CTRL), MDIO_BUSY)){
                return TRUE;       /* Success */
            }
        }
    }

    EMAC_PRINT_0("EPHY write failed, MDIO busy\r\n");

    return FALSE;   /* Failure */
}

int emac_ephy_isLinkUp_marvell_88e1111(uint8  ephyIndex, boolean *isLinkUp)
{
    uint16 valReg17 = 0;
    uint8 phyAddr = ephyAddr[ephyIndex];

    if (NULL == isLinkUp)
    {
        EMAC_PRINT_0("NULL parameter\r\n");
        return FALSE;   /* Failure */
    }

    /* Read PHY-Specific Status Register 17 */
    if (TRUE != Emac_EphyReadMiiReg(ephyIndex, phyAddr, 17, &valReg17))
    {
        EMAC_PRINT_0("Failed to read PHY-Specific Status Register\r\n");
        *isLinkUp = FALSE;
        return FALSE;   /* Failure */
    }

    /* Check bit 10 for real-time link status */
    if (0 == (valReg17 & (1 << 10)))
    {
        *isLinkUp = FALSE;
    }
    else
    {
        *isLinkUp = TRUE;
    }

    return TRUE;       /* Success */
}

int emac_ephy_getSpeedAndDuplex_marvell_88e1111
(
    uint8  ephyIndex,
    uint32  *speed,
    boolean *isFullDuplex
)
{
  uint16 valReg17;
  uint8 phyAddr = ephyAddr[ephyIndex];

  if (NULL == speed)
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
   * Auto-Negotiation is completed or Auto-Negotiation is disabled
   */
  if (0 == (valReg17 & (1 << 11)))
  {
    EMAC_PRINT_0("Link is up, but speed not resolved\r\n");
    return FALSE;   /* Failure */
  }

  /* Register 17 bits [14:15] mark the speed, both is resolved from
   * Auto-Negotiation or Auto-Negotiation is disabled
   */
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

