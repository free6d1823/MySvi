#include <target/kbuild.h>
#include <target/compiler.h>
#include <target/utils.h>
#include <asm/ptrace.h>
#include <stddef.h>


int main(void)
{
  DEFINE(S_R0,		  offsetof(struct pt_regs, ARM_r0));
  DEFINE(S_R1,		  offsetof(struct pt_regs, ARM_r1));
  DEFINE(S_R2,		  offsetof(struct pt_regs, ARM_r2));
  DEFINE(S_R3,		  offsetof(struct pt_regs, ARM_r3));
  DEFINE(S_R4,		  offsetof(struct pt_regs, ARM_r4));
  DEFINE(S_R5,		  offsetof(struct pt_regs, ARM_r5));
  DEFINE(S_R6,		  offsetof(struct pt_regs, ARM_r6));
  DEFINE(S_R7,		  offsetof(struct pt_regs, ARM_r7));
  DEFINE(S_R8,		  offsetof(struct pt_regs, ARM_r8));
  DEFINE(S_R9,		  offsetof(struct pt_regs, ARM_r9));
  DEFINE(S_R10,		  offsetof(struct pt_regs, ARM_r10));
  DEFINE(S_FP,		  offsetof(struct pt_regs, ARM_fp));
  DEFINE(S_IP,		  offsetof(struct pt_regs, ARM_ip));
  DEFINE(S_SP,		  offsetof(struct pt_regs, ARM_sp));
  DEFINE(S_LR,		  offsetof(struct pt_regs, ARM_lr));
  DEFINE(S_PC,		  offsetof(struct pt_regs, ARM_pc));
  DEFINE(S_PSR,		  offsetof(struct pt_regs, ARM_cpsr));
  DEFINE(S_OLD_R0,	  offsetof(struct pt_regs, ARM_ORIG_r0));
  DEFINE(PT_REGS_SIZE,		sizeof(struct pt_regs));
  DEFINE(SVC_REGS_SIZE,		sizeof(struct svc_pt_regs));
  return 0;
}
