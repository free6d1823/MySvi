/** @file

Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

**/
#ifndef _NXPPCA9551_H_
#define _NXPPCA9551_H_

//NXP PCA9551 registers

#define REG_PCA9551_INPUT 0x00 //input register
#define REG_PCA9551_PSC0  0x01 //frequency prescaler 0
#define REG_PCA9551_PWM0  0x02 //PWM register 0
#define REG_PCA9551_PSC1  0x03 //frequency prescaler 1
#define REG_PCA9551_PWM1  0x04 //PWM register 1
#define REG_PCA9551_LS0   0x05 //LED0 to LED3 selector
#define REG_PCA9551_LS1   0x06 //LED4 to LED7 selector

#define AUTO_INCREMENT    0x10

#endif //_NXPPCA9551_H_