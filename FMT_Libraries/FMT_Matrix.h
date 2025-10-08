// =====================================================================================
/**
 * @file					CFMT_Matrix.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					03/04/2018
 * @brief					Template class for 2D-matrix
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][03/04/2018]
 */
// =====================================================================================

#ifndef FMTDEF_MATRIX_H
#define FMTDEF_MATRIX_H

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


//template <class T> class CFMT_List;
template <class T> class CFMT_Vector;

using namespace FMT;


// =====================================================================================
//  DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Template Class CFMT_Matrix
// *************************************************************************************
// *************************************************************************************

template <class T> class CFMT_Matrix : public CFMT_Object
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

    //!	Data buffer
    T*				m_pBuf;

    //!	Number of rows
    t_FMT_Uint32    m_uiNumRows;

    //!	Number of columns
    t_FMT_Uint32    m_uiNumColumns;


public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    // =====================================================================================
    //	CFMT_Matrix::CFMT_Matrix
    // -----------------------------------------------------------------------------------
    /**	Empty constructor
    *
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    CFMT_Matrix()
	{
        m_uiNumRows = 0;
        m_uiNumColumns = 0;
        m_pBuf = FMTDEF_NULL;
	}


    // =====================================================================================
    //	CFMT_Matrix::CFMT_Matrix
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiRows x uiCols without initializing
    *
    *	@param		uiRows: number of rows
    *	@param		uiCols: number of columns
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    CFMT_Matrix(t_FMT_Uint32 uiRows, t_FMT_Uint32 uiCols)
	{
        m_uiNumRows = 0;
        m_uiNumColumns = 0;
        m_pBuf = FMTDEF_NULL;

        Create(uiRows, uiCols);
	}


    // =====================================================================================
    //	CFMT_Matrix::CFMT_Matrix
    // -----------------------------------------------------------------------------------
    /**	Copy constructor
     *
     *  @param      op: source
     *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    CFMT_Matrix(const CFMT_Matrix<T>& op)
	{
        m_uiNumRows = 0;
        m_uiNumColumns = 0;
        m_pBuf = FMTDEF_NULL;

        DataCopy(op);
	}


    // =====================================================================================
    //	CFMT_Matrix::CFMT_Matrix
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiRows x uiCols initializing with value
    *
    *	@param		uiRows: number of rows
    *	@param		uiCols: number of columns
    *	@param		value: initializing value
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    CFMT_Matrix(t_FMT_Uint32 uiRows, t_FMT_Uint32 uiCols, const T& value)
    {
        m_uiNumRows = 0;
        m_uiNumColumns = 0;
        m_pBuf = FMTDEF_NULL;

        Create(uiRows, uiCols, value);
    }


    // =====================================================================================
    //	CFMT_Matrix::~CFMT_Matrix
    // -----------------------------------------------------------------------------------
    /**	Destructor
    *
    *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    ~CFMT_Matrix()
	{
		DeleteBuffer();
	}


// =====================================================================================
//	FUNCTIONS
// =====================================================================================

protected:

    // =====================================================================================
    //	CFMT_Matrix::DataCopy
    // -----------------------------------------------------------------------------------
    /**	Copy from an homogeneous object
     *
     *  @param      op = source object (C-Style)
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void DataCopy(const CFMT_Matrix<T>& op)
    {
        t_FMT_Uint32	d;
        t_FMT_Uint32	i;

        d = op.m_uiNumRows * op.m_uiNumColumns;

        if (d != (m_uiNumRows * m_uiNumColumns))
        {
            delete[] m_pBuf;
            m_pBuf = new T[d];
        }

        for (i=0; i<d; i++)
        {
            m_pBuf[i] = op.m_pBuf[i];
        }

        m_uiNumRows = op.m_uiNumRows;
        m_uiNumColumns = op.m_uiNumColumns;
    }


    // =====================================================================================
    //	CFMT_Matrix::DeleteBuffer
    // -----------------------------------------------------------------------------------
    /**	Delete array buffer
     *
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void DeleteBuffer()
    {
        if (m_pBuf != FMTDEF_NULL)
        {
            delete[] m_pBuf;

            m_pBuf = FMTDEF_NULL;
            m_uiNumColumns = 0;
            m_uiNumRows = 0;
        }
    }


    #if 0

    // =====================================================================================
    //	CFMT_Matrix::UpShift
    // -----------------------------------------------------------------------------------
    /**	Shift-up uiStep items starting from uiStart
     *
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
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
    //	CFMT_Matrix::DownShift
    // -----------------------------------------------------------------------------------
    /**	Shift-down uiStep items starting from uiStart
     *
     *  @return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
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
#endif

public:

    // =====================================================================================
    //	CFMT_Matrix::Create
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiRows x uiCols without initializing
    *
    *	@param		uiRows: number of rows
    *	@param		uiCols: number of columns
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void Create(t_FMT_Uint32 uiRows, t_FMT_Uint32 uiCols)
    {
        if ((uiRows == 0) || (uiCols == 0))
        {
            throw CFMT_Exception(e_Return_InvalidSize, this);
        }

        DeleteBuffer();

        m_pBuf = new T[uiRows * uiCols];
        m_uiNumColumns = uiCols;
        m_uiNumRows = uiRows;
    }


    // =====================================================================================
    //	CFMT_Matrix::Create
    // -----------------------------------------------------------------------------------
    /**	Build an object of uiRows x uiCols initializing with value
    *
    *	@param		uiRows: number of rows
    *	@param		uiCols: number of columns
    *	@param		value: initializing value
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void Create(t_FMT_Uint32 uiRows, t_FMT_Uint32 uiCols, const T& value)
    {
        if ((uiRows == 0) || (uiCols == 0))
        {
            throw CFMT_Exception(e_Return_InvalidSize, this);
        }

        t_FMT_Uint32    i;

        DeleteBuffer();

        m_pBuf = new T[uiRows * uiCols];
        m_uiNumColumns = uiCols;
        m_uiNumRows = uiRows;

        for (i=0; i < uiRows*uiCols; i++)
        {
            m_pBuf[i] = value;
        }
    }


    // =====================================================================================
    //	CFMT_Matrix::Recreate
    // -----------------------------------------------------------------------------------
    /**	Re-Build the object of uiRows x uiCols items and copy the original items from
    *   uiR1 x uiC1
    *
    *	@param		uiRows: new number of rows
    *	@param		uiCols: new number of columns
    *	@param		uiR1: starting row for copy
    *	@param		uiC1: starting column for copy
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void Recreate(t_FMT_Uint32 uiRows, t_FMT_Uint32 uiCols, t_FMT_Uint32 uiR1, t_FMT_Uint32 uiC1)
    {
        T*              pHBuf;
        t_FMT_Uint32    i;
        t_FMT_Uint32    j;
        t_FMT_Uint32    k;
        t_FMT_Uint32    w;

        if ((m_uiNumRows == 0) || (m_uiNumColumns == 0))
        {
            Create(uiRows, uiCols);
            return;
        }

        pHBuf = new T[uiRows * uiCols];

        for (i = uiR1, k = 0; i< FMTDEFM_MIN(uiR1 + uiRows, m_uiNumRows); i++, k++)
        {
            for (j = uiC1, w = 0; j <FMTDEFM_MIN(uiC1 + uiCols, m_uiNumColumns); j++, w++)
            {
                pHBuf[k * uiCols + w] = m_pBuf[i * m_uiNumColumns + j];
            }
        }

        DeleteBuffer();

        m_pBuf = pHBuf;

        m_uiNumRows = uiRows;
        m_uiNumColumns = uiCols;
    }


    // =====================================================================================
    //	CFMT_Matrix::Recreate
    // -----------------------------------------------------------------------------------
    /**	Re-Build the object of uiRows x uiCols items and copy the original items from
    *   uiR1 x uiC1 and initializing the others with value
    *
    *	@param		uiRows: new number of rows
    *	@param		uiCols: new number of columns
    *	@param		uiR1: starting row for copy
    *	@param		uiC1: starting column for copy
    *	@param		value: initializing value
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void Recreate(t_FMT_Uint32 uiRows, t_FMT_Uint32 uiCols, t_FMT_Uint32 uiR1, t_FMT_Uint32 uiC1, const T& value)
    {
        T*              pHBuf;
        t_FMT_Uint32    i;
        t_FMT_Uint32    j;
        t_FMT_Uint32    k;
        t_FMT_Uint32    w;

        if ((m_uiNumRows == 0) || (m_uiNumColumns == 0))
        {
            Create(uiRows, uiCols);
            return;
        }

        pHBuf = new T[uiRows * uiCols];

        for (i = uiR1, k = 0; i< FMTDEFM_MIN(uiR1 + uiRows, m_uiNumRows); i++, k++)
        {
            for (j = uiC1, w = 0; j <FMTDEFM_MIN(uiC1 + uiCols, m_uiNumColumns); j++, w++)
            {
                pHBuf[k * uiCols + w] = m_pBuf[i * m_uiNumColumns + j];
            }
        }

        for (j = 0; (j < uiRows); j++)
        {
            for (k = m_uiNumColumns; (k < uiCols); k++)
            {
                pHBuf[j * uiCols + k] = value;
            }
        }

        for (j = m_uiNumRows; (j < uiRows); j++)
        {
            for (k = 0; (k < uiCols); k++)
            {
                pHBuf[j * uiCols + k] = value;
            }
        }


        DeleteBuffer();

        m_pBuf = pHBuf;

        m_uiNumRows = uiRows;
        m_uiNumColumns = uiCols;
    }


    // =====================================================================================
    //	CFMT_Matrix::GetNumRows
    // -----------------------------------------------------------------------------------
    /**	Get the number of rows
    *
    *	@return     number of rows
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    t_FMT_Uint32 GetNumRows() const
    {
        return (m_uiNumRows);
    }


    // =====================================================================================
    //	CFMT_Matrix::GetNumColumns
    // -----------------------------------------------------------------------------------
    /**	Get the number of columns
    *
    *	@return     number of columns
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    t_FMT_Uint32 GetNumColumns() const
    {
        return (m_uiNumColumns);
    }


    // =====================================================================================
    //	CFMT_Matrix::operator[]
    // -----------------------------------------------------------------------------------
    /**	Return a pointer of the row of index uiIndex
    *
    *	@param      uiIndex: row index
    *	@return     pointer of the row
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    T* operator[](t_FMT_Uint32 uiIndex)
    {
        return (m_pBuf + uiIndex * m_uiNumColumns);
    }


    // =====================================================================================
    //	CFMT_Matrix::GetRow
    // -----------------------------------------------------------------------------------
    /**	Copy a matrix row into a vector
    *
    *	@param      uiRow: row index
    *	@param      v: returned vector
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void GetRow(t_FMT_Uint32 uiRow, CFMT_Vector<T>& v)
    {
        t_FMT_Uint32        k;

        v.Create(m_uiNumColumns);

        for (k=0; k<m_uiNumColumns; k++)
        {
            v[k] = (*this)[uiRow][k];
        }
    }


    // =====================================================================================
    //	CFMT_Matrix::GetRow
    // -----------------------------------------------------------------------------------
    /**	Copy a matrix row into a vector
    *
    *	@param      uiRow: row index
    *	@param      pV: returned vector
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void GetRow(t_FMT_Uint32 uiRow, T* pV)
    {
        t_FMT_Uint32        k;

        for (k=0; k<m_uiNumColumns; k++)
        {
            pV[k] = (*this)[uiRow][k];
        }
    }


    // =====================================================================================
    //	CFMT_Matrix::GetColumn
    // -----------------------------------------------------------------------------------
    /**	Copy a matrix column into a vector
    *
    *	@param      uiCol: column index
    *	@param      v: returned vector
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void GetColumn(t_FMT_Uint32 uiCol, CFMT_Vector<T>& v)
    {
        t_FMT_Uint32        k;

        v.Create(m_uiNumRows);

        for (k=0; k<m_uiNumRows; k++)
        {
            v[k] = (*this)[k][uiCol];
        }
    }


    // =====================================================================================
    //	CFMT_Matrix::GetColumn
    // -----------------------------------------------------------------------------------
    /**	Copy a matrix column into a vector
    *
    *	@param      uiCol: column index
    *	@param      pV: returned vector
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    void GetColumn(t_FMT_Uint32 uiCol, T* pV)
    {
        t_FMT_Uint32        k;

        for (k=0; k<m_uiNumRows; k++)
        {
            pV[k] = (*this)[k][uiCol];
        }
    }


    // =====================================================================================
    //	CFMT_Matrix::Extract
    // -----------------------------------------------------------------------------------
    /**	Extract a sub-matrix of uiNumRows x uiNumCols items from uiStartRow x uiStartCol
    *
    *	@param      dest: destination vector
    *	@param      uiNumRows: number of destination rows
    *	@param      uiNumCols: number of destination columns
    *	@param      uiStartRow: source starting row
    *	@param      uiStartCol: source starting column
    *	@return     void
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    void Extract(CFMT_Matrix<T>& dest, t_FMT_Uint32 uiNumRows, t_FMT_Uint32 uiNumCols, t_FMT_Uint32 uiStartRow, t_FMT_Uint32 uiStartCol)
    {
        dest.DeleteAll();

        t_FMT_Uint32        dr;
        t_FMT_Uint32        dc;
        t_FMT_Uint32        sr;
        t_FMT_Uint32        sc;

        dest.Create(uiNumRows, uiNumCols);

        for (dr=0, sr=uiStartRow; (dr<uiNumRows) && (sr<m_uiNumRows); dr++, sr++)
        {
            for (dc=0, sc=uiStartCol; (dc<uiNumCols) && (sc<m_uiNumColumns); dc++, sc++)
            {
                dest[dr][dc] = m_pBuf[sr*m_uiNumColumns + sc];
            }
        }
    }


    // =====================================================================================
    //	CFMT_Matrix::operator=
    // -----------------------------------------------------------------------------------
    /**	Assignment from an homogeneous object and return a reference to the vector
     *
     *  @param      op = source object (C-Style)
     *  @return     reference to the vector
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    CFMT_Matrix<T>& operator=(const CFMT_Matrix<T>& op)
    {
        DataCopy(op);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::ShiftRows
    // -----------------------------------------------------------------------------------
    /**	Shifts uiNumRows rows starting from uiStartRow, to the bottom if bDir=FMTDEF_TRUE,
     *  otherwise, to the top.
     *
     *  @param      uiStartRow: starting row
     *  @param      uiNumRows: number of rows to shift
     *  @param      bDir: FMTDEF_TRUE = to the bottom
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& ShiftRows(t_FMT_Uint32 uiStartRow, t_FMT_Uint32 uiNumRows, t_FMT_Bool bDir = FMTDEF_TRUE)
    {
        if (uiNumRows == 0)
        {
            return (*this);
        }

        if (bDir)
        {
            if ((uiStartRow + uiNumRows > m_uiNumRows - 1) || (uiNumRows == 0))
            {
                return (*this);
            }

            t_FMT_Uint32 uiShift, uiDest;
            t_FMT_Uint32 j, i;

            uiDest = uiStartRow + uiNumRows;
            uiShift = m_uiNumRows - uiDest;

            T* pST = m_pBuf + (uiStartRow + uiShift)*m_uiNumColumns - 1;
            T* pDT = m_pBuf + m_uiNumRows * m_uiNumColumns -1;

            for (j = 0; j < uiShift; j++)
            {
                for (i = 0; i < m_uiNumColumns; i++)
                {
                    (*pDT--) = (*pST--);

                }
            }
        }
        else
        {
            if (uiStartRow >= m_uiNumRows)
            {
                return (*this);
            }

            t_FMT_Uint32 j, i;

            if (uiNumRows > uiStartRow)
            {
                uiNumRows = uiStartRow;
            }

            T* pDT = m_pBuf + (uiStartRow - uiNumRows)*m_uiNumColumns;
            T* pST = m_pBuf + uiStartRow*m_uiNumColumns;

            for (j=0; j<m_uiNumRows - uiStartRow; j++)
            {
                for (i=0; i<m_uiNumColumns; i++)
                {
                    (*pDT++) = (*pST++);
                }
            }
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::ShiftColumns
    // -----------------------------------------------------------------------------------
    /**	Shifts uiNumCols columns starting from uiStartCol, to the right if bDir=FMTDEF_TRUE,
     *  otherwise, to the left.
     *
     *  @param      uiStartRow: starting row
     *  @param      uiNumRows: number of rows to shift
     *  @param      bDir: FMTDEF_TRUE = to the bottom
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& ShiftColumns(t_FMT_Uint32 uiStartCol, t_FMT_Uint32 uiNumCols, t_FMT_Bool bDir = FMTDEF_TRUE)
    {
        if (uiNumCols==0)
        {
            return (*this);
        }

        if (bDir)
        {
            if ((uiStartCol + uiNumCols > m_uiNumColumns - 1) || (uiNumCols == 0))
            {
                return (*this);
            }

            t_FMT_Uint32 uiShift,uiDest;
            t_FMT_Uint32 j, i;

            uiDest = uiStartCol + uiNumCols;
            uiShift = m_uiNumColumns - uiDest;

            T* pST = m_pBuf + (m_uiNumRows -1 )*m_uiNumColumns + uiStartCol + uiShift - 1;
            T* pDT = m_pBuf + m_uiNumRows*m_uiNumColumns - 1;

            for (j=0; j<m_uiNumRows; j++)
            {
                for (i=0; i<uiShift; i++)
                {
                    (*pDT) = (*pST);
                    pDT--;
                    pST--;
                }

                pST -= (m_uiNumColumns - uiShift);
                pDT -= (m_uiNumColumns - uiShift);
            }
        }
        else
        {
            t_FMT_Uint32 uiShift;

            if (uiStartCol >= m_uiNumColumns)
            {
                return (*this);
            }

            t_FMT_Uint32 j, i;

            if (uiNumCols>uiStartCol)
            {
                uiNumCols=uiStartCol;
            }

            T* pST =m_pBuf + uiStartCol;
            T* pDT =m_pBuf + uiStartCol - uiNumCols;

            uiShift = m_uiNumColumns - uiStartCol;

            for (j=0; j<m_uiNumRows; j++)
            {
                for (i=0; i<uiShift; i++)
                {
                    (*pDT) = (*pST);
                    pDT++;
                    pST++;
                }

                pST += (m_uiNumColumns - uiShift);
                pDT += (m_uiNumColumns - uiShift);
            }
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::DeleteAll
    // -----------------------------------------------------------------------------------
    /**	Delete all list items and return a reference to the object
     *
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix& DeleteAll()
    {
        DeleteBuffer();

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::DeleteColumn
    // -----------------------------------------------------------------------------------
    /**	Delete a column from the matrix
     *
     *  @param      uiCol: column index to delete
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& DeleteColumn(t_FMT_Uint32 uiCol)
    {
        return DeleteColumns(uiCol, 1);
    }


    // =====================================================================================
    //	CFMT_Matrix::DeleteColumns
    // -----------------------------------------------------------------------------------
    /**	Delete a uiNumCols from the matrix starting from uiStartCol
     *
     *  @param      uiStartCol: starting column for deletion
     *  @param      uiNumCols: number of columns to delete
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& DeleteColumns(t_FMT_Uint32 uiStartCol, t_FMT_Uint32 uiNumCols)
    {
        if (uiStartCol >= m_uiNumRows)
        {
            return (*this);
        }

        if (uiNumCols > m_uiNumColumns - uiStartCol)
        {
            uiNumCols = m_uiNumColumns - uiStartCol;
        }

        ShiftColumns(uiStartCol + uiNumCols, uiNumCols, FMTDEF_FALSE);

        Recreate(m_uiNumRows, m_uiNumColumns - uiNumCols, 0, 0);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::DeleteRow
    // -----------------------------------------------------------------------------------
    /**	Delete a row from the matrix
     *
     *  @param      uiRow: row index to delete
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& DeleteRow(t_FMT_Uint32 uiRow)
    {
        return DeleteRows(uiRow, 1);
    }


    // =====================================================================================
    //	CFMT_Matrix::DeleteRows
    // -----------------------------------------------------------------------------------
    /**	Delete uiNumRows rows from the matrix starting from uiStartRow
     *
     *  @param      uiStartRow: starting row for deletion
     *  @param      uiNumRows: number of rows to delete
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& DeleteRows(t_FMT_Uint32 uiStartRow, t_FMT_Uint32 uiNumRows)
    {
        if (uiStartRow >= m_uiNumRows)
        {
            return (*this);
        }

        if (uiNumRows > m_uiNumRows - uiStartRow)
        {
            uiNumRows = m_uiNumRows - uiStartRow;
        }

        ShiftRows(uiStartRow + uiNumRows, uiNumRows, FMTDEF_FALSE);

        Recreate(m_uiNumRows - uiNumRows, m_uiNumColumns, 0, 0);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::InsertRowsFrom
    // -----------------------------------------------------------------------------------
    /**	Insert uiNumRows rows from uiStartRow initializing them with tValue
     *
     *  @param      uiStartRow: starting row for insertion
     *  @param      uiNumRows: number of rows to insert
     *  @param      tValue: initializing value
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& InsertRowsFrom(t_FMT_Uint32 uiStartRow, t_FMT_Uint32 uiNumRows, T tValue)
    {
        Recreate(m_uiNumRows + uiNumRows, m_uiNumColumns, 0, 0);
        ShiftRows(uiStartRow, uiNumRows);

        return FillRows(uiStartRow, uiNumRows, tValue);
    }


    // =====================================================================================
    //	CFMT_Matrix::InsertRowFroms
    // -----------------------------------------------------------------------------------
    /**	Insert uiNumRows rows from uiStartRow initializing them with the vector v
     *
     *  @param      uiStartRow: starting row for insertion
     *  @param      uiNumRows: number of rows to insert
     *  @param      v: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& InsertRowsFrom(t_FMT_Uint32 uiStartRow, t_FMT_Uint32 uiNumRows, CFMT_Vector<T>& v)
    {
        t_FMT_Uint32        k;

        Recreate(m_uiNumRows + uiNumRows, m_uiNumColumns, 0, 0);
        ShiftRows(uiStartRow, uiNumRows);

        for (k=0; k<uiNumRows; k++)
        {
            CopyRowItemsFrom(uiStartRow+k, 0, v, 0, m_uiNumColumns, FMTDEF_FALSE);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::InsertRowFroms
    // -----------------------------------------------------------------------------------
    /**	Insert uiNumRows rows from uiStartRow initializing them with the vector pV
     *
     *  @param      uiStartRow: starting row for insertion
     *  @param      uiNumRows: number of rows to insert
     *  @param      pV: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& InsertRowsFrom(t_FMT_Uint32 uiStartRow, t_FMT_Uint32 uiNumRows, T *pV)
    {
        t_FMT_Uint32        k;

        Recreate(m_uiNumRows + uiNumRows, m_uiNumColumns, 0, 0);
        ShiftRows(uiStartRow, uiNumRows);

        for (k=0; k<uiNumRows; k++)
        {
            CopyRowItemsFrom(uiStartRow+k, 0, pV, 0, m_uiNumColumns, FMTDEF_FALSE);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::AppendRows
    // -----------------------------------------------------------------------------------
    /**	Append a row initializing them the vector v
     *
     *  @param      uiNumRows: number of rows to append
     *  @param      v: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& AppendRows(t_FMT_Uint32 uiNumRows, CFMT_Vector<T>& v)
    {
        return InsertRowsFrom(m_uiNumRows, uiNumRows, v);
    }


    // =====================================================================================
    //	CFMT_Matrix::AppendRows
    // -----------------------------------------------------------------------------------
    /**	Append a row initializing them the vector pV
     *
     *  @param      uiNumRows: number of rows to append
     *  @param      pV: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& AppendRows(t_FMT_Uint32 uiNumRows,  T *pV)
    {
        return InsertRowsFrom(m_uiNumRows, uiNumRows, pV);
    }


    // =====================================================================================
    //	CFMT_Matrix::AppendRows
    // -----------------------------------------------------------------------------------
    /**	Appends uiNumRows rows initializing them with tValue
     *
     *  @param      uiNumRows: number of rows to append
     *  @param      tValue: initializing value
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& AppendRows(t_FMT_Uint32 uiNumRows, T tValue)
    {
        return InsertRowsFrom(m_uiNumRows, uiNumRows, tValue);
    }


    // =====================================================================================
    //	CFMT_Matrix::InsertColumnsFrom
    // -----------------------------------------------------------------------------------
    /**	Insert uiNumCols columns from uiStartCol initializing them with tValue
     *
     *  @param      uiStartCol: starting column for insertion
     *  @param      uiNumCols: number of columns to insert
     *  @param      tValue: initializing value
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& InsertColumnsFrom(t_FMT_Uint32 uiStartCol, t_FMT_Uint32 uiNumCols, T tValue)
    {
        Recreate(m_uiNumRows, m_uiNumColumns+uiNumCols, 0, 0);
        ShiftColumns(uiStartCol, uiNumCols);

        return FillColumns(uiStartCol, uiNumCols, tValue);
    }


    // =====================================================================================
    //	CFMT_Matrix::InsertColumnsFrom
    // -----------------------------------------------------------------------------------
    /**	Insert uiNumCols columns from uiStartCol initializing them with v vector
     *
     *  @param      uiStartCol: starting column for insertion
     *  @param      uiNumCols: number of columns to insert
     *  @param      v: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& InsertColumnsFrom(t_FMT_Uint32 uiStartCol, t_FMT_Uint32 uiNumCols, CFMT_Vector<T>& v)
    {
        t_FMT_Uint32        k;

        Recreate(m_uiNumRows, m_uiNumColumns+uiNumCols, 0, 0);
        ShiftColumns(uiStartCol, uiNumCols);

        for (k=0; k<uiNumCols; k++)
        {
            CopyColumnItemsFrom(0, uiStartCol+k, v, 0, m_uiNumRows, FMTDEF_FALSE);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::InsertColumnsFrom
    // -----------------------------------------------------------------------------------
    /**	Insert uiNumCols columns from uiStartCol initializing them with pV vector
     *
     *  @param      uiStartCol: starting column for insertion
     *  @param      uiNumCols: number of columns to insert
     *  @param      pV: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& InsertColumnsFrom(t_FMT_Uint32 uiStartCol, t_FMT_Uint32 uiNumCols, T *pV)
    {
        t_FMT_Uint32        k;

        Recreate(m_uiNumRows, m_uiNumColumns+uiNumCols, 0, 0);
        ShiftColumns(uiStartCol, uiNumCols);

        for (k=0; k<uiNumCols; k++)
        {
            CopyColumnItemsFrom(0, uiStartCol+k, pV, 0, m_uiNumRows, FMTDEF_FALSE);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::AppendColumns
    // -----------------------------------------------------------------------------------
    /**	Insert uiNumCols columns initializing them with tValue
     *
     *  @param      uiNumCols: number of columns to insert
     *  @param      tValue: initializing value
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& AppendColumns(t_FMT_Uint32 uiNumCols, T tValue)
    {
        return InsertColumnsFrom(m_uiNumColumns, uiNumCols, tValue);
    }


    // =====================================================================================
    //	CFMT_Matrix::AppendColumns
    // -----------------------------------------------------------------------------------
    /**	Append uiNumCols columns initializing them the vector v
     *
     *  @param      uiNumCols: number of columns to append
     *  @param      v: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& AppendColumns(t_FMT_Uint32 uiNumCols, CFMT_Vector<T>& v)
    {
        return InsertColumnsFrom(m_uiNumColumns, uiNumCols, v);
    }


    // =====================================================================================
    //	CFMT_Matrix::AppendColumns
    // -----------------------------------------------------------------------------------
    /**	Append uiNumCols columns initializing them the vector pV
     *
     *  @param      uiNumCols: number of columns to append
     *  @param      pV: initializing vector
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    CFMT_Matrix& AppendColumns(t_FMT_Uint32 uiNumCols,  T *pV)
    {
        return InsertColumnsFrom(m_uiNumColumns, uiNumCols, pV);
    }


    // =====================================================================================
    //	CFMT_Matrix::Fill
    // -----------------------------------------------------------------------------------
    /**	Fill all matrix with tValue
    *
    *	@param      tValue: source value
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix<T>& Fill(const T& tValue)
    {
        t_FMT_Uint32    i;

        for (i = 0; i < m_uiNumColumns * m_uiNumRows; i++)
        {
            m_pBuf[i] = tValue;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::FillRow
    // -----------------------------------------------------------------------------------
    /**	Fill all row items with tValue
    *
    *	@param      uiRow: row index
    *	@param      tValue: source value
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix<T>& FillRow(t_FMT_Uint32 uiRow, const T& tValue)
    {
        t_FMT_Uint32    i;

        for (i = 0; i < m_uiNumColumns; i++)
        {
            (*this)[uiRow][i] = tValue;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::FillRows
    // -----------------------------------------------------------------------------------
    /**	Fill uiNumRows rows sitems with tValue starting from uiStartRow
    *
    *	@param      uiStartRow: starting row index
    *	@param      uiNumRows: rows to fill
    *	@param      tValue: source value
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix<T>& FillRows(t_FMT_Uint32 uiStartRow, t_FMT_Uint32 uiNumRows, const T& tValue)
    {
        t_FMT_Uint32    k;
        t_FMT_Uint32    r;

        for (k=0, r=uiStartRow; k<uiNumRows; k++, r++)
        {
            FillRow(r, tValue);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::FillRow
    // -----------------------------------------------------------------------------------
    /**	Fill uiSize row items with tValue
    *
    *	@param      uiRow: row index
    *	@param      uiPos: insert index
    *	@param      uiSize: number of items to fill
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix<T>& FillRow(t_FMT_Uint32 uiRow, const T& tValue, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        t_FMT_Uint32    i;

        if ((bResize) && (uiPos + uiSize > m_uiNumColumns))
        {
            Recreate(m_uiNumRows, uiPos + uiSize, 0, 0);
        }

        if (uiPos + uiSize > m_uiNumColumns)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        for (i = uiPos; i < uiSize; i++)
        {
            (*this)[uiRow][i] = tValue;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::CopyRowItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiNumItems items of vet vector from uiStart posizion to uiColPos position of
    *   row uiRow
    *
    *	@param      uiRow: destination row index
    *	@param      uiColPos: column destination index
    *	@param      vet: source vector
    *	@param      uiStart: starting vector item index
    *	@param      uiNumItems: number of items to copy
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][04/04/2018]
    // =====================================================================================

    CFMT_Matrix<T>& CopyRowItemsFrom(t_FMT_Uint32 uiRow, t_FMT_Uint32 uiColPos, CFMT_Vector<T>& vet, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiNumItems, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (uiRow >= m_uiNumRows)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((uiColPos + uiNumItems > m_uiNumColumns) && !bResize)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if (vet.GetLength() < uiStart + uiNumItems)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((bResize) && (uiColPos + uiNumItems > m_uiNumColumns))
        {
            Recreate(m_uiNumRows, uiColPos + uiNumItems, 0, 0);
        }

        t_FMT_Uint32    i;
        T* pHT = m_pBuf + uiRow * m_uiNumColumns + uiColPos;

        for (i = uiStart; i < uiNumItems + uiStart; i++)
        {
            (*pHT++) = vet[i];
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::CopyRowItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiNumItems items of vet vector from uiStart posizion to uiColPos position of
    *   row uiRow
    *
    *	@param      uiRow: destination row index
    *	@param      uiColPos: column destination index
    *	@param      pV: source vector
    *	@param      uiStart: starting vector item index
    *	@param      uiNumItems: number of items to copy
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][04/04/2018]
    // =====================================================================================

    CFMT_Matrix<T>& CopyRowItemsFrom(t_FMT_Uint32 uiRow, t_FMT_Uint32 uiColPos, T* pV, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiNumItems, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if (uiRow >= m_uiNumRows)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((uiColPos + uiNumItems > m_uiNumColumns) && !bResize)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((bResize) && (uiColPos + uiNumItems > m_uiNumColumns))
        {
            Recreate(m_uiNumRows, uiColPos + uiNumItems, 0, 0);
        }

        t_FMT_Uint32    i;
        T* pHT = m_pBuf + uiRow * m_uiNumColumns + uiColPos;

        for (i = uiStart; i < uiNumItems + uiStart; i++)
        {
            (*pHT++) = pV[i];
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::FillColumn
    // -----------------------------------------------------------------------------------
    /**	FillColumn all column items with tValue
    *
    *	@param      uiCol: column index
    *	@param      tValue: source value
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix<T>& FillColumn(t_FMT_Uint32 uiCol, const T& tValue)
    {
        t_FMT_Uint32    i;

        for (i = 0; i < m_uiNumRows; i++)
        {
            (*this)[i][uiCol] = tValue;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::FillColumns
    // -----------------------------------------------------------------------------------
    /**	Fill uiNumCols columns items with tValue starting from uiStartCol
    *
    *	@param      uiStartCol: starting column index
    *	@param      uiNumCols: columns to fill
    *	@param      tValue: source value
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix<T>& FillColumns(t_FMT_Uint32 uiStartCol, t_FMT_Uint32 uiNumCols, const T& tValue)
    {
        t_FMT_Uint32    k;
        t_FMT_Uint32    r;

        for (k=0, r=uiStartCol; k<uiNumCols; k++, r++)
        {
            FillColumn(r, tValue);
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::FillColumn
    // -----------------------------------------------------------------------------------
    /**	FillColumn all column items with tValue
    *
    *	@param      uiCol: column index
    *	@param      uiPos: insert index
    *	@param      uiSize: number of items to fill
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][19/03/2018]
    // =====================================================================================

    CFMT_Matrix<T>& FillColumn(t_FMT_Uint32 uiCol, const T& tValue, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        t_FMT_Uint32    i;

        if ((bResize) && (uiPos + uiSize > m_uiNumRows))
        {
            Recreate(uiPos + uiSize, m_uiNumColumns, 0, 0);
        }

        if (uiPos + uiSize > m_uiNumRows)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        for (i = uiPos; i < m_uiNumRows; i++)
        {
            (*this)[i][uiCol] = tValue;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::CopyColumnItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiNumItems items of vet vector from uiStart posizion to uiRowPos position of
    *   column uiCol
    *
    *	@param      uiRowPos: rowdestination index
    *	@param      uiCol: destination column index
    *	@param      vet: source vector
    *	@param      uiStart: starting vector item index
    *	@param      uiNumItems: number of items to copy
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][04/04/2018]
    // =====================================================================================

    CFMT_Matrix<T>& CopyColumnItemsFrom(t_FMT_Uint32 uiRowPos, t_FMT_Uint32 uiCol, CFMT_Vector<T>& vet, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiNumItems, t_FMT_Bool bResize)
    {
        if (uiCol >= m_uiNumColumns)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((uiRowPos + uiNumItems > m_uiNumRows) && !bResize)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if (vet.GetLength() < uiStart + uiNumItems)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((bResize) && (uiRowPos + uiNumItems > m_uiNumRows))
        {
            Recreate(uiRowPos + uiNumItems, m_uiNumColumns, 0, 0);
        }

        t_FMT_Uint32    i;
        T* pHT = m_pBuf + uiRowPos * m_uiNumColumns + uiCol;

        for (i = uiStart; i < uiNumItems + uiStart; i++)
        {
            (*pHT) = vet[i];
            pHT += m_uiNumColumns;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::CopyColumnItemsFrom
    // -----------------------------------------------------------------------------------
    /**	Copy uiNumItems items of vet vector from uiStart posizion to uiRowPos position of
    *   column uiCol
    *
    *	@param      uiRowPos: rowdestination index
    *	@param      uiCol: destination column index
    *	@param      pV: source vector
    *	@param      uiStart: starting vector item index
    *	@param      uiNumItems: number of items to copy
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][04/04/2018]
    // =====================================================================================

    CFMT_Matrix<T>& CopyColumnItemsFrom(t_FMT_Uint32 uiRowPos, t_FMT_Uint32 uiCol, T* pV, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiNumItems, t_FMT_Bool bResize)
    {
        if (uiCol >= m_uiNumColumns)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((uiRowPos + uiNumItems > m_uiNumRows) && !bResize)
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((bResize) && (uiRowPos + uiNumItems > m_uiNumRows))
        {
            Recreate(uiRowPos + uiNumItems, m_uiNumColumns, 0, 0);
        }

        t_FMT_Uint32    i;
        T* pHT = m_pBuf + uiRowPos * m_uiNumColumns + uiCol;

        for (i = uiStart; i < uiNumItems + uiStart; i++)
        {
            (*pHT) = pV[i];
            pHT += m_uiNumColumns;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Matrix::Copy
    // -----------------------------------------------------------------------------------
    /**	Copy a sub-matrix of mat from uiSrcRow,uiSrcCol to uiDestRow,uiDestCol of size
    *   uiNumRows x uiNumCols
    *
    *	@param      uiDestRow: row destination index
    *	@param      uiDestCol: destination column index
    *	@param      mat: source matrix
    *	@param      uiSrcRow: row source index
    *	@param      uiSrcCol: column source index
    *	@param      uiNumRows: number of rows to copy
    *	@param      uiNumCols: number of columns to copy
    *   @param      bResize: FMTDEF_TRUE -> resize if needed
    *	@return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][04/04/2018]
    // =====================================================================================

    CFMT_Matrix<T>& Copy(t_FMT_Uint32 uiDestRow, t_FMT_Uint32 uiDestCol, t_FMT_Uint32 uiNumRows, t_FMT_Uint32 uiNumCols, CFMT_Matrix<T>& mat, t_FMT_Uint32 uiSrcRow, t_FMT_Uint32 uiSrcCol, t_FMT_Bool bResize = FMTDEF_TRUE)
    {
        if ((uiSrcRow + uiNumRows > mat.m_uiNumRows) || (uiSrcCol + uiNumCols > mat.m_uiNumColumns))
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if (!bResize && ((uiDestRow + uiNumRows > m_uiNumRows) || (uiDestCol + uiNumCols > m_uiNumColumns)))
        {
            throw CFMT_Exception(e_Return_InvalidParameter, this);
        }

        if ((bResize) && ((uiDestRow + uiNumRows > m_uiNumRows) || (uiDestCol + uiNumCols > m_uiNumColumns)))
        {
            Recreate(uiDestRow + uiNumRows, uiDestCol + uiNumCols, 0, 0);
        }

        T* pHT = m_pBuf + uiDestRow*m_uiNumColumns + uiDestCol;
        T* pHST = mat.m_pBuf + uiSrcRow * mat.m_uiNumColumns + uiSrcCol;

        t_FMT_Uint32 uiStep = m_uiNumColumns - uiNumCols;
        t_FMT_Uint32 uiSStep = mat.m_uiNumColumns - uiNumCols;

        for (t_FMT_Uint32 j=0; j<uiNumRows; j++)
        {
            for (t_FMT_Uint32 i=0; i<uiNumCols; i++)
            {
                (*pHT++) = (*pHST++);
            }
            pHT += uiStep;
            pHST += uiSStep;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Buffer::operator<<
    // -----------------------------------------------------------------------------------
    /**	Serializes a vector into the buffer
     *
     *  @param      buf: destination buffer
     *  @param      mtx: source matrix
     *  @return     reference of the buffer
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_Matrix<T>& mtx)
    {
        t_FMT_Uint32	r;
        t_FMT_Uint32	c;

        buf << mtx.m_uiNumRows;
        buf << mtx.m_uiNumColumns;

        for (r=0; r<mtx.GetNumRows(); r++)
        {
            for (c=0; c<mtx.GetNumColumns(); c++)
            {
                buf << mtx.m_pBuf[r* mtx.GetNumColumns() + c];
            }
        }

        return buf;
    }


    // =====================================================================================
    //	CFMT_Buffer::operator>>
    // -----------------------------------------------------------------------------------
    /**	Serializes a matrix from the buffer
     *
     *  @param      buf: source buffer
     *  @param      mtx: destination matrix
     *  @return     reference of the buffer
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][05/04/2018]
    // =====================================================================================

    friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_Matrix<T>& mtx)
    {
        t_FMT_Uint32	r;
        t_FMT_Uint32	c;
        t_FMT_Uint32	uiNumRows;
        t_FMT_Uint32	uiNumColumns;

        buf >> uiNumRows;
        buf >> uiNumColumns;

        if ((uiNumRows != mtx.GetNumRows()) || (uiNumColumns != mtx.GetNumColumns()))
        {
            mtx.Create(uiNumRows, uiNumColumns);
        }

        for (r=0; r<mtx.GetNumRows(); r++)
        {
            for (c=0; c<mtx.GetNumColumns(); c++)
            {
                buf >> mtx.m_pBuf[r*mtx.GetNumColumns() + c];
            }
        }

        return buf;
    }


    // =====================================================================================
    //	CFMT_Matrix::operator==
    // -----------------------------------------------------------------------------------
    /**	Checks if two matrix are equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    t_FMT_Bool operator==(const CFMT_Matrix<T>& op)
    {
        if (m_uiNumRows != op.m_uiNumRows)
        {
            return FMTDEF_FALSE;
        }

        if (m_uiNumColumns != op.m_uiNumColumns)
        {
            return FMTDEF_FALSE;
        }

        t_FMT_Uint32        r;
        t_FMT_Uint32        c;

        for (r=0; r<m_uiNumRows; r++)
        {
            for (c=0; c<m_uiNumColumns; c++)
            {
                if (m_pBuf[r*m_uiNumColumns + c] != op.m_pBuf[r*m_uiNumColumns + c])
                {
                    return FMTDEF_FALSE;
                }
            }
        }

        return FMTDEF_TRUE;
    }


    // =====================================================================================
    //	CFMT_Matrix::operator!=
    // -----------------------------------------------------------------------------------
    /**	Checks if two matrix are not equal
    *
    *	@param      op: comparision object
    *	@return     FMTDEF_TRUE if equals
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][03/04/2018]
    // =====================================================================================

    t_FMT_Bool operator!=(const CFMT_Matrix<T>& op)
    {
        return !(operator==(op));
    }



};


#endif

