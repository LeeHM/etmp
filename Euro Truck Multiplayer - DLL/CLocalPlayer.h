/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CLocalPlayer.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once

class CLocalPlayer /*: public CETSTruck*/
{
private:
	CVector3D					m_vecPosition;
	CVector3D					m_vecRotation;
	CString						m_strName;
	int							m_iPlayerId;
	DWORD						m_dwColor;
	bool						m_bSpawned;
public:
								CLocalPlayer();
								~CLocalPlayer();

	void						Process();

	inline void					SetName(CString strName) { m_strName.Set(strName); }
	inline CString				GetName() { return m_strName; }
	inline void					SetId(int iPlayerId) { m_iPlayerId = iPlayerId; }
	inline int					GetId() { return m_iPlayerId; }
	inline void					SetColor(DWORD dwColor) { m_dwColor = dwColor; }
	inline DWORD				GetColor() { return m_dwColor; }

	void						SetPosition(CVector3D *vecPosition);
	CVector3D					*GetPosition();
	void						GetPosition(CVector3D  *vecPosition);
	void						SetRotation(CVector3D *vecRotation);
	CVector3D					*GetRotation();
	void						GetRotation(CVector3D  *vecRotation);

	unsigned int				GetPing();
};