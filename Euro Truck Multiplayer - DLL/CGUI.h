/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CGUI.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>,
 *				LeNy <>
 *
 **********************************************************************/
#pragma once

//Elements
class CTexture;

class CGUI
{
private:
	IDirect3DDevice9	   *m_pD3DDevice;

	//Elementy
	std::list<CTexture *>   m_Textures;
public:
	CGUI(IDirect3DDevice9 *pD3DDevice);
	~CGUI();
	
	void					Render();
	void					OnLostDevice();
	void					OnResetDevice();

	CTexture *				CreateTexture( const char*szPath );
	void					DeleteTexture ( CTexture *pTexture );
};

//Elementy

//Tekstury
class CTexture
{
private:
	IDirect3DTexture9	    *m_pTexture;
	D3DSURFACE_DESC			m_TexDesc;
	ID3DXSprite			    *m_pSprite;
	IDirect3DDevice9		* m_pD3DDevice;
	float					m_fX;
	float					m_fY;
	float					m_fWidth;
	float					m_fHeight;
	float					m_fScaleX;
	float					m_fScaleY;
	bool					m_bShowed;
	int						m_iAlpha;
	char					m_szPath[256];
public:
	CTexture ( const char *szPath, IDirect3DDevice9 * pD3DDevice );
	~CTexture ( );

	void Draw ( );
	void OnLostDevice ();
	void OnResetDevice ( );

	inline void SetPosition ( float fX, float fY ) { m_fX = fX; m_fY = fY; }
	inline void SetSize ( float fWidth, float fHeight ) { m_fWidth = fWidth; m_fHeight = fHeight; }
	inline void SetScale ( float fScaleX, float fScaleY ) { m_fScaleX = fScaleX; m_fScaleY = fScaleY; }
	inline void SetVisible ( bool bShowed ) { m_bShowed = bShowed; }
	inline bool GetVisible ( ) { return m_bShowed; }
	inline void SetAlpha ( int iAlpha ) { if ( iAlpha > 255 ) { m_iAlpha = 255; } else if ( iAlpha < 0 ) { m_iAlpha = 0; } else { m_iAlpha = iAlpha; } }
	inline int GetAlpha ( ) { return m_iAlpha; }
	void		ToggleVisible ( );
};