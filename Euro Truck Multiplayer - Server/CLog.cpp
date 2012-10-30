/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CLog.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

FILE * CLog::m_fFile = NULL;
extern CServer * g_pClient;

void CLog::SetFile(const char*szFile)
{
	m_fFile = fopen(szFile, "a");

	if(m_fFile)
	{
		// Nothing?
	}
}

void CLog::Printf(const char*szLog, ...)
{
	if(m_fFile)
	{
		va_list vaArgs;
		char szBuffer[2048];

		va_start(vaArgs, szLog);
		vsnprintf(szBuffer, sizeof(szBuffer), szLog, vaArgs);
		va_end(vaArgs);

#ifdef SERVER
		printf("%s\n", szBuffer);
#endif
		fprintf(m_fFile, "%s\n", szBuffer);

		fflush(m_fFile);
	}
}