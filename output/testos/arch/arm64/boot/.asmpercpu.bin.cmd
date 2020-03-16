cmd_arch/arm64/boot/asmpercpu.bin := aarch64-linux-gnu-objcopy -O binary -R .note -R .note.gnu.build-id -R .comment -S  asmpercpu.strip arch/arm64/boot/asmpercpu.bin
