// =====================================================================================
/**
 * @file                    FMT_Dumper.h
 * @author                  M.Forzieri, Formatech Engineering S.R.L.
 * @date                    09/03/2018
 * @brief                   Dumper for code debug.
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][22/01/2018]
 */
// =====================================================================================



#ifndef FMTDEF_DUMPER_H
#define FMTDEF_DUMPER_H

// =====================================================================================
//	INCLUDES
// =====================================================================================

#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif

/*#ifndef FMTDEF_TIMESTAMP_H
#include "Ppa_TimeStamp.h"
#endif*/


using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Dumper
// *************************************************************************************
// *************************************************************************************

/*! @brief Application class.
 *
 *	The CFMT_Dumper implements a dumper for code debug.
 */


class FMTDEF_LIB_DLLSPEC CFMT_Dumper
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================


protected:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

private:

    //!	Dumper level
    t_FMT_Uint32 			m_uiLevel;

    //!	Dumper End-Of-Line Flag
    t_FMT_Bool              m_bDumpEol;


protected:


public:

    // ---[t_Level] -----------------------------

    //! Level enumerator
    enum t_Level
    {
        e_Level_Low			= 0,
        e_Level_Medium		= 1,
        e_Level_High		= 2
    };


    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    //!	Base constructor
    CFMT_Dumper();

    //!	Constructor with level
    CFMT_Dumper(t_FMT_Uint32 uiLevel);

    //!	Destructor
    ~CFMT_Dumper();


    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

private:
        //!	Add time stamp to log text
        //void    PutTimeStamp(void);

protected:

public:
        //!	Add a String to log text
        virtual CFMT_Dumper& operator <<(const CFMT_String& sData);

        //!	Add an t_FMT_Int32 to log text
        virtual CFMT_Dumper& operator <<(t_FMT_Int32 iData);

        //!	Add an t_FMT_Uint32 to log text
        virtual CFMT_Dumper& operator <<(t_FMT_Uint32 uiData);

        //!	Add an t_FMT_Int64 to log text
        virtual CFMT_Dumper& operator <<(t_FMT_Int64 qiData);

        //!	Add an t_FMT_Uint64 to log text
        virtual CFMT_Dumper& operator <<(t_FMT_Uint64 quiData);

        //!	Add an t_FMT_Char* to log text
        virtual CFMT_Dumper& operator <<(const t_FMT_Char* pchData);

        //!	Add an t_FMT_Double to log text
        virtual CFMT_Dumper& operator <<(t_FMT_Double dData);
};

#endif

