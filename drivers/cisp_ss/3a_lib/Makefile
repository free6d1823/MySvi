STATIC_LIB := lib3a.a
SHARED_LIB := lib3a.so

# Set fallbacks if not set already
CC ?= /exports/kernels/juno-bsp_kernel-4.9/toolchain/bin/aarch64-linux-gnu-gcc
AR ?= /exports/kernels/juno-bsp_kernel-4.9/toolchain/bin/aarch64-linux-gnu-gcc-ar
RANLIB ?= /exports/kernels/juno-bsp_kernel-4.9/toolchain/bin/aarch64-linux-gnu-gcc-ranlib
FIRMWARE_CONTEXT_NUMBER ?= 16
CFLAGS?=-O3 -Wall 

CFLAGS+=-fPIC 
C_DEFINES := -DFIRMWARE_CONTEXT_NUMBER=$(FIRMWARE_CONTEXT_NUMBER) 
C_INCLUDES := -Iinclude/

SOURCES := $(shell find -type f -name '*.c')
OBJECTS := $(SOURCES:.c=.o)
LDFLAGS?=-lrt -ldl -pthread

REBUILDABLES = $(OBJECTS) $(STATIC_LIB) $(SHARED_LIB)

.PHONY: all static shared
all : static shared
static : $(STATIC_LIB)
shared : $(SHARED_LIB)

$(STATIC_LIB) : $(OBJECTS)
	@echo [AR] $@
	@$(AR) rc $@ $^
	@$(RANLIB) $@

$(SHARED_LIB): $(OBJECTS)
	@echo [LD] $@
	@$(CC) ${LDFLAGS} -shared -o $@ $^

%.o: %.c
	@echo [CC] $@
	@$(CC) $(CFLAGS) $(C_DEFINES) $(C_INCLUDES) -c -o $@ $<

clean :
	@rm -f $(REBUILDABLES)
	@echo 'Clean done'

print-%:
	@echo $*=$($*)
