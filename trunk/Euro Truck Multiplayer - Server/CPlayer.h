/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPlayer.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CPlayer
{
private:
	int							m_iPlayerId;
	CString						m_strName;
	CVector3D					m_vecPosition;
	CVector3D					m_vecRotation;
	
	DWORD						m_dwColor;

	float						m_fChatboxX;
	float						m_fChatboxY;

	unsigned short				m_usHour;
	unsigned short				m_usMinute;
public:
	CPlayer();
	~CPlayer();

	void Process();
	void StoreSync(SyncData *pSyncData);

	inline void SetId ( int iPlayerId ) { m_iPlayerId = iPlayerId; }
	inline int GetId ( ) { return m_iPlayerId; }
	inline void SetName ( CString strName ) { m_strName = strName; }
	inline CString GetName() { return m_strName; }
	inline void SetColor(DWORD dwColor) { m_dwColor = dwColor; }
	inline DWORD GetColor() { return m_dwColor; }

	inline unsigned int GetPing();

	void Add ( int iPlayerId );
	void Remove ( int iPlayerId );

	void SetChatBoxPosition(float fX, float fY);
	void GetChatBoxPosition(float *fX, float *fY);

	void SetTime(unsigned short usHour, unsigned short usMinute);
	void GetTime(unsigned short *usHour, unsigned short *usMinute);
};