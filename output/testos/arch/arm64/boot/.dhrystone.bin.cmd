cmd_arch/arm64/boot/dhrystone.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  dhrystone.strip arch/arm64/boot/dhrystone.bin
