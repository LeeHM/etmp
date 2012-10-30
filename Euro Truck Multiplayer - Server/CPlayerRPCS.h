/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
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
	//CRPCManager *m_pRPCManager;

	// Funkcje
	static void RPC_Chat(RakNet::BitStream * pBitStream, RakNet::Packet *pPacket);
	static void RPC_Command(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket);
	static void RPC_Connect(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket);

	static void RPC_Sync(RakNet::BitStream *pBitStream, RakNet::Packet *pPacket);
public:
	CPlayerRPCS ( RakNet::RPC4 *pRPC4 );
	~CPlayerRPCS ( );

	void Install();
	void Uninstall();	
};