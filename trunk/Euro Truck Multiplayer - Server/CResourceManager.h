/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CResourceManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include "CEventManager.h"

class CResourceManager
{
private:
	std::list<CResource *>			m_Resources;
	int								m_iLoaded;
	int								m_iHaveError;
	CString							m_szDirectory;
	CEventManager				   *m_pEventManager;
public:
	CResourceManager  ( const char *m_szDirectory );
	~CResourceManager ();

	void ParseConfig ( );

	bool RegisterEvent ( CString strName, SQObjectPtr pHandler, SQVM *pVM );
	void AddEvent ( CString strName, bool bTriggerable );

	void Call ( SQVM *pVM, SQObjectPtr pFunction, CSquirrelArguments *pArguments );
	void Call ( SQVM *pVM, CEventHandler *pEventHandler, CSquirrelArguments *pArguments );

	bool Load   ( const char *szName );
	void Unload ( const char *szName );
	void Restart ( const char *szName );

	CEventManager *GetEventManager()	{ return m_pEventManager; }
};