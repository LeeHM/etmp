/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CStatsGraph.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CStatsGraph
{
private:
	IDirect3DDevice9			* m_pD3DDevice;
	ID3DXFont					* m_Font;
public:
	CStatsGraph(IDirect3DDevice9 *pD3DDevice);
	~CStatsGraph();

	void Render();
};