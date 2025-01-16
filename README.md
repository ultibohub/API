## Ultibo API

Ultibo core API for C and C++

### Supported interfaces:

The includes directory contains header files for interfaces to the following Ultibo APIs

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
* sys/dirent.h - Directory entry definition and access
* sys/socket.h - Internet protocol sockets interface
* sys/statfs.h - Filesystem statistics definitions

### Example projects:

Located under the samples directory are a number of simple projects that show how to use the API

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
