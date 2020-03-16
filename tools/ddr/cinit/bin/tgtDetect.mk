#  ------------------------------------------------------------------------
#
#                    (C) COPYRIGHT 2014 SYNOPSYS, INC.
#                            ALL RIGHTS RESERVED
#
#  This software and the associated documentation are confidential and
#  proprietary to Synopsys, Inc.  Your use or disclosure of this
#  software is subject to the terms and conditions of a written
#  license agreement between you, or your company, and Synopsys, Inc.
#
# The entire notice above must be reproduced on all authorized copies.
#
#  -----------------------------------------------------------------------

#
# Makefile snipet to detect current target platform and include the appropriate
# variables.
#
ifndef ROOTDIR_ABS
$(error ROOTDIR_ABS is not defined)
endif

# Determine current target platform
HOST_PLATFORM := $(shell uname | cut -d _ -f 1 | tr [:upper:] [:lower:])

# If HARDWARE_TARGET is defined then we'll append it to the host platform that
# we are running on. This is used for specific flavour of target platform.
ifdef HARDWARE_TARGET
TARGET := $(HOST_PLATFORM).$(HARDWARE_TARGET)
else
TARGET := $(HOST_PLATFORM)
endif

##############################################################################
# Path definition
OS_ABS_PATH := $(ROOTDIR_ABS)/bin/os/$(TARGET)

# Include host/target specific options
include $(OS_ABS_PATH)/targetBin.mk
