/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Shared
 * Licence    : GNU GPL v3
 * File       : CString.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

#include <string>
#include <stdarg.h>
#include <sstream>

#define BUFFER_SIZE 8192
#ifdef WIN32
#define stricmp _stricmp
#else
#define stricmp strcasecmp
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
inline char* itoa(int value, char* str, int radix);
#endif

class CString
{
private:
	std::string			m_szValue;
	size_t				m_sLimit;
	void				Init ( ) ;
public:
	CString(const char *szFormat, ...);
	CString();

	static const unsigned int nPos;
	operator const char * () const;

	void Set ( const char * szFormat );
	void Set ( const CString szString );

	void Format ( const char *szFormat, ... );

	std::string GetPointer ( );

	bool IsEmpty ( ) ;
	bool IsNotEmpty ( );

	const char * Get ( ) const;

	int Check (const char * szString) const;
	int Check (const CString szString) const;

	unsigned char operator [] (size_t sOffset) const;

	CString& operator = (const char * szString);
	CString& operator = (const CString strString);
	CString& operator = (const unsigned char ucChar);

	CString& operator += (const char * szString);
	CString& operator += (const CString strString);
	CString& operator += (const unsigned char ucChar);

	CString operator + (const char * szString) const;
	CString operator + (const CString strString) const;
	CString operator + (const unsigned char ucChar) const;

	bool operator == (const char * szString) const;
	bool operator == (const CString strString) const;

	bool operator != (const char * szString) const;
	bool operator != (const CString strString) const;

	bool operator > (const char * szString) const;
	bool operator > (const CString strString) const;

	bool operator >= (const char * szString) const;
	bool operator >= (const CString strString) const;

	bool operator < (const char * szString) const;
	bool operator < (const CString strString) const;

	bool operator <= (const char * szString) const;
	bool operator <= (const CString strString) const;

	// Funkcja pobieraj¹ca znak z tekstu
	unsigned char GetChar(size_t sOffset) const;

	bool LimitTruncate();

	// Funkcja pobieraj¹ca d³ugoœæ tekstu.
	size_t GetLength() const;

	// Funkcje do przeszukiwania tekstu.
	size_t Find(const char * szString, size_t sPos = 0) const;
	size_t Find(const unsigned char ucChar, size_t sPos = 0) const;
	size_t Find(const CString strString, size_t sPos = 0) const;

	// Funkcje do wycinania tekstu.
	CString CutStr(size_t sStart, size_t sStop) const;

	// Funkcje dodaj¹ce.
	void          Append(const char * szString);
	void          Append(const char * szString, unsigned int uiLength);
	void          Append(const CString strString);
	void          Append(const CString strString, unsigned int uiLength);
	void          AppendF(const char * szFormat, ...);
	void          Append(const unsigned char ucChar);

	CString&       ToLower();
};