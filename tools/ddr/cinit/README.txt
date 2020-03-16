###########################################
# UMCTL2 Controller initialization library.
###########################################
# TODO list
  - how to select TCK using CINIT or override to lower frequency?
  - VIRL_LPDDR4_BOOT_CLK_EN is used in ddrc_cfg and in software -> trace it and its meaning
  - VIRL_CID_EN is using hdlr->spdData_m.sg >= SG1600J_3DS2B) && (hdlr->spdData_m.sg <= SG3200AC_3DS4A  ?? Question this
  - calculation for rc_derate_byte and derate_value need to be part of ddr_timing?
  - if DLL_OFF mode is set then 8ns is the min TCK update the function for the max clock.

NB: currently we apply register reset values to the register structures but the mctl_qdyn_cfg_t and mctl_static_cfg_t 
have no defaults and rely on SV constraints.
So what happens if CINIT is used standalone?

