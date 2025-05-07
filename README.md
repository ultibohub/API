## Ultibo API

Ultibo core API for C and C++

### Supported interfaces:

The includes folder contains header files for interfaces to the following Ultibo APIs

* ultibo/console.h - Text console device interfaces, windowing and output
* ultibo/devices.h - Base device interface and common devices such as clock, timer and random
* ultibo/devicetree.h - Device tree interfaces and enumeration
* ultibo/dma.h - DMA controller access 
* ultibo/filesystem.h - Standard file system interfaces for all supported file systems
* ultibo/font.h - Text mode font handling and enumeration
* ultibo/framebuffer.h - Framebuffer device access and configuration
* ultibo/globalconst.h - Definitions common to many device interfaces
* ultibo/globaltypes.h - Structures and types used by various parts the API
* ultibo/gpio.h - GPIO device functionality
* ultibo/graphicsconsole.h - Graphics console device interfaces and output
* ultibo/heapmanager.h - Heap manager access for specialized memory handling
* ultibo/hid.h - Human interface device (HID) parsing and device configuration
* ultibo/i2c.h - I2C device access and configuration
* ultibo/iphlpapi.h - IP Helper API compatible interface for Winsock and Winsock2
* ultibo/joystick.h - Joystick and gamepad device interfaces
* ultibo/keyboard.h - Keyboard device interface and keyboard buffer
* ultibo/keymap.h - Keymap handling and enumeration
* ultibo/locale.h - Locale configuration and management
* ultibo/logging.h - Logging device interface
* ultibo/mmc.h - MMC/SD/SDIO device interface and configuration
* ultibo/mouse.h - Mouse device interface and mouse buffer
* ultibo/network.h - Network device access and configuration
* ultibo/platform.h - Common platform functionality
* ultibo/pwm.h - PWM device access and configuration
* ultibo/rtc.h - Real time clock device interface
* ultibo/serial.h - Serial device access and configuration
* ultibo/spi.h - SPI device access and configuration
* ultibo/storage.h - Storage (disk) device handling and enumeration
* ultibo/system.h - System specific types and definitions
* ultibo/sysutils.h - System utility  types and definitions
* ultibo/tftframebuffer.h - TFT framebuffer device access and configuration
* ultibo/threads.h - Thread and synchronization interfaces
* ultibo/timezone.h - Timezone handling and enumeration
* ultibo/touch.h - Touch device access and configuration 
* ultibo/uart.h - UART device access and configuration
* ultibo/ultibo.h - Ultibo specific and compatibility interfaces
* ultibo/unicode.h - Uncode text functionality
* ultibo/usb.h - USB device access, configuration and enumeration
* ultibo/winsock.h - Winsock 1.1 compatible sockets interface
* ultibo/winsock2.h - Winsock 2.0 compatible sockets interface

In addition to the Ultibo interface headers a small number of headers that expose functionality not normally available in the Newlib C library are also provided

* netdb.h - Definitions for network database operations
* semaphore.h - Definitions for performing semaphore operations
* arpa/inet.h - Definitions for internet operations
* netinet/in.h - Internet address family definitions
* netinet6/in6.h - IPv6 address family definitions
* sys/_iovec.h - Vector I/O data structure
* sys/_pthreadtypes.h - Structure definitions for pthreads (Redefined)
* sys/cpuset.h - Definitions for manipulating CPU sets
* sys/dirent.h - Directory entry definition and access
* sys/socket.h - Internet protocol sockets interface
* sys/stat.h - File information definitions (Redefined)
* sys/statfs.h - Filesystem statistics definitions
* sys/statvfs.h - Filesystem statistics definitions
* sys/uio.h - Definitions for vector I/O operations

### Additional functions:

The src folder contains C sources for some additional functions not relevant to the standard Ultibo run time

These modules don't need to be added to your project Makefile, precompiled versions are already included in the Ultibo run time 

To use these functions simply include the appropriate header in your source and the linker will find the precompiled object files when compiling

* console/consoleprintf.c - Implementation of console_printf() for ultibo/console.h
* console/consolewindowprintf.c - Implementation of console_window_printf() for ultibo/console.h
* platform/loggingoutputf.c - Implementation of logging_outputf() for ultibo/platform.h
* logging/loggingdeviceoutputf.c - Implementation of logging_device_outputf() for ultibo/logging.h
* platform/serialprintf.c - Implementation of serial_printf() for ultibo/platform.h
* serial/serialdeviceprintf.c - Implementation of serial_device_printf() for ultibo/serial.h

### Third party libraries:

The libs folder contains header files for interfaces to the following third party libraries

These are included in the Ultibo RTL as precompiled static libraries for each platform and can be included in your project by adding them to the LIBS = line of your Makefile

* fftw3f - FFTW Fast Fourier Transforms
* freetype2 - FreeType Font Rendering
* libpng16 - PNG (Portable Network Graphics) Image Format
* lua - LUA Language Interpreter
* lvgl - Light and Versatile Graphics Library
* sqlite3 - SQLite Database Engine
* vc4 - VideoCore IV Graphics Processor Interfaces
* zlib - ZLIB Data Compression

### Example projects:

Located under the samples folder are a number of simple projects that show how to use the API

* Hello World
* Blinker
* Screen Output
* Keyboard Input
* Time Date
* File Handling
* Log Output
* Multi Threading
* Multi CPU
* Serial Connection
* GPIO Handling
* Mouse Cursor
* Bouncing Boxes
* PWM Control
* Sense Hat
* PWM Sound
* Joystick Gamepad

### Advanced examples:

* Dedicated CPU
* LVGL Demo