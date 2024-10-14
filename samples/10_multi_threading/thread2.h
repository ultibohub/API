#ifndef _THREAD2_H
#define _THREAD2_H

#ifdef __cplusplus
extern "C" {
#endif

/* This is a POSIX pThread, it needs a thread function to run which
 * is defined here, the implementation of the function can be found
 * in the thread2.c source file
 */ 
void * thread2_execute(void * args);

#endif // _THREAD2_H