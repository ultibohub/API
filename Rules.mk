#
# Rules.mk
#
# This file is part of the Ultibo project, https://ultibo.org/
#
# The MIT License (MIT)
#
# Copyright (c) 2018 Garry Wood <garry@softoz.com.au>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

ifeq ($(strip $(API_PATH)),)
API_PATH = ..
endif

ifeq ($(strip $(FPC_PATH)),)
FPC_PATH = C:/Ultibo/Core/fpc/3.1.1/bin/i386-win32/
endif

-include $(API_PATH)/Config.mk

BOARD_TYPE ?= RPI2B

# Normalize board type
ifeq ($(strip $(BOARD_TYPE)),rpia)
BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpia+)
BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpib+)
BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpi0)
BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpi0w)
BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpi3b+)
BOARD_TYPE = rpi3b
else ifeq ($(strip $(BOARD_TYPE)),qemu)
BOARD_TYPE = qemuvpb
endif

OPT_LEVEL ?= -O2

# Setup board specific parameters
ifeq ($(strip $(BOARD_TYPE)),rpib)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv6 -mfpu=vfp -mfloat-abi=hard -D__DYNAMIC_REENT__
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV6 -WpRPIB @$(FPC_PATH)RPI.CFG $(OPT_LEVEL) -dRPIB $(PROJECT_NAME)
TARGET_NAME ?= rpi
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi2b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV7A -WpRPI2B @$(FPC_PATH)RPI2.CFG $(OPT_LEVEL) -dRPI2B $(PROJECT_NAME)
TARGET_NAME ?= rpi2
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi3b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV7A -WpRPI3B @$(FPC_PATH)RPI3.CFG $(OPT_LEVEL) -dRPI3B $(PROJECT_NAME)
TARGET_NAME ?= rpi3
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),qemuvpb)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV7A -WpQEMUVPB @$(FPC_PATH)QEMUVPB.CFG $(OPT_LEVEL) -dQEMUVPB $(PROJECT_NAME)
TARGET_NAME ?= qemuvpb
TOOLS_PREFIX ?= arm-none-eabi-
else
$(error No valid board type specified.)
endif

CC	= $(TOOLS_PREFIX)gcc
CPP	= $(TOOLS_PREFIX)g++
AS	= $(CC)
LD	= $(TOOLS_PREFIX)ld
AR	= $(TOOLS_PREFIX)ar
FPC = $(FPC_PATH)fpc

INCLUDE	+= -I $(API_PATH)/include

AFLAGS	+= $(CC_FLAGS) $(INCLUDE)
CFLAGS	+= $(CC_FLAGS) -Wall $(INCLUDE)
CPPFLAGS+= $(CFLAGS) -std=c++14

%.o: %.S
	$(AS) $(AFLAGS) -c -o $@ $<
	$(shell) echo {$$LINK $@} >>  __link.inc
    
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 
	$(shell) echo {$$LINK $@} >>  __link.inc
    
%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<
	$(shell) echo {$$LINK $@} >>  __link.inc

$(TARGET_NAME): $(OBJS) $(LIBS)
	$(FPC) $(FPC_FLAGS)

clean:
	rm -f *.o *.a *.elf *.lst *.img *.bin *.map *~ *.ppu
	rm __link.inc
