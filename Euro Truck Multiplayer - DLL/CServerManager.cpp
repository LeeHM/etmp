/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CServerManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#include "StdInc.h"

CServerManager::CServerManager()
{
	m_strHostName = CString("Mój serwer ET-MP!");
	m_uiMaxPlayers = MAX_PLAYERS;
}

CServerManager::~CServerManager()
{
	
}

void CServerManager::SetHostName(CString strHostName)
{
	m_strHostName = strHostName;
}

CString CServerManager::GetHostName()
{
	return m_strHostName;
}

void CServerManager::SetMaxPlayers(unsigned int uiMaxPlayers)
{
	m_uiMaxPlayers = uiMaxPlayers;
}

unsigned int CServerManager::GetMaxPlayers()
{
	return m_uiMaxPlayers;
}

void CServerManager::SetSystemAddress(RakNet::SystemAddress serverAddress)
{
	m_systemAddress = serverAddress;
}

RakNet::SystemAddress CServerManager::GetSystemAddress()
{
	return m_systemAddress;
}