#pragma once

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <mmsystem.h> 
#include <stdlib.h>     
#include <time.h>      
#include "Thrd.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#pragma comment(lib, "winmm.lib")

#define RX_BUF_SIZE		(1000000)
#define PKT_BUF_SIZE	(10000)