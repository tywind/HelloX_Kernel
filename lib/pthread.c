#include "StdAfx.h"
#include "stdio.h"
#include "pthread.h"

static int  s_nThreadIndex = 1; 

//////////////////////////////////////////////////////////////////////////
int  pthread_create (pthread_t * tid,	const pthread_attr_t * attr,void *(*start) (void *),void *arg)
{		
	__KERNEL_THREAD_OBJECT*    lpKernelThread  = NULL;
	char                       szThreadName[64]    ; 

	if(tid == NULL)
	{
		return -1;
	}
	
	_hx_sprintf(szThreadName,"pthread_%d",s_nThreadIndex++);
	lpKernelThread = KernelThreadManager.CreateKernelThread(
		             (__COMMON_OBJECT*)&KernelThreadManager,
		             0,
		             KERNEL_THREAD_STATUS_READY,
		             PRIORITY_LEVEL_NORMAL,
		             (__KERNEL_THREAD_ROUTINE)start,
		             arg,
		             NULL,
		             szThreadName);

	if(NULL == lpKernelThread)  
	{
		return -1;
	}
	

	tid->x = lpKernelThread->dwThreadID;
	tid->p = lpKernelThread;

	return S_OK;
}

int  pthread_kill(pthread_t thread, int sig)
{
	KernelThreadManager.DestroyKernelThread((__COMMON_OBJECT*)&KernelThreadManager,
		                                   (__COMMON_OBJECT*)thread.p);

	return S_OK;
}

int  pthread_detach (pthread_t tid)
{
	return S_OK;
}

int  pthread_equal (pthread_t t1, pthread_t t2)
{
	return (t1.x == t2.x)?TRUE:FALSE;
}

void  pthread_exit (void *value_ptr)
{
	
   KernelThreadManager.DestroyKernelThread((__COMMON_OBJECT*)&KernelThreadManager,
	                                       (__COMMON_OBJECT*)KernelThreadManager.lpCurrentKernelThread);

   
}

int  pthread_join (pthread_t thread, void **value_ptr)
{
	__KERNEL_THREAD_OBJECT*  lpThread = thread.p;
			
	if(lpThread)
	{
		return lpThread->WaitForThisObject((__COMMON_OBJECT*)lpThread);
	}
	else
	{
		return -1;
	}
		
}

pthread_t  pthread_self (void)
{
	pthread_t  p; 

	p.x  = KernelThreadManager.lpCurrentKernelThread->dwThreadID;
	p.p  = KernelThreadManager.lpCurrentKernelThread;
	
	return p;
}

int  pthread_cancel (pthread_t thread)
{
	KernelThreadManager.DestroyKernelThread((__COMMON_OBJECT*)&KernelThreadManager,
                                            (__COMMON_OBJECT*)thread.p);

	return S_OK;
}

int  pthread_setcancelstate (int state, int *oldstate)
{
	return S_OK;
}

int  pthread_setcanceltype (int type, int *oldtype)
{
	return S_OK;
}

void  pthread_testcancel (void)
{
	return;
}

int  pthread_once (pthread_once_t * once_control,  void (*init_routine) (void))
{
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////
//pthread_attr
int  pthread_attr_init (pthread_attr_t * attr)
{
	return S_OK;
}

int  pthread_attr_destroy (pthread_attr_t * attr)
{
	return S_OK;
}

int  pthread_attr_getdetachstate (const pthread_attr_t * attr,int *detachstate)
{
	return S_OK;
}

int  pthread_attr_getstackaddr (const pthread_attr_t * attr,void **stackaddr)
{
	return S_OK;
}

int  pthread_attr_getstacksize (const pthread_attr_t * attr, size_t * stacksize)
{
	return S_OK;
}

int  pthread_attr_setdetachstate (pthread_attr_t * attr,int detachstate)
{
	return S_OK;
}

int  pthread_attr_setstackaddr (pthread_attr_t * attr, void *stackaddr)
{
	return S_OK;
}

int  pthread_attr_setstacksize (pthread_attr_t * attr, size_t stacksize)
{
	return S_OK;
}

int  pthread_attr_getschedparam (const pthread_attr_t *attr, struct sched_param *param)
{
	return S_OK;
}

int  pthread_attr_setschedparam (pthread_attr_t *attr, const struct sched_param *param)
{
	return S_OK;
}

int  pthread_attr_setschedpolicy (pthread_attr_t *attr, int n)
{
	return S_OK;
}

int  pthread_attr_getschedpolicy (pthread_attr_t *attr, int *p)
{
	return S_OK;
}

int  pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched)
{
	return S_OK;
}

int  pthread_attr_getinheritsched(pthread_attr_t *attr,int * inheritsched)
{
	return S_OK;
}

int  pthread_attr_setscope (pthread_attr_t *attr, int n)
{
	return S_OK;
}

int  pthread_attr_getscope (const pthread_attr_t *attr,int *p)
{
	return S_OK;
}

int  pthread_key_create (pthread_key_t * key,void (*destructor) (void *))
{
	return S_OK;
}

int  pthread_key_delete (pthread_key_t key)
{
	return S_OK;
}

int  pthread_setspecific (pthread_key_t key,	const void *value)
{
	return S_OK;
}

void*  pthread_getspecific (pthread_key_t key)
{
	return NULL;
}


/*
 * Barrier Attribute Functions
 */
int  pthread_barrierattr_init (pthread_barrierattr_t * attr)
{
	return S_OK;
}

int  pthread_barrierattr_destroy (pthread_barrierattr_t * attr)
{
	return S_OK;
}

int  pthread_barrierattr_getpshared (const pthread_barrierattr_t *attr,int *pshared)
{
	return S_OK;
}

int  pthread_barrierattr_setpshared (pthread_barrierattr_t * attr, int pshared)
{
	return S_OK;
}
