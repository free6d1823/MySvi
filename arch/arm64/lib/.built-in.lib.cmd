cmd_arch/arm64/lib/built-in.lib :=  aarch64-linux-gnu-ld -EL  -maarch64linux  -r -o arch/arm64/lib/built-in.lib arch/arm64/lib/memcmp.o arch/arm64/lib/memmove.o arch/arm64/lib/memset.o arch/arm64/lib/strcmp.o arch/arm64/lib/strlen.o arch/arm64/lib/strncmp.o arch/arm64/lib/strnlen.o arch/arm64/lib/cache_helpers.o
