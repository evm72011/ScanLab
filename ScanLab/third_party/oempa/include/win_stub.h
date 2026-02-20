
#pragma once
#ifdef __linux__
#include "LinDefine.h"
#endif // __linux__

#ifndef DllExport
#ifdef _WIN32
#define DllExport __declspec(dllexport)
#elif defined __linux__
#define DllExport __attribute__((visibility ("default")))
#endif // __linux__
#endif

#ifndef DllImport
#ifdef _WIN32
#define DllImport __declspec(dllimport)
#elif defined __linux__
#define DllImport extern
#endif // __linux__
#endif

#ifdef _WIN32
#define L_PATH_SEP_C	L'\\'
#define LS				L"\\"
#define L_PATH_ROOT		L"C:"
#define L_PATH_ROOT_SEP	L"C:\\"
#define PS				"\\"
#define PATH_ROOT		"C:"
#define PATH_ROOT_SEP	"C:\\"
#define L_DLL			L".dll"
#define l_DLL			".dll"
#define PL_DLL
#define Pl_DLL
#define FPGAMGR_PATH	L"FpgaManager_v1.32\\"
#define PROGRAM_FILES	L"C:\\Program Files"
#define PROGRAM_SOURCES_INSTALL_FOLDER	L"Sources\\UTKernel\\x64\\Release\\"
#elif defined __linux__
#define L_PATH_SEP_C	L'/'
#define LS				L"/"
#define L_PATH_ROOT		L"~"
#define L_PATH_ROOT_SEP	L"~/"
#define PS				"/"
#define PATH_ROOT		"~"
#define PATH_ROOT_SEP	"~/"
#define L_DLL			L".so"
#define l_DLL			".so"
#define PL_DLL			L"lib"
#define Pl_DLL			"lib"
#define FPGAMGR_PATH
// There is no equivalent of "Program Files" on Linux, there are instead standard path for executables (/bin), libraries (/lib) and headers (/include).
#define PROGRAM_FILES	L"/usr/local"
#define PROGRAM_SOURCES_INSTALL_FOLDER	L"Sources/UTKernel/x64/Release/"
#endif // __linux__

#define CYCLE_ORDERING

#if !defined(INT8_MIN) || defined(__linux__)
#include <stdint.h>
#else
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif



const int g_iSharedDeviceMax = 256;

#ifndef PSAPI_STUB_API
#ifndef __linux__
// On Linux this struct is defined in the file "LinDefine.h"
typedef struct structToolboxWizard {
	//Wizard beam management
	int iCount;
	int iIndex;
	double dProbeX, dProbeY, dProbeZ;
	double dEmergenceX, dEmergenceY, dEmergenceZ;
	double dFocalX, dFocalY, dFocalZ;
	wchar_t pInput[MAX_PATH];
	wchar_t pOutput[MAX_PATH];
	//Wizard device
	wchar_t pIPAddress[50];
	int iPort;
	int iDeviceId;
} structToolboxWizard;
#endif // !__linux__
const int g_iSharedDeviceMutexMax = 48;
typedef bool(*pCallbackWriteAcquisitionData)(BYTE *pBuffer, int64_t i64BufferSize, void *pData, int64_t i64DataSize, int64_t &i64Index);
typedef bool(*pCallbackReadAcquisitionData)(BYTE *pBuffer, int64_t i64BufferSize, void *pData, int64_t i64DataSize, int64_t &i64Index);

#endif //PSAPI_STUB_API


#ifdef PSAPI_STUB_EXPORTS
#ifndef PSAPI_STUB_API
#ifdef _WIN32
#define PSAPI_STUB_API __declspec(dllexport)
#elif defined __linux__
#define PSAPI_STUB_API  __attribute__((visibility ("default")))
#endif // __linux__
#endif //PSAPI_STUB_API
#else
#ifndef PSAPI_STUB_API
#ifdef _WIN32
#define PSAPI_STUB_API __declspec(dllimport)
#elif defined __linux__
#define PSAPI_STUB_API
#endif	// __linux__
#endif //PSAPI_STUB_API
#endif

#ifdef _WIN32
PSAPI_STUB_API BOOL fileCloseHandle(HANDLE a);
PSAPI_STUB_API BOOL mmapCloseHandle(HANDLE a);
PSAPI_STUB_API BOOL eventCloseHandle(HANDLE a);
PSAPI_STUB_API BOOL mutexCloseHandle(HANDLE a);
PSAPI_STUB_API BOOL processCloseHandle(HANDLE a);
PSAPI_STUB_API BOOL threadCloseHandle(HANDLE a);
#endif //_WIN32
PSAPI_STUB_API BOOL IsWow64();
void PSAPI_STUB_API SafeCopyWString(wchar_t *wcDst, int iSize, const wchar_t *wcSrc);

//#define DEFINE_UTKERNEL_ERROR
#if !defined(DEFINE_UTKERNEL_ERROR) && !defined(PSAPI_STUB_EXPORTS)
#include "win_err.h"
#pragma comment(lib,"win_err.lib")
#endif

#ifdef DEFINE_UTKERNEL_ERROR
PSAPI_STUB_API bool GetKernelPathExe(const wchar_t *wcFileName,int iSize,wchar_t *wcPathExe);
PSAPI_STUB_API bool GetKernelMsgBoxCmd(int iSize,wchar_t *pText);
PSAPI_STUB_API const wchar_t* GetKernelMsgBoxCmd();
PSAPI_STUB_API bool SetKernelMsgBoxCmd(const wchar_t *pText);
PSAPI_STUB_API bool GetKernelMsgBoxText(int iSize,wchar_t *pText);
PSAPI_STUB_API const wchar_t* GetKernelMsgBoxText();
PSAPI_STUB_API bool SetKernelMsgBoxText(const wchar_t *pText);
PSAPI_STUB_API bool GetKernelMsgBoxTitle(int iSize,wchar_t *pText);
PSAPI_STUB_API const wchar_t* GetKernelMsgBoxTitle();
PSAPI_STUB_API bool SetKernelMsgBoxTitle(const wchar_t *pText);
PSAPI_STUB_API HWND GetKernelMsgBoxHwnd();
PSAPI_STUB_API void SetKernelMsgBoxHwnd(HWND hWnd);
PSAPI_STUB_API LONG GetKernelMsgBoxType();
PSAPI_STUB_API void SetKernelMsgBoxType(LONG alSharedKernelMsgBoxType);
PSAPI_STUB_API LONG GetKernelMsgBoxReturn();
PSAPI_STUB_API void SetKernelMsgBoxReturn(LONG alSharedKernelMsgBoxReturn);
PSAPI_STUB_API HWND GetKernelMsgBoxHwndDebug();
PSAPI_STUB_API void SetKernelMsgBoxHwndDebug(HWND hWnd);
#endif //DEFINE_UTKERNEL_ERROR


/**
   Checks in the following order if one private path to 'CfgKernel.txt' is defined:
   - 'CfgKernel' environment variable;
   - '/CfgKernel=<path>' command line argument (no space allowed);
   - or the special one-line file: '<app>_CfgKernel.txt'.

   If the path contains %EnvironmentVariable%, they are interpolated.

   The private path has to end with: 'Cfg\CfgKernel.txt':

   @param [in,out] wcCfgKernelPath is the private "CfgKernel.txt" path if the function returns true
   @returns true if a valid private 'CfgKernel.txt' file was defined */
PSAPI_STUB_API bool GetPrivateCfgKernelPath(wchar_t wcCfgKernelPath[MAX_PATH]);



#define WPARAM_TOOLBOX_HWND					0x00000001
#define WPARAM_TOOLBOX_CLOSE				0x00000002
#define WPARAM_TOOLBOX_WIZARD_NEW			0x00000003
#define WPARAM_TOOLBOX_WIZARD_DEL			0x00000004
#define WPARAM_TOOLBOX_WIZARD_UPDATE		0x00000005
#define WPARAM_TOOLBOX_WIZARD_RESET			0x00000006
#define WPARAM_TOOLBOX_WIZARD_ISENABLED		0x00000007
#define WPARAM_TOOLBOX_LOAD_WIZARD			0x00000008
#define WPARAM_TOOLBOX_SAVE_WIZARD			0x00000009
#define WPARAM_TOOLBOX_LOAD_MATRIX			0x0000000A
#define WPARAM_TOOLBOX_SAVE_MATRIX			0x0000000B
#define WPARAM_TOOLBOX_WIZARD_BEAM_COUNT	0x0000000C
#define WPARAM_TOOLBOX_WIZARD_BEAM			0x0000000D
#define WPARAM_TOOLBOX_WIZARD_ELEMENT_COUNT	0x0000000E
#define WPARAM_TOOLBOX_WIZARD_ELEMENT		0x0000000F
#define WPARAM_TOOLBOX_TOOLBOX_GET			0x00000010
#define WPARAM_TOOLBOX_TOOLBOX_SET			0x00000011
#define WPARAM_TOOLBOX_KEEPALIVE			0x00000012
#define WPARAM_TOOLBOX_WIZARD_GETID			0x00000013
#define WPARAM_TOOLBOX_SAVE_SETUP_DEFAULT	0x00000014
#define WPARAM_TOOLBOX_DEVICE_GETID			0x00000015
#define WPARAM_TOOLBOX_DEVICE_ADDRESS		0x00000016
#define WPARAM_TOOLBOX_DEVICE_CONNECTION	0x00000017
#define WPARAM_TOOLBOX_DEVICE_ISCONNECTED	0x00000018
#define WPARAM_TOOLBOX_DISPLAY				0x00000019
#define WPARAM_TOOLBOX_GETROOTID			0x0000001A
#define WPARAM_TOOLBOX_VISIBLE				0x0000001B
#define WPARAM_TOOLBOX_SAVE_SETUP			0x0000001C
#define WPARAM_TOOLBOX_DEVICE_TYPE			0x0000001D
#define WPARAM_TOOLBOX_ECHO					0x0000001E
#define WPARAM_ENABLE_EVENT_UPDATE			0x0000001F

#if (defined(_WIN32) && defined(WIN_STUB_ADAPTERS))
#include <IPTypes.h>
const int g_iAdapterCountMax = 32;
typedef DWORD(*WTSGETACTIVECONSOLESESSIONID)();
typedef BOOL(*LPFN_CreateEnvironmentBlock)(LPVOID *lpEnvironment, HANDLE hToken, BOOL bInherit);
typedef BOOL(*LPFN_DestroyEnvironmentBlock)(LPVOID lpEnvironment);
typedef struct structEthernetAdapter
{
	IP_ADAPTER_INFO info;
	union {
		ULONG Flags;
		struct {
			ULONG DdnsEnabled : 1;
			ULONG RegisterAdapterSuffix : 1;
			ULONG Dhcpv4Enabled : 1;
			ULONG ReceiveOnly : 1;
			ULONG NoMulticast : 1;
			ULONG Ipv6OtherStatefulConfig : 1;
			ULONG NetbiosOverTcpipEnabled : 1;
			ULONG Ipv4Enabled : 1;
			ULONG Ipv6Enabled : 1;
			ULONG Ipv6ManagedAddressConfigurationSupported : 1;
		};
	};
	ULONG Mtu;
	IFTYPE IfType;
	ULONG64 TransmitLinkSpeed;
	ULONG64 ReceiveLinkSpeed;
} structEthernetAdapter;
typedef struct structEthernetAdapter2 {
	DWORD dwInterfaceIndex;
}structEthernetAdapter2;
#endif
