cmd_arch/arm64/boot/linpack.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  linpack.strip arch/arm64/boot/linpack.bin
