#include "afbc_interrupt.h"
#include "afbc.h"
#include "system_isp_io.h"
#include "acamera_logger.h"

void afbc_interrupt_handler()
{
	uint32_t base = AFBC_BASE;
	LOG(LOG_NOTICE, "%s", __FUNCTION__);
	uint32_t curr = system_isp_read_32(base + IRQ_STATUS);
	printf("afbc interrupt, irq_status = 0x%2x\n", curr);
	system_isp_write_32(base + IRQ_CLEAR, curr);
}
