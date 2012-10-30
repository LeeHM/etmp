/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Launcher
 * Licence    : GNU GPL v3
 * File       : Utils.h
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
	static bool    InjectLibraryIntoProcess(HANDLE hProcess, char * szLibPath);
};