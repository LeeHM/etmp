/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CDebug.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;
bool bToFile = true; 

void CDebug::Log(const char *szLog, ...)
{
	va_list vaArgs;
	char szBuffer[2048];

	va_start(vaArgs, szLog);
	vsnprintf(szBuffer, sizeof(szBuffer), szLog, vaArgs);
	va_end(vaArgs);


	if(bToFile)
	{
		CLog::Printf(szBuffer);
	}

	/*CChatbox * pChatbox = g_pClient->GetChatbox();
	if( pChatbox )
	{
		pChatbox->AddChatMessage(szBuffer, 0xFFFFFFFF);
	}*/
}