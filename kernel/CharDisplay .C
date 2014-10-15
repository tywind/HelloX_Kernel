//***********************************************************************/
//    Author                    : tywind
//    Original Date             : Nov,02 2014
//    Module Name               : CharDisplay
//    Module Funciton           : 
//                                
//                                
//
//    Last modified Author      :
//    Last modified Date        :
//    Last modified Content     :
//                                1.
//                                2.
//    Lines number              :
//***********************************************************************/

#ifndef __STDAFX_H__
#include "..\INCLUDE\STDAFX.H"
#endif

#ifndef __KAPI_H__
#include "..\INCLUDE\KAPI.H"
#endif

#include "..\INCLUDE\CharDisPlay.H"

//显示设备句柄
static HANDLE      s_hDisplayObj = NULL;

//初始化显示设备
BOOL CD_InitDisplay(INT nDisplayMode)
{
	if(s_hDisplayObj)
	{
		return TRUE;
	}

	//目前只支持默认显示
	if(nDisplayMode != DISPLAY_MODE_DEFAULT)
	{
		return FALSE;
	}

	s_hDisplayObj =  DisplayManager.OpenDisplay((__COMMON_OBJECT*)&DisplayManager,DISPLAY_BIOSVGA);
	
	return TRUE;
}

//设置显示模式
BOOL CD_SetDisplayMode(INT nMode)
{
	return TRUE;
}

//得到行和列
BOOL CD_GetDisPlayRang(WORD* pLines,WORD* pColums)
{
	return DisplayManager.GetDisplayRange((__COMMON_OBJECT*)&DisplayManager,
		                                 (__COMMON_OBJECT*)s_hDisplayObj,
										 pLines,
										 pColums);
	
}

//得到当前光标位置
INT  CD_GetCursorPos(WORD* pCursorX,WORD* pCursorY)
{
	return DisplayManager.GetCursorPos((__COMMON_OBJECT*)&DisplayManager,
		                                 (__COMMON_OBJECT*)s_hDisplayObj,
		                                 pCursorX,
		                                 pCursorY);
}

//换行
BOOL CD_ChangeLine()
{
	return DisplayManager.ChangeLine((__COMMON_OBJECT*)&DisplayManager,
		                            (__COMMON_OBJECT*)s_hDisplayObj);
}
//设置当前光标位置
INT  CD_SetCursorPos(WORD nCursorX,WORD nCursorY)
{
	return DisplayManager.SetCursorPos((__COMMON_OBJECT*)&DisplayManager,
									  (__COMMON_OBJECT*)s_hDisplayObj,
		                              nCursorX,
		                              nCursorY);
}

//打印字符串,cl表示是否换行
BOOL CD_PrintString(LPSTR pStr,BOOL cl)
{
	return DisplayManager.PrintString((__COMMON_OBJECT*)&DisplayManager,
		                       (__COMMON_OBJECT*)s_hDisplayObj,
							   pStr,
							   cl);
}

//打印一个字符
BOOL CD_PrintChar(CHAR ch)
{
	return  DisplayManager.PrintChar((__COMMON_OBJECT*)&DisplayManager,
		                     (__COMMON_OBJECT*)s_hDisplayObj,
		                     ch);
}

//从指定位置得到字符串
BOOL  CD_GetString(WORD nCursorX,WORD nCursorY,LPSTR pString,INT nBufLen)
{
	return  DisplayManager.GetString((__COMMON_OBJECT*)&DisplayManager,
		                             (__COMMON_OBJECT*)s_hDisplayObj,
		                             nCursorX,
		                             nCursorY,
									 pString,
									 nBufLen);
}

//删除字符串
BOOL  CD_DelString(WORD nCursorX,WORD nCursorY,INT nDelLen)
{
	return  DisplayManager.DelString((__COMMON_OBJECT*)&DisplayManager,
		                             (__COMMON_OBJECT*)s_hDisplayObj,
		                             nCursorX,
									 nCursorY,
									 nDelLen
									 );
}

//删除字符
BOOL  CD_DelChar(INT nDelMode)
{
	return  DisplayManager.DelChar((__COMMON_OBJECT*)&DisplayManager,
		                           (__COMMON_OBJECT*)s_hDisplayObj,
		                           nDelMode);
}

//清屏
BOOL  CD_Clear()
{
	return DisplayManager.Clear((__COMMON_OBJECT*)&DisplayManager,
		                         (__COMMON_OBJECT*)s_hDisplayObj);
}