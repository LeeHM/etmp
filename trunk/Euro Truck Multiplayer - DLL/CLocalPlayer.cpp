/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CLocalPlayer.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#include "StdInc.h"

extern CClient *g_pClient;

CLocalPlayer::CLocalPlayer()
{
	m_vecPosition = CVector3D();
	m_vecRotation = CVector3D();
	m_iPlayerId = 0;
	m_dwColor = 0xFF5E00FF;
	m_bSpawned = true;
}

CLocalPlayer::~CLocalPlayer()
{

}

void CLocalPlayer::Process()
{
	//Wysy³anie synchronizacji do serwera ^^.
	if(m_bSpawned)
	{
		SyncData syncData;

		GetPosition(&syncData.vecPosition);

		GetRotation(&syncData.vecRotation);

		RakNet::BitStream bsSync;
		bsSync.Write((char*)&syncData, sizeof(SyncData));

		g_pClient->GetNetworkManager()->Call("Player_Sync", &bsSync, HIGH_PRIORITY, RELIABLE, 0, true);
	}
}

void CLocalPlayer::SetPosition(CVector3D *vecPosition)
{

}

CVector3D *CLocalPlayer::GetPosition()
{
	return &CVector3D(TOFLOAT(0x614CAC), TOFLOAT(0x614CB0), TOFLOAT(0x614CB4));
}

void CLocalPlayer::GetPosition(CVector3D *vecPosition)
{
	vecPosition->fX = TOFLOAT(g_pClient->GetBaseAddress()+0x614CAC);
	vecPosition->fY = TOFLOAT(g_pClient->GetBaseAddress()+0x614CB0);
	vecPosition->fZ = TOFLOAT(g_pClient->GetBaseAddress()+0x614CB4);
}

void CLocalPlayer::SetRotation(CVector3D *vecRotation)
{

}

CVector3D * CLocalPlayer::GetRotation()
{

}

void CLocalPlayer::GetRotation(CVector3D *vecRotation)
{
	memcpy(vecRotation, &m_vecRotation, sizeof(CVector3D));
}

unsigned int CLocalPlayer::GetPing()
{
	return (unsigned int)g_pClient->GetNetworkManager()->GetRakPeer()->GetLastPing(g_pClient->GetNetworkManager()->GetServerManager()->GetSystemAddress());
}