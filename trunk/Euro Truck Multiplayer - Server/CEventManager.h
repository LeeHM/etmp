/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CEventManager.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CEventHandler 
{
public:
	SQObjectPtr		   m_pFunction;
	SQVM			   *m_pVM;
	CString				m_strName;

	CEventHandler ( CString strName, SQObjectPtr pFunction, SQVM *pVM )
	{
		m_strName = strName;
		m_pFunction = pFunction;
		m_pVM = pVM;
	}
};

class CEvent
{
public:
	CString				m_strName;
	bool				m_bTriggerable;

	CEvent ( CString strName, bool bTriggerable )
	{
		m_strName = strName;
		m_bTriggerable = bTriggerable;
	}
};

class CEventManager
{
public:
	std::list<CEventHandler *>  m_EventHandler;
	std::list<CEvent *>			m_Event;

	CEventManager ( )
	{
		m_EventHandler.clear();
	}

	bool RegisterEvent ( CString strName, SQObjectPtr pHandler, SQVM *pVM )
	{
		for ( std::list<CEvent *>::iterator iter = m_Event.begin(); iter != m_Event.end(); iter ++ )
		{
			if ( (*iter)->m_strName == strName )
			{
				CEventHandler * pEventHandler = new CEventHandler ( strName, pHandler, pVM );
				m_EventHandler.push_back(pEventHandler);
				return true;
			}
		}
		return false;
	}

	void AddEvent ( CString strName, bool bTriggelable )
	{
		CEvent * pEvent = new CEvent ( strName, bTriggelable );
		m_Event.push_back ( pEvent );
	}

	void Call ( CString strName, CSquirrelArguments *pArguments = NULL );
};