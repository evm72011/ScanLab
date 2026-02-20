#pragma once
//USER_HEADER_START
#ifndef LIN_DEFINE_H
#define LIN_DEFINE_H

#if defined (__amd64__) || defined (__aarch64__) 
	#define _WIN64
	#define _M_X64
#else
	#define 32_BITS_ARCH
#endif

//#define PRINT_ERRORS
//#define THREAD_DEBUG

#include <cstdint>
#include <limits.h>
#include <unistd.h>
#include <cwchar>
#include <cstring>
#include <cerrno>
#include <cstring>
#include <pthread.h>

#if defined(_WIN64) 
typedef int64_t INT_PTR;
#else 
typedef int32_t INT_PTR;
#endif

#ifndef _UNICODE
	#define _UNICODE
#endif

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#define WINAPI
#define APIENTRY
#define CALLBACK
#define __stdcall
#define _inline				inline
#define __forceinline		__attribute__((always_inline))
#define __cdecl

#ifndef TRUE
#define TRUE				true
#endif
#ifndef FALSE
#define FALSE				false
#endif
#define MAX_PATH			0x00000104
#define _MAX_PATH			0x00000104
#define _MAX_FNAME			NAME_MAX
#define _MAX_EXT			256
#define _MAX_DRIVE			3
#define _MAX_DIR			256
#define CP_ACP				0
#define FD_MAX_EVENTS		10
#define NO_ERROR			0
#define INFINITE			-1

#define WAIT_TIMEOUT			ETIMEDOUT
#define WAIT_OBJECT_0			0
#define WAIT_ABANDONED			EOWNERDEAD
#define WAIT_ABANDONED_0		0x00000080L
#define WAIT_FAILED				(DWORD)0xFFFFFFFF
#define ERROR_ALREADY_EXISTS	EEXIST
#define ERROR_FILE_NOT_EXIST	EINVAL
#define MUTEX_ALL_ACCESS		1

#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L

#define UNICODE
#define _FLASH_SIZE_						(0x80*16)

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

#define ERROR_SUCCESS			0
#define ERROR_MORE_DATA			234
#define ERROR_FILE_NOT_FOUND	2

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

/* ----- VS_VERSION.dwFileFlags ----- */
#define VS_FF_DEBUG             0x00000001L
#define VS_FF_PRERELEASE        0x00000002L
#define VS_FF_PATCHED           0x00000004L
#define VS_FF_PRIVATEBUILD      0x00000008L
#define VS_FF_INFOINFERRED      0x00000010L
#define VS_FF_SPECIALBUILD      0x00000020L

/* ----- VS_VERSION.dwFileOS ----- */
#define VOS_UNKNOWN             0x00000000L
#define VOS_DOS                 0x00010000L
#define VOS_OS216               0x00020000L
#define VOS_OS232               0x00030000L
#define VOS_NT                  0x00040000L
#define VOS_WINCE               0x00050000L

#define VOS__BASE               0x00000000L
#define VOS__WINDOWS16          0x00000001L
#define VOS__PM16               0x00000002L
#define VOS__PM32               0x00000003L
#define VOS__WINDOWS32          0x00000004L

#define VOS_DOS_WINDOWS16       0x00010001L
#define VOS_DOS_WINDOWS32       0x00010004L
#define VOS_OS216_PM16          0x00020002L
#define VOS_OS232_PM32          0x00030003L
#define VOS_NT_WINDOWS32        0x00040004L

/* ----- VS_VERSION.dwFileType ----- */
#define VFT_UNKNOWN             0x00000000L
#define VFT_APP                 0x00000001L
#define VFT_DLL                 0x00000002L
#define VFT_DRV                 0x00000003L
#define VFT_FONT                0x00000004L
#define VFT_VXD                 0x00000005L
#define VFT_STATIC_LIB          0x00000007L

/*
* Dialog Box Command IDs
*/
#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7

#define HKEY_CURRENT_USER	NULL

#define DRVOEMPA_ITEM_ENCODER			0
#define DRVOEMPA_ITEM_ENCODER_RESET		1
#define DRVOEMPA_ITEM_ENCODER_COUNT		2
#define DRVOEMPA_ITEM_CONFIGURATION		3
#define DRVOEMPA_ITEM_REQDIGINPUT		4
#define DRVOEMPA_ITEM_TRIGGER			5
#define DRVOEMPA_ITEM_ENABLE_SHOT		6
#define DRVOEMPA_ITEM_LOCK_DISABLE		7
#define DRVOEMPA_ITEM_UNLOCK_ENABLE		8
#define DRVOEMPA_ITEM_FILTER			9
#define DRVOEMPA_ITEM_TIMER_ENABLE		10
#define DRVOEMPA_ITEM_TIMER_DISABLE		11
#define DRVOEMPA_ITEM_READ_CUSTOMREG	13
#define DRVOEMPA_UPDATE_DIGINPUT		15
#define DRVOEMPA_UPDATE_ASCAN_REQUEST	16

/* Windows messaging */
#define HWND_BROADCAST		(void*)0xffff
#define SW_HIDE				0
#define SW_SHOW				5
#define WM_CLOSE			0x0010
#define WM_DESTROY			0x0002   

#define DLL_PROCESS_ATTACH	1
#define DLL_THREAD_ATTACH	2
#define DLL_THREAD_DETACH	3
#define DLL_PROCESS_DETACH	4

/*
* ShowWindow() Commands
*/
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

/* ARP error constants */
#define ERROR_BAD_NET_NAME			1
#define ERROR_BUFFER_OVERFLOW		2
#define ERROR_GEN_FAILURE			3
#define ERROR_INVALID_PARAMETER		4
#define ERROR_INVALID_USER_BUFFER	5
#define ERROR_NOT_FOUND				6
#define ERROR_NOT_SUPPORTED			7


#define SM_CMONITORS		80 // https://msdn.microsoft.com/en-us/library/windows/desktop/ms724385(v=vs.85).aspx

#define ANYSIZE_ARRAY		1	// msdn: The constant ANYSIZE_ARRAY is defined as 1 in the public header Winnt.h. To create this array with more than one element, you must allocate sufficient memory for the structure to take into account additional elements.

/* Built-in atomics */
#define InterlockedCompareExchange(a, b, c)		__sync_val_compare_and_swap(a, c, b)
#define InterlockedIncrement(a)					__atomic_add_fetch(a, 1, __ATOMIC_ACQ_REL)
#define InterlockedIncrement64(a)				__atomic_add_fetch(a, 1, __ATOMIC_ACQ_REL)
#define InterlockedAdd(a, b)					__atomic_add_fetch(a, b, __ATOMIC_ACQ_REL)
#define InterlockedAdd64(a, b)					__atomic_add_fetch(a, b, __ATOMIC_ACQ_REL)
#define InterlockedDecrement(a)					__atomic_sub_fetch(a, 1, __ATOMIC_ACQ_REL)
#define InterlockedDecrement64(a)				__atomic_sub_fetch(a, 1, __ATOMIC_ACQ_REL)
#define InterlockedCompareExchange64(a, b, c)	__sync_val_compare_and_swap(a, c, b)
#define InterlockedExchange(a, b)				__atomic_exchange_n(a, b, __ATOMIC_ACQ_REL)
#define InterlockedExchange64(a, b)				__atomic_exchange_n(a, b, __ATOMIC_ACQ_REL)

#define GetCurrentProcessId()					getpid()

#define _tprintf(...)	wprintf(__VA_ARGS__)
#define __try			try
#define __except(a)		catch(a)
#define EXCEPTION_EXECUTE_HANDLER	...

#define CREATE_SUSPENDED			5	//needs to be defined
#define THREAD_PRIORITY_HIGHEST		6	//idem
#define THREAD_PRIORITY_NORMAL		0
#define SYNCHRONIZE					1

class CUTStringTable;
extern "C" {extern CUTStringTable g_StringTable; }

typedef pthread_mutex_t CRITICAL_SECTION;
typedef int32_t BOOL, *LPBOOL, *PBOOL;
typedef uint32_t COLORREF, DWORD_PTR, UINT_PTR, DWORD, *PDWORD, *LPDWORD, ULONG;
typedef int32_t LONG, *PLONG;
typedef uint64_t LONG_PTR, ULONGLONG, WPARAM, ULONG64, DWORD64;
typedef int64_t __int64, LONGLONG;
typedef uint16_t WORD, ATOM;
typedef char *LPSTR, CHAR;
typedef unsigned char BYTE;
typedef const wchar_t *LPCWSTR;
typedef wchar_t *LPWSTR, _TCHAR, WCHAR;
typedef const char *LPCSTR;
typedef void *HANDLE, *HWND, *LPVOID, *HKEY, *HINSTANCE, *HMODULE, *PVOID, VOID;
typedef LONG_PTR LRESULT, LPARAM;
typedef const void *LPCVOID;
typedef unsigned int SOCKET, UINT;
typedef unsigned char UCHAR, *PUCHAR;
typedef size_t SIZE_T, *PSIZE_T;
typedef DWORD (*LPTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);
typedef void *WSAEVENT; // Opaque pointer to struct defined in LinSock.

#ifdef UNICODE
typedef LPCWSTR LPCTSTR;
#else
typedef LPCSTR LPCTSTR;
#endif

typedef struct ip_option_information {
	UCHAR  Ttl;
	UCHAR  Tos;
	UCHAR  Flags;
	UCHAR  OptionsSize;
	PUCHAR OptionsData;
} IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;

// Microsoft structs
typedef union _LARGE_INTEGER {	//winnt.h (windows.h)
	struct {
		DWORD LowPart;
		LONG  HighPart;
	};
	struct {
		DWORD LowPart;
		LONG  HighPart;
	} u;
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef struct _SYSTEM_TIME {	//winBase.h (Windows.h)
	int wYear;
	int wMonth;
	int wDayOfWeek;
	int wDay;
	int wHour;
	int wMinute;
	int wSecond;
	int wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

// Number of 100 ns interval since jan 1, 1601 
typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME;

typedef struct tagVS_FIXEDFILEINFO {	//verrsrc.h (windows.h)
	DWORD   dwSignature;            /* e.g. 0xfeef04bd */
	DWORD   dwStrucVersion;         /* e.g. 0x00000042 = "0.42" */
	DWORD   dwFileVersionMS;        /* e.g. 0x00030075 = "3.75" */
	DWORD   dwFileVersionLS;        /* e.g. 0x00000031 = "0.31" */
	DWORD   dwProductVersionMS;     /* e.g. 0x00030010 = "3.10" */
	DWORD   dwProductVersionLS;     /* e.g. 0x00000031 = "0.31" */
	DWORD   dwFileFlagsMask;        /* = 0x3F for version "0.42" */
	DWORD   dwFileFlags;            /* e.g. VFF_DEBUG | VFF_PRERELEASE */
	DWORD   dwFileOS;               /* e.g. VOS_DOS_WIN3216 */
	DWORD   dwFileType;             /* e.g. VFT_DRIVER */
	DWORD   dwFileSubtype;          /* e.g. VFT2_DRV_KEYBOARD */
	DWORD   dwFileDateMS;           /* e.g. 0 */
	DWORD   dwFileDateLS;           /* e.g. 0 */
} VS_FIXEDFILEINFO;

typedef struct tagPOINT {
	LONG x;
	LONG y;
} POINT, *PPOINT;

typedef struct _RECT {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT, *PRECT;

typedef struct tagWINDOWPLACEMENT {
	UINT  length;
	UINT  flags;
	UINT  showCmd;
	POINT ptMinPosition;
	POINT ptMaxPosition;
	RECT  rcNormalPosition;
} WINDOWPLACEMENT, *PWINDOWPLACEMENT, *LPWINDOWPLACEMENT;

typedef struct _SYSTEM_INFO {
	DWORD     dwPageSize;
	DWORD     dwNumberOfProcessors;
} SYSTEM_INFO;

typedef struct _PROCESS_MEMORY_COUNTERS {
	DWORD  cb;
	DWORD  PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS, *PPROCESS_MEMORY_COUNTERS;

typedef struct _MEMORYSTATUS {
	DWORD  dwLength;
	DWORD  dwMemoryLoad;
	SIZE_T dwTotalPhys;
	SIZE_T dwAvailPhys;
	SIZE_T dwTotalPageFile;
	SIZE_T dwAvailPageFile;
	SIZE_T dwTotalVirtual;
	SIZE_T dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

typedef struct _DISPLAY_DEVICE {
	DWORD cb;
	WCHAR DeviceName[32];
	WCHAR DeviceString[128];
	DWORD StateFlags;
	WCHAR DeviceID[128];
	WCHAR DeviceKey[128];
} DISPLAY_DEVICE, *PDISPLAY_DEVICE;

typedef struct _LUID {
	DWORD LowPart;
	LONG  HighPart;
} LUID, *PLUID;

typedef struct _LUID_AND_ATTRIBUTES {
	LUID  Luid;
	DWORD Attributes;
} LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;

typedef struct _TOKEN_PRIVILEGES {
	DWORD               PrivilegeCount;
	LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;

/* All this was in defaultstdafx.h */
void* MFC_NewErrorList();
bool MFC_FreeErrorList(void *pErrorList);
bool MFC_AddError(void *pErrorList, wchar_t *pString);
int MFC_GetErrorCount(void *pErrorList);
int MFC_GetErrorStringSize(void *pErrorList, int iIndex);
bool MFC_GetErrorString(void *pErrorList, int iIndex, int iSize, wchar_t *pValue);
bool IsCurrentThreadOneWindow();
extern int g_iLanguage;
//USER_HEADER_STOP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// #pragma data_seg workaround /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define g_iMaxPassCodeCount 16
#define g_bTraceEventCount 64
#define g_bTraceRootTypeCount 64
#define g_iSharedDeviceMax 256
#define g_iIOManagerCountMax 8
#define g_iPrimeNumbersMaximum 10000
#define g_iPrimeNumbersCount 1229
#define g_iDigitalInputMaxCount 24//maximum encoder count.
#define g_iSharedEncoderMaxCount 32//maximum encoder count.
#define g_iSharedEmuMonMax 32
#define g_iSharedDeviceCallMax 256
#define g_iSlaveCountMax 32
#define g_iIOMax (256 * 8)

#ifdef OEMPA11XY
class CHWDevice;
typedef struct structIOManager {
	//Useful to save StremIO coming from the master board.
	//in case of independent device (no master, no slave) then the StreamIO is saved in "_CHWDevice::m_ioManager".
	//in case of master/slave then the StreamIO is saved in shared memory "g_ioManager[g_iIOManagerCountMax]" (maximum of "g_iIOManagerCountMax" masters).
	LONG lIOMutex;//0 (default value), mutex to access the values.
	LONG lIOMutexThreadId;//0
	LONG lIOMutexCount;//0
	LONG lIOCount;//0
	LONG lIOHead;//-1
	LONG lIOTail;//-1
	unsigned long long aullIOSequence[g_iIOMax];
	LONG alIOCycle[g_iIOMax];
	unsigned long long aullIOTimeStamp[g_iIOMax];
	LONG alIOEncoder1[g_iIOMax];
	LONG alIOEncoder2[g_iIOMax];
	LONG alIODigitalInput[g_iIOMax];
	LONG alMaxTemperature[g_iIOMax];//1.1.5.3m
	LONG lMasterCycleCount;//-1
	int g_iErrorIODataLost;

	LONG lDigitalInputOwnerRootId[g_iDigitalInputMaxCount];//root id of the object that have the ownership of the digital input.
	LONG lDigitalInputOwnerIndex[g_iDigitalInputMaxCount];
}structIOManager;
typedef struct structMessageBox
{
	DWORD g_dwSystemMessageBoxDisplay;//Matrix
	DWORD g_dwSystemMessageBoxDisplay2;//LabView
	DWORD g_dwSystemMessageBoxDisplay3;//Tpacquisition
	DWORD g_dwSystemMessageBoxDisplay4;//WT SW
	DWORD g_dwSystemMessageBoxDisplay5;//Matlab
	DWORD g_dwSystemMessageBoxDisplay6;//TFM
	DWORD g_dwSystemMessageBoxDisplay7;//SubSequence
	DWORD g_dwSystemMessageBoxListMutex;
	DWORD g_dwSystemMessageBoxListMutexThreadId;

	LONG g_alSharedKernelMsgBoxType;
	HWND g_alSharedKernelMsgBoxHwnd;
	LONG g_alSharedKernelMsgBoxReturn;
	HWND g_alSharedKernelMsgBoxHwndDebug;

	//#define MAX_PATH          260
	wchar_t g_wcSharedKernelMsgBoxText[4 * MAX_PATH];
	wchar_t g_wcSharedKernelMsgBoxTitle[MAX_PATH];
	wchar_t g_wcSharedKernelMsgBoxCmd[MAX_PATH];

	LONG g_lFWUpdateProgressCount;
	LONG g_lFWUpdateProgressIndex;
	LONG g_lFWUpdateProgressCancel;
	LONG g_lFWUpdateProgressAttention;
}structMessageBox;

/* This struct represents the data organization in shared memory.	*
 * Fields are not initialized as this is never "created" by the OS	*
 * but casted from a pointer to shared memory (returned by mmap).	*
 * Data is initialized at UTCom loading.							*/
typedef struct _win_stub_shared_mem
{
	///////////////////////////////////// win_stub /////////////////////////////////////////
	structMessageBox SharedMessageBox;

	LONG g_alSharedTraceMutex = 0;
	LONG g_alSharedTraceMutexThreadId = 0;

	DWORD g_dwTraceGlobalMutex = 0;
	DWORD g_dwTraceGlobalMutexThreadId = 0;
	bool g_bTraceGlobalEnableDisplay = true;
	bool g_bTraceGlobalEnable = false;
	bool g_bTraceCallbackCall = false;
	bool g_bTraceCallbackDone = false;
	bool g_bTraceCallbackWndMessage = false;
	bool g_bTraceCallbackViaThread = false;
	bool g_bTraceCallbackReplay = false;
	bool g_bTraceCallbackRegister = false;
	bool g_bTraceCallbackUnregister = false;
	bool g_bFileSaveStatusEnable = false;
	bool g_bInspectionCounters = true;
	bool g_bSimulatorRandomFunction = true;
	DWORD g_dwInspectionDataListCountMax = 1024;//go to registry (configuration file) OR automatic evaluation ?
	LONG g_bCallbackTimerUpdate = true;
	ULONGLONG g_ullCallbackTimerUpdate = 0;
	wchar_t g_strTraceGlobalName[MAX_PATH] = L"";
	DWORD g_dwTraceGlobalFileMaxSize = 0x00100000;//1MB

	wchar_t g_wcRootProgramDataFileCfgKernel[MAX_PATH] = L"";
	wchar_t g_wcUTKernelConfigurationFileError[MAX_PATH] = L"";
	wchar_t g_wcRootProgramDataCfgFileInitError[MAX_PATH] = L"";
	wchar_t g_wcRootProgramDataSubFolderCfg[MAX_PATH] = L"";
	wchar_t g_wcRootProgramDataFolder[MAX_PATH] = L"";
	wchar_t g_wcUTKernelFolderDataFilesOEMPA[MAX_PATH] = L"";
	wchar_t g_wcUTKernelFolderDataFilesToolbox[MAX_PATH] = L"";
	wchar_t g_wcApplicationFolderExe[MAX_PATH] = L"";
	wchar_t g_wcApplicationExeFolder[MAX_PATH] = L"";
	wchar_t GetApplicationName[MAX_PATH] = L"";//specific for each application=>not in shared memory
	wchar_t g_wcUTKernelDriverModuleDll[MAX_PATH] = L"";
	DWORD g_dwDataTroughputTimeStep = 100;//ms
	DWORD g_dwDataTroughputTimeRange = 4000;//ms
	DWORD g_dwDataTroughputTimeDisplay = 1000;//ms
	ULONGLONG g_ullTickCountUs = 0;//us
	double g_dTickCount = 0.0;
	double g_dRealTimeResolutionNs = 0.0;

	bool g_bTraceMemoryEnable = false;
	DWORD g_dwTraceMemorySize = 0;
	DWORD g_dwTraceMemoryMutex = 0;
	DWORD g_dwTraceMemoryMutexThreadId = 0;
	DWORD g_dwTraceMemoryStart = 0;
	DWORD g_dwTraceMemoryStop = 0;

	bool g_bTraceEvent[g_bTraceEventCount];
	bool g_bTraceRootType[g_bTraceRootTypeCount];

	LONG g_alSharedDeviceMonitorPort[g_iSharedDeviceMax];
	LONG g_alSharedDevice[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMutex[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMutexThreadId[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMutexCount[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerIndex[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerMutex[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerMutexThreadId[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerMutexCount[g_iSharedDeviceMax];
	LONG g_alSharedIOManager[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerDeviceId[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerMutex[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerMutexCount[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerMutexThreadId[g_iIOManagerCountMax];

	//HWDevice.cpp
	LONG g_bSharedDeviceMultiDeviceLink = true;
	LONG g_lSharedDeviceMultiDeviceMutex = 0;
	LONG g_lSharedDeviceMultiDeviceMutexThreadId = 0;
	LONG g_lSharedDeviceMultiDeviceMutexCount = 0;
	LONG g_lSharedDeviceMultiDeviceCount = -1;
	LONG g_alSharedDeviceMultiDeviceList[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMultiDeviceIOCurrentIndex[g_iSharedDeviceMax];

	//DigitalIO.cpp
	LONG g_lSharedDigitalInputOwnerRootId[g_iDigitalInputMaxCount];//root if of the object that have the ownership of the digital input.
	LONG g_lSharedDigitalInputOwnerIndex[g_iDigitalInputMaxCount];
	LONG g_lDigitalInputMutex = 0;
	LONG g_lDigitalInputMutexThread = 0;

	//SWEncoder.cpp
	LONG g_lSharedEncoderMode[g_iSharedEncoderMaxCount];
	LONG g_lSharedInternalMode[g_iSharedEncoderMaxCount];
	double g_dSharedEncoderSW[g_iSharedEncoderMaxCount];//distance value (unit meter, usi).
	double g_dSharedEncoderHWFactor[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHWResolution[g_iSharedEncoderMaxCount];
	DWORD g_dwSharedEncoderHWResolutionDivider[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHW[g_iSharedEncoderMaxCount];//raw HW value (encoder resolution is not taken into account).
	LONG g_lSharedEncoderHWStart[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHWStop[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHWStep[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderIndex[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderIndexList[g_iSharedEncoderMaxCount];//the last value is the sentinelle.
	LONG g_lSharedEncoderIndexLink[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderRootId[g_iSharedEncoderMaxCount];
	LONG g_iSharedEncoderIndexMutex = 0;
	LONG g_iSharedEncoderIndexMutexThread = 0;

	//_Socket.cpp
	LARGE_INTEGER g_llLocalFrequency;
	LARGE_INTEGER g_llTimeStampStart;

	//////////////////////////////////// UTCOM /////////////////////////////////////////////
	//used by EmuMon
	LONG g_lSharedEmuMonMutex = 0;
	LONG g_lSharedEmuMonMutexThreadId = 0;
	LONG g_lSharedEmuMonCount = 0;
	//each application need to register one ID.
	LONG g_alSharedEmuMonID[g_iSharedEmuMonMax];
	LONG g_alSharedEmuMonProcessID[g_iSharedEmuMonMax];

	//////////////////////////////////// UTKERNEL //////////////////////////////////////////
	bool g_bSharedCommonKeepAlive = true;
	bool g_bSharedCommonUnlockEnableShot = false;
	bool g_bSharedCommonLockDisableShot = false;
	LONG g_alSharedMultiDeviceMutex[g_iSharedDeviceMax];
	LONG g_alSharedMultiDeviceMutexThreadId[g_iSharedDeviceMax];
	LONG g_alSharedMultiDeviceMutexCount[g_iSharedDeviceMax];
	LONG g_lSharedMultiSystemEventCallMutex = 0;
	LONG g_lSharedMultiSystemEventCallMutexThreadId = 0;
	LONG g_lSharedMultiSystemEventCallMutexCount = 0;
	LONG g_lSharedMultiSystemEventCallIndex = 0;
	LONG g_lSharedMultiSystemEventCallThread = 1;
	LONG g_alSharedMultiSystemEventCallIndex[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventState[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventDataInput[g_iSharedDeviceCallMax];
	ULONGLONG g_apSharedMultiSystemEventDataOutput[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventThreadIdSrc[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventThreadIdDst[g_iSharedDeviceCallMax];
	bool g_bSharedMultiSystemEncoderEnable[g_iSharedDeviceMax];
	bool g_bSharedMultiSystemSubSequenceEncoderEnable[g_iSharedDeviceMax];
	bool g_bSharedMultiSystemSubSequenceGateEnable[g_iSharedDeviceMax];
	ULONGLONG g_ullSharedMultiSystemTmpTimeStamp = 0;
	ULONGLONG *g_pullSharedMultiSystemTmpTimeStampResult = NULL;
	int g_iSharedMultiSystemTmpTimeStampDeviceId = -1;
	int *g_piSharedMultiSystemTmpTimeStampCount = NULL;
	int g_iSharedMultiSystemTmpTimeStampIndex = 0;
	ULONGLONG g_ullSharedMultiSystemTmpTimeStampOut[g_iSlaveCountMax];
	LONG g_alSharedMultiSystemTmpTimeStampDeviceId[g_iSlaveCountMax];

	DWORD g_apSharedDeviceProcessId[g_iSharedDeviceMax];
	CHWDevice* g_apSharedDeviceList[g_iSharedDeviceMax];
	DWORD g_apSharedDeviceSlaveCount[g_iSharedDeviceMax];
	DWORD g_apSharedDeviceMasterId[g_iSharedDeviceMax];
	LONG g_apSharedDeviceResolution[g_iSharedDeviceMax];
	DWORD g_apSharedDeviceResolutionDivider[g_iSharedDeviceMax];
	DWORD g_apSharedMatchedDeviceIndex[g_iSharedDeviceMax];

	//////////////////////////////////// UTKERNELOEMPA /////////////////////////////////////
	bool g_bMultiSequence = false;
	structIOManager g_ioManager[g_iIOManagerCountMax];
	bool g_apSharedDeviceResetIOAscan[g_iSharedDeviceMax];
	bool g_apSharedDeviceResetIOCscan[g_iSharedDeviceMax];

	//////////////////////////////////// linux /////////////////////////////////////////////
	int g_bShmemPtrCount;
} win_stub_shared_mem;

#define g_SharedMessageBox shared_struct->SharedMessageBox

#define g_alSharedTraceMutex shared_struct->g_alSharedTraceMutex
#define g_alSharedTraceMutexThreadId shared_struct->g_alSharedTraceMutexThreadId
#define g_dwTraceGlobalMutex shared_struct->g_dwTraceGlobalMutex
#define g_dwTraceGlobalMutexThreadId shared_struct->g_dwTraceGlobalMutexThreadId
#define g_bTraceGlobalEnableDisplay shared_struct->g_bTraceGlobalEnableDisplay
#define g_bTraceGlobalEnable shared_struct->g_bTraceGlobalEnable
#define g_bTraceCallbackCall shared_struct->g_bTraceCallbackCall
#define g_bTraceCallbackDone shared_struct->g_bTraceCallbackDone
#define g_bTraceCallbackWndMessage shared_struct->g_bTraceCallbackWndMessage
#define g_bTraceCallbackViaThread shared_struct->g_bTraceCallbackViaThread
#define g_bTraceCallbackReplay shared_struct->g_bTraceCallbackReplay
#define g_bTraceCallbackRegister shared_struct->g_bTraceCallbackRegister
#define g_bTraceCallbackUnregister shared_struct->g_bTraceCallbackUnregister
#define g_bFileSaveStatusEnable shared_struct->g_bFileSaveStatusEnable
#define g_bInspectionCounters shared_struct->g_bInspectionCounters
#define g_bSimulatorRandomFunction shared_struct->g_bSimulatorRandomFunction
#define g_dwInspectionDataListCountMax shared_struct->g_dwInspectionDataListCountMax
#define g_bCallbackTimerUpdate shared_struct->g_bCallbackTimerUpdate
#define g_ullCallbackTimerUpdate shared_struct->g_ullCallbackTimerUpdate
#define g_strTraceGlobalName shared_struct->g_strTraceGlobalName
#define g_dwTraceGlobalFileMaxSize shared_struct->g_dwTraceGlobalFileMaxSize
#define g_wcRootProgramDataFileCfgKernel shared_struct->g_wcRootProgramDataFileCfgKernel
#define g_wcUTKernelConfigurationFileError shared_struct->g_wcUTKernelConfigurationFileError
#define g_wcRootProgramDataCfgFileInitError shared_struct->g_wcRootProgramDataCfgFileInitError
#define g_wcRootProgramDataSubFolderCfg shared_struct->g_wcRootProgramDataSubFolderCfg
#define g_wcRootProgramDataFolder shared_struct->g_wcRootProgramDataFolder
#define g_wcUTKernelFolderDataFilesOEMPA shared_struct->g_wcUTKernelFolderDataFilesOEMPA
#define g_wcUTKernelFolderDataFilesToolbox shared_struct->g_wcUTKernelFolderDataFilesToolbox
#define g_wcApplicationFolderExe shared_struct->g_wcApplicationFolderExe
#define g_wcApplicationExeFolder shared_struct->g_wcApplicationExeFolder
#define GetApplicationName shared_struct->GetApplicationName
#define g_wcUTKernelDriverModuleDll shared_struct->g_wcUTKernelDriverModuleDll
#define g_dwDataTroughputTimeStep shared_struct->g_dwDataTroughputTimeStep
#define g_dwDataTroughputTimeRange shared_struct->g_dwDataTroughputTimeRange
#define g_dwDataTroughputTimeDisplay shared_struct->g_dwDataTroughputTimeDisplay
#define g_ullTickCountUs shared_struct->g_ullTickCountUs
#define g_dTickCount shared_struct->g_dTickCount
#define g_dRealTimeResolutionNs shared_struct->g_dRealTimeResolutionNs
#define g_bTraceMemoryEnable shared_struct->g_bTraceMemoryEnable
#define g_dwTraceMemorySize shared_struct->g_dwTraceMemorySize
#define g_dwTraceMemoryMutex shared_struct->g_dwTraceMemoryMutex
#define g_dwTraceMemoryMutexThreadId shared_struct->g_dwTraceMemoryMutexThreadId
#define g_dwTraceMemoryStart shared_struct->g_dwTraceMemoryStart
#define g_dwTraceMemoryStop shared_struct->g_dwTraceMemoryStop
#define g_bTraceEvent shared_struct->g_bTraceEvent
#define g_bTraceRootType shared_struct->g_bTraceRootType

#define g_alSharedDeviceMonitorPort shared_struct->g_alSharedDeviceMonitorPort
#define g_alSharedDevice shared_struct->g_alSharedDevice
#define g_alSharedDeviceMutex shared_struct->g_alSharedDeviceMutex
#define g_alSharedDeviceMutexThreadId shared_struct->g_alSharedDeviceMutexThreadId
#define g_alSharedDeviceMutexCount shared_struct->g_alSharedDeviceMutexCount
#define g_alSharedDeviceIOManagerIndex shared_struct->g_alSharedDeviceIOManagerIndex

#define g_alSharedIOManager shared_struct->g_alSharedIOManager
#define g_alSharedIOManagerMutex shared_struct->g_alSharedIOManagerMutex
#define g_alSharedIOManagerMutexCount shared_struct->g_alSharedIOManagerMutexCount
#define g_alSharedIOManagerMutexThreadId shared_struct->g_alSharedIOManagerMutexThreadId
#define g_alSharedIOManagerDeviceId shared_struct->g_alSharedIOManagerDeviceId

#define g_bSharedDeviceMultiDeviceLink shared_struct->g_bSharedDeviceMultiDeviceLink
#define g_lSharedDeviceMultiDeviceMutex shared_struct->g_lSharedDeviceMultiDeviceMutex
#define g_lSharedDeviceMultiDeviceMutexThreadId shared_struct->g_lSharedDeviceMultiDeviceMutexThreadId
#define g_lSharedDeviceMultiDeviceMutexCount shared_struct->g_lSharedDeviceMultiDeviceMutexCount
#define g_lSharedDeviceMultiDeviceCount shared_struct->g_lSharedDeviceMultiDeviceCount
#define g_alSharedDeviceMultiDeviceList shared_struct->g_alSharedDeviceMultiDeviceList
#define g_alSharedDeviceMultiDeviceIOCurrentIndex shared_struct->g_alSharedDeviceMultiDeviceIOCurrentIndex

#define g_lSharedDigitalInputOwnerRootId shared_struct->g_lSharedDigitalInputOwnerRootId
#define g_lSharedDigitalInputOwnerIndex shared_struct->g_lSharedDigitalInputOwnerIndex
#define g_lDigitalInputMutex shared_struct->g_lDigitalInputMutex
#define g_lDigitalInputMutexThread shared_struct->g_lDigitalInputMutexThread

#define g_lSharedEncoderMode shared_struct->g_lSharedEncoderMode
#define g_lSharedInternalMode shared_struct->g_lSharedInternalMode
#define g_dSharedEncoderSW shared_struct->g_dSharedEncoderSW
#define g_dSharedEncoderHWFactor shared_struct->g_dSharedEncoderHWFactor
#define g_lSharedEncoderHWResolution shared_struct->g_lSharedEncoderHWResolution
#define g_dwSharedEncoderHWResolutionDivider shared_struct->g_dwSharedEncoderHWResolutionDivider
#define g_lSharedEncoderHW shared_struct->g_lSharedEncoderHW
#define g_lSharedEncoderHWStart shared_struct->g_lSharedEncoderHWStart
#define g_lSharedEncoderHWStop shared_struct->g_lSharedEncoderHWStop
#define g_lSharedEncoderHWStep shared_struct->g_lSharedEncoderHWStep
#define g_lSharedEncoderIndex shared_struct->g_lSharedEncoderIndex
#define g_lSharedEncoderIndexList shared_struct->g_lSharedEncoderIndexList
#define g_lSharedEncoderIndexLink shared_struct->g_lSharedEncoderIndexLink
#define g_lSharedEncoderRootId shared_struct->g_lSharedEncoderRootId
#define g_iSharedEncoderIndexMutex shared_struct->g_iSharedEncoderIndexMutex
#define g_iSharedEncoderIndexMutexThread shared_struct->g_iSharedEncoderIndexMutexThread

#define g_llLocalFrequency shared_struct->g_llLocalFrequency
#define g_llTimeStampStart shared_struct->g_llTimeStampStart

#define g_lSharedEmuMonMutex shared_struct->g_lSharedEmuMonMutex
#define g_lSharedEmuMonMutexThreadId shared_struct->g_lSharedEmuMonMutexThreadId
#define g_lSharedEmuMonCount shared_struct->g_lSharedEmuMonCount
#define g_alSharedEmuMonID shared_struct->g_alSharedEmuMonID
#define g_alSharedEmuMonProcessID shared_struct->g_alSharedEmuMonProcessID

#define g_bSharedCommonKeepAlive shared_struct->g_bSharedCommonKeepAlive
#define g_bSharedCommonUnlockEnableShot shared_struct->g_bSharedCommonUnlockEnableShot
#define g_bSharedCommonLockDisableShot shared_struct->g_bSharedCommonLockDisableShot
#define g_alSharedMultiDeviceMutex shared_struct->g_alSharedMultiDeviceMutex
#define g_alSharedMultiDeviceMutexThreadId shared_struct->g_alSharedMultiDeviceMutexThreadId
#define g_alSharedMultiDeviceMutexCount shared_struct->g_alSharedMultiDeviceMutexCount
#define g_lSharedMultiSystemEventCallMutex shared_struct->g_lSharedMultiSystemEventCallMutex
#define g_lSharedMultiSystemEventCallMutexThreadId shared_struct->g_lSharedMultiSystemEventCallMutexThreadId
#define g_lSharedMultiSystemEventCallMutexCount shared_struct->g_lSharedMultiSystemEventCallMutexCount
#define g_lSharedMultiSystemEventCallIndex shared_struct->g_lSharedMultiSystemEventCallIndex
#define g_lSharedMultiSystemEventCallThread shared_struct->g_lSharedMultiSystemEventCallThread
#define g_alSharedMultiSystemEventCallIndex shared_struct->g_alSharedMultiSystemEventCallIndex
#define g_apSharedMultiSystemEventState shared_struct->g_apSharedMultiSystemEventState
#define g_apSharedMultiSystemEventDataInput shared_struct->g_apSharedMultiSystemEventDataInput
#define g_apSharedMultiSystemEventDataOutput shared_struct->g_apSharedMultiSystemEventDataOutput
#define g_apSharedMultiSystemEventThreadIdSrc shared_struct->g_apSharedMultiSystemEventThreadIdSrc
#define g_apSharedMultiSystemEventThreadIdDst shared_struct->g_apSharedMultiSystemEventThreadIdDst
#define g_bSharedMultiSystemEncoderEnable shared_struct->g_bSharedMultiSystemEncoderEnable
#define g_bSharedMultiSystemSubSequenceEncoderEnable shared_struct->g_bSharedMultiSystemSubSequenceEncoderEnable
#define g_bSharedMultiSystemSubSequenceGateEnable shared_struct->g_bSharedMultiSystemSubSequenceGateEnable
#define g_ullSharedMultiSystemTmpTimeStamp shared_struct->g_ullSharedMultiSystemTmpTimeStamp
#define g_pullSharedMultiSystemTmpTimeStampResult shared_struct->g_pullSharedMultiSystemTmpTimeStampResult
#define g_iSharedMultiSystemTmpTimeStampDeviceId shared_struct->g_iSharedMultiSystemTmpTimeStampDeviceId
#define g_piSharedMultiSystemTmpTimeStampCount shared_struct->g_piSharedMultiSystemTmpTimeStampCount
#define g_iSharedMultiSystemTmpTimeStampIndex shared_struct->g_iSharedMultiSystemTmpTimeStampIndex
#define g_ullSharedMultiSystemTmpTimeStampOut shared_struct->g_ullSharedMultiSystemTmpTimeStampOut
#define g_alSharedMultiSystemTmpTimeStampDeviceId shared_struct->g_alSharedMultiSystemTmpTimeStampDeviceId

#define g_apSharedDeviceProcessId shared_struct->g_apSharedDeviceProcessId
#define g_apSharedDeviceList shared_struct->g_apSharedDeviceList
#define g_apSharedDeviceSlaveCount shared_struct->g_apSharedDeviceSlaveCount
#define g_apSharedDeviceMasterId shared_struct->g_apSharedDeviceMasterId
#define g_apSharedDeviceResolution shared_struct->g_apSharedDeviceResolution
#define g_apSharedDeviceResolutionDivider shared_struct->g_apSharedDeviceResolutionDivider
#define g_apSharedMatchedDeviceIndex shared_struct->g_apSharedMatchedDeviceIndex

#define g_bMultiSequence shared_struct->g_bMultiSequence
#define g_ioManager shared_struct->g_ioManager

#define g_apSharedDeviceResetIOAscan shared_struct->g_apSharedDeviceResetIOAscan
#define g_apSharedDeviceResetIOCscan shared_struct->g_apSharedDeviceResetIOCscan
#else
class CHWDevice;
typedef struct structIOManager {
	//Useful to save StremIO coming from the master board.
	//in case of independent device (no master, no slave) then the StreamIO is saved in "_CHWDevice::m_ioManager".
	//in case of master/slave then the StreamIO is saved in shared memory "g_ioManager[g_iIOManagerCountMax]" (maximum of "g_iIOManagerCountMax" masters).
	LONG lIOMutex;//0 (default value), mutex to access the values.
	LONG lIOMutexThreadId;//0
	LONG lIOMutexCount;//0
	LONG lIOCount;//0
	LONG lIOHead;//-1
	LONG lIOTail;//-1
	ULONGLONG aullIOSequence[g_iIOMax];
	LONG alIOCycle[g_iIOMax];
	ULONGLONG aullIOTimeStamp[g_iIOMax];
	LONG alIOEncoder1[g_iIOMax];
	LONG alIOEncoder2[g_iIOMax];
	LONG alIODigitalInput[g_iIOMax];
	LONG alMaxTemperature[g_iIOMax];//1.1.5.3m
	LONG lMasterCycleCount;//-1
	int g_iErrorIODataLost;

	LONG lDigitalInputOwnerRootId[g_iDigitalInputMaxCount];//root id of the object that have the ownership of the digital input.
	LONG lDigitalInputOwnerIndex[g_iDigitalInputMaxCount];
}structIOManager;
typedef struct structMessageBoxDisplay
{
	DWORD g_dwSystemMessageBoxDisplay;//Matrix
	DWORD g_dwSystemMessageBoxDisplay2;//LabView
	DWORD g_dwSystemMessageBoxDisplay3;//Tpacquisition
	DWORD g_dwSystemMessageBoxDisplay4;//WT SW
	DWORD g_dwSystemMessageBoxDisplay5;//Matlab
	DWORD g_dwSystemMessageBoxDisplay6;//TFM
	DWORD g_dwSystemMessageBoxDisplay7;//SubSequence
}structMessageBoxDisplay;
typedef struct structMessageBox
{
	DWORD g_dwSystemMessageBoxListMutex;
	DWORD g_dwSystemMessageBoxListMutexThreadId;
	LONG g_alSharedKernelMsgBoxType;
	HWND g_alSharedKernelMsgBoxHwnd;
	LONG g_alSharedKernelMsgBoxReturn;
	HWND g_alSharedKernelMsgBoxHwndDebug;
	//#define MAX_PATH          260
	wchar_t g_wcSharedKernelMsgBoxText[4 * MAX_PATH];
	wchar_t g_wcSharedKernelMsgBoxTitle[MAX_PATH];
	wchar_t g_wcSharedKernelMsgBoxCmd[MAX_PATH];

	LONG g_lFWUpdateProgressCount;
	LONG g_lFWUpdateProgressIndex;
	LONG g_lFWUpdateProgressCancel;
	LONG g_lFWUpdateProgressAttention;
}structMessageBox;

/* This struct represents the data organization in shared memory.	*
 * Fields are not initialized as this is never "created" by the OS	*
 * but casted from a pointer to shared memory (returned by mmap).	*
 * Data is initialized at UTCom loading.							*/
typedef struct _win_stub_shared_mem
{
	///////////////////////////////////// win_stub /////////////////////////////////////////
	structMessageBox g_SharedMessageBox;
	structMessageBoxDisplay g_SharedMessageBoxDisplay;

	LONG g_alSharedTraceMutex = 0;
	LONG g_alSharedTraceMutexThreadId = 0;

	DWORD g_dwTraceGlobalMutex = 0;
	DWORD g_dwTraceGlobalMutexThreadId = 0;
	bool g_bTraceGlobalEnableDisplay = true;
	bool g_bTraceGlobalEnable = false;
	bool g_bTraceCallbackCall = false;
	bool g_bTraceCallbackDone = false;
	bool g_bTraceCallbackWndMessage = false;
	bool g_bTraceCallbackViaThread = false;
	bool g_bTraceCallbackReplay = false;
	bool g_bTraceCallbackRegister = false;
	bool g_bTraceCallbackUnregister = false;
	bool g_bFileSaveStatusEnable = false;
	bool g_bInspectionCounters = true;
	bool g_bSimulatorRandomFunction = true;
	DWORD g_dwInspectionDataListCountMax = 1024;//go to registry (configuration file) OR automatic evaluation ?
	LONG g_bCallbackTimerUpdate = true;
	ULONGLONG g_ullCallbackTimerUpdate = 0;
	wchar_t g_strTraceGlobalName[MAX_PATH] = L"";
	DWORD g_dwTraceGlobalFileMaxSize = 0x00100000;//1MB

	wchar_t g_wcRootProgramDataFileCfgKernel[MAX_PATH] = L"";
	wchar_t g_wcUTKernelConfigurationFileError[MAX_PATH] = L"";
	wchar_t g_wcRootProgramDataCfgFileInitError[MAX_PATH] = L"";
	wchar_t g_wcRootProgramDataSubFolderCfg[MAX_PATH] = L"";
	wchar_t g_wcRootProgramDataFolder[MAX_PATH] = L"";
	wchar_t g_wcUTKernelFolderDataFilesOEMPA[MAX_PATH] = L"";
	wchar_t g_wcUTKernelFolderDataFilesToolbox[MAX_PATH] = L"";
	wchar_t g_wcApplicationFolderExe[MAX_PATH] = L"";
	wchar_t g_wcApplicationExeFolder[MAX_PATH] = L"";
	wchar_t GetApplicationName[MAX_PATH] = L"";//specific for each application=>not in shared memory
	wchar_t g_wcUTKernelDriverModuleDll[MAX_PATH] = L"";
	DWORD g_dwDataTroughputTimeStep = 100;//ms
	DWORD g_dwDataTroughputTimeRange = 4000;//ms
	DWORD g_dwDataTroughputTimeDisplay = 1000;//ms
	ULONGLONG g_ullTickCountUs = 0;//us
	double g_dTickCount = 0.0;
	double g_dRealTimeResolutionNs = 0.0;

	bool g_bTraceMemoryEnable = false;
	DWORD g_dwTraceMemorySize = 0;
	DWORD g_dwTraceMemoryMutex = 0;
	DWORD g_dwTraceMemoryMutexThreadId = 0;
	DWORD g_dwTraceMemoryStart = 0;
	DWORD g_dwTraceMemoryStop = 0;

	bool g_bTraceEvent[g_bTraceEventCount];
	bool g_bTraceRootType[g_bTraceRootTypeCount];

	LONG g_alSharedDeviceMonitorPort[g_iSharedDeviceMax];
	LONG g_alSharedDevice[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMutex[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMutexThreadId[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMutexCount[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerIndex[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerMutex[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerMutexThreadId[g_iSharedDeviceMax];
	LONG g_alSharedDeviceIOManagerMutexCount[g_iSharedDeviceMax];
	LONG g_alSharedIOManager[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerDeviceId[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerMutex[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerMutexCount[g_iIOManagerCountMax];
	LONG g_alSharedIOManagerMutexThreadId[g_iIOManagerCountMax];

	//HWDevice.cpp
	LONG g_bSharedDeviceMultiDeviceLink = true;
	LONG g_lSharedDeviceMultiDeviceMutex = 0;
	LONG g_lSharedDeviceMultiDeviceMutexThreadId = 0;
	LONG g_lSharedDeviceMultiDeviceMutexCount = 0;
	LONG g_lSharedDeviceMultiDeviceCount = -1;
	LONG g_alSharedDeviceMultiDeviceList[g_iSharedDeviceMax];
	LONG g_alSharedDeviceMultiDeviceIOCurrentIndex[g_iSharedDeviceMax];

	//DigitalIO.cpp
	LONG g_lSharedDigitalInputOwnerRootId[g_iDigitalInputMaxCount];//root if of the object that have the ownership of the digital input.
	LONG g_lSharedDigitalInputOwnerIndex[g_iDigitalInputMaxCount];
	LONG g_lDigitalInputMutex = 0;
	LONG g_lDigitalInputMutexThread = 0;

	//SWEncoder.cpp
	LONG g_lSharedEncoderMode[g_iSharedEncoderMaxCount];
	LONG g_lSharedInternalMode[g_iSharedEncoderMaxCount];
	double g_dSharedEncoderSW[g_iSharedEncoderMaxCount];//distance value (unit meter, usi).
	double g_dSharedEncoderHWFactor[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHWResolution[g_iSharedEncoderMaxCount];
	DWORD g_dwSharedEncoderHWResolutionDivider[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHW[g_iSharedEncoderMaxCount];//raw HW value (encoder resolution is not taken into account).
	LONG g_lSharedEncoderHWStart[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHWStop[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderHWStep[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderIndex[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderIndexList[g_iSharedEncoderMaxCount];//the last value is the sentinelle.
	LONG g_lSharedEncoderIndexLink[g_iSharedEncoderMaxCount];
	LONG g_lSharedEncoderRootId[g_iSharedEncoderMaxCount];
	LONG g_iSharedEncoderIndexMutex = 0;
	LONG g_iSharedEncoderIndexMutexThread = 0;

	//_Socket.cpp
	LARGE_INTEGER g_llLocalFrequency;
	LARGE_INTEGER g_llTimeStampStart;

	//////////////////////////////////// UTCOM /////////////////////////////////////////////
	//used by EmuMon
	LONG g_lSharedEmuMonMutex = 0;
	LONG g_lSharedEmuMonMutexThreadId = 0;
	LONG g_lSharedEmuMonCount = 0;
	//each application need to register one ID.
	LONG g_alSharedEmuMonID[g_iSharedEmuMonMax];
	LONG g_alSharedEmuMonProcessID[g_iSharedEmuMonMax];

	//////////////////////////////////// UTKERNEL //////////////////////////////////////////
	bool g_bSharedCommonKeepAlive = true;
	bool g_bSharedCommonUnlockEnableShot = false;
	bool g_bSharedCommonLockDisableShot = false;
	LONG g_alSharedMultiDeviceMutex[g_iSharedDeviceMax];
	LONG g_alSharedMultiDeviceMutexThreadId[g_iSharedDeviceMax];
	LONG g_alSharedMultiDeviceMutexCount[g_iSharedDeviceMax];
	LONG g_lSharedMultiSystemEventCallMutex = 0;
	LONG g_lSharedMultiSystemEventCallMutexThreadId = 0;
	LONG g_lSharedMultiSystemEventCallMutexCount = 0;
	LONG g_lSharedMultiSystemEventCallIndex = 0;
	LONG g_lSharedMultiSystemEventCallThread = 1;
	LONG g_alSharedMultiSystemEventCallIndex[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventState[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventDataInput[g_iSharedDeviceCallMax];
	ULONGLONG g_apSharedMultiSystemEventDataOutput[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventThreadIdSrc[g_iSharedDeviceCallMax];
	DWORD g_apSharedMultiSystemEventThreadIdDst[g_iSharedDeviceCallMax];
	bool g_bSharedMultiSystemEncoderEnable[g_iSharedDeviceMax];
	bool g_bSharedMultiSystemSubSequenceEncoderEnable[g_iSharedDeviceMax];
	bool g_bSharedMultiSystemSubSequenceGateEnable[g_iSharedDeviceMax];
	ULONGLONG g_ullSharedMultiSystemTmpTimeStamp = 0;
	ULONGLONG *g_pullSharedMultiSystemTmpTimeStampResult = NULL;
	int g_iSharedMultiSystemTmpTimeStampDeviceId = -1;
	int *g_piSharedMultiSystemTmpTimeStampCount = NULL;
	int g_iSharedMultiSystemTmpTimeStampIndex = 0;
	ULONGLONG g_ullSharedMultiSystemTmpTimeStampOut[g_iSlaveCountMax];
	LONG g_alSharedMultiSystemTmpTimeStampDeviceId[g_iSlaveCountMax];

	DWORD g_apSharedDeviceProcessId[g_iSharedDeviceMax];
	CHWDevice* g_apSharedDeviceList[g_iSharedDeviceMax];
	DWORD g_apSharedDeviceSlaveCount[g_iSharedDeviceMax];
	DWORD g_apSharedDeviceMasterId[g_iSharedDeviceMax];
	LONG g_apSharedDeviceResolution[g_iSharedDeviceMax];
	DWORD g_apSharedDeviceResolutionDivider[g_iSharedDeviceMax];
	DWORD g_apSharedMatchedDeviceIndex[g_iSharedDeviceMax];

	bool g_bMultiSequence = false;
	structIOManager g_ioManager[g_iIOManagerCountMax];
	bool g_apSharedDeviceResetIOAscan[g_iSharedDeviceMax];
	bool g_apSharedDeviceResetIOCscan[g_iSharedDeviceMax];

	bool g_bPostFeedback = false;
	HWND g_hPostFeedbackWnd = 0;
	UINT g_uiPostFeedbackMsg = 0;
	WPARAM g_wPostFeedbackParam = 0;
	LPARAM g_lPostFeedbackParam = 0;

	//////////////////////////////////// linux /////////////////////////////////////////////
	int g_bShmemPtrCount;
} win_stub_shared_mem;

#define g_SharedMessageBox shared_struct->g_SharedMessageBox
#define g_SharedMessageBoxDisplay shared_struct->g_SharedMessageBoxDisplay

#define g_alSharedTraceMutex shared_struct->g_alSharedTraceMutex
#define g_alSharedTraceMutexThreadId shared_struct->g_alSharedTraceMutexThreadId
#define g_dwTraceGlobalMutex shared_struct->g_dwTraceGlobalMutex
#define g_dwTraceGlobalMutexThreadId shared_struct->g_dwTraceGlobalMutexThreadId
#define g_bTraceGlobalEnableDisplay shared_struct->g_bTraceGlobalEnableDisplay
#define g_bTraceGlobalEnable shared_struct->g_bTraceGlobalEnable
#define g_bTraceCallbackCall shared_struct->g_bTraceCallbackCall
#define g_bTraceCallbackDone shared_struct->g_bTraceCallbackDone
#define g_bTraceCallbackWndMessage shared_struct->g_bTraceCallbackWndMessage
#define g_bTraceCallbackViaThread shared_struct->g_bTraceCallbackViaThread
#define g_bTraceCallbackReplay shared_struct->g_bTraceCallbackReplay
#define g_bTraceCallbackRegister shared_struct->g_bTraceCallbackRegister
#define g_bTraceCallbackUnregister shared_struct->g_bTraceCallbackUnregister
#define g_bFileSaveStatusEnable shared_struct->g_bFileSaveStatusEnable
#define g_bInspectionCounters shared_struct->g_bInspectionCounters
#define g_bSimulatorRandomFunction shared_struct->g_bSimulatorRandomFunction
#define g_dwInspectionDataListCountMax shared_struct->g_dwInspectionDataListCountMax
#define g_bCallbackTimerUpdate shared_struct->g_bCallbackTimerUpdate
#define g_ullCallbackTimerUpdate shared_struct->g_ullCallbackTimerUpdate
#define g_strTraceGlobalName shared_struct->g_strTraceGlobalName
#define g_dwTraceGlobalFileMaxSize shared_struct->g_dwTraceGlobalFileMaxSize
#define g_wcRootProgramDataFileCfgKernel shared_struct->g_wcRootProgramDataFileCfgKernel
#define g_wcUTKernelConfigurationFileError shared_struct->g_wcUTKernelConfigurationFileError
#define g_wcRootProgramDataCfgFileInitError shared_struct->g_wcRootProgramDataCfgFileInitError
#define g_wcRootProgramDataSubFolderCfg shared_struct->g_wcRootProgramDataSubFolderCfg
#define g_wcRootProgramDataFolder shared_struct->g_wcRootProgramDataFolder
#define g_wcUTKernelFolderDataFilesOEMPA shared_struct->g_wcUTKernelFolderDataFilesOEMPA
#define g_wcUTKernelFolderDataFilesToolbox shared_struct->g_wcUTKernelFolderDataFilesToolbox
#define g_wcApplicationFolderExe shared_struct->g_wcApplicationFolderExe
#define g_wcApplicationExeFolder shared_struct->g_wcApplicationExeFolder
#define GetApplicationName shared_struct->GetApplicationName
#define g_wcUTKernelDriverModuleDll shared_struct->g_wcUTKernelDriverModuleDll
#define g_dwDataTroughputTimeStep shared_struct->g_dwDataTroughputTimeStep
#define g_dwDataTroughputTimeRange shared_struct->g_dwDataTroughputTimeRange
#define g_dwDataTroughputTimeDisplay shared_struct->g_dwDataTroughputTimeDisplay
#define g_ullTickCountUs shared_struct->g_ullTickCountUs
#define g_dTickCount shared_struct->g_dTickCount
#define g_dRealTimeResolutionNs shared_struct->g_dRealTimeResolutionNs
#define g_bTraceMemoryEnable shared_struct->g_bTraceMemoryEnable
#define g_dwTraceMemorySize shared_struct->g_dwTraceMemorySize
#define g_dwTraceMemoryMutex shared_struct->g_dwTraceMemoryMutex
#define g_dwTraceMemoryMutexThreadId shared_struct->g_dwTraceMemoryMutexThreadId
#define g_dwTraceMemoryStart shared_struct->g_dwTraceMemoryStart
#define g_dwTraceMemoryStop shared_struct->g_dwTraceMemoryStop
#define g_bTraceEvent shared_struct->g_bTraceEvent
#define g_bTraceRootType shared_struct->g_bTraceRootType

#define g_alSharedDeviceMonitorPort shared_struct->g_alSharedDeviceMonitorPort
#define g_alSharedDevice shared_struct->g_alSharedDevice
#define g_alSharedDeviceMutex shared_struct->g_alSharedDeviceMutex
#define g_alSharedDeviceMutexThreadId shared_struct->g_alSharedDeviceMutexThreadId
#define g_alSharedDeviceMutexCount shared_struct->g_alSharedDeviceMutexCount
#define g_alSharedDeviceIOManagerIndex shared_struct->g_alSharedDeviceIOManagerIndex

#define g_alSharedIOManager shared_struct->g_alSharedIOManager
#define g_alSharedIOManagerMutex shared_struct->g_alSharedIOManagerMutex
#define g_alSharedIOManagerMutexCount shared_struct->g_alSharedIOManagerMutexCount
#define g_alSharedIOManagerMutexThreadId shared_struct->g_alSharedIOManagerMutexThreadId
#define g_alSharedIOManagerDeviceId shared_struct->g_alSharedIOManagerDeviceId

#define g_bSharedDeviceMultiDeviceLink shared_struct->g_bSharedDeviceMultiDeviceLink
#define g_lSharedDeviceMultiDeviceMutex shared_struct->g_lSharedDeviceMultiDeviceMutex
#define g_lSharedDeviceMultiDeviceMutexThreadId shared_struct->g_lSharedDeviceMultiDeviceMutexThreadId
#define g_lSharedDeviceMultiDeviceMutexCount shared_struct->g_lSharedDeviceMultiDeviceMutexCount
#define g_lSharedDeviceMultiDeviceCount shared_struct->g_lSharedDeviceMultiDeviceCount
#define g_alSharedDeviceMultiDeviceList shared_struct->g_alSharedDeviceMultiDeviceList
#define g_alSharedDeviceMultiDeviceIOCurrentIndex shared_struct->g_alSharedDeviceMultiDeviceIOCurrentIndex

#define g_lSharedDigitalInputOwnerRootId shared_struct->g_lSharedDigitalInputOwnerRootId
#define g_lSharedDigitalInputOwnerIndex shared_struct->g_lSharedDigitalInputOwnerIndex
#define g_lDigitalInputMutex shared_struct->g_lDigitalInputMutex
#define g_lDigitalInputMutexThread shared_struct->g_lDigitalInputMutexThread

#define g_lSharedEncoderMode shared_struct->g_lSharedEncoderMode
#define g_lSharedInternalMode shared_struct->g_lSharedInternalMode
#define g_dSharedEncoderSW shared_struct->g_dSharedEncoderSW
#define g_dSharedEncoderHWFactor shared_struct->g_dSharedEncoderHWFactor
#define g_lSharedEncoderHWResolution shared_struct->g_lSharedEncoderHWResolution
#define g_dwSharedEncoderHWResolutionDivider shared_struct->g_dwSharedEncoderHWResolutionDivider
#define g_lSharedEncoderHW shared_struct->g_lSharedEncoderHW
#define g_lSharedEncoderHWStart shared_struct->g_lSharedEncoderHWStart
#define g_lSharedEncoderHWStop shared_struct->g_lSharedEncoderHWStop
#define g_lSharedEncoderHWStep shared_struct->g_lSharedEncoderHWStep
#define g_lSharedEncoderIndex shared_struct->g_lSharedEncoderIndex
#define g_lSharedEncoderIndexList shared_struct->g_lSharedEncoderIndexList
#define g_lSharedEncoderIndexLink shared_struct->g_lSharedEncoderIndexLink
#define g_lSharedEncoderRootId shared_struct->g_lSharedEncoderRootId
#define g_iSharedEncoderIndexMutex shared_struct->g_iSharedEncoderIndexMutex
#define g_iSharedEncoderIndexMutexThread shared_struct->g_iSharedEncoderIndexMutexThread

#define g_llLocalFrequency shared_struct->g_llLocalFrequency
#define g_llTimeStampStart shared_struct->g_llTimeStampStart

#define g_lSharedEmuMonMutex shared_struct->g_lSharedEmuMonMutex
#define g_lSharedEmuMonMutexThreadId shared_struct->g_lSharedEmuMonMutexThreadId
#define g_lSharedEmuMonCount shared_struct->g_lSharedEmuMonCount
#define g_alSharedEmuMonID shared_struct->g_alSharedEmuMonID
#define g_alSharedEmuMonProcessID shared_struct->g_alSharedEmuMonProcessID

#define g_bSharedCommonKeepAlive shared_struct->g_bSharedCommonKeepAlive
#define g_bSharedCommonUnlockEnableShot shared_struct->g_bSharedCommonUnlockEnableShot
#define g_bSharedCommonLockDisableShot shared_struct->g_bSharedCommonLockDisableShot
#define g_alSharedMultiDeviceMutex shared_struct->g_alSharedMultiDeviceMutex
#define g_alSharedMultiDeviceMutexThreadId shared_struct->g_alSharedMultiDeviceMutexThreadId
#define g_alSharedMultiDeviceMutexCount shared_struct->g_alSharedMultiDeviceMutexCount
#define g_lSharedMultiSystemEventCallMutex shared_struct->g_lSharedMultiSystemEventCallMutex
#define g_lSharedMultiSystemEventCallMutexThreadId shared_struct->g_lSharedMultiSystemEventCallMutexThreadId
#define g_lSharedMultiSystemEventCallMutexCount shared_struct->g_lSharedMultiSystemEventCallMutexCount
#define g_lSharedMultiSystemEventCallIndex shared_struct->g_lSharedMultiSystemEventCallIndex
#define g_lSharedMultiSystemEventCallThread shared_struct->g_lSharedMultiSystemEventCallThread
#define g_alSharedMultiSystemEventCallIndex shared_struct->g_alSharedMultiSystemEventCallIndex
#define g_apSharedMultiSystemEventState shared_struct->g_apSharedMultiSystemEventState
#define g_apSharedMultiSystemEventDataInput shared_struct->g_apSharedMultiSystemEventDataInput
#define g_apSharedMultiSystemEventDataOutput shared_struct->g_apSharedMultiSystemEventDataOutput
#define g_apSharedMultiSystemEventThreadIdSrc shared_struct->g_apSharedMultiSystemEventThreadIdSrc
#define g_apSharedMultiSystemEventThreadIdDst shared_struct->g_apSharedMultiSystemEventThreadIdDst
#define g_bSharedMultiSystemEncoderEnable shared_struct->g_bSharedMultiSystemEncoderEnable
#define g_bSharedMultiSystemSubSequenceEncoderEnable shared_struct->g_bSharedMultiSystemSubSequenceEncoderEnable
#define g_bSharedMultiSystemSubSequenceGateEnable shared_struct->g_bSharedMultiSystemSubSequenceGateEnable
#define g_ullSharedMultiSystemTmpTimeStamp shared_struct->g_ullSharedMultiSystemTmpTimeStamp
#define g_pullSharedMultiSystemTmpTimeStampResult shared_struct->g_pullSharedMultiSystemTmpTimeStampResult
#define g_iSharedMultiSystemTmpTimeStampDeviceId shared_struct->g_iSharedMultiSystemTmpTimeStampDeviceId
#define g_piSharedMultiSystemTmpTimeStampCount shared_struct->g_piSharedMultiSystemTmpTimeStampCount
#define g_iSharedMultiSystemTmpTimeStampIndex shared_struct->g_iSharedMultiSystemTmpTimeStampIndex
#define g_ullSharedMultiSystemTmpTimeStampOut shared_struct->g_ullSharedMultiSystemTmpTimeStampOut
#define g_alSharedMultiSystemTmpTimeStampDeviceId shared_struct->g_alSharedMultiSystemTmpTimeStampDeviceId

#define g_apSharedDeviceProcessId shared_struct->g_apSharedDeviceProcessId
#define g_apSharedDeviceList shared_struct->g_apSharedDeviceList
#define g_apSharedDeviceSlaveCount shared_struct->g_apSharedDeviceSlaveCount
#define g_apSharedDeviceMasterId shared_struct->g_apSharedDeviceMasterId
#define g_apSharedDeviceResolution shared_struct->g_apSharedDeviceResolution
#define g_apSharedDeviceResolutionDivider shared_struct->g_apSharedDeviceResolutionDivider
#define g_apSharedMatchedDeviceIndex shared_struct->g_apSharedMatchedDeviceIndex

#define g_bMultiSequence shared_struct->g_bMultiSequence
#define g_ioManager shared_struct->g_ioManager

#define g_apSharedDeviceResetIOAscan shared_struct->g_apSharedDeviceResetIOAscan
#define g_apSharedDeviceResetIOCscan shared_struct->g_apSharedDeviceResetIOCscan

#define g_bPostFeedback shared_struct->g_bPostFeedback
#define g_hPostFeedbackWnd shared_struct->g_hPostFeedbackWnd
#define g_uiPostFeedbackMsg shared_struct->g_uiPostFeedbackMsg
#define g_wPostFeedbackParam shared_struct->g_wPostFeedbackParam
#define g_lPostFeedbackParam shared_struct->g_lPostFeedbackParam
#endif

#undef g_iSharedEmuMonMax
#undef g_iSharedDeviceCallMax
#undef g_iSlaveCountMax
#undef g_iIOMax
#undef g_iMaxPassCodeCount
#undef g_bTraceEventCount
#undef g_bTraceRootTypeCount
#undef g_iSharedDeviceMax
#undef g_iIOManagerCountMax
#undef g_iPrimeNumbersMaximum
#undef g_iPrimeNumbersCount
#undef g_iDigitalInputMaxCount
#undef g_iSharedEncoderMaxCount

//USER_HEADER_START
#endif /* LIN_DEFINE_H */
//USER_HEADER_STOP