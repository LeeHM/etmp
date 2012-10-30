/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CPlayerTruck.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#define DWORD_Scania 0x0

class CPlayerTruck
{
private:
	CETSTruck		*pTruck;
public:
	CPlayerTruck ( );
	~CPlayerTruck ( );

	void Create ( );
	void Destroy ( );
	void SetTruckModel ( DWORD dwModelIndex );
};