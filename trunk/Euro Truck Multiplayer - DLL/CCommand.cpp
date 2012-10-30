/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CCommand.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;

void cmdQuit ( char *szParams )
{
	TerminateProcess(GetCurrentProcess(), 0);
}

void cmdTest(char *szParams)
{
	g_pClient->GetChatbox()->AddDebugMessage("%f, %f, %f", TOFLOAT(0x614CAC), TOFLOAT(0x614CB0), TOFLOAT(0x614CB4));
}

CCommand::CCommand( )
{
	AddCommand("/q", cmdQuit);
	AddCommand("/test", cmdTest);
}

CCommand::~CCommand( )
{
	RemoveCommand("/q");
	RemoveCommand("/test");
}

void CCommand::AddCommand ( const char *szCommandName, CMDFunction Function )
{
	// Tworzenie pointera komendy
	Command * pCommand = new Command();
	
	// Przypisywanie nazwy komendy.
	strcpy(pCommand->szCommand, szCommandName);
	
	// Przypisywanie funkcji do komendy
	pCommand->cmdFunction = Function;
	
	// Dodawanie komendy do kontentera std::list
	m_Commands.push_back(pCommand);
}

void CCommand::RemoveCommand ( const char *szCommandName )
{
	// Definicja pointera komendy.
	Command * pCommand = NULL;
	
	std::list < Command * >::iterator iter;
	
	for ( iter = m_Commands.begin(); iter != m_Commands.end(); iter ++ )
	{
		if(!strcmp((*iter)->szCommand, szCommandName))
		{
			pCommand = (*iter);
			break;
		}
	}
	
	if ( pCommand )
	{
		m_Commands.remove(pCommand);
		delete pCommand;
	}
}

bool CCommand::ProcessCommand ( const char *szBuffer )
{
	CString strInput = CString ( szBuffer );

	size_t sSpace = strInput.Find(' ', 0);
	CString strCommand = strInput.CutStr(0, sSpace++);
	CString strParams = strInput.CutStr(sSpace, (strInput.GetLength() - sSpace));

	std::list < Command * >::iterator iter;
	for ( iter = m_Commands.begin(); iter != m_Commands.end(); iter ++ )
	{
		if(!strcmp((*iter)->szCommand, strCommand.Get()))
		{
			(*iter)->cmdFunction(CUtils::ToChar(strParams.Get()));
			return true;
		}
	}
	return false;
}