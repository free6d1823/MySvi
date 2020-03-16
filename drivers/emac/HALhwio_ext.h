#ifndef __HALHWIO_EXT__
#define __HALHWIO_EXT__
/**---------------------------------------------------------------------------
 * @file     HALhwio_ext.h
 *
 * @brief    HW I/O macro extensions for setting multiple fields in register
 * 
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *--------------------------------------------------------------------------*/

#include "asm/hal/HALhwio.h"

#define HWIO_OUTF2(io, field2, field1, val2, val1)  \
            HWIO_OUTM(io,   \
                      (HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                      ((val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))))

#define HWIO_OUTF3(io, field3, field2, field1, val3, val2, val1) \
            HWIO_OUTM(io,   \
                      (HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                      ((val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))))

#define HWIO_OUTF4(io, field4, field3, field2, field1, val4, val3, val2, val1) \
            HWIO_OUTM(io,   \
                      (HWIO_FMSK(io, field4)|HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                      ((val4<<HWIO_SHFT(io, field4))|(val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))))

#define HWIO_OUTF5(io, field5, field4, field3, field2, field1, val5, val4, val3, val2, val1) \
            HWIO_OUTM(io,   \
                      (HWIO_FMSK(io, field5)|HWIO_FMSK(io, field4)|HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                      ((val5<<HWIO_SHFT(io, field5))|(val4<<HWIO_SHFT(io, field4))|(val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))))

#define HWIO_OUTF6(io, field6, field5, field4, field3, field2, field1, val6, val5, val4, val3, val2, val1) \
            HWIO_OUTM(io,   \
                      (HWIO_FMSK(io, field6)|HWIO_FMSK(io, field5)|HWIO_FMSK(io, field4)|HWIO_FMSK(io, field3)|HWIO_FMSK(io, field2)|HWIO_FMSK(io, field1)), \
                      ((val6<<HWIO_SHFT(io, field6))|(val5<<HWIO_SHFT(io, field5))|(val4<<HWIO_SHFT(io, field4))|(val3<<HWIO_SHFT(io, field3))|(val2<<HWIO_SHFT(io, field2))|(val1<<HWIO_SHFT(io, field1))))

#endif /* __HALHWIO_EXT__ */

