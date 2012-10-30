/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CStatsGraph.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CClient *g_pClient;

CStatsGraph::CStatsGraph(IDirect3DDevice9 *pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	D3DXCreateFont(m_pD3DDevice, 13, 0, NULL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &m_Font );
}

CStatsGraph::~CStatsGraph()
{

}

void CStatsGraph::Render()
{
	CVector3D vecPosition;
	g_pClient->GetNetworkManager()->GetPlayerManager()->GetLocalPlayer()->GetPosition(&vecPosition);

	g_pClient->GetGraphic()->DrawRectangle(0.0f, 300.0f, 200.0f, 200.0f, 0x3C000000);
	RECT rct;
	SetRect(&rct, (LONG)10.0f, (LONG)310.0f, 0, 0);
	/*Kamera*/
	m_Font->DrawText(NULL, CString("Float#1: %f,\nFloat #2: %f,\nFloat #3: %f,\nCzas: %d", 
		TO(float, 0x61E214),
		TO(float, 0x61E204),
		TO(float, 0x61E238),
		TO(int, 0x5A36E4)
		).Get(), -1, &rct,DT_NOCLIP, 0xFFFFFFFF);

	/*
.data:00614CB8 dword_614CB8    dd 0                    ; DATA XREF: snd_listener+23w
.data:00614CBC dword_614CBC    dd 0                    ; DATA XREF: snd_listener+2Cw
.data:00614CC0 dword_614CC0    dd 0                    ; DATA XREF: snd_listener+39w
.data:00614CC4 dword_614CC4    dd 0                    ; DATA XREF: snd_listener+42w
.data:00614CC8 dword_614CC8    dd 0                    ; DATA XREF: snd_listener+49w
.data:00614CCC dword_614CCC    dd 0                    ; DATA XREF: snd_listener+52w
.data:00614CD0 dword_614CD0    dd 0                    ; DATA XREF: snd_listener+5Aw
	*/
}
