/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPlayerManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include "CPlayer.h"

class CPlayerManager
{
private:
	CPlayer					*m_pPlayers[MAX_PLAYERS];
	bool					m_bSlotState[MAX_PLAYERS];
public:
	//std::list<CPlayer *>		m_Players;

	CPlayerManager();
	~CPlayerManager();

	bool New ( int iPlayerId, char *szName );
	bool Delete ( int iPlayerId );
	bool Exists ( int iPlayerId );

	void AddPlayer ( int iPlayerId );
	void RemovePlayer ( int iPlayerId );

	inline bool GetSlotState(int iPlayerId) { return m_bSlotState[iPlayerId]; }
	CPlayer * GetAt ( int iPlayerId );

	void Process ();
};