
//-----------------------------------------------------------------------------
// Qualcomm Technologies, Inc. Proprietary
// Copyright (c) 2012-2016, Qualcomm Technologies, Inc. All rights reserved.
//
// All data and information contained in or disclosed by this document are
// confidential and proprietary information of Qualcomm Technologies, Inc. or
// its Affiliates, or their licensors, and all rights therein are expressly
// reserved. By accepting this material, the recipient agrees that this
// material and the information contained therein are held in confidence and
// in trust and will not be used, copied, reproduced in whole or in part, nor
// its contents revealed in any manner to others, without the express written
// permission of Qualcomm Technologies, Inc., or to the extent expressly
// permitted by the Technology License Agreement between Qualcomm Technologies,

//
// This technology was exported from the United States in accordance with the
// approval from the U.S. Department of Commerce, Bureau of Industry and
// Security, Export Administration Regulations (EAR).  Any re-export or
// in-country transfers of this technology is subject to U.S. Laws and
// regulations. Diversion contrary to U.S. law prohibited.
//-----------------------------------------------------------------------------

#ifndef __VVDRV_QSMMUV3_COMMON_H__
#define __VVDRV_QSMMUV3_COMMON_H__

//#include "VVDRV_qsmmuv3_CommonInclude.h"
#include <stdint.h>
#define EVENT_BYTES  32

#define SYS_IMEM_START		0xFF70000000ULL
#define AW_NS_SUBTRACT_OFFSET   0x1f00000000ULL
#define QSMMU_S_OFFSET_PCIE_0	0xE100000000ULL
#define QSMMU_NS_OFFSET_PCIE_0	0xE200000000ULL
#define QSMMU_S_OFFSET_PCIE_1	0xE300000000ULL
#define QSMMU_NS_OFFSET_PCIE_1	0xE400000000ULL

#define QSMMU_PCIE_OFFSET0	0x3FD00000
#define QSMMU_PCIE_OFFSET1	0x3FE00000
#define QSMMU_PCIE_OFFSET2	0x3FF00000

#define CRYPTO0_QSMMU_BASE CE0_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE
#define CRYPTO1_QSMMU_BASE CE1_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F0_BASE
#define EMAC0_QSMMU_BASE GBE0_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE
#define EMAC1_QSMMU_BASE GBE1_QSMMUV3_STQS2_1_1_QAD11100_V64P44D64_C16UA_F1_BASE
#define HDMA0_QSMMU_BASE HDMA0_QSMMUV3_STQS256_8_8_QAD11100_V64P44D256_C16UA_F2_REG_BASE
#define HDMA1_QSMMU_BASE HDMA1_QSMMUV3_STQS256_8_8_QAD11100_V64P44D256_C16UA_F2_REG_BASE
#define HDMA2_QSMMU_BASE HDMA2_QSMMUV3_STQS256_8_8_QAD11100_V64P44D256_C16UA_F2_REG_BASE
#define HDMA3_QSMMU_BASE HDMA3_QSMMUV3_STQS256_8_8_QAD11100_V64P44D256_C16UA_F2_REG_BASE
#define IMC_QSMMU_BASE IMC_QSMMUV3_STS2_1_3_QAD10100_V64P44D64_C16S_F3_BASE
#define PCIE0_QSMMU_BASE PCIE0_QSMMUV3_STQS256_8_16_20_QAD11100_V64P44D256P32_CRL16UA_F9_REG_BASE
#define PCIE1_QSMMU_BASE PCIE1_QSMMUV3_STQS256_8_16_20_QAD11100_V64P44D256P32_CRL16UA_F8_REG_BASE
#define PCIE2_QSMMU_BASE PCIE2_QSMMUV3_STQS256_8_16_20_QAD11100_V64P44D256P32_CRL16UA_F8_REG_BASE
#define PCIE3_QSMMU_BASE PCIE3_QSMMUV3_STQS256_8_16_20_QAD11100_V64P44D256P32_CRL16UA_F9_REG_BASE
#define PCIE4_QSMMU_BASE PCIE4_QSMMUV3_STQS256_8_16_20_QAD11100_V64P44D256P32_CRL16UA_F8_REG_BASE
#define PCIE5_QSMMU_BASE PCIE5_QSMMUV3_STQS256_8_16_20_QAD11100_V64P44D256P32_CRL16UA_F8_REG_BASE
#define PSS_QSMMU_BASE PERIPH_QSMMUV3_STQS32_5_5_QAD11100_V64P44D64_C16UA_F6_REG_BASE
#define SATA0_QSMMU_BASE SATA0_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE
#define SATA1_QSMMU_BASE SATA1_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE
#define SATA2_QSMMU_BASE SATA2_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE
#define SATA3_QSMMU_BASE SATA3_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE
#define SATA4_QSMMU_BASE SATA4_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE
#define SATA5_QSMMU_BASE SATA5_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE
#define SATA6_QSMMU_BASE SATA6_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE
#define SATA7_QSMMU_BASE SATA7_QSMMUV3_STQS4_2_2_QAD11100_V64P44D64_C16UA_F7_REG_BASE

#ifdef CRYPTO0
#define QSMMU_BASE   CRYPTO0_QSMMU_BASE
#elif defined CRYPTO1
#define QSMMU_BASE   CRYPTO1_QSMMU_BASE
#elif defined EMAC0
#define QSMMU_BASE   EMAC0_QSMMU_BASE
#elif defined EMAC1
#define QSMMU_BASE   EMAC1_QSMMU_BASE
#elif defined HDMA0
#define QSMMU_BASE   HDMA0_QSMMU_BASE
#elif defined HDMA1
#define QSMMU_BASE   HDMA1_QSMMU_BASE
#elif defined HDMA2
#define QSMMU_BASE   HDMA2_QSMMU_BASE
#elif defined HDMA3
#define QSMMU_BASE   HDMA3_QSMMU_BASE
#elif defined IMCSS
#define QSMMU_BASE   IMC_QSMMU_BASE
#elif defined PCIE0
#define QSMMU_BASE   PCIE0_QSMMU_BASE
#elif defined PCIE1
#define QSMMU_BASE   PCIE1_QSMMU_BASE
#elif defined PCIE2
#define QSMMU_BASE   PCIE2_QSMMU_BASE
#elif defined PCIE3
#define QSMMU_BASE   PCIE3_QSMMU_BASE
#elif defined PCIE4
#define QSMMU_BASE   PCIE4_QSMMU_BASE
#elif defined PCIE5
#define QSMMU_BASE   PCIE5_QSMMU_BASE
#elif defined PSS
#define QSMMU_BASE   PSS_QSMMU_BASE
#elif defined SATA0
#define QSMMU_BASE   SATA0_QSMMU_BASE
#elif defined SATA1
#define QSMMU_BASE   SATA1_QSMMU_BASE
#elif defined SATA2
#define QSMMU_BASE   SATA2_QSMMU_BASE
#elif defined SATA3
#define QSMMU_BASE   SATA3_QSMMU_BASE
#elif defined SATA4
#define QSMMU_BASE   SATA4_QSMMU_BASE
#elif defined SATA5
#define QSMMU_BASE   SATA5_QSMMU_BASE
#elif defined SATA6
#define QSMMU_BASE   SATA6_QSMMU_BASE
#elif defined SATA7
#define QSMMU_BASE   SATA7_QSMMU_BASE
#endif

typedef enum {
  SIG_NONE = 0,
  SIG_IRQ = 1,
  SIG_SEV = 2
} SYNC_SIG;

typedef enum {
  SH_ATTR_NSH = 0,
  SH_ATTR_OSH = 2,
  SH_ATTR_ISH = 3
} SH_ATTR;

typedef enum {
  CH_ATTR_NC = 0,
  CH_ATTR_WB = 1,
  CH_ATTR_WT = 2,
} CH_ATTR;

typedef enum {
  MSI_ATTR_DEVICE_nGnRnE = 0x0,
  MSI_ATTR_DEVICE_nGnRE = 0x1,
  MSI_ATTR_DEVICE_nGRE = 0x2,
  MSI_ATTR_DEVICE_GRE = 0x3,
  MSI_ATTR_NORMAL_NC = 0x5,
  MSI_ATTR_NORMAL_WT = 0xa,
  MSI_ATTR_NORMAL_WB = 0xf
} MSI_ATTR;

typedef enum {
  CMD_PREFETCH_CONFIG = 0x01,
  CMD_PREFETCH_ADDR = 0x02,
  CMD_CFGI_STE = 0x03,
  CMD_CFGI_STE_RANGE = 0x04,
  CMD_CFGI_CD = 0x05,
  CMD_CFGI_CD_ALL = 0x06,
  CMD_TLBI_NH_ALL = 0x10,
  CMD_TLBI_NH_ASID = 0x11,
  CMD_TLBI_NH_VA = 0x12,
  CMD_TLBI_NH_VAA = 0x13,
  CMD_TLBI_EL3_ALL = 0x18,
  CMD_TLBI_EL3_VA = 0x1a,
  CMD_TLBI_EL2_ALL = 0x20,
  CMD_TLBI_EL2_ASID = 0x21,
  CMD_TLBI_EL2_VA = 0x22,
  CMD_TLBI_EL2_VAA = 0x23,
  CMD_TLBI_S12_VMALL = 0x28,
  CMD_TLBI_S2_IPA = 0x2a,
  CMD_TLBI_NSNH_ALL = 0x30,
  CMD_ATC_INV = 0x40,
  CMD_PRI_RESP = 0x41,
  CMD_RESUME = 0x44,
  CMD_STALL_TERM = 0x45,
  CMD_SYNC = 0x46
} CMD_TYPE;

typedef enum {
  EVENT_F_UUT = 0x1,
  EVENT_C_BAD_STREAMID = 0x2,
  EVENT_F_STE_FETCH = 0x3,
  EVENT_C_BAD_STE = 0x4,
  EVENT_F_BAD_ATS_TREQ = 0x5,
  EVENT_F_STREAM_DISABLED = 0x6,
  EVENT_F_TRANSL_FORBIDDEN = 0x7,
  EVENT_C_BAD_SUBSTREAMID = 0x8,
  EVENT_F_CD_FETCH = 0x9,
  EVENT_F_BAD_CD = 0xA,
  EVENT_F_WALK_EABT = 0xB,
  EVENT_F_TRANSLATION = 0x10,
  EVENT_F_ADDR_SIZE = 0x11,
  EVENT_F_ACCESS = 0x12,
  EVENT_F_PERMISSION = 0x13,
  EVENT_F_TLB_CONFLICT = 0x20,
  EVENT_F_CFG_CONFLICT = 0x21,
  EVENT_E_PAGE_REQUEST = 0x24
} EVENT_TYPE;

typedef enum {
  EC_CD = 0,	// CD fetch
  EC_TTD = 1,	// Stage 1 translation table fetch
  EC_IN = 2,	// Input address caused fault
} EVENT_CLASS;
typedef struct {
  uint32_t data[EVENT_BYTES/4];
  EVENT_TYPE type;
} event_struct;

void VVDRV_initIMEM(volatile uint64_t *imem_p, int32_t count);
void VVDRV_qsmmuv3_enableClocks(uint64_t reg_base);
void VVDRV_qsmmuv3_enableAllClocks();
int VVDRV_qsmmuv3_compare_data(uint32_t data_actual, uint32_t data_expect);
void VVDRV_qsmmuv3_default_enables(uint64_t reg_base, uint32_t secure);
void VVDRV_qsmmuv3_enable_dispatcher(uint64_t reg_base);
void VVDRV_qsmmuv3_disable_dispatcher(uint64_t reg_base);
void VVDRV_qsmmuv3_enable_RESP_TID_REPL_DIS(uint64_t reg_base);
void VVDRV_qsmmuv3_configureStreamTable(uint64_t reg_base, uint64_t strtab_base, uint32_t log2_numste, uint32_t secure);
void VVDRV_qsmmuv3_configureVMTable(uint64_t reg_base, uint64_t vmtab_base, uint32_t log2_numvmte);
void VVDRV_qsmmuv3_configureCommandQueue(uint64_t reg_base, uint64_t cmdq_base, uint32_t log2_numcmd, uint32_t secure);
void VVDRV_qsmmuv3_configureEventQueue(uint64_t reg_base, uint64_t cmdq_base, uint32_t log2_numcmd, uint32_t secure);
uint64_t VVDRV_qsmmuv3_readEventQueueBase( uint64_t reg_base, uint32_t secure);
uint32_t VVDRV_qsmmuv3_readEventQueueProdPtr( uint64_t reg_base, uint32_t secure);
uint32_t VVDRV_qsmmuv3_readEventQueueConsPtr( uint64_t reg_base, uint32_t secure);
uint32_t VVDRV_qsmmuv3_read_event ( uint64_t eventq_base, uint32_t index, event_struct* out_event_ptr );
void VVDRV_qsmmuv3_consume_next_event( uint64_t reg_base, uint32_t secure, event_struct* out_event_ptr );

void VVDRV_qsmmuv3_enable_TLB(uint64_t reg_base);
void VVDRV_qsmmuv3_disable_TLB_int_caching(uint64_t reg_base);
void VVDRV_qsmmuv3_enable_TLB_int_caching(uint64_t reg_base);
void VVDRV_qsmmuv3_enable_cfgcache(uint64_t reg_base);
void VVDRV_qsmmuv3_enable_cmdq(uint64_t reg_base, uint32_t secure);
void VVDRV_qsmmuv3_enable_eventq(uint64_t reg_base, uint32_t secure);
//void VVDRV_qsmmuv3_TableQueueAttributes(uint64_t reg_base, SH_ATTR table_sh, CH_ATTR table_oc, CH_ATTR table_ic, SH_ATTR queue_sh, CH_ATTR queue_oc, CH_ATTR queue_ic, uint32_t secure);
void VVDRV_qsmmuv3_enable(uint64_t reg_base, uint32_t secure);
void VVDRV_qsmmuv3_disable(uint64_t reg_base, uint32_t secure);
void VVDRV_qsmmuv3_enable_atschk(uint64_t reg_base);
void VVDRV_qsmmuv3_disable_atschk(uint64_t reg_base);
void VVDRV_qsmmuv3_enable_imc_msa_bypass_check(void);
void VVDRV_qsmmuv3_disable_imc_msa_bypass_check(void);
void VVDRV_qsmmuv3_enable_pss_msa_bypass_check(void);
void VVDRV_qsmmuv3_disable_pss_msa_bypass_check(void);
void VVDRV_qsmmuv3_enable_A53_protns_passthrough(void);
void VVDRV_qsmmuv3_intr_undef_addr(uint64_t reg_base, uint32_t secure);
void VVDRV_qsmmuv3_submit_CMD(uint64_t reg_base, uint32_t secure, uint32_t cmd_word[4]);
void VVDRV_qsmmuv3_CMD_ATC_INV(uint64_t reg_base, uint32_t global, uint32_t ssv, uint32_t substreamid, uint32_t streamid, uint32_t size, uint64_t address, uint32_t secure);
void VVDRV_qsmmuv3_CMD_SYNC(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t secure);
void VVDRV_qsmmuv3_CMD_TLBI_NH_ALL(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid);
void VVDRV_qsmmuv3_CMD_TLBI_NH_ASID(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid, uint32_t asid);
void VVDRV_qsmmuv3_CMD_TLBI_NH_VAA(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid, uint64_t addr, uint32_t leaf);
void VVDRV_qsmmuv3_CMD_TLBI_NH_VA(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t vmid, uint32_t asid, uint64_t addr, uint32_t leaf);
void VVDRV_qsmmuv3_CMD_TLBI_EL3_ALL(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr) ;
void VVDRV_qsmmuv3_CMD_TLBI_EL3_VA(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint64_t va) ;
void VVDRV_qsmmuv3_CMD_CFGI_STE(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t ssec, uint32_t sid);
void VVDRV_qsmmuv3_CMD_CFGI_CD(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t ssec, uint32_t sid);
void VVDRV_qsmmuv3_CMD_PREFETCH_CONFIG(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t sid, uint32_t ssec, int ssid);
void VVDRV_qsmmuv3_CMD_PREFETCH_ADDR(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t sid, uint32_t ssec, int ssid, uint64_t va, uint32_t size);
void VVDRV_qsmmuv3_DVM_CMDQ(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t secure);
void VVDRV_qsmmuv3_CMD_ILL(uint64_t reg_base, SYNC_SIG cs, uint32_t msi_attr, uint32_t msi_data, uint64_t msi_addr, uint32_t secure);
void VVDRV_qsmmuv3_CMD_RESUME(uint64_t reg_base, uint32_t action, uint32_t abort, uint32_t stream_id, uint32_t stag, uint32_t secure);
void VVDRV_qsmmuv3_base_addr(uint64_t *secure, uint64_t *nonsecure);
void VVDRV_qsmmuv3_setup_pcie_xlation(uint64_t desc_base, uint64_t cd_base, uint64_t s_strtab_base);
uint32_t VVDRV_qsmmuv3_readCommandQueueProdPtr( uint64_t reg_base, uint32_t secure);
uint32_t VVDRV_qsmmuv3_readCommandQueueConsPtr( uint64_t reg_base, uint32_t secure);
uint32_t VVDRV_qsmmuv3_isCommandQueueEmpty( uint64_t reg_base, uint32_t secure );
void VVDRV_qsmmuv3_full_system_barrier(void);
void VVDRV_qsmmuv3_set_httu_override( uint64_t reg_base); 
void VVDRV_qsmmuv3_clear_httu_override( uint64_t reg_base);  
uint32_t VVDRV_qsmmuv3_isEventQueueEmpty( uint64_t reg_base, uint32_t secure);
void VVDRV_qsmmuv3_consume_next_event( uint64_t reg_base, uint32_t secure, event_struct* out_event_ptr);

#endif

#ifndef CDVI_SVTB
void VVDRV_DVM_TLB_I(void);
void VVDRV_DVM_TLB_I_VA(uint64_t myaddr);
void VVDRV_DVM_TLB_I_ASIDE1IS(uint64_t myasid);
void VVDRV_DVM_TLB_I_Multi(uint64_t myaddr);
#endif
