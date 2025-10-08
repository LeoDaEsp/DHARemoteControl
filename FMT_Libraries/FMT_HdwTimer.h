// =====================================================================================
/**
 * @file					FMT_HdwTimer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Hardware Timer
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_TIMER_H
#define FMTDEF_HDW_TIMER_H

// =====================================================================================
//	INCLUDES
// =====================================================================================

#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifdef FMTDEF_COMPILE_OS_LINUX
#include <unistd.h>
#include <signal.h>
#include <time.h>
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwTimer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwTimer : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    typedef void (*t_TimerCallback)(t_FMT_Uint64 quiTimerCnt, void *pParam);

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

private:


protected:

    CFMT_Mutex          m_Mutex;            //! Timer Mutex

    t_FMT_Uint32		m_uiTimerPeriod;    //! Timer Period
    t_FMT_Int32			m_iTimerId;         //! Timer handle
    t_FMT_Uint64		m_quiTimerCnt;      //! Timer Counter
    t_TimerCallback     m_CallBack;         //! Timer Callback
    void                *m_pParam;          //! Callback Parameter


    #ifdef FMTDEF_COMPILE_OS_WINDOWS
    t_FMT_Int16			m_usResolution;     //! Timer Resolution
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    t_FMT_Int32         m_iSig;             //! Last pending signal
    sigset_t            m_tAlarm_Sig;       //! Signal set for wait method
    timer_t 			m_tTimer_id;        //! Timer ID
    #endif

public:

    #ifdef FMTDEF_COMPILE_OS_LINUX
    static t_FMT_Bool   s_bInitDone;        //! Timer initialization done flag
    static t_FMT_Int32  s_iNextAvailSignal; //! Next Available Signal
    #endif


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwTimer();

    //! Destructor
    virtual ~CFMT_HdwTimer();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

private:

    #ifdef FMTDEF_COMPILE_OS_LINUX
    static t_FMT_Uint64     ToUs(struct timespec *pTime);
    #endif

protected:

    #ifdef FMTDEF_COMPILE_OS_WINDOWS
    static void CALLBACK    HdwTimerProc(UINT wTimerID, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    static void HdwTimerProc(int sig, siginfo_t *si, void *uc);
    #endif

public:

    #ifdef FMTDEF_COMPILE_OS_LINUX
    //! Block all real time signals
    static t_FMT_Bool       InitTimerUnit();
    #endif

    //! Start the timer
    t_FMT_Uint32            Start(t_FMT_Uint32 uiTimerPeriod, t_TimerCallback callback, void *pParam);

    //! Stop the timer
    t_FMT_Uint32            Stop();

	//! Wait for microseconds
	static void				UsSleep(t_FMT_Uint64 quiUsSec);

	//! Wait for milliseconds
	static void				MsSleep(t_FMT_Uint64 quiMsSec);

	//! Wait for seconds
	static void				Sleep(t_FMT_Uint64 quiSec);

	//! Get Tick Counts (ms)
	static t_FMT_Uint64		GetTickCount();

	//! Get Elapsed Ticks (ms)
	static t_FMT_Uint64		GetElapsedTicks(t_FMT_Uint64 quiSince);
};



#endif







