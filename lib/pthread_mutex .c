
#include <StdAfx.h>
#ifndef __KTMGR_H__
#include "ktmgr.h"
#endif
#include "pthread.h"


int ptw32_mutex_check_need_init (pthread_mutex_t * mutex)
{
	return S_OK;
}

LONG ptw32_InterlockedExchange (LPLONG location,LONG value)
{
	LONG result = 0;

#ifdef __I386__
	_asm {
		PUSH         ecx
		MOV          ecx,dword ptr [location]
		MOV          eax,dword ptr [value]
		XCHG         dword ptr [ecx],eax
		MOV          dword ptr [result], eax
		POP          ecx
	}
#endif
	return result;
}

PTW32_LONG  ptw32_InterlockedCompareExchange (PTW32_LPLONG location,	PTW32_LONG value,	PTW32_LONG comparand)
{
	PTW32_LONG result;
#ifdef __I386__
	_asm {
		PUSH         ecx
		PUSH         edx
		MOV          ecx,dword ptr [location]
		MOV          edx,dword ptr [value]
		MOV          eax,dword ptr [comparand]
		LOCK CMPXCHG dword ptr [ecx],edx
		MOV          dword ptr [result], eax
		POP          edx
		POP          ecx
	}
#endif
	return result;
}

int  pthread_mutex_init (pthread_mutex_t* mutex,const pthread_mutexattr_t * attr)
{
	__EVENT*    pEvent    = NULL;

	pEvent = (__EVENT*)ObjectManager.CreateObject(&ObjectManager,
		NULL,
		OBJECT_TYPE_EVENT);
	if(NULL == pEvent)
	{
		return EINVAL;
	}

	if(!pEvent->Initialize((__COMMON_OBJECT*)pEvent))  //Can not initialize.
	{
		ObjectManager.DestroyObject(&ObjectManager,(__COMMON_OBJECT*)pEvent);
		return EINVAL;
	}

	*mutex  = KMemAlloc(sizeof(struct pthread_mutex_t_),KMEM_SIZE_TYPE_ANY);

	(*mutex)->lock_idx         = 0;
	(*mutex)->recursive_count  = 0;
	(*mutex)->kind             = PTHREAD_MUTEX_DEFAULT;
	(*mutex)->ownerThread.p    = NULL;
	(*mutex)->event            = pEvent;

	return S_OK;
}

int  pthread_mutex_destroy (pthread_mutex_t* mutex)
{
	__EVENT*    pEvent    = NULL;//(__EVENT*)(*mutex)->event;

	if(mutex == NULL || *mutex == NULL)
	{
		return -1;
	}

	pEvent = (__EVENT*)(*mutex)->event;
	ObjectManager.DestroyObject(&ObjectManager,	(__COMMON_OBJECT*)pEvent);

	return S_OK;
}

int  pthread_mutex_lock (pthread_mutex_t * mutex)
{  
	pthread_mutex_t mx;
	int result      = S_OK;


	if (*mutex == NULL)
	{
		return EINVAL;
	}


	mx = *mutex;

	if (mx->kind == PTHREAD_MUTEX_NORMAL)
	{
		if ((LONG) ptw32_InterlockedExchange(  (LPLONG) &mx->lock_idx,(LONG)1) != 0)
		{
			while ((LONG) ptw32_InterlockedExchange((LPLONG) &mx->lock_idx,(LONG) -1) != 0)
			{
				__EVENT* lpEvent = (__EVENT*)mx->event;

				if (OBJECT_WAIT_RESOURCE != lpEvent->WaitForThisObjectEx((__COMMON_OBJECT*)lpEvent,INFINITE))
				{
					result = EINVAL;
					break;
				}
			}
		}
	}
	else
	{
		pthread_t self = pthread_self();

		if ((PTW32_LONG) ptw32_InterlockedCompareExchange((PTW32_LPLONG) &mx->lock_idx,
			(PTW32_LONG) 1,
			(PTW32_LONG) 0) == 0)
		{
			mx->recursive_count = 1;
			mx->ownerThread = self;
		}
		else
		{
			if (pthread_equal (mx->ownerThread, self))
			{
				if (mx->kind == PTHREAD_MUTEX_RECURSIVE)
				{
					mx->recursive_count++;
				}
				else
				{
					result = EDEADLK;
				}
			}
			else
			{
				while ((LONG) ptw32_InterlockedExchange((LPLONG) &mx->lock_idx,(LONG) -1) != 0)
				{
					__EVENT* lpEvent = (__EVENT*)mx->event;

					if (OBJECT_WAIT_RESOURCE != lpEvent->WaitForThisObjectEx((__COMMON_OBJECT*)lpEvent,INFINITE))
					{
						result = EINVAL;
						break;
					}
				}

				if (0 == result)
				{
					mx->recursive_count = 1;
					mx->ownerThread = self;
				}
			}
		}
	}

	return (result);
}


int  pthread_mutex_unlock (pthread_mutex_t * mutex)
{	
	pthread_mutex_t mx;
	int result      = S_OK;

	mx = *mutex;

	/*
	* If the thread calling us holds the mutex then there is no
	* race condition. If another thread holds the
	* lock then we shouldn't be in here.
	*/
	if (mx < PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
	{
		if (mx->kind == PTHREAD_MUTEX_NORMAL)
		{
			LONG idx;

			idx = (LONG) ptw32_InterlockedExchange ((LPLONG) &mx->lock_idx,(LONG) 0);
			if (idx != 0)
			{
				if (idx < 0)
				{
					__EVENT* lpEvent = (__EVENT*)mx->event;

					lpEvent->SetEvent((__COMMON_OBJECT*)lpEvent);
				}
			}
			else
			{
				/*
				* Was not locked (so can't be owned by us).
				*/
				result = EPERM;
			}
		}
		else
		{
			if (pthread_equal (mx->ownerThread, pthread_self ()))
			{
				if (mx->kind != PTHREAD_MUTEX_RECURSIVE || 0 == --mx->recursive_count)
				{
					mx->ownerThread.p = NULL;

					if ((LONG) ptw32_InterlockedExchange ((LPLONG) &mx->lock_idx,(LONG) 0) < 0)
					{
						__EVENT* lpEvent = (__EVENT*)mx->event;

						/*
						* Someone may be waiting on that mutex.
						*/
						lpEvent->SetEvent((__COMMON_OBJECT*)lpEvent);
					}
				}
			}
			else
			{
				result = EPERM;
			}
		}
	}
	else
	{
		result = EINVAL;
	}

	return (result);
}

int  pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)
{
	return S_OK;
}

int  pthread_mutex_trylock (pthread_mutex_t * mutex)
{
  int result = 0;
  pthread_mutex_t mx;

  /*
   * We do a quick check to see if we need to do more work
   * to initialise a static mutex. We check
   * again inside the guarded section of ptw32_mutex_check_need_init()
   * to avoid race conditions.
   */
  if (*mutex >= PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
    {
      if ((result = ptw32_mutex_check_need_init (mutex)) != 0)
	{
	  return (result);
	}
    }

  mx = *mutex;

  if (0 == (LONG) ptw32_InterlockedCompareExchange((PTW32_LPLONG) &mx->lock_idx,(PTW32_LONG) 1,(PTW32_LONG) 0))
    {
    if (mx->kind != PTHREAD_MUTEX_NORMAL)
	{
	  mx->recursive_count = 1;
	  mx->ownerThread     = pthread_self ();
	}
    }
  else
    {
    if (mx->kind == PTHREAD_MUTEX_RECURSIVE &&   pthread_equal (mx->ownerThread, pthread_self ()))
		{
		mx->recursive_count++;
		}
      else
		{
	  result = EBUSY;
		}
    }

  return (result);
}


/*
* Mutex Attribute Functions
*/
int  pthread_mutexattr_init (pthread_mutexattr_t * attr)
{
	return S_OK;
}

int  pthread_mutexattr_destroy (pthread_mutexattr_t * attr)
{
	return S_OK;
}

int  pthread_mutexattr_getpshared (const pthread_mutexattr_t *attr,int *pshared)
{
	return S_OK;
}

int  pthread_mutexattr_setpshared (pthread_mutexattr_t * attr,int pshared)
{
	return S_OK;
}

int  pthread_mutexattr_settype (pthread_mutexattr_t * attr, int kind)
{
	return S_OK;
}

int  pthread_mutexattr_gettype (pthread_mutexattr_t * attr, int *kind)
{
	return S_OK;
}
