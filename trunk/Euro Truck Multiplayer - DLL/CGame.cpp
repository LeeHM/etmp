/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CGame.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CGame::CGame ( )
{
	//SetTime(12, 0);
	//SetMoney(1000);
	SetAudioVolume(1.0f);
	SetSFXVolume(1.0f);
}

CGame::~CGame ( )
{
	m_pCamera = new CCamera();

	if(!m_pCamera)
		return;
}

void CGame::SetAudioVolume(float fVolume)
{
	*(float *)FLOAT_AudioVolume = fVolume;
}

float CGame::GetAudioVolume()
{
	return *(float *)FLOAT_AudioVolume;
}

void CGame::SetSFXVolume(float fVolume)
{
	*(float *)FLOAT_SFXVolume = fVolume;
}

float CGame::GetSFXVolume()
{
	return *(float *)FLOAT_SFXVolume;
}

void CGame::SetTime(unsigned short usHour, unsigned short usMinute)
{
	CHookTools::UnProtect(DWORD_Hour, 1); 
	*(BYTE *)DWORD_Hour = (BYTE)usHour;
	CHookTools::UnProtect(DWORD_Minute, 1);
	*(BYTE *)DWORD_Minute = (BYTE)usMinute;
}

void CGame::GetTime(unsigned short* usHour, unsigned short* usMinute)
{
	// Bardzo zagmatwana sprawa z typami zmiennych
	// mo¿na by to zrobiæ inaczej?
	BYTE var;
	var = *(BYTE *)DWORD_Hour;
	usHour = (unsigned short *)var;
	var = *(BYTE *)DWORD_Minute;
	usMinute = (unsigned short *)var;
}

void CGame::SetMoney(int iMoney)
{
	CHookTools::UnProtect(DWORD_Money, 1);
	*(int *)DWORD_Money = iMoney;
}

int CGame::GetMoney()
{
	return *(int *)DWORD_Money;
}