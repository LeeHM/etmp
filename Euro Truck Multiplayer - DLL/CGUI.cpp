/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CGUI.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>,
 *				LeNy <>
 *
 **********************************************************************/
#include "StdInc.h"
#include <direct.h>
extern CClient *g_pClient;

CGUI::CGUI(IDirect3DDevice9 *pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}

CGUI::~CGUI()
{
	for(std::list<CTexture *>::iterator iter = m_Textures.begin(); iter != m_Textures.end(); iter ++)
	{
		m_Textures.remove((*iter));
		delete (*iter);
	}
}

#include <sys/stat.h> 
bool Exists(const char * szPath)
{
	struct stat St;
	return (stat(szPath, &St) == 0);
}

CTexture *	CGUI::CreateTexture( const char*szPath )
{
	if(!Exists(szPath))
	{
		CLog::Printf("Nie mo¿na znaleŸæ tekstury o lokalizacji - %s", szPath);
		return NULL;
	}
	CTexture *pTexture = new CTexture(szPath, m_pD3DDevice);
	m_Textures.push_back(pTexture);
	return pTexture;
}

void CGUI::DeleteTexture ( CTexture *pTexture )
{
	for(std::list<CTexture *>::iterator iter = m_Textures.begin(); iter != m_Textures.end(); iter ++)
	{
		if((*iter) == pTexture)
		{
			m_Textures.remove((*iter));
			delete (*iter);
		}
	}
}

void CGUI::Render()
{
	for(std::list<CTexture *>::iterator iter = m_Textures.begin(); iter != m_Textures.end(); iter ++)
	{
		(*iter)->Draw();
	}
}

void CGUI::OnLostDevice()
{
	for(std::list<CTexture *>::iterator iter = m_Textures.begin(); iter != m_Textures.end(); iter ++)
	{
		(*iter)->OnLostDevice();
	}
}

void CGUI::OnResetDevice()
{
	for(std::list<CTexture *>::iterator iter = m_Textures.begin(); iter != m_Textures.end(); iter ++)
	{
		(*iter)->OnResetDevice();
	}
}

//Tekstury (Obrazki)
CTexture::CTexture ( const char *szPath, LPDIRECT3DDEVICE9 pD3DDevice )
{
	m_pD3DDevice = pD3DDevice;
	strcpy(m_szPath, szPath);

	D3DXCreateSprite ( m_pD3DDevice, &m_pSprite );

	D3DXCreateTextureFromFile ( m_pD3DDevice, szPath, &m_pTexture );
	m_pTexture->GetLevelDesc ( 0, &m_TexDesc );

	m_bShowed = true;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fScaleX = 0.0f;
	m_fScaleY = 0.0f;
	m_iAlpha = 255;
}

CTexture::~CTexture()
{
	OnLostDevice();
}

void CTexture::Draw ( )
{
	if ( m_bShowed )
	{
		D3DXVECTOR2 vTransformation = D3DXVECTOR2( m_fX, m_fY );

		D3DXVECTOR2 vScaling( ( 1.0f ), ( 1.0f ) );
		/*if(m_fWidth >= 0 && m_TexDesc.Width > 0) vScaling.x = vScaling.x*m_fWidth/m_TexDesc.Width;
		if(m_fHeight >= 0 && m_TexDesc.Height > 0) vScaling.y = vScaling.y*m_fHeight/m_TexDesc.Height;*/

		if(m_fWidth >= 0.0f && m_TexDesc.Width > 0) vScaling.x = vScaling.x*m_fWidth/m_TexDesc.Width;
		if(m_fHeight >= 0.0f && m_TexDesc.Height > 0) vScaling.y = vScaling.y*m_fHeight/m_TexDesc.Height;


		D3DXMATRIX mainMatrix;
	
		D3DXMatrixTransformation2D( &mainMatrix, 0, 0, &vScaling, 0, 0, &vTransformation );

		m_pSprite->SetTransform( &mainMatrix );

		DWORD dwColor = D3DCOLOR_ARGB ( m_iAlpha, 255, 255, 255 );

		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		m_pSprite->Draw( m_pTexture, 0, 0, 0, dwColor );
		m_pSprite->End();
	}
}

void CTexture::OnResetDevice ()
{
	m_pSprite->OnResetDevice();

	D3DXCreateTextureFromFile ( m_pD3DDevice, m_szPath, &m_pTexture );

	if(!m_pTexture)
	{
		return;
	}

	m_pTexture->GetLevelDesc(0, &m_TexDesc);
}

void CTexture::OnLostDevice ()
{
	m_pSprite->OnLostDevice();

	SAFE_RELEASE(m_pTexture);
}

void CTexture::ToggleVisible ( )
{
	if ( GetVisible () )  
	{ 
		SetVisible ( false ); 
	} else { 
		SetVisible ( true ); 
	}
}