/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CPlayerNatives.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

//Fix for windows.
#ifdef SendMessage
	#undef SendMessage
#endif

class CPlayerNatives
{
public:
	static void Register ( CResourceScript *pResourceScript );

	static SQInteger GetName ( SQVM *pVM ); //getPlayerName(playerid)
	static SQInteger SendMessage (SQVM *pVM); //sendPlayerMessage(playerid, color, message)
	static SQInteger SendMessageToAll (SQVM *pVM); //sendMessageToAll(color, message)
	static SQInteger IsConnected (SQVM *pVM); //isPlayerConnected(playerid)
	static SQInteger GetPing(SQVM *pVM); //getPlayerPing(playerid)
	static SQInteger SetChatBoxPos(SQVM *pVM); //setChatBoxPosition(playerid, x, y)
	static SQInteger GetChatBoxPos(SQVM *pVM); //getChatBoxPosition(playerid)
};