/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CServerManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once

class CServerManager
{
private:
	CString						m_strHostName;
	unsigned int				m_uiMaxPlayers;
	RakNet::SystemAddress		m_systemAddress;
public:
	CServerManager();
	~CServerManager();

	CString						GetHostName();
	void						SetHostName(CString strHostName);

	unsigned int				GetMaxPlayers();
	void						SetMaxPlayers(unsigned int uiMaxPlayers);

	RakNet::SystemAddress		GetSystemAddress();
	void						SetSystemAddress(RakNet::SystemAddress serverAddress);
};