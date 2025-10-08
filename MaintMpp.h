#pragma once

// *************************************************************************************
// *************************************************************************************
//	Class CMaintMpp
// *************************************************************************************
// *************************************************************************************

// --- MPP Unit Address --------------------------------------

#define MSU_MAINT_MPP_UNIT_ADDRESS			0x010203		// *** TBD


#define MEM_CNF_MPP_START_ADDRESS			0x08000000
#define MEM_BLG_MPP_START_ADDRESS			0x09000000



class CMaintMpp : public CFMT_CommMppClient
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// --- t_MppRegisters ---------------------

	enum t_MppRegisters
	{
		e_MppReg_Ctrl			= 0x01,
		e_MppReg_Temp			= 0x02,
		e_MppReg_Brt			= 0x03,
		e_MppReg_Pat			= 0x04,
		e_MppReg_Stat			= 0x08,
		e_MppReg_Eti			= 0x09,

		e_MppReg_Adc1			= 0x10,
		e_MppReg_Adc14			= 0x1D,

	};

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:


public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CMaintMpp();
	virtual ~CMaintMpp();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:



public:

	t_FMT_Uint32	ProcCommandList(SCommand* pComList,t_FMT_Uint32 dwNC,t_FMT_Uint32 dwTimeout=500,t_FMT_Uint32 dwRetries=0);

	t_FMT_Uint32	WriteMemoryBuffer(SBufferTransferProperty *pBufferTransferProperty);
	t_FMT_Uint32	ReadMemoryBuffer(SBufferTransferProperty *pBufferTransferProperty);
	t_FMT_Uint32	EraseMemoryBuffer(SBufferTransferProperty *pBufferTransferProperty);

};
