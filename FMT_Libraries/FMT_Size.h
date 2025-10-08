// =====================================================================================
/**
 * @file					FMT_Size.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					12/09/2021
 * @brief					Basic size data object
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][12/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_SIZE_H
#define FMTDEF_SIZE_H

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
//	Template Class CFMT_Size
// *************************************************************************************
// *************************************************************************************

template <class T> class CFMT_Size : public CFMT_Object
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

    //!	Width coordinate
    T				m_tWidth;

    //!	Height coordinate
    T				m_tHeight;

public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    // =====================================================================================
    //	CFMT_Size::CFMT_Size
    // -----------------------------------------------------------------------------------
    /**	Empty constructor
    *
    *	@param		-
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Size()
	{
        m_tWidth = (T)0;
        m_tHeight = (T)0;
	}


    // =====================================================================================
    //	CFMT_Size::CFMT_Size
    // -----------------------------------------------------------------------------------
    /**	Copy constructor
    *
     *  @param      op = source object
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Size(const CFMT_Size<T>& op)
	{
        DataCopy(op);
	}

	
	// =====================================================================================
    //	CFMT_Size::CFMT_Size
    // -----------------------------------------------------------------------------------
    /**	Width,Height constructor
    *
    *	@param		Width: x coordinate
    *	@param		Height: y coordinate
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Size(const T& Width, const T& Height)
	{
        m_tWidth = Width;
        m_tHeight = Height;
	}


    // =====================================================================================
    // FUNCTIONS
    // =====================================================================================

protected:

    // =====================================================================================
    //	CFMT_Size::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous object
     *
     *  @param      op = source object
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void DataCopy(const CFMT_Size<T>& op)
    {
		m_tWidth = op.m_tWidth;
		m_tHeight = op.m_tHeight;
    }


public:

    // =====================================================================================
    //	CFMT_Size::Set
    // -----------------------------------------------------------------------------------
    /**	Set the point
     *
    *	@param		Width: width
    *	@param		Height: height
     *  @return     Reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Size<T>& Set(const T& Width, const T& Height)
    {
		m_tWidth = Width;
		m_tHeight = Height;

		return (*this);
    }


    // =====================================================================================
    //	CFMT_Size::GetWidth
    // -----------------------------------------------------------------------------------
    /**	Return the Width coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetWidth() const
    {
		return m_tWidth;
    }


    // =====================================================================================
    //	CFMT_Size::GetHeight
    // -----------------------------------------------------------------------------------
    /**	Return the Height coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetHeight() const
    {
		return m_tHeight;
    }

	
	// =====================================================================================
    //	CFMT_Size::SetWidth
    // -----------------------------------------------------------------------------------
    /**	Set the Width-coordinate of the point
     *
    *	@param		Width: x coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetWidth(const T& Width)
    {
		m_tWidth = Width;
    }


    // =====================================================================================
    //	CFMT_Size::SetHeight
    // -----------------------------------------------------------------------------------
    /**	Set the Height-coordinate of the point
     *
    *	@param		Height: y coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetHeight(const T& Height)
    {
		m_tHeight = Height;
    }


    // =====================================================================================
    //	CFMT_Size::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous object and return a reference to the object
     *
     *  @param      op = source object
     *  @return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Size<T>& operator=(const CFMT_Size<T>& op)
    {
        DataCopy(op);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Size::operator==
    // -----------------------------------------------------------------------------------
    /**	Checks if the values of two operands are equal 
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    t_FMT_Bool operator==(const CFMT_Size<T>& op)
    {
		if ((m_tWidth == op.m_tWidth) && (m_tHeight == op.m_tHeight))
        {
            return FMTDEF_TRUE;
        }

        return FMTDEF_FALSE;
    }


    // =====================================================================================
    //	CFMT_Size::operator!=
    // -----------------------------------------------------------------------------------
    /**	Checks if the values of two operands are not equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if not equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    t_FMT_Bool operator!=(const CFMT_Size<T>& op)
    {
        return !(operator==(op));
    }


    // =====================================================================================
    //	CFMT_Size::operator+
    // -----------------------------------------------------------------------------------
    /**	Add two points
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Size<T> operator+(const CFMT_Size<T>& op)
    {
		return CFMT_Size(m_tWidth + op.m_tWidth, m_tHeight + op.m_tHeight);
    }


    // =====================================================================================
    //	CFMT_Size::operator-
    // -----------------------------------------------------------------------------------
    /**	Subtract two points
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Size<T> operator-(const CFMT_Size<T>& op)
    {
		return CFMT_Size(m_tWidth - op.m_tWidth, m_tHeight - op.m_tHeight);
    }


    // =====================================================================================
    //	CFMT_Size::operator+=
    // -----------------------------------------------------------------------------------
    /**	Add a point to the object
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void operator+=(const CFMT_Size<T>& op)
    {
		m_tWidth += op.m_tWidth;
		m_tHeight += op.m_tHeight;
    }


    // =====================================================================================
    //	CFMT_Size::operator-=
    // -----------------------------------------------------------------------------------
    /**	Subtract a point from the object
    *
    *	@param      op: operand
    *	@return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void operator-=(const CFMT_Size<T>& op)
    {
		m_tWidth -= op.m_tWidth;
		m_tHeight -= op.m_tHeight;
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

	friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Size<T>& p)
	{
		buf << p.m_tWidth;
		buf << p.m_tHeight;

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

	friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Size<T>& p)
	{
		buf >> p.m_tWidth;
		buf >> p.m_tHeight;

		return buf;
}
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32Size
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32Size : public CFMT_Size<t_FMT_Int32>
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
    CFMT_Int32Size() {}

	//! Width,Height constructor
	CFMT_Int32Size(const t_FMT_Int32& Width, const t_FMT_Int32& Height) : CFMT_Size(Width, Height) {}

	//! Copy constructor
	CFMT_Int32Size(const CFMT_Int32Size& op) : CFMT_Size(op) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous item
    CFMT_Int32Size& operator=(const CFMT_Int32Size& op);
    CFMT_Int32Size& operator=(const CFMT_Size<t_FMT_Int32>& op);
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoubleSize
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoubleSize : public CFMT_Size<t_FMT_Double>
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
    CFMT_DoubleSize() {}

	//! Width,Height constructor
	CFMT_DoubleSize(const t_FMT_Double& Width, const t_FMT_Double& Height) : CFMT_Size(Width, Height) {}

	//! Copy constructor
	CFMT_DoubleSize(const CFMT_DoubleSize& op) : CFMT_Size(op) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous item
    CFMT_DoubleSize& operator=(const CFMT_DoubleSize& op);
    CFMT_DoubleSize& operator=(const CFMT_Size<t_FMT_Double>& op);

};



class CFMT_Int32SizeVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32SizeList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32SizeList : public CFMT_List<CFMT_Int32Size>
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
	CFMT_Int32SizeList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Int32SizeList(t_FMT_Uint32 uiLength, const CFMT_Int32Size& tValue) : CFMT_List(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Int32SizeList(const CFMT_Int32SizeList& list) : CFMT_List(list) {}

	//! Build the list from an array
	CFMT_Int32SizeList(CFMT_Int32Size* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Int32SizeList& operator=(const CFMT_Int32SizeList& op);
    CFMT_Int32SizeList& operator=(const CFMT_List<CFMT_Int32Size>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32SizeList& operator=(CFMT_Vector<CFMT_Int32Size>& op);
    CFMT_Int32SizeList& operator=(CFMT_Int32SizeVector& op);

};







// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32SizeVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32SizeVector : public CFMT_Vector<CFMT_Int32Size>
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
    CFMT_Int32SizeVector() {}

    //! Build an array of uiLength without intializing
    CFMT_Int32SizeVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_Int32SizeVector(const CFMT_Int32SizeVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_Int32SizeVector(t_FMT_Uint32 uiLength, const CFMT_Int32Size& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_Int32SizeVector(CFMT_Int32Size* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Compute the true RMS of the vector
    CFMT_Int32Size        GetRMS();

	//! Assignment from an homogeneous list
    CFMT_Int32SizeVector& operator=(CFMT_Int32SizeList& op);
    CFMT_Int32SizeVector& operator=(CFMT_List<CFMT_Int32Size>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32SizeVector& operator=(const CFMT_Vector<CFMT_Int32Size>& op);
    CFMT_Int32SizeVector& operator=(const CFMT_Int32SizeVector& op);
};






#endif







