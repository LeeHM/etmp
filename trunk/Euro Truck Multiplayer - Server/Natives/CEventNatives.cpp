/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CEventNatives.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "../StdInc.h"

extern CServer			*g_pServer;

void CEventNatives::Register ( CResourceScript *pResourceScript )
{
	pResourceScript->RegisterFunction ( "addEventHandler", AddEventHandler );
	pResourceScript->RegisterFunction ( "addEvent", AddEvent, 2, "sb" );
	pResourceScript->RegisterFunction ( "triggerEvent", TriggerEvent );
}

SQInteger CEventNatives::AddEventHandler ( SQVM *pVM )
{
	const char * szEventName;
	SQObjectPtr pEventHandler;
	sq_getstring ( pVM, 2, &szEventName );
	pEventHandler = stack_get(pVM, 3);

	bool bReturn = g_pServer->GetResourceManager()->RegisterEvent( CString(szEventName), pEventHandler, pVM );

	sq_pushbool(pVM, bReturn);
	return 1;
}

SQInteger CEventNatives::AddEvent ( SQVM *pVM )
{
	const char * szEventName;
	SQBool bTriggerable = SQTrue;
	sq_getstring ( pVM, 2, &szEventName );
	sq_getbool ( pVM, 3, &bTriggerable );

	g_pServer->GetResourceManager()->AddEvent ( CString ( szEventName ), (bTriggerable == SQTrue ? true : false) );

	sq_pushbool ( pVM, true );
	return 1;
}

SQInteger CEventNatives::TriggerEvent ( SQVM *pVM )
{
	const char * szEventName;
	sq_getstring ( pVM, 2, &szEventName );

	CSquirrelArguments pArguments;
	pArguments.fromVM ( pVM, 3 );

	g_pServer->GetResourceManager()->GetEventManager()->Call(szEventName, &pArguments);

	sq_pushbool ( pVM, true );
	return 1;
}