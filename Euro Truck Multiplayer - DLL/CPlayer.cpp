/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayer.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#include "StdInc.h"

extern CClient *g_pClient;

CPlayer::CPlayer()
{
	// Domyœlny kolor.
	m_dwColor = 0xFF5E00FF;

	m_uiPing = NULL;
	m_vecPosition = CVector3D();
	m_vecRotation = CVector3D();
}

CPlayer::~CPlayer()
{

}

void CPlayer::Process(){}

void CPlayer::StoreSync(SyncData *pSyncData)
{
	memcpy(&m_vecPosition, &pSyncData->vecPosition, sizeof(CVector3D));
	memcpy(&m_vecRotation, &pSyncData->vecRotation, sizeof(CVector3D));
}

unsigned int CPlayer::GetPing()
{
	return m_uiPing;
}