#ifndef __VVDRV_QSMMUV3_PROGRAM_H__
#define __VVDRV_QSMMUV3_PROGRAM_H__

//#include "VVDRV_qsmmuv3_CommonInclude.h"
#include "VVDRV_qsmmuv3_common_dvm.h"
#include "VVDRV_qsmmuv3_profile_dvm.h"
#include "VVDRV_qsmmuv3_TT_dvm.h"
//#include "vv_interrupt.h"

void VVDRV_qsmmuv3_api_init(system_profile *p_sys_profile, uint32_t inIMEM,smmu_profile profile);
void VVDRV_qsmmuv3_sys_profile_default(system_profile *p_sys_profile, uint32_t inIMEM,smmu_profile profile);
void VVDRV_qsmmuv3_vm_profile_default(vm_profile *p_vm_profile, uint32_t inIMEM,smmu_profile profile);

void VVDRV_qsmmuv3_program_QACT(qsmmu_profile * p_qsmmu_inst, uint32_t qactidx, uint32_t qact_s);
void VVDRV_qsmmuv3_free_QACT(qsmmu_profile * p_qsmmu_inst, uint32_t qactidx, uint32_t qact_s);
void VVDRV_qsmmuv3_program_qact(stream_profile *p_stream);
void VVDRV_qsmmuv3_free_qact(stream_profile *p_stream);

void VVDRV_qsmmuv3_program_enables(qsmmu_profile * p_qsmmu_inst);
void VVDRV_qsmmuv3_init_qsmmu_profile(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_alloc_qsmmu_queues(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_programCMDQ(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_programEventQ(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_alloc_qsmmu_st(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_programStreamTable(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_init_qsmmu(qsmmu_profile *p_qsmmu_inst);

uint64_t VVDRV_qsmmuv3_alloc_page(tt_tgs_e tgs, vm_profile* p_vm, int b_tt);

void VVDRV_qsmmuv3_program_MSI(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_program_stream(stream_profile *p_stream,uint64_t pt_base);
uint64_t VVDRV_qsmmuv3_alloc_CD(stream_profile * p_stream);
system_profile *VVDRV_qsmmuv3_get_sys_profile(uint32_t inIMEM);
qsmmu_profile * VVDRV_qsmmuv3_get_qsmmu(qsmmu_ss_e ss_e, uint32_t idx);
void VVDRV_qsmmuv3_set_qsmmu(qsmmu_profile *p_qsmmu_inst, qsmmu_ss_e ss_e, uint32_t idx);
void VVDRV_qsmmuv3_init_stream(stream_profile *p_stream, qsmmu_ss_e ss_e, uint32_t idx);
void VVDRV_qsmmuv3_zero_mem(uint64_t addr, uint32_t size_B);
void VVDRV_qsmmuv3_program_IMC();
//void VVDRV_qsmmuv3_program_Intr(vi_int_isr_func_type p_imc_irs);
void VVDRV_qsmmuv3_programGERROR_IRQ(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_check_eventq(qsmmu_profile *p_qsmmu_inst);
void VVDRV_qsmmuv3_process_event(qsmmu_profile *p_qsmmu_inst, event_struct* event_ptr);
#endif
