cmd_arch/arm64/boot/hvep.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  hvep.strip arch/arm64/boot/hvep.bin
