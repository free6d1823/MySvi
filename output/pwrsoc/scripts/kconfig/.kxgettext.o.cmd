cmd_scripts/kconfig/kxgettext.o := gcc -Wp,-MD,scripts/kconfig/.kxgettext.o.d -Iscripts/kconfig -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer -I/home/cj/MySvi/include -Iinclude -DCURSES_LOC="<ncurses.h>" -DLOCALE -c -o scripts/kconfig/kxgettext.o /home/cj/MySvi/scripts/kconfig/kxgettext.c

deps_scripts/kconfig/kxgettext.o := \
  /home/cj/MySvi/scripts/kconfig/kxgettext.c \
  /usr/include/stdc-predef.h \
  /usr/include/stdlib.h \
    $(wildcard include/config/en.h) \
    $(wildcard include/config/en2k8.h) \
    $(wildcard include/config/c.h) \
    $(wildcard include/config/c99.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/ern/inlines.h) \
    $(wildcard include/config/en/extended.h) \
    $(wildcard include/config/ix.h) \
    $(wildcard include/config/en2k.h) \
    $(wildcard include/config/c11.h) \
    $(wildcard include/config/cxx11.h) \
    $(wildcard include/config/e/offset64.h) \
    $(wildcard include/config/gefile64.h) \
    $(wildcard include/config/en2kxsi.h) \
    $(wildcard include/config/tify/level.h) \
  /usr/include/features.h \
    $(wildcard include/config/c95.h) \
    $(wildcard include/config/ix2.h) \
    $(wildcard include/config/ix199309.h) \
    $(wildcard include/config/ix199506.h) \
    $(wildcard include/config/x98.h) \
    $(wildcard include/config/en2k8xsi.h) \
    $(wildcard include/config/gefile.h) \
    $(wildcard include/config/ile.h) \
    $(wildcard include/config/ntrant.h) \
    $(wildcard include/config/ix/implicitly.h) \
  /usr/include/x86_64-linux-gnu/sys/cdefs.h \
    $(wildcard include/config/espaces.h) \
  /home/cj/MySvi/include/bits/wordsize.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stddef.h \
  /usr/include/x86_64-linux-gnu/bits/waitflags.h \
  /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
  /usr/include/endian.h \
  /usr/include/x86_64-linux-gnu/bits/endian.h \
  /usr/include/x86_64-linux-gnu/bits/byteswap.h \
  /usr/include/x86_64-linux-gnu/bits/types.h \
  /usr/include/x86_64-linux-gnu/bits/typesizes.h \
  /usr/include/x86_64-linux-gnu/bits/byteswap-16.h \
  /usr/include/x86_64-linux-gnu/sys/types.h \
  /usr/include/time.h \
  /usr/include/x86_64-linux-gnu/sys/select.h \
  /usr/include/x86_64-linux-gnu/bits/select.h \
  /usr/include/x86_64-linux-gnu/bits/sigset.h \
  /usr/include/x86_64-linux-gnu/bits/time.h \
  /usr/include/x86_64-linux-gnu/bits/select2.h \
  /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
  /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/alloca.h \
  /usr/include/x86_64-linux-gnu/bits/stdlib-bsearch.h \
  /usr/include/x86_64-linux-gnu/bits/stdlib-float.h \
  /usr/include/x86_64-linux-gnu/bits/stdlib.h \
  /usr/include/string.h \
    $(wildcard include/config/ing/inlines.h) \
  /usr/include/xlocale.h \
  /usr/include/x86_64-linux-gnu/bits/string.h \
    $(wildcard include/config/ing/arch/memset.h) \
    $(wildcard include/config/ing/arch/strchr.h) \
  /usr/include/x86_64-linux-gnu/bits/string2.h \
  /usr/include/x86_64-linux-gnu/bits/string3.h \
  /home/cj/MySvi/scripts/kconfig/lkc.h \
    $(wildcard include/config/list.h) \
  /home/cj/MySvi/scripts/kconfig/expr.h \
  /usr/include/stdio.h \
  /usr/include/libio.h \
    $(wildcard include/config/ar/t.h) \
    $(wildcard include/config//io/file.h) \
  /usr/include/_G_config.h \
  /usr/include/wchar.h \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
  /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
  /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
  /usr/include/x86_64-linux-gnu/bits/stdio.h \
  /usr/include/x86_64-linux-gnu/bits/stdio2.h \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdbool.h \
  /home/cj/MySvi/scripts/kconfig/lkc_port.h \
  /usr/include/libintl.h \
    $(wildcard include/config//gettext.h) \
  /usr/include/locale.h \
  /usr/include/x86_64-linux-gnu/bits/locale.h \
  /home/cj/MySvi/scripts/kconfig/lkc_proto.h \

scripts/kconfig/kxgettext.o: $(deps_scripts/kconfig/kxgettext.o)

$(deps_scripts/kconfig/kxgettext.o):
