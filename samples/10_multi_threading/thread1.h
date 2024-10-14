#ifndef _THREAD1_H
#define _THREAD1_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"

/* This is a standard Ultibo API thread, it needs a thread function to run
 * which is defined here, the implementation of the function can be found
 * in the thread1.c source file
 */ 
ssize_t STDCALL thread1_execute(void * parameter);

#endif // _THREAD1_H