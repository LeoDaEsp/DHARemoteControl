// =====================================================================================
/**
 * @file					FMT_HdwMilStd1553Message.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Mil-Std-1553 Message
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MILSTD1553MESSAGE_H
#define FMTDEF_HDW_MILSTD1553MESSAGE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_EXCEPTION_H
#include "FMT_Exception.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553BUFFER_H
#include "FMT_HdwMilStd1553Buffer.h"
#endif

#ifndef FMTDEF_MUTEX_H
#include "FMT_Mutex.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwMilStd1553Message
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwMilStd1553Message : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- t_Type ------------------------------------------------

    enum t_Type
    {
        e_Type_Bc2Rt								= 0,
        e_Type_Rt2Bc								= 1,
        e_Type_Rt2Rt								= 2,
        e_Type_ModeCode								= 3,
        e_Type_NotDefined							= 255
    };


    // --- t_ModeCode --------------------------------------------

    enum t_ModeCode
    {
        e_ModeCode_DynamicBusControl					= 0,
        e_ModeCode_SynchronizeWithoutData				= 1,
        e_ModeCode_TransmitStatus						= 2,
        e_ModeCode_InitiateSelfTest						= 3,
        e_ModeCode_TransmitterShutdown					= 4,
        e_ModeCode_OverrideTransmitterShutdown			= 5,
        e_ModeCode_InhibitTerminalFlagBit				= 6,
        e_ModeCode_OverrideInhibitTerminalFlagBit		= 7,
        e_ModeCode_ResetRemoteTerminal					= 8,
        e_ModeCode_TransmitVectorWord					= 16,
        e_ModeCode_SynchronizeWithData					= 17,
        e_ModeCode_TransmitLastCommand					= 18,
        e_ModeCode_TransmitBuiltInTestWord				= 19,
        e_ModeCode_SelectedTransmitterShutdown			= 20,
        e_ModeCode_OverrideSelectedTransmitterShutdown	= 21,
        e_ModeCode_NotDefined							= 255
    };

    // --- t_Channel ---------------------------------------------

    enum t_Channel
    {
        e_Channel_A			= 0,
        e_Channel_B			= 1
    };

    // --- CFMT_HdwMilStd1553MessageStatus -----------------------

    class FMTDEF_LIB_DLLSPEC CStatusWord : public CFMT_Object
    {
    public:

        t_FMT_Bool					m_bMessageError;
        t_FMT_Bool					m_bInstrumentation;
        t_FMT_Bool					m_bServiceRequest;
        t_FMT_Bool					m_bBroadcastCommandReceived;
        t_FMT_Bool					m_bBusy;
        t_FMT_Bool					m_bSubsystemFlag;
        t_FMT_Bool					m_bDynamicBusControlAcceptance;
        t_FMT_Bool					m_bTerminalFlag;
        t_FMT_Uint8					m_ucRtAdd;

        t_FMT_Uint16				m_usWord;

        CStatusWord();

        void						Build();
    };


    // --- CFMT_HdwMilStd1553MessageStatus -----------------------

    class FMTDEF_LIB_DLLSPEC CStatus : public CFMT_Object
    {
    public:

        t_FMT_Bool									m_bUpdated;

        CStatusWord									m_pStatusWord[2];

        t_FMT_Uint16								m_pusResponseTime[2];
        t_FMT_Bool									m_pbTimeout[2];
        t_FMT_Bool									m_pbNdwFail[2];
        t_FMT_Bool									m_pbCsFail[2];
        t_FMT_Bool									m_pbDataFail[2];
        t_FMT_Bool									m_pbSyncFail[2];
        t_FMT_Bool									m_pbParityFail[2];
        t_FMT_Bool									m_pbInvalidResponse[2];

        CStatus();
    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

public:

    friend class CFMT_HdwMilStd1553BcService;

protected:

    t_FMT_Uint32				m_uiIndex;
    CFMT_HdwMilStd1553Buffer	*m_pBuffer;
    t_FMT_Uint16				m_pusStatus[3];
    t_FMT_Bool					m_bUpdated;
    CFMT_Mutex					*m_pMutex;

public:

    t_FMT_Uint8					m_ucChannel;
    t_FMT_Uint8					m_ucType;
    t_FMT_Uint8					m_ucRtDest;
    t_FMT_Uint8					m_ucRtSrc;
    t_FMT_Uint8					m_ucSubaddDest;
    t_FMT_Uint8					m_ucSubaddSrc;
    t_FMT_Uint8					m_ucNdw;
    t_FMT_Uint8					m_ucModeCode;


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwMilStd1553Message();

    //! Destructor
    virtual ~CFMT_HdwMilStd1553Message();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Lock message access
    t_FMT_Uint32			Lock();

    //! Unlock message access
    t_FMT_Uint32			Unlock();

public:

    //! Return FMTDEF_TRUE is the message has a receiving buffer
    t_FMT_Bool				HasReceivingBuffer();

    //! Return FMTDEF_TRUE is the message has a transmitting buffer
    t_FMT_Bool				HasTransmittingBuffer();

    //! Create a BC to RT Message
    t_FMT_Uint32			CreateBc2Rt(t_FMT_Uint8 ucRtDest, t_FMT_Uint8 ucSubaddDest, t_FMT_Uint8 ucNdw, t_FMT_Uint8 ucChannel, CFMT_HdwMilStd1553Buffer *pBuffer);

    //! Create a BC to RT Broadcast Message
    t_FMT_Uint32			CreateBc2RtBroadcast(t_FMT_Uint8 ucSubaddDest, t_FMT_Uint8 ucNdw, t_FMT_Uint8 ucChannel, CFMT_HdwMilStd1553Buffer *pBuffer);

    //! Create a RT to BC Message
    t_FMT_Uint32			CreateRt2Bc(t_FMT_Uint8 ucRtSrc, t_FMT_Uint8 ucSubaddSrc ,t_FMT_Uint8 ucNdw, t_FMT_Uint8 ucChannel, CFMT_HdwMilStd1553Buffer *pBuffer);

    //! Create a RT to RT Message
    t_FMT_Uint32			CreateRt2Rt(t_FMT_Uint8 ucRtSrc, t_FMT_Uint8 ucSubaddSrc, t_FMT_Uint8 ucRtDest, t_FMT_Uint8 ucSubaddDest, t_FMT_Uint8 ucNdw,
                                            t_FMT_Uint8 ucChannel, CFMT_HdwMilStd1553Buffer *pBuffer);

    //! Create a RT to RT Message
    t_FMT_Uint32			CreateRt2RtBroadcast(t_FMT_Uint8 ucRtSrc, t_FMT_Uint8 ucSubaddSrc, t_FMT_Uint8 ucSubaddDest, t_FMT_Uint8 ucNdw,
                                            t_FMT_Uint8 ucChannel ,CFMT_HdwMilStd1553Buffer *pBuffer);

    //! Create a Mode Code Message
    t_FMT_Uint32			CreateModeCode(t_FMT_Uint8 ucRtDest, t_FMT_Uint8 ucModeCode, t_FMT_Uint8 ucChannel, CFMT_HdwMilStd1553Buffer *pBuffer);

    //! Return the message status
    void					GetStatus(CStatus *pStatus, t_FMT_Bool bResetUpdateFlag = FMTDEF_TRUE);

};



#endif







