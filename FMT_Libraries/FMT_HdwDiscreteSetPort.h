// =====================================================================================
/**
 * @file					FMT_HdwDiscreteSetPort.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					27/04/2022
 * @brief					Abstract Hardware Discrete Set Port Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][27/04/2022]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_DISCRETESETPORT_H
#define FMTDEF_HDW_DISCRETESETPORT_H

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

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_PORT_H
#include "FMT_HdwPort.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_HDW_DISCRETESETPORT_PORTNUM_INVALID		0


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwDiscreteSetPort
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwDiscreteSetPort : public CFMT_HdwPort
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- Discrete Configuration -----------------------------------------

    class FMTDEF_LIB_DLLSPEC CDiscreteConfiguration
    {
    public:
		
		t_FMT_Bool			m_bDinEnable;
		t_DiscreteType		m_DinType;
		t_FMT_Double		m_dDinOpenGndLoThreshold;
		t_FMT_Double		m_dDinOpenGndHiThreshold;
		t_FMT_Double		m_dDinSupplyOpenLoThreshold;
		t_FMT_Double		m_dDinSupplyOpenHiThreshold;

		t_FMT_Bool			m_bDoutEnable;
		t_DiscreteType		m_DoutType;
		
        CDiscreteConfiguration();

	    t_FMT_Bool			operator==(const CDiscreteConfiguration& op);
	    t_FMT_Bool			operator!=(const CDiscreteConfiguration& op);

		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CDiscreteConfiguration& m);
		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CDiscreteConfiguration& m);

    };


    // --- CPortDescriptorsVector --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDiscreteConfigurationVector : public CFMT_Vector<CDiscreteConfiguration>
    {
    };



    // --- CParameters ----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwPort::CParameters
    {
    public:

		CDiscreteConfigurationVector	m_vConfiguration;

        CParameters();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    CParameters					m_Parameters;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwDiscreteSetPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

    //! Destructor
    virtual ~CFMT_HdwDiscreteSetPort();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Open the port
    virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);

    //! Close the port
    virtual t_FMT_Uint32		Close();

    //! Return the port parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Enable a service on the port
    virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam);
};



#endif







