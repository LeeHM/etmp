/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CClient.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient *g_pClient;
void MainLoop(PVOID v)
{
	while(true)
	{
		g_pClient->GameLoop();
		Sleep(5);
	}
}

CClient::CClient()
{
	// Set default values for private class varibles.
	// And set null value for all pointers be default.
	m_bInitialized = false;
	m_bInput = true;
	m_pChatbox = NULL;
	m_pDirectInputHook = NULL;
	m_pDirect3D9Hook = NULL;
	m_pNetworkManager = NULL;
	m_pD3DDevice = NULL;
	m_pGraphic = NULL;
}

CClient::~CClient()
{
	// Unload client.
	//UnLoad();
}

bool CClient::Load()
{
	if(!m_bInitialized)
	{
		m_uiBaseAddress = (unsigned int)GetModuleHandle(NULL);
		m_uiBaseAddress -= 0x400000;

		// Get game root path.
		SetRootPath(CUtils::GetFromRegistry(HKEY_LOCAL_MACHINE, "Software\\Euro Truck Multiplayer", "MPPath").Get());

		// Start log system.
		CString szLogFile("C:\\Development\\Release\\Client.log");
		CLog::SetFile(szLogFile.Get());

		// Install DirectInput Hook
		m_pDirectInputHook = new CDirectInputHook();
		if(!m_pDirectInputHook)
			return false;

		m_pDirectInputHook->Install();

		CLog::Printf("(Startup) Started! (Address: 0x%x)", m_pDirectInputHook);

		// Install DirectX Hook.
		CLog::Printf("(Startup) CDirect3D9Hook");

		m_pDirect3D9Hook = new CDirect3D9Hook();
		if(!m_pDirect3D9Hook) 
			return false;

		m_pDirect3D9Hook->Install();

		CLog::Printf("(Startup) Started! (Address: 0x%x)", m_pDirect3D9Hook);
		
		CLog::Printf("(Startup) CHooks");
		
		// Install all hooks.
		m_pHooks = new CHooks();
		if(!m_pHooks)
			return false;

		m_pHooks->Install();

		CLog::Printf("(Startup) Started! (Address: 0x%x)", m_pHooks);

		// Create Game Interface.
		m_pGame = new CGame ();

		if(!m_pGame)
			return false;

		// Create NetworkManager.
		m_pNetworkManager = new CNetworkManager ( );

		if ( !m_pNetworkManager )
			return false;

		m_pCommandLine = new CCommandLine();

		if(!m_pCommandLine)
			return false;

		m_pCommandLine->Parse(GetCommandLineA());

		m_pExceptionHandler = new CExceptionHandler();
	
		if(!m_pExceptionHandler)
			return false;

		_beginthread(MainLoop, 0, NULL);

		// Print debug information about startup all.
		CLog::Printf( "(DEBUG) Klient wystartowa³ pomyœlnie o pointerze - 0x%x.", this );

		// Set initialize value to true.
		m_bInitialized = true;
		return true;
	}
	return false;
}

void CClient::UnLoad()
{
	// Uninstall DirectInputHook.
	m_pDirectInputHook->Uninstall();
	SAFE_DELETE(m_pDirectInputHook);

	// Delete CGraphic.
	SAFE_DELETE(m_pGraphic);

	// Uninstall Direct3D9Hook.
	m_pDirect3D9Hook->Uninstall();
	SAFE_DELETE(m_pDirect3D9Hook);

	// Uninstall another hooks.
	m_pHooks->Uninstall();
	SAFE_DELETE(m_pHooks);

	// Uninstall network.
	if ( m_pNetworkManager->IsConnected() )
	{
		m_pNetworkManager->Disconnect();
	}
	SAFE_DELETE(m_pNetworkManager);

	// Delete game interface.
	SAFE_DELETE(m_pGame);

	// Set initialized to false.
	m_bInitialized = false;
}

eInit CClient::GetState()
{ 
	switch(m_bInitialized) 
	{ 
	case false: 
		return NOINITED;  
	case true: 
		return INITED;
	}
	return NOINITED;
}

void CClient::OnLostDevice()
{
	CLog::Printf("(Call) CClient::OnLostDevice");
	
	if(m_pChatbox)
	{
		m_pChatbox->OnLostDevice ( );
	}

	if ( m_pGraphic )
	{
		m_pGraphic->OnLostDevice ( );
	}
}

void CClient::OnResetDevice()
{
	CLog::Printf("(Call) CClient::OnResetDevice");

	if(m_pChatbox)
	{
		m_pChatbox->OnResetDevice ( );
	}

	if ( m_pGraphic )
	{
		m_pGraphic->OnResetDevice ( );
	}
}

void CClient::OnRender()
{
	if(m_pChatbox)
	{
		m_pChatbox->Render();
	}

	if ( m_pGraphic )
	{
		m_pGraphic->Render ( );
	}

	//GameLoop();
}

void CClient::OnDirectDeviceCreate ( IDirect3DDevice9 * pD3DDevice )
{
	// Warp D3DDevice pointer.
	m_pD3DDevice = pD3DDevice;

	// Initialize DirectX Elements.
	if ( !m_pChatbox )
	{
		m_pChatbox = new CChatbox(m_pD3DDevice);
		m_pChatbox->AddChatMessage( VERSION_STRING" - Wystartowa³!", 0xFF0000FF);

		m_pNetworkManager->Connect(m_pCommandLine->GetValue("host")->strValue.Get(), atoi(m_pCommandLine->GetValue("port")->strValue.Get()),
			m_pCommandLine->GetValue("nick")->strValue.Get());
	}

	if ( !m_pGraphic )
	{
		m_pGraphic = new CGraphic ( m_pD3DDevice ) ;
	}
}

bool CClient::GameWindow()
{
	return WndHook();
}

void CClient::GameLoop()
{
	if(m_pNetworkManager)
	{
		m_pNetworkManager->Process();
	}
}