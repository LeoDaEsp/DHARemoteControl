// =====================================================================================
/**
 * @file					FMT_Time.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					02/09/2022
 * @brief					Time Management
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][21/03/2022]
 */
// =====================================================================================



#ifndef FMTDEF_TIME_H
#define FMTDEF_TIME_H

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




class CFMT_TimeVector;
class CFMT_TimeList;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Time
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Time : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:

    // --- t_Time -----------------------------------

    typedef struct t_Date_Struct
    {
        t_FMT_Uint8     m_ucHour;
        t_FMT_Uint8     m_ucMinute;
        t_FMT_Uint8     m_ucSecond;
        t_FMT_Uint16    m_usMillisecond;

    } t_Time;


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    // Time
    t_FMT_Int32         m_iTime;

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

private:

public:

    // Empty constructor
    CFMT_Time();

    // Constructs with hour, minute m, seconds s and milliseconds ms
    CFMT_Time(t_FMT_Int32 iHour, t_FMT_Int32 iMinute, t_FMT_Int32 iSecond = 0, t_FMT_Int32 iMillisec = 0);

    // Copy constructor
    CFMT_Time(const CFMT_Time& op);

    // Destructor
    virtual ~CFMT_Time();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

private:

protected:

    // Copy from an homogeneous object
    void                    DataCopy(const CFMT_Time& op);

    // Check if the specified time is valid
    static t_FMT_Bool       IsValid(t_FMT_Int32 iHour, t_FMT_Int32 iMinute, t_FMT_Int32 iSecond, t_FMT_Int32 iMillisec);

public:

    // Properties ------------------------------------

    // Check if the time is valid
    t_FMT_Bool              IsValid() const;

    // Check if the time is null
    t_FMT_Bool              IsNull() const;

    // Returns the hour
    t_FMT_Int32             GetHour() const;

    // Returns the minute
    t_FMT_Int32             GetMinute() const;

    // Returns the second
    t_FMT_Int32             GetSecond() const;

    // Returns the milliseconds
    t_FMT_Int32             GetMillisecond() const;

    // Returns the time structure
    t_FMT_Uint32            GetTimeStruct(t_Time& Time) const;


    // Assignment ------------------------------------

    // Set with hour, minute m, seconds s and milliseconds ms
    t_FMT_Uint32            Set(t_FMT_Int32 iHour, t_FMT_Int32 iMinute, t_FMT_Int32 iSecond = 0, t_FMT_Int32 iMillisec = 0);

    // Set with time structure
    t_FMT_Uint32            Set(t_Time& Time);

    // Return current time
    static CFMT_Time        GetCurrentTime();

    // Set the object with current time
    void                    FromCurrentTime();

    // Assignment operator from homogeneous object
    CFMT_Time&              operator=(const CFMT_Time& op);


    // Operations ------------------------------------

    // Add milliseconds
    CFMT_Time               AddMilliseconds(t_FMT_Int32 iMs);

    // Add seconds
    CFMT_Time               AddSeconds(t_FMT_Int32 iSec);

    // Returns the number of milliseconds to t; if earlier, returned is negative.
    t_FMT_Int32             MillisecondsTo(CFMT_Time t) const;

    // Returns the number of seconds to t; if earlier, returned is negative.
    t_FMT_Int32             SecondsTo(CFMT_Time t) const;


    // Comparison -------------------------------------

    // Sort comparison function
    static t_FMT_Int8       SortCompare(const CFMT_Time& op1, const CFMT_Time& op2);

    // Check if the object is equal to op
    t_FMT_Bool              operator==(const CFMT_Time& op) const;

    // Check if the object is not equal to op
    t_FMT_Bool              operator!=(const CFMT_Time& op) const;

    // Check if the object is greater or equal to op
    t_FMT_Bool              operator>=(const CFMT_Time& op) const;

    // Check if the object is greater to op
    t_FMT_Bool              operator>(const CFMT_Time& op) const;

    // Check if the object is less or equal to op
    t_FMT_Bool              operator<=(const CFMT_Time& op) const;

    // Check if the object is less to op
    t_FMT_Bool              operator<(const CFMT_Time& op) const;


    // String Formatting -------------------------------------

    // Returns the time as a string using a format parameters string
    CFMT_String             ToString(const CFMT_String &sFormat) const;


    // Serialization ---------------------------------------------------------

    //! Serializes a date into the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Time& d);

    //! Serializes a date from the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Time& d);
};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_TimeList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_TimeList : public CFMT_List<CFMT_Time>
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
    CFMT_TimeList() {}

    //! Build a list of uiLength items with initialization value tValue
    CFMT_TimeList(t_FMT_Uint32 uiLength, const CFMT_Time& tValue) : CFMT_List(uiLength, tValue) {}

    //! Copy constructor
    CFMT_TimeList(const CFMT_TimeList& list) : CFMT_List(list) {}

    //! Build the list from an array
    CFMT_TimeList(CFMT_Time* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}




// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Sorting function
    t_FMT_Int8      SortCompare(const CFMT_Time& op1, const CFMT_Time& op2);

public:

    //! Sort the list
    CFMT_TimeList&  Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_TimeList&  operator=(const CFMT_TimeList& op);
    CFMT_TimeList&  operator=(const CFMT_List<CFMT_Time>& op);

	//! Assignment from an homogeneous vector
    CFMT_TimeList&  operator=(CFMT_Vector<CFMT_Time>& op);
    CFMT_TimeList&  operator=(CFMT_TimeVector& op);
	
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_TimeVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_TimeVector : public CFMT_Vector<CFMT_Time>
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
    CFMT_TimeVector() {}

    //! Build an array of uiLength without intializing
    CFMT_TimeVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_TimeVector(const CFMT_TimeVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_TimeVector(t_FMT_Uint32 uiLength, const CFMT_Time& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_TimeVector(CFMT_Time* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the list
    CFMT_TimeVector&		Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_TimeVector&        operator=(CFMT_TimeList& op);
    CFMT_TimeVector&        operator=(CFMT_List<CFMT_Time>& op);

	//! Assignment from an homogeneous vector
    CFMT_TimeVector&        operator=(const CFMT_Vector<CFMT_Time>& op);
    CFMT_TimeVector&        operator=(const CFMT_TimeVector& op);

};


#endif









