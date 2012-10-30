/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CEventNatives.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CEventNatives
{
public:
	static void Register ( CResourceScript *pResourceScript );

	static SQInteger AddEventHandler ( SQVM *pVM );
	static SQInteger AddEvent ( SQVM * pVM );
	static SQInteger TriggerEvent ( SQVM * pVM );
};