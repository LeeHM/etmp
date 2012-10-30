/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPlayerRPCS.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer *g_pServer;

CPlayerRPCS::CPlayerRPCS ( RakNet::RPC4 *pRPC4 )
{
	//m_pRPCManager = pRPCManager;
	m_pRPC4 = pRPC4;
}

CPlayerRPCS::~CPlayerRPCS( )
{
	Uninstall();
}

void CPlayerRPCS::Install()
{
	m_pRPC4->RegisterFunction("Player_Chat", RPC_Chat);
	m_pRPC4->RegisterFunction("Player_Command", RPC_Command);
	m_pRPC4->RegisterFunction("Player_Connect", RPC_Connect);

	//Sync
	m_pRPC4->RegisterFunction("Player_Sync", RPC_Sync);
}

void CPlayerRPCS::Uninstall()
{
	m_pRPC4->UnregisterFunction("Player_Chat");
	m_pRPC4->UnregisterFunction("Player_Command");
	m_pRPC4->UnregisterFunction("Player_Connect");

	//Sync
	m_pRPC4->UnregisterFunction("Player_Sync");
}

// RPC4 Functions
void CPlayerRPCS::RPC_Chat(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
    char szMessage[256];
	int iPlayerId = CNetworkTools::GetIdFromPacket(pPacket);
	CPlayer *pPlayer = g_pServer->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);

	if(pPlayer)
	{
		pBitStream->Read(szMessage, sizeof(szMessage));
		CLog::Printf("[Chat] %s: %s", pPlayer->GetName().Get(), szMessage);

		RakNet::BitStream bsChat;
		bsChat.WriteCompressed(iPlayerId);
		bsChat.Write(szMessage, 256);

		CSquirrelArguments pArgs;
		pArgs.push(iPlayerId);
		pArgs.push(szMessage);
		g_pServer->GetResourceManager()->GetEventManager()->Call("onPlayerChat", &pArgs);

		for(int i = 0; i < MAX_PLAYERS; i++)
		{
			if(g_pServer->GetNetworkManager()->GetPlayerManager()->GetSlotState(i))
			{
				g_pServer->GetNetworkManager()->Call("Player_Chat", &bsChat, i, HIGH_PRIORITY, RELIABLE, 0, false);
			}
		}
	}
}

void CPlayerRPCS::RPC_Command(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	char szCommand[256];
	int iPlayerId = CNetworkTools::GetIdFromPacket(pPacket);
	pBitStream->Read(szCommand, sizeof(szCommand));

	CSquirrelArguments pArgs;
	pArgs.push(iPlayerId);
	pArgs.push(szCommand);
	g_pServer->GetResourceManager()->GetEventManager()->Call("onPlayerCommand", &pArgs);
}

void CPlayerRPCS::RPC_Connect(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{	
	char szName[MAX_PLAYER_NAME];
	int iPlayerId = CNetworkTools::GetIdFromPacket(pPacket);
	pBitStream->Read(szName, sizeof(szName));
	g_pServer->GetNetworkManager()->GetPlayerManager()->New(iPlayerId, szName);
}

//Sync
void CPlayerRPCS::RPC_Sync(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket)
{
	int iPlayerId = CNetworkTools::GetIdFromPacket(pPacket);

	CPlayer *pPlayer = g_pServer->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);

	if(pPlayer)
	{
		SyncData syncData;
		pBitStream->Read((char *)&syncData, sizeof(SyncData));
		pPlayer->StoreSync(&syncData);
	}
}