/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CResource.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer *g_pServer;

_MEMBER_FUNCTION_IMPL(TestClass, constructor)
{
	//sq_setinstance ( pVM, pInstance )
	//sq_getinstance<MyClass*>(pVM, pMyPointer)
	//CLog::Printf("Twoja pierwsza klasa.");
	return 1;
}

_MEMBER_FUNCTION_IMPL(TestClass, test)
{
	//sq_setinstance ( pVM, pInstance )
	//sq_getinstance<MyClass*>(pVM, pMyPointer)
	//CLog::Printf("Funkcja.");
	return 1;
}

// Test Class
_BEGIN_CLASS(TestClass)
_MEMBER_FUNCTION(TestClass, constructor, 0, NULL)
_MEMBER_FUNCTION(TestClass, test, 0, NULL)
_END_CLASS(TestClass)
// TextClass End

CResource::CResource ( )
{
	
}

CResource::~CResource ( )
{

}

void CResource::Start ( )
{
	CString szDir;
	szDir.Format("%s\\%s", m_szDirectory.Get(), m_szName.Get());

	// Parsowanie mety
	CString szMeta("%s\\meta.xml", szDir.Get());

	if(m_document.LoadFile(szMeta.Get()))
	{
		m_document.SetTabSize(4);
	}

	// Rejestracja klas
	CreateClass(&_CLASS_DECL(TestClass));

	// Pobieranie wszystkich skryptów z pliku meta.xml
	CString strName;
	CString strType;

	// Pêtla przeszukuj¹ca meta.xml
	//m_node->Type() != TiXmlNode::COMMENT && 

	for(TiXmlNode * m_node = m_document.RootElement()->FirstChildElement(); m_node; m_node = m_node->NextSibling())
	{
		if ( !strcmp(m_node->Value(), "script") )
		{
			// Przypisywanie atrybutu src do pointer'a.
			strName.Set(m_node->ToElement()->Attribute("src"));

			// Przypisywanie atrybutu type do pointer'a
			strType.Set(m_node->ToElement()->Attribute("type"));

			if ( strType.IsNotEmpty() && strName.IsNotEmpty() )
			{
				if ( !strType.Check("server") )
				{				
					CResourceScript *pResourceScript = new CResourceScript ( strName, 1, this );
					m_ResourceScript.push_back(pResourceScript); 
				} 
				else if ( !strType.Check("client") ) 
				{			
					CResourceScript *pResourceScript = new CResourceScript ( strName, 0, this );
					m_ResourceScript.push_back(pResourceScript);
				}
			}
		} 
		else	if ( !strcmp(m_node->Value(), "info") )
		{
			// Todo parse <info />
			/*
				Arguments:

					author
					version
					name
					type
					site
			*/
		}
	}

	m_document.SaveFile();
}

void CResource::Stop()
{
	for(std::list<CResourceScript *>::iterator iter = m_ResourceScript.begin(); iter != m_ResourceScript.end(); iter ++ )
	{
		m_ResourceScript.remove((*iter));
		delete (*iter);
	}

	m_ResourceScript.clear();
}

void CResource::Restart()
{
	Stop();
	//Mo¿e coœ nie trybiæ - ale raczej powinno byæ git :).
	Start();
}


void CResource::SetName ( const char *szName )
{
	m_szName.Set(szName);
}

void CResource::SetDirectory ( const char *szDirectory )
{
	m_szDirectory.Set(szDirectory);
}

CString CResource::GetName ( )
{
	return m_szName;
}

CString CResource::GetDirectory ( )
{
	return m_szDirectory;
}

void CResource::CreateClass(SquirrelClassDecl * pClassDecl)
{
	m_SQClass.push_back(pClassDecl);
}

void CResource::RegisterClass ( CResourceScript * pResourceScript )
{
	// Sprawdzamy czy skrypt jest server-side.
	if ( pResourceScript->GetType ( ) == SCRIPT_SERVER )
	{
		for ( std::list<SquirrelClassDecl *>::iterator viter = m_SQClass.begin(); viter != m_SQClass.end(); viter ++ )
		{
			// Je¿eli tak rejestrujemy klasê.
			pResourceScript->CreateClass((*viter));
		} 	
	}
}

void CResource::Call ( SQVM *pVM, SQObjectPtr pFunction, CSquirrelArguments *pArguments )
{
	for ( std::list<CResourceScript *>::iterator iter = m_ResourceScript.begin(); iter != m_ResourceScript.end(); iter ++ )
	{
		if ( (*iter)->GetVM() == pVM )
		{
			(*iter)->Call ( pFunction, pArguments );
		}
	}
}