#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h> 
#include <time.h>
#include <UrlMon.h>
#include <Shlobj.h>
#include "detours\detours.h"

#define __DEBUG__
#define __OUTTMPFILE__
//#define __MSGBOx__
#define LSHL									1
#define LDBG									2
#define LROP									3

#define MCEDP_ERROR_BASE						0x13000000
#define MCEDP_STATUS_SUCCESS					MCEDP_ERROR_BASE
#define MCEDP_STATUS_NO_MORE_ENTRIES			MCEDP_ERROR_BASE+1
#define MCEDP_STATUS_INTERNAL_ERROR				MCEDP_ERROR_BASE+2
#define MCEDP_STATUS_PARTIAL_DISASSEMBLE		MCEDP_ERROR_BASE+3
#define MCEDP_STATUS_INVALID_ACCESS				MCEDP_ERROR_BASE+4
#define MCEDP_STATUS_VALID_ACCESS				MCEDP_ERROR_BASE+5
#define MCEDP_STATUS_GENERAL_FAIL				MCEDP_ERROR_BASE+6
#define MCEDP_STATUS_SHELLCODE_FLAG_NOT_SET		MCEDP_ERROR_BASE+7
#define MCEDP_STATUS_SHELLCODE_FLAG_SET			MCEDP_ERROR_BASE+8
#define MCEDP_STATUS_ROP_FLAG_SET				MCEDP_ERROR_BASE+9
#define MCEDP_STATUS_ROP_FLAG_NOT_SET			MCEDP_ERROR_BASE+10
#define MCEDP_STATUS_INSUFFICIENT_BUFFER		MCEDP_ERROR_BASE+11
#define MCEDP_STATUS_NORESPONSE					MCEDP_ERROR_BASE+12
#define MCEDP_STATUS_RESPONSE					MCEDP_ERROR_BASE+13
#define MCEDP_STATUS_OP_FREE					MCEDP_ERROR_BASE+14
#define MCEDP_STATUS_OP_BUSY					MCEDP_ERROR_BASE+15
#define MCEDP_STATUS_OP_SHELLCODE_DETECTED		MCEDP_ERROR_BASE+16

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)
#endif

#define UID_SIZE        50
#define SEC             1000
#define MAX_ERROR_MSG   256
typedef DWORD STATUS;


typedef struct _ERRORINFO {
	DWORD	dwErrorNum;
	CHAR	ErrorMsg[256];
	CHAR	*CompletErrorMsg;
} ERRORINFO, *PERRORINFO; 

VOID 
DEBUG_PRINTF(
	IN DWORD dwType,
	IN DWORD dwTID,
	IN PCHAR Format, 
	IN ...
	);

VOID 
REPORT_ERROR( 
	IN PCHAR Function,
	OUT PERRORINFO ErrorInfo
	);

VOID 
REPORT_ERROR_EX(
	IN PCHAR Function,
	IN DWORD dwErrorNumber,
	OUT PERRORINFO ErrorInfo
	);

BOOL 
FolderExists(
	LPTSTR szFolderName
	);

STATUS
InitLogPath(
	OUT PCHAR LogPath,
	IN DWORD Size
	);

PCHAR
strtolow(
    PCHAR szString
    );

PCHAR
GenRandomStr(
    PCHAR szString, 
    DWORD dwSize
    );

VOID
HexDumpToFile(
    PBYTE Data, 
    DWORD dwSize, 
    PCHAR szFileName
    );

#ifdef CUCKOO


VOID 
LOCAL_DEBUG_PRINTF(
    IN PCHAR Format, 
    IN ...
    );


STATUS
WriteFileSocket(
    SOCKET Socket,
    PCHAR Buffer
    );

STATUS
InitCuckooLogs();

STATUS
InitShellcodeLog();


STATUS
TransmitFile(
    PCHAR szLocalPath,
    PCHAR szFileName,
    PCHAR szRemotePath
    );

STATUS
TransmitBufAsFile(
    PCHAR szBuf,
    PCHAR szRemoteFileName
    );

STATUS
BufferedSend(
    SOCKET s,
    PCHAR szBuf
    );

#endif