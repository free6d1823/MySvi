#  ------------------------------------------------------------------------
#
#                    (C) COPYRIGHT 2018 SYNOPSYS, INC.
#                            ALL RIGHTS RESERVED
#
# This software and the associated  documentation are proprietary to Synopsys,
# Inc. This software may only be used in accordance with the terms and 
# conditions of a written license agreement with Synopsys, Inc. All other use,
# reproduction, or distribution of this software is strictly prohibited.
#
# The entire notice above must be reproduced on all authorized copies.
#
#  -----------------------------------------------------------------------
VERBOSE := @
# required definitions

ifndef LINK_PHYINT
  # control whether PHYINT objects are to be linked into 
  # the library produced.
  LINK_PHYINT=1
endif

ifndef ROOTDIR_ABS
ROOTDIR_ABS := $(shell cd ../; pwd)
endif

PROTOCOL  = lpddr4

ifeq ($(PROTOCOL),ddr5_rdimm)
  PROTOCOL_PHYINIT_FW_DIR_2D := ddr5_rdimm2d
else
  PROTOCOL_PHYINIT_FW_DIR_2D := $(PROTOCOL)_2d
endif

# Included makefiles
-include $(ROOTDIR_ABS)/bin/tgtDetect.mk

ifeq ($(FW_VERSION),)
  FW_VERSION="unknown_version"
endif

ifndef $(PHYINIT_SW_DIR)
  PHYINIT_SW_DIR := $(ROOTDIR_ABS)/../phy/software
endif 

ifndef $(PHYINIT_FW_DIR)
  PHYINIT_FW_DIR := $(ROOTDIR_ABS)/../phy/firmware
endif 

ifndef $(PHY_VDEFINES_FILE)
  PHY_VDEFINES_FILE := $(ROOTDIR_ABS)/../../../sim_mctl/testbench/macros/dwc_ddrphy_VDEFINES.v
endif

ifeq ($(LINK_PHYINT),1)
  PHYINIT_OBJ:= $(wildcard $(PHYINIT_SW_DIR)/$(PROTOCOL)_64/*.o )
  LIBNAME := cinit_phyinit_$(PROTOCOL)
  CFLAGS+=-DPHYINIT
else
  PHYINIT_OBJ:=
  LIBNAME := cinit
endif

# Output directories 
BUILD_DIR := $(ROOTDIR_ABS)/library/build
LIB_DIR := $(ROOTDIR_ABS)/lib
BIN_DIR := $(ROOTDIR_ABS)/bin

ifdef staticlib
  LIB := $(LIB_DIR)/lib$(LIBNAME).a
else
  # switches for shared object linked for simulation.
  CFLAGS+=-DSIM_MODE -fPIC
  LIB := $(LIB_DIR)/lib$(LIBNAME)$(SHARED_EXT)
endif

# These C headers will get converted to system-verilog syntax
C_HDR := $(ROOTDIR_ABS)/library/include/dwc_cinit_reg_struct.h \
  $(ROOTDIR_ABS)/library/include/dwc_cinit_regs.h \
  $(ROOTDIR_ABS)/library/include/dwc_cinit_cfg.h \
  $(ROOTDIR_ABS)/library/include/dwc_cinit_types.h \
  $(ROOTDIR_ABS)/library/include/dwc_cinit_dyn_struct.h \
  $(ROOTDIR_ABS)/library/include/dwc_cinit_qdyn_struct.h \
  $(ROOTDIR_ABS)/library/include/dwc_cinit_static_struct.h 


SV_HDR = $(C_HDR:.h=.svh)
# Include paths to pass to compiler 
INCL_DIR := \
	$(ROOTDIR_ABS)/library/include \
	$(ROOTDIR_ABS)/library/custom \
	$(PHYINIT_SW_DIR)/$(PROTOCOL)/src \
	$(PHYINIT_FW_DIR)/$(PROTOCOL) \
	$(PHYINIT_FW_DIR)/$(PROTOCOL_PHYINIT_FW_DIR_2D)

# header generated from verilog files
CC_CONSTANTS_FILE := /projects/soc_prj1/se1000/shuo.zhang/se1000/thirdip/ddrctl/DWC_ddrctl_v2.0/src/DWC_ddrctl_cc_constants.svh

CC_CONSTANTS_FILE_PREFIX := 

GEN_HDR := $(ROOTDIR_ABS)/library/include/DWC_ddrctl.h
# verilog source file used to generate c defines
V_SRC := \
   $(CC_CONSTANTS_FILE_PREFIX) \
   $(CC_CONSTANTS_FILE) \
   $(PHY_VDEFINES_FILE)

# Source file(s)

SRC := \
  $(notdir $(wildcard $(ROOTDIR_ABS)/library/src/*.c)) \
  $(notdir $(wildcard $(ROOTDIR_ABS)/library/custom/*.c)) 

# Source search paths
VPATH := \
	$(ROOTDIR_ABS)/library/src \
	$(ROOTDIR_ABS)/library/custom \
	$(PHYINIT_SW_DIR)

OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC)))
DEP := $(patsubst %.c,$(BUILD_DIR)/%.d,$(notdir $(SRC)))

CFLAGS += \
    $(foreach dir,$(INCL_DIR),-I$(dir))

CFLAGS += -g -std=gnu99
#CFLAGS += -Wno-unused-but-set-variable 
ifdef trace
  CFLAGS += -D_TRACE
endif


##############################################################################
# Targets
##############################################################################
.PHONY : all clean help debug
all: $(SV_HDR) $(LIB) 

clean: 
	rm -f $(SV_HDR)
	rm -rf $(BUILD_DIR) $(LIB_DIR)/*$(PROTOCOL)*.so $(DEP) $(GEN_HDR) ./include/DWC_ddrctl_header.h

debug :
	@echo "SRC = $(SRC)"
	@echo "C_HDR = $(C_HDR)"
	@echo "SV_HDR = $(SV_HDR)"
	@echo "OBJ = $(OBJ)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "LIB = $(LIB)"
	@echo "BUILD_DIR = $(BUILD_DIR)"
	@echo "INCL_DIR = $(INCL_DIR)"
	@echo "PHYINIT_OBJ = $(PHYINIT_OBJ)"

# The header files that are shared between simulation and C library are
# created shared.
# The syntax is very similar.
%.svh: %.h $(C_HDR)
	@echo "Converting $(<F) to systemverilog"
	$(VERBOSE) $(ROOTDIR_ABS)/bin/post_proc_c.pl -c_to_sv -src $<
	
$(BUILD_DIR)/%.o : %.c $(GEN_HDR)
	$(VERBOSE)$(MKDIR) $(@D)
	@echo "Compiling $(<F)"
	$(VERBOSE)$(COMPILE.c) $(OUTPUT_OPTION) $< ## -DFW_VERSION=$(FW_VERSION)

# Create a shared object for simulation
$(LIB_DIR)/%.so:$(OBJ) 
	@echo "Linking shared library $(@F)"
	$(VERBOSE)$(MKDIR) $(@D)
	$(VERBOSE)$(CC) -shared $(LDFLAGS) $(CFLAGS) -o $(LIB) $(OBJ) $(PHYINIT_OBJ)

$(LIB_DIR)/%.a : $(OBJ)
	@echo "Linking static library $(@F)"
	$(VERBOSE)$(MKDIR) $(@D)
	$(VERBOSE)$(AR) $@ $(OBJ)

$(GEN_HDR) :
ifndef CC_CONSTANTS_FILE
	$(error You must define the environment var CC_CONSTANTS_FILE = path to coreConsultant DWC_ddrctl_cc_constants.sv)
endif
	@echo "Generating header file DWC_ddrctl_header.h"
	$(VERBOSE) $(ROOTDIR_ABS)/bin/post_proc_c.pl  -umctl_header\
	  -src $(ROOTDIR_ABS)/../../../scratch/headers/DWC_ddrctl_header.h \
	  -out $(ROOTDIR_ABS)/library/include/DWC_ddrctl_header.h
	@echo "Generating header file $(@F)"
	$(VERBOSE) $(ROOTDIR_ABS)/bin/generate_c_defines_from_verilog.pl $@ $(V_SRC)


# Dependencies
-include $(DEP)


