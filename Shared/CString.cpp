/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Vendor
 * Licence    : GNU GPL v3
 * File       : CString.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 **********************************************************************/
#include "CString.h"

const unsigned int CString::nPos = (unsigned int)-1;

CString::CString(const char *szFormat, ...)
{
	Init();

	if ( szFormat )
	{
		char szBuffer[BUFFER_SIZE];
		va_list vList;
		va_start ( vList, szFormat );
		vsnprintf ( szBuffer, sizeof(szBuffer), szFormat, vList );
		va_end ( vList );
	
		Set ( szBuffer );
	}
}

CString::CString() 
{ 
	Init();
}

void CString::Init ( )
{
	m_sLimit = nPos;
}

void CString::Set ( const char * szFormat )
{
	if(szFormat)
	{
		// Przypisywanie stringu
		m_szValue.assign ( szFormat );

		//
		LimitTruncate();
	}
}

void CString::Set ( const CString szString )
{
	// Przypisywanie stringu
	m_szValue.assign ( szString.Get() );

	// 
	LimitTruncate();
}

void CString::Format ( const char *szFormat, ... )
{
	char *szBuffer = new char [ 2048 ];

	va_list vaArgs;
	va_start(vaArgs, szFormat);
	vsprintf(szBuffer, szFormat, vaArgs);
	va_end(vaArgs);

	Set ( szBuffer );
}

std::string CString::GetPointer ( )
{
	return m_szValue;
}

bool CString::IsEmpty ( ) 
{
	return m_szValue.empty();
}

bool CString::IsNotEmpty ( )
{
	return !m_szValue.empty();
}

const char * CString::Get ( ) const
{ 
	return m_szValue.c_str(); 
}

int CString::Check (const char * szString) const
{
	return strcmp(m_szValue.c_str(), szString);
}

int CString::Check (const CString szString) const
{
	return strcmp(m_szValue.c_str(), szString.Get());
}

CString::operator const char * () const
{
	return m_szValue.c_str();
}

CString& CString::operator = (const char * szString)
{
	Set(szString);
	return *this;
}

CString& CString::operator = (const CString strString)
{
	Set(strString.Get());
	return *this;
}

CString& CString::operator = (const unsigned char ucChar)
{
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';
	Set(szString);
	return *this;
}

CString& CString::operator += (const char * szString)
{
	Append(szString);
	return *this;
}

CString& CString::operator += (const CString strString)
{
	Append(strString.Get());
	return *this;
}

CString& CString::operator += (const unsigned char ucChar)
{
	Append(ucChar);
	return *this;
}

CString CString::operator + (const char * szString) const
{
	CString strNewString(*this);
	strNewString.Append(szString);
	return strNewString;
}

CString CString::operator + (const CString strString) const
{
	CString strNewString(*this);
	strNewString.Append(strString.Get());
	return strNewString;
}

CString CString::operator + (const unsigned char ucChar) const
{
	CString strNewString(*this);
	strNewString.Append(ucChar);
	return strNewString;
}

unsigned char CString::operator [] (size_t sOffset) const
{
	return GetChar(sOffset);
}

bool CString::operator == (const char * szString) const
{
	return (Check(szString) == 0);
}

bool CString::operator == (const CString strString) const
{
	return (Check(strString.Get()) == 0);
}

bool CString::operator != (const char * szString) const
{
	return (Check(szString) != 0);
}

bool CString::operator != (const CString strString) const
{
	return (Check(strString.Get()) != 0);
}

bool CString::operator > (const char * szString) const
{
	return (Check(szString) > 0);
}

bool CString::operator > (const CString strString) const
{
	return (Check(strString.Get()) > 0);
}

bool CString::operator >= (const char * szString) const
{
	return (Check(szString) >= 0);
}

bool CString::operator >= (const CString strString) const
{
	return (Check(strString.Get()) >= 0);
}

bool CString::operator < (const char * szString) const
{
	return (Check(szString) < 0);
}

bool CString::operator < (const CString strString) const
{
	return (Check(strString.Get()) < 0);
}

bool CString::operator <= (const char * szString) const
{
	return (Check(szString) <= 0);
}

bool CString::operator <= (const CString strString) const
{
	return (Check(strString.Get()) <= 0);
}

unsigned char CString::GetChar(size_t sOffset) const
{
	if(sOffset < GetLength())
	{
		return m_szValue[sOffset];
	}
	return 0;
}

bool CString::LimitTruncate()
{
	if(m_sLimit > nPos && GetLength() > m_sLimit)
	{
		m_szValue[m_sLimit] = '\0';
		return true;
	}
	return false;
}

size_t CString::GetLength() const
{
	return m_szValue.size();
}

size_t CString::Find(const char * szString, size_t sPos) const
{
	return m_szValue.find(szString, sPos);
}

size_t CString::Find(const unsigned char ucChar, size_t sPos) const
{
	return m_szValue.find(ucChar, sPos);
}

size_t CString::Find(const CString strString, size_t sPos) const
{
	return m_szValue.find(strString.Get(), sPos);
}

CString	CString::CutStr(size_t sStart, size_t sStop) const
{
	return CString(m_szValue.substr(sStart, sStop).c_str());
}	

void CString::Append(const char * szString)
{
	if(szString)
	{
		m_szValue.append(szString);
		LimitTruncate();
	}
}

void CString::Append(const char * szString, unsigned int uiLength)
{
	if(szString)
	{
		unsigned int uiStringLength = strlen(szString);

		if(uiLength > uiStringLength)
			uiLength = uiStringLength;

		m_szValue.append(szString, uiLength);

		LimitTruncate();
	}
}

void CString::Append(const CString strString)
{
	m_szValue.append(strString.Get());
	LimitTruncate();
}

void CString::Append(const CString strString, unsigned int uiLength)
{
	if(uiLength > strString.GetLength())
		uiLength = strString.GetLength();

	m_szValue.append(strString.Get(), uiLength);

	LimitTruncate();
}

void CString::AppendF(const char * szFormat, ...)
{
	if(szFormat)
	{
		char szString[BUFFER_SIZE];
		va_list vaArgs;
		va_start(vaArgs, szFormat);
		vsprintf_s(szString, sizeof(szString), szFormat, vaArgs);
		va_end(vaArgs);

		m_szValue.append(szString);

		LimitTruncate();
	}
}

void CString::Append(const unsigned char ucChar)
{
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';

	m_szValue.append(szString);

	LimitTruncate();
}
CString& CString::ToLower()
{
	for(size_t i = 0; i < GetLength(); i++)
		m_szValue[i] = tolower(m_szValue[i]);

	return *this;
}