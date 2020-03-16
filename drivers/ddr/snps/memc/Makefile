
obj-y := dwc_cinit_amap_reg_prgm.o dwc_cinit_ddr_jedec.o dwc_cinit_reg_prgm.o
obj-y += dwc_cinit_arb_reg_prgm.o dwc_cinit_freq_reg_prgm.o dwc_ddr_jedec_timing.o
obj-y += dwc_cinit.o dwc_cinit_lpddr_jedec.o dwc_cinit_phyinit_setuserinput_lpddr54.o
obj-y += dwc_cinit_ddrc_reg_prgm.o dwc_cinit_pre_cfg.o dwc_cinit_print.o cinit_main.o

ccflags-y += -Wno-incompatible-pointer-types 

ccflags-$(CONFIG_DDR_PHY_LPDDR4) += -Idrivers/ddr/snps/phys/lpddr4/sw/ -Idrivers/ddr/snps/phys/lpddr4/fw/
ccflags-$(CONFIG_DDR_PHY_LPDDR5) += -Idrivers/ddr/snps/phys/lpddr5/sw/ -Idrivers/ddr/snps/phys/lpddr5/fw/