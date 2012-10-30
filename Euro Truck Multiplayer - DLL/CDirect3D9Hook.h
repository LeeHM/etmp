/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CDirect3D9Hook.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CDirect3D9Hook
{
private:
	bool m_bHookInstalled;
	typedef IDirect3D9 *	 (WINAPI * Direct3DCreate9_t)(UINT);
	static Direct3DCreate9_t m_pfnDirect3DCreate9;
	static IDirect3D9 * WINAPI Direct3DCreate9_Hook(UINT SDKVersion);
	HINSTANCE	h_dllHandle;
public:
	CDirect3D9Hook();
	~CDirect3D9Hook();

	bool Install();
	void Uninstall();
};