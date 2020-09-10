# Find all folders and use them as a include path.
LIB3A_PATH:=../3a_lib
INC_FOLDERS := $(shell find "$(PWD)" -type d)
CFLAGS+=$(addprefix -I,$(INC_FOLDERS))
CFLAGS+=-I$(LIB3A_PATH)/include
obj-y :=

obj-y += ./src/
obj-y += ./isp/
obj-y += ./platform/
obj-y += ./util/
obj-y += ./sbus/
obj-y += ./connection/
obj-y += ./sensor/
obj-y += ./afbc/
