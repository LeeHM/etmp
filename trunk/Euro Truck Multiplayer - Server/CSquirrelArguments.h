/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CSquirrelArguments.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once

class CSquirrelArgument
{
public:
	SQObjectType type;

	union {
		int i;
		bool b;
		float f;
		char * sz;
		CString *str;
		SQObject sqObject;
		SQObjectPtr *pObjPtr;
		SQInstance * pInstance;
	} data;

	void Set ( int i )
	{
		data.i = i;
		type = OT_INTEGER;
	}

	void Set ( SQObject pObj )
	{
		data.sqObject = pObj;
		type = OT_CLOSURE;
	}

	void Set ( bool b )
	{
		data.b = b;
		type = OT_BOOL;
	}

	void Set ( float f )
	{
		data.f = f;
		type = OT_FLOAT;
	}

	void Set ( CString* str )
	{
		//data.sz = sz;
		data.str = str;
		type = OT_STRING;
	}

	void Set ( SQInstance * pInstance )
	{
		data.pInstance = pInstance;
		type = OT_INSTANCE;
	}

	void Set ( )
	{
		type = OT_NULL;
	}
};

class CSquirrelArguments
{
private:
	std::list<CSquirrelArgument *>  m_SquirrelArguments;
public:
	CSquirrelArguments ( )
	{
		//
		m_SquirrelArguments.clear();
	}

	void clear ( )
	{
		// Loop for all arguments list elements and delete.
		for ( std::list<CSquirrelArgument *>::iterator iter = m_SquirrelArguments.begin(); iter != m_SquirrelArguments.end(); iter ++ )
			delete *iter;

		m_SquirrelArguments.clear();
	}

	void push ( int i ) // int
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(i);

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	void push ( bool b ) // bool
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(b);

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	void push ( float f ) // float
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(f);

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	void push ( char *sz ) // char
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(new CString(sz));

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	void push ( const char *sz ) // const char
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(new CString(sz));

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	void push () // NULL
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set();

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	void fromBitStream ( RakNet::BitStream *pBitStream )
	{
		bool b = true;
		SQObjectType type;
		pBitStream->Read(type);
		while ( b == false )
		{		
			switch ( type )
			{
				case OT_INTEGER:
					{
						int i = 0;
						pBitStream->Read(i);
						push(i);
						break;
					}
				case OT_STRING:
					{
						CString *str;
						pBitStream->Read(str);
						push(const_cast<char*>(str->Get()));
						break;
					}	
				case OT_FLOAT:
					{
						float f;
						pBitStream->Read(f);
						push(f);
						break;
					}
				case OT_BOOL:
					{
						bool b;
						pBitStream->Read(b);
						push(b);
						break;
					}
				case OT_NULL:
					{
						push();						
						break;
					}
				default:
					{
						b=false;
						break;
					}
		
			}
		}
	}

	void toBitStream ( RakNet::BitStream * pBitStream )
	{
		for ( std::list<CSquirrelArgument *>::iterator iter = m_SquirrelArguments.begin(); iter !=  m_SquirrelArguments.end(); iter ++ )
		{
			switch ( (*iter)->type )
			{
			case OT_INTEGER:
				{
					pBitStream->Write(OT_INTEGER);
					pBitStream->Write((*iter)->data.i);
					break;
				}
			case OT_INSTANCE:
				{
					pBitStream->Write(OT_INSTANCE);
					pBitStream->Write((*iter)->data.pInstance);
					break;
				}
			case OT_STRING:
				{
					pBitStream->Write(OT_STRING);
					pBitStream->Write((*iter)->data.str);
					break;
				}
			case OT_FLOAT:
				{
					pBitStream->Write(OT_FLOAT);
					pBitStream->Write((*iter)->data.f );
					break;
				}
			case OT_BOOL:
				{
					pBitStream->Write(OT_BOOL);
					pBitStream->Write((*iter)->data.b);
					break;
				}
			case OT_NULL:
				{
					pBitStream->Write(OT_NULL);
					pBitStream->Write0();
					break;
				}
			default:
				{
					pBitStream->Write(OT_NULL);
					pBitStream->Write0();
					break;
				}
			}	
		}
	}

	void fromVM ( SQVM *pVM, int iFirst )
	{
		for ( int a = iFirst; a <= sq_gettop ( pVM ); a ++ )
		{
			SQObjectType type = sq_gettype ( pVM, a );

			switch ( type )
			{
			case OT_INTEGER:
				{
					SQInteger iValue;
					sq_getinteger ( pVM, a, &iValue );
					push(iValue);
					break;
				}
			case OT_STRING:
				{
					const char *szValue;
					sq_getstring ( pVM, a, &szValue );
					push ( szValue );
					break;
				}
			case OT_FLOAT:
				{
					float fValue;
					sq_getfloat ( pVM, a, &fValue );
					push ( fValue );
					break;
				}
			case OT_BOOL:
				{
					SQBool bValue;
					bool _bValue;
					sq_getbool ( pVM, a, &bValue );

					if ( bValue ) 
						_bValue = true;
					else 
						_bValue = false;

					push(_bValue);
					break;
				}
			case OT_NULL:
				{
					push();
					break;
				}
			default:
				{
					push();
					break;
				}
			}	
		}
	}

	void toVM ( SQVM *pVM )
	{
		for ( std::list<CSquirrelArgument *>::iterator iter = m_SquirrelArguments.begin(); iter !=  m_SquirrelArguments.end(); iter ++ )
		{
			switch ( (*iter)->type )
			{
			case OT_INTEGER:
				{
					sq_pushinteger( pVM, (*iter)->data.i );
					break;
				}
			case OT_INSTANCE:
				{
					SQObject obj;
					obj._type = OT_INSTANCE;
					obj._unVal.pInstance = (*iter)->data.pInstance;					
					sq_pushobject ( pVM, obj );
					break;
				}
			case OT_STRING:
				{
					sq_pushstring( pVM, (*iter)->data.str->Get(), (*iter)->data.str->GetLength() );
					break;
				}
			case OT_FLOAT:
				{
					sq_pushfloat( pVM, (*iter)->data.f );
					break;
				}
			case OT_BOOL:
				{
					sq_pushbool( pVM, (*iter)->data.b );
					break;
				}
			case OT_CLOSURE:
				{
					sq_pushobject ( pVM, (*iter)->data.sqObject );
					break;
				}
			case OT_NULL:
				{
					sq_pushnull ( pVM );
					break;
				}
			default:
				{
					sq_pushnull ( pVM );
					break;
				}
			}	
		}
	}
#if 0
	void push ( CString *str )
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(str);

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}
#endif
	void push ( SQInstance *pInst )
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(pInst);

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	void push ( SQObject pObj )
	{
		// Create argument instace.
		CSquirrelArgument * pArgument = new CSquirrelArgument;

		// Push argument value
		pArgument->Set(pObj);

		// Push argument to arg stack.
		m_SquirrelArguments.push_back(pArgument);
	}

	int size ( )
	{
		return m_SquirrelArguments.size();
	}
};