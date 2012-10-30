/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CServer.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include <CThread.h>
#include "CResource.h"
#include "CResourceManager.h"


#ifdef _WIN32
void InputProcess ( PVOID args );
#else
void InputProcess ( void *args );
#endif

class Vars
{
private:
	CString m_szName;
	CString m_szValue;
public:
	Vars(CString szName, CString szValue)
	{
		m_szName = szName;
		m_szValue = szValue;
	}

	CString GetName ( ) 
	{
		return m_szName;
	}

	CString GetValue ( ) 
	{
		return m_szValue;
	}

	void SetValue (CString szValue) 
	{
		m_szValue = szValue;
	}
};

class CServer
{
private:
	CConfig						*m_pConfig;
	CNetworkManager				*m_pNetworkManager;
	CCommandSystem				*m_pCommandSystem;
	CResourceManager			*m_pResourceManager;
	CThread						*m_pInputThread;
	bool						 m_bInitialized;
public:
	CServer( );
	~CServer( );

	bool Load ( );

	// Varsy :)
	std::list<Vars *> m_siVar;
	bool SetVarValue(CString szName, CString szValue)
	{
		bool bExists = false;

		Vars * pVars = NULL;
		std::list<Vars *>::iterator iter;
		for(iter = m_siVar.begin(); iter != m_siVar.end(); ++ iter )
		{
			if( (*iter)->GetName() == szName )
			{
				pVars = (*iter);
				bExists = true;
			}
		}

		if(bExists)
		{
			pVars->SetValue(szValue);
			return true;
		} else {
			Vars * pVars = new Vars(szName, szValue);
			m_siVar.push_back(pVars);
			return true;
		}
		return false;
	}

	bool VarExists(CString szName)
	{
		bool bExists = false;
		std::list<Vars *>::iterator iter;
		for(iter = m_siVar.begin(); iter != m_siVar.end(); ++ iter )
		{
			if( (*iter)->GetName() == szName )
			{
				bExists = true;
			}
		}

		if(bExists)
		{
			return true;
		}
		return false;
	}

	CString GetVarValue(CString szName)
	{
		for(std::list<Vars *>::iterator iter = m_siVar.begin(); iter != m_siVar.end(); ++ iter )
		{
			if((*iter)->GetName() == szName)
			{
				return (*iter)->GetValue( );
			}
		}
		return NULL;
	}

	bool DeleteVar(CString szName)
	{
		Vars * pVars = NULL;

		for(std::list<Vars *>::iterator iter = m_siVar.begin(); iter != m_siVar.end(); ++ iter )
		{
			if((*iter)->GetName() == szName)
			{
				pVars = (*iter);
			}
		}

		if(pVars)
		{
			m_siVar.remove(pVars);
			delete(pVars);
			return true;
		}
		return false;
	}

	CConfig				*	GetConfigParser    ( ) { return m_pConfig;			}
	CNetworkManager		*	GetNetworkManager  ( ) { return m_pNetworkManager;  }
	CCommandSystem		*	GetCommandSystem   ( ) { return m_pCommandSystem;   }
	CResourceManager	*	GetResourceManager ( ) { return m_pResourceManager; }
};