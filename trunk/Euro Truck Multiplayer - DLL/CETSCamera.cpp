/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CETSCamera.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CCamera::CCamera(unsigned int uiCameraHandler)
{
	if(uiCameraHandler)
	{
		m_uiCameraHandler = uiCameraHandler;
	} else
		m_uiCameraHandler = NULL;

	m_bEnabled = true;

	*m_camera = *(ETSCamera *)(0x614CA8);

	if(!IsHandled())
	{
		CHookTools::UnProtect(0x614CAC, 4);
		CHookTools::UnProtect(0x614CB0, 4);
		CHookTools::UnProtect(0x614CB4, 4);
	}
}

CCamera::~CCamera()
{
	m_bEnabled = false;
}

void CCamera::GetPosition(CVector3D *vecPosition)
{
	if(!IsHandled())
	{
		vecPosition->fX = *(float *)0x614CAC;
		vecPosition->fY = *(float *)0x614CB0;
		vecPosition->fZ = *(float *)0x614CB4;
	}
}

void CCamera::SetPosition(CVector3D *vecPosition)
{
	if(!IsHandled())
	{
		*(float *)0x614CAC = vecPosition->fX;
		*(float *)0x614CB0 = vecPosition->fY;
		*(float *)0x614CB4 = vecPosition->fZ;
	}
}


void CCamera::GetRotation(CVector3D *vecRotation)
{

}

void CCamera::SetRotation(CVector3D *vecRotation)
{
	
}