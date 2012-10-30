/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CUtils.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CUtils
{
public:
	static CString GetFromRegistry(HKEY hLoc, const char * szKeyName, const char * szNodeName);
	static char*   ToChar ( const char*szString );
};