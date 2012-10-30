/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Client
 * Licence    : GNU GPL v3
 * File       : Main.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "Main.h"

#define				WINDOW_NAME "Euro Truck Multiplayer- Development Preview ("__DATE__", "__TIME__")"
#define				ID_LISTVIEW    1

LRESULT CALLBACK	WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	WindowProcess2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND				g_hwMainWindow = NULL;
HWND				g_hwQuickConnectWindow = NULL;
HWND				g_hwListView[2];
MSG					g_pMsg;
int					g_iNextFreeSlot = 0;

HWND				g_hwButtons[7];
HWND				g_hwEdit[10];
HWND				g_hwLabel[10];

char cAlphabet[24] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
	'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'x',
	'y', 'z'
};

struct sSelected
{
	char szHostName[256];
	int iPlayers;
	int iMaxPlayers;
	char szMapName [256];
};

int getSelected ( sSelected &selectedData )
{
	int iSelected = ListView_GetSelectionMark ( g_hwListView[0] );
	if ( iSelected  != -1 )
	{
		char szElement[256];
		ListView_GetItemText ( g_hwListView[0], iSelected, 0, szElement, 256 );
		sprintf(selectedData.szHostName, szElement );

		int iElement = NULL;
		ListView_GetItemText ( g_hwListView[0], iSelected, 1, szElement, 256 );
		sscanf(szElement, "%d/%d", &selectedData.iPlayers, &selectedData.iMaxPlayers );

		ListView_GetItemText ( g_hwListView[0], iSelected, 2, szElement, 256 );
		sprintf(selectedData.szMapName, szElement );
		return 1;
	}
	return NULL;
}

void addServer ( char *szHostName, int iPlayers, char *szMapName )
{
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	lvi.pszText = szHostName;
	lvi.iItem = g_iNextFreeSlot;
	lvi.iSubItem = 0;
	ListView_InsertItem( g_hwListView[0], & lvi );

	char szPlayers[40];
	sprintf(szPlayers, "%d/10", iPlayers );
	ListView_SetItemText ( g_hwListView[0], g_iNextFreeSlot, 1, szPlayers );
	ListView_SetItemText ( g_hwListView[0], g_iNextFreeSlot, 2, szMapName );

	g_iNextFreeSlot++;
}

void StartGame(char *szCommandLine, ...);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitCommonControls();

	// Definicja WNDCLASSEX
	WNDCLASSEX wc_Class;

	// Czyszcznie klasy okna.
	ZeroMemory ( &wc_Class, sizeof ( WNDCLASSEX ) );

	// Podstawowe ustawienia.
    wc_Class.cbSize = sizeof(WNDCLASSEX);
    wc_Class.style = CS_HREDRAW | CS_VREDRAW;
    wc_Class.lpfnWndProc = (WNDPROC)WindowProcess;
    wc_Class.hInstance = hInstance;
    wc_Class.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc_Class.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc_Class.lpszClassName = "WindowClass1";

	// Rejestracja klasy.
	RegisterClassEx(&wc_Class);
	
	// Tworzenie okna
	g_hwMainWindow = CreateWindowEx(NULL, "WindowClass1", WINDOW_NAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, GetSystemMetrics( SM_CXSCREEN )/2-320, GetSystemMetrics( SM_CYSCREEN )/2-200, 700, 400, NULL, NULL, hInstance, NULL);

	//HRGN hrZaokr = CreateRoundRectRgn( 0, 0, 700, 400, 20, 20 );
	//SetWindowRgn( g_hwMainWindow, hrZaokr, TRUE );
	// Elementy (button / listview )
	HFONT hFont = CreateFont(-11, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana");

	// Connect /refresh button.
	g_hwEdit[2] = CreateWindowEx( 0, "Edit", "Player", WS_CHILD | WS_VISIBLE, 380, 2, 150, 20, g_hwMainWindow, (HMENU)ID_LISTVIEW, hInstance, NULL );
	SendMessage(g_hwEdit[2], WM_SETFONT, (WPARAM) hFont, TRUE);
	HWND hwLabel = CreateWindowEx( 0, "Static", "Nick", WS_CHILD | WS_VISIBLE, 350, 4, 24, 20, g_hwMainWindow, (HMENU)ID_LISTVIEW, hInstance, NULL );
	
	SendMessage(hwLabel, WM_SETFONT, (WPARAM) hFont, TRUE);

	g_hwButtons[0] = CreateWindowEx( 0, "BUTTON", "Po³¹cz", WS_CHILD | WS_VISIBLE, 2, 2, 100, 20, g_hwMainWindow, (HMENU)ID_LISTVIEW, hInstance, NULL );
	g_hwButtons[1] = CreateWindowEx( 0, "BUTTON", "Odœwie¿", WS_CHILD | WS_VISIBLE, 102, 2, 100, 20, g_hwMainWindow, (HMENU)ID_LISTVIEW, hInstance, NULL );
	g_hwButtons[2] = CreateWindowEx( 0, "BUTTON", "Szybkie £¹czenie", WS_CHILD | WS_VISIBLE, 204, 2, 130, 20, g_hwMainWindow, (HMENU)ID_LISTVIEW, hInstance, NULL );
	SendMessage(g_hwButtons[0], WM_SETFONT, (WPARAM) hFont, TRUE);
	SendMessage(g_hwButtons[1], WM_SETFONT, (WPARAM) hFont, TRUE);
	SendMessage(g_hwButtons[2], WM_SETFONT, (WPARAM) hFont, TRUE);

	// List view.
	g_hwListView[0] = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 2, 40, 500, 250, g_hwMainWindow, (HMENU)ID_LISTVIEW, hInstance, NULL );
	ListView_SetExtendedListViewStyle( g_hwListView[0], LVS_EX_FULLROWSELECT );
	SendMessage(g_hwListView[0], WM_SETFONT, (WPARAM) hFont, TRUE);
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	// Server Name
	lvCol.iSubItem = 0;
	lvCol.cx = 300;
	lvCol.pszText = "Nazwa Serwera";
	ListView_InsertColumn ( g_hwListView[0], 0, &lvCol );

	// Players
	lvCol.iSubItem = 1;
	lvCol.cx = 80;
	lvCol.pszText = "Gracze";
	ListView_InsertColumn ( g_hwListView[0], 1, &lvCol );

	// Map
	lvCol.iSubItem = 2;
	lvCol.cx = 100;
	lvCol.pszText = "Nazwa Mapy";
	ListView_InsertColumn ( g_hwListView[0], 2, &lvCol );

	// Servers
	/*addServer ( "Hostname", 0, "Polska" );
	addServer ( "Mój serwer Euro Truck Multiplayer", 1, "Niemcy" );*/

	// List view.
	g_hwListView[1] = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 510, 40, 180, 250, g_hwMainWindow, (HMENU)ID_LISTVIEW, hInstance, NULL );
	ListView_SetExtendedListViewStyle( g_hwListView[1], LVS_EX_FULLROWSELECT );
	SendMessage(g_hwListView[1], WM_SETFONT, (WPARAM) hFont, TRUE);

	lvCol.iSubItem = 1;
	lvCol.cx = 100;
	lvCol.pszText = "Nick";
	ListView_InsertColumn ( g_hwListView[1], 0, &lvCol );

	lvCol.iSubItem = 2;
	lvCol.cx = 70;
	lvCol.pszText = "Punkty";
	ListView_InsertColumn ( g_hwListView[1], 1, &lvCol );

	// Pokazywanie okna.
	ShowWindow ( g_hwMainWindow, SW_SHOWNORMAL );

	//Tworzenie okna szybkie - ³¹czenie (Quick Connect)
	// Definicja WNDCLASSEX
	WNDCLASSEX wc_Class2;

	// Czyszcznie klasy okna.
	ZeroMemory ( &wc_Class2, sizeof ( WNDCLASSEX ) );

	// Podstawowe ustawienia.
    wc_Class2.cbSize = sizeof(WNDCLASSEX);
    wc_Class2.style = CS_HREDRAW | CS_VREDRAW;
    wc_Class2.lpfnWndProc = (WNDPROC)WindowProcess2;
    wc_Class2.hInstance = hInstance;
    wc_Class2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc_Class2.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc_Class2.lpszClassName = "WindowClass2";

	// Rejestracja klasy.
	RegisterClassEx(&wc_Class2);

	g_hwQuickConnectWindow = CreateWindowEx(NULL, "WindowClass2", "Szybkie po³¹czenie", WS_OVERLAPPED | WS_CAPTION /*| WS_SYSMENU*/, GetSystemMetrics( SM_CXSCREEN )/2-150, GetSystemMetrics( SM_CYSCREEN )/2-75, 300, 170, NULL, NULL, hInstance, NULL);

	g_hwLabel[0] = CreateWindowEx( 0, "Static", "Adres:", WS_CHILD | WS_VISIBLE, 20, 3, 250, 20, g_hwQuickConnectWindow, NULL, hInstance, NULL );
	SendMessage(g_hwLabel[0], WM_SETFONT, (WPARAM) hFont, TRUE);

	g_hwEdit[0] = CreateWindowEx( 0, "Edit", "127.0.0.1", WS_CHILD | WS_VISIBLE, 20, 20, 250, 20, g_hwQuickConnectWindow, NULL, hInstance, NULL );
	SendMessage(g_hwEdit[0], WM_SETFONT, (WPARAM) hFont, TRUE);

	g_hwLabel[1] = CreateWindowEx( 0, "Static", "Port:", WS_CHILD | WS_VISIBLE, 20, 43, 250, 20, g_hwQuickConnectWindow, NULL, hInstance, NULL );
	SendMessage(g_hwLabel[1], WM_SETFONT, (WPARAM) hFont, TRUE);

	g_hwEdit[1] = CreateWindowEx( 0, "Edit", "9999", WS_CHILD | WS_VISIBLE, 20, 60, 250, 20, g_hwQuickConnectWindow, NULL, hInstance, NULL );
	SendMessage(g_hwEdit[1], WM_SETFONT, (WPARAM) hFont, TRUE);

	g_hwButtons[4] = CreateWindowEx( 0, "Button", "Po³¹cz", WS_CHILD | WS_VISIBLE, 20, 90, 250, 20, g_hwQuickConnectWindow, NULL, hInstance, NULL );
	SendMessage(g_hwButtons[4], WM_SETFONT, (WPARAM) hFont, TRUE);
	
	g_hwButtons[5] = CreateWindowEx( 0, "Button", "Zamknij", WS_CHILD | WS_VISIBLE, 20, 110, 250, 20, g_hwQuickConnectWindow, NULL, hInstance, NULL );
	SendMessage(g_hwButtons[5], WM_SETFONT, (WPARAM) hFont, TRUE);

	// Pêtla g³ówna.
    while (GetMessage(&g_pMsg, NULL, 0, 0))
    {
        TranslateMessage(&g_pMsg);
        DispatchMessage(&g_pMsg);
    }

	return g_pMsg.wParam;
}

bool ValideNick(char *szNick)
{
	if(!strlen(szNick) || strlen(szNick) > 32) return false;
	while(*szNick)
	{
		if(*szNick == ' '  || *szNick == '%' || *szNick == '=')
			return false;

		*szNick++;
	}
	return true;
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
    {
    case WM_DESTROY:
        {
			PostQuitMessage(0);
			TerminateProcess(GetCurrentProcess(), 0);
            return 0;
        } break;

	case WM_COMMAND:
		{
			if ( (HWND)lParam == g_hwButtons[0] ) 
			{
				sSelected selectedData;
				if ( !getSelected(selectedData) )
				{
					MessageBox ( NULL, "Przed klikniêciem tego przycisku zaznacz serwer\nz którym chcesz siê po³¹czyæ.", "B³ad!", MB_ICONERROR );
				} else {
					char szMessage[256];
					sprintf(szMessage, "Serwer (%s / %d / %s) jest aktualnie offline!", selectedData.szHostName, selectedData.iPlayers, selectedData.szMapName);
					MessageBox ( NULL, szMessage, "B³ad!", MB_ICONERROR );
				}
			} else if ( (HWND)lParam == g_hwButtons[1] ) {
				ListView_DeleteAllItems(g_hwListView[0]);
				g_iNextFreeSlot = 0;
	
				// TODO
			} else if ( (HWND)lParam == g_hwButtons[2] ) {
				ShowWindow ( g_hwQuickConnectWindow , SW_SHOWNORMAL );
			}
		}break;
	}
    return DefWindowProc (hWnd, message, wParam, lParam);
}

LRESULT CALLBACK WindowProcess2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
    {
    case WM_DESTROY:
        {
			/*HWND hw = FindWindow("WindowClass2", "Szybkie po³¹czenie");
			if(hw)
			{
				ShowWindow(hw, SW_HIDE);
			}
			//MessageBox(NULL, "", "", NULL);
			PostQuitMessage(0);
			TerminateProcess(GetCurrentProcess(), 0);
			PostQuitMessage(0);*/
            return 0;
        } break;
	case WM_COMMAND:
		{
		if ( (HWND)lParam == g_hwButtons[4] ) {
				//char szMessage[256];

				DWORD dlugosc = GetWindowTextLength( g_hwEdit[0] );
				LPSTR szIp =( LPSTR ) GlobalAlloc( GPTR, dlugosc + 1 );
				GetWindowText( g_hwEdit[0], szIp, dlugosc + 1);

				DWORD dlugosc2 = GetWindowTextLength( g_hwEdit[1] );
				LPSTR szPort =( LPSTR ) GlobalAlloc( GPTR, dlugosc2 + 1 );
				GetWindowText( g_hwEdit[1], szPort, dlugosc2 + 1);
				
				DWORD dlugosc3 = GetWindowTextLength( g_hwEdit[2] );
				LPSTR szNick =( LPSTR ) GlobalAlloc( GPTR, dlugosc3 + 1 );
				GetWindowText( g_hwEdit[2], szNick, dlugosc3 + 1);

				if(ValideNick(szNick))
				{
					/*sprintf(szMessage, "Nick: %s\nIP: %s\nPort: %s", szNick, szIp, szPort );
					MessageBox(NULL, szMessage, "Próba", NULL);*/

					StartGame("-host %s -port %s -nick %s", szIp, szPort, szNick);
				} else {
					MessageBox(NULL, "WprowadŸ prawid³owy nick!", "Uwaga!", NULL);
				}
			} else if((HWND)lParam == g_hwButtons[5]) {
				ShowWindow ( g_hwQuickConnectWindow , SW_HIDE );
			}
		}break;
	}
    return DefWindowProc (hWnd, message, wParam, lParam);
}

#include <sys/stat.h> 
bool Exists(const char * szPath)
{
	struct stat St;
	return (stat(szPath, &St) == 0);
}

void StartGame(char *szCommandLine, ...)
{
	// Commandline
	char szParams[1024];
	va_list vaArgs;
	va_start(vaArgs, szCommandLine);
	vsprintf(szParams, szCommandLine, vaArgs);
	va_end(vaArgs);
	CString strCommandLine("\"game.exe\" %s", szParams);

	CString szGamePath;
	//szGamePath.Format(CUtils::GetFromRegistry(HKEY_LOCAL_MACHINE, "SOFTWARE\\EuroTruckMultiplayer", "GamePath"));
	CString szMPPath;
	szMPPath.Append("C:\\Development\\Release");
	szGamePath.Append("C:\\Development\\ETS");
	//szMPPath.Format(CUtils::GetFromRegistry(HKEY_LOCAL_MACHINE, "SOFTWARE\\EuroTruckMultiplayer", "MPPath"));

	/*if(szGamePath.IsEmpty())
	{
		MessageBox(NULL, "Could not find the game path in the registry!\nTry to reinstall applications and try again!", "Error!", MB_ICONERROR);
		return;
	}*/

	std::string strString;
	strString.append(szGamePath.Get());
	strString.append("|");
	strString.append(szMPPath.Get());

	MessageBoxA(NULL, strString.c_str(), "ErroR", MB_OK);

	// Inicjalizacja stringu z lokalizacj¹ pliku .exe gry.
	CString szAppPath("%s\\game.exe", szGamePath.Get());

	// Inicjalizacja stringu wraz z DLL'k¹ multiplayer'a.
	CString szDLLPath("%s\\Client\\Client.dll", szMPPath.Get());

	if(!Exists(szAppPath.Get()) || !Exists(szDLLPath.Get()))
	{
		MessageBox(NULL, "Podane lokalizacje nie s¹ prawid³owe!\nZainstaluj aplikacjê ponownie aby naprawiæ ten problem.", "Error!", MB_ICONERROR);
		return;
	}

	// Startowanie procesu game.exe
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	if(!CreateProcess(szAppPath.Get(), const_cast<char*>(strCommandLine.Get()), NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, szGamePath.Get(), &siStartupInfo, &piProcessInfo))
	{
		MessageBox(NULL, "Failed to start the process of the game!!\nTry to reinstall applications and try again!", "Error!", MB_ICONERROR);
		return;
	}

	if(!CUtils::InjectLibraryIntoProcess(piProcessInfo.hProcess, const_cast<char *>(szDLLPath.Get())))
	{
		MessageBox(NULL, "Nie mo¿na za³adowaæ pliku Client.dll do aplikacji, spróbuj przeinstalowaæ aplikacje.", "Error!", MB_ICONERROR);
		TerminateProcess(piProcessInfo.hProcess, 0);
		return;
	}

	// Wznowienie w¹tku w procesie game.exe
	ResumeThread(piProcessInfo.hThread);
}