cmd_arch/arm64/boot/tcmtest.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  tcmtest.strip arch/arm64/boot/tcmtest.bin
