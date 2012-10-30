/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CCommandLine.h
 * Description: Parser command line.
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

struct sCommandLine
{
	CString			strName;
	CString			strValue;
};

class CCommandLine
{
private:
	std::list<sCommandLine*>	m_CommandLines;
public:
	CCommandLine();
	~CCommandLine();

	void Parse(char *szCommandLine);

	void AddValue(CString strName, CString strValue);
	sCommandLine *GetValue(CString strName);
};