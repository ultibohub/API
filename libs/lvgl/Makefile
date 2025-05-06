#
# Makefile for LVGL graphics library v9.2.2
#

# Default to arm arch
ARCH_TYPE ?= arm

# Default to unknown board
BOARD_TYPE ?= unknown

ifeq ($(OS),Windows_NT)
API_PATH = C:/Ultibo/API
else
API_PATH = $(HOME)/ultibo/api
endif

# Default to level 2 optimization
OPT_LEVEL ?= -O2

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

# Setup arch specific parameters
ifeq ($(strip $(ARCH_TYPE)),arm)

# Setup board specific parameters
ifeq ($(strip $(BOARD_TYPE)),rpib)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv6 -mfpu=vfp -mfloat-abi=hard -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBO -DRPIB
TARGET_NAME ?= rpi
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi2b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBO -DRPI2B
TARGET_NAME ?= rpi2
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi3b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBOO -DRPI3B
TARGET_NAME ?= rpi3
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),rpi4b)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBO -DRPI4B
TARGET_NAME ?= rpi4
TOOLS_PREFIX ?= arm-none-eabi-
else ifeq ($(strip $(BOARD_TYPE)),qemuvpb)
CC_FLAGS ?= --specs=nosys.specs $(OPT_LEVEL) -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBO -DQEMUVPB
TARGET_NAME ?= qemuvpb
TOOLS_PREFIX ?= arm-none-eabi-
else
$(error No valid board type specified (BOARD_TYPE=$(BOARD_TYPE)))
endif

else ifeq ($(strip $(ARCH_TYPE)),aarch64)

# Setup board specific parameters
ifeq ($(strip $(BOARD_TYPE)),rpi3b)
CC_FLAGS ?= --specs=rdimon.specs $(OPT_LEVEL) -march=armv8-a -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBO -DRPI3B
TARGET_NAME ?= rpi3
TOOLS_PREFIX ?= aarch64-none-elf-
else ifeq ($(strip $(BOARD_TYPE)),rpi4b)
CC_FLAGS ?= --specs=rdimon.specs $(OPT_LEVEL) -march=armv8-a -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBO -DRPI4B
TARGET_NAME ?= rpi4
TOOLS_PREFIX ?= aarch64-none-elf-
else ifeq ($(strip $(BOARD_TYPE)),qemuvpb)
CC_FLAGS ?= --specs=rdimon.specs $(OPT_LEVEL) -march=armv8-a -D__DYNAMIC_REENT__ -D__LARGE64_FILES -D_REENT_BACKWARD_BINARY_COMPAT -D_POSIX_THREADS -D_UNIX98_THREAD_MUTEX_ATTRIBUTES -DFD_SETSIZE=1024 -DULTIBO -DQEMUVPB
TARGET_NAME ?= qemuvpb
TOOLS_PREFIX ?= aarch64-none-elf-
else
$(error No valid board type specified (BOARD_TYPE = $(BOARD_TYPE)))
endif

else
$(error No valid architecture type specified (ARCH_TYPE = $(ARCH_TYPE)))
endif

LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}

include $(LVGL_DIR)/$(LVGL_DIR_NAME)/lvgl.mk

INCLUDE	+= -I $(LVGL_DIR)
INCLUDE	+= -I $(API_PATH)/include

CC	= $(TOOLS_PREFIX)gcc
CPP	= $(TOOLS_PREFIX)g++
AS	= $(CC)
LD	= $(TOOLS_PREFIX)ld
AR	= $(TOOLS_PREFIX)ar

AFLAGS	+= $(CC_FLAGS) $(INCLUDE)
CFLAGS	+= $(CC_FLAGS) -Wall $(INCLUDE)
CPPFLAGS+= $(CC_FLAGS) -Wall $(INCLUDE) -std=c++17

OBJEXT ?= .o

LIBS = liblvgl.a

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
CPPOBJS = $(CXXSRCS:$(CXXEXT)=$(OBJEXT))

OBJS = $(AOBJS) $(COBJS)

all: clean default

%.o: %.S
	@$(AS) $(AFLAGS) -c $< -o $@
	@echo "AS $<"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $<"

%.o: %.cc
	@$(CPP) $(CPPFLAGS) -c $< -o $@
	@echo "CPP $<"

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@
	@echo "CPP $<"

default: $(AOBJS) $(COBJS) $(CPPOBJS)
	@$(AR) rcs $(LIBS) $(AOBJS) $(COBJS) $(CPPOBJS)
	@echo "AR $(LIBS)"

clean:
	rm -f $(LIBS) $(AOBJS) $(COBJS) $(CPPOBJS)
