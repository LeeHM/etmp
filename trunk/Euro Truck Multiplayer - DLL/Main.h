/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : Main.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
//#define DEBUG

// Soft macro defines.
#define		TOFLOAT(d) *(float*)(d)
#define		TO(a,f) *(a *)(f)
#define		SAFE_DELETE(d)	if(d) { delete(d); (d)=NULL; }
#define		SAFE_RELEASE( pInterface ) if( pInterface ) { pInterface->Release(); pInterface = 0; }
#define		MAX_STRING		256
#define		VERSION_STRING	"Euro Truck Multiplayer - Development Bulid ("__DATE__", "__TIME__")"
#define		SUB_PATH		"\\Euro Truck Multiplayer\\"