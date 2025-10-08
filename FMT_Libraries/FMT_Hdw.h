// =====================================================================================
/**
 * @file					FMT_Hdw.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					21/04/2021
 * @brief					Library includes
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][06/09/2021]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_H
#define FMTDEF_HDW_H

// =====================================================================================
//	INCLUDES
// =====================================================================================

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_SOCKET_H
#include "FMT_HdwSocket.h"
#endif

#ifndef FMTDEF_HDW_UDPSOCKET_H
#include "FMT_HdwUdpSocket.h"
#endif

#ifndef FMTDEF_HDW_TCPCLIENTSOCKET_H
#include "FMT_HdwTcpClientSocket.h"
#endif

#ifndef FMTDEF_HDW_TCPSERVERSOCKET_H
#include "FMT_HdwTcpServerSocket.h"
#endif

#ifndef FMTDEF_HDW_TIMER_H
#include "FMT_HdwTimer.h"
#endif

#ifndef FMTDEF_HDW_EVENT_H
#include "FMT_HdwEvent.h"
#endif

#ifndef FMTDEF_HDW_PORT_H
#include "FMT_HdwPort.h"
#endif

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

#ifndef FMTDEF_HDW_DEVICE_H
#include "FMT_HdwDevice.h"
#endif

#ifndef FMTDEF_HDW_HOEDDEVICE_H
#include "FMT_HdwHoeDevice.h"
#endif

#ifndef FMTDEF_HDW_MANAGER_H
#include "FMT_HdwManager.h"
#endif

#ifndef FMTDEF_HDW_BYTEINBUFFERSERVICE_H
#include "FMT_HdwByteInBufferService.h"
#endif

#ifndef FMTDEF_HDW_BYTEOUTBUFFERSERVICE_H
#include "FMT_HdwByteOutBufferService.h"
#endif

#ifndef FMTDEF_HDW_UARTPORT_H
#include "FMT_HdwUartPort.h"
#endif

#ifndef FMTDEF_HDW_STDUARTDEVICE_H
#include "FMT_HdwStdUartDevice.h"
#endif

#ifndef FMTDEF_HDW_DATAGENERATORSERVICE_H
#include "FMT_HdwDataGeneratorService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429MESSAGE_H
#include "FMT_HdwArinc429Message.h"
#endif

#ifndef FMTDEF_HDW_ARINC429RXPORT_H
#include "FMT_HdwArinc429RxPort.h"
#endif

#ifndef FMTDEF_HDW_ARINC429TXPORT_H
#include "FMT_HdwArinc429TxPort.h"
#endif

#ifndef FMTDEF_HDW_DISCRETESETPORT_H
#include "FMT_HdwDiscreteSetPort.h"
#endif

#ifndef FMTDEF_HDW_ARINC429INBUFFERSERVICE_H
#include "FMT_HdwArinc429InBufferService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429OUTBUFFERSERVICE_H
#include "FMT_HdwArinc429OutBufferService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429OUTLBLSERVICE_H
#include "FMT_HdwArinc429OutLbloService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429INLBLSERVICE_H
#include "FMT_HdwArinc429InLbloService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429BYTEINBUFFERSERVICE_H
#include "FMT_HdwArinc429ByteInBufferService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429BYTEOUTBUFFERSERVICE_H
#include "FMT_HdwArinc429ByteOutBufferService.h"
#endif

#ifndef FMTDEF_HDW_FTDIUARTBRIDGEDDEVICE_H
#include "FMT_HdwFtdiUartBridgedDevice.h"
#endif

#ifndef FMTDEF_HDW_SIGNALSERVICE_H
#include "FMT_HdwSignalService.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553PORT_H
#include "FMT_HdwMilStd1553Port.h"
#endif

#ifndef FMTDEF_HDW_CANMESSAGE_H
#include "FMT_HdwCanMessage.h"
#endif

#ifndef FMTDEF_HDW_CANPORT_H
#include "FMT_HdwCanPort.h"
#endif

#ifndef FMTDEF_HDW_CANINBUFFERSERVICE_H
#include "FMT_HdwCanInBufferService.h"
#endif

#ifndef FMTDEF_HDW_CANOUTBUFFERSERVICE_H
#include "FMT_HdwCanOutBufferService.h"
#endif

#ifndef FMTDEF_HDW_CANBYTEINBUFFERSERVICE_H
#include "FMT_HdwCanByteInBufferService.h"
#endif

#ifndef FMTDEF_HDW_CANBYTEOUTBUFFERSERVICE_H
#include "FMT_HdwCanByteOutBufferService.h"
#endif


#ifndef FMTDEF_HDW_MILSTD1553SINGLERTSERVICE_H
#include "FMT_HdwMilStd1553SingleRtService.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553BCSERVICE_H
#include "FMT_HdwMilStd1553BcService.h"
#endif

#ifndef FMTDEF_HDW_I2CPORT_H
#include "FMT_HdwI2CPort.h"
#endif

#ifndef FMTDEF_HDW_SPIPORT_H
#include "FMT_HdwSpiPort.h"
#endif

#ifndef LFMT_HDW_I2CMASTERSERVICE_H
#include "FMT_HdwI2CMasterService.h"
#endif

#ifndef LFMT_HDW_SPIMASTERSERVICE_H
#include "FMT_HdwSpiMasterService.h"
#endif

#ifndef FMTDEF_HDW_PROTOCOL_H
#include "FMT_HdwProtocol.h"
#endif




#ifndef FMTDEF_HDW_FMTNETAVIOX96DEVICE_H
#include "FMT_HdwFmtNetAvioX96Device.h"
#endif

#ifndef FMTDEF_HDW_FMTNETARINC429X16DEVICE_H
#include "FMT_HdwFmtNetArinc429x16Device.h"
#endif

#ifndef FMTDEF_HDW_FMTUSB2ARINC429X2DEVICE_H
#include "FMT_HdwFmtUsb2Arinc429x2Device.h"
#endif

#ifndef FMTDEF_HDW_FMTNETUARTX6DEVICE_H
#include "FMT_HdwFmtNetUartX6Device.h"
#endif



#ifndef FMTDEF_COMPILE_OS_LINUX

#ifndef FMTDEF_HDW_FMTMULTIARINC429DEVICE_H
#include "FMT_HdwFmtMultiArinc429Device.h"
#endif

#ifndef FMTDEF_HDW_FMTMULTICOMMDEVICE_H
#include "FMT_HdwFmtMulticommDevice.h"
#endif

#ifndef FMTDEF_HDW_FMTMULTICOMMSMALLDEVICE_H
#include "FMT_HdwFmtMulticommSmallDevice.h"
#endif

#ifndef FMTDEF_HDW_FMTUSB2CANDEVICE_H
#include "FMT_HdwFmtUsb2CanDevice.h"
#endif

#ifndef FMTDEF_HDW_FMTUSB2CANX2DEVICE_H
#include "FMT_HdwFmtUsb2CanX2Device.h"
#endif

#ifndef FMTDEF_HDW_FMTUSB2SSIDEVICE_H
#include "FMT_HdwFmtUsb2SsiDevice.h"
#endif

#ifndef FMTDEF_HDW_UDPEMULATORDEVICE_H
#include "FMT_HdwUdpEmulatorDevice.h"
#endif

#endif

#endif







