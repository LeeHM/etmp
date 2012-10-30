/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Shared/Network
 * Licence    : GNU GPL v3
 * File       : CRPCManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include <list>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakNetTypes.h>

#include "RPCIdentifiers.h"

typedef void(* RPCHandler)(RakNet::BitStream *bitStream, RakNet::Packet *pPacket);

struct RPCFunction
{
	RPCIdentifier rpcId;
	RPCHandler rpcHandler;
};

class CRPCManager
{
private:
	std::list<RPCFunction *>	m_RPCFunctions;
	RakNet::RakPeerInterface    *m_pRakPeer;

	RakNet::SystemAddress		m_DefaultSystemAddress;
public:
	CRPCManager(RakNet::RakPeerInterface *pRakPeer);
	~CRPCManager();

	void Register ( RPCIdentifier rpcId, RPCHandler rpcHandler );
	void Remove ( RPCIdentifier rpcId );
	RPCFunction * GetFunctionFromId ( RPCIdentifier rpcId );

	inline void SetSystemAddress ( RakNet::SystemAddress systemAddress ) { m_DefaultSystemAddress = systemAddress; }
	inline void SetSystemAddress ( int iPlayerId ) { m_DefaultSystemAddress = m_pRakPeer->GetSystemAddressFromIndex(iPlayerId); }
	inline RakNet::SystemAddress GetSystemAddress () { return m_DefaultSystemAddress; }

	unsigned int Call ( RPCIdentifier rpcId, RakNet::BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = RELIABLE, char orderingChannel = 0, bool broadcast = true );

	bool HandlePacket( RakNet::Packet *pPacket );
};