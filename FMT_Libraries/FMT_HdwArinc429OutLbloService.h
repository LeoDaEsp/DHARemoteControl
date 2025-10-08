// =====================================================================================
/**
 * @file					FMT_HdwArinc429OutLbloService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
  * @brief					Abstract Arinc429 Output Label Service
*
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_ARINC429OUTLBLSERVICE_H
#define FMTDEF_HDW_ARINC429OUTLBLSERVICE_H

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

#ifndef FMTDEF_HDW_ARINC429MESSAGE_H
#include "FMT_HdwArinc429Message.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwArinc429OutLbloService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429OutLbloService : public CFMT_HdwService
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
        CParameters();
    };


    // --- CLabelCtrl ---------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CLabelCtrl : public CFMT_Object
    {
    public:

        t_FMT_Bool			m_bEnable;
        t_FMT_Uint8			m_ucLabel;
        t_FMT_Uint32		m_uiRate;

        t_FMT_Bool			m_bEnableDataGen;
        t_FMT_Bool			m_bIncDataGen;

        CLabelCtrl();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:
public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Base constructor
    CFMT_HdwArinc429OutLbloService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwArinc429OutLbloService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the service parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    //! Enable transmission
    virtual t_FMT_Uint32		EnableTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Disable transmission
    virtual t_FMT_Uint32		DisableTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Enable message transmission
    virtual t_FMT_Uint32		EnableLabel(t_FMT_Uint8 ucLabel, t_FMT_Uint32 uiRate, t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Enable label with data generator
    virtual t_FMT_Uint32		EnableLabelWithDataGen(t_FMT_Uint8 ucLabel, t_FMT_Uint32 uiRate, t_FMT_Bool bIncDataGen, t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Disable message transmission
    virtual t_FMT_Uint32		DisableLabel(t_FMT_Uint8 ucLabel, t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Enable/Disable transmission of a group of labels
    virtual t_FMT_Uint32		SetLabelsCtrl(CLabelCtrl *pLabelCtrl, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Update messages data fields
    virtual t_FMT_Uint32		UpdateMessages(CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Reset the TX
    virtual	t_FMT_Uint32		ResetTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);


};



#endif







