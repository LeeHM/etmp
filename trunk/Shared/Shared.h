/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Shared
 * Licence    : GNU GPL v3
 * File       : Shared.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#pragma once

#define				MAX_PLAYERS		 32
#define				MAX_PLAYER_NAME	 32

class CVector2D
{
public:
	float fX;
	float fY;

	CVector2D ()
	{
		fX = fY = 0.0f;
	}

	CVector2D ( float _fX, float _fY )
	{
		fX = _fX;
		fY = _fY;
	}
};

class CVector3D
{
public:
	float fX;
	float fY;
	float fZ;

	CVector3D ()
	{
		fX = fY = fZ = 0.0f;
	}

	CVector3D ( float _fX, float _fY, float _fZ )
	{
		fX = _fX;
		fY = _fY;
		fZ = _fZ;
	}
};

struct SyncData
{
	CVector3D vecPosition; // Pozycja,
	CVector3D vecRotation; // Rotacja,
	BYTE byteEngine; // Stan silnika,
	BYTE byteLights; // Stan œwiate³,
};