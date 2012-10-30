/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CChatbox.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient * g_pClient;

CChatbox::CChatbox(IDirect3DDevice9 *pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	m_pCommand   = NULL;
	if(m_pD3DDevice)
	{
		D3DXCreateFont(m_pD3DDevice, 15, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &m_Font );
	}

	for(int x = 0; x != 10; x++)
	{
		//memset(szLine[x], 0, 256);
		m_pLines[x] = new SChatLine;
		memset(m_pLines[x]->szMessage, 0, 256);
	}

	szInputBuffer[0] = '\0';

	// Set default varibles.
	m_bShowed = true;
	m_bTypping = false;

	// Create command instance.
	m_pCommand = new CCommand();

	// Ustawianie domyœlnej pozycji.
	RECT rect;
	GetWindowRect(g_pClient->GetGameWindow(), &rect);
	SetPosition(5.0f, (float)(rect.bottom-210.0f));
}

CChatbox::~CChatbox ()
{
	SAFE_DELETE(m_pCommand);

	for(int i = 0; i < 10; i ++)
	{
		SAFE_DELETE(m_pLines[i]);
	}
}

void CChatbox::DrawLine(int i, float fX, float fY)
{
	if(!m_pLines[i]) return;

	RECT rct = { 0 };
	if(m_pLines[i]->iType == TYPE_MESSAGE)
	{
		//Rysowanie wiadomoœci
		SetRect(&rct, (LONG)fX+1, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 
	
		SetRect(&rct, (LONG)fX-1, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY+1, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY-1, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, m_pLines[i]->dwColor); 
	} else if (m_pLines[i]->iType == TYPE_CHAT_MESSAGE) {
		SetRect(&rct, (LONG)fX+1, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szNick, -1, &rct, DT_NOCLIP, 0xFF000000); 
	
		SetRect(&rct, (LONG)fX-1, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szNick, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY+1, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szNick, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY-1, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szNick, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL,  m_pLines[i]->szNick, -1, &rct, DT_NOCLIP, ((m_pLines[i]->dwPlayerColor >> 8) | 0xFF000000)); 

		//Obliczanie d³ugoœci nicku.
        RECT rPosition;
        m_Font->DrawText(NULL, m_pLines[i]->szNick, -1, &rPosition, DT_CALCRECT, 0xFF000000);
        float fDlugosc = (float)(rPosition.right - rPosition.left);

		fX += fDlugosc+3.0f;

		//Rysowanie wiadomoœci
		SetRect(&rct, (LONG)fX+1, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 
	
		SetRect(&rct, (LONG)fX-1, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY+1, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY-1, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, 0xFF000000); 

		SetRect(&rct, (LONG)fX, (LONG)fY, 0, 0);
		m_Font->DrawText(NULL, m_pLines[i]->szMessage, -1, &rct, DT_NOCLIP, m_pLines[i]->dwColor);
	}
}

void CChatbox::Render()
{
	if(m_bShowed && m_Font)
	{
		RECT rct = { 0 };
		
		float fX = m_fX;
		float fY = m_fY;

		//Rysowanie lini czatu.
		for( int i = 0; i < 10; i++ )
		{	
			DrawLine(i, fX, fY);
			fY += 18.0f;
		}

		if(m_bTypping)
		{
			// Add some pixels for input box.
			fY += 2.0f; 
			
			// Define input text.

			CString szType;
			szType.Format("%s%s_", SAY_PERFIX, szInputBuffer);

			// Add some for input label.
			//fY += 2.0f;

			// Draw input background.
			float fWidth = 700.0f, fHeight = 20.0f;
			float fPad = 2.0f;
			g_pClient->GetGraphic()->DrawRectangle(fX, fY, fWidth, fHeight, 0xF8000000);
			g_pClient->GetGraphic()->DrawRectangle(fX + (fPad), fY + (fPad), (fWidth - (fPad*2)), (fHeight - (fPad*2)), 0x3CC0C0C0);

			fX += 4.0f;
			fY += 1.0f;
			/* Draw input shadow.
			SetRect(&rct, (LONG)fX+1, (LONG)fY, (LONG)fX, 0);
			m_Font->DrawText(NULL, szType.Get(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0)); 

			// Draw input shadow.
			SetRect(&rct, (LONG)fX-1, (LONG)fY, (LONG)fX, 0);
			m_Font->DrawText(NULL, szType.Get(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0)); 

			// Draw input shadow.
			SetRect(&rct, (LONG)fX, (LONG)fY+1, (LONG)fX, 0);
			m_Font->DrawText(NULL, szType.Get(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0)); 

			// Draw input shadow.
			SetRect(&rct, (LONG)fX, (LONG)fY-1, (LONG)fX, 0);
			m_Font->DrawText(NULL, szType.Get(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0)); */

			// Draw input
			SetRect(&rct, (LONG)fX, (LONG)fY, (LONG)fX, 0);
			m_Font->DrawText(NULL, szType.Get(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255)); 
		}
	}
}

void CChatbox::OnLostDevice()
{
	if(m_Font)
		m_Font->OnLostDevice();		
}

void CChatbox::OnResetDevice()
{
	if(m_Font)
		m_Font->OnResetDevice();
}

void CChatbox::AddDebugMessage(const char* szString, ...)
{
	char szBuffer[2048];
	va_list v_Args;
	va_start(v_Args, szString);
	vsnprintf ( szBuffer, sizeof(szBuffer), szString, v_Args );
	va_end(v_Args);
	AddChatMessage(szBuffer, 0xC0C0C0FF);
}

void CChatbox::AddChatMessage(const char* szString, DWORD dwColor)
{
	dwColor = (dwColor >> 8) | 0xFF000000;

	for ( int i = 0; i < 9; i ++ )
	{
		m_pLines[i]->dwColor = m_pLines[i+1]->dwColor;
		m_pLines[i]->dwPlayerColor = m_pLines[i+1]->dwPlayerColor;
		m_pLines[i]->iType = m_pLines[i+1]->iType;
		strcpy(m_pLines[i]->szMessage, m_pLines[i+1]->szMessage);
		strcpy(m_pLines[i]->szNick, m_pLines[i+1]->szNick);
	}

	strcpy(m_pLines[9]->szMessage, szString);
	m_pLines[9]->dwColor = dwColor;
	m_pLines[9]->iType = TYPE_MESSAGE;

	CLog::Printf("(Chat) %s", szString);
}

void CChatbox::AddPlayerMessage(int iPlayerId, const char *szString)
{
	//dwColor = (dwColor >> 8) | 0xFF000000;

	for ( int i = 0; i < 9; i ++ )
	{
		m_pLines[i]->dwColor = m_pLines[i+1]->dwColor;
		m_pLines[i]->dwPlayerColor = m_pLines[i+1]->dwPlayerColor;
		m_pLines[i]->iType = m_pLines[i+1]->iType;
		strcpy(m_pLines[i]->szMessage, m_pLines[i+1]->szMessage);
		strcpy(m_pLines[i]->szNick, m_pLines[i+1]->szNick);
	}

	CPlayer *pPlayer = g_pClient->GetNetworkManager()->GetPlayerManager()->GetAt(iPlayerId);

	if(pPlayer)
	{
		strcpy(m_pLines[9]->szNick, CString("%s: ", pPlayer->GetName().Get()));
		m_pLines[9]->dwPlayerColor = pPlayer->GetColor();
	} else {
		strcpy(m_pLines[9]->szNick, CString("%s: ", g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetName().Get()));
		m_pLines[9]->dwPlayerColor = g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetColor();
	}

	strcpy(m_pLines[9]->szMessage, szString);
	m_pLines[9]->dwColor = 0xFFFFFFFF;
	m_pLines[9]->iType = TYPE_CHAT_MESSAGE;

	CLog::Printf("(Chat %d) %s: %s", iPlayerId, m_pLines[9]->szNick, szString);
}

void CChatbox::AddChar(unsigned char ucChar)
{
	if(!m_bTypping) return;
	if(ucChar < ' ') return;
	int iCurBufferLen = strlen(szInputBuffer);
	if(iCurBufferLen < MAX_INPUT) 
	{ 
		szInputBuffer[iCurBufferLen] = ucChar;
		szInputBuffer[iCurBufferLen+1] = '\0';
	}
}

void CChatbox::ProcessInput()
{
	if(IsTypping())
	{
		if(strlen(szInputBuffer) > 0)
		{
			if(szInputBuffer[0] == '/')
			{
				// Proces komendy do CCommand
				if ( !m_pCommand->ProcessCommand ( szInputBuffer ) )
				{
					if(g_pClient->GetNetworkManager()->IsConnected())
					{
						RakNet::BitStream bitStream;
						bitStream.Write(szInputBuffer, 256);
						g_pClient->GetNetworkManager()->Call("Player_Command", &bitStream, HIGH_PRIORITY,RELIABLE, 0, TRUE);
					}
				}
			} else {
				if(g_pClient->GetNetworkManager()->IsConnected())
				{
					RakNet::BitStream bitStream;
					bitStream.Write(szInputBuffer, 256);
					g_pClient->GetNetworkManager()->Call("Player_Chat", &bitStream, HIGH_PRIORITY,RELIABLE, 0, TRUE);				
				} else {
					AddDebugMessage("Nie jesteœ pod³aczony/pod³¹czona do ¿adnego serwera!");
				}
			}
		}

		szInputBuffer[0] = '\0';
		Disable();
	}
}

void CChatbox::BackSpace()
{
	if(!IsTypping()) 
		return;

	int iCurBufferLen = strlen(szInputBuffer);
	if(iCurBufferLen > 0) {
		szInputBuffer[iCurBufferLen - 1] = '\0';
	}
}

void CChatbox::Disable()
{
	g_pClient->SetInputState(true);
	m_bTypping = false;
}

void CChatbox::Enable()
{
	m_iInputLines = 1;
	g_pClient->SetInputState(false);
	m_bTypping = true;
}