/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : Main.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CServer * g_pServer = NULL;

int main()
{
	// Startowanie core serwera.
	g_pServer = new CServer( );

	// Sprawdzanie uruchomienia serwera.
	if(!g_pServer || !g_pServer->Load( ))
	{
		CLog::Printf("[Error] Cannot start CServer core! Please reinstall and try leter.");
		Sleep(3000);
		TerminateProcess ( GetCurrentProcess(), 0 );
		return 0;
	}

	CLog::Printf("==========================================================");
	CLog::Printf("= " PROJECT_STRING);
	CLog::Printf("= " VERSION_STRING);
	CLog::Printf("==========================================================");
	CLog::Printf("= Hostname    : %s", g_pServer->GetVarValue("hostname").Get());
	CLog::Printf("= Port        : %d", atoi(g_pServer->GetVarValue("port").Get()));
	CLog::Printf("= Max Players : %d", atoi(g_pServer->GetVarValue("maxplayers").Get()));
	CLog::Printf("= Query Port  : %d", atoi(g_pServer->GetVarValue("port").Get())+1);
	if ( g_pServer->GetVarValue("serverip").IsNotEmpty() )
	{
		CLog::Printf("= Server IP   : %s", g_pServer->GetVarValue("serverip").Get());
	}
	CLog::Printf("==========================================================");

	// £adowanie zasobów.
	g_pServer->GetResourceManager()->ParseConfig();
	
	// If server started succesfull
	CLog::Printf("[Info] Server started succesfull!");

	// Pêtla g³ówna
	while ( true )
	{
		g_pServer->GetNetworkManager()->Process();
		
		Sleep(5);
	}

	// Usuwanie pointera server core
	SAFE_DELETE(g_pServer);
	return 0;
}