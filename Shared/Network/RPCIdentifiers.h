#pragma once

typedef unsigned char RPCIdentifier;

enum eRPCIdentifers
{
	// Client
	RPC_AddPlayer,
	RPC_RemovePlayer,
	RPC_Client_Chat,

	//Server
	RPC_Server_Chat,
	RPC_Server_Command,
	RPC_Server_Connect
};