## Ultibo API

Ultibo core API for C and C++

Note: This is an early pre-release of the API for testing only, many items are not yet included.

### Supported interfaces:

The includes directory contains header files for interfaces to the following Ultibo APIs

* ultibo/globalconst.h - 
* ultibo/globaltypes.h - 
* ultibo/platform.h - 

In addition to the Ultibo interface headers a small number of headers that expose functionality not normally available in the Newlib C library are also provided

* netdb.h - 
* semaphore.h -
* arpa/inet.h - 
* netinet/in.h - 
* netinet6/in6.h - 
* sys/dirent.h
* sys/socket.h
* sys/statfs.h

### Class libraries:

The library contains C++ classes for several of the interfaces above, more will be added in future


### Example projects:

Located under the samples directory are a number of simple projects that show how to use the API

* Blinktest

