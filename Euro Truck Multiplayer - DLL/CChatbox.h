/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CChatbox.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

enum eType
{
	TYPE_MESSAGE,
	TYPE_CHAT_MESSAGE
};

struct SChatLine
{
	char		szMessage[256];
	char		szNick[MAX_PLAYER_NAME+2];
	DWORD		dwColor;
	DWORD		dwPlayerColor;
	int			iType;
};

#define MAX_INPUT 96
#define SAY_PERFIX "Say: "

class CChatbox
{
private:
	CCommand		   *m_pCommand;
	IDirect3DDevice9   *m_pD3DDevice;
	SChatLine			*m_pLines[10];
	ID3DXFont		    *m_Font;
	bool			    m_bShowed;
	bool				m_bTypping;
	CHAR				szInputBuffer[MAX_INPUT];
	int					m_iInputLines;

	float				m_fX;
	float				m_fY;
public:
	CChatbox(IDirect3DDevice9 *pD3DDevice);
	~CChatbox();

	void DrawLine(int i, float fX, float fY);
	void Render();
	void AddChatMessage(const char* szString, DWORD dwColor);
	void AddDebugMessage(const char*szString, ...);
	void AddPlayerMessage(int iPlayerId, const char*szString);
	void OnLostDevice();
	void OnResetDevice();
	void AddChar(unsigned char ucChar);
	
	void Disable();
	void Enable();
	void ProcessInput();
	void BackSpace();
	inline bool IsTypping()						{ return m_bTypping; }
	inline void SetVisible ( bool bVisible )	{m_bShowed=bVisible;}
	inline bool GetVisible ( )					{ return m_bShowed; }

	inline void SetPosition(float fX, float fY) { m_fX = fX; m_fY = fY; }
	inline void GetPosition(float fX, float fY) { fX = m_fX; fY = m_fY; }
};