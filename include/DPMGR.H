//***********************************************************************/
//    Author                    : tywind
//    Original Date             : oct,11 2014
//    Module Name               : dpmgr.h
//    Module Funciton           : 
//                                This module countains the pre-definition of Input and
//                                Display manager.
//    Last modified Author      : tywind
//    Last modified Date        : oct,11 2014
//***********************************************************************/

#include "..\INCLUDE\CharDisPlay.H"


#ifndef __DPMGR_H__
#define __DPMGR_H__

#ifdef __cplusplus
extern "C" {
#endif

//display device id define
#define  DISPLAY_BIOSVGA			0x1001

#define  DISPLAY_SYSTEM_NUM         8	//displyObj max 	


//BEGIN_DEFINE_OBJECT(__DRIVER_OBJECT)
typedef struct tag__DISPLAY_OBJECT
{
    INHERIT_FROM_COMMON_OBJECT

    DWORD                dwExtInfo;          //display inside info
	DWORD                (*GetDisplayID)   ();
	BOOL                 (*GetDisplayRange)(WORD* pLines,WORD* pColums);

	BOOL                 (*PrintString)    (LPCSTR pString,BOOL Cl);  
	BOOL                 (*PrintChar)      (CHAR ch);

	INT                  (*GetCursorPos)   (WORD* pCursorX,WORD* pCursorY);
	INT                  (*SetCursorPos)  (WORD nCursorX,WORD nCursorY); 

	INT                  (*ChangeLine)     ();
	
	BOOL                 (*GetString)      (WORD nCursorX,WORD nCursorY,LPSTR pString,INT nBufLen);

	BOOL                 (*DelString)      (WORD nCursorX,WORD nCursorY,INT nDelLen);
    BOOL                 (*DelChar)        (INT nDelMode);	
	BOOL                 (*Clear)    ();

}__DISPALY_OBJECT;


typedef BOOL (*__DISPLAYDRIVER_ENTRY)(__DISPALY_OBJECT*);

//BEGIN_DEFINE_OBJECT(__IO_MANAGER)
typedef struct tag__DISPLAY_MANAGER
{
	__DISPALY_OBJECT*     szDisplayArray[DISPLAY_SYSTEM_NUM];
	
	BOOL                 (*LoadDisplay)    (__DISPLAYDRIVER_ENTRY DrvEntry);
	BOOL                 (*RegisterDisplay)(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* lpDisplayObj);

	__COMMON_OBJECT*     (*OpenDisplay)    (__COMMON_OBJECT*   lpThis,INT nDevID );
	VOID                 (*CloseDisplay)   (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj);

	BOOL                 (*GetDisplayRange)(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD* pLines,WORD* pColums);
	
	BOOL                 (*PrintString)    (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,LPCSTR pString,BOOL Cl);  
	BOOL                 (*PrintChar)      (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,CHAR ch);
	
	BOOL                 (*GetCursorPos)   (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD* pCursorX,WORD* pCursorY);
	BOOL                 (*SetCursorPos)   (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD nCursorX,WORD nCursorY); 

	BOOL                 (*ChangeLine)     (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj);

	BOOL                 (*GetString)      (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD nCursorX,WORD nCursorY,LPSTR pString,INT nBufLen);

	BOOL                 (*DelString)      (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD nCursorX,WORD nCursorY,INT nDelLen);
    BOOL                 (*DelChar)        (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,INT nDelMode);
	BOOL                 (*Clear)          (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj);
		
}__DISPLAY_MANAGER;
//END_DEFINE_OBJECT(__IO_MANAGER)    //End of __IO_MANAGER.

//
//The declaration of IOManager object.
//
extern __DISPLAY_MANAGER DisplayManager;

#ifdef __cplusplus
}
#endif

#endif    //dpmgr.h
