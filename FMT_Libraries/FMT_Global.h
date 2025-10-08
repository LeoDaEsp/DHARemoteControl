// =====================================================================================
/**
 * @file					FMT_Global.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					09/03/2018
 * @brief					Basic items
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][22/01/2018]
 */
// =====================================================================================



#ifndef FMTDEF_GLOBAL_H
#define FMTDEF_GLOBAL_H

// --- Basic includes --------------------------------------------------

#ifdef __cplusplus
#include <cstddef>
#endif

#include <iostream>




// --- Check OS/Compiler detection ---------------------------------------

#ifndef FMTDEF_COMPILE_OS_WINDOWS
    #ifndef FMTDEF_COMPILE_OS_LINUX
        #ifndef FMTDEF_COMPILE_OS_QNX
            !!!No OS defined!!!
        #endif
    #endif
#endif


// --- Other includes --------------------------------------------------


// --- Import/Export ----------------------------------------------------

#if defined FMTDEF_COMPILE_LIB_TEST || defined FMTDEF_COMPILE_APP

    #define FMTDEF_LIB_DLLSPEC	

#else

    #ifdef FMTDEF_COMPILE_OS_WINDOWS

        #ifdef FMTDEF_COMPILE_DLLEXPORT
            #define FMTDEF_LIB_DLLSPEC     __declspec(dllexport)
        #else
            #define FMTDEF_LIB_DLLSPEC     __declspec(dllimport)
        #endif

    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX

        #ifdef FMTDEF_COMPILE_DLLEXPORT
            #define FMTDEF_LIB_DLLSPEC     __attribute__((visibility("default")))
        #else
            #define FMTDEF_LIB_DLLSPEC
        #endif

    #endif

#endif


// --- Special values ---------------------------------------------------

//! True value for boolean type
#define FMTDEF_TRUE                             1

//! False value for boolean type
#define FMTDEF_FALSE                            0

//! NULL value for pointers
//#ifdef __cplusplus_cli
#if __cplusplus > 199711L
#define FMTDEF_NULL                             (nullptr)
#else
#define FMTDEF_NULL                             (0)
#endif





// --- Macroes ----------------------------------------------------------

//! Avoid unused parameters
#define FMTDEFM_UNUSED(x)                           (void)x

//! Return maximum value between a and b
#define FMTDEFM_MAX(a,b)							(((a)>(b))?(a):(b))

//! Return minimum value between a and b
#define FMTDEFM_MIN(a,b)							(((a)<(b))?(a):(b))

//! Return xval limited between minval and maxval
#define FMTDEFM_MIN_MAX(minval, xval, maxval)		(FMTDEFM_MIN(FMTDEFM_MAX((minval), (xval)), (maxval)))

//! Return absolute value of x
#define FMTDEFM_ABS(x)                              (((x)<0)?(-x):(x))


//	--- Atomic Types -------------------------------------------------------

typedef signed char         t_FMT_Int8;         //! 8 bit signed
typedef unsigned char       t_FMT_Uint8;        //! 8 bit unsigned
typedef short               t_FMT_Int16;        //! 16 bit signed
typedef unsigned short      t_FMT_Uint16;       //! 16 bit unsigned
typedef int                 t_FMT_Int32;        //! 32 bit signed
typedef unsigned int        t_FMT_Uint32;       //! 32 bit unsigned

#ifdef FMTDEF_COMPILE_OS_WINDOWS
typedef __int64             t_FMT_Int64;        //! 64 bit signed
typedef unsigned __int64    t_FMT_Uint64;       //! 64 bit unsigned
#else
typedef long long           t_FMT_Int64;        //! 64 bit signed
typedef unsigned long long  t_FMT_Uint64;       //! 64 bit unsigned
#endif

typedef float				t_FMT_Float;
typedef double				t_FMT_Double;
typedef	t_FMT_Uint8         t_FMT_Bool;
typedef char                t_FMT_Char;
typedef FILE				t_FMT_File;


// --- Conditions ---------------------------------------------------------

//! Global namespace of library
//namespace FMTDEF_LIB_DLLSPEC FMT
namespace FMT
{
    //! It enumerates common return for all project classes
    enum t_StdReturn
    {
        e_Return_OK						= 0,
        e_Return_Fail					= 1,
        e_Return_InvalidParameter		= 2,
        e_Return_Overflow				= 3,
        e_Return_Underflow				= 4,
        e_Return_OutOfRange				= 5,
        e_Return_InvalidOS				= 6,
        e_Return_ItemAlreadyPresent		= 7,
        e_Return_NotImplemented			= 8,
        e_Return_InvalidSize			= 9,
        e_Return_NotAllowed				= 10,
        e_Return_FormatError			= 11,
        e_Return_HardwareError			= 12,
        e_Return_DriverError			= 13,
        e_Return_DeviceError			= 14,
        e_Return_ServiceError			= 15,
        e_Return_PortError				= 16,
        e_Return_ProtocolError			= 17,
        e_Return_AlreadyOpen			= 18,
        e_Return_NotOpen				= 19,
        e_Return_ReadOnly				= 20,
        e_Return_NotFound				= 21,
        e_Return_Busy					= 22,
        e_Return_WriteError				= 23,
        e_Return_ReadError				= 24,
        e_Return_NotEnabled				= 25,
        e_Return_AlreadyEnable			= 26,
        e_Return_Timeout				= 27,
        e_Return_NotDefined				= 28,
        e_Return_NotProcessed			= 29,
        e_Return_FileError				= 30,
        e_Return_Halted					= 31,
        e_Return_InvalidObject			= 32,
        e_Return_NotAcknowledge			= 33,
        e_Return_DataError      		= 34
    };

    //! Byte Ordering
    enum t_ByteOrdering
    {
        e_ByteOrdering_LittleEndian		= 0,
        e_ByteOrdering_BigEndian		= 1
    };

    //! Windows RGBQUAD
    struct t_WinRgbQuad
    {
        t_FMT_Uint16     m_usRed;
        t_FMT_Uint16     m_usGreen;
        t_FMT_Uint16     m_usBlu;
        t_FMT_Uint16     m_usAlfa;
    };


    //! Number Representation
    enum t_FMT_NumberRepr
    {
        e_NumberRepr_StraightBinary		= 0,
        e_NumberRepr_C1					= 1,
        e_NumberRepr_C2					= 2,
        e_NumberRepr_SignedMagnitude	= 3,
        e_NumberRepr_OffsetBinary		= 4
    };


    //! Converts a byte buffer into a 16-bit unsigned integer according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Uint16    Uint16FromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a byte buffer into a 32-bit unsigned integer according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Uint32    Uint32FromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a byte buffer into a 64-bit unsigned integer according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Uint64    Uint64FromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a byte buffer into a 16-bit signed integer according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Int16     Int16FromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a byte buffer into a 32-bit signed integer according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Int32     Int32FromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a byte buffer into a 64-bit signed integer according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Int64     Int64FromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a byte buffer into a single precision float number according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Float     FloatFromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a byte buffer into a double precision float number according set byte ordering
    FMTDEF_LIB_DLLSPEC t_FMT_Double    DoubleFromBuf(t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);


    //! Converts a 16-bit unsigned integer into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            Uint16ToBuf(const t_FMT_Uint16& usSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a 32-bit unsigned integer into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            Uint32ToBuf(const t_FMT_Uint32& uiSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a 64-bit unsigned integer into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            Uint64ToBuf(const t_FMT_Uint64& quiSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a 16-bit signed integer into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            Int16ToBuf(const t_FMT_Int16& shSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a 32-bit signed integer into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            Int32ToBuf(const t_FMT_Int32& iSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a 64-bit signed integer into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            Int64ToBuf(const t_FMT_Int64& qiSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a single precision float number into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            FloatToBuf(const t_FMT_Float& fSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Converts a double precision float number into a byte buffer according set byte ordering
    FMTDEF_LIB_DLLSPEC void            DoubleToBuf(const t_FMT_Double& dSrc, t_FMT_Uint8 *pucBuf, t_ByteOrdering bo = e_ByteOrdering_LittleEndian);

    //! Invert bytes uiNumBytes position of buffer pucBuf
    FMTDEF_LIB_DLLSPEC void            InvertByteOrder(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiNumBytes);

    //! Invert order of bits of a 8-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint8     ReflectUint8(t_FMT_Uint8 val);

    //! Invert order of bits of a 16-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint16    ReflectUint16(t_FMT_Uint16 val);

    //! Invert order of bits of a 32-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint32    ReflectUint32(t_FMT_Uint32 val);

    //! Invert order of bits of a 64-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint64    ReflectUint64(t_FMT_Uint64 val);

    //! Integer ceil, returns the smallest integer value greater than or equal to x/d
    FMTDEF_LIB_DLLSPEC t_FMT_Uint64    IntCeil(t_FMT_Uint64 x, t_FMT_Uint64 d);



    //! Shift-rotating left a 8-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint8     ShiftRotatedLeft8(t_FMT_Uint8 ucData, t_FMT_Uint8 ucShift);

    //! Shift-rotating left a 16-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint16    ShiftRotatedLeft16(t_FMT_Uint16 usData, t_FMT_Uint16 usShift);

    //! Shift-rotating left a 32-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint32    ShiftRotatedLeft32(t_FMT_Uint32 uiData, t_FMT_Uint32 uiShift);

    //! Shift-rotating left a 64-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint64    ShiftRotatedLeft64(t_FMT_Uint64 quiData, t_FMT_Uint64 quiShift);


    //! Shift-rotating right a 8-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint8     ShiftRotatedRight8(t_FMT_Uint8 ucData, t_FMT_Uint8 ucShift);

    //! Shift-rotating right a 16-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint16    ShiftRotatedRight16(t_FMT_Uint16 usData, t_FMT_Uint16 usShift);

    //! Shift-rotating right a 32-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint32    ShiftRotatedRight32(t_FMT_Uint32 uiData, t_FMT_Uint32 uiShift);

    //! Shift-rotating right a 64-bit data
    FMTDEF_LIB_DLLSPEC t_FMT_Uint64    ShiftRotatedRight64(t_FMT_Uint64 quiData, t_FMT_Uint64 quiShift);



    //! Set the bit of position uiIdx of ucData with bValue
    FMTDEF_LIB_DLLSPEC void            SetBit(t_FMT_Uint8& ucData, const t_FMT_Uint32 uiIdx, t_FMT_Bool bValue);

    //! Set the bit of position uiIdx of usData with bValue
    FMTDEF_LIB_DLLSPEC void            SetBit(t_FMT_Uint16& usData, const t_FMT_Uint32 uiIdx, t_FMT_Bool bValue);

    //! Set the bit of position uiIdx of uiData with bValue
    FMTDEF_LIB_DLLSPEC void            SetBit(t_FMT_Uint32& uiData, const t_FMT_Uint32 uiIdx, t_FMT_Bool bValue);

    //! Set the bit of position uiIdx of quiData with bValue
    FMTDEF_LIB_DLLSPEC void            SetBit(t_FMT_Uint64& quiData, const t_FMT_Uint32 uiIdx, t_FMT_Bool bValue);

    //! Return the bit of uiIdx position of quiData
    FMTDEF_LIB_DLLSPEC t_FMT_Bool      GetBit(t_FMT_Uint64 quiData, const t_FMT_Uint32 uiIdx);


    //! Set a subset of bits of ucData from uiStart bit of size uiSize with field
    FMTDEF_LIB_DLLSPEC void            SetField(t_FMT_Uint8& ucData, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Uint8 field);

    //! Set a subset of bits of usData from uiStart bit of size uiSize with field
    FMTDEF_LIB_DLLSPEC void            SetField(t_FMT_Uint16& usData, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Uint16 field);

    //! Set a subset of bits of uiData from uiStart bit of size uiSize with field
    FMTDEF_LIB_DLLSPEC void            SetField(t_FMT_Uint32& uiData, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Uint32 field);

    //! Set a subset of bits of quiData from uiStart bit of size uiSize with field
    FMTDEF_LIB_DLLSPEC void            SetField(t_FMT_Uint64& quiData, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Uint64 field);

    //! Set a subset of bits of quiData from uiStart bit of size uiSize with field expressed into a desired number representation
    FMTDEF_LIB_DLLSPEC void            SetSignedField(t_FMT_Uint64& quiData, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiSize, t_FMT_Int64 field,
                                                      t_FMT_NumberRepr numrep = e_NumberRepr_C2);


    //! Extract a subset of bits from uiStart bit of size uiSize
    FMTDEF_LIB_DLLSPEC t_FMT_Uint64    GetField(t_FMT_Uint64 quiData, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize);

    //!	Extract a subset of bits from uiStart bit of size uiSize expressed into a desired number representation
    FMTDEF_LIB_DLLSPEC t_FMT_Int64     GetSignedField(t_FMT_Uint64 quiData, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiSize, t_FMT_NumberRepr numrep = e_NumberRepr_C2);


    //! Set a subset of bits of quiData from uiStart bit of number of digits uiDigits with field
    FMTDEF_LIB_DLLSPEC void            SetBcdField(t_FMT_Uint64& quiData, t_FMT_Uint32 uiPos, t_FMT_Uint32 uiDigits, t_FMT_Uint64 field);

    //! Extract a subset of bits from uiStart bit of digits uiDigits
    FMTDEF_LIB_DLLSPEC t_FMT_Uint64    GetBcdField(t_FMT_Uint64 quiData, t_FMT_Uint32 uiStart, t_FMT_Uint32 uiDigits);


    //! Converts a 32-bit or 24-bit color inside an unsigned 32-bit to a t_WinRgbQuad
    FMTDEF_LIB_DLLSPEC t_WinRgbQuad    ToWinRgbQuad32Bit(t_FMT_Uint32 uiColor);
}


#endif
