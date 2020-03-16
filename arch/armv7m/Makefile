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
ARMV7M_CFLAGS	+= \
	-mcpu=cortex-m4 \
	-funsigned-char \
	-fno-builtin-printf -fno-builtin-fprintf \
	-fstack-protector \
	-fno-strict-aliasing \
	-fno-common \
	-fverbose-asm \
	-ffunction-sections -fdata-sections \
	-Wno-unused \
	-Wno-nonnull-compare \

ARMV7M_CFLAGS += -mthumb -march=armv7e-m -mtune=cortex-m4

CFLAGS		+=$(ARMV7M_CFLAGS)
AFLAGS		+=$(ARMV7M_CFLAGS) -x assembler-with-cpp
LDFLAGS_hvep	:=--gc-sections -p --no-undefined -X

#svi has float calculation which cortexm4 doesn't support, seems need libgcc
LDFLAGS_m4_extra    :=  -lgcc  -L /opt/gcc-arm-none-eabi-8-2019-q3-update/lib/gcc/arm-none-eabi/8.3.1/thumb/v7e-m/nofp/


ifdef CONFIG_CC_GEN_DEBUG
CFLAGS		+= -g
AFLAGS		+= -g
endif

# Select a platform tht is kept up-to-date
KBUILD_DEFCONFIG := imc_defconfig

# Default program entry
head-y		:= arch/armv7m/common/startup.o

machine-$(CONFIG_ARCH_CORTEXM4)    := cortexm4

ifeq ($(incdir-y),)
incdir-y := $(machine-y)
endif
INCDIR   := mach-$(incdir-y)

ifneq ($(machine-y),)
MACHINE  := arch/armv7m/mach-$(machine-y)/
else
MACHINE  :=
endif

#plat-$(CONFIG_ARCH_CENTRIQ)       := centriq

machdirs := $(patsubst %,arch/armv7m/mach-%/,$(machine-y))
platdirs := $(patsubst %,arch/armv7m/plat-%/,$(plat-y))

export	GZFLAGS

# If we have a machine-specific directory, then include it in the build.
core-y				+= arch/armv7m/common/
core-y				+= arch/armv7m/lib/
drivers-y			+= $(machdirs) $(platdirs)

# Default target when executing plain make
KBUILD_IMAGE := hvep.bin

all:	$(KBUILD_IMAGE)

boot := arch/armv7m/boot

#	Update machine arch and proc symlinks if something which affects
#	them changed.  We use .arch to indicate when they were updated
#	last, otherwise make uses the target directory mtime.

include/asm/mach: $(wildcard include/config/arch/*.h) \
		include/config/auto.conf include/asm
	@echo '  SYMLINK include/asm/mach -> include/asm/$(INCDIR)'
	$(Q)$(SYMLINK) $(TOPDIR)/arch/armv7m/include/asm/$(INCDIR) $@

archprepare: maketools

PHONY += maketools FORCE
maketools: include/asm/mach FORCE

hvep.bin: hvep
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@

CLEAN_DIRS += arch/$(ARCH)/include/asm/mach
CLEAN_FILES += arch/$(ARCH)/include/asm/mach-types.h
CLEAN_FILES += arch/$(ARCH)/boot/hvep.bin

all:	$(KBUILD_IMAGE)

boot := arch/armv7m/boot

# We use MRPROPER_FILES and CLEAN_FILES now
archclean:
	$(Q)$(MAKE) $(clean)=$(boot)

define archhelp
  echo  '  hvep.bin        - Binary image (arch/$(ARCH)/boot/hvep.bin)'
endef
