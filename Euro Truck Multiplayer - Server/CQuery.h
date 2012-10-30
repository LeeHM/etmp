/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CQuery.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once

class CQuery
{
private:
	unsigned int				m_uiPort;
	CString						m_strBindHost;
	int							m_iSocket;
	bool						m_bState;
public:
								CQuery(unsigned int uiPort, CString szBindHost);
								~CQuery();

	void						Process();

	void						SetState(bool bState) { m_bState = bState; }
	bool						GetState() { return m_bState; }

	//Utils
	const char					*inet_ntop(int af, const void * src, char * dst, int cnt);
};