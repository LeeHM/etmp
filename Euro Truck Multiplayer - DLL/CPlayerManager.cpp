/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayerManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#include "StdInc.h"

CPlayerManager::CPlayerManager()
{
	m_pLocalPlayer = new CLocalPlayer();
}

CPlayerManager::~CPlayerManager()
{
	for(int i = 0; i < MAX_PLAYERS; i ++)
	{
		Delete(i);
	}
	delete m_pLocalPlayer;
}

bool CPlayerManager::New(int iPlayerId, char *szName, DWORD dwColor)
{
	CPlayer *pPlayer = GetAt(iPlayerId);
	if(pPlayer)
	{
		CLog::Printf("[Warning] Slot %d nie by³ wolny. Trwa czyszczenie.", iPlayerId);
		Delete(iPlayerId);
	}

	CLog::Printf("[HARD] pPlayer = new CPlayer(%d, %s);", iPlayerId, szName);
	m_pPlayers[iPlayerId] = new CPlayer();

	if(m_pPlayers[iPlayerId])
	{	
		m_pPlayers[iPlayerId]->SetId(iPlayerId);
		m_pPlayers[iPlayerId]->SetName(CString(szName));
		m_pPlayers[iPlayerId]->SetColor(dwColor);
		m_bSlotState[iPlayerId] = true;

		CLog::Printf("[Info] Gracz %d zosta³ dodany.", iPlayerId);
		//m_Players.push_back(pPlayer);
		return true;
	}
	return false;
}

bool CPlayerManager::Delete(int iPlayerId)
{
	if(GetAt(iPlayerId))
	{
		m_bSlotState[iPlayerId] = false;
		SAFE_DELETE(m_pPlayers[iPlayerId]);
		return true;
	}
	return false;
}

int CPlayerManager::GetPlayersCount()
{
	int iNum = 1;
	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		if(GetSlotState(i))
			iNum++;
	}
	return iNum;
}

CPlayer * CPlayerManager::GetAt ( int iPlayerId )
{
	if(m_bSlotState[iPlayerId])
		return m_pPlayers[iPlayerId];
	return NULL;
}

void CPlayerManager::Process()
{
	m_pLocalPlayer->Process();

	for(int i = 0; i < MAX_PLAYERS; i ++ )
	{
		if(m_bSlotState[i])
			m_pPlayers[i]->Process();
	}
}