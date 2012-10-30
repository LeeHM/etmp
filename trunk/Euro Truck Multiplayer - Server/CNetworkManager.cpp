/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CNetworkManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CNetworkManager::CNetworkManager()
{
	// Inizjalizacja rakpeer'a.
	m_pRakPeer = RakNet::RakPeerInterface::GetInstance();

	// Inicjalizacja pluginu RPC4
	m_pRPC4 = RakNet::RPC4::GetInstance();
}

CNetworkManager::~CNetworkManager()
{
	SAFE_DELETE(m_pQuery);
}

void CNetworkManager::Startup(unsigned int uiPort, int iMaxPlayers, CString strBindHost)
{
	// Tworzenie socket descriptora.
	RakNet::SocketDescriptor socketDescriptor(uiPort, strBindHost.Get());

	// Startowanie raknet'a.
	m_pRakPeer->Startup(iMaxPlayers, &socketDescriptor, 1); 
	m_pRakPeer->SetMaximumIncomingConnections(iMaxPlayers);
	// Dodawanie pluginu RPC4 do RakNet::RakPeer
	m_pRakPeer->AttachPlugin(m_pRPC4);

	// Inicjalizacja menad¿era RPC
	//m_pRPCManager = new CRPCManager(m_pRakPeer);

	// Inizjalizacja pakietów
	m_pPacketManager = new CPacketManager(m_pRPC4);

	// Instalacja pakietów
	m_pPacketManager->Install();

	// Inicjalizacja menad¿era graczy.
	m_pPlayerManager = new CPlayerManager ();

	SetStarted(true);

	// Inicjalizacja Query Interface.
	m_pQuery = new CQuery(uiPort, strBindHost);
}

void CNetworkManager::Process()
{
	if(IsStarted())
	{
		m_pPlayerManager->Process();

		if(m_pQuery)
			m_pQuery->Process();

		RakNet::Packet * pPacket = NULL;

		while(pPacket = m_pRakPeer->Receive())
		{
			switch(pPacket->data[0])
			{
			case ID_NEW_INCOMING_CONNECTION:
				char szString[256];
				pPacket->systemAddress.ToString(true, szString, ':');
				CLog::Printf("Nowe nadchodzace polaczenie z adresu ip %s.", szString);
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				m_pPlayerManager->Delete((int)pPacket->systemAddress.systemIndex);
				break;
			case ID_CONNECTION_LOST:
				m_pPlayerManager->Delete((int)pPacket->systemAddress.systemIndex);
				break;
			}
			m_pRakPeer->DeallocatePacket(pPacket);
		}
	}
}

/*void CNetworkManager::RPC( RPCIdentifier rpcId, RakNet::BitStream *bitStream, int iPlayerId, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadcast )
{
	m_pRPCManager->SetSystemAddress(iPlayerId);
	m_pRPCManager->Call(rpcId, bitStream, priority, reliability, orderingChannel, broadcast);
}*/

bool CNetworkManager::Call( const char* uniqueID, RakNet::BitStream * bitStream, int iPlayerId, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadcast )
{
	if(IsStarted())
	{
		m_pRPC4->Call(uniqueID, bitStream, priority, reliability, orderingChannel, 
			(iPlayerId == -1 ? RakNet::UNASSIGNED_SYSTEM_ADDRESS : GetPlayerAddress(iPlayerId)), broadcast);
		return true;
	}
	return false;
}