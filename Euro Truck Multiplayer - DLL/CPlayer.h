/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayer.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once

class CPlayer
{
private:
	int					m_iPlayerId;
	CString				m_strName;
	CPlayerTruck		*m_pTruck;
	DWORD				m_dwColor;

	unsigned int		m_uiPing;
	CVector3D			m_vecPosition;
	CVector3D			m_vecRotation;
public:
	CPlayer();
	~CPlayer();

	void				Process();
	void				StoreSync(SyncData *pSyncData);

	inline void			SetId ( int iPlayerId ) { m_iPlayerId = iPlayerId; }
	inline int			GetId() { return m_iPlayerId; }
	inline void			SetName( CString strName ) { m_strName = strName; }
	inline CString		GetName() { return m_strName; }	
	inline DWORD		GetColor() { return m_dwColor; }
	inline void			SetColor(DWORD dwColor) { m_dwColor = dwColor; }

	unsigned int		GetPing();
	void				SetPing(unsigned int uiPing) { m_uiPing = uiPing; }
};