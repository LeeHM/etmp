/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CClient.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include <process.h>

enum eInit
{
	UNKNOW = -1,
	NOINITED = 0,
	INITED = 1
};

class CClient
{
private:
	bool			   m_bInitialized;
	IDirect3DDevice9 * m_pD3DDevice;
	CDirect3D9Hook	 * m_pDirect3D9Hook;
	CDirectInputHook * m_pDirectInputHook;
	CChatbox	     * m_pChatbox;
	CNetworkManager	 * m_pNetworkManager;
	CGraphic		 * m_pGraphic;
	CHooks			 * m_pHooks;
	CGame			 * m_pGame;
	CCommandLine	 * m_pCommandLine;
	CExceptionHandler *m_pExceptionHandler;
	HWND		       m_dwGameWindow;
	bool			   m_bInput;
	CString			   m_szAppPath;
	unsigned int	   m_uiBaseAddress;
public:
	// Konstruktor i destruktor.
	CClient();
	~CClient();

	// Funkcje ³adowania oraz wy³adowania modu³y CClient
	bool			Load();
	void			UnLoad();

	// Funkcje Hooka DirectX'a
	void			OnDirectDeviceCreate ( IDirect3DDevice9 * pD3DDevice );
	void			OnLostDevice();
	void			OnResetDevice();
	void			OnRender();

	// Funkcje pobieraj¹ce stan klienta.
	eInit			GetState( );

	// Funkcje zarz¹dzaj¹ce oknem gry.
	void			SetGameWindow(HWND dwGameWindow) { m_dwGameWindow = dwGameWindow; }
	HWND			GetGameWindow()			{ return m_dwGameWindow; }

	// Hook okna gry
	bool			GameWindow();

	CChatbox        *GetChatbox()			{ return m_pChatbox; }
	CNetworkManager *GetNetworkManager()	{ return m_pNetworkManager; }
	CHooks			*GetHooks()				{ return m_pHooks; }
	CGraphic		*GetGraphic()			{ return m_pGraphic; }
	CGame			*GetGame()				{ return m_pGame; }
	CCommandLine    *GetCommandLineParser() { return m_pCommandLine; }

	void		    SetInputState(bool bState) { m_bInput = bState; }
	bool			GetInputState()			{ return m_bInput; }

	void			SetRootPath(const char *szAppPath) { m_szAppPath.Set(szAppPath); }
	CString			GetRootPath()			{ return m_szAppPath; }

	void			GameLoop();

	bool			IsInitialized ( )		{ return m_bInitialized; }
	unsigned int    GetBaseAddress()		{ return m_uiBaseAddress; }
};