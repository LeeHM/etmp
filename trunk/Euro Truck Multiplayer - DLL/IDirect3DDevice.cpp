/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : IDirect3DDevice.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;

IDirect3DDevice9Hook::IDirect3DDevice9Hook(IDirect3DDevice9 *pDevice)
{
	// Warpowanie poinetra Device DirectX'a.
	m_pDevice = pDevice;

	// Wysy³anie danych o stworzonym interfejsie directx do clienta.
	g_pClient->OnDirectDeviceCreate(m_pDevice);
}

HRESULT __stdcall IDirect3DDevice9Hook::Present ( CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return m_pDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall IDirect3DDevice9Hook::QueryInterface(REFIID riid, void** ppvObj)
{
	return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG __stdcall IDirect3DDevice9Hook::AddRef()
{
	return m_pDevice->AddRef();
}

ULONG __stdcall IDirect3DDevice9Hook::Release()
{
	ULONG uRet = m_pDevice->Release();

	if(uRet == 0)
	{
		delete this;
	}
	return uRet;
}

HRESULT __stdcall IDirect3DDevice9Hook::TestCooperativeLevel()
{
	return m_pDevice->TestCooperativeLevel();
}

UINT __stdcall IDirect3DDevice9Hook::GetAvailableTextureMem()
{
	return m_pDevice->GetAvailableTextureMem();
}

HRESULT __stdcall IDirect3DDevice9Hook::EvictManagedResources()
{
	return m_pDevice->EvictManagedResources();
}

HRESULT __stdcall IDirect3DDevice9Hook::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_pDevice->GetDirect3D(ppD3D9);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pDevice->GetDeviceCaps(pCaps);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_pDevice->GetDisplayMode(iSwapChain, pMode);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return m_pDevice->GetCreationParameters(pParameters);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_pDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void __stdcall IDirect3DDevice9Hook::SetCursorPosition(int X, int Y, DWORD Flags)
{
	m_pDevice->SetCursorPosition(X, Y, Flags);
}

BOOL __stdcall IDirect3DDevice9Hook::ShowCursor(BOOL bShow)
{
	return m_pDevice->ShowCursor(bShow);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDevice->GetSwapChain(iSwapChain, pSwapChain);
}

UINT __stdcall IDirect3DDevice9Hook::GetNumberOfSwapChains()
{
	return m_pDevice->GetNumberOfSwapChains();
}

HRESULT __stdcall IDirect3DDevice9Hook::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	CLog::Printf("(Call) IDirect3DDevice9Hook::Reset");
	g_pClient->OnLostDevice();

	HRESULT hr = m_pDevice->Reset(pPresentationParameters);

	if (SUCCEEDED(hr))
	{
		CLog::Printf("(Call) IDirect3DDevice9Hook::Reset-SUCCEDED");
	}
	g_pClient->OnResetDevice();
	return hr;
}

HRESULT __stdcall IDirect3DDevice9Hook::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_pDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_pDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pDevice->SetDialogBoxMode(bEnableDialogs);
}

void __stdcall IDirect3DDevice9Hook::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	m_pDevice->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void __stdcall IDirect3DDevice9Hook::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	m_pDevice->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	return m_pDevice->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT __stdcall IDirect3DDevice9Hook::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_pDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_pDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_pDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT __stdcall IDirect3DDevice9Hook::StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pDevice->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT __stdcall IDirect3DDevice9Hook::ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	return m_pDevice->ColorFill(pSurface, pRect, color);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return m_pDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_pDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_pDevice->SetDepthStencilSurface(pNewZStencil);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_pDevice->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT __stdcall IDirect3DDevice9Hook::BeginScene()
{
	return m_pDevice->BeginScene();
}

HRESULT __stdcall IDirect3DDevice9Hook::EndScene()
{
	g_pClient->OnRender();
	return m_pDevice->EndScene();
}

HRESULT __stdcall IDirect3DDevice9Hook::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* mat)
{
	return m_pDevice->SetTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* mat)
{
	return m_pDevice->GetTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9Hook::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* mat)
{
	return m_pDevice->MultiplyTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return m_pDevice->SetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pDevice->GetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return m_pDevice->SetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_pDevice->GetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	return m_pDevice->SetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
	return m_pDevice->GetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice9Hook::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pDevice->LightEnable(Index, Enable);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_pDevice->GetLightEnable(Index, pEnable);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return m_pDevice->SetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pDevice->GetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pDevice->SetRenderState(State, Value);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pDevice->GetRenderState(State, pValue);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_pDevice->CreateStateBlock(Type, ppSB);
}

HRESULT __stdcall IDirect3DDevice9Hook::BeginStateBlock()
{
	return m_pDevice->BeginStateBlock();
}

HRESULT __stdcall IDirect3DDevice9Hook::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_pDevice->EndStateBlock(ppSB);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDevice->SetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDevice->GetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_pDevice->GetTexture(Stage, ppTexture);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_pDevice->SetTexture(Stage, pTexture);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_pDevice->GetTextureStageState(Stage, Type, pValue);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pDevice->SetTextureStageState(Stage, Type, Value);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_pDevice->GetSamplerState(Sampler, Type, pValue);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT __stdcall IDirect3DDevice9Hook::ValidateDevice(DWORD* pNumPasses)
{
	return m_pDevice->ValidateDevice(pNumPasses);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return m_pDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_pDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pDevice->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetCurrentTexturePalette(UINT *PaletteNumber)
{
	return m_pDevice->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetScissorRect(CONST RECT* pRect)
{
	return m_pDevice->SetScissorRect(pRect);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetScissorRect(RECT* pRect)
{
	return m_pDevice->GetScissorRect(pRect);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pDevice->SetSoftwareVertexProcessing(bSoftware);
}

BOOL __stdcall IDirect3DDevice9Hook::GetSoftwareVertexProcessing()
{
	return m_pDevice->GetSoftwareVertexProcessing();
}

HRESULT __stdcall IDirect3DDevice9Hook::SetNPatchMode(float nSegments)
{
	return m_pDevice->SetNPatchMode(nSegments);
}

float __stdcall IDirect3DDevice9Hook::GetNPatchMode()
{
	return m_pDevice->GetNPatchMode();
}

HRESULT __stdcall IDirect3DDevice9Hook::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_pDevice->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice9Hook::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice9Hook::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_pDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_pDevice->SetVertexDeclaration(pDecl);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDevice->GetVertexDeclaration(ppDecl);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetFVF(DWORD FVF)
{
	return m_pDevice->SetFVF(FVF);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetFVF(DWORD* pFVF)
{
	return m_pDevice->GetFVF(pFVF);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return m_pDevice->CreateVertexShader(pFunction, ppShader);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_pDevice->SetVertexShader(pShader);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_pDevice->GetVertexShader(ppShader);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_pDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride)
{
	return m_pDevice->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetStreamSourceFreq(UINT StreamNumber, UINT Divider)
{
	return m_pDevice->SetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetStreamSourceFreq(UINT StreamNumber, UINT* Divider)
{
	return m_pDevice->GetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return m_pDevice->SetIndices(pIndexData);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_pDevice->GetIndices(ppIndexData);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return m_pDevice->CreatePixelShader(pFunction, ppShader);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_pDevice->SetPixelShader(pShader);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_pDevice->GetPixelShader(ppShader);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Hook::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT __stdcall IDirect3DDevice9Hook::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT __stdcall IDirect3DDevice9Hook::DeletePatch(UINT Handle)
{
	return m_pDevice->DeletePatch(Handle);
}

HRESULT __stdcall IDirect3DDevice9Hook::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_pDevice->CreateQuery(Type, ppQuery);
}