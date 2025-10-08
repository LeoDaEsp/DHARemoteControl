// =====================================================================================
/**
 * @file					FMT_IpAddress.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					15/05/2021
 * @brief					IP Address Object
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][15/05/2021]
 */
// =====================================================================================



#ifndef FMTDEF_IP_ADDRESS_H
#define FMTDEF_IP_ADDRESS_H

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
//	Class CFMT_IpAddress
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_IpAddress : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:

	//! t_IpVersion
	enum t_IpVersion
	{
		e_IpVersion_IPv4		= 0,
		e_IpVersion_IPv6		= 1,
		e_IpVersion_Undefined	= 65535
	};

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	//! IP Version
	t_IpVersion				m_IpVersion;

    //! Digits
    CFMT_Uint32Vector		m_Digits;

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_IpAddress();

    //! Copy constructor
    CFMT_IpAddress(const CFMT_IpAddress& op);

    //! Constructor from a string
    CFMT_IpAddress(const CFMT_String& op);

    //! Destructor
    virtual ~CFMT_IpAddress();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Copy from an homogeneous object
    void                    DataCopy(const CFMT_IpAddress& op);

    //! Copy from string
	void					DataCopy(const CFMT_String& op);

	//! Set to invalid IP
	void					SetToInvalid();

public:

    //! Assignment operator from homogeneous object
    CFMT_IpAddress&		operator=(const CFMT_IpAddress& op);

    //! Assignment operator from a string
    CFMT_IpAddress&		operator=(const CFMT_String& op);

    //! Convert to string
    CFMT_String			ToString() const;

    //! Check if the object is equal to op
    t_FMT_Bool			operator==(const CFMT_IpAddress& op);

    //! Check if the object is notequal to op
    t_FMT_Bool			operator!=(const CFMT_IpAddress& op);

	//! Return an address digit
	t_FMT_Uint8			GetDigit(t_FMT_Uint32 uiDigitIdx);

	//! Set an address digit
	void				SetDigit(t_FMT_Uint32 uiDigitIdx, t_FMT_Uint8 ucDigit);

    // Serialization ---------------------------------------------------------

    //! Serializes a string into the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_IpAddress& a);

    //! Serializes a string from the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_IpAddress& a);
};



class CFMT_IpAddressVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_IpAddressList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_IpAddressList : public CFMT_List<CFMT_IpAddress>
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:
public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

	//! Empty constructor
	CFMT_IpAddressList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_IpAddressList(t_FMT_Uint32 uiLength, const CFMT_IpAddress& tValue) : CFMT_List(uiLength, tValue) {}

	//! Copy constructor
	CFMT_IpAddressList(const CFMT_IpAddressList& list) : CFMT_List(list) {}

	//! Build the list from an array
	CFMT_IpAddressList(CFMT_IpAddress* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_IpAddressList& operator=(const CFMT_IpAddressList& op);
    CFMT_IpAddressList& operator=(const CFMT_List<CFMT_IpAddress>& op);

	//! Assignment from an homogeneous vector
    CFMT_IpAddressList& operator=(CFMT_Vector<CFMT_IpAddress>& op);
    CFMT_IpAddressList& operator=(CFMT_IpAddressVector& op);

};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int8Vector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_IpAddressVector : public CFMT_Vector<CFMT_IpAddress>
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:
public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

	//! Empty constructor
	CFMT_IpAddressVector() {}

	//! Build an array of uiLength without intializing
	CFMT_IpAddressVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

	//! Copy constructor
	CFMT_IpAddressVector(const CFMT_IpAddressVector& op) : CFMT_Vector(op) {}

	//! Build an array of uiLength initializing with value
	CFMT_IpAddressVector(t_FMT_Uint32 uiLength, const CFMT_IpAddress& value) : CFMT_Vector(uiLength, value) {}

	//! Build the object from an array of uiLength items
	CFMT_IpAddressVector(CFMT_IpAddress* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_IpAddressVector& operator=(CFMT_IpAddressList& op);
    CFMT_IpAddressVector& operator=(CFMT_List<CFMT_IpAddress>& op);

	//! Assignment from an homogeneous vector
    CFMT_IpAddressVector& operator=(const CFMT_Vector<CFMT_IpAddress>& op);
    CFMT_IpAddressVector& operator=(const CFMT_IpAddressVector& op);

};


#endif







