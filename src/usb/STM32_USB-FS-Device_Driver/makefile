# Compile the STM32F10x USB Full Speed Library

TARGET_ARCH = -mcpu=cortex-m3 -mthumb
TARGET_OPTS = -O2 -finline -finline-functions-called-once
WARNINGS = -Wall -W -Wshadow -Wwrite-strings -Winline
INCLUDE_DIRS = -I inc -I /usr/arm-none-eabi/include/STM32F10x/ -I /usr/arm-none-eabi/include/CMSIS -I ../STM32F10x_StdPeriph_Driver -I ../STM32F10x_StdPeriph_Driver/inc -I .
F_NO_STRICT_ALIASING = -fno-strict-aliasing
DEFINES = -DSTM32F10X_MD

COMPILE_OPTS = $(WARNINGS) $(TARGET_OPTS) $(MESSAGES) $(F_NO_STRICT_ALIASING) $(INCLUDE_DIRS) $(DEFINES)

CC = arm-none-eabi-gcc
CFLAGS = $(COMPILE_OPTS)

AS = $(CC) -x assembler-with-cpp -c $(TARGET_ARCH)
ASFLAGS = $(COMPILE_OPTS)

AR = arm-none-eabi-ar
ARFLAGS = cr

LIB_OUT = libstm32usb.a

LIB_OBJS = $(sort \
 $(patsubst %.c,%.o,$(wildcard src/*.c)) \
 $(patsubst %.s,%.o,$(wildcard src/*.s)))


.PHONY: all
all: $(LIB_OUT)

$(LIB_OUT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $(LIB_OBJS)

$(LIB_OBJS): $(wildcard *.h) $(wildcard inc/*.h)

.PHONY: clean
clean:
	-rm -f $(LIB_OBJS) $(LIB_OUT)
