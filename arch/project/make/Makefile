
.PHNOY= all  clean
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

PROJECT_ROOT=../..

TARGET_NAME = armv7
OUTDIR = $(PROJECT_ROOT)/target

CFLAGS   =  -mcpu=cortex-m3 -mthumb -g -Wall -fno-builtin -fno-strict-aliasing 
CFLAGS  +=  -ffunction-sections -fdata-sections -fno-common -std=gnu99
CFLAGS  +=  -specs=nosys.specs -ggdb -fno-exceptions
CFLAGS  +=  -O0 -DDEBUG

LDFLAGS = -T  $(PROJECT_ROOT)/boot/boot.ld  -Wl,-Map=$(OUTDIR)/$(TARGET_NAME).map

INCLUDES =  -I$(PROJECT_ROOT)/include/asm  -I$(PROJECT_ROOT)/include/   -I$(PROJECT_ROOT)/lib/include

SRCS  =   $(PROJECT_ROOT)/boot/init.S   $(PROJECT_ROOT)/kernel/*.c    $(PROJECT_ROOT)/mm/*.c
SRCS  +=  $(PROJECT_ROOT)/test/*.c  $(PROJECT_ROOT)/lib/*.c


all:
	mkdir   $(OUTDIR)
	$(CC)  -o $(OUTDIR)/$(TARGET_NAME).elf    $(CFLAGS) $(LDFLAGS)  $(SRCS) $(INCLUDES)
	$(OBJCOPY)  -O   ihex  $(OUTDIR)/$(TARGET_NAME).elf   $(OUTDIR)/$(TARGET_NAME).hex
	$(OBJCOPY)  -O   binary  $(OUTDIR)/$(TARGET_NAME).elf   $(OUTDIR)/$(TARGET_NAME).bin



clean:
	rm -rf  *.o   $(OUTDIR)


