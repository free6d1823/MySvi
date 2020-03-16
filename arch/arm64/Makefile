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
ARM64_CFLAGS	+= \
	-DAARCH64 \
	-mtune=cortex-a53 \
	-mcmodel=large \
	-mstrict-align \
	-funsigned-char \
	-fshort-wchar \
	-fno-builtin-printf -fno-builtin-fprintf \
	-fstack-protector \
	-fno-strict-aliasing \
	-fno-common \
	-fno-short-enums \
	-fverbose-asm \
	-ffunction-sections -fdata-sections \
	-ffixed-x18 \
	-Wno-unused \

ARM64_CFLAGS += -march=armv8.1-a+crypto+fp+simd+crc

CFLAGS		+=$(ARM64_CFLAGS)
AFLAGS		+=$(ARM64_CFLAGS) -x assembler-with-cpp
LDFLAGS_hvep	:=--gc-sections -p --no-undefined -X

ifeq ($(CONFIG_ARM64_ERRATUM_843419),y)
  ifeq ($(call ld-option, --fix-cortex-a53-843419),)
$(warning ld does not support --fix-cortex-a53-843419; kernel may be susceptible to erratum)
  else
LDFLAGS_vmlinux	+= --fix-cortex-a53-843419
  endif
endif

ifdef CONFIG_CC_GEN_DEBUG
CFLAGS		+= -g
AFLAGS		+= -g
endif

# Select a platform tht is kept up-to-date
KBUILD_DEFCONFIG := imc_defconfig

# Check for binutils support for specific extensions
lseinstr := $(call as-instr,.arch_extension lse,-DCONFIG_AS_LSE=1)

ifeq ($(CONFIG_ARM64_LSE_ATOMICS), y)
  ifeq ($(lseinstr),)
$(warning LSE atomics not supported by binutils)
  endif
endif

ifeq ($(CONFIG_ARM64), y)
brokengasinst := $(call as-instr,1:\n.inst 0\n.rept . - 1b\n\nnop\n.endr\n,,-DCONFIG_BROKEN_GAS_INST=1)

  ifneq ($(brokengasinst),)
$(warning Detected assembler with broken .inst; disassembly will be unreliable)
  endif
endif

CFLAGS	+= $(lseinstr) $(brokengasinst)
CFLAGS	+= -fno-asynchronous-unwind-tables
CFLAGS	+= $(call cc-option, -mpc-relative-literal-loads)
AFLAGS	+= $(lseinstr) $(brokengasinst)

#CFLAGS	+= $(call cc-option,-mabi=lp64)
#AFLAGS	+= $(call cc-option,-mabi=lp64)

CFLAGS	+= $(call cc-ifversion, -ge, 0500, -DCONFIG_ARCH_SUPPORTS_INT128)
CFLAGS	+= $(call cc-option,-Werror)

ifeq ($(CONFIG_CPU_BIG_ENDIAN), y)
CPPFLAGS	+= -mbig-endian
CHECKFLAGS	+= -D__AARCH64EB__
AS		+= -EB
LD		+= -EB
LDFLAGS		+= -maarch64linuxb
UTS_MACHINE	:= aarch64_be
else
CPPFLAGS	+= -mlittle-endian
CHECKFLAGS	+= -D__AARCH64EL__
AS		+= -EL
LD		+= -EL
LDFLAGS		+= -maarch64linux
UTS_MACHINE	:= aarch64
endif

CHECKFLAGS	+= -D__aarch64__ -m64


# Default program entry
head-y		:= arch/arm64/common/head.o

machine-$(CONFIG_ARCH_QDF2400)    := qdf2400
machine-$(CONFIG_ARCH_VIRT)    := virt
machine-$(CONFIG_ARCH_SE1000)    := se1000

ifeq ($(incdir-y),)
incdir-y := $(machine-y)
endif
INCDIR   := mach-$(incdir-y)

ifneq ($(machine-y),)
MACHINE  := arch/arm64/mach-$(machine-y)/
else
MACHINE  :=
endif

plat-$(CONFIG_ARCH_CENTRIQ)       := centriq

machdirs := $(patsubst %,arch/arm64/mach-%/,$(machine-y))
platdirs := $(patsubst %,arch/arm64/plat-%/,$(plat-y))

export	GZFLAGS

# If we have a machine-specific directory, then include it in the build.
core-y				+= arch/arm64/common/
core-y				+= arch/arm64/lib/
core-$(CONFIG_PSCI)		+= arch/arm64/psci/
drivers-y			+= $(machdirs) $(platdirs)

# Default target when executing plain make
KBUILD_IMAGE := hvep.bin
ifeq ($(CONFIG_TESTOS_DHRYSTONE), y)
KBUILD_IMAGE += dhrystone.bin
endif
ifeq ($(CONFIG_TESTOS_LINPACK), y)
KBUILD_IMAGE += linpack.bin
endif
ifeq ($(CONFIG_TESTOS_SAXPY), y)
KBUILD_IMAGE += saxpy.bin
endif
ifeq ($(CONFIG_TESTOS_QPOWER), y)
KBUILD_IMAGE += qpower.bin
endif
ifeq ($(CONFIG_TESTOS_ATEINIT), y)
KBUILD_IMAGE += ateinit.bin
endif
ifeq ($(CONFIG_TESTOS_GLKTEST), y)
KBUILD_IMAGE += glktest.bin
endif
ifeq ($(CONFIG_TESTOS_TCMTEST), y)
KBUILD_IMAGE += tcmtest.bin
endif
ifeq ($(CONFIG_TESTOS_ASMPERCPU), y)
KBUILD_IMAGE += asmpercpu.bin
endif
ifeq ($(CONFIG_TESTOS_MEMRAND), y)
KBUILD_IMAGE += memrand.bin
endif
ifeq ($(CONFIG_TESTOS_ARM64ISA), y)
KBUILD_IMAGE += arm64isa.bin
endif

all:	$(KBUILD_IMAGE)

boot := arch/arm64/boot

#	Update machine arch and proc symlinks if something which affects
#	them changed.  We use .arch to indicate when they were updated
#	last, otherwise make uses the target directory mtime.

include/asm/mach: $(wildcard include/config/arch/*.h) \
		include/config/auto.conf include/asm
	@echo '  SYMLINK include/asm/mach -> include/asm/$(INCDIR)'
	$(Q)$(SYMLINK) $(TOPDIR)/arch/arm64/include/asm/$(INCDIR) $@

archprepare: maketools

PHONY += maketools FORCE
maketools: include/asm/mach FORCE

hvep.bin: hvep
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
dhrystone.bin: dhrystone
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
linpack.bin: linpack
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
saxpy.bin: saxpy
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
qpower.bin: qpower
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
ateinit.bin: ateinit
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
glktest.bin: glktest
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
tcmtest.bin: tcmtest
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
asmpercpu.bin: asmpercpu
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
memrand.bin: memrand
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@
arm64isa.bin: arm64isa
	$(Q)$(MAKE) $(build)=$(boot) MACHINE=$(MACHINE) $(boot)/$@

CLEAN_DIRS += arch/$(ARCH)/include/asm/mach
CLEAN_FILES += arch/$(ARCH)/include/asm/mach-types.h
CLEAN_FILES += arch/$(ARCH)/boot/hvep.bin
CLEAN_FILES += arch/$(ARCH)/boot/dhrystone.bin
CLEAN_FILES += arch/$(ARCH)/boot/linpack.bin
CLEAN_FILES += arch/$(ARCH)/boot/saxpy.bin
CLEAN_FILES += arch/$(ARCH)/boot/qpower.bin
CLEAN_FILES += arch/$(ARCH)/boot/ateinit.bin
CLEAN_FILES += arch/$(ARCH)/boot/glktest.bin
CLEAN_FILES += arch/$(ARCH)/boot/tcmtest.bin
CLEAN_FILES += arch/$(ARCH)/boot/asmpercpu.bin
CLEAN_FILES += arch/$(ARCH)/boot/memrand.bin
CLEAN_FILES += arch/$(ARCH)/boot/arm64isa.bin

all:	$(KBUILD_IMAGE)

boot := arch/arm64/boot

# We use MRPROPER_FILES and CLEAN_FILES now
archclean:
	$(Q)$(MAKE) $(clean)=$(boot)

define archhelp
  echo  '  hvep.bin        - Binary image (arch/$(ARCH)/boot/hvep.bin)'
  echo  '  dhrystone.bin   - Binary image (arch/$(ARCH)/boot/dhrystone.bin)'
  echo  '  linpack.bin     - Binary image (arch/$(ARCH)/boot/linpack.bin)'
  echo  '  saxpy.bin       - Binary image (arch/$(ARCH)/boot/saxpy.bin)'
  echo  '  qpower.bin      - Binary image (arch/$(ARCH)/boot/qpower.bin)'
  echo  '  ateinit.bin     - Binary image (arch/$(ARCH)/boot/ateinit.bin)'
  echo  '  glktest.bin     - Binary image (arch/$(ARCH)/boot/glktest.bin)'
  echo  '  tcmtest.bin     - Binary image (arch/$(ARCH)/boot/tcmtest.bin)'
  echo  '  asmpercpu.bin   - Binary image (arch/$(ARCH)/boot/asmpercpu.bin)'
  echo  '  memrand.bin     - Binary image (arch/$(ARCH)/boot/memrand.bin)'
  echo  '  arm64isa.bin    - Binary image (arch/$(ARCH)/boot/arm64isa.bin)'
endef
