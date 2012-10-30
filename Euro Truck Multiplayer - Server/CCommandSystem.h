/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CCommandSystem.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

#define MAX_COMMAND_LEN 128

typedef void (* Cmd_Function )( char *szParams );
struct CCommand
{
	char m_szCommand[MAX_COMMAND_LEN];
	Cmd_Function m_Function;
};

class CCommandSystem
{
private:
	CString szInput;
	std::list < CCommand *> m_Commands;
public:
	CCommandSystem();
	~CCommandSystem();

	void ParseCommand ( const char * szInputB );

	void RegisterCommands();
	void UnregisterCommands();

	void AddCommand ( const char *szCommand, Cmd_Function Function );
	void RemoveCommand ( const char *szCommand);
	bool ProcessCommand ( const char *szCommand, const char *szParams );
};