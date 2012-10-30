/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CResourceManager.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer * g_pServer;

CResourceManager::CResourceManager( const char * szDirectory )
{
	// Clear loaded stats varible.
	m_iLoaded		= NULL;
	m_iHaveError	= NULL;

	// Clear resources list.
	m_Resources.clear();

	// Set resources root directory.
	m_szDirectory.Set(szDirectory);

	// Create event manager instance.
	m_pEventManager = new CEventManager ( );

	// Register events.
	m_pEventManager->AddEvent ( "onServerStart", false );
	m_pEventManager->AddEvent ( "onServerStop", false );
	m_pEventManager->AddEvent ( "onResourceStart", false );
	m_pEventManager->AddEvent ( "onResourceStop", false );
	m_pEventManager->AddEvent ( "onResourceRestart", false );
	m_pEventManager->AddEvent ( "onPlayerConnect", false );
	m_pEventManager->AddEvent ( "onPlayerDisconnect", false );
	m_pEventManager->AddEvent ( "onPlayerChat", false );
	m_pEventManager->AddEvent ( "onPlayerCommand", false );
	m_pEventManager->AddEvent ( "onPlayerEvent", false );
	m_pEventManager->AddEvent ( "onPlayerKey", false );
}

CResourceManager::~CResourceManager()
{
	// Clear varibles with loading stats.
	m_iLoaded		= NULL;
	m_iHaveError	= NULL;
}

void CResourceManager::ParseConfig ( )
{
	// Get server.xml document pointer.
	TiXmlDocument m_document = g_pServer->GetConfigParser()->GetXMLDocument();

	// Define resource name pointer.
	CString	strName;

	// Loop for all nodes in server.xml
	for(TiXmlNode * m_node = m_document.RootElement()->FirstChildElement(); m_node; m_node = m_node->NextSibling())
	{
		// Check node name, if name is resoruce..
		if ( !strcmp(m_node->Value(), "resource") )
		{
			// If node isn't comment,
			if ( m_node->Type() != TiXmlNode::COMMENT)
			{
				// Attribution resource name to strName varible.
				strName.Set(m_node->ToElement()->Attribute("name"));
				
				// Check loading state.
				if(!Load(strName.Get()))
				{	
					// If loading failed add resource with error.
					m_iHaveError++;
				}

				// Add new resource to resources counter
				m_iLoaded++;				
			}
		} 
	}

	// Print to console loading stats.
	CLog::Printf("[Info] Loaded %d resources. (%d with error)", m_iLoaded, m_iHaveError);

	CSquirrelArguments pArguments;
	pArguments.push(const_cast<char*>(g_pServer->GetVarValue("hostname").Get()));
	g_pServer->GetResourceManager()->GetEventManager()->Call("onServerStart", &pArguments);
}

#include <sys/stat.h> 
bool Exists(const char * szPath)
{
	struct stat St;
	return (stat(szPath, &St) == 0);
}

bool CResourceManager::Load( const char *szName )
{
	// Check resource exists.
	if ( !Exists ( CString("%s\\%s", m_szDirectory.Get(), szName).Get() ) )
	{
		// Print if resource doesn't exists.
		CLog::Printf("[Resource] %s doesn't exists!", szName);
		return false;
	}

	// Create resource pointer.
	CResource * pResource = new CResource();

	// Set resources root directory.
	pResource->SetDirectory(m_szDirectory.Get());

	// Set resource name,
	pResource->SetName(szName);

	// Start resource,
	pResource->Start();

	// Check resource pointer.
	if ( pResource )
	{
		// Push to resources list,
		m_Resources.push_back(pResource);

		// Call onResourceStart ( resourcename ) event.
		CSquirrelArguments pArguments;
		pArguments.push(szName);
		g_pServer->GetResourceManager()->GetEventManager()->Call("onResourceStart", &pArguments);
		return true;
	}
	return false;
}

void CResourceManager::Unload( const char *szName)
{
	// Loop for Resources list.
	for ( std::list<CResource *>::iterator iter = m_Resources.begin(); iter != m_Resources.end(); iter ++ )
	{
		// Check resource name.
		if ( !(*iter)->GetName().Check(szName) )
		{
			// Call onResourceStop ( resourcename ) event.
			CSquirrelArguments pArguments;
			pArguments.push((*iter)->GetName().Get());
			g_pServer->GetResourceManager()->GetEventManager()->Call("onResourceStop", &pArguments);

			(*iter)->Stop();
		}
	}
}

void CResourceManager::Restart( const char *szName )
{
	// Loop for Resources list.
	for ( std::list<CResource *>::iterator iter = m_Resources.begin(); iter != m_Resources.end(); iter ++ )
	{
		// Check resource name.
		if ( !(*iter)->GetName().Check(szName) )
		{
			CSquirrelArguments pArguments;
			pArguments.push((*iter)->GetName().Get());
			g_pServer->GetResourceManager()->GetEventManager()->Call("onResourceRestart", &pArguments);

			(*iter)->Restart();
		}
	}
}


bool CResourceManager::RegisterEvent ( CString strName, SQObjectPtr pHandler, SQVM *pVM )
{
	return m_pEventManager->RegisterEvent(strName, pHandler, pVM);
}

void CResourceManager::AddEvent ( CString strName, bool bTriggerable )
{
	m_pEventManager->AddEvent ( strName, bTriggerable );
}

void CResourceManager::Call ( SQVM *pVM, SQObjectPtr pFunction, CSquirrelArguments *pArguments )
{
	for ( std::list<CResource *>::iterator iter = m_Resources.begin(); iter != m_Resources.end(); iter ++ )
	{
		(*iter)->Call(pVM, pFunction, pArguments);
	}
}

void CResourceManager::Call ( SQVM *pVM, CEventHandler *pEventHandler, CSquirrelArguments *pArguments )
{
	Call(pVM, pEventHandler->m_pFunction, pArguments);
}