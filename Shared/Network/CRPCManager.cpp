/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Shared/Network
 * Licence    : GNU GPL v3
 * File       : CRPCManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "CRPCManager.h"

CRPCManager::CRPCManager(RakNet::RakPeerInterface *pRakPeer)
{
	m_pRakPeer = pRakPeer;

	m_DefaultSystemAddress = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
}

CRPCManager::~CRPCManager()
{
	for(std::list<RPCFunction *>::iterator iter = m_RPCFunctions.begin(); iter != m_RPCFunctions.end(); iter ++ )
	{
		m_RPCFunctions.remove((*iter));
		delete (*iter);
	}
}

void CRPCManager::Register ( RPCIdentifier rpcId, RPCHandler rpcHandler )
{
	RPCFunction *pFunction = GetFunctionFromId (rpcId);

	if(pFunction)
		return;

	pFunction = new RPCFunction;
	pFunction->rpcId = rpcId;
	pFunction->rpcHandler = rpcHandler;

	m_RPCFunctions.push_back(pFunction);
}

void CRPCManager::Remove ( RPCIdentifier rpcId )
{
	RPCFunction *pFunction = GetFunctionFromId (rpcId);

	if(!pFunction)
		return;

	m_RPCFunctions.remove(pFunction);
	delete pFunction;
}

RPCFunction * CRPCManager::GetFunctionFromId ( RPCIdentifier rpcId )
{
	for(std::list<RPCFunction *>::iterator iter = m_RPCFunctions.begin(); iter != m_RPCFunctions.end(); iter ++ )
	{
		if((*iter)->rpcId == rpcId)
		{
			return (*iter);
		}
	}

	return NULL;
}

unsigned int CRPCManager::Call ( RPCIdentifier rpcId, RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadcast )
{
	RakNet::BitStream bsRPC;
	bsRPC.Write((RakNet::MessageID)(ID_USER_PACKET_ENUM+1));
	bsRPC.Write(rpcId);

	if(bitStream)
		bsRPC.Write(bitStream);

	return m_pRakPeer->Send(&bsRPC, priority, reliability, orderingChannel, m_DefaultSystemAddress, broadcast );
}

bool CRPCManager::HandlePacket(RakNet::Packet *pPacket)
{
	// Sprawdzanie czy napewno ten pakiet jest ID_RPC = ID_USER_PACKET_ENUM+1
	if(pPacket->data[0] == (ID_USER_PACKET_ENUM+1))
	{
		RakNet::BitStream bitStream(pPacket->data, pPacket->length, false);

		RPCIdentifier rpcId;

		bitStream.IgnoreBytes(sizeof(RakNet::MessageID));

		if(bitStream.Read(rpcId))
		{
			RPCFunction * pFunction = GetFunctionFromId(rpcId);

			RakNet::BitStream bsData;
			bitStream.Read(bsData);

			if(pFunction)
			{
				pFunction->rpcHandler(&bsData, pPacket);
				return true;
			}
		}
	}
	return false;
}