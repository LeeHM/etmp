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
#pragma once

#define MAX_JUMPCODE_SIZE 50

//FROM MTA
class CHookTools
{
public:
	static VOID			HookInstallMethod( DWORD dwInstallAddress, DWORD dwHookFunction );
	static VOID			HookInstallCall ( DWORD dwInstallAddress, DWORD dwHookFunction );
	static BOOL			HookInstall( DWORD dwInstallAddress, DWORD dwHookHandler, int iJmpCodeSize );
	static BYTE *		CreateJump ( DWORD dwFrom, DWORD dwTo, BYTE * ByteArray );
	static DWORD		UnProtect ( DWORD dwAddress, int iSize );
};

class CHooks
{
private:
	bool		m_bInstalled;
public:
	CHooks();
	~CHooks();

	void Install();
	void Uninstall();
};