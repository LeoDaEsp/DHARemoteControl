// =====================================================================================
/**
 * @file					FMT_List.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					19/03/2018
 * @brief					Template class for linked list
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][09/03/2018]
 */
// =====================================================================================


#ifndef FMTDEF_LIST_H
#define FMTDEF_LIST_H

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

#ifndef FMTDEF_BUFFER_H
#include "FMT_Buffer.h"
#endif


template <class T> class CFMT_Vector;

using namespace FMT;

// =====================================================================================
//  DEFINES
// =====================================================================================




// *************************************************************************************
// *************************************************************************************
//	Template Class CFMT_ListItem
// *************************************************************************************
// *************************************************************************************

//! Basic item for list

template <class T> class CFMT_ListItem
{
public:

    //! Previous item
    CFMT_ListItem*	pPrec;

    //! Next item
    CFMT_ListItem*	pNext;

    //! Item data
    T               Data;

    CFMT_ListItem()
    {
        pPrec = FMTDEF_NULL;
        pNext = FMTDEF_NULL;
    }


};


// *************************************************************************************
// *************************************************************************************
//	Template Class CFMT_List
// *************************************************************************************
// *************************************************************************************

//! Linked list container

template <class T> class CFMT_List : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

    //! Sorting function
    typedef t_FMT_Int8 (*t_SortCompareFunct)(const T& op1, const T& op2);

public:

// =====================================================================================
//	VARIABLES
// =====================================================================================


protected:

    //!	First list item
    CFMT_ListItem<T>		*m_pStart;

    //!	Last list item
    CFMT_ListItem<T>		*m_pEnd;

    //!	Current list item
    CFMT_ListItem<T>		*m_pPos;

    //!	Number of items of list
	t_FMT_Uint32	        m_uiLength;


public:



// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    // =====================================================================================
    //	CFMT_List::CFMT_List
    // -----------------------------------------------------------------------------------
    /**	Empty constructor
    *
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

	CFMT_List()
	{
        m_uiLength = 0;
        m_pStart = FMTDEF_NULL;
        m_pEnd = FMTDEF_NULL;
        m_pPos = FMTDEF_NULL;
	}

    // =====================================================================================
    //	CFMT_List::CFMT_List
    // -----------------------------------------------------------------------------------
    /**	Build a list of uiLength items with initialization value tValue
    *
    *   @param      uiLength:   list length
    *   @param      tValue:     init value
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List(t_FMT_Uint32 uiLength, const T& tValue)
    {
        if (uiLength == 0)
        {
            m_pStart = FMTDEF_NULL;
            m_pEnd = FMTDEF_NULL;
            m_pPos = FMTDEF_NULL;
            m_uiLength = 0;

            return;
        }

        CFMT_ListItem<T>        *pE, *pP;
        t_FMT_Uint32            i;

        pP = FMTDEF_NULL;
        m_pStart = FMTDEF_NULL;
        pE = FMTDEF_NULL;

        for (i = 0; i < uiLength; i++)
        {
            pE = new CFMT_ListItem<T>;

            if (m_pStart == FMTDEF_NULL)
            {
                m_pStart = pE;
            }
            else
            {
                pP->pNext = pE;
            }

            pE->pPrec = pP;
            pE->pNext = FMTDEF_NULL;

            pE->Data = tValue;

            pP = pE;
        }

        m_uiLength = uiLength;
        m_pEnd = pE;
        m_pPos = m_pStart;
    }


    // =====================================================================================
    //	CFMT_List::CFMT_List
    // -----------------------------------------------------------------------------------
    /**	Copy constructor
     *
     *  @param      op: source
     *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List(const CFMT_List<T>& list)
    {
        m_uiLength = 0;
        m_pStart = FMTDEF_NULL;
        m_pEnd = FMTDEF_NULL;
        m_pPos = FMTDEF_NULL;

        DataCopy(list);
    }


    // =====================================================================================
    //	CFMT_List::CFMT_List
    // -----------------------------------------------------------------------------------
    /**	Build the list from an array
     *
     *  @param      pVet: array
     *  @param      uiLength: array length
     *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List(T* pVet, t_FMT_Uint32 uiLength)
	{
        if (uiLength == 0)
		{
            throw CFMT_Exception(e_Return_InvalidSize, this);
		}

        CFMT_ListItem<T>        *pE,*pP;
        t_FMT_Uint32    i;

        pP = FMTDEF_NULL;
        m_pStart = FMTDEF_NULL;
        pE = FMTDEF_NULL;

        for (i = 0; i < uiLength; i++)
		{
            pE = new CFMT_ListItem<T>;

            if (m_pStart == FMTDEF_NULL)
            {
                m_pStart = pE;
            }
            else
            {
                pP->pNext = pE;
            }

            pE->pPrec = pP;
            pE->pNext = FMTDEF_NULL;
            pE->Data = pVet[i];

            pP = pE;
		}

        m_pEnd = pE;
        m_uiLength = uiLength;
        m_pPos = m_pStart;
	}



    // =====================================================================================
    //	CFMT_List::~CFMT_List
    // -----------------------------------------------------------------------------------
    /**	Destructor
    *
    *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][09/03/2018]
    // =====================================================================================

    virtual ~CFMT_List()
	{
		DeleteAll();
	}


    // =====================================================================================
    // FUNCTIONS
    // =====================================================================================

protected:

    // =====================================================================================
    //	CFMT_List::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous object
     *
     *  @param      op = source object
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void DataCopy(const CFMT_List<T>& op)
	{
        if (this == &op)
        {
            return;
        }

        t_FMT_Uint32	i;
        CFMT_ListItem<T>*       pE;

        if (op.m_uiLength == 0)
		{
			return;
		}

        CFMT_ListItem<T>* p1 = m_pStart;
        CFMT_ListItem<T>* p2 = op.m_pStart;

        for (i = 0; i < FMTDEFM_MIN(op.m_uiLength, m_uiLength); i++)
		{
            p1->Data = p2->Data;
            p1 = p1->pNext;
            p2 = p2->pNext;
		}

        if (op.m_uiLength > m_uiLength)
		{
            t_FMT_Uint32 dwL = op.m_uiLength - m_uiLength;

            for (i = 0; i<dwL; i++)
			{
                pE = new CFMT_ListItem<T>;
                pE->pPrec = m_pEnd;
                pE->pNext = FMTDEF_NULL;
                pE->Data = p2->Data;

                if (m_pEnd == FMTDEF_NULL)
				{
                    m_pStart = pE;
                    m_pEnd = pE;
				}
                else
                {
                    m_pEnd->pNext = pE;
                }

                m_pEnd = pE;
                p2 = p2->pNext;
				m_uiLength++;
			}
		}
        else if (m_uiLength > op.m_uiLength)
		{
            m_pEnd = p1->pPrec;
            m_pEnd->pNext = FMTDEF_NULL;

            t_FMT_Uint32 dwL = m_uiLength - op.m_uiLength;

            for (i = 0; i < dwL; i++)
			{
                pE = p1->pNext;
				delete p1;
                p1 = pE;

				m_uiLength--;
			}
		}

        m_pPos = m_pStart;
	}


    // =====================================================================================
    //	CFMT_List::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous vector
     *
     *  @param      op = source object
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][16/05/2021]
    // =====================================================================================
public:

    void DataCopy(CFMT_Vector<T>& op)
    {
        DeleteAll();

        t_FMT_Uint32    k;

        for (k=0; k<op.GetLength(); k++)
        {
            AppendItem(op[k]);
        }
    }
protected:

    // =====================================================================================
    //	CFMT_List::NextFunction
    // -----------------------------------------------------------------------------------
    /**	Return a reference to the current item and move the pointer to the next
     *
     *  @return     Reference to the current object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    inline T& NextFunction(t_FMT_Uint32 op)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        T* pT = &(m_pPos->Data);

        t_FMT_Bool      bAgain = FMTDEF_TRUE;
        t_FMT_Uint32    i = 0;

        while ((i<op) && bAgain)
        {
            if (m_pPos->pNext == FMTDEF_NULL)
            {
                bAgain = FMTDEF_FALSE;
            }
            else
            {
                m_pPos = m_pPos->pNext;
                i++;
            }
        }

        return (*pT);
    }


    // =====================================================================================
    //	CFMT_List::PreviousFunction
    // -----------------------------------------------------------------------------------
    /**	Return a reference to the current item and move the pointer to the previous
     *
     *  @return     Reference to the current object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    inline T& PreviousFunction(t_FMT_Uint32 op)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        T* pT = &(m_pPos->Data);

        t_FMT_Bool      bAgain = FMTDEF_TRUE;
        t_FMT_Uint32    i = 0;

        while ((i<op) && bAgain)
        {
            if (m_pPos->pPrec == FMTDEF_NULL)
            {
                bAgain = FMTDEF_FALSE;
            }
            else
            {
                m_pPos = m_pPos->pPrec;
                i++;
            }
        }

        return (*pT);
    }


    // =====================================================================================
    //	CFMT_List::PosFunction
    // -----------------------------------------------------------------------------------
    /**	Extract the item of idx position, move the pointer to it and return a reference
     *  to the list
    *
    *	@param      idx: item index
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    inline T& PosFunction(t_FMT_Uint32 idx)
    {
        if (idx >= m_uiLength)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        t_FMT_Uint32    i;

        m_pPos = m_pStart;

        if (idx >= m_uiLength)
        {
            return m_pPos->Data;
        }

        for (i=0; i<idx; i++)
        {
            m_pPos = m_pPos->pNext;
        }

        return (m_pPos->Data);
    }



public:

    // =====================================================================================
    //	CFMT_List::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous object and return a reference to the list
     *
     *  @param      op = source object (C-Style)
     *  @return     reference to the list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List& operator=(const CFMT_List<T>& op)
	{
		DataCopy(op);

		return (*this);
	}


    // =====================================================================================
    //	CFMT_List::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous vector and return a reference to the list
     *
     *  @param      op = source list
     *  @return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_List<T>& operator=(CFMT_Vector<T>& op)
    {
        DataCopy(op);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::CopyItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items from src array, starting from uiStart to current position
    *   and return a reference to the object
    *
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& CopyItemsFrom(T* src, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        CFMT_ListItem<T>        *pE;
        t_FMT_Uint32	k;

        pE = m_pPos;

        k = uiStart;
        while ((pE != FMTDEF_NULL) && (k - uiStart < uiSize))
        {
            pE->Data = src[k];
            pE = pE->pNext;
            k++;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::CopyItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items from src array, starting from uiStart to current position
    *   and return a reference to the object
    *
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_List<T>& CopyItemsFrom(CFMT_Vector<T>& src, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        CFMT_ListItem<T>        *pE;
        t_FMT_Uint32	k;

        pE = m_pPos;

        k = uiStart;
        while ((pE != FMTDEF_NULL) && (k - uiStart < uiSize) && (k<src.GetLength()))
        {
            pE->Data = src[k];
            pE = pE->pNext;
            k++;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::CopyItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items from src list, starting from its current position, to current
    *   position and return a reference to the object
    *
    *	@param      src: source list
    *	@param      uiSize: number of items to insert
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& CopyItemsFrom(CFMT_List<T> &src, t_FMT_Uint32 uiSize)
    {
        CFMT_ListItem<T>        *pE1;
        CFMT_ListItem<T>        *pE2;
        t_FMT_Uint32	k;

        pE1 = src.m_pPos;
        pE2 = m_pPos;

        k = 0;
        while (k < uiSize)
        {
            if ((pE1 == FMTDEF_NULL) || (pE2 == FMTDEF_NULL))
            {
                throw CFMT_Exception(e_Return_OutOfRange,this);
            }

            pE2->Data = pE1->Data;
            pE1 = pE1->pNext;
            pE2 = pE2->pNext;

            k++;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::CopyItemsTo
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items to src array, starting from current position to uiStart position
    *   of array
    *
    *	@param      dest: destination array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void CopyItemsTo(T* dest, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        CFMT_ListItem<T>        *pE;
        t_FMT_Uint32	k;

        pE = m_pPos;

        k = uiStart;
        while ((pE != FMTDEF_NULL) && (k - uiStart < uiSize))
        {
            dest[k] = pE->Data;
            pE = pE->pNext;
            k++;
        }
    }


    // =====================================================================================
    //	CFMT_List::AppendItem
    // -----------------------------------------------------------------------------------
    /**	Create a new item and append to the list
    *
    *	@return     pointer to the new item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T* AppendItem()
	{
        CFMT_ListItem<T>*   pE;

        if (m_uiLength == 0)
		{
            pE = new CFMT_ListItem<T>;
            pE->pPrec = FMTDEF_NULL;
            pE->pNext = FMTDEF_NULL;

            m_pEnd = pE;
            m_pStart = pE;

            m_pPos = pE;

			m_uiLength++;
		}
		else
		{
            pE = new CFMT_ListItem<T>;
            pE->pPrec = m_pEnd;
            pE->pNext = FMTDEF_NULL;

            m_pEnd->pNext = pE;

            m_pEnd = pE;

			m_uiLength++;
		}

        m_pPos = m_pEnd;

		return &(pE->Data);
	}	
	

    // =====================================================================================
    //	CFMT_List::AppendItem
    // -----------------------------------------------------------------------------------
    /**	Append a copy of op to the list
    *
    *	@param      item to append
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void AppendItem(const T& op)
    {
        T* pT = AppendItem();
        (*pT) = op;
    }


    // =====================================================================================
    //	CFMT_List::operator+=
    // -----------------------------------------------------------------------------------
    /**	Append a copy of op to the list
    *
    *	@param      item to append
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void operator+=(const T& op)
    {
        T* pT = AppendItem();
        (*pT) = op;
    }


    // =====================================================================================
    //	CFMT_List::AppendList
    // -----------------------------------------------------------------------------------
    /**	List concatenation; return a reference to the list
    *
    *	@param      list to join
    *	@return     reference to the list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& AppendList(CFMT_List<T>& op)
    {
        CFMT_ListItem<T>* pP = op.m_pStart;
        CFMT_ListItem<T>* pE;

        while (pP != FMTDEF_NULL)
        {
            pE = new CFMT_ListItem<T>;
            if (m_pStart==FMTDEF_NULL)
            {
                m_pStart = pE;
            }

            pE->pPrec = m_pEnd;
            pE->pNext = FMTDEF_NULL;
            pE->Data = pP->Data;

            if (m_pEnd != FMTDEF_NULL)
            {
                m_pEnd->pNext = pE;
            }
            pP = pP->pNext;
            m_pEnd = pE;

            m_uiLength++;
        }

        m_pPos = m_pEnd;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::AppendVector
    // -----------------------------------------------------------------------------------
    /**	Append a vector to the list and return a reference to the list
    *
    *	@param      vector to join
    *	@return     list reference
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_List<T>& AppendVector(CFMT_Vector<T>& op)
    {
        t_FMT_Uint32        k;

        for (k=0; k<op.GetLength(); k++)
        {
            AppendItem(op[k]);
        }

        m_pPos = m_pEnd;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::operator&=
    // -----------------------------------------------------------------------------------
    /**	List concatenation; return a reference to the list
    *
    *	@param      list to join
    *	@return     reference to the list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& operator&=(CFMT_List<T>& op)
    {
        return AppendList(op);
    }


    // =====================================================================================
    //	CFMT_List::operator&=
    // -----------------------------------------------------------------------------------
    /**	Append a vector to the list and return a reference to the list
    *
    *	@param      vector to join
    *	@return     list reference
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& operator&=(CFMT_Vector<T>& op)
    {
        return AppendVector(op);
    }


    // =====================================================================================
    //	CFMT_List::AppendItems
    // -----------------------------------------------------------------------------------
    /**	Append uiSize items from src array, starting from uiStart and return a
    *   reference to the object
    *
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& AppendItems(T* src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart=0)
    {
        CFMT_ListItem<T>*       pE;
        t_FMT_Uint32    k;
        t_FMT_Uint32    pos;

        pos = uiStart;

        for (k=0; k<uiSize; k++)
        {
            pE = new CFMT_ListItem<T>;
            if (m_pStart==FMTDEF_NULL)
            {
                m_pStart = pE;
            }

            pE->pPrec = m_pEnd;
            pE->pNext = FMTDEF_NULL;
            pE->Data = src[pos];

            if (m_pEnd != FMTDEF_NULL)
            {
                m_pEnd->pNext = pE;
            }

            m_pEnd = pE;
            pos++;

            m_uiLength++;
        }

        m_pPos = m_pEnd;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::AppendItems
    // -----------------------------------------------------------------------------------
    /**	Append uiSize items from src list, starting from current position,
    *   and return a reference to the object
    *
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T> AppendItems(CFMT_List<T> &src, t_FMT_Uint32 uiSize)
    {
        t_FMT_Uint32    k;
        CFMT_ListItem<T>*       pE;

        CFMT_ListItem<T>*       pP = src.m_pPos;

        k = 0;

        while ((pP != FMTDEF_NULL) && (k<uiSize))
        {
            pE = new CFMT_ListItem<T>;
            if (m_pStart==FMTDEF_NULL)
            {
                m_pStart = pE;
            }

            pE->pPrec = m_pEnd;
            pE->pNext = FMTDEF_NULL;
            pE->Data = pP->Data;

            if (m_pEnd != FMTDEF_NULL)
            {
                m_pEnd->pNext = pE;
            }
            pP = pP->pNext;
            m_pEnd = pE;

            m_uiLength++;
            k++;
        }

        m_pPos = m_pEnd;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::InsertItem
    // -----------------------------------------------------------------------------------
    /**	Create a new item and insert it at the current position
    *
    *	@return     pointer to the new item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T* InsertItem()
	{
        CFMT_ListItem<T>* pE = new CFMT_ListItem<T>();

        if (m_uiLength == 0)
		{
            pE->pPrec = FMTDEF_NULL;
            pE->pNext = FMTDEF_NULL;

            m_pStart = pE;
            m_pEnd = pE;
            m_pPos = pE;
			m_uiLength++;
			
			return &(pE->Data);
		}

        pE->pPrec = m_pPos->pPrec;
        pE->pNext = m_pPos;

        if (m_pPos == m_pStart)
        {
            m_pStart = pE;
        }
        else
        {
            (m_pPos->pPrec)->pNext = pE;
        }
		
        m_pPos->pPrec = pE;
		m_uiLength++;

        m_pPos = pE;

		return &(pE->Data);
	}


    // =====================================================================================
    //	CFMT_List::InsertItem
    // -----------------------------------------------------------------------------------
    /**	Insert a copy of data at the current position
    *
    *	@param      data: item to add
    *	@return     pointer to the new item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void InsertItem(const T& data)
    {
        T* pT = InsertItem();
        (*pT)= data;
    }


    // =====================================================================================
    //	CFMT_List::InsertList
    // -----------------------------------------------------------------------------------
    /**	Insert a copy of list at the current position and return a reference to the object
    *
    *	@param      list: list to add
    *	@return     reference to the list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& InsertList(CFMT_List<T>& list)
    {
        CFMT_ListItem<T>* pE = FMTDEF_NULL;
        CFMT_ListItem<T>* pO = list.m_pStart;
        CFMT_ListItem<T>* pP;

        if (m_uiLength == 0)
        {
            pP = FMTDEF_NULL;
            while (pO != FMTDEF_NULL)
            {
                pE = new CFMT_ListItem<T>();
                pE->pPrec = pP;
                pE->pNext = FMTDEF_NULL;
                pE->Data = pO->Data;

                if (pP == FMTDEF_NULL)
                {
                    m_pStart = pE;
                }
                else
                {
                    pP->pNext = pE;
                }

                pP = pE;
                pO = pO->pNext;
                m_pEnd = pE;
                m_uiLength++;
                m_pPos = pE;
            }

            return (*this);
        }

        pP = m_pPos->pPrec;

        while (pO != FMTDEF_NULL)
        {
            pE = new CFMT_ListItem<T>();
            pE->pPrec = pP;
            pE->pNext = FMTDEF_NULL;
            pE->Data = pO->Data;

            if (pP == FMTDEF_NULL)
            {
                m_pStart = pE;
            }
            else
            {
                pP->pNext = pE;
            }

            pP = pE;
            pO = pO->pNext;
            m_pEnd = pE;
            m_uiLength++;
        }

        m_pPos->pPrec = pE;
        pE->pNext = m_pPos;
        m_pPos = pE;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::InsertItems
    // -----------------------------------------------------------------------------------
    /**	Insert uiSize items from src array, starting from uiStart, to the current position
    *   and return a reference to the object
    *
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& InsertItems(T* src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart=0)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        CFMT_ListItem<T>        *pE = FMTDEF_NULL;
        CFMT_ListItem<T>        *pP;
        t_FMT_Uint32	k;

        pP = m_pPos->pPrec;

        k = uiStart;
        while (k - uiStart <uiSize)
        {
            pE = new CFMT_ListItem<T>;

            if (m_pPos == m_pStart)
            {
                m_pStart = pE;
            }

            pE->pPrec = pP;

            pE->Data = src[k];

            if (pP != FMTDEF_NULL)
            {
                pP->pNext = pE;
            }

            pP = pE;

            m_uiLength++;
            k++;
        }

        if (pE != FMTDEF_NULL)
        {
            pE->pNext = m_pPos;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::InsertItems
    // -----------------------------------------------------------------------------------
    /**	Insert uiSize items from src list, starting from current position,
    *   to the current position and return a reference to the object
    *
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T> InsertItems(CFMT_List<T> &src, t_FMT_Uint32 uiSize)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        CFMT_ListItem<T>        *pE = FMTDEF_NULL;
        CFMT_ListItem<T>        *pP;
        CFMT_ListItem<T>        *pSE;
        t_FMT_Uint32	k;

        pP = m_pPos->pPrec;
        pSE = src.m_pPos;

        k = 0;
        while (k < uiSize)
        {
            if (pSE == FMTDEF_NULL)
            {
                throw CFMT_Exception(e_Return_OutOfRange,this);
            }

            pE = new CFMT_ListItem<T>;

            if (m_pPos == m_pStart)
            {
                m_pStart = pE;
            }

            pE->pPrec = pP;

            pE->Data = pSE->Data;

            if (pP != FMTDEF_NULL)
            {
                pP->pNext = pE;
            }

            pP = pE;
            pSE = pSE->pNext;

            m_uiLength++;
            k++;
        }

        if (pE != FMTDEF_NULL)
        {
            pE->pNext = m_pPos;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::InsertItems
    // -----------------------------------------------------------------------------------
    /**	Insert uiSize items from src array, starting from uiStart, to the current position
    *   and return a reference to the object
    *
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& InsertItems(CFMT_Vector<T>& src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart=0)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        CFMT_ListItem<T>        *pE = FMTDEF_NULL;
        CFMT_ListItem<T>        *pP;
        t_FMT_Uint32	        k;

        pP = m_pPos->pPrec;

        k = uiStart;
        while ((k - uiStart < uiSize) && (k < src.GetLength()))
        {
            pE = new CFMT_ListItem<T>;

            if (m_pPos == m_pStart)
            {
                m_pStart = pE;
            }

            pE->pPrec = pP;

            pE->Data = src[k];

            if (pP != FMTDEF_NULL)
            {
                pP->pNext = pE;
            }

            pP = pE;

            m_uiLength++;
            k++;
        }

        if (pE != FMTDEF_NULL)
        {
            pE->pNext = m_pPos;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::Push
    // -----------------------------------------------------------------------------------
    /**	Push an item as to a stack
     *
     *  @param      data: item to insert
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void Push(const T& data)
    {
        T* pT = AppendItem();
        (*pT) = data;
    }


    // =====================================================================================
    //	CFMT_List::Pop
    // -----------------------------------------------------------------------------------
    /**	Pop an item from the list as from a stack
     *
     *  @param      data: read item
     *  @return     FMTDEF_TRUE if data has been pop
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Bool Pop(T* pData)
    {
        if (m_uiLength > 0)
        {
            m_pPos = m_pEnd;

            *pData = m_pPos->Data;

            DeleteItem();

            return FMTDEF_TRUE;
        }
        else
        {
            return FMTDEF_FALSE;
        }
    }


    // =====================================================================================
    //	CFMT_List::DeleteAll
    // -----------------------------------------------------------------------------------
    /**	Delete all list items and return a reference to the object
     *
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& DeleteAll()
	{
        CFMT_ListItem<T>* pE = m_pStart;
        CFMT_ListItem<T>* pP;

        while (pE != FMTDEF_NULL)
		{
            pP = pE->pNext;
			delete pE;
            pE = pP;
		}

        m_pStart = FMTDEF_NULL;
        m_pEnd = FMTDEF_NULL;
        m_pPos = FMTDEF_NULL;
        m_uiLength = 0;

        return (*this);
	}


    // =====================================================================================
    //	CFMT_List::DeleteItems
    // -----------------------------------------------------------------------------------
    /**	Delete uiNumItems items from the current position and return a reference to the
     *  object
     *
     *  @param      uiNumItems: number of items to delete
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& DeleteItems(t_FMT_Uint32 uiNumItems)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return (*this);
        }

        t_FMT_Uint32    i;
        CFMT_ListItem<T>*       pE = m_pPos;
        CFMT_ListItem<T>*       pS = m_pPos->pPrec;

        i = 0;
        while (i < uiNumItems)
        {
            if (pE == m_pEnd)
            {
                if (pS == FMTDEF_NULL)
                {
                    m_pStart = FMTDEF_NULL;
                }
                else
                {
                    pS->pNext = FMTDEF_NULL;
                }

                delete pE;

                m_pEnd = pS;
                m_uiLength--;

                m_pPos = pS;

                return (*this);
            }

            m_pPos = pE->pNext;
            m_pPos->pPrec = pS;

            if (pS == FMTDEF_NULL)
            {
                m_pStart = m_pPos;
            }
            else
            {
                pS->pNext = m_pPos;
            }

            delete pE;
            pE = m_pPos;

            m_uiLength--;

            i++;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::DeleteItem
    // -----------------------------------------------------------------------------------
    /**	Delete current item and return a reference to the object
     *
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& DeleteItem()
	{
        if (m_pPos == FMTDEF_NULL)
		{
            return (*this);
		}

        if (m_uiLength == 1)
		{
            m_pStart = FMTDEF_NULL;
            m_pEnd = FMTDEF_NULL;
			delete m_pPos;
            m_pPos = FMTDEF_NULL;
            m_uiLength = 0;

            return (*this);
		}

        if (m_pPos == m_pStart)
		{
            (m_pStart->pNext)->pPrec = FMTDEF_NULL;
            m_pStart = m_pStart->pNext;
			delete m_pPos;
            m_pPos = m_pStart;
			m_uiLength--;

            return (*this);
        }

        (m_pPos->pPrec)->pNext = m_pPos->pNext;
		
        CFMT_ListItem<T>* pH;
        if (m_pPos == m_pEnd)
		{
            m_pEnd = m_pPos->pPrec;
            pH = m_pEnd;
		}
		else 
		{
            (m_pPos->pNext)->pPrec = m_pPos->pPrec;
            pH = m_pPos->pNext;
		}
		delete m_pPos;
        m_pPos = pH;
		m_uiLength--;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::Truncate
    // -----------------------------------------------------------------------------------
    /**	Truncate the list starting current position, toward top or down and return a
     *  reference to the object
     *
     *  @param      bUp: FMTDEF_TRUE, toward top
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_List<T>& Truncate(t_FMT_Bool bUp = FMTDEF_FALSE)
	{
        if (m_pPos == FMTDEF_NULL)
        {
            return (*this);
        }

        CFMT_ListItem<T>    *pE = m_pPos;

        if (bUp)
		{
            if (m_pPos == m_pEnd)
			{
                m_pEnd = FMTDEF_NULL;
                m_pStart = FMTDEF_NULL;
			}
			else 
			{
                m_pStart = m_pPos->pNext;
                m_pStart->pPrec = FMTDEF_NULL;
			}

            while (pE != FMTDEF_NULL)
			{
                m_pPos = pE->pPrec;
				delete pE;
                pE = m_pPos;

				m_uiLength--;
			}
		}
		// Down
		else
		{
            if (m_pPos == m_pStart)
			{
                m_pEnd = FMTDEF_NULL;
                m_pStart = FMTDEF_NULL;
			}
			else 
			{
                m_pEnd = m_pPos->pPrec;
                m_pEnd->pNext = FMTDEF_NULL;
			}

            while (pE != FMTDEF_NULL)
			{
                m_pPos = pE->pNext;
				delete pE;
                pE = m_pPos;

				m_uiLength--;
			}
		}

        m_pPos = m_pEnd;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_List::Extract
    // -----------------------------------------------------------------------------------
    /**	Extract a sub-list of uiNumItems items from the current pointer
    *
    *	@param      dest: destination list
    *	@param      uiNumItems: number of items to extract
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void Extract(CFMT_List<T>& dest, t_FMT_Uint32 uiNumItems)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        dest.DeleteAll();

        CFMT_ListItem<T>* pE = m_pPos;

        t_FMT_Uint32 i = 0;
        while ((pE != FMTDEF_NULL) && (i < uiNumItems))
        {
            dest += pE->Data;
            pE = pE->pNext;
            i++;
        }
    }


    // =====================================================================================
    //	CFMT_List::operator[]
    // -----------------------------------------------------------------------------------
    /**	Extract the item of idx position, move the pointer to it and return a reference
     *  to the list
    *
    *	@param      idx: item index
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& operator[](t_FMT_Uint32 idx)
	{
        return PosFunction(idx);
	}


    // =====================================================================================
    //	CFMT_List::ToStart
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to the start of the list and return a reference to the
     *  first object
     *
     *  @return     reference to the first object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& ToStart()
	{
        m_pPos = m_pStart;
		return (m_pPos->Data);
	}


    // =====================================================================================
    //	CFMT_List::ToEnd
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to the end of the list and return a reference to the
     *  first object
     *
     *  @return     reference to the end object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& ToEnd()
	{
        m_pPos = m_pEnd;
		return (m_pPos->Data);
	}


    // =====================================================================================
    //	CFMT_List::ToPos
    // -----------------------------------------------------------------------------------
    /**	Extract the item of idx position, move the pointer to it and return a reference
     *  to the list
    *
    *	@param      idx: item index
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& ToPos(t_FMT_Uint32 idx)
    {
        return PosFunction(idx);
    }
	

    // =====================================================================================
    //	CFMT_List::operator>>
    // -----------------------------------------------------------------------------------
    /**	Return a reference to the current item and move the pointer to the next
     *
     *  @return     Reference to the current object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& operator>>(t_FMT_Uint32 op)
	{
        return NextFunction(op);
	}


    // =====================================================================================
    //	CFMT_List::Next
    // -----------------------------------------------------------------------------------
    /**	Return a reference to the current item and move the pointer to the next
     *
     *  @return     Reference to the current object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& Next(t_FMT_Uint32 op=1)
    {
        return NextFunction(op);
    }


    // =====================================================================================
    //	CFMT_List::operator<<
    // -----------------------------------------------------------------------------------
    /**	Return a reference to the current item and move the pointer to the previous
     *
     *  @return     Reference to the current object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& operator<<(t_FMT_Uint32 op)
	{
        return PreviousFunction(op);
	}


    // =====================================================================================
    //	CFMT_List::Prev
    // -----------------------------------------------------------------------------------
    /**	Return a reference to the current item and move the pointer to the previous
     *
     *  @return     Reference to the current object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& Prev(t_FMT_Uint32 op = 1)
    {
        return PreviousFunction(op);
    }


    // =====================================================================================
    //	CFMT_List::IsStart
    // -----------------------------------------------------------------------------------
    /**	Checks if the pointer is at the beginning of the list
     *
     *  @return     FMTDEF_TRUE = at the beginning
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Bool IsStart() const
    {
        return (m_pPos==m_pStart);
    }


    // =====================================================================================
    //	CFMT_List::IsEnd
    // -----------------------------------------------------------------------------------
    /**	Checks if the pointer is at the end of the list
     *
     *  @return     FMTDEF_TRUE = at the end
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Bool IsEnd() const
    {
        return (m_pPos==m_pEnd);
    }


    // =====================================================================================
    //	CFMT_List::ItemsFromStart
    // -----------------------------------------------------------------------------------
    /**	Gets the number of items from current pointer to the beginning of the list
     *
     *  @return     number of items from current pointer to the beginning of the list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Uint32 ItemsFromStart() const
    {
        CFMT_ListItem<T>* pPos = m_pPos;

        if (pPos == FMTDEF_NULL)
        {
            return 0;
        }

        t_FMT_Uint32 i = 0;

        while (pPos->pPrec != FMTDEF_NULL)
        {
            pPos = pPos->pPrec;
            i++;
        }

        return i;
    }


    // =====================================================================================
    //	CFMT_List::ItemsToEnd
    // -----------------------------------------------------------------------------------
    /**	Gets the number of items from current pointer to the end of the list
     *
     *  @return     number of items from current pointer to the end of the list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Uint32 ItemsToEnd() const
    {
        CFMT_ListItem<T>* pPos = m_pPos;

        if (pPos == FMTDEF_NULL)
        {
            return 0;
        }

        t_FMT_Uint32 i = 0;

        while (pPos->pNext != FMTDEF_NULL)
        {
            pPos = pPos->pNext;
            i++;
        }

        return i;
    }


    // =====================================================================================
    //	CFMT_List::CurItem
    // -----------------------------------------------------------------------------------
    /**	Get the current item
    *
    *	@return     Current item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    T& CurItem()
	{
        if (m_pPos == FMTDEF_NULL)
		{
			throw CFMT_Exception(e_Return_OutOfRange,this);
		}

		return (m_pPos->Data);
	}


    // =====================================================================================
    //	CFMT_List::GetLength
    // -----------------------------------------------------------------------------------
    /**	Get the length of the list
    *
    *	@return     List length
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

	t_FMT_Uint32 GetLength() const
	{
		return (m_uiLength);
	}


    // =====================================================================================
    //	CFMT_List:: operator!
    // -----------------------------------------------------------------------------------
    /**	Get the length of the list
    *
    *	@return     List length
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Uint32 operator!() const
	{
        return (m_uiLength);
	}


    // =====================================================================================
    //	CFMT_List::FindToEnd
    // -----------------------------------------------------------------------------------
    /**	Find the first item op starting from the current position, toward the end and
    *   moving the pointer to it
    *
    *	@param      op: object to find
    *	@return     FMTDEF_TRUE if found
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Bool FindToEnd(const T& op)
    {
        CFMT_ListItem<T>*   pE;

        pE = m_pPos;

        while (pE != FMTDEF_NULL)
        {
            if (pE->Data == op)
            {
                m_pPos = pE;
                return FMTDEF_TRUE;
            }
            else
            {
                pE = pE->pNext;
            }
        }
        return FMTDEF_FALSE;
    }


    // =====================================================================================
    //	CFMT_List::FindToStart
    // -----------------------------------------------------------------------------------
    /**	Find the first item op starting from the current position, toward the start and
    *   moving the pointer to it
    *
    *	@param      op: object to find
    *	@return     FMTDEF_TRUE if found
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Bool FindToStart(const T& op)
    {
        CFMT_ListItem<T>*   pE;

        pE = m_pPos;

        while (pE != FMTDEF_NULL)
        {
            if (pE->Data == op)
            {
                m_pPos = pE;
                return FMTDEF_TRUE;
            }
            else
            {
                pE = pE->pPrec;
            }
        }
        return FMTDEF_FALSE;
    }


    // =====================================================================================
    //	CFMT_List::operator==
    // -----------------------------------------------------------------------------------
    /**	Checks if two lists are equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Bool operator==(const CFMT_List<T>& op)
    {
        if (m_uiLength != op.m_uiLength)
        {
            return FMTDEF_FALSE;
        }

        CFMT_ListItem<T>*   p1 = m_pStart;
        CFMT_ListItem<T>*   p2 = op.m_pStart;

        while (p1 != FMTDEF_NULL)
        {
            if (p1->Data != p2->Data)
            {
                return FMTDEF_FALSE;
            }

            p1 = p1->pNext;
            p2 = p2->pNext;
        }

        return FMTDEF_TRUE;
    }


    // =====================================================================================
    //	CFMT_List::operator!=
    // -----------------------------------------------------------------------------------
    /**	Checks if two lists are not equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    t_FMT_Bool operator!=(const CFMT_List<T>& op)
    {
        return !(operator==(op));
    }


    // =====================================================================================
    //	CFMT_List::CurItemRef
    // -----------------------------------------------------------------------------------
    /**	Return the current item reference
    *
    *	@param      -
    *	@return     item reference
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

   void*  CurItemRef() const
    {
        return (void*)(m_pPos);
    }


    // =====================================================================================
    //	CFMT_List::SwapItems
    // -----------------------------------------------------------------------------------
    /**	Swap the item pvItem with the next item
    *
    *	@param      pvItem: item to swap
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void SwapItems(void* pvItem)
    {
        CFMT_ListItem<T>    *pE2;
        CFMT_ListItem<T>    *pP;
        CFMT_ListItem<T>    *pE = (CFMT_ListItem<T>*)pvItem;

        pE2 = pE->pNext;

        if (pE == m_pStart)
        {
            m_pStart = pE2;
        }
        if (pE2 == m_pEnd)
        {
            m_pEnd = pE;
        }

        pP = pE->pPrec;

        if (pE->pPrec != FMTDEF_NULL)
        {
            pE->pPrec->pNext = pE2;
        }

        pE->pPrec = pE2;
        pE->pNext = pE2->pNext;

        pE2->pPrec = pP;
        pE2->pNext = pE;

        if (pE->pNext != FMTDEF_NULL)
        {
            pE->pNext->pPrec = pE;
        }
    }


    // =====================================================================================
    //	CFMT_List::Sort
    // -----------------------------------------------------------------------------------
    /**	Sort the list and return a reference to it
    *
    *	@param      pCompareFunct: sort function
    *	@param      bOrder: FMTDEF_TRUE, ascending
    *	@return     reference to the sorted list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void Sort(t_SortCompareFunct pCompareFunct, t_FMT_Bool bOrder)
    {
        if (m_uiLength < 2)
        {
            return;
        }

        CFMT_ListItem<T>*   pPos;
        t_FMT_Bool  bOrdered = FMTDEF_FALSE;

        while (!bOrdered)
        {
            bOrdered = FMTDEF_TRUE;
            pPos = m_pStart;

            while (pPos->pNext != FMTDEF_NULL)
            {
                if ((pCompareFunct((pPos->pNext)->Data, pPos->Data)>0 && !bOrder) ||
                    (pCompareFunct((pPos->pNext)->Data, pPos->Data)<0 && bOrder))
                {
                    SwapItems(pPos);

                    bOrdered = FMTDEF_FALSE;
                }
                else
                {
                    pPos = pPos->pNext;
                }
            }
        }

        return;
    }


    // =====================================================================================
    //	CFMT_Buffer::operator<<
    // -----------------------------------------------------------------------------------
    /**	Serializes a list into the buffer
     *
     *  @param      buf: destination buffer
     *  @param      list: source list
     *  @return     reference of the buffer
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_List<T>& list)
    {
        CFMT_ListItem<T>	*pE;

        buf << list.m_uiLength;

        pE = list.m_pStart;

        while (pE != FMTDEF_NULL)
        {
            buf << pE->Data;
            pE = pE->pNext;
        }

        return buf;
    }


    // =====================================================================================
    //	CFMT_Buffer::operator>>
    // -----------------------------------------------------------------------------------
    /**	Serializes a list from the buffer
     *
     *  @param      buf: source buffer
     *  @param      list: destination list
     *  @return     reference of the buffer
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_List<T>& list)
    {
        CFMT_ListItem<T>	*pE;
        CFMT_ListItem<T>	*pO;
        t_FMT_Uint32        k;
        t_FMT_Uint32        uiSize;

        list.DeleteAll();
        buf >> uiSize;

        pO = FMTDEF_NULL;
		pE = FMTDEF_NULL;
        for (k=0; k<uiSize; k++)
        {
            pE = new CFMT_ListItem<T>;

            if (list.m_pStart == FMTDEF_NULL)
            {
                list.m_pStart = pE;
            }

            pE->pPrec = pO;
            pE->pNext = FMTDEF_NULL;

            if (pO != FMTDEF_NULL)
            {
                pO->pNext = pE;
            }

            buf >> pE->Data;

            list.m_uiLength++;

            pO = pE;
        }

        list.m_pEnd = pE;
        list.m_pPos = pE;

        return buf;
    }


};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_OrderedList
// *************************************************************************************
// *************************************************************************************

//! Ordered linked list container

template <class T> class CFMT_OrderedList : public CFMT_List<T>
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
    CFMT_OrderedList() {}

    //! Build a list of uiLength items with initialization value tValue
    CFMT_OrderedList(t_FMT_Uint32 uiLength, const T& tValue) : CFMT_List<T>(uiLength, tValue) {}

    //! Copy constructor
    CFMT_OrderedList(const CFMT_OrderedList& list) : CFMT_List<T>(list) {}

    //! Build the list from an array
    CFMT_OrderedList(T* pVet, t_FMT_Uint32 uiLength) : CFMT_List<T>(pVet, uiLength) {}


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Compare two objects
    static t_FMT_Int8   Compare(const T& op1, const T& op2)
    {
        if (op1>op2)
        {
            return 1;
        }
        else if (op1<op2)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

public:

    // =====================================================================================
    //	CFMT_OrderedList::Sort
    // -----------------------------------------------------------------------------------
    /**	Sort the list and return a reference to it
    *
    *	@param      bOrder: FMTDEF_TRUE, ascending
    *	@return     reference to the sorted list
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    CFMT_OrderedList& Sort(t_FMT_Bool bOrder)
    {
        CFMT_List<T>::Sort(&Compare, bOrder);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_OrderedList::Max
    // -----------------------------------------------------------------------------------
    /**	Return the maximum of the list
    *
    *	@return     maximum value
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    T& Max()
    {
        t_FMT_Uint32            k;
        CFMT_ListItem<T>        *pMax;
        CFMT_ListItem<T>        *pE;

        pMax = this->m_pStart;
        pE = this->m_pStart;

        for (k=1; k<this->m_uiLength; k++)
        {
            pE = pE->pNext;

            if (pE->Data > pMax->Data)
            {
                pMax = pE;
            }
        }

        return pMax->Data;
    }


    // =====================================================================================
    //	CFMT_OrderedList::Min
    // -----------------------------------------------------------------------------------
    /**	Return the minimum of the list
    *
    *	@return     minimum value
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    T& Min()
    {
        t_FMT_Uint32            k;
        CFMT_ListItem<T>        *pMin;
        CFMT_ListItem<T>        *pE;

        pMin = this->m_pStart;
        pE = this->m_pStart;

        for (k=1; k<this->m_uiLength; k++)
        {
            pE = pE->pNext;

            if (pE->Data < pMin->Data)
            {
                pMin = pE;
            }
        }

        return pMin->Data;
    }

};



#endif

