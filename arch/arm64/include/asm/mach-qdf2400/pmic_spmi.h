#ifndef __SPMI_PMICARB_H_INCLUDE__
#define __SPMI_PMICARB_H_INCLUDE__

#include <target/spmi.h>

typedef struct {
    uint32_t irqStatus;
    uint32_t geniStatus;
    uint32_t geniCtrl;
} PmicArbHwStatus;

typedef void (*PmicArbIsrCallback)(uint8_t bid,
				   uint16_t channel,
				   uint8_t mask);

Spmi_Result PmicArb_ExecuteCommand(PmicArbCmd cmd,
                                   Spmi_AccessPriority priority,
                                   uint8_t bid,
                                   uint8_t slaveId,
                                   uint16_t address,
                                   uint8_t *data,
                                   uint32_t dataLen,
                                   uint32_t *bytesTransacted);

void pmic_init(uint8_t bid, uint8_t masterId);

Spmi_Result pmic_cmd(PmicArbCmd cmd, uint8_t slaveId,
		     uint16_t address, uint8_t data);

#endif
