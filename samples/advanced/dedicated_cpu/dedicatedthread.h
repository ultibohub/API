#ifndef _DEDICATEDTHREAD_H
#define _DEDICATEDTHREAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"

/* The start function which does all the setup work for our dedicated thread */
void start_dedicated_thread(WINDOW_HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif // _DEDICATEDTHREAD_H