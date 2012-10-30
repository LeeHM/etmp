/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CGraphic.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *				LeNy <>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;

const unsigned char g_szPixel [] = { 0x42, 0x4D, 0x3A, 0, 0, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0x28, 0, 0, 
									0, 0x1, 0, 0, 0, 0x1, 0, 0, 0, 0x1, 0, 0x18, 0, 0, 0, 0, 0,
                                    0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0xFF, 0xFF, 0xFF, 0 };

CGraphic::CGraphic ( IDirect3DDevice9 * pD3DDevice ) 
{
	m_pGUI			=   NULL;
	m_pD3DDevice	=	pD3DDevice;
	m_bHidden		=	false;
	
	D3DXCreateTextureFromFileInMemory	( m_pD3DDevice, g_szPixel, sizeof (g_szPixel), &m_pDXPixelTexture );
	D3DXCreateSprite					( m_pD3DDevice, &m_pDXSprite );
	D3DXCreateFont(m_pD3DDevice, 18, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &m_Font );

	m_pGUI = new CGUI(m_pD3DDevice);
	m_pStatsGraph = new CStatsGraph(m_pD3DDevice);
}

CGraphic::~CGraphic ( )
{
	SAFE_DELETE(m_pGUI);
	SAFE_DELETE(m_pStatsGraph);
}

void CGraphic::Render ( )
{
	if(m_pStatsGraph)
		m_pStatsGraph->Render();

	if(m_bHidden)
	{
		RECT rct;
		GetWindowRect(g_pClient->GetGameWindow(), &rct);
		DrawRectangle(0.0f, 0.0f, (float)rct.right, (float)rct.bottom, 0x3C000000);
	}
   
	RECT rPosition;
    m_Font->DrawText(NULL, VERSION_STRING, -1, &rPosition, DT_CALCRECT, 0xFF000000);
    float fDlugosc = (float)(rPosition.right - rPosition.left);

	RECT rct;
	GetWindowRect(g_pClient->GetGameWindow(), &rct);
	SetRect(&rct, (LONG)(rct.right-fDlugosc), (LONG)(rct.bottom-20.0f), 0, 0);
	m_Font->DrawText(NULL, VERSION_STRING, -1, &rct, DT_NOCLIP, 0x3CFFFFFF); 

	//Score Board
	if(GetAsyncKeyState(VK_TAB) && g_pClient->GetNetworkManager()->IsConnected())
	{
		g_pClient->GetChatbox()->SetVisible(false);

		RECT rct;
		RECT screenRCT;
		GetWindowRect(g_pClient->GetGameWindow(), &screenRCT);

		// T³o
		DrawRectangle((float)screenRCT.right/2-400.0f, (float)screenRCT.bottom/2-250.0f, 800.0f, 500.0f, 0x3C000000);

		//Nag³owek
		DrawRectangle((float)screenRCT.right/2-400.0f, (float)screenRCT.bottom/2-250.0f, 800.0f, 30.0f, 0xFF000000);

		//Nag³owek #2
		DrawRectangle((float)screenRCT.right/2-400.0f, (float)screenRCT.bottom/2-250.0f+30.0f, 800.0f, 17.0f, 0x3C000000);

		// Nazwa serwera
		SetRect(&rct, (LONG)(screenRCT.right/2-400.0f+8.0f), (LONG)(screenRCT.bottom/2-250.0f+7.0f), 0, 0);
		m_Font->DrawText(NULL, g_pClient->GetNetworkManager()->GetServerManager()->GetHostName().Get(), -1, &rct, DT_NOCLIP, 0xFFFFFFFF);

		//Liczba graczy
		SetRect(&rct, (LONG)(screenRCT.right/2-400.0f+700.0f), (LONG)(screenRCT.bottom/2-250.0f+7.0f), 0, 0);
		m_Font->DrawText(NULL, CString("Graczy: %d/%d", g_pClient->GetNetworkManager()->GetPlayerManager()->GetPlayersCount(), g_pClient->GetNetworkManager()->GetServerManager()->GetMaxPlayers()).Get(), -1, &rct, DT_NOCLIP, 0xFFFFFFFF);

		float fX, fY;
		fX = (float)screenRCT.right/2-400.0f; fY = (float)screenRCT.bottom/2-250.0f+30.0f;

		// ID
		SetRect(&rct, (LONG)(fX +20.0f)+1, (LONG)fY+1, 0, 0);
		m_Font->DrawText(NULL, "ID", -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)(fX +20.0f), (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, "ID", -1, &rct, DT_NOCLIP, 0xFFFFFFFF); 

		// Nick
		SetRect(&rct, (LONG)(fX+100.0f)+1, (LONG)fY+1, 0, 0);
		m_Font->DrawText(NULL, "Nick", -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)(fX+100.0f), (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, "Nick", -1, &rct, DT_NOCLIP, 0xFFFFFFFF); 

		//Ping
		SetRect(&rct, (LONG)(fX +400.0f)+1, (LONG)fY+1, 0, 0);
		m_Font->DrawText(NULL, "Ping", -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)(fX+400.0f), (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, "Ping", -1, &rct, DT_NOCLIP, 0xFFFFFFFF); 

		fY += 15.0f;

		for(int i = 0; i < MAX_PLAYERS; i ++)
		{
			if(g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetId() == i)
			{
				// Nick;

				SetRect(&rct, (LONG)(fX+100.0f)+1, (LONG)fY+1, 0, 0);
				m_Font->DrawText(NULL, g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetName().Get(), -1, &rct, DT_NOCLIP, 0xFF000000); 
 
				DWORD dwColor = g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetColor();
				SetRect(&rct, (LONG)(fX+100.0f), (LONG)fY, 0, 0);
				m_Font->DrawText(NULL, g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetName().Get(), -1, &rct, DT_NOCLIP, ((dwColor >> 8) | 0xFF000000)); 

				// ID
				SetRect(&rct, (LONG)(fX +20.0f)+1, (LONG)fY+1, 0, 0);
				m_Font->DrawText(NULL, CString("%d", g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetId()).Get(), -1, &rct, DT_NOCLIP, 0xFF000000); 

				SetRect(&rct, (LONG)(fX +20.0f), (LONG)fY, 0, 0);
				m_Font->DrawText(NULL, CString("%d", g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetId()).Get(), -1, &rct, DT_NOCLIP, 0xFFFFFFFF); 
	
				// Ping				
				SetRect(&rct, (LONG)(fX +400.0f)+1, (LONG)fY+1, 0, 0);
				m_Font->DrawText(NULL, CString("%d", g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetPing()).Get(), -1, &rct, DT_NOCLIP, 0xFF000000);

				SetRect(&rct, (LONG)(fX +400.0f), (LONG)fY, 0, 0);
				m_Font->DrawText(NULL, CString("%d", g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetPing()).Get(), -1, &rct, DT_NOCLIP, 0xFFFFFFFF); 

				fY += 15.0f;
			} else {
				CPlayer *pPlayer = g_pClient->GetNetworkManager()->GetPlayerManager()->GetAt(i);			

				if(pPlayer)
				{
					SetRect(&rct, (LONG)(fX+20.0f)+1, (LONG)fY+1, 0, 0);
					m_Font->DrawText(NULL, CString("%d", pPlayer->GetId()).Get(), -1, &rct, DT_NOCLIP, 0xFF000000);
	
					SetRect(&rct, (LONG)(fX+20.0f), (LONG)fY, 0, 0);
					m_Font->DrawText(NULL, CString("%d", pPlayer->GetId()).Get(), -1, &rct, DT_NOCLIP, 0xFFFFFFFF); 

					SetRect(&rct, (LONG)(fX+400.0f)+1, (LONG)fY+1, 0, 0);
					m_Font->DrawText(NULL, CString("%d", pPlayer->GetPing()).Get(), -1, &rct, DT_NOCLIP, 0xFF000000);
	
					SetRect(&rct, (LONG)(fX+400.0f), (LONG)fY, 0, 0);
					m_Font->DrawText(NULL, CString("%d", pPlayer->GetPing()).Get(), -1, &rct, DT_NOCLIP, 0xFFFFFFFF); 

					SetRect(&rct, (LONG)(fX+100.0f)+1, (LONG)fY+1, 0, 0);
					m_Font->DrawText(NULL, pPlayer->GetName().Get(), -1, &rct, DT_NOCLIP, 0xFF000000); 
	
					SetRect(&rct, (LONG)(fX+100.0f), (LONG)fY, 0, 0);
					m_Font->DrawText(NULL, pPlayer->GetName().Get(), -1, &rct, DT_NOCLIP, ((pPlayer->GetColor() >> 8) | 0xFF000000)); 
					
					fY += 15.0f;
				}
			}
		}
	} else
		g_pClient->GetChatbox()->SetVisible(true);


	if(m_pGUI)
		m_pGUI->Render();
}

void CGraphic::OnLostDevice ( )
{
	if(m_pDXSprite)
		m_pDXSprite->OnLostDevice();

	m_pGUI->OnLostDevice();
}

void CGraphic::OnResetDevice ( )
{
	if(m_pDXSprite)
		m_pDXSprite->OnResetDevice();

	m_pGUI->OnResetDevice();
}

void CGraphic::DrawRectangle ( float fX, float fY, float fWidth, float fHeight, unsigned long ulColor )
{
    m_pDXSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

    D3DXMATRIX matrix;
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &D3DXVECTOR2(fWidth, fHeight), NULL, 0.0f, &D3DXVECTOR2(fX, fY));

    m_pDXSprite->SetTransform(&matrix);
    m_pDXSprite->Draw(m_pDXPixelTexture, NULL, NULL, NULL, ulColor);
    m_pDXSprite->End();
}

void CGraphic::Fade(bool bFade) 
{ 
	m_bHidden = bFade; 
}

bool CGraphic::Fade() 
{ 
	return m_bHidden; 
}

bool CGraphic::WindowProcess( HWND hwnd,UINT uMsg, WPARAM wParam,LPARAM lParam )
{
	return false;
}

float CGraphic::GetScreenWidth() 
{ 
	RECT rct;
	GetWindowRect(g_pClient->GetGameWindow(), &rct);
	return (float)rct.right;
}

float CGraphic::GetScreenHeight() 
{ 
	RECT rct;
	GetWindowRect(g_pClient->GetGameWindow(), &rct);
	return (float)rct.bottom;
}