/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Vendor
 * Licence    : GNU GPL v3
 * File       : CThread.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 **********************************************************************/
#include "CThread.h"

CThread::CThread ( ThreadHandle pHandle )
{
	m_pHandle = pHandle;

	// Creating thread
#ifdef _WIN32
	m_hHandle = CreateThread ( NULL, 0, (LPTHREAD_START_ROUTINE)m_pHandle, NULL, 0, NULL );
#else
	pthread_create(&m_pThread, NULL, m_pHandle, NULL );
#endif
}

CThread::~CThread()
{
	// Stop thread.
#ifdef _WIN32
	TerminateThread ( m_hHandle, 0 );
	CloseHandle ( m_hHandle );

	m_hHandle = NULL;
#else
	pthread_cancel ( m_pThread );
	
	m_pThread = NULL;
#endif
}