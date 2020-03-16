/** @file

Copyright (c) 2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

**/
#ifndef _SEMTECH1509B_H_
#define _SEMTECH1509B_H_

//SEMTECH 1509B registers

#define REG_INPUTDISABLE_B 0x00   //Input buffer disable register - I/O[15-8] (Bank B) 0000 0000
#define REG_INPUTDISABLE_A 0x01     //Input buffer disable register - I/O[7-0] (Bank A) 0000 0000
#define REG_LONGSLEW_B 0x02     //Output buffer long slew register - I/O[15-8] (Bank B) 0000 0000
#define REG_LONGSLEW_A 0x03     //Output buffer long slew register - I/O[7-0] (Bank A) 0000 0000
#define REG_LOWDRIVE_B 0x04     //Output buffer low drive register - I/O[15-8] (Bank B) 0000 0000
#define REG_LOWDRIVE_A 0x05     //Output buffer low drive register - I/O[7-0] (Bank A) 0000 0000
#define REG_PULLUP_B 0x06     //Pull-up register - I/O[15-8] (Bank B) 0000 0000
#define REG_PULLUP_A 0x07     //Pull-up register - I/O[7-0] (Bank A) 0000 0000
#define REG_PULLDOWN_B 0x08     //Pull-down register - I/O[15-8] (Bank B) 0000 0000
#define REG_PULLDOWN_A 0x09     //Pull-down register - I/O[7-0] (Bank A) 0000 0000
#define REG_OPENDRAIN_B 0x0A      //Open drain register - I/O[15-8] (Bank B) 0000 0000
#define REG_OPENDRAIN_A 0x0B      //Open drain register - I/O[7-0] (Bank A) 0000 0000
#define REG_POLARITY_B 0x0C     //Polarity register - I/O[15-8] (Bank B) 0000 0000
#define REG_POLARITY_A 0x0D     //Polarity register - I/O[7-0] (Bank A) 0000 0000
#define REG_DIR_B 0x0E      //Direction register - I/O[15-8] (Bank B) 1111 1111
#define REG_DIR_A 0x0F      //Direction register - I/O[7-0] (Bank A) 1111 1111
#define REG_DATA_B 0x10     //Data register - I/O[15-8] (Bank B) 1111 1111*
#define REG_DATA_A 0x11     //Data register - I/O[7-0] (Bank A) 1111 1111*
#define REG_INTERRUPTMASK_B 0x12      //Interrupt mask register - I/O[15-8] (Bank B) 1111 1111
#define REG_INTERRUPTMASK_A 0x13      //Interrupt mask register - I/O[7-0] (Bank A) 1111 1111
#define REG_SENSEHIGH_B 0x14      //Sense register for I/O[15:12] 0000 0000
#define REG_SENSELOW_B 0x15     //Sense register for I/O[11:8] 0000 0000
#define REG_SENSEHIGH_A 0x16      //Sense register for I/O[7:4] 0000 0000
#define REG_SENSELOW_A 0x17     //Sense register for I/O[3:0] 0000 0000
#define REG_INTERRUPTSOURCE_B 0x18      //Interrupt source register - I/O[15-8] (Bank B) 0000 0000
#define REG_INTERRUPTSOURCE_A 0x19      //Interrupt source register - I/O[7-0] (Bank A) 0000 0000
#define REG_EVENTSTATUS_B 0x1A      //Event status register - I/O[15-8] (Bank B) 0000 0000
#define REG_EVENTSTATUS_A 0x1B      //Event status register - I/O[7-0] (Bank A) 0000 0000
#define REG_LEVELSHIFTER1 0x1C      //Level shifter register 0000 0000
#define REG_LEVELSHIFTER2 0x1D      //Level shifter register 0000 0000
#define REG_CLOCK 0x1E      //Clock management register 0000 0000
#define REG_MISC 0x1F     //Miscellaneous device settings register 0000 0000
#define REG_LEDDRIVERENABLE_B 0x20      //LED driver enable register - I/O[15-8] (Bank B) 0000 0000
#define REG_LEDDRIVERENABLE_A 0x21      //LED driver enable register - I/O[7-0] (Bank A) 0000 0000
#define REG_DEBOUNCECONFIG 0x22     //Debounce configuration register 0000 0000
#define REG_DEBOUNCEENABLE_B 0x23     //Debounce enable register - I/O[15-8] (Bank B) 0000 0000
#define REG_DEBOUNCEENABLE_A 0x24     //Debounce enable register - I/O[7-0] (Bank A) 0000 0000
#define REG_KEYCONFIG1 0x25     //Key scan configuration register 0000 0000
#define REG_KEYCONFIG2 0x26     //Key scan configuration register 0000 0000
#define REG_KEYDATA1 0x27     //Key value (column) 1111 1111
#define REG_KEYDATA2 0x28     //Key value (row) 1111 1111
//LED Driver (PWM, blinking, breathing)
#define REG_TON0 0x29     //ON time register for I/O[0] 0000 0000
#define REG_ION0 0x2A     //ON intensity register for I/O[0] 1111 1111
#define REG_OFF0 0x2B     //OFF time/intensity register for I/O[0] 0000 0000
#define REG_TON1 0x2C     //ON time register for I/O[1] 0000 0000
#define REG_ION1 0x2D     //ON intensity register for I/O[1] 1111 1111
#define REG_OFF1 0x2E     //OFF time/intensity register for I/O[1] 0000 0000
#define REG_TON2 0x2F     //ON time register for I/O[2] 0000 0000
#define REG_ION2 0x30     //ON intensity register for I/O[2] 1111 1111
#define REG_OFF2 0x31     //OFF time/intensity register for I/O[2] 0000 0000
#define REG_TON3 0x32     //ON time register for I/O[3] 0000 0000
#define REG_ION3 0x33     //ON intensity register for I/O[3] 1111 1111
#define REG_OFF3 0x34     //OFF time/intensity register for I/O[3] 0000 0000
#define REG_TON4 0x35     //ON time register for I/O[4] 0000 0000
#define REG_ION4 0x36     //ON intensity register for I/O[4] 1111 1111
#define REG_OFF4 0x37     //OFF time/intensity register for I/O[4] 0000 0000
#define REG_TRISE4 0x38     //Fade in register for I/O[4] 0000 0000
#define REG_TFALL4 0x39     //Fade out register for I/O[4] 0000 0000
#define REG_TON5 0x3A     //ON time register for I/O[5] 0000 0000
#define REG_ION5 0x3B     //ON intensity register for I/O[5] 1111 1111
#define REG_OFF5 0x3C     //OFF time/intensity register for I/O[5] 0000 0000
#define REG_TRISE5 0x3D     //Fade in register for I/O[5] 0000 0000
#define REG_TFALL5 0x3E     //Fade out register for I/O[5] 0000 0000
#define REG_TON6 0x3F     //ON time register for I/O[6] 0000 0000
#define REG_ION6 0x40     //ON intensity register for I/O[6] 1111 1111
#define REG_OFF6 0x41     //OFF time/intensity register for I/O[6] 0000 0000
#define REG_TRISE6 0x42     //Fade in register for I/O[6] 0000 0000
#define REG_TFALL6 0x43     //Fade out register for I/O[6] 0000 0000
#define REG_TON7 0x44     //ON time register for I/O[7] 0000 0000
#define REG_ION7 0x45     //ON intensity register for I/O[7] 1111 1111
#define REG_OFF7 0x46     //OFF time/intensity register for I/O[7] 0000 0000
#define REG_TRISE7 0x47     //Fade in register for I/O[7] 0000 0000
#define REG_TFALL7 0x48     //Fade out register for I/O[7] 0000 0000
#define REG_TON8 0x49     //ON time register for I/O[8] 0000 0000
#define REG_ION8 0x4A     //ON intensity register for I/O[8] 1111 1111
#define REG_OFF8 0x4B     //OFF time/intensity register for I/O[8] 0000 0000
#define REG_TON9 0x4C     //ON time register for I/O[9] 0000 0000
#define REG_ION9 0x4D     //ON intensity register for I/O[9] 1111 1111
#define REG_OFF9 0x4E     //OFF time/intensity register for I/O[9] 0000 0000
#define REG_TON10 0x4F      //ON time register for I/O[10] 0000 0000
#define REG_ION10 0x50      //ON intensity register for I/O[10] 1111 1111
#define REG_OFF10 0x51      //OFF time/intensity register for I/O[10] 0000 0000
#define REG_TON11 0x52      //ON time register for I/O[11] 0000 0000
#define REG_ION11 0x53      //ON intensity register for I/O[11] 1111 1111
#define REG_OFF11 0x54      //OFF time/intensity register for I/O[11] 0000 0000
#define REG_TON12 0x55      //ON time register for I/O[12] 0000 0000
#define REG_ION12 0x56      //ON intensity register for I/O[12] 1111 1111
#define REG_OFF12 0x57      //OFF time/intensity register for I/O[12] 0000 0000
#define REG_TRISE12 0x58      //Fade in register for I/O[12] 0000 0000
#define REG_TFALL12 0x59      //Fade out register for I/O[12] 0000 0000
#define REG_TON13 0x5A      //ON time register for I/O[13] 0000 0000
#define REG_ION13 0x5B      //ON intensity register for I/O[13] 1111 1111
#define REG_OFF13 0x5C      //OFF time/intensity register for I/O[13] 0000 0000
#define REG_TRISE13 0x5D      //Fade in register for I/O[13] 0000 0000
#define REG_TFALL13 0x5E      //Fade out register for I/O[13] 0000 0000
#define REG_TON14 0x5F      //ON time register for I/O[14] 0000 0000
#define REG_ION14 0x60      //ON intensity register for I/O[14] 1111 1111
#define REG_OFF14 0x61      //OFF time/intensity register for I/O[14] 0000 0000
#define REG_TRISE14 0x62      //Fade in register for I/O[14] 0000 0000
#define REG_TFALL14 0x63      //Fade out register for I/O[14] 0000 0000
#define REG_TON15 0x64      //ON time register for I/O[15] 0000 0000
#define REG_ION15 0x65      //ON intensity register for I/O[15] 1111 1111
#define REG_OFF15 0x66      //OFF time/intensity register for I/O[15] 0000 0000
#define REG_TRISE15 0x67      //Fade in register for I/O[15] 0000 0000
#define REG_TFALL15 0x68      //Fade out register for I/O[15] 0000 0000
//Miscellaneous
#define REG_HIGHINPUT_B 0x69      //High input enable register - I/O[15-8] (Bank B) 0000 0000
#define REG_HIGHINPUT_A 0x6A      //High input enable register - I/O[7-0] (Bank A) 0000 0000
//Reset Software
#define REG_RESET 0x7D      //Software reset register 0000 0000
//Test (not to be written)
#define REG_TEST1 0x7E      //Test register 0000 0000
#define REG_TEST2 0x7F      //Test register 0000 0000

#endif //_SEMTECH1509B_H_
