#ifndef __ARM64_SPMI_H_INCLUDE__
#define __ARM64_SPMI_H_INCLUDE__

#include <asm/mach/hal/msmhwiobase.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach/pmic_swio.h>
#include <asm/mach/spmi_swio.h>

extern uint8_t* pmicArbBaseAddrs[];

#define PMIC_ARB_BASE_ARRAY pmicArbBaseAddrs

#define SWIO_MAX_BUSES_SUPPORTED 3

#define SWIO_MAX_CHANNELS_SUPPORTED (HWIO_I1_PMIC_ARB_REG_CHNLn_MAXn + 1)

#define SPMI_HWIO_IN(addr)        __inpdw(addr)
#define SPMI_HWIO_OUT(addr, val)  __outpdw(addr, val)

#define SPMI_HWIO_OUT_SET(addr, mask)    SPMI_HWIO_OUT(addr, ((SPMI_HWIO_IN(addr)) | (mask)))
#define SPMI_HWIO_OUT_CLEAR(addr, mask)  SPMI_HWIO_OUT(addr, ((SPMI_HWIO_IN(addr)) & (~(mask))))

#define SPMI_HWIO_IN_MASK(addr, mask)         (SPMI_HWIO_IN(addr) & (mask))
#define SPMI_HWIO_OUT_MASK(addr, mask, val)    SPMI_HWIO_OUT(addr, ((SPMI_HWIO_IN(addr) & (~(mask))) | ((val) & (mask))))

#define SPMI_HWIO_GET_FIELD_VALUE(value, field)  (((value) & field##_BMSK) >> field##_SHFT)
#define SPMI_HWIO_SET_FIELD_VALUE(value, field)  (((value) << field##_SHFT) & field##_BMSK)
#define SPMI_HWIO_IN_FIELD(addr, field)       (SPMI_HWIO_IN_MASK( addr, field##_BMSK ) >> field##_SHFT)
#define SPMI_HWIO_OUT_FIELD(addr, field, val)  SPMI_HWIO_OUT_MASK( addr, field##_BMSK, (val) << field##_SHFT )

#define SPMI_SWIO_GET_FIELD_VALUE(bid, value, field)  (((value) & field##_BMSK(bid)) >> field##_SHFT(bid))
#define SPMI_SWIO_SET_FIELD_VALUE(bid, value, field)  (((value) << field##_SHFT(bid)) & field##_BMSK(bid))
#define SPMI_SWIO_IN_FIELD(bid, addr, field)  (SPMI_HWIO_IN_MASK( addr, field##_BMSK(bid) ) >> field##_SHFT(bid))
#define SPMI_SWIO_OUT_FIELD(bid, addr, field, val)  SPMI_HWIO_OUT_MASK( addr, field##_BMSK(bid), (val) << field##_SHFT(bid) )

Spmi_Result SpmiHal_Init(void);
uint8_t *SpmiHal_GetBaseAddr(uint8_t bid);

#endif
