// =====================================================================================
/**
 * @file					FMT_Ip4Address.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					15/05/2021
 * @brief					IP4 Address
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][15/05/2021]
 */
// =====================================================================================



#ifndef FMTDEF_IP4_ADDRESS_H
#define FMTDEF_IP4_ADDRESS_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_BASICCONTAINERS_H
#include "FMT_BasicContainers.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif


using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_String
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Ip4Address : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    //! Digits
    CFMT_Uint8Vector       m_Digits;

public:


// =====================================================================================
// CONSTRUCTORS & DECTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_Ip4Address();

    //! Copy constructor
    CFMT_Ip4Address(const CFMT_Ip4Address& op);

    //! Constructor from a string
    CFMT_Ip4Address(const CFMT_String& op);

    //! Destructor
    virtual ~CFMT_Ip4Address();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Copy from an homogeneous object
    void                    DataCopy(const CFMT_Ip4Address& op);


public:

    //! Assignment operator from homogeneous object
    CFMT_Ip4Address&		operator=(const CFMT_Ip4Address& op);

    //! Assignment operator from a string
    CFMT_Ip4Address&		operator=(const CFMT_String& op);

    //! Convert to string
    CFMT_String             ToString() const;


    // Serialization ---------------------------------------------------------

    //! Serializes a string into the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Ip4Address& a);

    //! Serializes a string from the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Ip4Address& a);
};





#endif







