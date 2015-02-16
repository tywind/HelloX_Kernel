//***********************************************************************/
//    Author                    : tywind
//    Original Date             : oct,27 2014
//    Module Name               : SHELL_HELP.c
//    Module Funciton           : 
//                                This module countains shell input  routes
//    Last modified Author      :
//    Last modified Date        :
//    Last modified Content     :
//                                1.
//                                2.
//    Lines number              :
//***********************************************************************/

#include "../include/StdAfx.h"
#include "../INCLUDE/KAPI.H"
#include "../include/CharDisplay.h"
#include "shell.h"

#define  ERROR_STR   "  You entered incorrect command name."
#define  ERROR_STR2  "  Failed to process the command."

typedef struct tag__SHELL_MSG_INFO
{
	HISOBJ                    hHisInfoObj;
	LPSTR                     pPrompt;
	__SHELL_CMD_HANDLER       pCmdRoute;
	__SHELL_NAMEQUERY_HANDLER pNameQuery;

}SHELL_MSG_INFO;


static VOID PrintPrompt(SHELL_MSG_INFO*  pShellInfo)
{
	WORD CursorX = 0,CursorY = 0;

	CD_GetCursorPos(&CursorX,&CursorY);
	if(CursorX != 0)
	{
		CD_ChangeLine();
	}

	CD_PrintString(pShellInfo->pPrompt,FALSE);
}

//The following function form the command parameter object link from the command
//line string.
__CMD_PARA_OBJ* FormParameterObj(LPCSTR pszCmd)
{
	__CMD_PARA_OBJ*     pObjBuffer    = NULL;  
	LPSTR               pCmdPos       = (LPSTR)pszCmd;
	BYTE                byParamPos    = 0;
	BYTE                byParamNum    = 0;

	if(NULL == pCmdPos)    //Parameter check.
	{
		return NULL;
	}

	pObjBuffer = (__CMD_PARA_OBJ*)KMemAlloc(sizeof(__CMD_PARA_OBJ),KMEM_SIZE_TYPE_ANY);
	if(NULL == pObjBuffer)
	{
		return NULL;
	}
	memzero(pObjBuffer,sizeof(__CMD_PARA_OBJ));

	while(*pCmdPos)
	{
		if(' ' == *pCmdPos)
		{
			pCmdPos ++;
			continue; 
		}    

		// add papam
		while((' ' != *pCmdPos) && (*pCmdPos) && (byParamPos <= CMD_PARAMETER_LEN))
		{
			if(pObjBuffer->Parameter[byParamNum] == NULL)
			{
				pObjBuffer->Parameter[byParamNum] = (CHAR*)KMemAlloc(CMD_PARAMETER_LEN+1,KMEM_SIZE_TYPE_ANY);
				memzero(pObjBuffer->Parameter[byParamNum],CMD_PARAMETER_LEN+1);
			}

			pObjBuffer->Parameter[byParamNum][byParamPos] = *pCmdPos;
			pCmdPos   ++;
			byParamPos ++;
		}

		byParamNum ++;                                     
		byParamPos = 0;

		if(byParamNum >= CMD_PARAMETER_COUNT)
		{
			break;
		}

		//Skip the no space characters if the parameter's length
		while(' ' != *pCmdPos && *pCmdPos)
		{					
			pCmdPos ++;          
		}	
	}

	pObjBuffer->byParameterNum  = byParamNum;

	return pObjBuffer;
}

//
//Releases the parameter object created by FormParameterObj routine.
//
VOID ReleaseParameterObj(__CMD_PARA_OBJ* lpParamObj)
{	
	BYTE     Index      = 0;

	if(NULL == lpParamObj)  //Parameter check.
	{
		return;
	}

	for(Index = 0;Index < lpParamObj->byParameterNum;Index ++)
	{
		KMemFree((LPVOID)lpParamObj->Parameter[Index],KMEM_SIZE_TYPE_ANY,0);
	}

	KMemFree((LPVOID)lpParamObj,KMEM_SIZE_TYPE_ANY,0);
	
	return;
}

//load history cmd to current cmd line
static 	void LoadHisCmd(SHELL_MSG_INFO*  pShellInfo,BOOL bUp)
{
	CHAR   szHisCmd[CMD_MAX_LEN] = {0};
	WORD   CursorX               = 0;
	WORD   CursorY               = 0;


	if(His_LoadHisCmd(pShellInfo->hHisInfoObj,bUp,szHisCmd,sizeof(szHisCmd)) == FALSE)
	{		
		return; 
	}

	CD_GetCursorPos(&CursorX,&CursorY);
	CD_SetCursorPos(strlen(pShellInfo->pPrompt),CursorY);
	CD_DelString(strlen(pShellInfo->pPrompt),CursorY,CMD_MAX_LEN);
	CD_PrintString(szHisCmd,FALSE);

}

//key  msg 
static INT OnKeyControl(SHELL_MSG_INFO*  pShellInfo,BYTE   bt )
{

	switch(bt)
	{
		case VK_RETURN:
		{
			CHAR   szCmdBuffer[CMD_MAX_LEN] = {0};			
			WORD   CursorX                  = 0;
			WORD   CursorY                  = 0;

			//得到命令输入串
			CD_GetCursorPos(&CursorX,&CursorY);		
			CD_GetString(strlen(pShellInfo->pPrompt),CursorY,szCmdBuffer,sizeof(szCmdBuffer));
			strtrim(szCmdBuffer,TRIM_LEFT|TRIM_RIGHT);
			CD_ChangeLine();

			if(strlen(szCmdBuffer) > 0)
			{
				His_SaveCmd(pShellInfo->hHisInfoObj,szCmdBuffer);
								
				switch(pShellInfo->pCmdRoute(szCmdBuffer))
				{
					case SHELL_CMD_PARSER_TERMINAL: //Exit command is entered.
					{
						return FALSE;
					}
					break;
					case SHELL_CMD_PARSER_INVALID:  //Can not parse the command.
					{
						CD_PrintString(ERROR_STR,TRUE);
					}							
					break;
					case SHELL_CMD_PARSER_FAILED:
					{
						CD_PrintString(ERROR_STR2,TRUE);
					}
					break;
				default:
					break;
				}
			}

			PrintPrompt(pShellInfo);
		}
		break;
		case VK_BACKSPACE:
		{
			WORD CursorX = 0;
			WORD CursorY = 0;

			CD_GetCursorPos(&CursorX,&CursorY);
			if(CursorX <= strlen(pShellInfo->pPrompt))
			{
				break;
			}

			CD_DelChar(DISPLAY_DELCHAR_PREV);
		}
		break;
		default:
		{
			CD_PrintChar(bt);
		}
	}

	return TRUE;
}

static BOOL FindSub(const char*  srcstr,const char* substr)
{
	const char*  srcp    = srcstr;
	const char*  subp    = substr;
	BOOL   bFound  = TRUE;

	while(*srcp != 0 && *subp != 0)
	{
		if(*srcp != *subp)
		{
			bFound = FALSE;

			break;
		}

		srcp ++;
		subp ++;
	}

	return bFound;
}

static BOOL OnAutoName(SHELL_MSG_INFO*  pShellInfo)
{
	CHAR   szUserInput[CMD_MAX_LEN] = {0};			
	WORD   CursorX                  = 0;
	WORD   CursorY                  = 0;

	//得到命令输入串
	CD_GetCursorPos(&CursorX,&CursorY);		
	CD_GetString(strlen(pShellInfo->pPrompt),CursorY,szUserInput,sizeof(szUserInput));

	//检查是否有匹配项
	if(strlen(szUserInput) > 0 && pShellInfo->pNameQuery)
	{	
		//清空
		pShellInfo->pNameQuery(NULL,0);

		//逐个询问匹配
		while(TRUE)
		{
			CHAR  szCmdNmae[CMD_MAX_LEN] = {0};
						
			if(pShellInfo->pNameQuery(szCmdNmae,sizeof(szCmdNmae)) == SHELL_QUERY_CANCEL)
			{
				break;
			}
			
			if(FindSub(szCmdNmae,szUserInput))
			{	
				//
				if(strlen(szCmdNmae) <= strlen(szUserInput))
				{
					break;
				}

				CD_SetCursorPos(strlen(pShellInfo->pPrompt),CursorY);
				CD_DelString(strlen(pShellInfo->pPrompt),CursorY,CMD_MAX_LEN);
				CD_PrintString(szCmdNmae,FALSE);

				break;
			}				
		}				
	}

	return TRUE;
}

static BOOL OnVkKeyControl(SHELL_MSG_INFO*  pShellInfo,BYTE bt)
{
	WORD CursorX = 0;
	WORD CursorY = 0;

	CD_GetCursorPos(&CursorX,&CursorY);

	switch(bt)
	{
		case VK_LEFTARROW:
		{
			if(CursorX <= strlen(pShellInfo->pPrompt))
			{
				break;
			}

			CursorX --;
			CD_SetCursorPos(CursorX,CursorY);
		}
		break;
		case VK_RIGHTARROW:
		{
			CHAR szCurChar[2] = {0};

			CD_GetString(CursorX,CursorY,szCurChar,1);
			if(szCurChar[0] > 0)
			{
				CD_SetCursorPos(CursorX+1,CursorY);
			}
			else
			{
				OnAutoName(pShellInfo);
			}
		}
		break;
		case VK_UPARROW:
		{			
			LoadHisCmd(pShellInfo,TRUE);
		}
		break;
		case VK_DOWNARROW:
		{
			LoadHisCmd(pShellInfo,FALSE);
		}
		break;
		case VK_DELETE:
		{
			CD_DelChar(DISPLAY_DELCHAR_CURR);
		}
		break;
		case VK_HOME:
		{			
			CD_SetCursorPos(strlen(pShellInfo->pPrompt),CursorY);
		}
		break;
		case VK_END:
		{
			CHAR szCmdBuf[CMD_MAX_LEN] = {0};

			CursorX = strlen(pShellInfo->pPrompt);
			CD_GetString(CursorX,CursorY,szCmdBuf,sizeof(szCmdBuf));

			CursorX += strlen(szCmdBuf);
			CD_SetCursorPos(CursorX,CursorY);
		}
		break;
		default:
		{
			return FALSE;
		}
	}


	return TRUE;
}

//shell 输入 循环处理 
DWORD Shell_Msg_Loop2(const char* pPrompt,__SHELL_CMD_HANDLER pCmdRoute,__SHELL_NAMEQUERY_HANDLER pNameQuery)
{
	SHELL_MSG_INFO*  pShellInfo = NULL;

	if(NULL == pPrompt || NULL == pCmdRoute)
	{
		return 0;
	}

	pShellInfo = (SHELL_MSG_INFO*)KMemAlloc(sizeof(SHELL_MSG_INFO),KMEM_SIZE_TYPE_ANY);
	if(NULL == pShellInfo)
	{
		return 0;
	}

	pShellInfo->pPrompt     = (char*)pPrompt;
	pShellInfo->pCmdRoute   = pCmdRoute;
	pShellInfo->pNameQuery   = pNameQuery;

	pShellInfo->hHisInfoObj = His_CreateHisObj(HISCMD_MAX_COUNT);

	PrintPrompt(pShellInfo);

	while(TRUE)
	{
		__KERNEL_THREAD_MESSAGE     Msg;

		if(GetMessage(&Msg))
		{
			BYTE bt = (BYTE)(Msg.dwParam);

			switch(Msg.wCommand)
			{
			case MSG_KEY_DOWN:
				{
					if(OnKeyControl(pShellInfo,bt) == FALSE)
					{
						goto __TERMINAL;
					}
				}
				break;
			case MSG_VK_KEY_DOWN:
				{					
					OnVkKeyControl(pShellInfo,bt);
				}
				break;
			case KERNEL_MESSAGE_TIMER:
				{
					PrintLine("Timer message received.");
				}
				break;
			case KERNEL_MESSAGE_TERMINAL: 
				{
				goto __TERMINAL;
				}
				break;
			}
		}
	}

__TERMINAL:

	His_DeleteHisObj(pShellInfo->hHisInfoObj);
	KMemFree(pShellInfo,KMEM_SIZE_TYPE_ANY,0);

	return 0;
}

//shell 输入 循环处理
DWORD Shell_Msg_Loop(const char* pPrompt,__SHELL_CMD_HANDLER pCmdRoute,__SHELL_NAMEQUERY_HANDLER pNameQuery)
{
	return Shell_Msg_Loop2(pPrompt,pCmdRoute,pNameQuery);	
}
