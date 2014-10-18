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

//��ʾ�豸���
static HANDLE      s_hDisplayObj = NULL;

//��ʼ����ʾ�豸
BOOL CD_InitDisplay(INT nDisplayMode)
{
	if(s_hDisplayObj)
	{
		return TRUE;
	}

	//Ŀǰֻ֧��Ĭ����ʾ
	if(nDisplayMode != DISPLAY_MODE_DEFAULT)
	{
		return FALSE;
	}

	s_hDisplayObj =  DisplayManager.OpenDisplay((__COMMON_OBJECT*)&DisplayManager,DISPLAY_BIOSVGA);
	
	return TRUE;
}

//������ʾģʽ
BOOL CD_SetDisplayMode(INT nMode)
{
	return TRUE;
}

//�õ��к���
BOOL CD_GetDisPlayRang(WORD* pLines,WORD* pColums)
{
	return DisplayManager.GetDisplayRange((__COMMON_OBJECT*)&DisplayManager,
		                                 (__COMMON_OBJECT*)s_hDisplayObj,
										 pLines,
										 pColums);
	
}

//�õ���ǰ���λ��
INT  CD_GetCursorPos(WORD* pCursorX,WORD* pCursorY)
{
	return DisplayManager.GetCursorPos((__COMMON_OBJECT*)&DisplayManager,
		                                 (__COMMON_OBJECT*)s_hDisplayObj,
		                                 pCursorX,
		                                 pCursorY);
}

//����
BOOL CD_ChangeLine()
{
	return DisplayManager.ChangeLine((__COMMON_OBJECT*)&DisplayManager,
		                            (__COMMON_OBJECT*)s_hDisplayObj);
}
//���õ�ǰ���λ��
INT  CD_SetCursorPos(WORD nCursorX,WORD nCursorY)
{
	return DisplayManager.SetCursorPos((__COMMON_OBJECT*)&DisplayManager,
									  (__COMMON_OBJECT*)s_hDisplayObj,
		                              nCursorX,
		                              nCursorY);
}

//��ӡ�ַ���,cl��ʾ�Ƿ���
BOOL CD_PrintString(LPSTR pStr,BOOL cl)
{
	return DisplayManager.PrintString((__COMMON_OBJECT*)&DisplayManager,
		                       (__COMMON_OBJECT*)s_hDisplayObj,
							   pStr,
							   cl);
}

//��ӡһ���ַ�
BOOL CD_PrintChar(CHAR ch)
{
	return  DisplayManager.PrintChar((__COMMON_OBJECT*)&DisplayManager,
		                     (__COMMON_OBJECT*)s_hDisplayObj,
		                     ch);
}

//��ָ��λ�õõ��ַ���
BOOL  CD_GetString(WORD nCursorX,WORD nCursorY,LPSTR pString,INT nBufLen)
{
	return  DisplayManager.GetString((__COMMON_OBJECT*)&DisplayManager,
		                             (__COMMON_OBJECT*)s_hDisplayObj,
		                             nCursorX,
		                             nCursorY,
									 pString,
									 nBufLen);
}

//ɾ���ַ���
BOOL  CD_DelString(WORD nCursorX,WORD nCursorY,INT nDelLen)
{
	return  DisplayManager.DelString((__COMMON_OBJECT*)&DisplayManager,
		                             (__COMMON_OBJECT*)s_hDisplayObj,
		                             nCursorX,
									 nCursorY,
									 nDelLen
									 );
}

//ɾ���ַ�
BOOL  CD_DelChar(INT nDelMode)
{
	return  DisplayManager.DelChar((__COMMON_OBJECT*)&DisplayManager,
		                           (__COMMON_OBJECT*)s_hDisplayObj,
		                           nDelMode);
}

//����
BOOL  CD_Clear()
{
	return DisplayManager.Clear((__COMMON_OBJECT*)&DisplayManager,
		                         (__COMMON_OBJECT*)s_hDisplayObj);
}