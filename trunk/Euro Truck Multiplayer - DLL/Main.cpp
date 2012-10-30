/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : Main.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CClient * g_pClient = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			g_pClient = new CClient();

			if(!g_pClient || !g_pClient->Load())
			{
				MessageBox(NULL, "Nie uda³o siê uruchomiæ clienta!\nPrzeinstaluj aplikacje a nastêpnie spróbuj ponownie.", "B³ad!", MB_ICONERROR);
				TerminateProcess(GetCurrentProcess(), 0);
			}
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			g_pClient->UnLoad();
			SAFE_DELETE(g_pClient);
			break;
		}
	}
	return TRUE;
}