// =====================================================================================
/**
 * @file					FMT_HdwManager.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Hardware Manager
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MANAGER_H
#define FMTDEF_HDW_MANAGER_H

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

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif

#ifndef FMTDEF_CRC_H
#include "FMT_Crc.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_TIMER_H
#include "FMT_HdwTimer.h"
#endif

#ifndef FMTDEF_HDW_DEVICE_H
#include "FMT_HdwDevice.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_HDWMANAGER_SOURCE_BASE_PORT			58000
#define FMTDEF_HDWMANAGER_SOURCE_TOT_PORTS			4000


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwManager
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwManager : public CFMT_HdwObject
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

    // --- CPortDescriptor --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptor : public CFMT_Object
    {
    public:
        CFMT_HdwDevice		*m_pDevice;
        CFMT_HdwPort		*m_pPort;
        CFMT_String         m_sIntChannel;
        t_FMT_Uint32		m_uiPortAbsoluteNum;
        CFMT_String			m_sManufacturer;
        CFMT_String			m_sFullName;
        t_FMT_Uint32		m_uiBusType;
        CFMT_String			m_sHardwareID;
        CFMT_String			m_sSN;
        CFMT_String			m_sRevision;
        CFMT_String			m_sDescription;

        CPortDescriptor();

	    t_FMT_Bool operator==(const CPortDescriptor& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}
	    t_FMT_Bool operator!=(const CPortDescriptor& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CPortDescriptor& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CPortDescriptor& s);

    };

    // --- CDeviceList --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDeviceList : public CFMT_List<CFMT_HdwDevice*>
    {
    };

    // --- CDeviceVector --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDeviceVector : public CFMT_Vector<CFMT_HdwDevice*>
    {
    };


    // --- CPortDescriptorsVector --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptorsVector : public CFMT_Vector<CPortDescriptor>
    {
    };

    // --- CPortDescriptorsMatrix --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptorsMatrix : public CFMT_Vector<CPortDescriptorsVector>
    {
    };



public:

    // --- t_PortIdStatus ---------------------------------------------

    enum t_PortIdStatus
    {
        e_PortIdStatus_Unassigned		= 0,
        e_PortIdStatus_Present			= 1
    };

    // --- t_InitResult ---------------------------------------------

    enum t_EnumResult
    {
        e_EnumResult_ToBeChecked		= 0,
        e_EnumResult_NotPresent			= 1,
        e_EnumResult_Present			= 2,
        e_EnumResult_Remapped			= 3
    };

    // --- t_InitMode ---------------------------------------------

    enum t_EnumMode
    {
        e_EnumMode_Clear				= 0,
        e_EnumMode_Keep					= 1,
        e_EnumMode_Remap				= 2
    };


    // --- CPortIdentifier --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortIdentifier : public CFMT_Object
    {
    protected:

        CFMT_String				m_sKey;
        t_FMT_Uint32			m_uiPortType;
        t_FMT_Uint32			m_uiAbsNum;
        CFMT_String				m_sManufacturer;
        CFMT_String				m_sFullName;
        CFMT_String				m_sSN;
        CFMT_String				m_sRevision;
        CFMT_String				m_sIntChannel;


        t_FMT_Uint32			CalcCrc(const CFMT_String& sKey);
        void					AppendChecksum(CFMT_String& sKey);

    public:

        friend class CFMT_HdwManager;

        CFMT_Crc                m_Crc;
        t_FMT_Uint32			m_uiStatus;


        CPortIdentifier();
		CPortIdentifier&		operator=(const CPortIdentifier& op);

        void					Clear();

        t_FMT_Uint32			Set(const CFMT_String& sKey);
        t_FMT_Uint32			Set(t_FMT_Uint32 uiPortType, t_FMT_Uint32 uiAbsNum, CFMT_String sManufacturer,
                                    CFMT_String sFullName, CFMT_String sRevision, CFMT_String sSN, t_FMT_Uint32 uiIntChannel);
        t_FMT_Uint32			Set(t_FMT_Uint32 uiPortType,CPortDescriptor& src);

        CFMT_String				GetKeyString();

        t_FMT_Uint32			Get(t_FMT_Uint32 *puiPortType,CPortDescriptor *pSrc);
        t_FMT_Uint32			Get(t_FMT_Uint32 *puiPortType, t_FMT_Uint32 *puiAbsNum, CFMT_String *psManufacturer,
                                    CFMT_String *psFullName, CFMT_String *psRevision, CFMT_String *psSN, t_FMT_Uint32 *puiIntChannel);

        t_FMT_Uint32			GetPortType();
        t_FMT_Uint32			GetAbsNum();
        CFMT_String				GetManufacturer();
        CFMT_String				GetFullName();
        CFMT_String				GetSN();
        CFMT_String             GetRevision();
		CFMT_String				GetIntChannel();

        static t_FMT_Bool		IsValid(const CFMT_String& sKey);

        t_FMT_Bool				CheckMatch(const CFMT_String& sKey);
        t_FMT_Bool				CheckMatch(CPortIdentifier& pid);
    };


    // --- CPortInfo --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortInfo : public CFMT_Object
    {
    public:

        t_FMT_Uint32		m_uiPortNum;
        CFMT_String			m_sManufacturer;
        CFMT_String			m_sFullName;
        t_FMT_Uint32		m_uiBusType;
        CFMT_String			m_sHardwareID;
        CFMT_String			m_sSN;
        CFMT_String			m_sRevision;
        CFMT_String			m_sIntChannel;
        CPortIdentifier		m_PortID;
        CFMT_String			m_sDescription;

        CPortInfo();

	    //! Assignment operator from homogeneous object
	    CPortInfo&			operator=(const CPortInfo& op);

	    t_FMT_Bool operator==(const CPortInfo& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}
	    t_FMT_Bool operator!=(const CPortInfo& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CPortInfo& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CPortInfo& s);

    };


    // --- CParameters --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters
    {
    public:

        t_FMT_Uint32		m_uiHdwTimerPeriod;

        CParameters();
    };


    // --- CPortDescriptorsList --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptorsList : public CFMT_List<CPortDescriptor>
    {
    };


    // --- CPortInfoVector ------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortInfoVector : public CFMT_Vector<CPortInfo>
    {
    };


    // --- CInitPortDesc ------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CInitPortDesc : public CFMT_HdwObject
    {
    public:

        CFMT_String		m_sActualKey;
        CFMT_String		m_sNewKey;
        t_FMT_Uint32	m_uiEnumResult;

        CInitPortDesc();

    };

    // --- CSysEthPort ------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CSysEthPort
	{
	public:
		t_FMT_Bool			m_bUsed;
		t_FMT_Uint16		m_usPort;

		CSysEthPort();

	    t_FMT_Bool operator==(const CSysEthPort& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}
	    t_FMT_Bool operator!=(const CSysEthPort& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CSysEthPort& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CSysEthPort& s);

	};

    // --- CSysEthPortVector ------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CSysEthPortVector : public CFMT_Vector<CSysEthPort>
    {
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Bool						m_bRun;                 //! Running flag
    t_FMT_Uint32					m_uiTotalPortTypes;     //! Total Port Types
    CDeviceVector					m_DeviceVector;         //! Managed Devices as vector
    CFMT_HdwTimer					m_HdwTimer;             //! The hardware Timer
    CDeviceList						m_DeviceList;           //! Managed Devices as list
    CPortDescriptorsMatrix			m_PortDescriptors;      //! Port Descriptors
    CParameters						m_Parameters;           //! Manager Parameters
	CSysEthPortVector				m_vSysEthPort;			//! System Ethernet Port				
	t_FMT_Uint32					m_uiLastSysEthPortIdx;	//! Last used Ethernet Port Index
	CFMT_Mutex						m_SysEthPortMutex;		//! Mutex for System Ethernet Port


public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwManager();

    //! Destructor
    virtual ~CFMT_HdwManager();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Destroy the device list
    void				DestroyDeviceList();

    //! Get the first absolute reference of a port
    t_FMT_Uint32		GetFirstFreeAbsoluteNum(t_FMT_Uint32 uiPortType, CPortDescriptorsList& list);

    //! Get the first absolute reference of a port, excluding the ones associated to pPortList
    t_FMT_Uint32		GetFirstFreeAbsoluteNum(t_FMT_Uint32 uiPortType, CPortDescriptorsList& list, CInitPortDesc *pPortList, t_FMT_Uint32 uiSize);


    //! Start the main timer for hardware device processing
    t_FMT_Uint32		StartMainTimer(t_FMT_Uint32 uiPeriod);

    //! Stop the main timer for hardware device processing
    t_FMT_Uint32		StopMainTimer();

    //! Hardware Timer Handler
    static void         HdwTimerHandler(t_FMT_Uint64 quiTimerCnt, void *pParam);

    static t_FMT_Int8	PortSorter(const CPortDescriptor& op1, const CPortDescriptor& op2);

public:

    //! Check if manager is running
    t_FMT_Bool			IsRunning() const;

    //! Destroy all manager content
    t_FMT_Uint32		Destroy();

    //! Attach a device to the manager
    t_FMT_Uint32		AttachDevice(CFMT_HdwDevice *pDevice);

    //! Enumerate all devices and related ports added to the manager
    t_FMT_Uint32		Enumerate();

    //! Enumerate all devices and related ports added to the manager applying the initialization mode
    t_FMT_Uint32		Enumerate(CInitPortDesc *pPortList, t_FMT_Uint32 uiSize, t_FMT_Uint32 uiInitMode);

    //! Run hardware management
    t_FMT_Uint32		Run();

    //! Run hardware management
    t_FMT_Uint32		Run(CParameters param);

    //! Stop hardware management
    t_FMT_Uint32		Stop();

    //! Return the port descriptor of a given type
    t_FMT_Uint32		GetPortList(t_FMT_Uint32 uiPortType,CPortInfoVector& desc);

    //! Return the port from its number
    CFMT_HdwPort*		GetPort(t_FMT_Uint32 uiPortType, t_FMT_Uint32 dwPortNum);

    //! Return a free system ethernet port
    t_FMT_Uint32		GetSysEthPort(t_FMT_Uint16& usPort);

    //! Release an ethernet port
    void				ReleaseSysEthPort(t_FMT_Uint16 usPort);
};



#endif







