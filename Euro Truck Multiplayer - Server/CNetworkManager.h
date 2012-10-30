/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CNetworkManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once

class CNetworkTools
{
public:
	inline static int GetIdFromPacket(RakNet::Packet *pPacket) { int iPlayerId = (BYTE)pPacket->guid.systemIndex; return iPlayerId; }
};

class CNetworkManager
{
private:
	RakNet::RakPeerInterface		* m_pRakPeer;
	RakNet::RPC4					* m_pRPC4;
	char							m_szBindHost[64];
	unsigned int					m_uiPort;
	int								m_iMaxPlayers;
	bool							m_bStarted;

	CPacketManager					* m_pPacketManager;
	CPlayerManager					* m_pPlayerManager;
	//CRPCManager					* m_pRPCManager;

	CQuery							* m_pQuery;
public:
									CNetworkManager();
									~CNetworkManager();

	void							Startup(unsigned int uiPort, int iMaxPlayers, CString strBindHost = "");
	void							Process();

	inline void						SetStarted ( bool bStarted ) { m_bStarted = bStarted; }
	inline bool						IsStarted ( ) { return m_bStarted; }

	RakNet::RakPeerInterface *		GetRakPeer() { return m_pRakPeer; }
	RakNet::RPC4 *					GetRPC4 () { return m_pRPC4; }
	CPlayerManager					*GetPlayerManager() { return m_pPlayerManager; }
	//CRPCManager				*GetRPC() { return m_pRPCManager; }

	inline RakNet::SystemAddress	GetPlayerAddress ( int iPlayerId ) { return m_pRakPeer->GetSystemAddressFromIndex(iPlayerId); }

	//void RPC( RPCIdentifier rpcId, RakNet::BitStream *bitStream, int iPlayerId, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = RELIABLE, char orderingChannel = 0, bool broadcast = false );
	bool							Call( const char* uniqueID, RakNet::BitStream * bitStream, int iPlayerId, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadcast );
};