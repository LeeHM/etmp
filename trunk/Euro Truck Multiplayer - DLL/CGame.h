/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CGame.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

#ifdef _WIN32
	#ifdef GetMenuState
		#undef GetMenuState
	#endif
#endif

// Mem func
#define Padding(prefix, name, size) BYTE prefix##_##name##[size]

#include "CETSTruck.h"
#include "CETSCamera.h"

#include "CPlayerTruck.h"

class CGame
{
private:
	CCamera					*m_pCamera;
public:
							CGame  ( );
							~CGame ( );

	void					SetTime(unsigned short usHour, unsigned short usMinute);
	void					GetTime(unsigned short *usHour, unsigned short *usMinute);

	void					SetMoney(int iMoney);
	int						GetMoney();

	void					SetAudioVolume(float fVolume);
	float					GetAudioVolume();

	void					SetSFXVolume(float fVolume);
	float					GetSFXVolume();

	CCamera					*GetCamera() { return m_pCamera; }
};

// Nowe adresy pod ETS 1.3
#define FLOAT_SFXVolume			0x6041A4/*0x5D63F4*/
#define FLOAT_AudioVolume		0x6041A0/*0x5D63F0*/
#define DWORD_Hour				0x0
#define DWORD_Minute			0x0
#define DWORD_Money				0x0
/*
	Na hudzie czas:
	0x0CA925AF = %02d:%02d - size: 5
*/
//Funkcje zarz¹dzaj¹ce tirami w grze.
#define FUNC_CreateTruck			0x4C3700 
//0x4C3700(int this(nie znana operacja), int a2(uid tira), char a3(mo¿e model?))
#define FUNC_DestroyTruck			0x0
#define FUNC_ChangeTruckModel		0x4D5ED0

//int __cdecl gfx_set_rendering_device(int a1) - 0x00405C40