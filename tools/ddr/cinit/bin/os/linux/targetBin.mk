#  ------------------------------------------------------------------------
#
#                    (C) COPYRIGHT 2014 SYNOPSYS, INC.
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

# Utilities
CC    := gcc
CPP   := g++
LD    := gcc
AR    := ar rcs
RM    := rm -Rf
CP    := cp
MKDIR := mkdir -p
CHMOD := chmod 755

# Optional Utilities
SWIG  := swig
TCLSH := tclsh
DOXYGEN := doxygen

# Compiler Options
CFLAGS += \
	-Wall

# Default is to always build for 64b arch
ifeq ($(32BIT),1)
  CFLAGS += -m32
else
  CFLAGS += -m64
endif

# Linker Options
LDFLAGS += \
    -fPIC

# Output options
PROG_EXT = 
SHARED_EXT = .so

# Export all variables
export
