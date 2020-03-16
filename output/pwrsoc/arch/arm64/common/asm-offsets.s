	.arch armv8.1-a+crypto+crc
	.file	"asm-offsets.c"
// GNU C11 (Linaro GCC 7.4-2019.02) version 7.4.1 20181213 [linaro-7.4-2019.02 revision 56ec6f6b99cc167ff0c2f8e1a2eed33b1edc85d4] (aarch64-linux-gnu)
//	compiled by GNU C version 4.8.4, GMP version 6.1.2, MPFR version 3.1.5, MPC version 1.0.3, isl version none
// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// options passed:  -nostdinc -I include -I include/std -I include2
// -I /home/cj/MySvi/include -I include/hdts -I /home/cj/MySvi/. -I .
// -I /home/cj/MySvi/include -I include -I /home/cj/MySvi/include/std
// -I include/std -I /home/cj/MySvi/include2 -I include2
// -I /home/cj/MySvi/include -I /home/cj/MySvi/include/hdts -I include/hdts
// -imultiarch aarch64-linux-gnu
// -iprefix /opt/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/7.4.1/
// -isysroot /opt/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/../aarch64-linux-gnu/libc
// -D __KERNEL__ -D KBUILD_CONF -D AARCH64 -D CONFIG_BROKEN_GAS_INST=1
// -D CONFIG_ARCH_SUPPORTS_INT128
// -include /home/cj/MySvi/include/target/config.h
// -include /home/cj/MySvi/include/target/config.h
// -MD arch/arm64/common/.asm-offsets.s.d
// /home/cj/MySvi/arch/arm64/common/asm-offsets.c -mlittle-endian
// -mtune=cortex-a53 -mcmodel=large -mstrict-align
// -march=armv8.1-a+crypto+fp+simd+crc -mpc-relative-literal-loads
// -mabi=lp64 -auxbase-strip arch/arm64/common/asm-offsets.s -g -g -Wall
// -Wno-unused -Werror -funsigned-char -fshort-wchar -fno-builtin-printf
// -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common
// -fno-short-enums -ffunction-sections -fdata-sections -ffixed-x18
// -fno-asynchronous-unwind-tables -fomit-frame-pointer -fverbose-asm
// options enabled:  -faggressive-loop-optimizations -fauto-inc-dec
// -fchkp-check-incomplete-type -fchkp-check-read -fchkp-check-write
// -fchkp-instrument-calls -fchkp-narrow-bounds -fchkp-optimize
// -fchkp-store-bounds -fchkp-use-static-bounds
// -fchkp-use-static-const-bounds -fchkp-use-wrappers -fdata-sections
// -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
// -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
// -ffunction-sections -fgcse-lm -fgnu-runtime -fgnu-unique -fident
// -finline-atomics -fira-hoist-pressure -fira-share-save-slots
// -fira-share-spill-slots -fivopts -fkeep-static-consts
// -fleading-underscore -flifetime-dse -flto-odr-type-merging -fmath-errno
// -fmerge-debug-strings -fomit-frame-pointer -fpeephole -fplt
// -fprefetch-loop-arrays -freg-struct-return
// -fsched-critical-path-heuristic -fsched-dep-count-heuristic
// -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
// -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
// -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
// -fshow-column -fshrink-wrap-separate -fsigned-zeros
// -fsplit-ivs-in-unroller -fssa-backprop -fstack-protector -fstdarg-opt
// -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
// -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
// -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
// -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
// -fverbose-asm -fzero-initialized-in-bss -mfix-cortex-a53-835769
// -mfix-cortex-a53-843419 -mglibc -mlittle-endian
// -momit-leaf-frame-pointer -mpc-relative-literal-loads -mstrict-align

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.main,"ax",@progbits
	.align	2
	.global	main
	.type	main, %function
main:
.LFB0:
	.file 1 "/home/cj/MySvi/arch/arm64/common/asm-offsets.c"
	.loc 1 5 0
	.cfi_startproc
// /home/cj/MySvi/arch/arm64/common/asm-offsets.c:6: 	return 0;
	.loc 1 6 0
	mov	w0, 0	// _1,
// /home/cj/MySvi/arch/arm64/common/asm-offsets.c:7: }
	.loc 1 7 0
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.text
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x4a
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF0
	.byte	0xc
	.4byte	.LASF1
	.4byte	.LASF2
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF3
	.byte	0x1
	.byte	0x4
	.4byte	0x46
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB0
	.8byte	.LFE0
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF1:
	.string	"/home/cj/MySvi/arch/arm64/common/asm-offsets.c"
.LASF0:
	.ascii	"GNU C11 7.4.1 20181213 [linaro-7.4-2019.02 revision 56ec6f6b"
	.ascii	"99cc167ff0c2f8e1a2eed33b1edc85d4] -mlittle-endian -mtune=cor"
	.ascii	"tex-a53 -mcmodel=large -mstrict-align -march=armv8.1-a+crypt"
	.ascii	"o+fp+simd+crc -mpc-relative-literal-loads "
	.string	"-mabi=lp64 -g -g -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -ffunction-sections -fdata-sections -ffixed-x18 -fno-asynchronous-unwind-tables -fomit-frame-pointer"
.LASF2:
	.string	"/home/cj/MySvi/output/pwrsoc"
.LASF3:
	.string	"main"
	.ident	"GCC: (Linaro GCC 7.4-2019.02) 7.4.1 20181213 [linaro-7.4-2019.02 revision 56ec6f6b99cc167ff0c2f8e1a2eed33b1edc85d4]"
	.section	.note.GNU-stack,"",@progbits
