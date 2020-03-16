cmd_arch/arm64/boot/arm64isa.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  arm64isa.strip arch/arm64/boot/arm64isa.bin
