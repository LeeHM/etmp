/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CExceptionHandler.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#include <tlhelp32.h>

class CExceptionHandler
{
//private:
public:
	CExceptionHandler();
	~CExceptionHandler();

	static long WINAPI ExceptionHandler(_EXCEPTION_POINTERS * ExceptionInfo);
};