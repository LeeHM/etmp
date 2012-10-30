/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPacketManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

#include "CPlayerRPCS.h"

class CPacketManager
{
private:
	CPlayerRPCS * m_pPlayerRPCS;
	//CRPCManager * m_pRPCManager;
	RakNet::RPC4 * m_pRPC4;
public:
	CPacketManager(RakNet::RPC4 *pRPC4/*CRPCManager *pRPCManager*/);
	~CPacketManager();

	void Install();
	void Uninstall();
};