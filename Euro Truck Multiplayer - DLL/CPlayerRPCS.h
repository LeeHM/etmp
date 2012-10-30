/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayerRPCS.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CPlayerRPCS
{
private:
	RakNet::RPC4 * m_pRPC4;
	//CRPCManager			*m_pRPCManager;

	static void RPC_Chat(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket);
	static void RPC_Add(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket);
	static void RPC_Remove(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket);
	static void RPC_Sync(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket);
	static void RPC_Info(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket);

	static void RPC_Script_Chat(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket);
	static void RPC_Script_SetChatBoxPositon(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket);
	static void RPC_Script_SetTime(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket);
public:
	CPlayerRPCS ( RakNet::RPC4 *pRPC4/*CRPCManager *pRPCManager*/ );
	~CPlayerRPCS ( );

	void Install();
	void Uninstall();	
};