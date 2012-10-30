/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CDirectInputHook.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CDirectInputHook::DirectInput8Create_t CDirectInputHook::m_pDirectInput8Create;
bool CDirectInputHook::m_bOurDeviceCreated = true;

CDirectInputHook::CDirectInputHook()
{
	m_bHookInstalled = false;
}

HRESULT WINAPI CDirectInputHook::DirectInput8Create_Hook(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
	CLog::Printf("(Hook) CDirectInputHook::DirectInput8Create_Hook");
	HRESULT hr = m_pDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	if(SUCCEEDED(hr))
	{
		if(m_bOurDeviceCreated)
		{
			IDirectInput8 * pDInput = (IDirectInput8 *)*ppvOut;
			*ppvOut = new CDirectInput8Proxy(pDInput);
		}
		else
			m_bOurDeviceCreated = true;
	} else
		CLog::Printf("(Hook) CDirectInputHook::DirectInput8Create_Hook - Cannot install a HOOK!");

	return hr;
}

void CDirectInputHook::Install()
{
	if(!m_bHookInstalled)
	{
		CLog::Printf("(Hook) CDirectInputHook::Install");

		m_pDirectInput8Create = reinterpret_cast < DirectInput8Create_t > ( DetourFunction ( DetourFindFunction ( "DInput8.dll", "DirectInput8Create" ), reinterpret_cast < PBYTE > ( DirectInput8Create_Hook ) ) );

		CLog::Printf("(Hook) CDirectInputHook::Install - Installed!");

		m_bHookInstalled = true;
	}
}

void CDirectInputHook::Uninstall()
{
	if(m_bHookInstalled)
	{
		if ( m_pDirectInput8Create )
		{
			DetourRemove ( reinterpret_cast < PBYTE > ( m_pDirectInput8Create ), reinterpret_cast < PBYTE > ( DirectInput8Create_Hook ) );
		}
		m_bHookInstalled = false;
	}
}
