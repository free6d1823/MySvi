#
# arch/arm64/boot/Makefile
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies.
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

hvep := hvep.bin

quiet_cmd_strip     = STRIP   $@
      cmd_strip     = $(STRIP) -R .comment -R .note $< -o $@

hvep.strip: hvep FORCE
	$(call if_changed,strip)

dhrystone.strip: dhrystone FORCE
	$(call if_changed,strip)

linpack.strip: linpack FORCE
	$(call if_changed,strip)

saxpy.strip: saxpy FORCE
	$(call if_changed,strip)

qpower.strip: qpower FORCE
	$(call if_changed,strip)

ateinit.strip: ateinit FORCE
	$(call if_changed,strip)

glktest.strip: glktest FORCE
	$(call if_changed,strip)

tcmtest.strip: tcmtest FORCE
	$(call if_changed,strip)

asmpercpu.strip: asmpercpu FORCE
	$(call if_changed,strip)

memrand.strip: memrand FORCE
	$(call if_changed,strip)

arm64isa.strip: arm64isa FORCE
	$(call if_changed,strip)

$(obj)/hvep.bin: hvep.strip FORCE
	$(call if_changed,objcopy)

$(obj)/dhrystone.bin: dhrystone.strip FORCE
	$(call if_changed,objcopy)

$(obj)/linpack.bin: linpack.strip FORCE
	$(call if_changed,objcopy)

$(obj)/saxpy.bin: saxpy.strip FORCE
	$(call if_changed,objcopy)

$(obj)/qpower.bin: qpower.strip FORCE
	$(call if_changed,objcopy)

$(obj)/ateinit.bin: ateinit.strip FORCE
	$(call if_changed,objcopy)

$(obj)/glktest.bin: glktest.strip FORCE
	$(call if_changed,objcopy)

$(obj)/tcmtest.bin: tcmtest.strip FORCE
	$(call if_changed,objcopy)

$(obj)/asmpercpu.bin: asmpercpu.strip FORCE
	$(call if_changed,objcopy)

$(obj)/memrand.bin: memrand.strip FORCE
	$(call if_changed,objcopy)

$(obj)/arm64isa.bin: arm64isa.strip FORCE
	$(call if_changed,objcopy)
