#
# Makefile
#
# This file is part of the Ultibo project, https://ultibo.org/
#
# The MIT License (MIT)
#
# Copyright (c) 2025 Garry Wood <garry@softoz.com.au>
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

# Base path of the Ultibo API
API_PATH = ..

# List of C/C++ source files to compile (with .o extension)
OBJS = myfile.o

# List of static libraries to link (with .a extension)
# (eg LIBS = freetype.a sqlite3.a)
#LIBS =

# Additional GCC and G++ defines and options
#CFLAGS +=
#CPPFLAGS +=

# Additional GCC and G++ include paths
# (eg INCLUDE += -I $(API_PATH)/libs/freetype2 -I $(API_PATH)/libs/sqlite3)
#INCLUDE +=

# Additional FPC defines and options
FPCOPT += -dUSE_WEBSTATUS -dUSE_SHELL

# Name of the Ultibo project file
PROJECT_NAME = apiproject.lpr

include $(API_PATH)/Rules.mk
