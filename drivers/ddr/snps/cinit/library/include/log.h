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


#ifndef LOG_H
#define	LOG_H

#include <stdio.h>
#include <stdlib.h>
#include "dwc_cinit_custom.h"

#ifdef __cplusplus
extern "C" {
#endif

	void break_b4_exit();

	/*************************************************************************
	* T Y P E D E F S    &    D E F I N E S
	*************************************************************************/

	//lvl = 1 most important 
	//lvl = 2..3
	//lvl = 5 print regs
	//lvl = 7 apb transactions

	#define LOG_MESSAGE(hdlr,lvl,str)			\
		do {									\
			if ((lvl) <= (hdlr)->logLevel_m) {\
		      	  dwc_cinit_print("[%s() %s:%d] ",__FUNCTION__,basename(__FILE__),__LINE__ );						\
		      	  dwc_cinit_print str ;						\
			}									\
		} while (0)
#ifdef SIM_MODE 

	#define ERROR_MESSAGE(str)													\
		do { char mystr[50];\
			sprintf(mystr, "CININT ERROR in %s() %s:%d\n", __FUNCTION__, __FILE__, __LINE__);	\
			dwc_cinit_print str; \
                        abort_simulation(mystr);\
		} while (0)

#else 

	#define ERROR_MESSAGE(str)													\
		do { \
			dwc_cinit_print("CININT ERROR in %s() %s:%d\n", __FUNCTION__, __FILE__, __LINE__);	\
			dwc_cinit_print str; \
			break_b4_exit(); \
			exit(-1); \
		} while (0)
#endif 

//define _TRACE to enable function tracing
#ifdef _TRACE
	#define TRACE()																\
		do {																	\
			dwc_cinit_print("TRACE %s() %s:%d\n", __FUNCTION__,basename(__FILE__), __LINE__);		\
		} while (0)
#else
	#define TRACE()
#endif

#ifdef __cplusplus
}
#endif
#endif	//LOG_H

