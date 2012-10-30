/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : Input.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;
WNDPROC OldProcess;

bool WndHook()
{
	HWND GameWindow = g_pClient->GetGameWindow();
 
	//SetWindowText(GameWindow, "Euro Truck Multiplayer");
	
	if(GameWindow) 
	{
		OldProcess = (WNDPROC)GetWindowLong(GameWindow ,GWL_WNDPROC);
		SetWindowLong(GameWindow, GWL_WNDPROC, (LONG)WindowProcess);
		return true;
	}
	return false;
}

LRESULT APIENTRY WindowProcess( HWND hwnd,UINT uMsg, WPARAM wParam,LPARAM lParam ) 
{ 	
	if(g_pClient->GetGraphic())
	{
		if(g_pClient->GetGraphic()->WindowProcess(hwnd, uMsg, wParam, lParam))
		{
			return 1;
		}
	}
	switch(uMsg) 
	{
		case WM_KEYUP:
			HandleKeyPress((DWORD)wParam);
			break;
		case WM_CHAR:
			HandleCharacterInput((DWORD)wParam);
			break;
	}
	return CallWindowProc(OldProcess,hwnd,uMsg,wParam,lParam);
}

BOOL HandleKeyPress(DWORD vKey) 
{
	switch(vKey)
	{
		case VK_RETURN:
		{
			g_pClient->GetChatbox()->ProcessInput();
			return TRUE;			
		}break;
	}
	return FALSE;
}

BOOL HandleCharacterInput(DWORD dwChar)
{
	if(g_pClient->GetChatbox()->IsTypping() == TRUE)
	{
		if(dwChar == 8) 
		{
			g_pClient->GetChatbox()->BackSpace();
			return TRUE;
		}
		else if(dwChar == VK_ESCAPE)
		{
			g_pClient->GetChatbox()->Disable();
			return TRUE;
		} 

		g_pClient->GetChatbox()->AddChar((char)dwChar);
		return TRUE;	
	}
	else if(g_pClient->GetChatbox()->IsTypping() == FALSE)
	{
		switch(dwChar) 
		{
			case '`':
			case 't':
			case 'T':
				g_pClient->GetChatbox()->Enable();
				return TRUE;
		}
	}
	return FALSE;
}