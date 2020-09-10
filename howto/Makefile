help:
	@echo Help:
	@echo "    make zebu   : create image for zebu"
	@echo "    make vcs    : create hex files for vcs"
	@echo "    make vdkrom : create vdkrom"
	@echo "    make r52rom : create r52rom"

zebu: linux.hex

linux.hex: se1000_debug.dtb.hex Image.hex rootfs.cpio.hex
	cat se1000_debug.dtb.hex Image.hex rootfs.cpio.hex > $@

se1000_debug.dtb.hex: se1000_debug.dtb
	./bin4zebu.sh se1000_debug.dtb 0x00200000

se1000_debug.dtb:
	dtc -I dts -O dtb se1000_debug.dts >$@

Image.hex:
	./bin4zebu.sh ~/linux/arch/arm64/boot/Image 0x00280000

rootfs.cpio.hex:
	./bin4zebu.sh ../rootfs.cpio 0x04000000

vdkrom: vdkrom.S Makefile
	aarch64-linux-gnu-gcc $< -nostdlib -Ttext=0x58000000 -DENTRY=0x10000 -Wl,--build-id=none -Wl,-n -o vdkrom.elf
	aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S vdkrom.elf $@

r52rom: r52rom.S Makefile
	arm-none-eabi-gcc $< -nostdlib -Ttext=0x38000000 -DENTRY=0x60000000 -Wl,--build-id=none -Wl,-n -o r52rom.elf
	arm-none-eabi-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S r52rom.elf $@

vcs:
	./bin4vcs.sh ../arch/arm64/boot/hvep.bin

m4vcs:
	./bin4vcs.sh ../arch/arm64/boot/hvep.bin ../arch/armv7m/boot/hvep.bin
