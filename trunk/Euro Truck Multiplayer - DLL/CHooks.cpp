/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CHooks.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;

CHooks::CHooks()
{
	m_bInstalled = false;
}

CHooks::~CHooks()
{

}


/*
	HOOK START
*/
void _declspec(naked) HOOK_MainLoop ()
{
	_asm {
		pushad
	}

	g_pClient->GameLoop();

	_asm {
		popad
		pop esi
		add esp, 1Ch
		retn
	}
}

#define FUNC_PrismMessage 0x58E6F8
DWORD dwFunc = FUNC_PrismMessage;
void _declspec(naked) HOOK_ProcessExit()
{
	if(g_pClient->GetNetworkManager())
		g_pClient->GetNetworkManager()->Disconnect();


	// Print message

	_asm
	{
		push	0x59B308
		call	dwFunc
		pop		ecx
		retn
	}
}

/*
	HOOK END
 */

void CHooks::Install()
{
	if(!m_bInstalled)
	{
		// Game loop hook !Caused crash!.
		//CHookTools::HookInstall( FUNC_MainLoop, (DWORD)HOOK_MainLoop, 4 );
		CHookTools::HookInstall(0x4074B0, (DWORD)HOOK_ProcessExit, 6);
		/*UnProtect(FLOAT_AudioVolume, 4);
		*(float*)FLOAT_AudioVolume = 0.00000f;
		UnProtect(FLOAT_SFXVolume, 4);
		*(float*)FLOAT_SFXVolume = 0.000000f;*/



		m_bInstalled = true;
	}
}

void CHooks::Uninstall()
{
	if(m_bInstalled)
	{
		m_bInstalled = false;
	}
}

VOID CHookTools::HookInstallMethod( DWORD dwInstallAddress, DWORD dwHookFunction )
{
    *(PDWORD)dwInstallAddress = (DWORD)dwHookFunction;
}

VOID CHookTools::HookInstallCall ( DWORD dwInstallAddress, DWORD dwHookFunction )
{
    DWORD dwOffset = dwHookFunction - (dwInstallAddress + 5);
    *(BYTE*)(dwInstallAddress) = 0xE8;
    *(DWORD*)(dwInstallAddress+1) = dwOffset;
}

BOOL CHookTools::HookInstall( DWORD dwInstallAddress, DWORD dwHookHandler, int iJmpCodeSize )
{
    BYTE JumpBytes[MAX_JUMPCODE_SIZE];
	UnProtect(dwInstallAddress, (iJmpCodeSize+5));
    memset ( JumpBytes, 0x90, MAX_JUMPCODE_SIZE );
    if ( CreateJump ( dwInstallAddress, dwHookHandler, JumpBytes ) )
    {
        memcpy ( (PVOID)dwInstallAddress, JumpBytes, iJmpCodeSize );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BYTE * CHookTools::CreateJump ( DWORD dwFrom, DWORD dwTo, BYTE * ByteArray )
{
    ByteArray[0] = 0xE9;
    *(DWORD *)(&ByteArray[1]) = dwTo - (dwFrom + 5);
    return ByteArray;
}


DWORD CHookTools::UnProtect ( DWORD dwAddress, int iSize )
{
	DWORD dwOldProtection;
	VirtualProtect((void *)dwAddress, iSize, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	return dwOldProtection;
}
