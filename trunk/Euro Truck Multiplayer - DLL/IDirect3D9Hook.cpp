/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : IDirect3D9Hook.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;

IDirect3D9Hook::IDirect3D9Hook(IDirect3D9 * pD3D)
{
	m_pD3D = pD3D;
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::QueryInterface(REFIID riid, void ** ppvObj)
{
	return m_pD3D->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE IDirect3D9Hook::AddRef()
{
	return m_pD3D->AddRef();
}

ULONG STDMETHODCALLTYPE IDirect3D9Hook::Release()
{
	ULONG uRet = m_pD3D->Release();

	if(uRet == 0)
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::RegisterSoftwareDevice(void * pInitializeFunction)
{
	return m_pD3D->RegisterSoftwareDevice(pInitializeFunction);
}

UINT STDMETHODCALLTYPE IDirect3D9Hook::GetAdapterCount()
{
	return m_pD3D->GetAdapterCount();
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 * pIdentifier)
{
	return m_pD3D->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT STDMETHODCALLTYPE IDirect3D9Hook::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return m_pD3D->GetAdapterModeCount(Adapter, Format);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return m_pD3D->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return m_pD3D->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return m_pD3D->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return m_pD3D->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD * pQualityLevels)
{
	return m_pD3D->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return m_pD3D->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return m_pD3D->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	return m_pD3D->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR STDMETHODCALLTYPE IDirect3D9Hook::GetAdapterMonitor(UINT Adapter)
{
	return m_pD3D->GetAdapterMonitor(Adapter);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Hook::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS * pPresentationParameters, IDirect3DDevice9 ** ppReturnedDeviceInterface)
{
	HRESULT hr = m_pD3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	g_pClient->SetGameWindow(hFocusWindow);
	g_pClient->GameWindow();

	if(SUCCEEDED(hr))
	{
		*ppReturnedDeviceInterface = new IDirect3DDevice9Hook(*ppReturnedDeviceInterface);
	}
	return hr;
}
