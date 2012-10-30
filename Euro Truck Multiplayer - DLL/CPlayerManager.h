/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayerManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once
#include "CPlayer.h"
#include "CLocalPlayer.h"

class CPlayerManager
{
private:
	//std::list<CPlayer *>		m_Players;
	CPlayer						*m_pPlayers[MAX_PLAYERS];
	bool						m_bSlotState[MAX_PLAYERS];

	CLocalPlayer				*m_pLocalPlayer;
public:
								CPlayerManager();
								~CPlayerManager();

	int							GetPlayersCount();
	bool						New(int iPlayerid, char *szName, DWORD dwColor);
	bool						Delete(int iPlayerId);
	CPlayer *					GetAt ( int iPlayerId );
	bool						GetSlotState(int iPlayerId) { return m_bSlotState[iPlayerId]; }

	void						Process();

	inline CLocalPlayer			*GetLocalPlayer() { return m_pLocalPlayer; }
};
