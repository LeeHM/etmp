/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : StdInc.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

//DEBUG STATE (NO!)
//#define DEBUG

// RakNet 
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakNetTypes.h>
#include <RPC4Plugin.h>

/* Default */
#include <Windows.h>
#include <Windowsx.h>
#include <string.h>
#include <direct.h>
#include <tlhelp32.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <list>
#include <detours.h>

#ifndef _WIN32
	#define MAX_PATH PATH_MAX
#endif

// Network
#include <network/CRPCManager.h>

/* DirectX */
#include <d3d9.h>
#include "../Vendor/DXSDK/Include/d3dx9.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "CDirectInputDevice8Proxy.h"
#include "CDirectInputHook8.h"
#include "CDirectInputHook.h"

/* Other */
#include "Main.h"
#include <Shared.h>

/* Classes */
#include <CString.h>
#include <CThread.h>

#include "CExceptionHandler.h"
#include "CGame.h"
#include "CCommandLine.h"
#include "Input.h"
#include "CDirect3D9Hook.h"
#include "IDirect3D9Hook.h"
#include "IDirect3DDevice.h"
#include "CGUI.h"
#include "CGraphic.h"
#include "CCommand.h"
#include "CChatbox.h"
#include "CPlayerManager.h"
#include "CPacketManager.h"
#include "CServerManager.h"
#include "CNetworkManager.h"
#include "CHooks.h"
#include "CClient.h"
#include "CDebug.h"
#include "CLog.h"
#include "CUtils.h"