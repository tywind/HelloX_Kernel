//***********************************************************************/
//    Author                    : tywind
//    Original Date             : oct,13 2014
//    Module Name               : chardisplay.h
//    Module Funciton           : char display api
//                                
//    Last modified Author      : tywind
//    Last modified Date        : oct,11 2014
//***********************************************************************/

#ifndef __CHARDISPLAY_H__
#define __CHARDISPLAY_H__

#ifndef __TYPES_H__
#include "TYPES.H"
#endif

#ifndef __CONFIG_H__
#include "..\config\config.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

//显示模式
#define  DISPLAY_MODE_DEFAULT   0    //默认显示模式 80*25

//删除模式
#define  DISPLAY_DELCHAR_PREV		 0		//删除光标前面一个字符
#define  DISPLAY_DELCHAR_CURR        1      //删除光标当前位置一个字符

//初始化显示设备
BOOL CD_InitDisplay(INT nDisplayMode);

//设置显示模式
BOOL CD_SetDisplayMode(INT nMode);

//得到行和列
BOOL CD_GetDisPlayRang(WORD* pLines,WORD* pColums);

//换行
BOOL CD_ChangeLine();

//得到当前光标位置
INT  CD_GetCursorPos(WORD* pCursorX,WORD* pCursorY);

//设置当前光标位置
INT  CD_SetCursorPos(WORD nCursorX,WORD nCursorY);

//打印字符串,cl表示是否换行
BOOL CD_PrintString(LPSTR pStr,BOOL cl);

//打印一个字符
BOOL CD_PrintChar(CHAR ch);

//从指定位置得到字符串
BOOL  CD_GetString(WORD nCursorX,WORD nCursorY,LPSTR pString,INT nBufLen);

//删除字符串
BOOL  CD_DelString(WORD nCursorX,WORD nCursorY,INT nDelLen);	

//删除字符
BOOL  CD_DelChar(INT nDelMode);	

//清屏
BOOL  CD_Clear();

#ifdef __cplusplus
}
#endif

#endif    //cd.h
