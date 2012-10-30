/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CNetworkManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once

class CNetworkManager
{
private:
	RakNet::RakPeerInterface  * m_pRakPeer;
	RakNet::RPC4			  * m_pRPC4;
	RakNet::SystemAddress       m_ServerAddress;

	CPacketManager			  * m_pPacketManager;
	CPlayerManager			  * m_pPlayerManager;
	CServerManager			  * m_pServerManager;

	bool						m_bConnected;

	unsigned int				m_uiPort;
	CString						m_strHost;
public:
	CNetworkManager();
	~CNetworkManager();

	void							Connect(const char*szHost, unsigned int uiPort, const char*szNickName);
	bool							Disconnect();
	void							Process();

	RakNet::RakPeerInterface *		GetRakPeer() { return m_pRakPeer; }

	bool							Call( const char* uniqueID, RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadcast );
	inline bool						IsConnected ( ) { return m_bConnected; }
	inline void						SetConnected ( bool bConnected ) { m_bConnected = bConnected; }
	inline void						SetServerAddress ( RakNet::SystemAddress serverAddress ) { m_ServerAddress = serverAddress; m_pServerManager->SetSystemAddress(serverAddress); }
	void							ConnectionSuccess(RakNet::Packet *pPacket);

	CPlayerManager					*GetPlayerManager() { return m_pPlayerManager; }
	CServerManager					*GetServerManager() { return m_pServerManager; }
};