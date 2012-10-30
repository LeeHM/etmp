/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CConfig.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

//extern CServer * g_pServer;

CConfig::CConfig(CString szConfigFileName)
{
	m_node = NULL;
	m_bInitialized = false;
	m_szConfigFileName.Set(szConfigFileName.Get());

	if(m_document.LoadFile(m_szConfigFileName.Get()))
	{
		m_document.SetTabSize(4);
		m_node = m_document.RootElement();
		m_bInitialized = true;
	}
}

CConfig::~CConfig()
{
	//m_pXML->save();
	//SAFE_DELETE(m_pXML);
}

CString CConfig::Get(CString szNodeName)
{
	if(!m_bInitialized) 
	{
		return NULL;
	}

	CString strValue;

	m_node = m_document.RootElement();
	if(m_node && m_node->FirstChild(szNodeName.Get()) != 0)
	{
		m_node = m_node->FirstChild(szNodeName.Get())->ToElement();
		if ( m_node && m_node->Type() != TiXmlNode::COMMENT )
		{
			strValue.Set ( m_node->GetText ( ) );
			return strValue;
		}
	}
	return NULL;
}