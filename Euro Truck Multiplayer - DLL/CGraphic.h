/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CGraphic.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include "CStatsGraph.h"

#define FT_NONE		0x0
#define FT_CENTER	0x1
#define FT_BORDER	0x2
#define FT_VCENTER	0x4
#define FT_SINGLELINE 0x8

class CGraphic
{
private:
	IDirect3DDevice9			* m_pD3DDevice;
	ID3DXSprite					* m_pDXSprite;
	IDirect3DTexture9			* m_pDXPixelTexture;
	ID3DXFont					* m_Font;
	CGUI						* m_pGUI;
	CStatsGraph					* m_pStatsGraph;
	bool						m_bHidden;
public:
	// Kostruktor oraz destruktor
	CGraphic ( IDirect3DDevice9 * pD3DDevice );
	~CGraphic ( );

	// Inne funkcje
	void						Render			( );
	void						OnLostDevice	( );
	void						OnResetDevice	( );

	// Funkcje rysuj¹ce
	void						DrawRectangle ( float fX, float fY, float fWidth, float fHeight, unsigned long ulColor ) ;
	void						Fade(bool bFade);
	bool						Fade();

	// Funkcje inline
	inline IDirect3DDevice9	*	GetD3DDevice	( ) { return m_pD3DDevice; }
	inline CGUI					*GetGUI			( ) { return m_pGUI; }

	bool						WindowProcess( HWND hwnd,UINT uMsg, WPARAM wParam,LPARAM lParam ) ;

	float						GetScreenWidth();
	float						GetScreenHeight();
};