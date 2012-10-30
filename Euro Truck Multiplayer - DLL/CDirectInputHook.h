/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CDirectInputHook.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CDirectInputHook
{
private:
	typedef HRESULT				 (WINAPI * DirectInput8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);

	static DirectInput8Create_t  m_pDirectInput8Create;
	bool					 m_bHookInstalled;
	static bool					 m_bOurDeviceCreated;
	static HRESULT WINAPI		 DirectInput8Create_Hook(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);

public:
	CDirectInputHook();

	void Install();
	void Uninstall();
};
