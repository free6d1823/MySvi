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
