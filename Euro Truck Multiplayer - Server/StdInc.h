/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : StdInc.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#define SERVER

// RakNet 
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakNetTypes.h>
#include <RPC4Plugin.h>

// Default includes
#include <iostream>
#include <list>
#include <map>
#include <locale.h>

#if defined _WIN32
	#include <windows.h>
	#include <sys/stat.h>
#else
	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
#endif
#include <stdarg.h>
#include <sstream>
#include <time.h>
#include <assert.h>

// Squirrel
#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdaux.h>
#include <sqstdblob.h>
#include <sqstdio.h>
#include <sqstdsystem.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstate.h>
#include <sqvm.h>

// Network
#include <network/CRPCManager.h>

// Tiny XML
#include "ticpp.h"
#include "tinyxml.h"

// Includy Multiplayer'a
#include "Main.h"
#include <Shared.h>
#include <CString.h>
#include "CCommandSystem.h"
#include "CConfig.h"
#include "CPacketManager.h"
#include "CPlayerManager.h"
#include "CQuery.h"
#include "CNetworkManager.h"
#include "CPlayer.h"
#include "CServer.h"
#include "CLog.h"

// Scripting
#include "CSquirrelArguments.h"
#include "CEventManager.h"
#include "CResource.h"
#include "CResourceScript.h"
#include "CResourceManager.h"