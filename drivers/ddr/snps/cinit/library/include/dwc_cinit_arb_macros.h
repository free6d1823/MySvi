//------------------------------------------------------------------------------
//
// Copyright 2019 Synopsys, INC.
//
// This Synopsys IP and all associated documentation are proprietary to
// Synopsys, Inc. and may only be used pursuant to the terms and conditions of a
// written license agreement with Synopsys, Inc. All other use, reproduction,
// modification, or distribution of the Synopsys IP or the associated
// documentation is strictly prohibited.
//
// Component Name   : DWC_ddrctl
// Component Version: 1.00a-ea06
// Release Type     : EA
//------------------------------------------------------------------------------

#ifndef __CINIT_ARB_MACROS_H__
#define __CINIT_ARB_MACROS_H__


#ifdef	__cplusplus
extern "C" {
#endif

  #if defined(UMCTL2_PORT_CH0_0)
    #define DWC_DDRCTL_PORT_CH0_0 UMCTL2_PORT_CH0_0
  #else
    #define DWC_DDRCTL_PORT_CH0_0 0
  #endif

  #if defined(UMCTL2_PORT_CH0_1)
    #define DWC_DDRCTL_PORT_CH0_1 UMCTL2_PORT_CH0_1
  #else
    #define DWC_DDRCTL_PORT_CH0_1 0
  #endif

  #if defined(UMCTL2_PORT_CH0_2)
    #define DWC_DDRCTL_PORT_CH0_2 UMCTL2_PORT_CH0_2
  #else
    #define DWC_DDRCTL_PORT_CH0_2 0
  #endif

  #if defined(UMCTL2_PORT_CH0_3)
    #define DWC_DDRCTL_PORT_CH0_3 UMCTL2_PORT_CH0_3
  #else
    #define DWC_DDRCTL_PORT_CH0_3 0
  #endif

  #if defined(UMCTL2_PORT_CH0_4)
    #define DWC_DDRCTL_PORT_CH0_4 UMCTL2_PORT_CH0_4
  #else
    #define DWC_DDRCTL_PORT_CH0_4 0
  #endif

  #if defined(UMCTL2_PORT_CH0_5)
    #define DWC_DDRCTL_PORT_CH0_5 UMCTL2_PORT_CH0_5
  #else
    #define DWC_DDRCTL_PORT_CH0_5 0
  #endif

  #if defined(UMCTL2_PORT_CH0_6)
    #define DWC_DDRCTL_PORT_CH0_6 UMCTL2_PORT_CH0_6
  #else
    #define DWC_DDRCTL_PORT_CH0_6 0
  #endif

  #if defined(UMCTL2_PORT_CH0_7)
    #define DWC_DDRCTL_PORT_CH0_7 UMCTL2_PORT_CH0_7
  #else
    #define DWC_DDRCTL_PORT_CH0_7 0
  #endif

  #if defined(UMCTL2_PORT_CH0_8)
    #define DWC_DDRCTL_PORT_CH0_8 UMCTL2_PORT_CH0_8
  #else
    #define DWC_DDRCTL_PORT_CH0_8 0
  #endif

  #if defined(UMCTL2_PORT_CH0_9)
    #define DWC_DDRCTL_PORT_CH0_9 UMCTL2_PORT_CH0_9
  #else
    #define DWC_DDRCTL_PORT_CH0_9 0
  #endif

  #if defined(UMCTL2_PORT_CH0_10)
    #define DWC_DDRCTL_PORT_CH0_10 UMCTL2_PORT_CH0_10
  #else
    #define DWC_DDRCTL_PORT_CH0_10 0
  #endif

  #if defined(UMCTL2_PORT_CH0_11)
    #define DWC_DDRCTL_PORT_CH0_11 UMCTL2_PORT_CH0_11
  #else
    #define DWC_DDRCTL_PORT_CH0_11 0
  #endif

  #if defined(UMCTL2_PORT_CH0_12)
    #define DWC_DDRCTL_PORT_CH0_12 UMCTL2_PORT_CH0_12
  #else
    #define DWC_DDRCTL_PORT_CH0_12 0
  #endif

  #if defined(UMCTL2_PORT_CH0_13)
    #define DWC_DDRCTL_PORT_CH0_13 UMCTL2_PORT_CH0_13
  #else
    #define DWC_DDRCTL_PORT_CH0_13 0
  #endif

  #if defined(UMCTL2_PORT_CH0_14)
    #define DWC_DDRCTL_PORT_CH0_14 UMCTL2_PORT_CH0_14
  #else
    #define DWC_DDRCTL_PORT_CH0_14 0
  #endif

  #if defined(UMCTL2_PORT_CH0_15)
    #define DWC_DDRCTL_PORT_CH0_15 UMCTL2_PORT_CH0_15
  #else
    #define DWC_DDRCTL_PORT_CH0_15 0
  #endif

  #define DWC_DDRCTL_A_PORT_MACRO(_macro,_port) \
    _macro##_##_port

  #define DWC_DDRCTL_MP_PARAMETER(_macro,_port,_var,_type) \
    _type _var;\
    if (_port==15) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,15); \
    } else if (_port==14) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,14); \
    } else if (_port==13) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,13); \
    } else if (_port==12) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,12); \
    } else if (_port==11) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,11); \
    } else if (_port==10) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,10); \
    } else if (_port==9) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,9); \
    } else if (_port==8) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,8); \
    } else if (_port==7) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,7); \
    } else if (_port==6) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,6); \
    } else if (_port==5) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,5); \
    } else if (_port==4) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,4); \
    } else if (_port==3) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,3); \
    } else if (_port==2) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,2); \
    } else if (_port==1) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,1); \
    } else if (_port==0) { \
      _var = DWC_DDRCTL_A_PORT_MACRO(_macro,0); \
    }

#ifdef	__cplusplus
}
#endif


#endif // __CINIT_ARB_MACROS_H__
