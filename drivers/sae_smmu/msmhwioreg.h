#ifndef __MSMHWIOREG_H__
#define __MSMHWIOREG_H__

#include "msmhwiobase.h"
#define IMC_CSR_REG_BASE                                                           (IMC_BASE      + 0x003c0000)
#define HWIO_IMC_MSA_CTRL_ADDR                                                     (IMC_CSR_REG_BASE      + 0x00000300)
#define HWIO_QSMMU_MSA_TRANS_CHECK_ADDR                                            (IMC_CSR_REG_BASE      + 0x00000314)
#define HWIO_IMC_PROTNS_CTRL_ADDR                                                  (IMC_CSR_REG_BASE      + 0x00000304)
#define HWIO_IMC_MSA_CTRL_RMSK                                                     0x80000003
#define HWIO_IMC_PROTNS_CTRL_RMSK                                                  0x80000003                                                        
#define HWIO_QSMMU_MSA_TRANS_CHECK_RMSK                                                   0x3
#define HWIO_QSMMU_MSA_TRANS_CHECK_IN          \
        in_dword_masked(HWIO_QSMMU_MSA_TRANS_CHECK_ADDR, HWIO_QSMMU_MSA_TRANS_CHECK_RMSK)
#define HWIO_IMC_MSA_CTRL_IN          \
                in_dword_masked(HWIO_IMC_MSA_CTRL_ADDR, HWIO_IMC_MSA_CTRL_RMSK)        
#define HWIO_QSMMU_MSA_TRANS_CHECK_IMC_CHECK_BMSK                                         0x1
#define HWIO_QSMMU_MSA_TRANS_CHECK_PERPH_CHECK_BMSK                                       0x2
#define HWIO_IMC_PROTNS_CTRL_PROTNS_EXTERNAL_ENA_SHFT                                     0x1
#define HWIO_IMC_PROTNS_CTRL_PROTNS_EXTERNAL_ENA_BMSK                                     0x2                       

#define HWIO_IMC_MSA_CTRL_MSA_CTRL_WRITTEN_BMSK                                    0x80000000
#define HWIO_IMC_MSA_CTRL_MSA_CTRL_WRITTEN_SHFT                                          0x1f
#define HWIO_IMC_MSA_CTRL_MSA_CTRL_WRITTEN_NOT_WRITTEN_FVAL                               0x0
#define HWIO_IMC_MSA_CTRL_MSA_CTRL_WRITTEN_WRITTEN_FVAL                                   0x1
#define HWIO_IMC_MSA_CTRL_MSA_EXTERNAL_ENA_BMSK                                           0x2
#define HWIO_IMC_MSA_CTRL_MSA_EXTERNAL_ENA_SHFT                                           0x1
#define HWIO_IMC_MSA_CTRL_MSA_EXTERNAL_ENA_QSMMU_DEASSERT_FVAL                            0x0
#define HWIO_IMC_MSA_CTRL_MSA_EXTERNAL_ENA_QSMMU_ASSERT_FVAL                              0x1
#define HWIO_IMC_MSA_CTRL_MSA_INTERNAL_ENA_BMSK                                           0x1
#define HWIO_IMC_MSA_CTRL_MSA_INTERNAL_ENA_SHFT                                           0x0
#define HWIO_IMC_MSA_CTRL_MSA_INTERNAL_ENA_CORTEXA53_DEASSERT_FVAL                        0x0
#define HWIO_IMC_MSA_CTRL_MSA_INTERNAL_ENA_CORTEXA53_ASSERT_FVAL                          0x1



#define HWIO_QSMMU_MSA_TRANS_CHECK_OUT(v)      \
                out_dword(HWIO_QSMMU_MSA_TRANS_CHECK_ADDR,v)
#define HWIO_IMC_PROTNS_CTRL_OUTM(m,v) \
                        out_dword_masked_ns(HWIO_IMC_PROTNS_CTRL_ADDR,m,v,HWIO_IMC_PROTNS_CTRL_IN)              
#define HWIO_IMC_PROTNS_CTRL_IN          \
                                in_dword_masked(HWIO_IMC_PROTNS_CTRL_ADDR, HWIO_IMC_PROTNS_CTRL_RMSK)
#define HWIO_IMC_MSA_CTRL_OUTM(m,v) \
                                        out_dword_masked_ns(HWIO_IMC_MSA_CTRL_ADDR,m,v,HWIO_IMC_MSA_CTRL_IN)                                
#endif
