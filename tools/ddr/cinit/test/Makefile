#  ------------------------------------------------------------------------
#
#                    (C) COPYRIGHT 2017 SYNOPSYS, INC.
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
ifndef ROOTDIR_ABS
ROOTDIR_ABS := $(shell cd ../; pwd)
endif
# Included makefiles
-include $(ROOTDIR_ABS)/bin/tgtDetect.mk

ifndef $(PHYINIT_SW_DIR)
  PHYINIT_SW_DIR := $(ROOTDIR_ABS)/../phy/software
endif 

ifndef $(PHYINIT_FW_DIR)
  PHYINIT_FW_DIR := $(ROOTDIR_ABS)/../phy/firmware
endif
PROTOCOL  = ddr5

# Output directories 
LIB_DIR := $(ROOTDIR_ABS)/lib
BUILD_DIR := $(ROOTDIR_ABS)/test/build

INCL_DIR := \
	$(ROOTDIR_ABS)/library/include \
	$(ROOTDIR_ABS)/library/custom \
	$(ROOTDIR_ABS)/../../../../scratch/headers \
	$(PHYINIT_SW_DIR)/$(PROTOCOL)/src \
	$(PHYINIT_FW_DIR)/$(PROTOCOL) \
	$(PHYINIT_FW_DIR)/$(PROTOCOL)_2d

DDR_LIBS := snpsDdr
DDR_STATIC_LIBS := $(DDR_LIBS:%=$(LIB_DIR)/lib%.a)
# Tell the linker where to search for libraries with -L
LDFLAGS += \
	$(foreach dir,$(LIB_DIR),-L$(dir))

# List the required libraries to link with -l
LDFLAGS += \
	-Wl,-Bstatic \
	$(foreach lib,$(DDR_LIBS),-l$(lib)) \
	-Wl,-Bdynamic \
	-lm

# Compiler Options	
CFLAGS += \
    $(foreach dir,$(INCL_DIR),-I$(dir))
CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -std=gnu99

SRC=cinit_main.c 
    
PROG_EXT=.exe

OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC)))
EXE := cinit_main$(PROG_EXT)

$(BUILD_DIR)/%.o : %.c
	$(VERBOSE)$(MKDIR) $(@D)
	@echo "Compiling $(<F)"
	$(VERBOSE)$(CC) $(CFLAGS) -c -o $@ $<
##############################################################################
# Targets
##############################################################################
.PHONY : all clean help debug

all : $(EXE)

debug :
	@echo "ROOTDIR_ABS = $(ROOTDIR_ABS)"
	@echo "BUILD_DIR = $(BUILD_DIR)"
	@echo "LIB_DIR = $(LIB_DIR)"
	@echo "INCL_DIR = $(INCL_DIR)"
	@echo "DDR_STATIC_LIBS = $(DDR_STATIC_LIBS)"
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"
	@echo "EXE = $(EXE)"
	@echo "LIB = $(LIB)"
	@echo "CFLAGS = $(CFLAGS)"

help :
	@echo ""
	@echo "This makefile builds the Synopsys DDR Controller Software library in the lib directory"
	@echo "make          - builds lib"
	@echo "make test     - builds lib and runs offline test"
	@echo "make clean    - deletes all generated targets"
	@echo "make help     - prints help"
	@echo ""

$(EXE) : $(DDR_STATIC_LIBS) $(OBJ)
	$(VERBOSE)$(MKDIR) $(@D)
	@echo "Linking binary: $(@F)"
	$(LD) $(OBJ) $(LDFLAGS) $(CFLAGS) -o $@

clean:
	$(VERBOSE)$(RM) $(EXE) $(OBJ) $(DDR_STATIC_LIBS) *.log core*

$(DDR_STATIC_LIBS) : 
	$(VERBOSE)$(MAKE) $(MAKE_VERBOSE) -C $(ROOTDIR_ABS)/library staticlib=1 trace=1 LIBNAME=snpsDdr

