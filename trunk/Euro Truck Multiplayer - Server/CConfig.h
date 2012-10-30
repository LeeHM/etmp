/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CConfig.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CConfig
{
private:
	CString m_szConfigFileName;
	TiXmlDocument m_document;
	TiXmlElement * m_node;
	bool			m_bInitialized;
public:
	CConfig(CString szConfigFileName);
	~CConfig();

	CString Get(CString szNodeName);

	TiXmlDocument GetXMLDocument()  { return m_document; }
	TiXmlElement *GetNode()			{ return m_node; }
};
