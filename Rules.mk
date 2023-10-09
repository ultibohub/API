#
# Rules.mk
#
# This file is part of the Ultibo project, https://ultibo.org/
#
# The MIT License (MIT)
#
# Copyright (c) 2023 Garry Wood <garry@softoz.com.au>
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
FPC_PATH = C:/Ultibo/Core/fpc/3.2.2/bin/i386-win32/
endif

# Include user customizations without error if file doesn't exist
-include $(API_PATH)/Config.mk

BOARD_TYPE ?= unknown

BUILD_MODE ?= release

# Normalize board type
ifeq ($(strip $(BOARD_TYPE)),rpia)
override BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpia+)
override BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpib+)
override BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpi0)
override BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpi0w)
override BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpicm)
override BOARD_TYPE = rpib
else ifeq ($(strip $(BOARD_TYPE)),rpi3a+)
override BOARD_TYPE = rpi3b
else ifeq ($(strip $(BOARD_TYPE)),rpi3b+)
override BOARD_TYPE = rpi3b
else ifeq ($(strip $(BOARD_TYPE)),rpicm3)
override BOARD_TYPE = rpi3b
else ifeq ($(strip $(BOARD_TYPE)),rpi02w)
override BOARD_TYPE = rpi3b
else ifeq ($(strip $(BOARD_TYPE)),rpi400)
override BOARD_TYPE = rpi4b
else ifeq ($(strip $(BOARD_TYPE)),rpicm4)
override BOARD_TYPE = rpi4b
else ifeq ($(strip $(BOARD_TYPE)),qemu)
override BOARD_TYPE = qemuvpb
endif

OPT_LEVEL ?= -O2

# Setup board specific parameters
ifeq ($(strip $(BOARD_TYPE)),rpib)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv6 -mfpu=vfp -mfloat-abi=hard -D__DYNAMIC_REENT__ -D_POSIX_THREADS -DULTIBO -DRPIB
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV6 -WpRPIB @$(FPC_PATH)RPI.CFG $(OPT_LEVEL) -dRPIB $(PROJECT_NAME)
TARGET_NAME ?= rpi
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi2b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D_POSIX_THREADS -DULTIBO -DRPI2B
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV7A -WpRPI2B @$(FPC_PATH)RPI2.CFG $(OPT_LEVEL) -dRPI2B $(PROJECT_NAME)
TARGET_NAME ?= rpi2
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi3b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D_POSIX_THREADS -DULTIBO -DRPI3B
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV7A -WpRPI3B @$(FPC_PATH)RPI3.CFG $(OPT_LEVEL) -dRPI3B $(PROJECT_NAME)
TARGET_NAME ?= rpi3
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi4b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D_POSIX_THREADS -DULTIBO -DRPI4B
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV7A -WpRPI4B @$(FPC_PATH)RPI4.CFG $(OPT_LEVEL) -dRPI4B $(PROJECT_NAME)
TARGET_NAME ?= rpi4
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),qemuvpb)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D_POSIX_THREADS -DULTIBO -DQEMUVPB
FPC_FLAGS ?= -B -Tultibo -Parm -CpARMV7A -WpQEMUVPB @$(FPC_PATH)QEMUVPB.CFG $(OPT_LEVEL) -dQEMUVPB $(PROJECT_NAME)
TARGET_NAME ?= qemuvpb
TOOLS_PREFIX ?= arm-none-eabi-
else
$(error No valid board type specified (BOARD_TYPE = $(BOARD_TYPE)))
endif

# Setup build mode
ifeq ($(strip $(BUILD_MODE)),debug)
CC_FLAGS += -DDEBUG
FPC_FLAGS += -dDEBUG
else
CC_FLAGS += -DRELEASE
FPC_FLAGS += -dRELEASE
endif

# Setup default libs
ifeq ($(strip $(LIBS)),)
LIBS = c.a
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
FPCOPT  += $(FPC_FLAGS)

all: info clean $(TARGET_NAME)

%.a:
	@$(shell) echo {$$LINKLIB $@} >>  __linklib.inc

%.o: %.S
	@$(AS) $(AFLAGS) -c -o $@ $<
	@echo "AS $<"
	@$(shell) echo {$$LINK $@} >>  __link.inc

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "CC $<"
	@$(shell) echo {$$LINK $@} >>  __link.inc

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c -o $@ $<
	@echo "CPP $<"
	@$(shell) echo {$$LINK $@} >>  __link.inc

$(TARGET_NAME): $(OBJS) $(LIBS)
	@echo "FPC $(PROJECT_NAME)"
	@$(FPC) $(FPCOPT)

clean:
	rm -f *.o *.a *.elf *.lst *.img *.bin *.map *~ *.ppu link*.res
	rm -f __link.inc
	rm -f __linklib.inc

info:
	@echo Build Information
	@echo -----------------
	@echo  -
	@echo  - BOARD_TYPE = $(BOARD_TYPE)
	@echo  - BUILD_MODE = $(BUILD_MODE)
	@echo  - OBJS = $(OBJS)
	@echo  - LIBS = $(LIBS)
	@echo  - CFLAGS = $(CFLAGS)
	@echo  - FPCOPT = $(FPCOPT)
	@echo  -
