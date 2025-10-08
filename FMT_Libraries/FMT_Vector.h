// =====================================================================================
/**
 * @file					CFMT_Vector.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					19/03/2018
 * @brief					Template class for array
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][21/03/2018]
 */
// =====================================================================================

#ifndef FMTDEF_VECTOR_H
#define FMTDEF_VECTOR_H

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

template <class T> class CFMT_List;


using namespace FMT;

// =====================================================================================
//  DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Template Class CFMT_Vector
// *************************************************************************************
// *************************************************************************************

template <class T> class CFMT_Vector : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

public:

    //! Sorting function
    typedef t_FMT_Int8 (*t_SortCompareFunct)(const T& op1, const T& op2);

// =====================================================================================
//	VARIABLES
// =====================================================================================


protected:

    //!	Data buffer
    T*				m_pBuf;

    //!	Number of items of the array
    t_FMT_Uint32	m_uiLength;


public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    // =====================================================================================
    //	CFMT_Vector::CFMT_Vector
    // -----------------------------------------------------------------------------------
    /**	Empty constructor
    *
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

	CFMT_Vector()
	{
        m_uiLength = 0;
        m_pBuf = FMTDEF_NULL;
	}


    // =====================================================================================
    //	CFMT_Vector::CFMT_Vector
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiLength without intializing
    *
    *	@param		uiLength: array length
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector(t_FMT_Uint32 uiLength)
	{
        m_pBuf = FMTDEF_NULL;
        m_uiLength = 0;

        Create(uiLength);
	}


    // =====================================================================================
    //	CFMT_Vector::CFMT_Vector
    // -----------------------------------------------------------------------------------
    /**	Copy constructor
     *
     *  @param      op: source
     *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

	CFMT_Vector(const CFMT_Vector<T>& op)
	{
        m_uiLength = 0;
        m_pBuf = FMTDEF_NULL;

        DataCopy(op);
	}


    // =====================================================================================
    //	CFMT_Vector::CFMT_Vector
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiLength initializing with value
    *
    *	@param		uiLength: array length
    *	@param		value: initializing value
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector(t_FMT_Uint32 uiLength, const T& value)
    {
        m_pBuf = FMTDEF_NULL;

        Create(uiLength, value);
    }


    // =====================================================================================
    //	CFMT_Vector::CFMT_Vector
    // -----------------------------------------------------------------------------------
    /**	Build the object from an array of uiLength items
    *
    *	@param		pVet: source array
    *	@param		uiLength: array length
    *	@param		value: initializing value
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector(T* pVet, t_FMT_Uint32 uiLength)
	{
        m_pBuf = FMTDEF_NULL;

        Create(pVet, uiLength);
    }


    // =====================================================================================
    //	CFMT_Vector::~CFMT_Vector
    // -----------------------------------------------------------------------------------
    /**	Destructor
    *
    *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][09/03/2018]
    // =====================================================================================

	~CFMT_Vector()
	{
		DeleteBuffer();
	}


// =====================================================================================
//	FUNCTIONS
// =====================================================================================

protected:

    // =====================================================================================
    //	CFMT_Vector::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous object
     *
     *  @param      op = source object
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void DataCopy(const CFMT_Vector<T>& op)
    {
        if (this == &op)
        {
            return;
        }

        t_FMT_Uint32	i;

        if (op.m_uiLength != m_uiLength)
        {
            DeleteBuffer();

            m_pBuf = new T[op.m_uiLength];
        }

        for (i = 0; i < op.m_uiLength; i++)
        {
            m_pBuf[i] = op.m_pBuf[i];
        }

        m_uiLength = op.m_uiLength;
    }


    // =====================================================================================
    //	CFMT_Vector::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous object
     *
     *  @param      op = source object
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][16/05/2021]
    // =====================================================================================

    void DataCopy(CFMT_List<T>& op)
    {
        t_FMT_Uint32    k;

        if (m_uiLength != op.GetLength())
        {
            DeleteBuffer();

            m_uiLength = op.GetLength();

            if (op.GetLength() == 0)
            {
                return;
            }

            m_pBuf = new T[op.GetLength()];
        }

        op.ToStart();

        for (k=0; k< op.GetLength(); k++)
        {
            m_pBuf[k] = (op>>1);
        }
    }


    // =====================================================================================
    //	CFMT_Vector::DeleteBuffer
    // -----------------------------------------------------------------------------------
    /**	Delete array buffer
     *
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void DeleteBuffer()
    {
        if (m_pBuf != FMTDEF_NULL)
        {
            delete[] m_pBuf;

            m_pBuf = FMTDEF_NULL;
            m_uiLength = 0;
        }
    }




public:

    // =====================================================================================
    //	CFMT_Vector::UpShift
    // -----------------------------------------------------------------------------------
    /**	Shift-up uiStep items starting from uiStart
     *
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void UpShift(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiStep)
    {
        if (uiStart >= m_uiLength)
        {
            throw CFMT_Exception(e_Return_InvalidParameter,this);
        }

        t_FMT_Uint32    i,j;

        for (i = uiStart, j = uiStart + uiStep; j < m_uiLength; i++, j++)
        {
            m_pBuf[i] = m_pBuf[j];
        }
    }


    // =====================================================================================
    //	CFMT_Vector::DownShift
    // -----------------------------------------------------------------------------------
    /**	Shift-down uiStep items starting from uiStart
     *
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void DownShift(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiStep)
    {
        if (uiStart > m_uiLength - 1)
        {
            throw CFMT_Exception(e_Return_InvalidParameter,this);
        }

        t_FMT_Int32     i,j;
        for (i = (t_FMT_Int32)m_uiLength - 1, j = (t_FMT_Int32)m_uiLength - uiStep -1; j >= (t_FMT_Int32)(uiStart); i--, j--)
        {
            m_pBuf[i] = m_pBuf[j];
        }
    }


    // =====================================================================================
    //	CFMT_Vector::Create
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiLength without intializing
    *
    *	@param		uiLength: array length
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void Create(t_FMT_Uint32 uiLength)
    {
        if (uiLength == 0)
        {
            throw CFMT_Exception(e_Return_InvalidSize, this);
        }

        DeleteBuffer();

        m_uiLength = uiLength;
        m_pBuf = new T[uiLength];
    }


    // =====================================================================================
    //	CFMT_Vector::Create
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiLength initializing with value
    *
    *	@param		uiLength: array length
    *	@param		value: initializing value
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void Create(t_FMT_Uint32 uiLength, const T& value)
    {
        if (uiLength == 0)
        {
            throw CFMT_Exception(e_Return_InvalidSize, this);
        }

        DeleteBuffer();

        t_FMT_Uint32    i;

        m_uiLength = uiLength;
        m_pBuf = new T[uiLength];

        for (i = 0; i < uiLength; i++)
        {
            m_pBuf[i] = value;
        }
    }


    // =====================================================================================
    //	CFMT_Vector::Create
    // -----------------------------------------------------------------------------------
    /**	Build the object from an array of uiLength items
    *
    *	@param		pVet: source array
    *	@param		uiLength: array length
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void Create(T* pVet, t_FMT_Uint32 uiLength)
    {
        if (uiLength == 0)
        {
            throw CFMT_Exception(e_Return_InvalidSize, this);
        }

        DeleteBuffer();

        t_FMT_Uint32    i;

        m_uiLength = uiLength;
        m_pBuf = new T[uiLength];

        for (i = 0; i < uiLength; i++)
        {
            m_pBuf[i] = pVet[i];
        }
    }


    // =====================================================================================
    //	CFMT_Vector::Recreate
    // -----------------------------------------------------------------------------------
    /**	Re-Build the object of uiLength items and copy from uiStart the original items
    *
    *	@param		uiLength: new array length
    *	@param		uiStart: starting copy
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void Recreate(t_FMT_Uint32 uiLength, t_FMT_Uint32 uiStart)
    {
        if (m_uiLength == 0)
        {
            Create(uiLength);

            return;
        }

        T*              pHBuf;
        t_FMT_Uint32    i,j;

        if (m_pBuf == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_InvalidParameter,this);
        }

        pHBuf = new T[uiLength];
        for (i = uiStart, j = 0; ((j < uiLength) && (i < m_uiLength)); i++, j++)
        {
            pHBuf[j] = m_pBuf[i];
        }

        DeleteBuffer();

        m_pBuf = pHBuf;
        m_uiLength = uiLength;
    }


    // =====================================================================================
    //	CFMT_Vector::Recreate
    // -----------------------------------------------------------------------------------
    /**	Re-Build the object of uiLength items and copy from uiStart the original items and
    *  initializing the others with value
    *
    *	@param		uiLength: new array length
    *	@param		uiStart: starting copy
    *	@param		value: initializing value
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void Recreate(t_FMT_Uint32 uiLength, t_FMT_Uint32 uiStart, const T& value)
    {
        if (m_uiLength == 0)
        {
            Create(uiLength, value);

            return;
        }

        T*              pHBuf;
        t_FMT_Uint32    i, j;
        t_FMT_Uint32    pos;

        if (m_pBuf == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_InvalidParameter,this);
        }

        pos = 0;
        pHBuf = new T[uiLength];
        for (i = uiStart, j = 0; ((j < uiLength) && (i < m_uiLength)); i++, j++)
        {
            pHBuf[j] = m_pBuf[i];
            pos++;
        }

        for (j = pos; (j < uiLength); j++)
        {
            pHBuf[j] = value;
        }

        DeleteBuffer();

        m_pBuf = pHBuf;
        m_uiLength = uiLength;
    }


    // =====================================================================================
    //	CFMT_Vector::GetLength
    // -----------------------------------------------------------------------------------
    /**	Get the length of the array
    *
    *	@return     Array length
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    t_FMT_Uint32 GetLength() const
    {
        return (m_uiLength);
    }


    // =====================================================================================
    //	CFMT_Vector::operator!
    // -----------------------------------------------------------------------------------
    /**	Get the length of the array
    *
    *	@return     Array length
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    t_FMT_Uint32 operator!() const
    {
        return (m_uiLength);
    }


    // =====================================================================================
    //	CFMT_Vector::operator[]
    // -----------------------------------------------------------------------------------
    /**	Get item of index uiIndex
    *
    *	@param      Item index
    *	@return     item of index uiIndex
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    T& operator[](t_FMT_Uint32 uiIndex) const
    {
        if (uiIndex >= m_uiLength)
        {
            throw CFMT_Exception(e_Return_OutOfRange, this);
        }

        return m_pBuf[uiIndex];
    }



    // =====================================================================================
    //	CFMT_Vector::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous object and return a reference to the vector
     *
     *  @param      op = source object (C-Style)
     *  @return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& operator=(const CFMT_Vector<T>& op)
    {
        DataCopy(op);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous list and return a reference to the vector
     *
     *  @param      op = source list
     *  @return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& operator=(CFMT_List<T>& op)
    {
        DataCopy(op);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::GetBUf
    // -----------------------------------------------------------------------------------
    /**	Return the array buffer pointer
     *
     *  @return     array buffer pointer
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][30/03/2018]
    // =====================================================================================

    T* GetBuf() const
    {
        return  m_pBuf;
    }


    // =====================================================================================
    //	CFMT_Vector::DeleteAll
    // -----------------------------------------------------------------------------------
    /**	Delete all list items and return a reference to the object
     *
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector& DeleteAll()
    {
        DeleteBuffer();

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::DeleteItems
    // -----------------------------------------------------------------------------------
    /**	Delete uiSize items from uiPos and return a reference to the object
     *
     *  @param      uiPos: starting position
     *  @param      uiSize: number of items to delete
     *  @param      bResize: FMTDEF_TRUE -> resize if needed
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector& DeleteItems(t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        UpShift(uiPos, uiSize);

        if (bResize)
        {
            t_FMT_Uint32        newsize;

            newsize = uiPos + FMTDEFM_MAX((((t_FMT_Int64)m_uiLength - uiPos) - uiSize), 0);

            Recreate(newsize, 0);
        }

        return (*this);
    }



    // =====================================================================================
    //	CFMT_Vector::AppendItem
    // -----------------------------------------------------------------------------------
    /**	Append a copy of op to the vector
    *
    *	@param      item to append
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void AppendItem(const T& op)
    {
        Recreate(m_uiLength+1, 0, op);
    }


    // =====================================================================================
    //	CFMT_Vector::operator+=
    // -----------------------------------------------------------------------------------
    /**	Append a copy of op to the vector
    *
    *	@param      item to append
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    void operator+=(const T& op)
    {
        Recreate(m_uiLength+1, 0, op);
    }


    // =====================================================================================
    //	CFMT_Vector::AppendList
    // -----------------------------------------------------------------------------------
    /**	Append a homogeneous list and return a reference to the vector
    *
    *	@param      list to join
    *	@return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& AppendList(CFMT_List<T>& op)
    {
        t_FMT_Uint32        k;
        t_FMT_Uint32        pos;

        pos = m_uiLength;

        Recreate(m_uiLength + op.GetLength(), 0);

        op.ToStart();
        for (k=0; k<op.GetLength(); k++)
        {
            m_pBuf[pos] = op>>1;
            pos++;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::AppendVector
    // -----------------------------------------------------------------------------------
    /**	Append a vector and return a reference to the vector
    *
    *	@param      vector to join
    *	@return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& AppendVector(CFMT_Vector<T>& op)
    {
        t_FMT_Uint32        k;
        t_FMT_Uint32        pos;

        pos = m_uiLength;

        Recreate(m_uiLength + op.GetLength(), 0);

        for (k=0; k<op.GetLength(); k++)
        {
            m_pBuf[pos] = op[k];
            pos++;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::operator&=
    // -----------------------------------------------------------------------------------
    /**	List concatenation; return a reference to the vector
    *
    *	@param      list to join
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& operator&=(CFMT_List<T>& op)
    {
        return AppendList(op);
    }


    // =====================================================================================
    //	CFMT_Vector::operator&=
    // -----------------------------------------------------------------------------------
    /**	Append a vector to the list and return a reference to the vector
    *
    *	@param      vector to join
    *	@return     list reference
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& operator&=(CFMT_Vector<T>& op)
    {
        return AppendVector(op);
    }


    // =====================================================================================
    //	CFMT_Vector::InsertItem
    // -----------------------------------------------------------------------------------
    /**	Insert uiSize copies of data at the uiPos position
    *
    *	@param      uiPos: insert index
    *	@param      data: item to add
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& InsertItems(t_FMT_Uint32 uiPos, const T& data, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (bResize)
        {
            Recreate(m_uiLength + uiSize, 0);
        }

        DownShift(uiPos, uiSize);

        t_FMT_Uint32        k;

        for (k=0; k<uiSize; k++)
        {
           m_pBuf[uiPos++] = data;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::InsertItems
    // -----------------------------------------------------------------------------------
    /**	Insert uiSize items from src array, starting from uiStart, to the current position
    *   and return a reference to the object
    *
    *	@param      uiPos: insert index
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& InsertItems(t_FMT_Uint32 uiPos, T* src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart = 0, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (bResize)
        {
            Recreate(m_uiLength + uiSize, 0);
        }

        DownShift(uiPos, uiSize);

        CopyItemsFrom(uiPos, src, uiStart, uiSize);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::InsertItems
    // -----------------------------------------------------------------------------------
    /**	Insert uiSize items from src list, starting from current position,
    *   to the current position and return a reference to the object
    *
    *	@param      uiPos: insert index
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T> InsertItems(t_FMT_Uint32 uiPos, CFMT_List<T> &src, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (bResize)
        {
            Recreate(m_uiLength + uiSize, 0);
        }

        DownShift(uiPos, uiSize);

        CopyItemsFrom(uiPos, src, uiSize);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::InsertItems
    // -----------------------------------------------------------------------------------
    /**	Insert uiSize items from src array, starting from uiStart, to the current position
    *   and return a reference to the object
    *
    *	@param      uiPos: insert index
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& InsertItems(t_FMT_Uint32 uiPos, CFMT_Vector<T>& src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart = 0, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (bResize)
        {
            Recreate(m_uiLength + uiSize, 0);
        }

        DownShift(uiPos, uiSize);

        CopyItemsFrom(uiPos, src, uiStart, uiSize);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::CopyItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items from src array, starting from uiStart to uiPos position
    *   and return a reference to the object
    *
    *	@param      uiPos: insert index
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& CopyItemsFrom(t_FMT_Uint32 uiPos, T* src, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (uiSize == 0)
        {
            return (*this);
        }

        if ((bResize) && (uiPos + uiSize > m_uiLength))
        {
            Recreate(uiPos+uiSize,0);
        }

        if (uiPos + uiSize > m_uiLength)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        t_FMT_Uint32 i,j;

        for (i = uiStart, j = uiPos; i < uiStart + uiSize; i++, j++)
        {
            m_pBuf[j] = (src[i]);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::CopyItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items from src array, starting from uiStart to uiPos position
    *   and return a reference to the object
    *
    *	@param      uiPos: insert index
    *	@param      src: source array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][21/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& CopyItemsFrom(t_FMT_Uint32 uiPos, CFMT_Vector<T>& src, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (uiSize == 0)
        {
            return (*this);
        }

        if ((bResize) && (uiPos + uiSize > m_uiLength))
        {
            Recreate(uiPos+uiSize,0);
        }

        if (uiPos + uiSize > m_uiLength)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        t_FMT_Uint32 i,j;

        for (i = uiStart, j = uiPos; i < uiStart + uiSize; i++, j++)
        {
            m_pBuf[j] = (src[i]);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::CopyItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items from src list, starting from its current position, to uiPos
    *   position and return a reference to the object
    *
    *	@param      uiPos: insert index
    *	@param      src: source list
    *	@param      uiSize: number of items to insert
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& CopyItemsFrom(t_FMT_Uint32 uiPos, CFMT_List<T> &src, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (uiSize == 0)
        {
            return (*this);
        }

        if ((bResize) && (uiPos + uiSize > m_uiLength))
        {
            Recreate(uiPos+uiSize,0);
        }

        if (uiPos + uiSize > m_uiLength)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        t_FMT_Uint32    k;
        t_FMT_Bool      bAgain;

        k = uiPos;
        bAgain = FMTDEF_TRUE;

        while (bAgain && (k < uiPos + uiSize))
        {
            m_pBuf[k] = src.CurItem();

            if (src.IsEnd())
            {
                bAgain = FMTDEF_FALSE;
            }
            else
            {
                src.Next();
                k++;
            }
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::CopyItemsTo
    // -----------------------------------------------------------------------------------
    /**	Copy uiSize items to src array, starting from current position to uiStart position
    *   of array
    *
    *	@param      uiPos: starting array position of destination
    *	@param      dest: destination array
    *	@param      uiSize: number of items to insert
    *	@param      uiStart: starting array position of source
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void CopyItemsTo(t_FMT_Uint32 uiPos, T* dest, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize)
    {
        t_FMT_Uint32	k;
        t_FMT_Uint32	j;
        t_FMT_Uint32	w;

        for (k = uiPos, j = uiStart, w = 0; (w < uiSize) && (j < m_uiLength); k++, j++, w++)
        {
            dest[k] = m_pBuf[j];
        }
    }


    // =====================================================================================
    //	CFMT_Vector::Fill
    // -----------------------------------------------------------------------------------
    /**	Fill uiSize items with tValue, to uiPos position and return a reference to the object
    *
    *	@param      uiPos: insert index
    *	@param      uiSize: number of items to fill
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& Fill(const T& tValue, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (uiSize==0)
        {
            return (*this);
        }

        if ((bResize) && (uiPos + uiSize > m_uiLength))
        {
            Recreate(uiPos + uiSize, 0);
        }

        if (uiPos + uiSize > m_uiLength)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        t_FMT_Uint32    i;

        for (i = uiPos; i < uiPos + uiSize; i++)
        {
            m_pBuf[i] = tValue;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::Fill
    // -----------------------------------------------------------------------------------
    /**	Fill all vector with tValue
    *
    *	@param      tValue: source value
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& Fill(const T& tValue)
    {
        t_FMT_Uint32    i;

        for (i = 0; i < m_uiLength; i++)
        {
            m_pBuf[i] = tValue;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::Extract
    // -----------------------------------------------------------------------------------
    /**	Extract a sub-vectors of uiNumItems items from uiPos
    *
    *	@param      dest: destination vector
    *	@param      uiPos: starting position
    *	@param      uiNumItems: number of items to extract
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void Extract(CFMT_Vector<T>& dest, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiNumItems)
    {
        dest.DeleteAll();

        t_FMT_Uint32        k;
        t_FMT_Uint32        j;

        dest.Create(uiNumItems);

        for (k=0, j=uiPos; (k<uiNumItems) && (j<m_uiLength); k++, j++)
        {
            dest.m_pBuf[k] = m_pBuf[j];
        }
    }


    // =====================================================================================
    //	CFMT_Vector::FindToEnd
    // -----------------------------------------------------------------------------------
    /**	Find the first item op starting from uiPos toward the end of the vector
    *
    *	@param      uiStart: starting position
    *	@param      op: object to find
    *	@param      puiPos: returned position
    *	@return     FMTDEF_TRUE if found
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    t_FMT_Bool FindToEnd(const T& op, t_FMT_Uint32 *puiPos, t_FMT_Uint32 uiStart)
    {
        t_FMT_Uint32        k;

        k = uiStart;

        while (k<m_uiLength)
        {
            if (m_pBuf[k] == op)
            {
                *puiPos = k;
                return FMTDEF_TRUE;
            }
            else
            {
                k++;
            }
        }

        return FMTDEF_FALSE;
    }


    // =====================================================================================
    //	CFMT_Vector::FindToStart
    // -----------------------------------------------------------------------------------
    /**	Find the first item op starting from uiPos toward the start of the vector
    *
    *	@param      uiStart: starting position
    *	@param      op: object to find
    *	@param      puiPos: returned position
    *	@return     FMTDEF_TRUE if found
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    t_FMT_Bool FindToStart(const T& op, t_FMT_Uint32 *puiPos, t_FMT_Uint32 uiStart)
    {
        t_FMT_Int32        k;

        k = uiStart;

        while (k>=0)
        {
            if (m_pBuf[k] == op)
            {
                *puiPos = k;
                return FMTDEF_TRUE;
            }
            else
            {
                k--;
            }
        }

        return FMTDEF_FALSE;
    }


    // =====================================================================================
    //	CFMT_Vector::operator==
    // -----------------------------------------------------------------------------------
    /**	Checks if two vectors are equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    t_FMT_Bool operator==(const CFMT_Vector<T>& op)
    {
        if (m_uiLength != op.m_uiLength)
        {
            return FMTDEF_FALSE;
        }

        t_FMT_Uint32        k;

        for (k=0; k<m_uiLength; k++)
        {
            if (m_pBuf[k] != op.m_pBuf[k])
            {
                return FMTDEF_FALSE;
            }
        }

        return FMTDEF_TRUE;
    }


    // =====================================================================================
    //	CFMT_Vector::operator!=
    // -----------------------------------------------------------------------------------
    /**	Checks if two vectors are not equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    t_FMT_Bool operator!=(const CFMT_Vector<T>& op)
    {
        return !(operator==(op));
    }


    // =====================================================================================
    //	CFMT_Vector::SwapItems
    // -----------------------------------------------------------------------------------
    /**	Swap the item dwA with dwB
    *
    *	@param      uiA: item 1 to swap
    *	@param      uiB: item 2 to swap
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    void SwapItems(t_FMT_Uint32 uiA, t_FMT_Uint32 uiB)
    {
        if (uiA > m_uiLength)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }
        if (uiB > m_uiLength)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        T   tTemp = m_pBuf[uiA];
        m_pBuf[uiA] = m_pBuf[uiB];
        m_pBuf[uiB] = tTemp;
    }


    // =====================================================================================
    //	CFMT_Vector::Sort
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
        if (m_uiLength==0)
        {
            throw CFMT_Exception(e_Return_InvalidParameter,this);
        }

        if (m_uiLength < 2)
        {
            return;
        }

        t_FMT_Uint32    i;
        t_FMT_Bool      bOrdered;

		bOrdered = FMTDEF_FALSE;

        while (!bOrdered)
        {
            for (i = 1; i < m_uiLength; i++)
            {
                if ((pCompareFunct(m_pBuf[i], m_pBuf[i-1])>0 && !bOrder) ||
                    (pCompareFunct(m_pBuf[i], m_pBuf[i-1])<0 && bOrder))
                {
                    SwapItems(i, i-1);

                    bOrdered = FMTDEF_FALSE;
                }
            }
        }
    }


    // =====================================================================================
    //	CFMT_Vector::ExtractInvertVector
    // -----------------------------------------------------------------------------------
    /**	Extract a vector with inverted items order
    *
    *	@param      uiStart: starting items
    *	@param      uiNumItems: number of items to invert
    *	@return     inverted vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    CFMT_Vector<T> ExtractInvertVector(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiNumItems)
    {
        if (uiNumItems==0)
        {
            return CFMT_Vector<T>();
        }

        CFMT_Vector<T>  v(uiNumItems);
        t_FMT_Uint32    k;
        t_FMT_Uint32    w;

        for (k=0, w=uiStart; (k<uiNumItems) && (w<m_uiLength); k++, w++)
        {
            v[uiNumItems-k-1] = m_pBuf[w];
        }

        return v;
    }


    // =====================================================================================
    //	CFMT_Vector::InvertItemsOrder
    // -----------------------------------------------------------------------------------
    /**	Invert the items order
    *
    *	@param      uiStart: starting items
    *	@param      uiNumItems: number of items to invert
    *	@return     reference to the inverted vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& InvertItemsOrder(t_FMT_Uint32 uiStart, t_FMT_Uint32 uiNumItems)
    {
        if (uiNumItems==0)
        {
            return (*this);
        }

        t_FMT_Uint32    k;
        t_FMT_Uint32    w;

        for (k=0, w=uiStart; (k<uiNumItems/2) && (w<m_uiLength); k++, w++)
        {
            SwapItems(uiStart+uiNumItems-k-1, w);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Vector::InvertItemsOrder
    // -----------------------------------------------------------------------------------
    /**	Invert the items order of all the vector
    *
    *	@return     reference to the inverted vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    CFMT_Vector<T>& InvertItemsOrder()
    {
        return InvertItemsOrder(0, m_uiLength);
    }


    // =====================================================================================
    //	CFMT_Buffer::operator<<
    // -----------------------------------------------------------------------------------
    /**	Serializes a vector into the buffer
     *
     *  @param      buf: destination buffer
     *  @param      vector: source vector
     *  @return     reference of the buffer
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Vector<T>& vector)
    {
        t_FMT_Uint32	k;

        buf << vector.m_uiLength;

        for (k=0; k<vector.m_uiLength; k++)
        {
            buf << vector.m_pBuf[k];
        }

        return buf;
    }


    // =====================================================================================
    //	CFMT_Buffer::operator>>
    // -----------------------------------------------------------------------------------
    /**	Serializes a vector from the buffer
     *
     *  @param      buf: source buffer
     *  @param      vector: destination vector
     *  @return     reference of the buffer
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Vector<T>& vector)
    {
        t_FMT_Uint32	k, uiSize;

        buf >> uiSize;

        if (uiSize != vector.m_uiLength)
        {
            vector.Create(uiSize);
        }

        for (k=0; k<uiSize; k++)
        {
            buf >> vector.m_pBuf[k];
        }

        return buf;
    }


};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_OrderedVector
// *************************************************************************************
// *************************************************************************************

//! Ordered linked vector container

template <class T> class CFMT_OrderedVector : public CFMT_Vector<T>
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
    CFMT_OrderedVector() {}

    //! Build an array of uiLength without intializing
    CFMT_OrderedVector(t_FMT_Uint32 uiLength) : CFMT_Vector<T>(uiLength) {}

    //! Copy constructor
    CFMT_OrderedVector(const CFMT_OrderedVector& op) : CFMT_Vector<T>(op) {}

    //! Build an array of uiLength initializing with value
    CFMT_OrderedVector(t_FMT_Uint32 uiLength, const T& value) : CFMT_Vector<T>(uiLength, value) {}

    //! Build the object from an array of uiLength items
    CFMT_OrderedVector(T* pVet, t_FMT_Uint32 uiLength) : CFMT_Vector<T>(pVet, uiLength) {}


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
    //	CFMT_OrderedVector::Sort
    // -----------------------------------------------------------------------------------
    /**	Sort the list and return a reference to it
    *
    *	@param      bOrder: FMTDEF_TRUE, ascending
    *	@return     reference to the sorted vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    CFMT_OrderedVector& Sort(t_FMT_Bool bOrder)
    {
        CFMT_Vector<T>::Sort(&Compare, bOrder);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_OrderedVector::Max
    // -----------------------------------------------------------------------------------
    /**	Return the maximum of the vector
    *
    *	@return     maximum value
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    T& Max()
    {
        t_FMT_Uint32            k;
        t_FMT_Uint32            uiMax;

        uiMax = 0;

        for (k=1; k<this->m_uiLength; k++)
        {
            if (this->m_pBuf[k] > this->m_pBuf[uiMax])
            {
                uiMax = k;
            }
        }

        return this->m_pBuf[uiMax];
    }


    // =====================================================================================
    //	CFMT_OrderedVector::Min
    // -----------------------------------------------------------------------------------
    /**	Return the minimum of the vector
    *
    *	@return     minimum value
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][24/03/2018]
    // =====================================================================================

    T& Min()
    {
        t_FMT_Uint32            k;
        t_FMT_Uint32            uiMin;

        uiMin = 0;

        for (k=1; k<this->m_uiLength; k++)
        {
            if (this->m_pBuf[k] < this->m_pBuf[uiMin])
            {
                uiMin = k;
            }
        }

        return this->m_pBuf[uiMin];
    }

};


#endif

