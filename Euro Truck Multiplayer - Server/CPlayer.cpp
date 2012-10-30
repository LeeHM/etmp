/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPlayer.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer *g_pServer;

DWORD g_dwColors[32] = {
	0xFF8400FF, 0x006600FF, 0x0066FFFF, 0x6600FFFF, 0x660099FF, 0x66CCFFFF,
	0x990000FF, 0x990066FF, 0x996600FF, 0xFFFF00FF, 0xFF99FFFF, 0x666666FF,
	0x989EC3FF, 0xB25900FF, 0x6B006BFF, 0xB2B300FF, 0xFFFF00FF, 0x809FFEFF,
	0x006B6BFF, 0xFECC80FF, 0xFE9980FF, 0xA10048FF, 0x47006BFF, 0xA2B31CFF,
	0x4C4E3EFF, 0x398F3EFF, 0x398F88FF, 0xCB8C8CFF, 0xC5CB8CFF, 0x7E8A16FF,
	0x726464FF, 0x30C723FF
};

CPlayer::CPlayer()
{
	m_iPlayerId = 0;
	m_vecPosition = CVector3D();

	//SetChatBoxPosition(40.0f, 30.0f);
	//SetTime(12, 00);
}

CPlayer::~CPlayer()
{

}

void CPlayer::Process()
{

}

void CPlayer::StoreSync(SyncData *pSyncData)
{
	// Ustalanie danych lokalnych.
	memcpy(&m_vecPosition, &pSyncData->vecPosition, sizeof(CVector3D));

	memcpy(&m_vecRotation, &pSyncData->vecRotation, sizeof(CVector3D));

	//CLog::Printf("[PLAYER_SYNC] [%d] X: %f Y: %f Z: %f", GetId(), m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ);

	// Przygotowywanie nowego bitStreamu do wys³ania.
	RakNet::BitStream bitStream;
	bitStream.WriteCompressed(GetId());
	bitStream.WriteCompressed(GetPing());
	bitStream.Write((char *)pSyncData, sizeof(SyncData));

	// Wysy³ pakietu Player_Sync do wszystkich graczy.
	g_pServer->GetNetworkManager()->Call("Player_Sync", &bitStream, -1, LOW_PRIORITY, UNRELIABLE_SEQUENCED, 0, true);
}

void CPlayer::Add ( int iPlayerId )
{
	RakNet::BitStream bitStream;
	bitStream.Write(m_iPlayerId);
	bitStream.Write(const_cast<char*>(m_strName.Get()), MAX_PLAYER_NAME);
	bitStream.Write(GetColor());
	
	g_pServer->GetNetworkManager()->Call("Player_Add", &bitStream, iPlayerId, HIGH_PRIORITY, RELIABLE, 0, true);
}

void CPlayer::Remove ( int iPlayerId )
{
	RakNet::BitStream bitStream;
	bitStream.Write(m_iPlayerId);

	g_pServer->GetNetworkManager()->Call("Player_Remove", &bitStream, iPlayerId, HIGH_PRIORITY, RELIABLE, 0, true);
}

unsigned int CPlayer::GetPing()
{
	return (unsigned int)g_pServer->GetNetworkManager()->GetRakPeer()->GetLastPing(g_pServer->GetNetworkManager()->GetPlayerAddress(GetId()));
}

//Funkcje skryptowe
void CPlayer::SetChatBoxPosition(float fX, float fY)
{
	m_fChatboxX = fX;
	m_fChatboxY = fY;

	RakNet::BitStream bitStream;

	bitStream.Write(fX);
	bitStream.Write(fY);

	g_pServer->GetNetworkManager()->Call("Script_SetChatBoxPositon", &bitStream, GetId(), HIGH_PRIORITY, RELIABLE, 0, true); // jak nie false xD
}

void CPlayer::GetChatBoxPosition(float *fX, float *fY)
{
	fX = &m_fChatboxX;
	fY = &m_fChatboxY;
}

void CPlayer::SetTime(unsigned short usHour, unsigned short usMinute)
{
	m_usHour = usHour;
	m_usMinute = usMinute;

	// Wysy³anie czasu do klienta.
	RakNet::BitStream bitStream;
	bitStream.Write(m_usHour);
	bitStream.Write(m_usMinute);
	g_pServer->GetNetworkManager()->Call("Script_SetTime", &bitStream, GetId(), HIGH_PRIORITY, RELIABLE, 0, true);
}

void CPlayer::GetTime(unsigned short *usHour, unsigned short *usMinute)
{
	usHour = &m_usHour;
	usMinute = &m_usMinute;
}