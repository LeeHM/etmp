/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : Input.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

bool WndHook();
LRESULT APIENTRY WindowProcess( HWND hwnd,UINT uMsg, WPARAM wParam,LPARAM lParam );
BOOL HandleKeyPress(DWORD vKey);
BOOL HandleCharacterInput(DWORD dwChar);