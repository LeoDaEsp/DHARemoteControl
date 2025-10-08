// =====================================================================================
/**
 * @file					FMT_Date.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					09/03/2018
 * @brief					Date Management
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][21/03/2022]
 */
// =====================================================================================



#ifndef FMTDEF_DATE_H
#define FMTDEF_DATE_H

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




class CFMT_DateVector;
class CFMT_DateList;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Date
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Date : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:

    // --- t_Calendar -----------------------------------

    enum t_Calendar
    {
        e_Calendar_Gregorian      = 0,
        e_Calendar_Julian         = 1,
        e_Calendar_Milankovic     = 2,
        e_Calendar_Jalali         = 3,
        e_Calendar_IslamicCivil   = 4,

        e_Calendar_Total          = 5
    };


    // --- t_Date -----------------------------------

    typedef struct t_Date_Struct
    {
        t_FMT_Int32     m_iDay;
        t_FMT_Int32     m_iMonth;
        t_FMT_Int32     m_iYear;

    } t_Date;


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    // Julian Day
    t_FMT_Int64         m_qiJulianDay;


public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

private:

    //Constructor with julian day
    CFMT_Date(t_FMT_Int64 qiJD);

public:

    // Empty constructor
    CFMT_Date();

    // Constructor with year, month and day
    CFMT_Date(t_FMT_Int32 iYear, t_FMT_Int32 iMonth, t_FMT_Int32 iDay, t_Calendar Calendar = e_Calendar_Gregorian);


    // Copy constructor
    CFMT_Date(const CFMT_Date& op);

    // Destructor
    virtual ~CFMT_Date();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

private:

protected:

    //	Convert the given date into a Julian Day according to the given Calendar
    static t_FMT_Int64      DateToJulianDay(t_FMT_Int32 iYear, t_FMT_Int32 iMonth, t_FMT_Int32 iDay, CFMT_Date::t_Calendar Calendar);

    // Copy from an homogeneous object
    void                    DataCopy(const CFMT_Date& op);

    // Check if the specified date is valid in the given calendar system
    static t_FMT_Bool       IsValid(t_FMT_Int32 iYear, t_FMT_Int32 iMonth, t_FMT_Int32 iDay, t_Calendar Calendar = e_Calendar_Gregorian);

    // Check if the specified year is a leap year
    static t_FMT_Bool       IsLeapYear(t_FMT_Int32 iYear, t_Calendar Calendar = e_Calendar_Gregorian);

    // Get a date object from a Julian day performing validity check
    static CFMT_Date        CreateFromJulianDay(t_FMT_Int64 qiJD);

public:

    // Properties ------------------------------------

    // Return the number of days in the given month/year
    static t_FMT_Int32      GetDaysPerMonth(t_FMT_Int32 iMonth, t_FMT_Int32 iYear, t_Calendar Calendar = e_Calendar_Gregorian);

    // Return the number of days in the given year
    static t_FMT_Int32      GetDaysPerYear(t_FMT_Int32 iYear, t_Calendar Calendar = e_Calendar_Gregorian);

    // Return the number of months in the given year
    static t_FMT_Int32      GetMonthsPerYear(t_FMT_Int32 iYear, t_Calendar Calendar = e_Calendar_Gregorian);

    // Return the number of days in the current month
    t_FMT_Int32             GetDaysPerMonth(t_Calendar Calendar = e_Calendar_Gregorian);

    // Return the number of days in the current year
    t_FMT_Int32             GetDaysPerYear(t_Calendar Calendar = e_Calendar_Gregorian);

    // Check if the is valid
    t_FMT_Bool              IsValid() const;

    // Check if the date is null
    t_FMT_Bool              IsNull() const;

    // Returns the date struct in the given calendar system
    t_FMT_Uint32            GetDateStruct(t_Date& Date, t_Calendar Calendar = e_Calendar_Gregorian) const;

    // Returns the year in the given calendar system
    t_FMT_Int32             GetYear(t_Calendar Calendar = e_Calendar_Gregorian) const;

    // Returns the month in the given calendar system
    t_FMT_Int32             GetMonth(t_Calendar Calendar = e_Calendar_Gregorian) const;

    // Returns the day in the given calendar system
    t_FMT_Int32             GetDay(t_Calendar Calendar = e_Calendar_Gregorian) const;

    // Returns the weekday in the given calendar system
    t_FMT_Int32             GetWeekday(t_Calendar Calendar = e_Calendar_Gregorian) const;

    // Returns the day of the year in the given calendar system
    t_FMT_Int32             GetDayOfyear(t_Calendar Calendar = e_Calendar_Gregorian) const;

    // Returns the number of days from this date to Date
    t_FMT_Int64             GetDaysTo(const CFMT_Date& Date) const;


    // Assignment ------------------------------------

    // Set to represent the date in the Gregorian calendar with the given year, month and day numbers
    t_FMT_Uint32            Set(t_FMT_Int32 iYear, t_FMT_Int32 iMonth, t_FMT_Int32 iDay, t_Calendar Calendar = e_Calendar_Gregorian);

    // Return current date
    static CFMT_Date        GetCurrentDate();

    // Set the object with current date
    void                    FromCurrentDate();

    // Assignment operator from homogeneous object
    CFMT_Date&              operator=(const CFMT_Date& op);


    // Operations ------------------------------------

    // Returns a date containing a date qiDays later or earlier (if negative)
    CFMT_Date               AddDays(t_FMT_Int64 qiDays) const;

    // Returns a date containing a date iMonths later or earlier (if negative)
    CFMT_Date               AddMonths(t_FMT_Int32 iMonths, t_Calendar Calendar = e_Calendar_Gregorian) const;

    // Returns a date containing a date iMonths later or earlier (if negative)
    CFMT_Date               AddYears(t_FMT_Int32 iYears, t_Calendar Calendar = e_Calendar_Gregorian) const;


    // Comparison -------------------------------------

    // Sort comparison function
    static t_FMT_Int8       SortCompare(const CFMT_Date& op1, const CFMT_Date& op2);

    // Check if the object is equal to op
    t_FMT_Bool              operator==(const CFMT_Date& op) const;

    // Check if the object is not equal to op
    t_FMT_Bool              operator!=(const CFMT_Date& op) const;

    // Check if the object is greater or equal to op
    t_FMT_Bool              operator>=(const CFMT_Date& op) const;

    // Check if the object is greater to op
    t_FMT_Bool              operator>(const CFMT_Date& op) const;

    // Check if the object is less or equal to op
    t_FMT_Bool              operator<=(const CFMT_Date& op) const;

    // Check if the object is less to op
    t_FMT_Bool              operator<(const CFMT_Date& op) const;


    // String Formatting -------------------------------------

    // Returns the date as a string using a format parameters string
    CFMT_String             ToString(const CFMT_String &sFormat, t_Calendar Calendar = e_Calendar_Gregorian) const;


    // Serialization ---------------------------------------------------------

    //! Serializes a date into the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Date& d);

    //! Serializes a date from the buffer
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Date& d);
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DateList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DateList : public CFMT_List<CFMT_Date>
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
    CFMT_DateList() {}

    //! Build a list of uiLength items with initialization value tValue
    CFMT_DateList(t_FMT_Uint32 uiLength, const CFMT_Date& tValue) : CFMT_List(uiLength, tValue) {}

    //! Copy constructor
    CFMT_DateList(const CFMT_DateList& list) : CFMT_List(list) {}

    //! Build the list from an array
    CFMT_DateList(CFMT_Date* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}




// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Sorting function
    t_FMT_Int8      SortCompare(const CFMT_Date& op1, const CFMT_Date& op2);

public:

    //! Sort the list
    CFMT_DateList&  Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_DateList&  operator=(const CFMT_DateList& op);
    CFMT_DateList&  operator=(const CFMT_List<CFMT_Date>& op);

	//! Assignment from an homogeneous vector
    CFMT_DateList&  operator=(CFMT_Vector<CFMT_Date>& op);
    CFMT_DateList&  operator=(CFMT_DateVector& op);
	
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DateVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DateVector : public CFMT_Vector<CFMT_Date>
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
    CFMT_DateVector() {}

    //! Build an array of uiLength without intializing
    CFMT_DateVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_DateVector(const CFMT_DateVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_DateVector(t_FMT_Uint32 uiLength, const CFMT_Date& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_DateVector(CFMT_Date* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Sort the list
    CFMT_DateVector&		Sort(t_FMT_Bool bOrder);

	//! Assignment from an homogeneous list
    CFMT_DateVector&        operator=(CFMT_DateList& op);
    CFMT_DateVector&        operator=(CFMT_List<CFMT_Date>& op);

	//! Assignment from an homogeneous vector
    CFMT_DateVector&        operator=(const CFMT_Vector<CFMT_Date>& op);
    CFMT_DateVector&        operator=(const CFMT_DateVector& op);

};
#endif









