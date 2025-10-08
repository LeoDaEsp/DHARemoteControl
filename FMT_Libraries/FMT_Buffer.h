// =====================================================================================
/**
 * @file					FMT_Buffer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					24/03/2018
 * @brief					Abstract buffer management
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][24/03/2018]
 */
// =====================================================================================


#ifndef FMTDEF_BUFFER_H
#define FMTDEF_BUFFER_H

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


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Buffer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Buffer : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    //! Buffer access mode
    enum t_Access
    {
        e_Access_Write		= 0,
        e_Access_Read		= 1,
        e_Access_ReadWrite	= 2
    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    //! Buffer size
    t_FMT_Uint64				m_quiSize;

    //! End of buffer flag
    t_FMT_Bool					m_bEndOfBuffer;

    //! Buffer data block size
    t_FMT_Uint32    			m_uiDataBlockSize;

    //! Buffer access mode
    t_Access                    m_Access;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_Buffer(t_FMT_Uint32 uiDataBlockSize = 1024);

    //! Destructor
    virtual ~CFMT_Buffer();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //virtual void        DataCopy(const CFMT_Buffer& op);

public:

    //! Return the size of the buffer
    t_FMT_Uint64            GetSize();

    //! Return the end of buffer flag
    t_FMT_Bool              IsEnd();

    //! Get absolute pointer position
    virtual t_FMT_Uint64	GetAbsPosition();

    //! Empty the buffer
    virtual void            DeleteAll();

    //! Set the pointer at the beginning of the buffer
    virtual void            ToStart();

    //! Set the pointer at the end of the buffer
    virtual void            ToEnd();

    //! Append a byte block of uiSize
    virtual void            AppendData(void *pvData,t_FMT_Uint32 uiSize);

    //! Read a byte block of uiSize
    virtual void            RetrieveData(void *pvData, t_FMT_Uint32 uiSize);


    #if 0
    // Assignment
    virtual CFMT_Buffer& operator=(const CFMT_Buffer& op);

    // Comparison
    virtual t_FMT_Bool  operator ==(const CFMT_Buffer& op);
    virtual t_FMT_Bool  operator !=(const CFMT_Buffer& op);
    #endif

    //! Serializes a char into the buffer
    virtual void        operator<<(t_FMT_Char chData);

    //! Serializes a 8-bit unsigned integer into the buffer
    virtual void        operator<<(t_FMT_Uint8 ucData);

    //! Serializes a 16-bit unsigned integer into the buffer
    virtual void        operator<<(t_FMT_Uint16 usData);

    //! Serializes a 32-bit unsigned integer into the buffer
    virtual void        operator<<(t_FMT_Uint32 uiData);

    //! Serializes a 64-bit unsigned integer into the buffer
    virtual void        operator<<(t_FMT_Uint64 quiData);

    //! Serializes a 8-bit signed integer into the buffer
    virtual void        operator<<(t_FMT_Int8 chData);

    //! Serializes a 16-bit signed integer into the buffer
    virtual void        operator<<(t_FMT_Int16 shData);

    //! Serializes a 32-bit signed integer into the buffer
    virtual void        operator<<(t_FMT_Int32 iData);

    //! Serializes a 64-bit signed integer into the buffer
    virtual void        operator<<(t_FMT_Int64 qiData);

    //! Serializes a single precision floating point into the buffer
    virtual void        operator<<(t_FMT_Float fData);

    //! Serializes a double precision floating point into the buffer
    virtual void        operator<<(t_FMT_Double dData);

    //! Serializes a pointer
    virtual void        operator<<(void *pVoid);


    //! Serializes a char from the buffer
    virtual void        operator>>(t_FMT_Char& chData);

    //! Serializes a 8-bit unsigned integer from the buffer
    virtual void        operator>>(t_FMT_Uint8& ucData);

    //! Serializes a 16-bit unsigned integer from the buffer
    virtual void        operator>>(t_FMT_Uint16& usData);

    //! Serializes a 32-bit unsigned integer from the buffer
    virtual void        operator>>(t_FMT_Uint32& uiData);

    //! Serializes a 64-bit unsigned integer from the buffer
    virtual void        operator>>(t_FMT_Uint64& quiData);

    //! Serializes a 8-bit signed integer from the buffer
    virtual void        operator>>(t_FMT_Int8& chData);

    //! Serializes a 16-bit signed integer from the buffer
    virtual void        operator>>(t_FMT_Int16& shData);

    //! Serializes a 32-bit signed integer from the buffer
    virtual void        operator>>(t_FMT_Int32& iData);

    //! Serializes a 64-bit signed integer from the buffer
    virtual void        operator>>(t_FMT_Int64& qiData);

    //! Serializes a single precision floating point from the buffer
    virtual void        operator>>(t_FMT_Float& fData);

    //! Serializes a double precision floating point from the buffer
    virtual void        operator>>(t_FMT_Double& dData);

    //! Serializes a pointer
    virtual void        operator>>(void *pVoid);


};



#endif







