/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CCommandSystem.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer *g_pServer;

CCommandSystem::CCommandSystem()
{
	
}

CCommandSystem::~CCommandSystem()
{

}

void CCommandSystem::ParseCommand ( const char * szInputB )
{
	// Warpowanie klasy string do CString
	szInput.Set(szInputB);

	// Sprawdzanie czy wpisany tekst jest napewno wpisany (Wiem bezsensowny tekst).
	if(szInput.IsNotEmpty()) 
	{
		size_t sSpace = szInput.Find(' ', 0);
		CString szCommand = szInput.CutStr(0, sSpace++);
		CString szParams = szInput.CutStr(sSpace, (szInput.GetLength() - sSpace));

		// Sprawdzanie czy komenda nadal jest pe³na. Je¿eli nie stop.
		if ( szCommand.IsEmpty( ) )
			return;

		// Komendy
		ProcessCommand ( szCommand.Get(), (!szParams.GetLength() ? "" : szParams.Get()) );
	}
}

void CCommandSystem::AddCommand ( const char *szCommand, Cmd_Function Function )
{
	// Tworzenie pointera komendy.
	CCommand * pCommand = new CCommand();

	// Zapisywanie jej nazwy do pointera.
	strcpy(pCommand->m_szCommand, szCommand);

	// Zapisywanie jej callbacka do pointera.
	pCommand->m_Function = Function;

	// Dodawanie komendy do kontenera.
	m_Commands.push_back(pCommand);
}

void CCommandSystem::RemoveCommand ( const char *szCommand )
{
	CCommand * pCommand = NULL;
	std::list<CCommand *>::iterator iter;
	for ( iter = m_Commands.begin(); iter != m_Commands.end(); iter ++ )
	{
		if ( !strcmp( (*iter)->m_szCommand , szCommand ) )
		{
			pCommand = (*iter);
		}
	}

	if ( pCommand )
	{
		m_Commands.remove ( pCommand );
		delete pCommand;
	}
}

bool CCommandSystem::ProcessCommand ( const char *szCommand, const char *szParams )
{
	CCommand * pCommand = NULL;
	std::list<CCommand *>::iterator iter;
	for ( iter = m_Commands.begin(); iter != m_Commands.end(); iter ++ )
	{
		if ( !_stricmp( (*iter)->m_szCommand , const_cast<char *>(szCommand) ) )
		{
			pCommand = (*iter);
			if(pCommand)
			{
				pCommand->m_Function(const_cast<char *>(szParams));	
				return true;
			}
		}
	}
	return false;
}

/* 
 * Dodawanie & Usuwanie komend.
 */
namespace Util
{
	void Quit(char *szParams)
	{
		ExitProcess ( 0 );
	}
}

void LoadRes(char *szParams)
{
	CLog::Printf("Trwa ladowanie zasobu o nazwie %s..", szParams);
	g_pServer->GetResourceManager()->Load(szParams);
}

void UnLoadRes(char *szParams)
{
	CLog::Printf("Trwa stopowanie zasobu o nazwie %s..", szParams);;
	g_pServer->GetResourceManager()->Unload(szParams);
}

void ReStartRes(char *szParams)
{
	CLog::Printf("Trwa restartowanie zasobu o nazwie %s..", szParams);;
	g_pServer->GetResourceManager()->Restart(szParams);
}

void CCommandSystem::RegisterCommands()
{
	AddCommand("/q", Util::Quit);

	// Funkcje do zarz¹dzania zasobami. TODO! Dodanie sprawdzania czy zasób istnieje etc.
	AddCommand("/loadresource", LoadRes);
	AddCommand("/unloadresource", UnLoadRes);
	AddCommand("/restartresource", ReStartRes);
}

void CCommandSystem::UnregisterCommands()
{
	RemoveCommand("q");

	// Funkcje do zarz¹dzania zasobami.
	RemoveCommand("loadresource");
	RemoveCommand("unloadresource");
	RemoveCommand("restartresource");
}