/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Shared
 * Licence    : GNU GPL v3
 * File       : CThread.h
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#pragma once
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
	#include <pthread.h>
	#define Sleep usleep
#endif

#ifdef _WIN32
	typedef void(*ThreadHandle)(PVOID args);
#else
	typedef void(*ThreadHandle)(void *args);
#endif

class CThread
{
private:
#ifdef _WIN32
	HANDLE					m_hHandle;
#else
	pthread_t				m_pThread;
#endif

	ThreadHandle		    m_pHandle;
public:
							CThread ( ThreadHandle pHandle );
							~CThread ( );

};