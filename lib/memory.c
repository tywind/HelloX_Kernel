
#include "StdAfx.h"
#include "string.h"

//------------------------------------------------------------------------
// Memory manipulating functions,memcpy,memset,...
//------------------------------------------------------------------------

void* memcpy (void * dst,const void * src,size_t count	)
{
	void * ret = dst;

	//copy from lower addresses to higher addresses
	while (count--) 
	{
		*(char *)dst = *(char *)src;
		dst = (char *)dst + 1;
		src = (char *)src + 1;
	}

	return(ret);
}

void* memset (void *dst,int val,size_t count)
{
	void *start = dst;

	while (count--) 
	{
		*(char *)dst = (char)val;
		dst = (char *)dst + 1;
	}

	return(start);
}

void* memzero(	void* dst,	size_t count)
{
	return memset(dst,0,count);
}

void* memchr (const void * buf,int chr,size_t cnt)
{
	while ( cnt && (*(unsigned char *)buf != (unsigned char)chr) ) 
	{
		buf = (unsigned char *)buf + 1;
		cnt--;
	}

	return(cnt ? (void *)buf : NULL);
}

int memcmp(const void *buffer1,const void *buffer2,int count)
{
	if (!count) return(0);

	while ( --count && *(char *)buffer1 == *(char *)buffer2)
	{
		buffer1 = (char *)buffer1 + 1;
		buffer2 = (char *)buffer2 + 1;
	}

	return( *((unsigned char *)buffer1) - *((unsigned char *)buffer2) );
}
