// =====================================================================================
/**
 * @file					FMT_HdwService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Service
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_SERVICE_H
#define FMTDEF_HDW_SERVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_EVENT_H
#include "FMT_HdwEvent.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwService : public CFMT_HdwObject
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- t_Service -----------------------------------------------------

    enum t_Service
    {
        e_Service_Undefined				= 0,
        e_Service_Signal				= 1,
        e_Service_ByteInBuffer			= 2,
        e_Service_ByteOutBuffer			= 3,
        e_Service_Arinc429InBuffer		= 4,
        e_Service_Arinc429OutBuffer		= 5,
        e_Service_Arinc429InLblo		= 6,
        e_Service_Arinc429OutLblo		= 7,
        e_Service_CanOutBuffer			= 8,
        e_Service_CanInBuffer			= 9,
        e_Service_MilStd1553Bc			= 10,
        e_Service_MilStd1553SingleRt	= 11,
        e_Service_MilStd1553MultiRt		= 12,
        e_Service_MilStd1553Mt			= 13,
        e_Service_SpiMaster				= 14,
        e_Service_DataGenerator			= 15,
        e_Service_I2CMaster				= 16,
		e_Service_DiscreteIn			= 17,
		e_Service_DiscreteOut			= 18

    };

    // --- t_ServiceStatus -----------------------------------------------------

    enum t_ServiceStatus
    {
        e_ServiceStatus_Off				= 0,
        e_ServiceStatus_On				= 1,
        e_ServiceStatus_Failure			= 2
    };

    // --- CParameters -----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_Object
    {
    public:

        CParameters();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint32		m_uiServiceType;        //! Service Type
    CFMT_HdwObject		*m_pPort;               //! Parent Port
    t_FMT_Uint32		m_uiStatus;             //! Service Status

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Unique constructor
    CFMT_HdwService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the type of the service
    t_FMT_Uint32			GetServiceType() const;

    //! Get the port where the service is working
    CFMT_HdwObject*			GetPort();

    //! Get the device where the working port is installed
    CFMT_HdwObject*			GetDevice();

    //! Get the status of the service
    t_FMT_Uint32			GetStatus() const;

    //! Return the service parameters
    virtual t_FMT_Uint32	GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32	SetParameters(CParameters *pParameters);

    //! Hardware Timer Handler
    virtual t_FMT_Uint32	HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

    //! Lock the device when service is running
    void					DeviceLock();

    //! Unlock the device when service is running
    void					DeviceUnlock();

    //! Start the service
    virtual t_FMT_Uint32	Start();

    //! Stop the service
    virtual t_FMT_Uint32	Stop();

    //! Abort the service
    virtual t_FMT_Uint32	Abort();

    //! Process a hardware event
    virtual t_FMT_Uint32	ProcessEvent(CFMT_HdwEvent* pEvent);

};



#endif







