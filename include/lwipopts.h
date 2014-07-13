//***********************************************************************/
//    Author                    : Garry
//    Original Date             : Jun 26,2014
//    Module Name               : lwipopts.h
//    Module Funciton           : 
//                                Options definition file for lwIP,it is required
//                                by lwIP stack.
//    Last modified Author      :
//    Last modified Date        : Jun 26,2014
//    Last modified Content     :
//                                1. 
//    Lines number              :
//***********************************************************************/

#ifndef __STDAFX_H__
#include "StdAfx.h"
#endif

#ifndef __STDLIB_H__
#include "stdlib.h"      //For memory allocation.
#endif

#ifndef __LWIPOPTS_H__

//Use binary semaphore for mutex.
#define LWIP_COMPAT_MUTEX    1

//Use light weight protection.
#define SYS_LIGHTWEIGHT_PROT 1

//Use standard C memory manipulation routines,such as malloc/free.
#define MEM_LIBC_MALLOC      1

//Enable loop back interface.
#define LWIP_HAVE_LOOPIF     1

//Enable receive timeout mechanism.
#define LWIP_SO_RCVTIMEO     1

//*-----------------------------------------------------------------------
//*
//*  Thread options for lwIP's internal threads.
//*
//*-----------------------------------------------------------------------

//TCPIP thread's name.
#define TCPIP_THREAD_NAME                "tcpip_thread"

//TCPIP thread's stack size,use default value.
#define TCPIP_THREAD_STACKSIZE           0

//TCPIP thread's priority.
#define TCPIP_THREAD_PRIO                PRIORITY_LEVEL_HIGH

//Mail box's size for TCP/IP thread.Increase this value may improve performance.
#define TCPIP_MBOX_SIZE                  8

//SLIP interface's thread name.
#define SLIPIF_THREAD_NAME               "slipif_loop"

//Stack size of slipif.
#define SLIPIF_THREAD_STACKSIZE          0

//SLIPIF thread's priority.
#define SLIPIF_THREAD_PRIO               PRIORITY_LEVEL_NORMAL

//Thread name of PPP function.
#define PPP_THREAD_NAME                  "ppp_in_thrd"

//Stack size of PPP thread.
#define PPP_THREAD_STACKSIZE             0

//Priority level of PPP thread.
#define PPP_THREAD_PRIO                  PRIORITY_LEVEL_NORMAL

//Default value for other lwIP thread.
#define DEFAULT_THREAD_NAME              "lwIP stack"
#define DEFAULT_THREAD_STACKSIZE         0
#define DEFAULT_THREAD_PRIO              PRIORITY_LEVEL_NORMAL

#endif  //__LWIPOPTS_H__

