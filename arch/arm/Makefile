#
# arch/arm/Makefile
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies.
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

OBJCOPYFLAGS	:=-O binary -R .note -R .note.gnu.build-id -R .comment -S
ARM_CFLAGS	+= \
	-funsigned-char \
	-fno-builtin-printf -fno-builtin-fprintf \
	-fstack-protector \
	-fno-strict-aliasing \
	-fno-common \
	-fverbose-asm \
	-ffunction-sections -fdata-sections \
	-Wno-unused \
	-Wno-nonnull-compare \

ARM_CFLAGS += -march=armv8-r

CFLAGS		+=$(ARM_CFLAGS)
AFLAGS		+=$(ARM_CFLAGS) -x assembler-with-cpp
LDFLAGS_hvep	:=--gc-sections -p --no-undefined -X

LDFLAGS_r52_extra    :=  -lgcc  -L /opt/gcc-arm-none-eabi-8-2019-q3-update/lib/gcc/arm-none-eabi/8.3.1/

ifdef CONFIG_CC_GEN_DEBUG
CFLAGS		+= -g
AFLAGS		+= -g
endif

# Select a platform tht is kept up-to-date
KBUILD_DEFCONFIG := _defconfig

# Default program entry
head-y		:= arch/arm/common/head.o

machine-y    := r52

ifeq ($(incdir-y),)
incdir-y := $(machine-y)
endif
INCDIR   := mach-$(incdir-y)

ifneq ($(machine-y),)
MACHINE  := arch/arm/mach-$(machine-y)/
else
MACHINE  :=
endif

machdirs := $(patsubst %,arch/arm/mach-%/,$(machine-y))
platdirs := $(patsubst %,arch/arm/plat-%/,$(plat-y))

export	GZFLAGS

# If we have a machine-specific directory, then include it in the build.
core-y				+= arch/arm/common/
core-y				+= arch/arm/lib/
drivers-y			+= $(machdirs) $(platdirs)

# Default target when executing plain make
KBUILD_IMAGE := hvep.bin

all:	$(KBUILD_IMAGE)

boot := arch/arm/boot

#	Update machine arch and proc symlinks if something which affects
#	them changed.  We use .arch to indicate when they were updated
#	last, otherwise make uses the target directory mtime.

include/asm/mach: $(wildcard include/config/arch/*.h) \
		include/config/auto.conf include/asm
	@echo '  SYMLINK include/asm/mach -> include/asm/$(INCDIR)'
	$(Q)$(SYMLINK) $(TOPDIR)/arch/arm/include/asm/$(INCDIR) $@

archprepare: maketools

PHONY += maketools FORCE
maketools: include/asm/mach FORCE

hvep.bin: hvep
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@

CLEAN_DIRS += arch/$(ARCH)/include/asm/mach
CLEAN_FILES += arch/$(ARCH)/include/asm/mach-types.h
CLEAN_FILES += arch/$(ARCH)/boot/hvep.bin

all:	$(KBUILD_IMAGE)

boot := arch/arm/boot

# We use MRPROPER_FILES and CLEAN_FILES now
archclean:
	$(Q)$(MAKE) $(clean)=$(boot)

define archhelp
  echo  '  hvep.bin        - Binary image (arch/$(ARCH)/boot/hvep.bin)'
endef
