// =====================================================================================
/**
 * @file					FMT_HdwArinc429InBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Arinc429 Input Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_ARINC429INBUFFERSERVICE_H
#define FMTDEF_HDW_ARINC429INBUFFERSERVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
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
//	Class CFMT_HdwArinc429InBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429InBufferService : public CFMT_HdwService
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- CParameters ---------------------------------------------------------

	//! CParameters
    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwService::CParameters
    {
    public:
        t_FMT_Uint32			m_uiBufferSize;

        CParameters();
    };

	//! t_FilterSDI
    enum t_FilterSDI
    {
        e_FilterSDI_00			= 0x01,
        e_FilterSDI_01			= 0x02,
        e_FilterSDI_10			= 0x04,
        e_FilterSDI_11			= 0x08,
        e_FilterSDI_DontCare	= 0x0F
    };

	//! t_FilterSSM
    enum t_FilterSSM
    {
        e_FilterSSM_00			= 0x01,
        e_FilterSSM_01			= 0x02,
        e_FilterSSM_10			= 0x04,
        e_FilterSSM_11			= 0x08,
        e_FilterSSM_DontCare	= 0x0F
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	//! Buffer Size
    t_FMT_Uint32					m_uiBufferSize;

	//! Message Filter
    t_FMT_Uint16					*m_pusMessageFilter;

	//! Message buffer
    CFMT_HdwArinc429MessageList		m_Buffer;

public:



// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwArinc429InBufferService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwArinc429InBufferService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

	//! Apply the filter on an Arinc429 message; return FMTDEF_TRUE if the message is accepted by the filter
	virtual t_FMT_Bool			ApplyFilter(CFMT_HdwArinc429Message& mess, t_FMT_Uint16 *pusMessageFilter);

public:

    //! Return the service parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    //! Start the service
    virtual t_FMT_Uint32		Start();

    //! Stop the service
    virtual t_FMT_Uint32		Stop();

    //! Return the number of words into buffer
    t_FMT_Uint32                GetBufferSize() const;

    //! Return the number of received messages
    virtual t_FMT_Uint32		GetReadMessagesNumber(t_FMT_Uint32& dwNom);

    //! Read dwSize messages from the input buffer
    virtual t_FMT_Uint32		Read(CFMT_HdwArinc429Message *pMess,t_FMT_Uint32 dwSize,t_FMT_Uint32& dwReadSize);

    //! Set input filter to accept all messages
    virtual t_FMT_Uint32		AcceptAllMessages();

    //! Set input filter to discard all messages
    virtual t_FMT_Uint32		DiscardAllMessages();

    //! Set input filter to accept message with predefined label,SDI and SSM fields.
    virtual t_FMT_Uint32		AcceptMessage(t_FMT_Uint8 ucLabel,t_FMT_Uint8 ucSDI,t_FMT_Uint8 ucSSM);

    //! Set input filter to discard a message with predefined label
    virtual t_FMT_Uint32		DiscardMessage(t_FMT_Uint8 ucLabel);

	//! Enable reception
    virtual t_FMT_Uint32		EnableRx();

    //! Disable reception
    virtual t_FMT_Uint32		DisableRx();

    //! Reset the reception
    virtual t_FMT_Uint32		ResetRx();

};



#endif







