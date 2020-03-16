cmd_arch/arm64/psci/built-in.lib :=  aarch64-linux-gnu-ld -EL  -maarch64linux  -r -o arch/arm64/psci/built-in.lib arch/arm64/psci/std_svc_setup.o arch/arm64/psci/psci.o
