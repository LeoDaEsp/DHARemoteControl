// =====================================================================================
/**
 * @file					FMT_Code.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					09/06/2021
 * @brief					Codes management
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][09/06/2021]
 */
// =====================================================================================



#ifndef FMTDEF_CODE_H
#define FMTDEF_CODE_H

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



// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Code
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Code : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

    enum t_FormatNodeType
    {
        e_FormatNodeType_Field  = 0,
        e_FormatNodeType_Text   = 1
    };

    class FMTDEF_LIB_DLLSPEC CFormatNode
    {
	public:
        t_FormatNodeType    m_Type;
        void                *m_pItem;

	    t_FMT_Bool          operator==(const CFormatNode& op)
		{
            FMTDEFM_UNUSED(op);
			return FMTDEF_FALSE;
		}
	    t_FMT_Bool          operator!=(const CFormatNode& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFormatNode& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFormatNode& s);
	};

    class FMTDEF_LIB_DLLSPEC CFormatList : public CFMT_List<CFormatNode>
    {
    };

    class FMTDEF_LIB_DLLSPEC CFormatVector : public CFMT_Vector<CFormatNode>
    {
    public:
        CFormatVector& operator=(CFormatList& op)
        {
            DataCopy(op);

            return (*this);
        }
    };

public:


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    CFMT_StringVector   m_Fields;
    CFMT_StringVector   m_Values;
    CFormatVector       m_Format;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_Code();

    //! Constructor with format
    CFMT_Code(const CFMT_String& sFormat);

    //! Copy constructor
    CFMT_Code(const CFMT_Code& op);

    //! Destructor
    virtual ~CFMT_Code();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

private:

    //! Clear the format
    void            ClearFormat();

protected:

    //! Copy from an homogeneous object
    void            DataCopy(const CFMT_Code& op);

public:

    //! Set the code format
    t_FMT_Uint32    Format(const CFMT_String& sFormat);

    //! Set the code from string
    CFMT_Code&      Set(const CFMT_String& sValue);

    //! Set the code another code
    CFMT_Code&      Set(CFMT_Code& Src);

    //! Set a field of the code
    CFMT_Code&      SetField(const CFMT_String& sField, const CFMT_String& sValue);

    //! Get a code field string
    CFMT_String     GetField(const CFMT_String& field);

    //! Get the code string
    CFMT_String     GetString();

    //! Assignment operator from homogeneous object
    CFMT_Code&      operator=(const CFMT_Code& op);

};



#endif







