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
#pragma once

class CLog
{
private:
	static FILE * m_fFile;
public:
	static void SetFile(const char*szFile);
	static void Printf(const char*szLog, ...);
};