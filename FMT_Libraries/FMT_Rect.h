// =====================================================================================
/**
 * @file					FMT_Rect.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					12/09/2021
 * @brief					Basic rectangle data object
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][12/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_RECT_H
#define FMTDEF_RECT_H

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

#ifndef FMTDEF_POINT_H
#include "FMT_Point.h"
#endif

#ifndef FMTDEF_SIZE_H
#include "FMT_Size.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Rect
// *************************************************************************************
// *************************************************************************************

using namespace FMT;



// =====================================================================================
//  DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Template Class CFMT_Rect
// *************************************************************************************
// *************************************************************************************

template <class T> class CFMT_Rect : public CFMT_Object
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

    //!	X1,Y1 coordinate
    T				m_tLeft;
    T				m_tTop;

    //!	X2,Y2 coordinate
    T				m_tRight;
    T				m_tBottom;

public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    // =====================================================================================
    //	CFMT_Rect::CFMT_Rect
    // -----------------------------------------------------------------------------------
    /**	Empty constructor
    *
    *	@param		-
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect()
	{
        m_tLeft = (T)0;
        m_tTop = (T)0;

        m_tRight = (T)0;
        m_tBottom = (T)0;
	}


    // =====================================================================================
    //	CFMT_Rect::CFMT_Rect
    // -----------------------------------------------------------------------------------
    /**	Set constructor
    *
    *	@param		left = left coordinate
    *	@param		top = top coordinate
    *	@param		right = right coordinate
    *	@param		bottom = bottom coordinate
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect(T left, T top, T right, T bottom)
	{
        m_tLeft = left;
        m_tTop = top;

        m_tRight = right;
        m_tBottom = bottom;
	}


    // =====================================================================================
    //	CFMT_Rect::CFMT_Rect
    // -----------------------------------------------------------------------------------
    /**	Copy constructor
    *
    *	@param		src = source
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect(const CFMT_Rect<T>& src)
	{
		DataCopy(src);
	}


    // =====================================================================================
    //	CFMT_Rect::CFMT_Rect
    // -----------------------------------------------------------------------------------
    /**	Set from two points
    *
    *	@param		src = source
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect(const CFMT_Point<T>& TopLeft, const CFMT_Point<T>& BottomRight)
	{
		m_tLeft = TopLeft.GetX();
		m_tTop = TopLeft.GetY();

		m_tRight = BottomRight.GetX();
		m_tBottom = BottomRight.GetY();
	}


    // =====================================================================================
    //	CFMT_Rect::CFMT_Rect
    // -----------------------------------------------------------------------------------
    /**	Constructor from point-size
    *
    *	@param		src = source
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect(const CFMT_Point<T>& TopLeft, const CFMT_Size<T>& Size)
	{
		m_tLeft = TopLeft.GetX();
		m_tTop = TopLeft.GetY();

		m_tRight = m_tLeft + Size.GetWidth();
		m_tBottom = m_tTop + Size.GetHeight();
	}

	
	// =====================================================================================
    // FUNCTIONS
    // =====================================================================================

protected:
	

    // =====================================================================================
    //	CFMT_Rect::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous object
     *
     *  @param      op = source object
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void DataCopy(const CFMT_Rect<T>& op)
    {
        m_tLeft = op.m_tLeft;
        m_tTop = op.m_tTop;

        m_tRight = op.m_tRight;
        m_tBottom = op.m_tBottom;
    }

public:


    // =====================================================================================
    //	CFMT_Rect::Set
    // -----------------------------------------------------------------------------------
    /**	Set the rect
     *
    *	@param		X: x coordinate
    *	@param		Y: y coordinate
     *  @return     Reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T>& Set(const T& left, const T& top, const T& right, const T& bottom)
    {
        m_tLeft = left;
        m_tTop = top;

        m_tRight = right;
        m_tBottom = bottom;

		return (*this);
    }


    // =====================================================================================
    //	CFMT_Rect::Set
    // -----------------------------------------------------------------------------------
    /**	Set from two points
    *
    *	@param		src = source
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T>& Set(const CFMT_Point<T>& TopLeft, const CFMT_Point<T>& BottomRight)
	{
		m_tLeft = TopLeft.GetX();
		m_tTop = TopLeft.GetY();

		m_tRight = BottomRight.GetX();
		m_tBottom = BottomRight.GetY();

		return (*this);
	}


    // =====================================================================================
    //	CFMT_Rect::Set
    // -----------------------------------------------------------------------------------
    /**	Constructor from point-size
    *
    *	@param		src = source
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T>& Set(const CFMT_Point<T>& TopLeft, const CFMT_Size<T>& Size)
	{
		m_tLeft = TopLeft.GetX();
		m_tTop = TopLeft.GetY();

		m_tRight = m_tLeft + Size.GetWidth();
		m_tBottom = m_tTop + Size.GetHeight();

		return (*this);
	}


	// =====================================================================================
    //	CFMT_Rect::SetLeft
    // -----------------------------------------------------------------------------------
    /**	Set the left coordinate
     *
    *	@param		left: left coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetLeft(const T& left)
    {
		m_tLeft = left;
    }


	// =====================================================================================
    //	CFMT_Rect::SetTop
    // -----------------------------------------------------------------------------------
    /**	Set the top coordinate
     *
    *	@param		top: top coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetTop(const T& top)
    {
		m_tTop = top;
    }


	// =====================================================================================
    //	CFMT_Rect::SetRight
    // -----------------------------------------------------------------------------------
    /**	Set the right coordinate
     *
    *	@param		top: right coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetRight(const T& right)
    {
		m_tRight = right;
    }


	// =====================================================================================
    //	CFMT_Rect::SetBottom
    // -----------------------------------------------------------------------------------
    /**	Set the top coordinate
     *
    *	@param		top: top coordinate
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetBottom(const T& bottom)
    {
		m_tBottom = bottom;
    }

	
	// =====================================================================================
    //	CFMT_Rect::SetTopLeft
    // -----------------------------------------------------------------------------------
    /**	Set the top-left point
     *
     *	@param		topleft: top-left point
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetTopLeft(const CFMT_Point<T>& topleft)
    {
		m_tLeft = topleft.GetX();
		m_tTop = topleft.GetY();
    }


	// =====================================================================================
    //	CFMT_Rect::SetTopRight
    // -----------------------------------------------------------------------------------
    /**	Set the top-right point
     *
     *	@param		topright: top-right point
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetTopRight(const CFMT_Point<T>& topright)
    {
		m_tRight = topright.GetX();
		m_tTop = topright.GetY();
    }


	// =====================================================================================
    //	CFMT_Rect::SetBottomLeft
    // -----------------------------------------------------------------------------------
    /**	Set the bottom-left point
     *
     *	@param		bottomleft: bottom-left point
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetBottomLeft(const CFMT_Point<T>& bottomleft)
    {
		m_tLeft = bottomleft.GetX();
		m_tBottom = bottomleft.GetY();
    }


	// =====================================================================================
    //	CFMT_Rect::SetBottomRight
    // -----------------------------------------------------------------------------------
    /**	Set the bottom-right point
     *
     *	@param		bottomright: bottom-right point
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    void SetBottomRight(const CFMT_Point<T>& bottomright)
    {
		m_tRight = bottomright.GetX();
		m_tBottom = bottomright.GetY();
    }


	// =====================================================================================
    //	CFMT_Rect::GetLeft
    // -----------------------------------------------------------------------------------
    /**	Return the left coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetLeft() const
    {
		return m_tLeft;
    }


    // =====================================================================================
    //	CFMT_Rect::GetTop
    // -----------------------------------------------------------------------------------
    /**	Return the top coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetTop() const
    {
		return m_tTop;
    }

	
    // =====================================================================================
    //	CFMT_Rect::GetRight
    // -----------------------------------------------------------------------------------
    /**	Return the right coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetRight() const
    {
		return m_tRight;
    }


    // =====================================================================================
    //	CFMT_Rect::GetBottom
    // -----------------------------------------------------------------------------------
    /**	Return the bottom coordinate
     *
     *	@param		-
     *  @return     Returned coordinate
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	T GetBottom() const
    {
		return m_tBottom;
    }


	// =====================================================================================
    //	CFMT_Rect::GetTopLeft
    // -----------------------------------------------------------------------------------
    /**	Return the top-left point
     *
     *	@param		-
     *  @return     Returned point
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point<T> GetTopLeft() const
    {
		return CFMT_Point<T>(m_tLeft, m_tTop);
    }


	// =====================================================================================
    //	CFMT_Rect::GetTopRight
    // -----------------------------------------------------------------------------------
    /**	Return the top-right point
     *
     *	@param		-
     *  @return     Returned point
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point<T> GetTopRight() const
    {
		return CFMT_Point<T>(m_tRight, m_tTop);
    }


	// =====================================================================================
    //	CFMT_Rect::GetBottomLeft
    // -----------------------------------------------------------------------------------
    /**	Return the bottom-left point
     *
     *	@param		-
     *  @return     Returned point
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point<T> GetBottomLeft() const
    {
		return CFMT_Point<T>(m_tLeft, m_tBottom);
    }


	// =====================================================================================
    //	CFMT_Rect::GetBottomRight
    // -----------------------------------------------------------------------------------
    /**	Return the bottom-right point
     *
     *	@param		-
     *  @return     Returned point
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Point<T> GetBottomRight() const
    {
		return CFMT_Point<T>(m_tRight, m_tBottom);
    }


	// =====================================================================================
    //	CFMT_Rect::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous object and return a reference to the object
     *
     *  @param      op = source object
     *  @return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Rect<T>& operator=(const CFMT_Rect<T>& op)
    {
        DataCopy(op);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Rect::operator==
    // -----------------------------------------------------------------------------------
    /**	Checks if the values of two operands are equal 
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    t_FMT_Bool operator==(const CFMT_Rect<T>& op)
    {
		if (
			(m_tLeft == op.m_tLeft) && (m_tTop == op.m_tTop) &&
			(m_tRight == op.m_tRight) && (m_tBottom == op.m_tBottom)
			)
        {
            return FMTDEF_TRUE;
        }

        return FMTDEF_FALSE;
    }


    // =====================================================================================
    //	CFMT_Rect::operator!=
    // -----------------------------------------------------------------------------------
    /**	Checks if the values of two operands are not equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if not equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    t_FMT_Bool operator!=(const CFMT_Rect<T>& op)
    {
        return !(operator==(op));
    }


	// =====================================================================================
    //	CFMT_Rect::GetWidth
    // -----------------------------------------------------------------------------------
    /**	Return the width
     *
     *  @param      -
     *  @return     Width
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    T GetWidth() const
    {
        return m_tRight - m_tLeft;
    }


	// =====================================================================================
    //	CFMT_Rect::GetHeight
    // -----------------------------------------------------------------------------------
    /**	Return the height
     *
     *  @param      -
     *  @return     Height
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    T GetHeight() const
    {
        return m_tBottom - m_tTop;
    }


	// =====================================================================================
    //	CFMT_Rect::GetCenter
    // -----------------------------------------------------------------------------------
    /**	Return the center
     *
     *  @param      -
     *  @return     Center
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

    CFMT_Point<T> GetCenter() const
    {
        return CFMT_Point<T>((m_tRight + m_tLeft) / 2, (m_tBottom + m_tTop) / 2);
    }


	// =====================================================================================
    //	CFMT_Rect::MoveTo
    // -----------------------------------------------------------------------------------
    /**	Moves the rectangle, leaving the top-left corner at the given position (x, y)
     *
     *  @param      x : new left position
     *  @param      y : new top position
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	void MoveTo(T x, T y)
	{
		T	w;
		T	h;

		w = GetWidth();
		h = GetHeight();

		m_tLeft = x;
		m_tTop = y;
		m_tRight = m_tLeft + w;
		m_tBottom = m_tTop + h;
	}


	// =====================================================================================
    //	CFMT_Rect::MoveTo
    // -----------------------------------------------------------------------------------
    /**	Moves the rectangle, leaving the top-left corner at the given position pos
     *
     *  @param      pos : new top-left position
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	void MoveTo(const CFMT_Point<T>& pos)
	{
		MoveTo(pos.GetX(), pos.GetY());
	}


	// =====================================================================================
    //	CFMT_Rect::TranslateX
    // -----------------------------------------------------------------------------------
    /**	Moves the rectangle horizontally of the offset
     *
     *  @param      T : Left/Right shift
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	void TranslateX(T off)
	{
		m_tLeft += off;
		m_tRight += off;
	}


	// =====================================================================================
    //	CFMT_Rect::TranslateY
    // -----------------------------------------------------------------------------------
    /**	Moves the rectangle vertically of the offset
     *
     *  @param      T : Up/Down shift
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	void TranslateY(T off)
	{
		m_tTop += off;
		m_tBottom += off;
	}


	// =====================================================================================
    //	CFMT_Rect::Translate
    // -----------------------------------------------------------------------------------
    /**	Moves the rectangle horizontally and vertically of the offset
     *
     *  @param      T : Up/Down shift
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	void Translate(T offx, T offy)
	{
		m_tLeft += offx;
		m_tRight += offx;

		m_tTop += offy;
		m_tBottom += offy;
	}


	// =====================================================================================
    //	CFMT_Rect::IsInside
    // -----------------------------------------------------------------------------------
    /**	Returns FMTDEF_TRUE if the point is inside the rectangle. 
     *
     *  @param      x : x coordinate of the given point
     *  @param      y : y coordinate of the given point
     *  @param      bOnBorder : FMTDEF_TRUE = the border is part of the check
     *  @return     Check result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	t_FMT_Bool IsInside(T x, T y, t_FMT_Bool bOnBorder)
	{
		if (bOnBorder)
		{
			if (
				(x < m_tLeft) ||
				(x > m_tRight) ||
				(y < m_tTop) ||
				(y > m_tBottom)
				)
			{
				return FMTDEF_FALSE;
			}
			else
			{
				return FMTDEF_TRUE;
			}
		}
		else
		{
			if (
				(x <= m_tLeft) ||
				(x >= m_tRight) ||
				(y <= m_tTop) ||
				(y >= m_tBottom)
				)
			{
				return FMTDEF_FALSE;
			}
			else
			{
				return FMTDEF_TRUE;
			}
		}
	}


	// =====================================================================================
    //	CFMT_Rect::IsInside
    // -----------------------------------------------------------------------------------
    /**	Returns FMTDEF_TRUE if the point is inside the rectangle. 
     *
     *  @param      p : Given point
     *  @param      bOnBorder : FMTDEF_TRUE = the border is part of the check
     *  @return     Check result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	t_FMT_Bool IsInside(const CFMT_Point<T>& p, t_FMT_Bool bOnBorder)
	{
		return IsInside(p.GetX(), p.GetY(), bOnBorder);
	}


	// =====================================================================================
    //	CFMT_Rect::IsInside
    // -----------------------------------------------------------------------------------
    /**	Returns FMTDEF_TRUE if the rect is inside the rectangle. 
     *
     *  @param      r : Given rect
     *  @param      bOnBorder : FMTDEF_TRUE = the border is part of the check
     *  @return     Check result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	t_FMT_Bool IsInside(const CFMT_Rect<T>& r, t_FMT_Bool bOnBorder)
	{
		if (!IsInside(r.GetTopLeft(), bOnBorder))
		{
			return FMTDEF_FALSE;
		}

		if (!IsInside(r.GetTopRight(), bOnBorder))
		{
			return FMTDEF_FALSE;
		}

		if (!IsInside(r.GetBottomLeft(), bOnBorder))
		{
			return FMTDEF_FALSE;
		}

		if (!IsInside(r.GetBottomRight(), bOnBorder))
		{
			return FMTDEF_FALSE;
		}

		return FMTDEF_TRUE;
	}


	// =====================================================================================
    //	CFMT_Rect::IsValid
    // -----------------------------------------------------------------------------------
    /**	Returns FMTDEF_TRUE if the rectangle is valid
     *
     *  @param      -
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	t_FMT_Bool IsValid()
	{
		return ((m_tLeft <= m_tRight) && (m_tTop <= m_tBottom)); 
	}


	// =====================================================================================
    //	CFMT_Rect::IsNull
    // -----------------------------------------------------------------------------------
    /**	Returns FMTDEF_TRUE if the rectangle is null
     *
     *  @param      -
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	t_FMT_Bool IsNull()
	{
		return ((m_tLeft == m_tRight) || (m_tTop == m_tBottom)); 
	}


	// =====================================================================================
    //	CFMT_Rect::Intersect
    // -----------------------------------------------------------------------------------
    /**	Returns the intersection of this rectangle and the given rectangle. 
     *
     *  @param      r : operand rect
     *  @return     Intersected Rect
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T> Intersect(const CFMT_Rect<T>& r) const
	{
		// gives bottom-left point of intersection rectangle
		T x5 = FMTDEFM_MAX(m_tLeft, r.m_tLeft);
		T y5 = FMTDEFM_MAX(m_tTop, r.m_tTop);
 
		// gives top-right point of intersection rectangle
		T x6 = FMTDEFM_MIN(m_tRight, r.m_tRight);
		T y6 = FMTDEFM_MIN(m_tBottom, r.m_tBottom);
 
		// no intersection
		if ((x5 > x6) || (y5 > y6))
		{
			return CFMT_Rect<T>();
		}

		return CFMT_Rect<T>(x5, y5, x6, y6);
 	}


	// =====================================================================================
    //	CFMT_Rect::operator&
    // -----------------------------------------------------------------------------------
    /**	Returns the intersection of this rectangle and the given rectangle. 
     *
     *  @param      r : operand rect
     *  @return     Intersected Rect
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T> operator&(const CFMT_Rect<T>& r) const
	{
		return Intersect(r);
	}


	// =====================================================================================
    //	CFMT_Rect::operator&=
    // -----------------------------------------------------------------------------------
    /**	Intersects this rectangle and the given rectangle. 
     *
     *  @param      r : operand rect
     *  @return     Object reference
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T>& operator&=(const CFMT_Rect<T>& r)
	{
		(*this) = Intersect(r);
		return (*this);
	}


	// =====================================================================================
    //	CFMT_Rect::Merge
    // -----------------------------------------------------------------------------------
    /**	Returns the union of this rectangle and the given rectangle. 
     *
     *  @param      r : operand rect
     *  @return     Merged Rect
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T> Merge(const CFMT_Rect<T>& r) const
	{
		// gives bottom-left point of intersection rectangle
		T x5 = FMTDEFM_MIN(m_tLeft, r.m_tLeft);
		T y5 = FMTDEFM_MIN(m_tTop, r.m_tTop);
 
		// gives top-right point of intersection rectangle
		T x6 = FMTDEFM_MAX(m_tRight, r.m_tRight);
		T y6 = FMTDEFM_MAX(m_tBottom, r.m_tBottom);
 
		// no intersection
		if ((x5 > x6) || (y5 > y6))
		{
			return CFMT_Rect<T>();
		}

		return CFMT_Rect<T>(x5, y5, x6, y6);
 	}


	// =====================================================================================
    //	CFMT_Rect::operator|
    // -----------------------------------------------------------------------------------
    /**	Returns the union of this rectangle and the given rectangle. 
     *
     *  @param      r : operand rect
     *  @return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T> operator|(const CFMT_Rect<T>& r) const
	{
		return Merge(r);
	}


	// =====================================================================================
    //	CFMT_Rect::operator|=
    // -----------------------------------------------------------------------------------
    /**	Merge this rectangle and the given rectangle. 
     *
     *  @param      r : operand rect
     *  @return     Object reference
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T>& operator|=(const CFMT_Rect<T>& r)
	{
		(*this) = Merge(r);
		return (*this);
	}


	// =====================================================================================
    //	CFMT_Rect::operator+
    // -----------------------------------------------------------------------------------
    /**	Add to rectangle width/height 
     *
     *  @param      r : operand rect
     *  @return     Result
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T> operator+(const CFMT_Size<T>& sz) const
	{
		T		w;
		T		h;

		w = GetWidth() + sz.GetWidth();
		h = GetHeight() + sz.GetHeight();

		return CFMT_Rect<T>(m_tLeft, m_tTop, m_tLeft + w, m_tBottom + h);
	}


	// =====================================================================================
    //	CFMT_Rect::operator+=
    // -----------------------------------------------------------------------------------
    /**	Add to rectangle width/height 
     *
     *  @param      r : operand rect
     *  @return     Object reference
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
    // =====================================================================================

	CFMT_Rect<T>& operator+=(const CFMT_Size<T>& sz)
	{
		T		w;
		T		h;

		w = GetWidth() + sz.GetWidth();
		h = GetHeight() + sz.GetHeight();

		m_tRight = m_tLeft + w;
		m_tBottom = m_tTop + h;

		return (*this);
	}


	// =====================================================================================
	//	CFMT_Rect<T>::SetWidth
	// -----------------------------------------------------------------------------------
	/**	Sets the width of the rectangle to the given size
	 *
	 *  @param      width: new width
	 *  @return     Object reference
	*/
	// -----------------------------------------------------------------------------------
	//! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
	// =====================================================================================

	void SetWidth(T width)
	{
		m_tRight = m_tLeft + width;
	}


	// =====================================================================================
	//	CFMT_Rect<T>::SetHeight
	// -----------------------------------------------------------------------------------
	/**	Sets the height of the rectangle to the given size
	 *
	 *  @param      height: new height
	 *  @return     Object reference
	*/
	// -----------------------------------------------------------------------------------
	//! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
	// =====================================================================================

	void SetHeight(T height)
	{
		m_tBottom = m_tTop + height;
	}


	// =====================================================================================
	//	CFMT_Rect<T>::SetSize
	// -----------------------------------------------------------------------------------
	/**	Sets the size of the rectangle to the given size
	 *
	 *  @param      size: new size
	 *  @return     Object reference
	*/
	// -----------------------------------------------------------------------------------
	//! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
	// =====================================================================================

	void SetSize(const CFMT_Size<T>& sz)
	{
		m_tRight = m_tLeft + sz.GetWidth();
		m_tBottom = m_tTop + sz.GetHeight();
	}


	// =====================================================================================
	//	operator<<
	// -----------------------------------------------------------------------------------
	/**	Serializes a rect into the buffer
	 *
	 *  @param      buf: destination buffer
	 *  @param      p: source
	 *  @return     reference of the buffer
	*/
	// -----------------------------------------------------------------------------------
	//! @version 1.1.0001	[First issue][M.Forzieri][12/09/2021]
	// =====================================================================================

	friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Rect<T>& r)
	{
		buf << r.m_tLeft;
		buf << r.m_tTop;
		buf << r.m_tRight;
		buf << r.m_tBottom;

		return buf;
	}


	// =====================================================================================
	//	operator>>
	// -----------------------------------------------------------------------------------
	/**	Serializes a rect from the buffer
	 *
	 *  @param      buf: source buffer
	 *  @param      p: destination
	 *  @return     reference of the buffer
	*/
	// -----------------------------------------------------------------------------------
	//! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
	// =====================================================================================

	friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Rect<T>& r)
	{
		buf >> r.m_tLeft;
		buf >> r.m_tTop;
		buf >> r.m_tRight;
		buf >> r.m_tBottom;

		return buf;
	}
};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32Rect
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32Rect : public CFMT_Rect<t_FMT_Int32>
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

    //!	Empty constructor
	CFMT_Int32Rect() {}

    //!	Set constructor
	CFMT_Int32Rect(t_FMT_Int32 left, t_FMT_Int32 top, t_FMT_Int32 right, t_FMT_Int32 bottom) : CFMT_Rect(left, top, right, bottom) {}

    //!	Copy constructor
	CFMT_Int32Rect(const CFMT_Rect<t_FMT_Int32>& src) : CFMT_Rect(src) {}

    //!	Copy constructor
	CFMT_Int32Rect(const CFMT_Point<t_FMT_Int32>& TopLeft, const CFMT_Point<t_FMT_Int32>& BottomRight) : CFMT_Rect(TopLeft, BottomRight) {}

    //!	Constructor from point-size
	CFMT_Int32Rect(const CFMT_Point<t_FMT_Int32>& TopLeft, const CFMT_Size<t_FMT_Int32>& Size) : CFMT_Rect(TopLeft, Size) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous item
    CFMT_Int32Rect& operator=(const CFMT_Int32Rect& op);
    CFMT_Int32Rect& operator=(const CFMT_Rect<t_FMT_Int32>& op);
};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoubleRect
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoubleRect : public CFMT_Rect<t_FMT_Double>
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

    //!	Empty constructor
	CFMT_DoubleRect() {}

    //!	Set constructor
	CFMT_DoubleRect(t_FMT_Double left, t_FMT_Double top, t_FMT_Double right, t_FMT_Double bottom) : CFMT_Rect(left, top, right, bottom) {}

    //!	Copy constructor
	CFMT_DoubleRect(const CFMT_Rect<t_FMT_Double>& src) : CFMT_Rect(src) {}

    //!	Copy constructor
	CFMT_DoubleRect(const CFMT_Point<t_FMT_Double>& TopLeft, const CFMT_Point<t_FMT_Double>& BottomRight) : CFMT_Rect(TopLeft, BottomRight) {}

    //!	Constructor from point-size
	CFMT_DoubleRect(const CFMT_Point<t_FMT_Double>& TopLeft, const CFMT_Size<t_FMT_Double>& Size) : CFMT_Rect(TopLeft, Size) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous item
    CFMT_DoubleRect& operator=(const CFMT_DoubleRect& op);
    CFMT_DoubleRect& operator=(const CFMT_Rect<t_FMT_Double>& op);

};



class CFMT_Int32RectVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32RectList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32RectList : public CFMT_List<CFMT_Int32Rect>
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
	CFMT_Int32RectList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_Int32RectList(t_FMT_Uint32 uiLength, const CFMT_Int32Rect& tValue) : CFMT_List(uiLength, tValue) {}

	//! Copy constructor
	CFMT_Int32RectList(const CFMT_Int32RectList& list) : CFMT_List(list) {}

	//! Build the list from an array
	CFMT_Int32RectList(CFMT_Int32Rect* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_Int32RectList& operator=(const CFMT_Int32RectList& op);
    CFMT_Int32RectList& operator=(const CFMT_List<CFMT_Int32Rect>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32RectList& operator=(CFMT_Vector<CFMT_Int32Rect>& op);
    CFMT_Int32RectList& operator=(CFMT_Int32RectVector& op);

};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Int32RectVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Int32RectVector : public CFMT_Vector<CFMT_Int32Rect>
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
    CFMT_Int32RectVector() {}

    //! Build an array of uiLength without intializing
    CFMT_Int32RectVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_Int32RectVector(const CFMT_Int32RectVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_Int32RectVector(t_FMT_Uint32 uiLength, const CFMT_Int32Rect& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_Int32RectVector(CFMT_Int32Rect* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_Int32RectVector& operator=(CFMT_Int32RectList& op);
    CFMT_Int32RectVector& operator=(CFMT_List<CFMT_Int32Rect>& op);

	//! Assignment from an homogeneous vector
    CFMT_Int32RectVector& operator=(const CFMT_Vector<CFMT_Int32Rect>& op);
    CFMT_Int32RectVector& operator=(const CFMT_Int32RectVector& op);
};



class CFMT_DoubleRectVector;

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoubleRectList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoubleRectList : public CFMT_List<CFMT_DoubleRect>
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
	CFMT_DoubleRectList() {}

	//! Build a list of uiLength items with initialization value tValue
	CFMT_DoubleRectList(t_FMT_Uint32 uiLength, const CFMT_DoubleRect& tValue) : CFMT_List(uiLength, tValue) {}

	//! Copy constructor
	CFMT_DoubleRectList(const CFMT_DoubleRectList& list) : CFMT_List(list) {}

	//! Build the list from an array
	CFMT_DoubleRectList(CFMT_DoubleRect* pVet, t_FMT_Uint32 uiLength) : CFMT_List(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

	//! Assignment from an homogeneous list
    CFMT_DoubleRectList& operator=(const CFMT_DoubleRectList& op);
    CFMT_DoubleRectList& operator=(const CFMT_List<CFMT_DoubleRect>& op);

	//! Assignment from an homogeneous vector
    CFMT_DoubleRectList& operator=(CFMT_Vector<CFMT_DoubleRect>& op);
    CFMT_DoubleRectList& operator=(CFMT_DoubleRectVector& op);

};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DoubleRectVector
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_DoubleRectVector : public CFMT_Vector<CFMT_DoubleRect>
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
    CFMT_DoubleRectVector() {}

    //! Build an array of uiLength without intializing
    CFMT_DoubleRectVector(t_FMT_Uint32 uiLength) : CFMT_Vector(uiLength) {}

    //! Copy constructor
    CFMT_DoubleRectVector(const CFMT_DoubleRectVector& op) : CFMT_Vector(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_DoubleRectVector(t_FMT_Uint32 uiLength, const CFMT_DoubleRect& value) : CFMT_Vector(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_DoubleRectVector(CFMT_DoubleRect* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector(pVet, uiLength) {}



// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Assignment from an homogeneous list
    CFMT_DoubleRectVector& operator=(CFMT_DoubleRectList& op);
    CFMT_DoubleRectVector& operator=(CFMT_List<CFMT_DoubleRect>& op);

	//! Assignment from an homogeneous vector
    CFMT_DoubleRectVector& operator=(const CFMT_Vector<CFMT_DoubleRect>& op);
    CFMT_DoubleRectVector& operator=(const CFMT_DoubleRectVector& op);
};




#endif

