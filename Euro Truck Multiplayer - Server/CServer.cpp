/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CServer.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer *	g_pServer;
CString				g_strInput;

CServer::CServer ( )
{
	m_pConfig			= NULL;
	m_pNetworkManager	= NULL;
	m_pCommandSystem	= NULL;
	m_pResourceManager  = NULL;
	m_bInitialized		= false;

	setlocale(LC_ALL,"C");
}

CServer::~CServer ( )
{
	GetResourceManager()->GetEventManager()->Call("onServerStop");

	SAFE_DELETE(m_pResourceManager);

	SAFE_DELETE(m_pNetworkManager);
	SAFE_DELETE(m_pConfig);

	m_pCommandSystem->UnregisterCommands();
	SAFE_DELETE(m_pCommandSystem);

	SAFE_DELETE(m_pInputThread);
}

bool CServer::Load()
{
	// Check initialize state.
	if ( m_bInitialized )
		return false;

	// Startup logging system.
	CLog::SetFile("logs\\server.log");

	// Startup Config parser.
	m_pConfig = new CConfig("server.xml");

	// Check config pointer.
	if(!m_pConfig) 
		return false;

	// Startup command system.
	m_pCommandSystem = new CCommandSystem();

	// Check command system pointer.
	if(!m_pCommandSystem) 
		return false;

	// Register basic commands.
	m_pCommandSystem->RegisterCommands();

	// Parse config file.
	SetVarValue("hostname", m_pConfig->Get("hostname"));

	SetVarValue("port", m_pConfig->Get("port"));

	CString strValue;
	if ( atoi(m_pConfig->Get("maxplayers")) > MAX_PLAYERS 
		|| atoi(m_pConfig->Get("maxplayers")) <= 0 )
		strValue.Format("%d", MAX_PLAYERS);
	else
		strValue = m_pConfig->Get("maxplayers");

	SetVarValue ( "maxplayers", strValue );

	SetVarValue("serverip", m_pConfig->Get("serverip"));

	// Create network.
	m_pNetworkManager = new CNetworkManager();

	// Check network pointer.
	if ( !m_pNetworkManager )
		return false;

	// Startup network for connections.
	m_pNetworkManager->Startup(atoi(GetVarValue("port").Get()), atoi(GetVarValue("maxplayers").Get()), GetVarValue("serverip"));

	// Startup resource manager.
	m_pResourceManager = new CResourceManager("resources");

	// Check resource manager pointer.
	if(!m_pResourceManager)
		return false;

	// Create thread for input.
	m_pInputThread = new CThread ( InputProcess );

	// Check input thread.
	if ( !m_pInputThread )
		return false;

	// Set initialize state.
	m_bInitialized = true;
	return true;
}

#ifdef _WIN32
void InputProcess ( PVOID args )
#else
void InputProcess ( void *args )
#endif
{
	while ( true )
	{
		char szInput[256];
		fgets(szInput, sizeof(szInput), stdin);
		size_t sLen = strlen(szInput);

		if ( szInput [ sLen - 1 ] == '\n' )
		{
			if(szInput[ sLen - 2] == '\r')
			{
				szInput[ sLen - 2] = '\0';
			}
			else
			{
				szInput[ sLen - 1] = '\0';
			}

			CString strsInput = g_strInput + szInput;
			if( g_pServer->GetCommandSystem())
			{
				g_pServer->GetCommandSystem()->ParseCommand(strsInput.GetPointer().c_str());
			}
		} else {
			g_strInput += szInput;
		}
		Sleep(10);
	}
}