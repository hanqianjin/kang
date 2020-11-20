CROSS_COMPILE_ARM = arm-linux-gnueabihf-
AS		= $(CROSS_COMPILE_ARM)as
LD		= $(CROSS_COMPILE_ARM)ld
CC		= $(CROSS_COMPILE_ARM)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE_ARM)ar
NM		= $(CROSS_COMPILE_ARM)nm

STRIP		= $(CROSS_COMPILE_ARM)strip
OBJCOPY		= $(CROSS_COMPILE_ARM)objcopy
OBJDUMP		= $(CROSS_COMPILE_ARM)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

CFLAGS := -Wall -O0 -g
CFLAGS += -I $(shell pwd)/unity_api/functions/include -I $(shell pwd)/unity_api/functions -I. -I.. -I../.. -I$(shell pwd)/unity_api/functions/nmealib -I$(shell pwd)/unity_api/functions/alsa_lib/include

LDFLAGS :=-L$(shell pwd)/unity_api/functions/alsa_lib/lib -lpthread  -lm -lasound

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

TARGET := SysCtrl

obj-y += whoref.o
obj-y += DiIoCtrl.o
obj-y += BitSehInfo.o
obj-y += MidMsg.o
obj-y += ShmEngine.o
obj-y += msgNoticeCode.o
obj-y += main.o
obj-y += unity_api/

all : 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) $(LDFLAGS) -g -o $(TARGET) built-in.o -lpthread  -lm -lasound


clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)
	
