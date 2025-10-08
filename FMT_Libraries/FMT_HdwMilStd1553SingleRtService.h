// =====================================================================================
/**
 * @file					FMT_HdwMilStd1553SingleRtService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Mil-Std-1553 Single Remote Terminal Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MILSTD1553SINGLERTSERVICE_H
#define FMTDEF_HDW_MILSTD1553SINGLERTSERVICE_H

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


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwMilStd1553SingleRtService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwMilStd1553SingleRtService : public CFMT_HdwService
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

        t_FMT_Uint8				m_ucResponseDelay;

        CParameters();
    };

    // --- CSubaddressDesc ---------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CSubaddressDesc : public CFMT_HdwObject
    {
    public:

        t_FMT_Bool					m_bEnable;
        CFMT_HdwMilStd1553Buffer	*m_pBuffer;

        CSubaddressDesc();
    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint8				m_ucResponseDelay;
    t_FMT_Bool              m_bRtRunning;
    t_FMT_Uint8             m_ucRtAdd;
    CSubaddressDesc         *m_pppSubaddressMap[2][32];

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwMilStd1553SingleRtService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwMilStd1553SingleRtService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    virtual void				CreateSubaddressmap();
    virtual void				DestroySubaddressmap();
    t_FMT_Uint32				GetBufferIndex(CFMT_HdwMilStd1553Buffer *pBuffer);
    void						SetBufferIndex(CFMT_HdwMilStd1553Buffer *pBuffer,t_FMT_Uint32 uiIndex);

public:

    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    virtual t_FMT_Uint32		Start();
    virtual t_FMT_Uint32		Stop();

    virtual t_FMT_Uint32		RunRt(t_FMT_Uint8 ucRtAdd);
    virtual t_FMT_Uint32		StopRt();

    virtual t_FMT_Uint32		ConfigSubaddress(t_FMT_Uint8 ucSubadd,t_FMT_Bool bTR,t_FMT_Bool bEnable,CFMT_HdwMilStd1553Buffer *pBuffer);


};



#endif







