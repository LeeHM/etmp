/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPacketManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CPacketManager::CPacketManager(RakNet::RPC4 *pRPC4/*CRPCManager *pRPCManager*/)
{
	// Zbieranie pointera plugin'a RPC4
	m_pRPC4 = pRPC4;
	//m_pRPCManager = pRPCManager;

	m_pPlayerRPCS = new CPlayerRPCS(m_pRPC4/*m_pRPCManager*/);
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