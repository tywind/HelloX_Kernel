//***********************************************************************/
//    Author                    : Garry
//    Original Date             : May,28 2004
//    Module Name               : string.h
//    Module Funciton           : 
//                                This module and string.cpp countains the
//                                string operation method.
//    Last modified Author      :
//    Last modified Date        :
//    Last modified Content     :
//                                1.
//                                2.
//    Lines number              :
//***********************************************************************/

#ifndef __STRING__
#define __STRING__

#define MAX_STRING_LEN 512       //Max string length.

BOOL StrCmp(LPSTR,LPSTR);      //String compare functions.
//#define strcmp StrCmp

WORD StrLen(LPSTR);            //Get the string's length.
//#define strlen StrLen

BOOL Hex2Str(DWORD,LPSTR);     //Convert the first parameter(hex format)
                               //to string.
BOOL Str2Hex(LPSTR,DWORD*);    //Convert the string to hex number.

BOOL Str2Int(LPSTR,DWORD*);    //Convert the string to int.
BOOL Int2Str(DWORD,LPSTR);     //Convert the 32 bit int to string.

VOID PrintLine(LPSTR);         //Print the string at a new line.

VOID StrCpy(LPSTR,LPSTR);      //Copy one string to the second string.
//#define strcpy StrCpy

VOID ConvertToUper(LPSTR);     //Convert the string's characters from low to uper.

INT FormString(LPSTR,LPSTR,LPVOID*);

//Memory manipulating functions.
void* memcpy(void* dst,const void* src,size_t count);
void* memset(void* dst,int val,size_t count);
void* memzero(void* dst,size_t count); 
int memcmp(const void* p1,const void* p2,int count);

//Standard C Lib string operations.
char* strcat(char* dst,const char* src);
char* strcpy(char* dst,const char* src);
char* strchr(const char* string,int ch);
int strcmp(const char* src,const char* dst);
int strlen(const char* s);

//Secured string manipulation functions.
char* strncpy(char *dest,char *src,unsigned int n);

//����ո����־
#define TRIM_LEFT    0x1
#define TRIM_RIGHT   0x2

//����ո��
void strtrim(char * dst,int flag);

long atol(const char* nptr);
int atoi(const char* nptr);

void ToCapital(LPSTR lpszString);

#endif //string.h
