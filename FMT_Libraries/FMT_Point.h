// =====================================================================================
/**
 * @file					FMT_Point.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					12/09/2021
 * @brief					Basic point data object
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][12/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_POINT_H
#define FMTDEF_POINT_H

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

#ifndef FMTDEF_BASICCONTAINERS_H
#include "FMT_BasicContainers.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif

#ifndef FMTDEF_BUFFER_H
#include "FMT_Buffer.h"
#endif


using namespace FMT;



// =====================================================================================
//  DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Template Class CFMT_Point
// *************************************************************************************
// *************************************************************************************

template <class T> class CFMT_Point : public CFMT_Object
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

    //!	X coordinate
    T				m_tX;

    //!	Y coordinate
    T				m_tY;

public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    // =====================================================================================
    //	CFMT_Point::CFMT_Point
    // -----------------------------------------------------------------------------------
    /**	Empty constructor
    *
    *	@param		-
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point()
	{
        m_tX = (T)0;
        m_tY = (T)0;
	}


    // =====================================================================================
    //	CFMT_Point::CFMT_Point
    // -----------------------------------------------------------------------------------
    /**	Copy constructor
    *
     *  @param      op = source object
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point(const CFMT_Point<T>& op)
	{
        DataCopy(op);
	}

	
	// =====================================================================================
    //	CFMT_Point::CFMT_Point
    // -----------------------------------------------------------------------------------
    /**	X,Y constructor
    *
    *	@param		X: x coordinate
    *	@param		Y: y coordinate
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point(const T& X, const T& Y)
	{
        m_tX = X;
        m_tY = Y;
	}


    // =====================================================================================
    // FUNCTIONS
    // =====================================================================================

protected:

    // =====================================================================================
    //	CFMT_Point::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous object
     *
     *  @param      op = source object
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void DataCopy(const CFMT_Point<T>& op)
    {
		m_tX = op.m_tX;
		m_tY = op.m_tY;
    }


public:

    // =====================================================================================
    //	CFMT_Point::Set
    // -----------------------------------------------------------------------------------
    /**	Set the point
     *
    *	@param		X: x coordinate
    *	@param		Y: y coordinate
     *  @return     Reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point<T>& Set(const T& X, const T& Y)
    {
		m_tX = X;
		m_tY = Y;

		return (*this);
    }


    // =====================================================================================
    //	CFMT_Point::GetX
    // -----------------------------------------------------------------------------------
    /**	Return the X coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetX() const
    {
		return m_tX;
    }


    // =====================================================================================
    //	CFMT_Point::GetY
    // -----------------------------------------------------------------------------------
    /**	Return the Y coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetY() const
    {
		return m_tY;
    }

	
	// =====================================================================================
    //	CFMT_Point::SetX
    // -----------------------------------------------------------------------------------
    /**	Set the X-coordinate of the point
     *
    *	@param		X: x coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetX(const T& X)
    {
		m_tX = X;
    }


    // =====================================================================================
    //	CFMT_Point::SetY
    // -----------------------------------------------------------------------------------
    /**	Set the Y-coordinate of the point
     *
    *	@param		Y: y coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetY(const T& Y)
    {
		m_tY = Y;
    }


    // =====================================================================================
    //	CFMT_Point::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous object and return a reference to the object
     *
     *  @param      op = source object
     *  @return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Point<T>& operator=(const CFMT_Point<T>& op)
    {
        DataCopy(op);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Point::operator==
    // -----------------------------------------------------------------------------------
    /**	Checks if the values of two operands are equal 
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    t_FMT_Bool operator==(const CFMT_Point<T>& op)
    {
		if ((m_tX == op.m_tX) && (m_tY == op.m_tY))
        {
            return FMTDEF_TRUE;
        }

        return FMTDEF_FALSE;
    }


    // =====================================================================================
    //	CFMT_Point::operator!=
    // -----------------------------------------------------------------------------------
    /**	Checks if the values of two operands are not equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if not equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    t_FMT_Bool operator!=(const CFMT_Point<T>& op)
    {
        return !(operator==(op));
    }


    // =====================================================================================
    //	CFMT_Point::operator+
    // -----------------------------------------------------------------------------------
    /**	Add two points
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Point<T> operator+(const CFMT_Point<T>& op)
    {
		return CFMT_Point(m_tX + op.m_tX, m_tY + op.m_tY);
    }


    // =====================================================================================
    //	CFMT_Point::operator-
    // -----------------------------------------------------------------------------------
    /**	Subtract two points
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Point<T> operator-(const CFMT_Point<T>& op)
    {
		return CFMT_Point(m_tX - op.m_tX, m_tY - op.m_tY);
    }


    // =====================================================================================
    //	CFMT_Point::operator+=
    // -----------------------------------------------------------------------------------
    /**	Add a point to the object
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void operator+=(const CFMT_Point<T>& op)
    {
		m_tX += op.m_tX;
		m_tY += op.m_tY;
    }


    // =====================================================================================
    //	CFMT_Point::operator-=
    // -----------------------------------------------------------------------------------
    /**	Subtract a point from the object
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void operator-=(const CFMT_Point<T>& op)
    {
		m_tX -= op.m_tX;
		m_tY -= op.m_tY;
    }


	// =====================================================================================
	//	operator<<
	// -----------------------------------------------------------------------------------
	/**	Serializes a point into the buffer
	 *
	 *  @param      buf: destination buffer
	 *  @param      p: source
	 *  @return     reference of the buffer
	*/
	// -----------------------------------------------------------------------------------
	//! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
	// =====================================================================================

	friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Point<T>& p)
	{
		buf << p.m_tX;
		buf << p.m_tY;

		return buf;
	}


	// =====================================================================================
	//	operator>>
	// -----------------------------------------------------------------------------------
	/**	Serializes a point from the buffer
	 *
	 *  @param      buf: source buffer
	 *  @param      p: destination
	 *  @return     reference of the buffer
	*/
	// -----------------------------------------------------------------------------------
	//! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
	// =====================================================================================

	friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Point<T>& p)
	{
		buf >> p.m_tX;
		buf >> p.m_tY;

		return buf;
	}
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32Point
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32Point : public CFMT_Point<t_FMT_Int32>
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
    CFMT_Int32Point() {}

	//! X,Y constructor
	CFMT_Int32Point(const t_FMT_Int32& X, const t_FMT_Int32& Y) : CFMT_Point(X, Y) {}

	//! Copy constructor
	CFMT_Int32Point(const CFMT_Int32Point& op) : CFMT_Point(op) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous item
    CFMT_Int32Point& operator=(const CFMT_Int32Point& op);
    CFMT_Int32Point& operator=(const CFMT_Point<t_FMT_Int32>& op);
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoublePoint
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoublePoint : public CFMT_Point<t_FMT_Double>
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
    CFMT_DoublePoint() {}

	//! X,Y constructor
	CFMT_DoublePoint(const t_FMT_Double& X, const t_FMT_Double& Y) : CFMT_Point(X, Y) {}

	//! Copy constructor
	CFMT_DoublePoint(const CFMT_DoublePoint& op) : CFMT_Point(op) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous item
    CFMT_DoublePoint& operator=(const CFMT_DoublePoint& op);
    CFMT_DoublePoint& operator=(const CFMT_Point<t_FMT_Double>& op);

};



class CFMT_Int32PointVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32PointList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32PointList : public CFMT_List<CFMT_Int32Point>
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
	CFMT_Int32PointList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Int32PointList(t_FMT_Uint32 uiLength, const CFMT_Int32Point& tValue) : CFMT_List(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Int32PointList(const CFMT_Int32PointList& list) : CFMT_List(list) {}

	//! Build the list from an array
	CFMT_Int32PointList(CFMT_Int32Point* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Int32PointList& operator=(const CFMT_Int32PointList& op);
    CFMT_Int32PointList& operator=(const CFMT_List<CFMT_Int32Point>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32PointList& operator=(CFMT_Vector<CFMT_Int32Point>& op);
    CFMT_Int32PointList& operator=(CFMT_Int32PointVector& op);

};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32PointVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32PointVector : public CFMT_Vector<CFMT_Int32Point>
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
    CFMT_Int32PointVector() {}

    //! Build an array of uiLength without intializing
    CFMT_Int32PointVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_Int32PointVector(const CFMT_Int32PointVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_Int32PointVector(t_FMT_Uint32 uiLength, const CFMT_Int32Point& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_Int32PointVector(CFMT_Int32Point* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Int32PointVector& operator=(CFMT_Int32PointList& op);
    CFMT_Int32PointVector& operator=(CFMT_List<CFMT_Int32Point>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32PointVector& operator=(const CFMT_Vector<CFMT_Int32Point>& op);
    CFMT_Int32PointVector& operator=(const CFMT_Int32PointVector& op);
};



class CFMT_DoublePointVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoublePointList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoublePointList : public CFMT_List<CFMT_DoublePoint>
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
	CFMT_DoublePointList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_DoublePointList(t_FMT_Uint32 uiLength, const CFMT_DoublePoint& tValue) : CFMT_List(uiLength, tValue) {}

	//! Copy constructor
	CFMT_DoublePointList(const CFMT_DoublePointList& list) : CFMT_List(list) {}

	//! Build the list from an array
	CFMT_DoublePointList(CFMT_DoublePoint* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_DoublePointList& operator=(const CFMT_DoublePointList& op);
    CFMT_DoublePointList& operator=(const CFMT_List<CFMT_DoublePoint>& op);

	//! Assignment from an homogeneous vector
    CFMT_DoublePointList& operator=(CFMT_Vector<CFMT_DoublePoint>& op);
    CFMT_DoublePointList& operator=(CFMT_DoublePointVector& op);

};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoublePointVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoublePointVector : public CFMT_Vector<CFMT_DoublePoint>
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
    CFMT_DoublePointVector() {}

    //! Build an array of uiLength without intializing
    CFMT_DoublePointVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_DoublePointVector(const CFMT_DoublePointVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_DoublePointVector(t_FMT_Uint32 uiLength, const CFMT_DoublePoint& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_DoublePointVector(CFMT_DoublePoint* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_DoublePointVector& operator=(CFMT_DoublePointList& op);
    CFMT_DoublePointVector& operator=(CFMT_List<CFMT_DoublePoint>& op);

	//! Assignment from an homogeneous vector
    CFMT_DoublePointVector& operator=(const CFMT_Vector<CFMT_DoublePoint>& op);
    CFMT_DoublePointVector& operator=(const CFMT_DoublePointVector& op);
};



#endif







