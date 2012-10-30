/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CResource.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include "CResourceScript.h"

class CResource
{
private:
	std::list<SquirrelClassDecl *>  m_SQClass;
	std::list<CResourceScript *>	m_ResourceScript;
	CString							m_szName;
	CString							m_szDirectory;
	TiXmlDocument					m_document;
public:
	CResource();
	~CResource();

	void Start();
	void Stop();
	void Restart();

	void SetDirectory	( const char *szDirectory	);
	void SetName		( const char *szName		);

	CString GetDirectory ( );
	CString	GetName ( );

	// Squirrel functions
	void CreateClass(SquirrelClassDecl * pClassDecl);

	void RegisterClass ( CResourceScript * pResourceScript );

	void Call ( SQVM *pVM, SQObjectPtr pFunction, CSquirrelArguments *pArguments );
};
