cmd_arch/arm64/boot/saxpy.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  saxpy.strip arch/arm64/boot/saxpy.bin
