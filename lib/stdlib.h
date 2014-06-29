//***********************************************************************/
//    Author                    : Garry
//    Original Date             : Jun 26,2014
//    Module Name               : stdlib.h
//    Module Funciton           : 
//                                Stdand C library simulation code.It only implements a subset
//                                of C library,even much more simple.
//    Last modified Author      :
//    Last modified Date        : Jun 26,2014
//    Last modified Content     :
//                                1. 
//    Lines number              :
//***********************************************************************/

#ifndef __STDLIB_H__
#define __STDLIB_H__

//Standard C malloc/free/calloc routine.
void* _cdecl malloc(size_t size);
void  _cdecl free(void* p);
void* _cdecl calloc(size_t n,size_t s);

#endif  //__STDLIB_H__