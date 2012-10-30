/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CExceptionHandler.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient *g_pClient;

CExceptionHandler::CExceptionHandler()
{
	SetUnhandledExceptionFilter(ExceptionHandler);
}

CExceptionHandler::~CExceptionHandler()
{

}

long WINAPI CExceptionHandler::ExceptionHandler(_EXCEPTION_POINTERS * ExceptionInfo)
{
	ShowWindow(g_pClient->GetGameWindow(), SW_MINIMIZE);

	MessageBox(NULL, 
		CString(
			"Kod Bledu: 0x%p\nAdres B³êdu : 0x%p\nInfo B³êdu: 0x%d", 
			ExceptionInfo->ExceptionRecord->ExceptionCode, 
			ExceptionInfo->ExceptionRecord->ExceptionAddress,  
			ExceptionInfo->ExceptionRecord->ExceptionInformation
		).Get(), 
	"Crash!", NULL);

	TerminateProcess(GetCurrentProcess(), 0);
	return EXCEPTION_EXECUTE_HANDLER;
}

