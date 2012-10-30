/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CETSCamera.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

// 
/*
.data:00614CAC dword_614CAC    dd 0                    ; DATA XREF: sub_401B90+6r
.data:00614CAC                                         ; snd_listener+8w ...
.data:00614CB0 dword_614CB0    dd 0                    ; DATA XREF: sub_401B90+1Ar
.data:00614CB0                                         ; snd_listener+11w
.data:00614CB4 dword_614CB4    dd 0                    ; DATA XREF: sub_401B90+2Fr
.data:00614CB4                                         ; snd_listener+1Aw

.data:00614CB8 dword_614CB8    dd 0                    ; DATA XREF: snd_listener+23w
.data:00614CBC dword_614CBC    dd 0                    ; DATA XREF: snd_listener+2Cw
.data:00614CC0 dword_614CC0    dd 0                    ; DATA XREF: snd_listener+39w
.data:00614CC4 dword_614CC4    dd 0                    ; DATA XREF: snd_listener+42w
.data:00614CC8 dword_614CC8    dd 0                    ; DATA XREF: snd_listener+49w
.data:00614CCC dword_614CCC    dd 0                    ; DATA XREF: snd_listener+52w
.data:00614CD0 dword_614CD0    dd 0                    ; DATA XREF: snd_listener+5Aw

*/

class ETSCamera //0x614CA8
{
public:
	float fX;
	float fY;
	float fZ;
	BYTE pad1[55];
};

class CCamera
{
public:
	unsigned int				m_uiCameraHandler;
	bool						m_bEnabled;
	ETSCamera				* 	m_camera;
public:
								CCamera(unsigned int uiCameraHandler = NULL);
								~CCamera();

	void						GetPosition(CVector3D *vecPosition);
	void						SetPosition(CVector3D *vecPosition);

	void						GetRotation(CVector3D *vecRotation);
	void						SetRotation(CVector3D *vecRotation);


	bool						IsHandled() { return (m_uiCameraHandler != NULL); }
};