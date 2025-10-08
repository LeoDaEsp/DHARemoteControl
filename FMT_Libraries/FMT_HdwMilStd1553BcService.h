// =====================================================================================
/**
 * @file					FMT_HdwMilStd1553BcService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Mil-Std-1553 Bus Controller Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MILSTD1553BCSERVICE_H
#define FMTDEF_HDW_MILSTD1553BCSERVICE_H

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

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553BUFFER_H
#include "FMT_HdwMilStd1553Buffer.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553MESSAGE_H
#include "FMT_HdwMilStd1553Message.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553MAJORFRAME_H
#include "FMT_HdwMilStd1553MajorFrame.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwMilStd1553BcService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwMilStd1553BcService : public CFMT_HdwService
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- CParameters ---------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwService::CParameters
    {
    public:

        t_FMT_Uint32	m_uiMsgIntergap;

        CParameters();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint32		m_uiMsgIntergap;
    t_FMT_Bool			m_bBcRunning;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwMilStd1553BcService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwMilStd1553BcService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    CFMT_HdwMilStd1553Buffer*	GetMessageBuffer(CFMT_HdwMilStd1553Message *pMsg);

    t_FMT_Uint32				GetMinorFrameIndex(CFMT_HdwMilStd1553MinorFrame *pMnr);
    t_FMT_Uint32				GetMessageIndex(CFMT_HdwMilStd1553Message *pMsg);
    t_FMT_Uint32				GetBufferIndex(CFMT_HdwMilStd1553Buffer *pBuffer);

    void						SetMinorFrameIndex(CFMT_HdwMilStd1553MinorFrame *pMnr,t_FMT_Uint32 uiIndex);
    void						SetMessageIndex(CFMT_HdwMilStd1553Message *pMsg,t_FMT_Uint32 uiIndex);
    void						SetBufferIndex(CFMT_HdwMilStd1553Buffer *pBuffer,t_FMT_Uint32 uiIndex);

    void						UpdateMessage(CFMT_HdwMilStd1553Message *pMsg,t_FMT_Uint16 *pusStatus,t_FMT_Uint8 ucBufSize,t_FMT_Uint16 *pusBuffer);

public:

    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    virtual t_FMT_Uint32		Start();
    virtual t_FMT_Uint32		Stop();

    virtual t_FMT_Uint32		LoadConfiguration(t_FMT_Uint32 uiTotMajorFrames, CFMT_HdwMilStd1553MajorFrame *pMjrFrames);
    virtual t_FMT_Uint32		RunBc(t_FMT_Uint32 uiMajorFrameIdx,t_FMT_Uint32 uiMinorFrameTime);
    virtual t_FMT_Uint32		StopBc();
    virtual t_FMT_Uint32		ChangeMajorFrame(t_FMT_Uint32 uiMajorFrameIdx,t_FMT_Uint32 uiMinorFrameTime);

};



#endif







