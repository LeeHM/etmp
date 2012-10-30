/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayerRPCS.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient *g_pClient;

CPlayerRPCS::CPlayerRPCS ( /*CRPCManager *pRPCManager*/RakNet::RPC4 *pRPC4 )
{
	// Inicjalizacja RPC4
	m_pRPC4 = pRPC4;

	//m_pRPCManager = pRPCManager;
}

CPlayerRPCS::~CPlayerRPCS( )
{
	Uninstall();
}

void CPlayerRPCS::Install()
{
	m_pRPC4->RegisterFunction("Player_Chat", RPC_Chat);
	m_pRPC4->RegisterFunction("Player_Sync", RPC_Sync);
	m_pRPC4->RegisterFunction("Player_Add", RPC_Add);
	m_pRPC4->RegisterFunction("Player_Remove", RPC_Remove);
	
	m_pRPC4->RegisterFunction("Script_Chat", RPC_Script_Chat);	
	m_pRPC4->RegisterFunction("Script_SetChatBoxPositon", RPC_Script_SetChatBoxPositon);
	m_pRPC4->RegisterFunction("Script_SetTime", RPC_Script_SetTime);

	m_pRPC4->RegisterFunction("Server_Info", RPC_Info);
}

void CPlayerRPCS::Uninstall()
{
	m_pRPC4->UnregisterFunction("Player_Chat");
	m_pRPC4->UnregisterFunction("Player_Sync");
	m_pRPC4->UnregisterFunction("Player_Add");
	m_pRPC4->UnregisterFunction("Player_Remove");

	m_pRPC4->UnregisterFunction("Script_Chat");
	m_pRPC4->UnregisterFunction("Script_SetChatBoxPositon");
	m_pRPC4->UnregisterFunction("Script_SetTime");

	m_pRPC4->UnregisterFunction("Server_Info");
}

// RPC4 Functions
void CPlayerRPCS::RPC_Chat(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
    char szMessage[256];
	int iPlayerId;

	pBitStream->ReadCompressed(iPlayerId);
	pBitStream->Read(szMessage, sizeof(szMessage));

	g_pClient->GetChatbox()->AddPlayerMessage(iPlayerId, szMessage);
}

void CPlayerRPCS::RPC_Add(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	int iPlayerId;
	char szNick[MAX_PLAYER_NAME];
	DWORD dwColor = 0xFFFFFFFF;
	pBitStream->Read(iPlayerId);
	pBitStream->Read(szNick, sizeof(szNick));
	pBitStream->Read(dwColor);

	//Dodajemy nowego gracza.
	if(g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetId() != iPlayerId)
	{
		if(!g_pClient->GetNetworkManager()->GetPlayerManager()->New(iPlayerId, szNick, dwColor))
			g_pClient->GetChatbox()->AddDebugMessage("[Error] Nie uda³o siê dodaæ gracza do kontenera danych!");
	}
}

void CPlayerRPCS::RPC_Remove(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	int iPlayerId;
	pBitStream->Read(iPlayerId);
	
	//Sprawdzamy czy istnieje gracz na tym slocie - jeœli tak usuwamy go.
	g_pClient->GetNetworkManager()->GetPlayerManager()->Delete(iPlayerId);
}


//Sync
void CPlayerRPCS::RPC_Sync(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	int iPlayerId;
	unsigned int uiPing;
	pBitStream->ReadCompressed(iPlayerId);
	pBitStream->ReadCompressed(uiPing);

	CPlayer *pPlayer = g_pClient->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);

	if(pPlayer)
	{
		SyncData syncData;
		pBitStream->Read((char*)&syncData, sizeof(SyncData));
		pPlayer->StoreSync(&syncData);
		pPlayer->SetPing(uiPing);
	}
}

void CPlayerRPCS::RPC_Info(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	int iPlayerId;
	int iLength;
	char szHostName[128];
	DWORD dwColor = 0xFFFFFFFF;
	int iMaxPlayers = MAX_PLAYERS;

	pBitStream->Read(iPlayerId);
	pBitStream->Read(dwColor);
	pBitStream->Read(iLength);
	pBitStream->Read(szHostName, iLength);
	pBitStream->Read(iMaxPlayers);
	szHostName[iLength] = '\0';
	
	g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->SetId(iPlayerId);
	g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->SetColor(dwColor);
	g_pClient->GetNetworkManager()->GetServerManager()->SetHostName(CString(szHostName));
	g_pClient->GetNetworkManager()->GetServerManager()->SetMaxPlayers(iMaxPlayers);
}

void CPlayerRPCS::RPC_Script_Chat(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket)
{
	char szMessage[256];
	int iMessage;
	DWORD dwColor;
	pBitStream->Read(dwColor);
	pBitStream->Read(iMessage);
	pBitStream->Read(szMessage, iMessage);
	szMessage[iMessage] = '\0';

	g_pClient->GetChatbox()->AddChatMessage(szMessage, dwColor);
}

void CPlayerRPCS::RPC_Script_SetChatBoxPositon(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	float fX, fY;
	pBitStream->Read(fX);
	pBitStream->Read(fY);

	g_pClient->GetChatbox()->SetPosition(fX, fY);
}

void CPlayerRPCS::RPC_Script_SetTime(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	unsigned short usHour;
	unsigned short usMinute;

	pBitStream->Read(usHour);
	pBitStream->Read(usMinute);

	g_pClient->GetGame()->SetTime(usHour, usMinute);
}