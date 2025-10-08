//***************************************************************************
//
// Module:		MaintMpp.cpp
//
// Description:	Maintenance Point To Point Protocol applied to M345 MFD
//				
// Environment:	Microsoft Visual C++	
//
// Version control
//
// Rev.		Data		Author			Modified		
// --------------------------------------------------------------------------
//	1.1		26-05-2014	M.Forzieri		First issue
// --------------------------------------------------------------------------
//***************************************************************************

#include "stdafx.h"
#include "MaintMpp.h"


// *************************************************************************************
// *************************************************************************************
//	Class CMaintMpp
// *************************************************************************************
// *************************************************************************************


// -----------------------------------------------------------------------------------
//	CMaintMpp
// -----------------------------------------------------------------------------------

CMaintMpp::CMaintMpp() : CFMT_CommMppClient()
{
}

// -----------------------------------------------------------------------------------
//	~CMaintMpp
// -----------------------------------------------------------------------------------

CMaintMpp::~CMaintMpp()
{
}


// -----------------------------------------------------------------------------------
//	CMaintMpp::ProcCommandList
// -----------------------------------------------------------------------------------

t_FMT_Uint32 CMaintMpp::ProcCommandList(SCommand* pComList,t_FMT_Uint32 dwNC,t_FMT_Uint32 dwTimeout,t_FMT_Uint32 dwRetries)
{
	return CFMT_CommMppClient::ProcCommandList(MSU_MAINT_MPP_UNIT_ADDRESS, 0, pComList, dwNC, dwTimeout, dwRetries);
}


// -----------------------------------------------------------------------------------
//	CMaintMpp::WriteMemoryBuffer
// -----------------------------------------------------------------------------------

t_FMT_Uint32 CMaintMpp::WriteMemoryBuffer(SBufferTransferProperty *pBufferTransferProperty)
{
	return CFMT_CommMppClient::WriteMemoryBuffer(MSU_MAINT_MPP_UNIT_ADDRESS, 0, pBufferTransferProperty);
}

// -----------------------------------------------------------------------------------
//	CMaintMpp::ReadMemoryBuffer
// -----------------------------------------------------------------------------------

t_FMT_Uint32 CMaintMpp::ReadMemoryBuffer(SBufferTransferProperty *pBufferTransferProperty)
{
	return CFMT_CommMppClient::ReadMemoryBuffer(MSU_MAINT_MPP_UNIT_ADDRESS, 0, pBufferTransferProperty);
}

// -----------------------------------------------------------------------------------
//	CMaintMpp::EraseMemoryBuffer
// -----------------------------------------------------------------------------------

t_FMT_Uint32 CMaintMpp::EraseMemoryBuffer(SBufferTransferProperty *pBufferTransferProperty)
{
	return CFMT_CommMppClient::EraseMemoryBuffer(MSU_MAINT_MPP_UNIT_ADDRESS, 0, pBufferTransferProperty);
}

