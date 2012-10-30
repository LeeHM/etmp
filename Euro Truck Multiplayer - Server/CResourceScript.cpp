/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CResourceScript.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "StdInc.h"

extern CServer * g_pServer;

void PrintFunction(SQVM * pVM, const char * szFormat, ...)
{
	va_list args;
	char szBuffer[512];
	va_start(args, szFormat);
	vsnprintf(szBuffer, sizeof(szBuffer), szFormat, args);
	va_end(args);
	CLog::Printf(szBuffer);
}

void ErrorFunction(SQVM * pVM, const char * szFormat, ...)
{
	va_list args;
	char szBuffer[512];
	va_start(args, szFormat);
	vsnprintf(szBuffer, sizeof(szBuffer), szFormat, args);
	va_end(args);
	CLog::Printf(szBuffer);
}

void CompilerErrorFunction(SQVM * pVM, const char * szError, const char * szSource, int iLine, int iColumn)
{
	CLog::Printf ( "CompilerErrorFunction( 0x%x, %s, %s, %d, %d)", pVM, szError, szSource, iLine, iColumn );
}

/* Zmieniæ lokacje
bool Exists(const char * szPath)
{
	struct stat St;
	return (stat(szPath, &St) == 0);
}*/

CResourceScript::CResourceScript ( CString strFile, int ScriptType, CResource *pResource )
{
	// Warp some varibles.
	m_pResource = pResource;
	m_iScriptType = ScriptType;

	// Format script localization.
	m_strFile.Format("%s\\%s\\%s", m_pResource->GetDirectory().Get(), m_pResource->GetName().Get(), strFile.Get());

	// Check if file exists.
	if(!Exists(m_strFile.Get()))
	{
		CLog::Printf( "[Resources] Script %s not found!", m_strFile.Get() );
		return;
	}

	// Check script type - default server.
	if ( ScriptType == SCRIPT_CLIENT )
	{
		/*
			TODO:
				- Warp to code WebServ,
				- Create class for client resources,
				- ..
		*/
	} else {
		// Create root stack for script.
		m_pVM = sq_open(1024);

		//Register error and print functions.
		sqstd_seterrorhandlers(m_pVM);
		sq_setprintfunc(m_pVM, PrintFunction, ErrorFunction);
		sq_setcompilererrorhandler(m_pVM, CompilerErrorFunction);

		// Push root vm table.
		sq_pushroottable(m_pVM);

		// Register basic systems.
		sqstd_register_systemlib(m_pVM);
		sqstd_register_iolib(m_pVM);
		sqstd_register_bloblib(m_pVM);
		sqstd_register_mathlib(m_pVM);
		sqstd_register_stringlib(m_pVM);

		// Register Squirrel Classes
		m_pResource->RegisterClass(this);
		
		// Register all functions.

		// Event functions.
		CEventNatives::Register(this);

		// Funkcje gracza.
		CPlayerNatives::Register(this);

		if ( SQ_FAILED ( sqstd_dofile(m_pVM, m_strFile.Get(), SQFalse, SQTrue) ) )
		{
			// cannot compile script file.
			return;
		}

		// Define basic varibles.
		CSquirrelArguments pArgs;
		pArgs.push(MAX_PLAYERS);
		RegisterVarible ( "MAX_PLAYERS", &pArgs );
		pArgs.clear();
	}
}

CResourceScript::~CResourceScript ( )
{
	// Call sq_pop
	sq_pop(m_pVM, 1);

	// Free vm
	sq_close(m_pVM);
	delete m_pVM;
}

bool CResourceScript::CreateClass(SquirrelClassDecl * pClassDecl)
{
	// Get script VM Top
	int iTop = sq_gettop ( m_pVM );

	// Push class name.
	sq_pushstring ( m_pVM, pClassDecl->name, -1 );

	// Check class 
	if ( pClassDecl->base )
	{
		// Push class base name.
		sq_pushstring ( m_pVM, pClassDecl->base, -1 );

		// Check sq_get state.
		if(SQ_FAILED(sq_get(m_pVM, -3)))
		{
			// Set default top.
			sq_settop(m_pVM, iTop);
			return false;
		}
	}

	// Register class
	if ( SQ_FAILED ( sq_newclass ( m_pVM, pClassDecl->base ? 1 : 0 ) ) )
	{
		// If class register failed - back to top.
		sq_settop ( m_pVM, iTop );
		return false;
	}

	// Register class functions.
	const ScriptClassMemberDecl * pMembers = pClassDecl->members;

	for(int x = 0; pMembers[x].szFunctionName; x++)
		RegisterFunction(pMembers[x].szFunctionName, pMembers[x].sqFunc, pMembers[x].iParameterCount, 
			pMembers[x].szFunctionTemplate);

	// Register slot for class.
	sq_createslot(m_pVM, -3);
	return true;
}

void CResourceScript::RegisterFunction ( CString strFunction, SQFUNCTION sqFunction, int iParams, CString strTemplate )
{
	// Push function name.
	sq_pushstring ( m_pVM, strFunction.Get(), -1 );

	// Push function C++ handle,
	sq_newclosure ( m_pVM, sqFunction, 0 );

	// Make params / check.
	if ( iParams != -1 )
	{
		CString strParams;
		strParams.Format( ".%s", strTemplate.Get() );

		sq_setparamscheck ( m_pVM, (iParams+1), strParams.Get() );
	}

	// Create slot for function,
	sq_createslot ( m_pVM, -3 );
}

void CResourceScript::Call ( SQObjectPtr pFunction, CSquirrelArguments *pArguments, CSquirrelArguments *pReturn )
{
	// Get script vm top,
	int iTop = sq_gettop(m_pVM);

	// Default params value,
	int iParams = 1;

	// Check arguments,
	if ( pArguments )
	{
		// Push arguments to VM
		pArguments->toVM(m_pVM);

		// Add arguments to params number.
		iParams += pArguments->size();
	}

	// Return pointer.
	SQObjectPtr res;

	// Call function,
	if ( m_pVM->Call(pFunction, iParams, m_pVM->_top-iParams, res, true) )
	{
		if ( pReturn )
			pReturn->push(res);
	}

	// Set old top
	sq_settop(m_pVM, iTop);
}

void CResourceScript::RegisterVarible ( CString strName, CSquirrelArguments* pArguments )
{
	// Push varible name.
	sq_pushstring ( m_pVM, strName.Get(), -1 );

	// Push arguments.
	pArguments->toVM(m_pVM);

	// Create new slot for varible.
	sq_createslot ( m_pVM, -3 );
}