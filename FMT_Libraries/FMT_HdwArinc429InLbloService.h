// =====================================================================================
/**
 * @file					FMT_HdwArinc429InLbloService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					05/09/2021
 * @brief					Abstract Arinc429 Input Label Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][05/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_ARINC429INLBLSERVICE_H
#define FMTDEF_HDW_ARINC429INLBLSERVICE_H

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
//	Class CFMT_HdwArinc429InLbloService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429InLbloService : public CFMT_HdwService
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


    // --- CLabelBuffer ------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CLabelBuffer : public CFMT_Object
	{
	public:
		t_FMT_Bool						m_bEnable;
		t_FMT_Uint32					m_uiMaxDepth;

		CFMT_HdwArinc429MessageList		m_Buffer;

		CLabelBuffer();
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

	//! Message Filters
	t_FMT_Uint16			*m_pusMessageFilter;

	// Label Buffers
	CLabelBuffer			*m_pLabelBuffer;




public:


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
    //! Base constructor
	CFMT_HdwArinc429InLbloService(CFMT_HdwObject *pPort);

    //! Destructor
	virtual ~CFMT_HdwArinc429InLbloService();


	// =====================================================================================
	//	FUNCTIONS
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

    //! Enable reception
	virtual t_FMT_Uint32		EnableRx();

    //! Disable reception
	virtual t_FMT_Uint32		DisableRx();

    //! Reset the reception
	virtual t_FMT_Uint32		ResetRx();

	//! Enable the reception of a label
	virtual t_FMT_Uint32		EnableLabel(t_FMT_Uint8 ucLabel, t_FMT_Uint32 uiDepth, t_FMT_Uint8 ucSDI = e_FilterSDI_DontCare, t_FMT_Uint8 ucSSM = e_FilterSSM_DontCare);

	//! Disable the reception of a label
	virtual t_FMT_Uint32		DisableLabel(t_FMT_Uint8 ucLabel);

	//! Pop a set of message from a label buffer
	virtual t_FMT_Uint32		ReadMessages(t_FMT_Uint8 ucLabel, CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Uint32 *puiReadSize);

	//! Pop last received message from a label buffer
	virtual t_FMT_Uint32		ReadLastMessage(t_FMT_Uint8 ucLabel, CFMT_HdwArinc429Message *pMess);

	//! Get the number of received message from a label buffer
	virtual t_FMT_Uint32		GetLabelNumMessages(t_FMT_Uint8 ucLabel, t_FMT_Uint32 *puiQueueSize);

	//! Flush a specific RX queue 
	virtual	t_FMT_Uint32		FlushQueue(t_FMT_Uint8 ucLabel);
};



#endif







