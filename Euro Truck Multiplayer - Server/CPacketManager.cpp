/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPacketManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CPacketManager::CPacketManager(RakNet::RPC4 * pRPC4)
{
	// Zbieranie pointera plugin'a RPC4
	m_pRPC4 = pRPC4;

	m_pPlayerRPCS = new CPlayerRPCS(m_pRPC4);
}

CPacketManager::~CPacketManager( )
{
	Uninstall(); 
}

void CPacketManager::Install()
{
	m_pPlayerRPCS->Install();
}

void CPacketManager::Uninstall()
{
	m_pPlayerRPCS->Uninstall();
	SAFE_DELETE(m_pPlayerRPCS);
}