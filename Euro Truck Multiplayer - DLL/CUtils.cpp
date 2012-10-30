/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CUtils.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CString CUtils::GetFromRegistry(HKEY hLoc, const char * szKeyName, const char * szNodeName)
{
	HKEY hKey = NULL;
	char cszResult[MAX_PATH];
	CString szResult;
	DWORD dwSize = 255;

	if(RegOpenKeyEx(hLoc, szKeyName, NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		RegQueryValueEx(hKey, szNodeName, NULL, &dwType, (BYTE *)cszResult, &dwSize);
		szResult.Set(cszResult);
		RegCloseKey(hKey);
		return szResult;
	}
	return NULL;
}

char *CUtils::ToChar ( const char*szString )
{
	return const_cast<char*>(szString);
}