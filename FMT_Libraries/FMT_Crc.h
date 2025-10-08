// =====================================================================================
/**
 * @file					FMT_Crc.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					31/03/2018
 * @brief					CRC computation
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][31/03/2018]
 */
// =====================================================================================



#ifndef FMTDEF_CRC_H
#define FMTDEF_CRC_H

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




// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Crc
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_Crc : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    //! CRC type
    enum t_CrcType
    {
        e_CrcType_Undefined     = 0,
        e_CrcType_8             = 1,
        e_CrcType_16            = 2,
        e_CrcType_32            = 3,
        e_CrcType_64            = 4
    };


    //! Standard CRC
    enum t_StdCrc
    {
        e_StdCrc_Crc8               = 0x0000,
        e_StdCrc_Crc8_Aes           = 0x0001,
        e_StdCrc_Crc8_Autosar       = 0x0002,
        e_StdCrc_Crc8_Bluetooth     = 0x0003,
        e_StdCrc_Crc8_Cdma2000      = 0x0004,
        e_StdCrc_Crc8_Darc          = 0x0005,
        e_StdCrc_Crc8_DowCrc        = 0x0006,
        e_StdCrc_Crc8_DvbS2         = 0x0007,
        e_StdCrc_Crc8_Ebu           = 0x0008,
        e_StdCrc_Crc8_GsmA          = 0x0009,
        e_StdCrc_Crc8_GsmB          = 0x000A,
        e_StdCrc_Crc8_ICode         = 0x000B,
        e_StdCrc_Crc8_Itu           = 0x000C,
        e_StdCrc_Crc8_Ltu           = 0x000D,
        e_StdCrc_Crc8_Maxim         = 0x000E,
        e_StdCrc_Crc8_OpenSafety    = 0x000F,
        e_StdCrc_Crc8_Rohc          = 0x0010,
        e_StdCrc_Crc8_SaeJ1850      = 0x0011,
        e_StdCrc_Crc8_Wcdma         = 0x0012,

        e_StdCrc_Crc16              = 0x1000,
        e_StdCrc_CrcA               = 0x1001,
        e_StdCrc_Crc16_Acorn        = 0x1002,
        e_StdCrc_Crc16_Arc          = 0x1003,
        e_StdCrc_Crc16_AugCcitt     = 0x1004,
        e_StdCrc_Crc16_Buypass      = 0x1005,
        e_StdCrc_Crc16_Ccitt        = 0x1006,
        e_StdCrc_Crc_Ccitt          = 0x1007,
        e_StdCrc_Crc16_CcittFalse   = 0x1008,
        e_StdCrc_Crc_CcittTrue      = 0x1009,
        e_StdCrc_Crc16_Cmda2000     = 0x100A,
        e_StdCrc_Crc16_Cms          = 0x100B,
        e_StdCrc_Crc16_CrcB         = 0x100C,
        e_StdCrc_Crc16_Darc         = 0x100D,
        e_StdCrc_Crc16_Dds110       = 0x100E,
        e_StdCrc_Crc16_DectR        = 0x100F,
        e_StdCrc_Crc16_DectX        = 0x1010,
        e_StdCrc_Crc16_Dnp          = 0x1011,
        e_StdCrc_Crc16_En13757      = 0x1012,
        e_StdCrc_Crc16_Epc          = 0x1013,
        e_StdCrc_Crc16_Genibus      = 0x1014,
        e_StdCrc_Crc16_Gsm          = 0x1015,
        e_StdCrc_Crc16_Ibm          = 0x1016,
        e_StdCrc_Crc16_IbmSdlc      = 0x1017,
        e_StdCrc_Crc16_Icode        = 0x1018,
        e_StdCrc_Crc16_Iec61158_2   = 0x1019,
        e_StdCrc_Crc16_IsoHdlc      = 0x101A,
        e_StdCrc_IsoIecFcd14443_3   = 0x101B,
        e_StdCrc_Crc16_Kermit       = 0x101C,
        e_StdCrc_Crc16_Lha          = 0x101D,
        e_StdCrc_Crc16_Lj1200       = 0x101E,
        e_StdCrc_Crc16_Lte          = 0x101F,
        e_StdCrc_Crc16_Maxim        = 0x1020,
        e_StdCrc_Crc16_Mcrf4xx      = 0x1021,
        e_StdCrc_Crc16_Modbus       = 0x1022,
        e_StdCrc_Crc16_OpenSafetyA  = 0x1023,
        e_StdCrc_Crc16_OpenSafetyB  = 0x1024,
        e_StdCrc_Crc16_Profibus     = 0x1025,
        e_StdCrc_Crc16_RCrc16       = 0x1026,
        e_StdCrc_Crc16_Riello       = 0x1027,
        e_StdCrc_Crc16_SpiFujitsu   = 0x1028,
        e_StdCrc_Crc16_T10Dif       = 0x1029,
        e_StdCrc_Crc16_Teledisk     = 0x102A,
        e_StdCrc_Crc16_Tms37157     = 0x102B,
        e_StdCrc_Crc16_Umts         = 0x102C,
        e_StdCrc_Crc16_Usb          = 0x102D,
        e_StdCrc_Crc16_Verifone     = 0x102E,
        e_StdCrc_Crc16_XCrc16       = 0x102F,
        e_StdCrc_Crc16_X25          = 0x1030,
        e_StdCrc_XModem             = 0x1031,
        e_StdCrc_ZModem             = 0x1032,
        e_StdCrc_MilStd1760         = 0x1033,
        e_StdCrc_Crc16_Arinc615     = 0x1034,

        e_StdCrc_Crc32              = 0x3000,
        e_StdCrc_Crc32_Adccp        = 0x3001,
        e_StdCrc_Pkzip              = 0x3002,
        e_StdCrc_Crc32_Autosar      = 0x3003,
        e_StdCrc_Crc32_Bzip2        = 0x3004,
        e_StdCrc_Crc32_Aal5         = 0x3005,
        e_StdCrc_Crc32_DectB        = 0x3006,
        e_StdCrc_BCrc32             = 0x3007,
        e_StdCrc_Crc32_C            = 0x3008,
        e_StdCrc_Crc32_Iscsi        = 0x3009,
        e_StdCrc_Crc32_Castagnoli   = 0x300A,
        e_StdCrc_Crc32_Interlaken   = 0x300B,
        e_StdCrc_Crc32_D            = 0x300C,
        e_StdCrc_Crc32_Mpeg2        = 0x300D,
        e_StdCrc_Crc32_Posix        = 0x300E,
        e_StdCrc_Cksum              = 0x300F,
        e_StdCrc_Crc32_Q            = 0x3010,
        e_StdCrc_Jamcrc             = 0x3011,
        e_StdCrc_Xfer               = 0x3012,
        e_StdCrc_Crc32_Arinc615     = 0x3013,

        e_StdCrc_Crc64              = 0x5000,
        e_StdCrc_Crc64_GoIso        = 0x5001,
        e_StdCrc_Crc64_We           = 0x5002,
        e_StdCrc_Crc64_Xz           = 0x5003,
        e_StdCrc_Crc64_GoEcma       = 0x5004
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    //! CRC Type
    t_CrcType       m_Type;

    //! Standard Type
    t_StdCrc        m_Std;

    //! Polynomial CRC
    t_FMT_Bool      m_bIsPolynomial;

    //! CRC Size
    t_FMT_Uint32    m_uiSize;

    //! Polynomial
    t_FMT_Uint64    m_quiPolynomial;

    //! Input Reflected flag
    t_FMT_Bool      m_bInputReflected;

    //! Output Reflected flag
    t_FMT_Bool      m_bOutputReflected;

    //! Seed
    t_FMT_Uint64    m_quiSeed;

    //! Final Xor
    t_FMT_Uint64    m_quiFinalXor;

    //! Byte Flip Table
    t_FMT_Uint8     m_pucByteFlip[256];

    //! CRC-8 Table
    t_FMT_Uint8     *m_pucCrcTable;

    //! CRC-16 Table
    t_FMT_Uint16    *m_pusCrcTable;

    //! CRC-32 Table
    t_FMT_Uint32    *m_puiCrcTable;

    //! CRC-64 Table
    t_FMT_Uint64    *m_pquiCrcTable;


public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_Crc();

    //! Full parameters constructor
    CFMT_Crc(t_CrcType type, t_FMT_Uint64 quiPoly, t_FMT_Uint64 quiSeed, t_FMT_Bool bInReflected, t_FMT_Bool bOutReflected, t_FMT_Uint64 quiFinalXor = 0);

    //! Constructor from standard type
    CFMT_Crc(t_StdCrc std);

    //! Constructor from homogeneous operator
    CFMT_Crc(const CFMT_Crc& op);

    //! Destructor
    virtual ~CFMT_Crc();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Build the byte inversion table
    void            BuildByteInversionTable();

    //! Build the CRC Table
    void            BuildCrcTable();

    //! Destroy CRC Tables
    void            DestroyCrcTables();

    //! Build the CRC Table for CRC-8
    void            BuildCrc8Table();

    //! Build the CRC Table for CRC-16
    void            BuildCrc16Table();

    //! Build the CRC Table for CRC-32
    void            BuildCrc32Table();

    //! Build the CRC Table for CRC-64
    void            BuildCrc64Table();


    //! Compute the CRC for a 4-bit -> 8-bit CRC
    void            ComputePolynomial(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint8 *pucCrc, t_FMT_Bool bUpdate);

    //! Compute the CRC for a 4-bit -> 8-bit CRC
    void            ComputePolynomial(CFMT_Uint8Vector& v, t_FMT_Uint8 *pucCrc, t_FMT_Bool bUpdate);


    //! Compute the CRC for a 9-bit -> 16-bit CRC
    void            ComputePolynomial(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint16 *pusCrc, t_FMT_Bool bUpdate);

    //! Compute the CRC for a 9-bit -> 16-bit CRC
    void            ComputePolynomial(CFMT_Uint8Vector& v, t_FMT_Uint16 *pusCrc, t_FMT_Bool bUpdate);


    //! Compute the CRC for a 17-bit -> 32-bit CRC
    void            ComputePolynomial(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint32 *puiCrc, t_FMT_Bool bUpdate);

    //! Compute the CRC for a 17-bit -> 32-bit CRC
    void            ComputePolynomial(CFMT_Uint8Vector& v, t_FMT_Uint32 *puiCrc, t_FMT_Bool bUpdate);


    //! Compute the CRC for a 33-bit -> 64-bit CRC
    void            ComputePolynomial(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint64 *pquiCrc, t_FMT_Bool bUpdate);

    //! Compute the CRC for a 33-bit -> 64-bit CRC
    void            ComputePolynomial(CFMT_Uint8Vector& v, t_FMT_Uint64 *pquiCrc, t_FMT_Bool bUpdate);

    //!	Compute the MIL-STD_1760 Checksum
    void            Compute_MilStd1760(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint16 *pusCrc, t_FMT_Bool bUpdate);

    //! Compute the CRC for 32-bit Arinc615
    void            ComputeCrc32_Arinc615(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint32 *puiCrc, t_FMT_Bool bUpdate);

    //! Compute the CRC for 32-bit Arinc615
    void            ComputeCrc32_Arinc615(CFMT_Uint8Vector& v, t_FMT_Uint32 *puiCrc, t_FMT_Bool bUpdate);


    //! Assignment function
    void            DataCopy(const CFMT_Crc& op);

public:

    //! Get CRC size
    t_FMT_Uint32    GetSize() const;

    //! Get CRC polynomial
    t_FMT_Uint64    GetPolynomial() const;

    //! Get CRC seed
    t_FMT_Uint64    GetSeed() const;

    //! Return input reflected flag
    t_FMT_Bool      IsInputReflected() const;

    //! Return output reflected flag
    t_FMT_Bool      IsOuputReflected() const;

    //! Return final xor
    t_FMT_Uint64    GetFinalXor() const;

    //! Create polynomial CRC with full parameters
    void            CreatePolynomial(t_CrcType type, t_FMT_Uint64 quiPoly, t_FMT_Uint64 quiSeed, t_FMT_Bool bInReflected, t_FMT_Bool bOutReflected, t_FMT_Uint64 quiFinalXor = 0);

    //! Create the CRC from a standard
    void            Create(t_StdCrc std);


    //! Compute the CRC for a 4-bit -> 8-bit CRC
    void            Compute(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint8 *pucCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the CRC for a 4-bit -> 8-bit CRC
    void            Compute(CFMT_Uint8Vector& v, t_FMT_Uint8 *pucCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the check value for a 4-bit -> 8-bit CRC
    void            ComputeCheckValue(t_FMT_Uint8 *pucCheckValue);


    //! Compute the CRC for a 9-bit -> 16-bit CRC
    void            Compute(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint16 *pusCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the CRC for a 9-bit -> 16-bit CRC from 16-bit buffer
    void            Compute(t_FMT_Uint16 *pusBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint16 *pusCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the CRC for a 9-bit -> 16-bit CRC
    void            Compute(CFMT_Uint8Vector& v, t_FMT_Uint16 *pusCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the check value for a 9-bit -> 16-bit CRC
    void            ComputeCheckValue(t_FMT_Uint16 *pusCheckValue);


    //! Compute the CRC for a 17-bit -> 32-bit CRC
    void            Compute(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint32 *puiCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the CRC for a 17-bit -> 32-bit CRC
    void            Compute(CFMT_Uint8Vector& v, t_FMT_Uint32 *puiCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the check value for a 17-bit -> 32-bit CRC
    void            ComputeCheckValue(t_FMT_Uint32 *puiCheckValue);


    //! Compute the CRC for a 33-bit -> 64-bit CRC
    void            Compute(t_FMT_Uint8 *pucBuf, t_FMT_Uint64 quiBufSize, t_FMT_Uint64 *pquiCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the CRC for a 33-bit -> 64-bit CRC
    void            Compute(CFMT_Uint8Vector& v, t_FMT_Uint64 *pquiCrc, t_FMT_Bool bUpdate = FMTDEF_FALSE);

    //! Compute the check value for a 33-bit -> 64-bit CRC
    void            ComputeCheckValue(t_FMT_Uint64 *pquiCheckValue);


    //! Assignment operator
    CFMT_Crc&       operator=(const CFMT_Crc& op);

};



#endif







