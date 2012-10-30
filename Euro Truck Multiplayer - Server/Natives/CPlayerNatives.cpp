/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPlayerNatives.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "../StdInc.h"

extern CServer			*g_pServer;

void CPlayerNatives::Register ( CResourceScript *pResourceScript )
{
	pResourceScript->RegisterFunction ("getPlayerName", GetName, 1, "d");
	pResourceScript->RegisterFunction ("getPlayerPing", GetPing, 1, "d");
	pResourceScript->RegisterFunction ("setChatBoxPosition", SetChatBoxPos, 3, "dff");
	pResourceScript->RegisterFunction ("getChatBoxPosition", GetChatBoxPos, 1, "d");

	pResourceScript->RegisterFunction ("sendPlayerMessage", SendMessage, 3, "dds");
	pResourceScript->RegisterFunction ("sendMessageToAll", SendMessageToAll, 2, "ds");

	pResourceScript->RegisterFunction ("isPlayerConnected", IsConnected, 1, "d");
}

//getPlayerName(playerid)
SQInteger CPlayerNatives::GetName ( SQVM *pVM )
{
	int iPlayerId = -1;
	sq_getinteger(pVM, 2, &iPlayerId);
	
	CPlayer *pPlayer = g_pServer->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);
	if(pPlayer)
	{
		sq_pushstring(pVM, pPlayer->GetName().Get(), -1);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

//getPlayerPing(playerid)
SQInteger CPlayerNatives::GetPing(SQVM *pVM)
{
	int iPlayerId = 0;
	sq_getinteger(pVM, 2, &iPlayerId);

	CPlayer *pPlayer = g_pServer->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);
	if(pPlayer)
	{
		sq_pushinteger(pVM, pPlayer->GetPing());
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

//isPlayerConnected(playerid)
SQInteger CPlayerNatives::IsConnected(SQVM *pVM)
{
	int iPlayerId;
	sq_getinteger(pVM, 2, &iPlayerId);

	if(g_pServer->GetNetworkManager()->GetPlayerManager()->GetSlotState(iPlayerId))
	{
		sq_pushbool(pVM, true);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

//sendPlayerMessage(playerid, color, message)
SQInteger CPlayerNatives::SendMessage ( SQVM *pVM )
{
	const char * szMessage;
	int iColor;
	int iPlayerId;
	sq_getinteger(pVM, 2, &iPlayerId);
	sq_getinteger(pVM, 3, &iColor);
	sq_getstring(pVM, 4, &szMessage);

	if(g_pServer->GetNetworkManager()->GetPlayerManager()->GetSlotState(iPlayerId))
	{
		RakNet::BitStream bsChat;
		bsChat.Write((DWORD)iColor);
		bsChat.Write(strlen(szMessage));
		bsChat.Write(szMessage, strlen(szMessage));

		g_pServer->GetNetworkManager()->Call("Script_Chat", &bsChat, iPlayerId, HIGH_PRIORITY, RELIABLE, 0, false);
		sq_pushbool(pVM, true);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

//sendMessageToAll(color, message)
SQInteger CPlayerNatives::SendMessageToAll (SQVM *pVM)
{
	const char * szMessage;
	int iColor;

	sq_getinteger(pVM, 2, &iColor);
	sq_getstring(pVM, 3, &szMessage);

	bool bState = false;
	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		if(g_pServer->GetNetworkManager()->GetPlayerManager()->GetSlotState(i))
		{
			RakNet::BitStream bsChat;
			bsChat.Write((DWORD)iColor);
			bsChat.Write(strlen(szMessage));
			bsChat.Write(szMessage, strlen(szMessage));

			g_pServer->GetNetworkManager()->Call("Script_Chat", &bsChat, i, HIGH_PRIORITY, RELIABLE, 0, false);
			bState = true;
		}
	}
	
	if(!bState)
	{
		sq_pushbool(pVM, false);
	} else {
		sq_pushbool(pVM, true);
	}
	return 1;
}

//setChatBoxPosition(playerid, x, y)
SQInteger CPlayerNatives::SetChatBoxPos(SQVM *pVM)
{
	int iPlayerId;
	float fX;
	float fY;

	sq_getinteger(pVM, 2, &iPlayerId);
	sq_getfloat(pVM, 3, &fX);
	sq_getfloat(pVM, 4, &fY);

	CPlayer * pPlayer = g_pServer->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);

	if(pPlayer)
	{
		pPlayer->SetChatBoxPosition(fX, fY);

		sq_pushbool(pVM, true);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}

//getChatBoxPosition(playerid)
SQInteger CPlayerNatives::GetChatBoxPos(SQVM *pVM)
{
	int iPlayerId;
	float fX;
	float fY;

	sq_getinteger(pVM, 2, &iPlayerId);
	
	CPlayer * pPlayer = g_pServer->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);

	if(pPlayer)
	{
		pPlayer->GetChatBoxPosition(&fX, &fY);

		//local pos = getChatBoxPosition(playerid)
		// pos[0] = x
		// pos[1] = y
		sq_newarray(pVM, 0);
		sq_pushfloat(pVM, fX);
		sq_arrayappend(pVM, -2);
		sq_pushfloat(pVM, fY);
		sq_arrayappend(pVM, -2);
		sq_push(pVM, -1);
		return 1;
	}

	sq_pushbool(pVM, false);
	return 1;
}