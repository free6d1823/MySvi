cmd_arch/arm64/boot/qpower.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  qpower.strip arch/arm64/boot/qpower.bin
