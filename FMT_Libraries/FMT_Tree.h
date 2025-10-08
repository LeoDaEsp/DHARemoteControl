// =====================================================================================
/**
 * @file					CFMT_Tree.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					06/04/2018
 * @brief					Template class for tree container
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][06/04/2018]
 */
// =====================================================================================


#ifndef FMTDEF_TREE_H
#define FMTDEF_TREE_H

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
//	Template Class CFMT_ListItem
// *************************************************************************************
// *************************************************************************************

//! Basic item for tree

template <class T> class CFMT_TreeItem
{
public:

    //! Previous item
    CFMT_TreeItem				*m_pPrev;

    //! Childs list
    CFMT_List<CFMT_TreeItem*>	m_ChildsList;

    //! Item data
    T							m_Data;
};



// *************************************************************************************
// *************************************************************************************
//	Template Class CFMT_Tree
// *************************************************************************************
// *************************************************************************************

template <class T> class CFMT_Tree
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:


// =====================================================================================
//	VARIABLES
// =====================================================================================

    //! Tree root item
    CFMT_TreeItem<T>		*m_pRoot;

    //! Current item pointer
    CFMT_TreeItem<T>		*m_pPos;

    //! Number of tree items
    t_FMT_Uint32            m_uiLength;



    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    // =====================================================================================
    //	CFMT_Tree::CFMT_Tree
    // -----------------------------------------------------------------------------------
    /**	Empty constructor
    *
    *	@return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    CFMT_Tree()
    {
        m_uiLength = 0;
        m_pRoot = FMTDEF_NULL;
        m_pPos = FMTDEF_NULL;
    }


    // =====================================================================================
    //	CFMT_Tree::~CFMT_Tree
    // -----------------------------------------------------------------------------------
    /**	Destructor
    *
    *  @return     N/A
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    ~CFMT_Tree()
    {
        DeleteAllChilds();
    }


    // =====================================================================================
    //	CFMT_Tree::DeleteAllChilds
    // -----------------------------------------------------------------------------------
    /**	Delete all tree items and return a reference to the object
     *
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& DeleteAllChilds()
    {
        if (m_pRoot == FMTDEF_NULL)
        {
            return (*this);
        }

        DestroyTree(m_pRoot);

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::DestroyTree
    // -----------------------------------------------------------------------------------
    /**	Delete all pTree items and return a reference to the object
     *
     *  @param      pTree: tree to delete
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& DestroyTree(CFMT_TreeItem<T> *pTree)
    {
        t_FMT_Uint32        k;
        CFMT_TreeItem<T>	*pT;

        pTree->m_ChildsList.ToStart();

        for (k = 0; k < pTree->m_ChildsList.GetLength(); k++)
        {
            pT = ((pTree->m_ChildsList)>>1);

            DestroyTree(pT);
        }

        delete pTree;

        m_uiLength--;

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::DeleteItem
    // -----------------------------------------------------------------------------------
    /**	Delete the current item and all its children and return a reference to the object;
     *  move the pointer to its parent
     *
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& DeleteItem()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return (*this);
        }

        CFMT_TreeItem<T>        *pParent;

        pParent = m_pPos->m_pPrev;

        if (pParent == FMTDEF_NULL)
        {
            m_pRoot = FMTDEF_NULL;
        }

        if (pParent != FMTDEF_NULL)
        {
            pParent->m_ChildsList.ToStart();
            pParent->m_ChildsList.FindToEnd(m_pPos);
            pParent->m_ChildsList.DeleteItem();
        }

        DestroyTree(m_pPos);

        m_pPos = pParent;


        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::DeleteAll
    // -----------------------------------------------------------------------------------
    /**	Delete all tree items
     *
     *  @return     reference to the object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& DeleteAll()
    {
        if (m_pRoot == FMTDEF_NULL)
        {
            return (*this);
        }

        DestroyTree(m_pRoot);

        m_pRoot = FMTDEF_NULL;
        m_pPos = FMTDEF_NULL;
        m_uiLength = 0;
    }


    // =====================================================================================
    //	CFMT_Tree::IsRoot
    // -----------------------------------------------------------------------------------
    /**	Check if the current item is the root item
     *
     *  @return     FMTDEF_TRUE if the current item is the root item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    t_FMT_Bool IsRoot()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_TRUE;
        }

        return (m_pPos->m_pPrev == FMTDEF_NULL);
    }


    // =====================================================================================
    //	CFMT_Tree::ToRoot
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to the root of the tree and return a pointer to the
     *  root object
     *
     *  @return     reference to the root object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* ToRoot()
    {
        m_pPos = m_pRoot;

        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        return &(m_pPos->m_Data);
    }

    // =====================================================================================
    //	CFMT_Tree::ToFirstChild
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to the root of the tree and return a pointer to the object
     *
     *  @return     reference to the root object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* ToFirstChild()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        if (m_pPos->m_ChildsList.GetLength() == 0)
        {
            return FMTDEF_NULL;
        }

        m_pPos->m_ChildsList.ToStart();

        m_pPos = m_pPos->m_ChildsList.CurItem();

        return (&m_pPos->m_Data);
    }


    // =====================================================================================
    //	CFMT_Tree::ToChild
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to child of index idx and return a pointer to the object
     *
     *  @param      idx: child index
     *  @return     reference to the child object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* ToChild(t_FMT_Uint32 uiIdx)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        if (uiIdx < m_pPos->m_ChildsList.GetLength())
        {
            m_pPos = m_pPos->m_ChildsList[uiIdx];
            return (&m_pPos->m_Data);
        }
        else
        {
            return FMTDEF_NULL;
        }

    }


    // =====================================================================================
    //	CFMT_Tree::ToParent
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to the parent of the current item and return a pointer to the object
     *
     *  @return     reference to the root object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* ToParent()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        m_pPos = m_pPos->m_pPrev;

        return (&m_pPos->m_Data);
    }


    // =====================================================================================
    //	CFMT_Tree::GetNumberOfChilds
    // -----------------------------------------------------------------------------------
    /**	Get the number of childs of the current item
     *
     *  @return     the number of childs of the current item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    t_FMT_Uint32 GetNumberOfChilds()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return 0;
        }

        return (m_pPos->m_ChildsList.GetLength());
    }


    // =====================================================================================
    //	CFMT_Tree::GetLength
    // -----------------------------------------------------------------------------------
    /**	Get the number of items
     *
     *  @return     the number of items
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    t_FMT_Uint32 GetLength() const
    {
        return (m_uiLength);
    }


    // =====================================================================================
    //	CFMT_Tree::CurItem
    // -----------------------------------------------------------------------------------
    /**	Get the pointer of current item
    *
    *	@return     pointer of current item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    T* CurItem()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange,this);
        }

        return &(m_pPos->m_Data);
    }


    // =====================================================================================
    //	CFMT_Tree::GetChild
    // -----------------------------------------------------------------------------------
    /**	Get the child pointer of index idx.
     *
     *  @param      idx: child index
     *  @return     reference to the child object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* GetChild(t_FMT_Uint32 uiIdx)
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        if (uiIdx < m_pPos->m_ChildsList.GetLength())
        {
            return &(m_pPos->m_ChildsList[uiIdx]->m_Data);
        }
        else
        {
            return FMTDEF_NULL;
        }

    }


    // =====================================================================================
    //	CFMT_Tree::GetParent
    // -----------------------------------------------------------------------------------
    /**	Get the parent pointer of current item.
     *
     *  @return     reference to the parent object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    T* GetParent()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        return (m_pPos->m_pPrev);
    }


    // =====================================================================================
    //	CFMT_Tree::GetNextBrother
    // -----------------------------------------------------------------------------------
    /**	Return a pointer to the next brother
     *
     *  @return     pointer to the next brother object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    T* GetNextBrother()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        if (m_pPos->m_pPrev == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        m_pPos->m_pPrev->m_ChildsList.ToStart();
        m_pPos->m_pPrev->m_ChildsList.FindToEnd(m_pPos);

        if (!m_pPos->m_pPrev->m_ChildsList.IsEnd())
        {
            (m_pPos->m_pPrev->m_ChildsList) >> 1;

            return &((m_pPos->m_pPrev->m_ChildsList).CurItem()->m_Data);
        }
        else
        {
            return FMTDEF_NULL;
        }
    }


    // =====================================================================================
    //	CFMT_Tree::GetPreviousBrother
    // -----------------------------------------------------------------------------------
    /**	Return a pointer to the previous brother
     *
     *  @return     pointer to the previous brother object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    T* GetPreviousBrother()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        if (m_pPos->m_pPrev == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        m_pPos->m_pPrev->m_ChildsList.ToStart();
        m_pPos->m_pPrev->m_ChildsList.FindToEnd(m_pPos);

        if (!m_pPos->m_pPrev->m_ChildsList.IsStart())
        {
            (m_pPos->m_pPrev->m_ChildsList) << 1;

            return &((m_pPos->m_pPrev->m_ChildsList).CurItem()->m_Data);
        }
        else
        {
            return FMTDEF_NULL;
        }
    }


    // =====================================================================================
    //	CFMT_Tree::AddChild
    // -----------------------------------------------------------------------------------
    /**	Add a child to the current node return a reference to the new object
     *
     *  @param      data: data to add
     *  @return     reference to the added object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T& AddChild(const T& data)
    {
        if (m_uiLength == 0)
        {
            m_pRoot = new CFMT_TreeItem<T>();

            m_pRoot->m_pPrev = FMTDEF_NULL;

            m_pRoot->m_Data = data;

            m_pPos = m_pRoot;

            m_uiLength = 1;

            return (m_pPos->m_Data);
        }

        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange, this);
        }

        CFMT_TreeItem<T>* pE = new CFMT_TreeItem<T>();

        m_pPos->m_ChildsList += pE;

        pE->m_pPrev = m_pPos;
        pE->m_Data = data;

        m_pPos = pE;

        m_uiLength++;

        return (m_pPos->m_Data);
    }


    // =====================================================================================
    //	CFMT_Tree::AddChild
    // -----------------------------------------------------------------------------------
    /**	Add a child to the current node return a pointer to the new object
     *
     *  @return     reference to the added object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* AddChild()
    {
        if (m_uiLength == 0)
        {
            m_pRoot = new CFMT_TreeItem<T>();

            m_pRoot->m_pPrev = FMTDEF_NULL;

            m_pPos = m_pRoot;

            m_uiLength = 1;

            return (&(m_pPos->m_Data));
        }

        if (m_pPos == FMTDEF_NULL)
        {
            throw CFMT_Exception(e_Return_OutOfRange, this);
        }

        CFMT_TreeItem<T>* pE = new CFMT_TreeItem<T>();

        m_pPos->m_ChildsList += pE;

        pE->m_pPrev = m_pPos;
        m_pPos = pE;

        m_uiLength++;

        return (&(m_pPos->m_Data));
    }


    // =====================================================================================
    //	CFMT_Tree::AddChilds
    // -----------------------------------------------------------------------------------
    /**	Add childs to the current node copying from src vector of length uiSize,
     *  starting copying from uiStart item and return a reference to the new object
     *
     *  @param      src: source vector
     *  @param      uiSize: number of items to copy
     *  @param      uiStart: first item index to copy
     *  @return     Reference to the tree
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& AddChilds(T* src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart=0)
    {
        t_FMT_Uint32        k;
        t_FMT_Uint32        w;
        T                   *pT;

        if (uiSize == 0)
        {
            return (*this);
        }

        pT = AddChild();
        *pT = src[uiStart];

        for (k=1, w=uiStart+1; k<uiSize; k++, w++)
        {
            pT = AddBrother();
            *pT = src[w];
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::AddChilds
    // -----------------------------------------------------------------------------------
    /**	Add childs to the current node copying from src vector of length uiSize,
     *  starting copying from uiStart item and return a reference to the new object
     *
     *  @param      src: source vector
     *  @param      uiSize: number of items to copy
     *  @param      uiStart: first item index to copy
     *  @return     Reference to the tree
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& AddChilds(CFMT_Vector<T>& src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart=0)
    {
        t_FMT_Uint32        k;
        t_FMT_Uint32        w;
        T                   *pT;

        if (uiSize == 0)
        {
            return (*this);
        }

        pT = AddChild();
        *pT = src[uiStart];

        for (k=1, w=uiStart+1; k<uiSize; k++, w++)
        {
            pT = AddBrother();
            *pT = src[w];
        }

        return (*this);
    }

    //CFMT_Tree<T>& AddChilds(CFMT_List<T> &src, t_FMT_Uint32 uiSize);

    // =====================================================================================
    //	CFMT_Tree::AddChilds
    // -----------------------------------------------------------------------------------
    /**	Add childs to the current node copying from src list of length uiSize,
     *  starting copying from current list position and return a reference to the new object
     *
     *  @param      src: source list
     *  @param      uiSize: number of items to copy
     *  @return     Reference to the tree
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& AddChilds(CFMT_List<T> &src, t_FMT_Uint32 uiSize)
    {
        t_FMT_Uint32        k;
        T                   *pT;

        if (uiSize == 0)
        {
            return (*this);
        }

        pT = AddChild();
        *pT = src >> 1;

        for (k=1; k<uiSize; k++)
        {
            pT = AddBrother();
            *pT = src >> 1;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::AddBrother
    // -----------------------------------------------------------------------------------
    /**	Add a brother to the current node return a reference to the new object
     *
     *  @param      data: data to add
     *  @return     reference to the added object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T& AddBrother(const T& data)
    {
        if ((m_pPos == m_pRoot) || (m_uiLength == 0))
        {
            throw CFMT_Exception(e_Return_OutOfRange, this);
        }

        CFMT_TreeItem<T>* pE = new CFMT_TreeItem<T>();

        m_pPos->m_pPrev->m_ChildsList += pE;

        pE->m_pPrev = m_pPos->m_pPrev;
        pE->m_Data = data;

        m_pPos = pE;

        m_uiLength++;

        return (m_pPos->m_Data);
    }


    // =====================================================================================
    //	CFMT_Tree::AddBrother
    // -----------------------------------------------------------------------------------
    /**	Add a brother to the current node and return a pointer to the new object
     *
     *  @return     pointer to the added object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* AddBrother()
    {
        if ((m_pPos == m_pRoot) || (m_uiLength == 0))
        {
            throw CFMT_Exception(e_Return_OutOfRange, this);
        }

        CFMT_TreeItem<T>* pE = new CFMT_TreeItem<T>();

        m_pPos->m_pPrev->m_ChildsList += pE;

        pE->m_pPrev = m_pPos->m_pPrev;

        m_pPos = pE;

        m_uiLength++;

        return (&(m_pPos->m_Data));
    }


    // =====================================================================================
    //	CFMT_Tree::InsertChild
    // -----------------------------------------------------------------------------------
    /**	Insert a child to the current node at idx index and return a pointer to it
     *
     *  @param      child index
     *  @return     pointer to the new item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    T* InsertChild(t_FMT_Uint32 idx)
    {
        if ((m_uiLength == 0) || (m_pPos == FMTDEF_NULL))
        {
            return FMTDEF_NULL;
        }

        idx = FMTDEFM_MIN(idx, m_pPos->m_ChildsList.GetLength());

        CFMT_TreeItem<T>* pE = new CFMT_TreeItem<T>();

        if (idx < m_pPos->m_ChildsList.GetLength())
        {
            m_pPos->m_ChildsList.ToPos(idx);
            m_pPos->m_ChildsList.InsertItem(pE);
        }
        else
        {
            m_pPos->m_ChildsList += pE;
        }

        pE->m_pPrev = m_pPos;

        m_uiLength++;

        return (&(pE->m_Data));
    }


    // =====================================================================================
    //	CFMT_Tree::InsertChild
    // -----------------------------------------------------------------------------------
    /**	Insert a child to the current node at idx index, initializes it with data and
     *  returna reference to the new item
     *
     *  @param      child index
     *  @return     reference to the new object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    T& InsertChild(t_FMT_Uint32 idx, const T& data)
    {
        if ((m_uiLength == 0) || (m_pPos == FMTDEF_NULL))
        {
            throw CFMT_Exception(e_Return_OutOfRange, this);
        }

        idx = FMTDEFM_MIN(idx, m_pPos->m_ChildsList.GetLength());

        CFMT_TreeItem<T>* pE = new CFMT_TreeItem<T>();

        if (idx < m_pPos->m_ChildsList.GetLength())
        {
            m_pPos->m_ChildsList.ToPos(idx);
            m_pPos->m_ChildsList.InsertItem(pE);
        }
        else
        {
            m_pPos->m_ChildsList += pE;
        }

        pE->m_pPrev = m_pPos;

        m_uiLength++;

        pE->m_Data = data;

        return (pE->m_Data);
    }


    // =====================================================================================
    //	CFMT_Tree::InsertChilds
    // -----------------------------------------------------------------------------------
    /**	Insert childs to the current node at idx index copying from src vector of length uiSize,
     *  starting copying from uiStart item and return a reference to the new object
     *
     *  @param      child index
     *  @param      src: source vector
     *  @param      uiSize: number of items to copy
     *  @param      uiStart: first item index to copy
     *  @return     Reference to the tree
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& InsertChilds(t_FMT_Uint32 idx, CFMT_Vector<T>& src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart=0)
    {
        t_FMT_Uint32        k;
        t_FMT_Uint32        j;
        t_FMT_Uint32        w;
        T                   *pT;

        for (k=0, j=idx, w=uiStart; k<uiSize; k++, j++, w++)
        {
            pT = InsertChild(j);
            *pT = src[w];
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::InsertChilds
    // -----------------------------------------------------------------------------------
    /**	Insert childs to the current node at idx index copying from src vector of length uiSize,
     *  starting copying from uiStart item and return a reference to the new object
     *
     *  @param      child index
     *  @param      src: source vector
     *  @param      uiSize: number of items to copy
     *  @param      uiStart: first item index to copy
     *  @return     Reference to the tree
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& InsertChilds(t_FMT_Uint32 idx, T* src, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiStart=0)
    {
        t_FMT_Uint32        k;
        t_FMT_Uint32        j;
        t_FMT_Uint32        w;
        T                   *pT;

        for (k=0, j=idx, w=uiStart; k<uiSize; k++, j++, w++)
        {
            pT = InsertChild(j);
            *pT = src[w];
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::InsertChilds
    // -----------------------------------------------------------------------------------
    /**	Insert childs to the current node at idx index copying from src list of length uiSize,
     *  starting copying from current list position and return a reference to the new object
     *
     *  @param      child index
     *  @param      src: source list
     *  @param      uiSize: number of items to copy
     *  @return     Reference to the tree
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    CFMT_Tree<T>& InsertChilds(t_FMT_Uint32 idx, CFMT_List<T> &src, t_FMT_Uint32 uiSize)
    {
        t_FMT_Uint32        k;
        t_FMT_Uint32        j;
        T                   *pT;

        for (k=0, j=idx; k<uiSize; k++, j++)
        {
            pT = InsertChild(j);
            *pT = src >> 1;
        }

        return (*this);
    }


    // =====================================================================================
    //	CFMT_Tree::IsFirstBrother
    // -----------------------------------------------------------------------------------
    /**	Checks if the current item is the first brother and return a pointer to the new object
     *
     *  @return     FMTDEF_TRUE if the current item is the first brother
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    t_FMT_Bool IsFirstBrother()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_TRUE;
        }

        if (m_pPos->m_pPrev == FMTDEF_NULL)
        {
            return FMTDEF_TRUE;
        }

        m_pPos->m_pPrev->m_ChildsList.ToStart();
        m_pPos->m_pPrev->m_ChildsList.FindToEnd(m_pPos);

        if (m_pPos->m_pPrev->m_ChildsList.IsStart())
        {
            return FMTDEF_TRUE;
        }
        else
        {
            return FMTDEF_FALSE;
        }
    }


    // =====================================================================================
    //	CFMT_Tree::IsLastBrother
    // -----------------------------------------------------------------------------------
    /**	Checks if the current item is the last brother and return a pointer to the new object
     *
     *  @return     FMTDEF_TRUE if the current item is the last brother
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    t_FMT_Bool IsLastBrother()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_TRUE;
        }

        if (m_pPos->m_pPrev == FMTDEF_NULL)
        {
            return FMTDEF_TRUE;
        }

        m_pPos->m_pPrev->m_ChildsList.ToStart();
        m_pPos->m_pPrev->m_ChildsList.FindToEnd(m_pPos);

        if (m_pPos->m_pPrev->m_ChildsList.IsEnd())
        {
            return FMTDEF_TRUE;
        }
        else
        {
            return FMTDEF_FALSE;
        }
    }


    // =====================================================================================
    //	CFMT_Tree::ToNextBrother
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to the next brother
     *
     *  @return     pointer to the next brother object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][06/04/2018]
    // =====================================================================================

    T* ToNextBrother()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        if (m_pPos->m_pPrev == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        m_pPos->m_pPrev->m_ChildsList.ToStart();
        m_pPos->m_pPrev->m_ChildsList.FindToEnd(m_pPos);

        if (!m_pPos->m_pPrev->m_ChildsList.IsEnd())
        {
            (m_pPos->m_pPrev->m_ChildsList) >> 1;
            m_pPos = (m_pPos->m_pPrev->m_ChildsList).CurItem();

            return &(m_pPos->m_Data);
        }
        else
        {
            return FMTDEF_NULL;
        }
    }


    // =====================================================================================
    //	CFMT_Tree::ToPreviousBrother
    // -----------------------------------------------------------------------------------
    /**	Move the pointer to the previous brother
     *
     *  @return     pointer to the previous brother object
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    T* ToPreviousBrother()
    {
        if (m_pPos == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        if (m_pPos->m_pPrev == FMTDEF_NULL)
        {
            return FMTDEF_NULL;
        }

        m_pPos->m_pPrev->m_ChildsList.ToStart();
        m_pPos->m_pPrev->m_ChildsList.FindToEnd(m_pPos);

        if (!m_pPos->m_pPrev->m_ChildsList.IsStart())
        {
            (m_pPos->m_pPrev->m_ChildsList) << 1;
            m_pPos = (m_pPos->m_pPrev->m_ChildsList).CurItem();

            return &(m_pPos->m_Data);
        }
        else
        {
            return FMTDEF_NULL;
        }
    }


    // =====================================================================================
    //	CFMT_Tree::GetCurrentLevel
    // -----------------------------------------------------------------------------------
    /**	Return the level of current item
     *
     *  @return     The level of current item
    */
    // -----------------------------------------------------------------------------------
    //! @version 1.1.0001	[First issue][M.Forzieri][10/04/2018]
    // =====================================================================================

    t_FMT_Uint32 GetCurrentLevel()
    {
        if ((m_pRoot == FMTDEF_NULL) || (m_pPos == m_pRoot))
        {
            return 0;
        }

        t_FMT_Uint32        uiLev;
        CFMT_TreeItem<T>    *p;

        uiLev = 0;
        p = m_pPos->m_pPrev;

        while (p != FMTDEF_NULL)
        {
            uiLev++;
            p = p->m_pPrev;
        };

        return uiLev;
    }



    // *** TBD **************

    /*
    t_FMT_Uint32 GetIndex();

    Compare
    Assignment

    CFMT_Tree<T>& Move(t_FMT_Uint32 uiDstIdx);
    CFMT_Tree<T>& MoveChild(t_FMT_Uint32 uiSrcIdx, t_FMT_Uint32 uiDstIdx);


    Find??
    Serializzazione
    */


#if 0


// -------------------------------------------------------------------------------------
//	Ritorna il valore del nodo corrente e si sposta con modalit Next Son
//	falsa se l'elemento letto era l'ultimo
// -------------------------------------------------------------------------------------

void IterateNextChild(t_FMT_Uint32& dwChild,T& tm_Data,BOOL& bEnd)
{
    CFMT_TreeItem *pE=m_pPos;

	// Se non ci sono pi figli torno indietro al padre, spostando il puntatore della
	// lista dei nodi figli al successivo

	if (!(*m_pPos->pSucc)==0)
	{
		if ((*m_pPos->pSucc).HasSucc())
            m_pPos=(m_pPos->m_pPrev)->pSucc>>1;
		else m_pPos
	}
}


// -------------------------------------------------------------------------------------
//	Trova l'elemento dato l'indirizzo 
// -------------------------------------------------------------------------------------

BOOL FindAdd(T *pAdd)
{
    if (&(m_pPos->m_Data)==pAdd)
		return TRUE;
	else
	{
        t_FMT_Uint32 k;
//		BOOL bRet;

        m_pPos->m_ChildsList.Start();
        for (k=0;k<!m_pPos->m_ChildsList;k++)
		{
			GoChild(k);
			if (FindAdd(pAdd))
			{
				return TRUE;
			}
			else
			{
				GoParent();
			}

		}
	}

	return FALSE;
}


// -----------------------------------------------------------------------------------
//	SaveTree
// -----------------------------------------------------------------------------------

static BOOL SaveTree(CArchive& ar, CFMT_Tree<T>& tree)
{
    t_FMT_Uint32 dwTemp;
    t_FMT_Uint32 k;

    // Save node m_Data
	ar<<tree.Value();

    // Save m_ChildsList
	
	dwTemp=tree.GetNodeNumber();

	ar<<dwTemp;

	for (k=0;k<dwTemp;k++)
	{
		tree.GoChild(k);
		SaveTree(ar,tree);
		tree.GoParent();
	}

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	LoadTree
// -----------------------------------------------------------------------------------

static BOOL LoadTree(CArchive& ar, CFMT_Tree<T>& tree)
{
    t_FMT_Uint32 dwTemp;
    t_FMT_Uint32 k;
	CDBItem item;

    // Load node m_Data
	ar>>item;
	tree+=item;

    // Load m_ChildsList
	
	ar>>dwTemp;

	for (k=0;k<dwTemp;k++)
	{
		LoadTree(ar,tree);
	}

	tree.GoParent();

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Serializzazione
// -----------------------------------------------------------------------------------


	friend CArchive& AFXAPI operator <<(CArchive& ar, CFMT_Tree<T>& tree)
	{
		tree.Start();
		SaveTree(ar,tree);

		return ar;
	}

	friend CArchive& AFXAPI operator >>(CArchive& ar, CFMT_Tree<T>& tree)
	{
		tree.DeleteAll();
		tree.Start();
		LoadTree(ar,tree);
		tree.Start();

		return ar;
	}







#endif
};



#endif
