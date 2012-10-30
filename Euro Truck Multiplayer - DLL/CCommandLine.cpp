/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - DLL
 * Licence    : GNU GPL v3
 * File       : CCommandLine.cpp
 * Description: Parser command line.
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

CCommandLine::CCommandLine()
{
	AddValue("nick", "Player");
	AddValue("host", "127.0.0.1");
	AddValue("port", "9999");
}

CCommandLine::~CCommandLine()
{

}

void CCommandLine::Parse(char *szCommandLine)
{
	while(*szCommandLine)
	{
		if(*szCommandLine != ' ')
		{
			if(*szCommandLine == '-')
			{
				szCommandLine++;

				CString strName;

				while(*szCommandLine && *szCommandLine != ' ')
				{
					strName += *szCommandLine;
					*szCommandLine++;
				}

				if(!(*szCommandLine))
					break;

				while(*szCommandLine && *szCommandLine == ' ')
				{
					szCommandLine++;
				}

				if(!(*szCommandLine))
					break;

				CString strValue;

				while(*szCommandLine && *szCommandLine != ' ')
				{
					strValue += *szCommandLine;
					*szCommandLine++;
				}

				AddValue(strName, strValue);

				if(!(*szCommandLine))
					break;
			}				
		}
		szCommandLine++;
	}
}

void CCommandLine::AddValue(CString strName, CString strValue)
{
	sCommandLine *pCommandLine = GetValue(strName);

	if(pCommandLine)
	{
		pCommandLine->strValue = strValue;
	} else {
		pCommandLine = new sCommandLine;
		pCommandLine->strName = strName;
		pCommandLine->strValue = strValue;

		m_CommandLines.push_back(pCommandLine);
	}
}

sCommandLine* CCommandLine::GetValue(CString strName)
{
	sCommandLine *pCommandLine = NULL;

	for(std::list<sCommandLine *>::iterator iter = m_CommandLines.begin();
		iter != m_CommandLines.end(); iter++)
	{
		if((*iter)->strName == strName)
		{
			pCommandLine = (*iter);
		}

	}
	return pCommandLine;
}