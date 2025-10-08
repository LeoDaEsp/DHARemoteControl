// =====================================================================================
/**
 * @file					FMT_HdwArinc429Message.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Arinc429 Message
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_ARINC429MESSAGE_H
#define FMTDEF_HDW_ARINC429MESSAGE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwArinc429Message
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429Message : public CFMT_Object
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

    t_FMT_Uint8		m_ucLabel;      //! Label Field
    t_FMT_Uint8		m_ucSDI;        //! SDI Field
    t_FMT_Uint8		m_ucSSM;        //! SSM Field
    t_FMT_Uint32	m_uiData;       //! Data Field
    t_FMT_Bool		m_bParity;      //! Parity

    t_FMT_Uint64	m_quiTimeMark;  //! Time Mark
    t_FMT_Uint32	m_uiIntergap;   //! Word Intergap
    t_FMT_Double	m_dRate;        //! Work Time rate


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwArinc429Message();

    //! Destructor
    virtual ~CFMT_HdwArinc429Message();

	//! Comparison operator
    t_FMT_Bool		operator==(const CFMT_HdwArinc429Message& op);

	//! Comparison operator
    t_FMT_Bool		operator!=(const CFMT_HdwArinc429Message& op);

	//! Set the message field from unsigned int 32
	void			SetFromUint32(t_FMT_Uint32 uiData);

	//! Get the message field to unsigned int 32
	t_FMT_Uint32	GetToUint32();

	//! Set the parity of the message
	void			SetParity(t_FMT_Bool bEven);


    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFMT_HdwArinc429Message& m);
    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFMT_HdwArinc429Message& m);

// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:


};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwArinc429MessageList
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429MessageList : public CFMT_List<CFMT_HdwArinc429Message>
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


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:


};



#endif








