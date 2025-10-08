// =====================================================================================
/**
 * @file					FMT_DecimalNumber.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					18/03/2024
 * @brief					Fixed Precision Decimal Number
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][18/03/2024]
 */
// =====================================================================================



#ifndef FMTDEF_DECIMAL_NUMBER_H
#define FMTDEF_DECIMAL_NUMBER_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_LIST_H
#include "FMT_List.h"
#endif

#ifndef FMTDEF_VECTOR_H
#include "FMT_Vector.h"
#endif

#ifndef FMTDEF_BUFFER_H
#include "FMT_Buffer.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif

using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================




class CFMT_DecimalNumberVector;
class CFMT_DecimalNumberList;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DecimalNumber
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DecimalNumber : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:

    //! Decimal Point Digit
    enum t_DecimalPointType
    {
        e_DecimalPointType_Dot          = 0,
        e_DecimalPointType_Comma        = 1,
        e_DecimalPointType_Any          = 2
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    //! Number of decimal digits
    t_FMT_Uint16    m_usDigits;

    //! Value
    t_FMT_Int64     m_qiValue;

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_DecimalNumber(t_FMT_Uint16 usDigits = 2);

    //! Copy constructor
    CFMT_DecimalNumber(const CFMT_DecimalNumber& op);

    //! Constructor from a integer
    CFMT_DecimalNumber(t_FMT_Uint16 usDigits, const t_FMT_Int64& qiInt);

    //! Constructor from a integer part and decimal part
    CFMT_DecimalNumber(t_FMT_Uint16 usDigits, const t_FMT_Int64& qiInt, const t_FMT_Uint16& usDec);

    //! Constructor from a floating point
    CFMT_DecimalNumber(t_FMT_Uint16 usDigits, const t_FMT_Double& op);

    //! Constructor from a C-style string
    CFMT_DecimalNumber(t_FMT_Uint16 usDigits, const t_FMT_Char* op, t_DecimalPointType DecPointType = e_DecimalPointType_Any);


    //! Destructor
    virtual ~CFMT_DecimalNumber();


// =====================================================================================
// FUNCTIONS
// =====================================================================================


protected:

    //! Copy from an homogeneous object
    void                        DataCopy(const CFMT_DecimalNumber& op);

    //! Get the maximum decimal number according to digit number
    static t_FMT_Uint64         GetMaxDec(t_FMT_Uint16 usDigits);

    //! Round a value into desired number of digits
    static t_FMT_Uint16         RoundDecimal(t_FMT_Uint16 usDigits, t_FMT_Uint64 quiVal);

    //! Addition between homogeneous objects
    static CFMT_DecimalNumber   Sum(CFMT_DecimalNumber& op1, CFMT_DecimalNumber& op2);

    //! Subtraction between homogeneous objects
    static CFMT_DecimalNumber   Sub(CFMT_DecimalNumber& op1, CFMT_DecimalNumber& op2);


public:


    // Properties ------------------------------------

    //! Get the sign part
    t_FMT_Int32             GetSign() const;

    //! Get the integral part
    t_FMT_Uint64            GetIntegral() const;

    //! Get the decimal part
    t_FMT_Uint16            GetDecimal() const;

    //! Change the number of digits
    void                    ChangeNumDigits(t_FMT_Uint16 usNewNumDigits);


    // Assignment ------------------------------------

    //! Assignment operator from homogeneous object
    CFMT_DecimalNumber&		operator=(const CFMT_DecimalNumber& op);

    //! Assignment operator from floating point
    CFMT_DecimalNumber&		operator=(const t_FMT_Double& op);

    //! Set from a integer part, decimal part and minus isgn
    CFMT_DecimalNumber&     Set(const t_FMT_Uint64& quiInt, const t_FMT_Uint16& usDec, t_FMT_Bool bMinus = FMTDEF_FALSE);

    //! Assignment from floating point
    CFMT_DecimalNumber&     Set(const t_FMT_Double& op);

    //! Assignment from integer
    CFMT_DecimalNumber&     Set(const t_FMT_Int64& op);

    //! Assign from a C-style string
    CFMT_DecimalNumber&     Set(const t_FMT_Char* op, t_DecimalPointType DecPointType);


    // Math -----------------------------------------

    //! Addition operator from homogeneous object
    CFMT_DecimalNumber		operator+(CFMT_DecimalNumber& op);

    //! Addition operator from homogeneous object with itself
    CFMT_DecimalNumber&		operator+=(CFMT_DecimalNumber& op);

    //! Subtraction operator from homogeneous object
    CFMT_DecimalNumber		operator-(CFMT_DecimalNumber& op);

    //! Subtraction operator from homogeneous object with itself
    CFMT_DecimalNumber&		operator-=(CFMT_DecimalNumber& op);

    //! Multiply operator to integer
    CFMT_DecimalNumber		operator*(const t_FMT_Int64& op);

    //! Multiply operator to integer
    FMTDEF_LIB_DLLSPEC friend CFMT_DecimalNumber  operator*(const t_FMT_Int64& op1, CFMT_DecimalNumber& op2);


    // Conversion -------------------------------------

    //!	Converts to a string
    CFMT_String             ToString(t_FMT_Char chDecDigit);

    //!	Converts to a string with also miles format
    CFMT_String             ToString(t_FMT_Char chDecDigit, t_FMT_Char chMilesDigit);

    //! Convert the string into a floating point number
    t_FMT_Double            ToDouble();


	// Comparison -------------------------------------

    //! Compare the object to another
    t_FMT_Int8              Compare(const CFMT_DecimalNumber& op) const;
    static t_FMT_Int8       Compare(const CFMT_DecimalNumber& op1, const CFMT_DecimalNumber& op2);

    //! Check if the object is equal to op
    t_FMT_Bool              operator==(const CFMT_DecimalNumber& op);

    //! Check if the object is not equal to op
    t_FMT_Bool              operator!=(const CFMT_DecimalNumber& op);

    //! Check if the object is greater or equal to op
    t_FMT_Bool              operator>=(const CFMT_DecimalNumber& op);

    //! Check if the object is greater to op
    t_FMT_Bool              operator>(const CFMT_DecimalNumber& op);

    //! Check if the object is less or equal to op
    t_FMT_Bool              operator<=(const CFMT_DecimalNumber& op);

    //! Check if the object is less to op
    t_FMT_Bool              operator<(const CFMT_DecimalNumber& op);



    // Serialization ---------------------------------------------------------

    //! Serializes a string into the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_DecimalNumber& s);

    //! Serializes a string from the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_DecimalNumber& s);
    #endif

};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DecimalNumberList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DecimalNumberList : public CFMT_List<CFMT_DecimalNumber>
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
    CFMT_DecimalNumberList() {}

    //! Build a list of uiLength items with initialization value tValue
    CFMT_DecimalNumberList(t_FMT_Uint32 uiLength, const CFMT_DecimalNumber& tValue) : CFMT_List(uiLength, tValue) {}

    //! Copy constructor
    CFMT_DecimalNumberList(const CFMT_DecimalNumberList& list) : CFMT_List(list) {}

    //! Build the list from an array
    CFMT_DecimalNumberList(CFMT_DecimalNumber* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}




// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the list
    CFMT_DecimalNumberList&    Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_DecimalNumberList& operator=(const CFMT_DecimalNumberList& op);
    CFMT_DecimalNumberList& operator=(const CFMT_List<CFMT_DecimalNumber>& op);

	//! Assignment from an homogeneous vector
    CFMT_DecimalNumberList& operator=(CFMT_Vector<CFMT_DecimalNumber>& op);
    CFMT_DecimalNumberList& operator=(CFMT_DecimalNumberVector& op);
	
};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DecimalNumberVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DecimalNumberVector : public CFMT_Vector<CFMT_DecimalNumber>
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
    CFMT_DecimalNumberVector() {}

    //! Build an array of uiLength without intializing
    CFMT_DecimalNumberVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_DecimalNumberVector(const CFMT_DecimalNumberVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_DecimalNumberVector(t_FMT_Uint32 uiLength, const CFMT_DecimalNumber& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_DecimalNumberVector(CFMT_DecimalNumber* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the list
    CFMT_DecimalNumberVector&		Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_DecimalNumberVector& operator=(CFMT_DecimalNumberList& op);
    CFMT_DecimalNumberVector& operator=(CFMT_List<CFMT_DecimalNumber>& op);

	//! Assignment from an homogeneous vector
    CFMT_DecimalNumberVector& operator=(const CFMT_Vector<CFMT_DecimalNumber>& op);
    CFMT_DecimalNumberVector& operator=(const CFMT_DecimalNumberVector& op);

};








