/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : Main.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include "CLog.h"

#define SAFE_DELETE(d) if(d) { delete(d); (d)=NULL; }

#define PROJECT_NAME "Euro Truck Multiplayer"
#define PROJECT_STRING "Euro Truck Multiplayer Server"
#define PROJECT_WEBSITE ""
#define VERSION_STRING "Development Bulid ("__DATE__", "__TIME__")"
#define SERVER_VERSION_STRING PROJECT_NAME" "VERSION_STRING