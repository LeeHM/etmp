/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CCommand.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

typedef void(* CMDFunction)(char *szParams);

struct Command
{
	char szCommand[25];
	CMDFunction cmdFunction;
};

class CCommand
{
private:
	std::list<Command *> m_Commands;
public:
	CCommand( );
	~CCommand ( );
	
	void AddCommand ( const char *szCommandName, CMDFunction Function );
	void RemoveCommand ( const char *szCommandName );
	bool ProcessCommand ( const char *szBuffer );
};