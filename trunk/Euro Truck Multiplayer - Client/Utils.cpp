/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Client
 * Licence    : GNU GPL v3
 * File       : Utils.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "Main.h"

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


bool CUtils::InjectLibraryIntoProcess(HANDLE hProcess, char * szLibPath)
{
	bool bReturn = true;

	size_t sLibraryPathLen = (strlen(szLibPath) + 1);

	void * pRemoteLibraryPath = VirtualAllocEx(hProcess, NULL, sLibraryPathLen, MEM_COMMIT, PAGE_READWRITE);

	SIZE_T sBytesWritten = 0;
	WriteProcessMemory(hProcess, pRemoteLibraryPath, (void *)szLibPath, sLibraryPathLen, &sBytesWritten);

	if(sBytesWritten != sLibraryPathLen) 
	{
		bReturn = false;
	} else {
		HMODULE hKernel32 = GetModuleHandle("Kernel32");
		FARPROC pfnLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");
		HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pfnLoadLibraryA, pRemoteLibraryPath, 0, NULL);
		
		if(hThread) 
		{
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		} else {
			bReturn = false;
		}
	}

	VirtualFreeEx(hProcess, pRemoteLibraryPath, sizeof(pRemoteLibraryPath), MEM_RELEASE);
	return bReturn;
}