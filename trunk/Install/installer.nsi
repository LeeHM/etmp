; inc
!include "MUI2.nsh"
!include MUI.nsh
!include nsDialogs.nsh
!include Sections.nsh
!include WinVer.nsh

; define project name and revision
!define NAME 'Euro Truck Multiplayer'
;!define REVISON '17'
!define VERSION '0.1' ;Only in stable release.

; Set outfile name & Generate full name

;!define FULL_NAME "${NAME} r${REVISON}"
;OutFile "installers/rev/ETMP-rev-${REVISON}-client.exe"

OutFile "installers/full/ETMP-${VERSION}.exe"
!define FULL_NAME '${NAME} ${VERSION}'
Name "${FULL_NAME}"

; insall info
SetCompressor /SOLID lzma
CRCCheck force
BrandingText /TRIMCENTER "${FULL_NAME} Setup"
ShowInstDetails show
ShowUninstDetails show
RequestExecutionLevel admin

; install macros
Var GAME_DIR

!insertmacro MUI_PAGE_WELCOME

InstallDir "$PROGRAMFILES\ET-MP"
!define MUI_DIRECTORYPAGE_VARIABLE				$INSTDIR
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_PAGE_HEADER_TEXT					"Wybierz lokalizacjê Euro Truck Simulator"
;!define MUI_PAGE_HEADER_SUBTEXT					""
!define MUI_DIRECTORYPAGE_TEXT_TOP				"Wybierz lokalizacjê Euro Truck Simulator$\n$\nPo wybraniu kliknij zainstaluj aby zainstalowaæ Euro Truck Multiplayer."
!define MUI_DIRECTORYPAGE_VARIABLE				$GAME_DIR
!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "Polish"

; Init section
Function .onInit	
	strcpy $GAME_DIR "$PROGRAMFILES\Euro Truck Simulator"
FunctionEnd
	
; Install section
Section "Install" SecDummy
	SetOverwrite on
	
	; Files
	SetOutPath "$INSTDIR"	
	File "..\Release\Client\Euro Truck Multiplayer.exe"
	
	SetOutPath "$INSTDIR\Euro Truck Multiplayer"
	File "..\Release\Client\Client.dll"
	
	; Short cuts
	CreateShortCut "$DESKTOP\Euro Truck Multiplayer.lnk" "$INSTDIR\Euro Truck Multiplayer.exe"
	
	; Uninstaller
	WriteUninstaller "$INSTDIR\Odinstaluj ${FULL_NAME}.exe"
	
	;Rejestr
	WriteRegStr HKEY_LOCAL_MACHINE "Software\${NAME}" "MPPath" "$INSTDIR"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\${NAME}" "GamePath" "$GAME_DIR"
SectionEnd

; Uninstall section
Section Uninstall
	; Clear Registry
	DeleteRegKey HKEY_LOCAL_MACHINE "Software\${NAME}"
	
	; Delete files
	Delete "$INSTDIR\Euro Truck Multiplayer.exe"
	Delete "$INSTDIR\Euro Truck Multiplayer\Client.dll"
	Delete "$INSTDIR\Euro Truck Multiplayer\client.log"
	
	; Delete shortcut
	Delete "$DESKTOP\Euro Truck Multiplayer.lnk"
	
	; Delete uninstall exe
	Delete "$INSTDIR\Odinstaluj ${FULL_NAME}.exe"
	
	; Delete directory
	RMDir "$INSTDIR\Euro Truck Multiplayer\"
	RMDir "$INSTDIR"
	
SectionEnd