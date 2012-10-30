/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CEventManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer		*g_pServer;

void CEventManager::Call ( CString strName, CSquirrelArguments *pArguments )
{
	for ( std::list<CEventHandler *>::iterator iter = m_EventHandler.begin(); iter != m_EventHandler.end(); iter ++ )
	{
		if ( (*iter)->m_strName == strName )
		{
			g_pServer->GetResourceManager()->Call((*iter)->m_pVM, (*iter), pArguments);
		}
	}	
}