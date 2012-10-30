/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayerTruck.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CPlayerTruck::CPlayerTruck (){}
CPlayerTruck::~CPlayerTruck (){}

void CPlayerTruck::Create ( )
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	DWORD dwModel = 0x2C3F8A90;
	DWORD dwFunc = FUNC_CreateTruck;

	_asm
	{
		push 0
		push 1
		push dwModel
		mov ecx, pTruck
		call dwFunc
	}
}

void CPlayerTruck::Destroy ( )
{
	DWORD dwFunc = FUNC_DestroyTruck;
	_asm
	{
		//push pTruck
		call dwFunc
	}
}

void CPlayerTruck::SetTruckModel ( DWORD dwModelIndex )
{
	DWORD dwFunc = FUNC_ChangeTruckModel;
	_asm
	{
		push dwModelIndex
		push pTruck
		push 0
		call dwFunc
	}
}