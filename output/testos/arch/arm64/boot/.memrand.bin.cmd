cmd_arch/arm64/boot/memrand.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  memrand.strip arch/arm64/boot/memrand.bin
