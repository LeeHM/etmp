/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CResourceScript.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#include "CSquirrelArguments.h"

#define SCRIPT_CLIENT 0
#define SCRIPT_SERVER 1

struct ScriptClassMemberDecl 
{
	char * szFunctionName;
	SQFUNCTION sqFunc;
	int iParameterCount;
	char * szFunctionTemplate;
};

struct SquirrelClassDecl
{
	char * name;
	char * base;
	ScriptClassMemberDecl * members;
};

struct SquirrelArguments
{
	int iArgumentCount;
	SQObjectPtr * pArguments;
};

template <typename T>
static SQRESULT sq_setinstance(SQVM * pVM, T pInstance, int iIndex = 1)
{
	return sq_setinstanceup(pVM, iIndex, (SQUserPointer *)pInstance);
}

// Now a function
template <typename T>
static T sq_getinstance(SQVM * pVM, int iIndex = 1)
{
	SQUserPointer pInstance = NULL;

	if(SQ_FAILED(sq_getinstanceup(pVM, iIndex, &pInstance, NULL)))
		pInstance = NULL;

	return (T)pInstance;
}

#define _SET_RELEASE_HOOK(classname) \
	sq_setreleasehook(pVM, 1, __##classname##_releasehook);

#define _MEMBER_FUNCTION_IMPL(classname, name) \
	SQInteger __##classname##_##name(SQVM * pVM)

#define _MEMBER_FUNCTION_RELEASE_HOOK(classname) \
	SQInteger __##classname##_releasehook(SQUserPointer pInst, SQInteger size)

#define _BEGIN_CLASS(classname)  \
	SQInteger __##classname##__typeof(SQVM * pVM) \
	{ \
		sq_pushstring(pVM, #classname, -1); \
		return 1; \
	} \
	struct ScriptClassMemberDecl __##classname##_members[] = \
	{ \
		{ "_typeof", __##classname##__typeof },

#define _MEMBER_FUNCTION(classname, name, parametercount, functiontemplate) \
		{ #name, __##classname##_##name, parametercount, functiontemplate },

#define _END_CLASS(classname) \
		{ NULL, NULL } \
	}; \
	struct SquirrelClassDecl __##classname##_decl = \
		{  #classname, NULL, __##classname##_members }; 

#define _END_CLASS_BASE(classname, baseclassname) \
		{ NULL, NULL } \
	}; \
	struct SquirrelClassDecl __##classname##_decl = \
{  #classname, #baseclassname, __##classname##_members }; 

#define _CLASS_DECL(classname) \
	__##classname##_decl

class CResource;
bool Exists(const char * szPath);
class CResourceScript
{
private:
	SQVM			*m_pVM;
	CString			 m_strFile;
	int 			 m_iScriptType;
	CResource		*m_pResource;
public:
	CResourceScript ( CString strFile, int ScriptType, CResource *pResource );
	~CResourceScript ( );

	int		GetType ( ) { return m_iScriptType; }

	bool	CreateClass(SquirrelClassDecl * pClassDecl);
	void	RegisterFunction ( CString strFunction, SQFUNCTION sqFunction, int iParams = -1, CString strTemplate = NULL );
	void	RegisterVarible ( CString strName, CSquirrelArguments* pArguments );

	void	Call ( SQObjectPtr pFunction, CSquirrelArguments *pArguments, CSquirrelArguments *pReturn = NULL );

	SQVM	*GetVM ( ) { return m_pVM; }
};

// Natives

// Event natives
#include "Natives\CEventNatives.h"

// Player Natives
#include "Natives\CPlayerNatives.h"