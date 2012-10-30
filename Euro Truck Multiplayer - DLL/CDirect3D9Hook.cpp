/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CDirect3D9Hook.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CDirect3D9Hook::Direct3DCreate9_t CDirect3D9Hook::m_pfnDirect3DCreate9;

CDirect3D9Hook::CDirect3D9Hook()
{
	m_bHookInstalled = false;
}

CDirect3D9Hook::~CDirect3D9Hook()
{

}

bool CDirect3D9Hook::Install()
{
	if(!m_bHookInstalled)
	{      
		CLog::Printf("(Hook) CDirect3D9Hook::Install");

		m_pfnDirect3DCreate9 = reinterpret_cast < Direct3DCreate9_t > ( DetourFunction ( DetourFindFunction ( "D3D9.DLL", "Direct3DCreate9" ), reinterpret_cast < PBYTE > ( Direct3DCreate9_Hook ) ) );

		CLog::Printf("(Hook) CDirect3D9Hook::Install - Installed!");
        m_bHookInstalled = true;
        return true;
    }
    return false;
}

void CDirect3D9Hook::Uninstall()
{
	if(m_bHookInstalled)
    {
        if ( m_pfnDirect3DCreate9 )
		{
			DetourRemove ( reinterpret_cast < PBYTE > ( m_pfnDirect3DCreate9 ), reinterpret_cast < PBYTE > ( Direct3DCreate9_Hook ) );
		}
                        
        m_bHookInstalled = false;
    }
}

IDirect3D9 * WINAPI CDirect3D9Hook::Direct3DCreate9_Hook(UINT SDKVersion)
{
    IDirect3D9 * pD3D = m_pfnDirect3DCreate9(SDKVersion);

    if(pD3D)
    {
		return new IDirect3D9Hook(pD3D);
    }
    return NULL;
}