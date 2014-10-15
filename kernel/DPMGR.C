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

#ifndef __STDAFX_H__
#include "..\INCLUDE\StdAfx.h"
#endif

#include "..\lib\string.h"


//RegisterDisplay,this routine add one display controller into system.
static BOOL RegisterDisplay(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* lpDisplayObj)
{
	__DISPLAY_MANAGER*  pManager = (__DISPLAY_MANAGER*)lpThis;
	DWORD               dwFlags  = 0;
	INT                 i        = 0;

	if((NULL == lpDisplayObj) || (NULL == lpThis)) //Invalid parameters.
	{
		return FALSE;
	}
	__ENTER_CRITICAL_SECTION(NULL,dwFlags);

	for(i = 0;i < DISPLAY_SYSTEM_NUM;i ++)
	{
		if(NULL == pManager->szDisplayArray[i]) //Find a empty slot.
		{
			break;
		}
	}

	if(DISPLAY_SYSTEM_NUM == i)  //Can not find a empty slot.
	{
		__LEAVE_CRITICAL_SECTION(NULL,dwFlags);

		return FALSE;
	}

	//Insert the file system object into this slot.
	pManager->szDisplayArray[i] = (__DISPALY_OBJECT*)lpDisplayObj;
	__LEAVE_CRITICAL_SECTION(NULL,dwFlags);

	return TRUE;
}

static __COMMON_OBJECT*     OpenDisplay(__COMMON_OBJECT*   lpThis,INT nDevID )
{
	__DISPLAY_MANAGER*  pManager    = (__DISPLAY_MANAGER*)lpThis;
	__COMMON_OBJECT*   lpDisplayObj = NULL;
	DWORD               dwFlags     = 0;
	DWORD              i            = 0;

	if(NULL == pManager)
	{
		return NULL;
	}
	__ENTER_CRITICAL_SECTION(NULL,dwFlags);

	for(i=0;i<DISPLAY_SYSTEM_NUM;i++)
	{
		if(pManager->szDisplayArray[i] && pManager->szDisplayArray[i]->GetDisplayID() == nDevID)
		{
			lpDisplayObj = (__COMMON_OBJECT*)pManager->szDisplayArray[i];
			break;
		}
	}
	__LEAVE_CRITICAL_SECTION(NULL,dwFlags);

	return lpDisplayObj;
}

static __DISPALY_OBJECT* GetDisplayObj(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj)
{

	if(NULL == lpThis)
	{
		return NULL	;
	}

	return  (__DISPALY_OBJECT*)pDpObj;
}

static  VOID CloseDisplay  (__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj)
{
	return ;
}

static BOOL  GetDisplayRange(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD* pLines,WORD* pColums)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}
		

	pDisplayObj->GetDisplayRange(pLines,pColums);

	return TRUE;
}

static BOOL   PrintString(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,LPCSTR pString,BOOL Cl)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}


	pDisplayObj->PrintString(pString,Cl);

	return TRUE;
}

static BOOL PrintChar(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,CHAR ch)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}


	pDisplayObj->PrintChar(ch);
	
	return TRUE;
}

static BOOL  GetCursorPos(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD* pCursorX,WORD* pCursorY)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}


	return pDisplayObj->GetCursorPos(pCursorX,pCursorY);		
}

static BOOL  SetCursorPos(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD nCursorX,WORD nCursorY)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}
	
	return pDisplayObj->SetCursorPos(nCursorX,nCursorY);		
}

static BOOL  _ChangeLine(__COMMON_OBJECT*  lpThis,__COMMON_OBJECT* pDpObj)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}
	
	return pDisplayObj->ChangeLine();	
}

static BOOL GetString(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD nCursorX,WORD nCursorY,LPSTR pString,INT nBufLen)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}


	return pDisplayObj->GetString(nCursorX,nCursorY,pString,nBufLen);		
}

static BOOL DelString(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,WORD nCursorX,WORD nCursorY,INT nDelLen)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}

	return pDisplayObj->DelString(nCursorX,nCursorY,nDelLen);	
}
static BOOL DelChar(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,INT nDelMode)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}
	
	return pDisplayObj->DelChar(nDelMode);		
}

/*static BOOL DelChar(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj,INT nDelMode)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}


	return pDisplayObj->DelChar(nDelMode);			
}*/

static BOOL  Clear(__COMMON_OBJECT*   lpThis,__COMMON_OBJECT* pDpObj)
{
	__DISPALY_OBJECT*  pDisplayObj = GetDisplayObj(lpThis,pDpObj);

	if(NULL == pDisplayObj)
	{
		return FALSE;
	}


	return pDisplayObj->Clear();			
}


//
//The implementation of LoadDriver.
//This routine is used by OS loader to load device drivers.
//
static BOOL LoadDisplay(__DISPLAYDRIVER_ENTRY DrvEntry)
{
	__DISPALY_OBJECT*   lpDrvObject  = NULL;

	if(NULL == DrvEntry)  //Invalid parameter.
	{
		return FALSE;
	}

	lpDrvObject = (__DRIVER_OBJECT*)ObjectManager.CreateObject(
		&ObjectManager,
		NULL,
		OBJECT_TYPE_DISPLAY);
	if(NULL == lpDrvObject)  //Can not create driver object.
	{
		return FALSE;
	}

	if(!lpDrvObject->Initialize((__COMMON_OBJECT*)lpDrvObject)) //Initialize failed.
	{
		return FALSE;
	}
	
	//Call the driver entry.
	if(DrvEntry(lpDrvObject))
	{
		return TRUE;
	}
	//Failed to call DrvEntry routine,so release the driver object.
	ObjectManager.DestroyObject(
		&ObjectManager,
		(__COMMON_OBJECT*)lpDrvObject);
	return FALSE;
}
__DISPLAY_MANAGER DisplayManager = 
{
	{0},      //DisplayArray.
		
	LoadDisplay,
	RegisterDisplay,

	OpenDisplay,
	CloseDisplay,

	GetDisplayRange,
	PrintString,
	PrintChar,
	GetCursorPos,
	
	SetCursorPos,	
	_ChangeLine,
	GetString,

	DelString,
	DelChar,
	Clear
};
