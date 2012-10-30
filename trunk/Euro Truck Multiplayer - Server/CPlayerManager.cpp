/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPlayerManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer *g_pServer;
extern DWORD g_dwColors[32];

CPlayerManager::CPlayerManager()
{
	for(int i = 0; i < MAX_PLAYERS; i ++ )
	{
		m_pPlayers[i] = NULL;
		m_bSlotState[i] = NULL;
	}
}

CPlayerManager::~CPlayerManager()
{
	for(int i = 0; i < MAX_PLAYERS; i ++ )
	{
		Delete(i);
	}
}

bool CPlayerManager::New(int iPlayerId, char *szName)
{
	m_pPlayers[iPlayerId] = new CPlayer();

	if (m_pPlayers[iPlayerId])
	{
		m_pPlayers[iPlayerId]->SetId(iPlayerId);
		m_pPlayers[iPlayerId]->SetName(CString(szName));
		m_pPlayers[iPlayerId]->SetColor(g_dwColors[iPlayerId]);

		m_bSlotState[iPlayerId] = true;

		CLog::Printf("Gracz %s[%d] dolaczyl do serwera.", m_pPlayers[iPlayerId]->GetName().Get(), m_pPlayers[iPlayerId]->GetId());

		CSquirrelArguments args;
		args.push(iPlayerId);		
		g_pServer->GetResourceManager()->GetEventManager()->Call("onPlayerConnect", &args);

		RakNet::BitStream bsInfo;
		bsInfo.Write(iPlayerId);
		bsInfo.Write(m_pPlayers[iPlayerId]->GetColor());
		bsInfo.Write((int)strlen(g_pServer->GetVarValue("hostname").Get()));
		bsInfo.Write(const_cast<char*>(g_pServer->GetVarValue("hostname").Get()), 
			(int)strlen(g_pServer->GetVarValue("hostname").Get()));
		bsInfo.Write(atoi(g_pServer->GetVarValue("maxplayers").Get()));


		g_pServer->GetNetworkManager()->Call("Server_Info", &bsInfo, iPlayerId, HIGH_PRIORITY, RELIABLE, 0, false);

		AddPlayer(m_pPlayers[iPlayerId]->GetId());
		return true;
	}
	return false;
}

bool CPlayerManager::Delete(int iPlayerId)
{
	CPlayer *pPlayer = GetAt (iPlayerId);

	if(pPlayer)
	{
		CLog::Printf("Gracz %s[%d] opuscil serwer.", pPlayer->GetName().Get(), pPlayer->GetId());

		CSquirrelArguments args;
		args.push(iPlayerId);
		g_pServer->GetResourceManager()->GetEventManager()->Call("onPlayerDisconnect", &args);

		RemovePlayer(m_pPlayers[iPlayerId]->GetId());

		m_bSlotState[iPlayerId] = false;
		SAFE_DELETE(m_pPlayers[iPlayerId]);		
		return true;
	}
	return false;
}

void CPlayerManager::AddPlayer(int iPlayerId)
{
	CPlayer *pPlayer = GetAt(iPlayerId);
	
	if(pPlayer)
	{
		for(int i = 0; i < MAX_PLAYERS; i++)
		{
			if(m_bSlotState[i])
			{
				if(i != iPlayerId)
				{
					pPlayer->Add(i);
				}
				m_pPlayers[i]->Add(i);
			}
		}
	}
}

void CPlayerManager::RemovePlayer ( int iPlayerId )
{
	CPlayer *pPlayer = GetAt(iPlayerId);

	if(pPlayer)
	{
		for(int i = 0; i < MAX_PLAYERS; i++)
		{
			if(m_bSlotState[i])
			{
				if(i != iPlayerId)
				{
					pPlayer->Remove (i);
				}
				m_pPlayers[i]->Remove(i);
			}
		}
	}
}

CPlayer * CPlayerManager::GetAt ( int iPlayerId )
{
	if(m_bSlotState[iPlayerId])
		return m_pPlayers[iPlayerId];

	return NULL;
}

void CPlayerManager::Process()
{
	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		if(m_bSlotState[i])
		{
			m_pPlayers[i]->Process();
		}
	}
}