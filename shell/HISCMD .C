//***********************************************************************/
//    Author                    : tywind
//    Original Date             : oct,15 2014
//    Module Name               : HITCMD.c
//    Module Funciton           : 
//                                This module countains shell history routes
//    Last modified Author      :
//    Last modified Date        :
//    Last modified Content     :
//                                1.
//                                2.
//    Lines number              :
//***********************************************************************/

#include "..\include\StdAfx.h"
#include "..\INCLUDE\KAPI.H"
#include "shell.h"

typedef struct tag__HISTORY_CMD_INFO
{
	HIS_CMD_OBJ*  pHisCmdArry;
	INT           nHisCount;
	INT           nSaveHisIndex;   
	INT           nExecHisIndex;   

}HISTORY_CMD_INFO;

HISOBJ His_CreateHisObj(INT nHisCount)
{
	HISTORY_CMD_INFO*  pHisInfo = NULL;

	if(nHisCount <= 0)
	{
		return NULL;
	}
	pHisInfo = (HISTORY_CMD_INFO*)KMemAlloc(sizeof(HISTORY_CMD_INFO),KMEM_SIZE_TYPE_ANY);
	if(NULL == pHisInfo)
	{
		return NULL;
	}

	pHisInfo->nHisCount     = nHisCount;
	pHisInfo->pHisCmdArry   = (HIS_CMD_OBJ*)KMemAlloc(sizeof(HIS_CMD_OBJ)*nHisCount,KMEM_SIZE_TYPE_ANY);
	pHisInfo->nSaveHisIndex = 0;
	pHisInfo->nExecHisIndex = 0;

	return (HISOBJ)pHisInfo;
}

VOID His_DeleteHisObj(HISOBJ hHisObj)
{
	HISTORY_CMD_INFO*  pHisInfo = (HISTORY_CMD_INFO*)hHisObj;

	if(pHisInfo)
	{
		KMemFree(pHisInfo->pHisCmdArry,KMEM_SIZE_TYPE_ANY,0);
		KMemFree(pHisInfo,KMEM_SIZE_TYPE_ANY,0);
	}
}

//save curcmd to history list
BOOL His_SaveCmd(HISOBJ hHisObj,LPCSTR pCmdStr)
{	
	HISTORY_CMD_INFO*  pHisInfo = (HISTORY_CMD_INFO*)hHisObj;
	INT           nEndHisIndex  = 0;//HISCMD_MAX_COUNT-1;

	if(NULL == pHisInfo)
	{
		return FALSE;
	}
	nEndHisIndex = pHisInfo->nHisCount-1;
	

	//判断是否重复
	if(strcmp(pCmdStr,pHisInfo->pHisCmdArry[pHisInfo->nSaveHisIndex].CmdStr) == 0)
	{
		pHisInfo->nExecHisIndex = pHisInfo->nSaveHisIndex+1;	
		return FALSE;
	}

	if(pHisInfo->nSaveHisIndex >= nEndHisIndex)
	{
		INT nMoveLen = sizeof(HIS_CMD_OBJ)*nEndHisIndex;

		//删除最后一个指令
		memcpy(&pHisInfo->pHisCmdArry[0],&pHisInfo->pHisCmdArry[1],nMoveLen);
	}

	StrCpy(pCmdStr,pHisInfo->pHisCmdArry[pHisInfo->nSaveHisIndex].CmdStr);
	if(pHisInfo->nSaveHisIndex < nEndHisIndex)
	{
		pHisInfo->nSaveHisIndex ++;
	}

	pHisInfo->nExecHisIndex = pHisInfo->nSaveHisIndex;	

	return TRUE;
}

//load history cmd to current line
BOOL His_LoadHisCmd(HISOBJ hHisObj,BOOL bUp,LPSTR pCmdBuf,INT nBufLen)
{
	HISTORY_CMD_INFO*  pHisInfo = (HISTORY_CMD_INFO*)hHisObj;	
	INT                nInc     = 0;

	if(NULL == pHisInfo)
	{
		return FALSE;
	}

	if(bUp == TRUE)	
	{
		if(pHisInfo->nExecHisIndex <= 0)
		{
			return FALSE;
		}
		nInc = -1;
	}
	else
	{		
		if(pHisInfo->nExecHisIndex >= pHisInfo->nSaveHisIndex-1)
		{
			return FALSE;
		}
		nInc = 1;
	}

	pHisInfo->nExecHisIndex += nInc;

	StrCpy(pHisInfo->pHisCmdArry[pHisInfo->nExecHisIndex].CmdStr,pCmdBuf);

	return TRUE;
	/*CD_GetCursorPos(&CursorX,&CursorY);
	CD_SetCursorPos(SHELL_INPUT_START_X,CursorY);
	CD_DelString(SHELL_INPUT_START_X,CursorY,CMD_MAX_LEN);
	CD_PrintString(s_szHisCmdArry[s_nExecHisIndex].CmdStr,FALSE);*/
}

