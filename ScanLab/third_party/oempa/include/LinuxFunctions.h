#pragma once
#ifndef _LINUX_FUNCTIONS_H_
#define _LINUX_FUNCTIONS_H_
#ifdef __linux__
#include "LinDefine.h"
#include <cstdarg>

#ifndef __GNUC__
#define __attribute__(a)
#endif

namespace linfuncs
{
	/* Window messaging */
	int PostMessage(void*, UINT, WPARAM, LPARAM);
	int SendMessage(void*, UINT, WPARAM, LPARAM);
	UINT RegisterWindowMessage(const wchar_t*);
	LRESULT DefWindowProc(void*, UINT, WPARAM, LPARAM);
	void PostQuitMessage(int);
	int DestroyWindow(void*);
	int IsWindow(void*);

	void OpenFileInEditor(const wchar_t*, bool);
	bool LinuxListProcessModules(const wchar_t *pModuleNameSearch, const wchar_t *pPathSearch, int iPathSize, wchar_t *pPathFound, int iModuleNameSize, wchar_t *pModuleName);
	bool LinuxComListProcessModules(const wchar_t *pSearchFor, int iSizeFull, wchar_t *wcUTSockFullPath, int iSize, wchar_t *wcUTSockPath);
	bool LinuxListProcessModules();
	bool LinuxFindProcessModule(const wchar_t *pExe, DWORD dwProcessId);
	bool LinuxFindProcess(const wchar_t *pExe, DWORD &dwProcessId);
	int LinuxUpdateCurrentProcessModuleList();
	int GetModuleFileName(void* module, wchar_t* resbuf, int buflen);
	bool LinuxEnableDebugPriv();
	bool LinuxGetMainWndFromProcessId(DWORD dwProcessId, HWND &hWnd);
	void LinuxDisplayInitError();
	int LinuxPostDisplayRootIdFromProcessId(DWORD dwOwnerPID, int iRootId, HWND hPostFeedbackWnd, UINT uiPostFeedbackMsg, WPARAM wPostFeedbackParam, LPARAM lPostFeedbackParam);
	bool LinuxUTKernel_RunExe(bool bWaitClose, const wchar_t* pExeName, HWND hPostFeedbackWnd, UINT uiPostFeedbackMsg, WPARAM wPostFeedbackParam, LPARAM lPostFeedbackParam);
	bool LinuxGetEnvironmentVariableProgramData(wchar_t *pData, int iSize);
	bool LinuxDumpModules(const wchar_t *pDumpFile);
	bool LinuxGetExeFolderId(DWORD &dwVolumeSerialNumber, DWORD &nFileIndexHigh, DWORD &nFileIndexLow, const char* = "");
	void LinuxUTKernel_TraceEdit(wchar_t *pFileName, bool bWaitClose);
	HWND LinuxDefaultWindow(HINSTANCE hInstance, int nCmdShow);
	CUTStringTable* LinuxGetStringTable(wchar_t *pModuleName);
	bool LinuxGetPrimaryDevice(DISPLAY_DEVICE &ddOut);
	bool LinuxListDisplaySettings(int index,
		wchar_t *m_DISPLAY_DEVICE_DeviceName,
		wchar_t *m_DISPLAY_DEVICE_DeviceID,
		DWORD &m_DEVMODE_dmDisplayFrequency,
		DWORD &m_DEVMODE_dmBitsPerPel,
		DWORD &m_DEVMODE_dmPelsWidth,
		DWORD &m_DEVMODE_dmPelsHeight);
	bool LinuxSetDisplayDefaults();
	bool LinuxSetDisplayResolution(LONG PelsWidth, LONG PelsHeight);
	bool LinuxGetOperatingSystemWindow(HWND hWnd, int iSize, wchar_t *pTitle, int &iResHorz, int &iResVert, WINDOWPLACEMENT &wndPlacement);

	int EnumThreadWindows(DWORD threadid, BOOL(*func)(void*, LPARAM), LONG param);
	int GetWindowText(void* window, wchar_t* text, int max);
	int GetSystemTimeAdjustment(PDWORD lpTimeAdjustment, PDWORD lpTimeIncrement, BOOL* lpTimeAdjustmentDisabled);
	DWORD GetFileVersionInfoSize(const wchar_t* filename, DWORD *handle);
	int GetFileVersionInfo(const wchar_t* filename, DWORD handle, DWORD len, void * data);
	int VerQueryValue(const void* block, const wchar_t* sub, void ** buf, unsigned int * len);
	int MessageBox(void*, const wchar_t*, const wchar_t*, unsigned int);
	void GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer);
	BOOL GetProcessWorkingSetSize(HANDLE  hProcess, PSIZE_T lpMinimumWorkingSetSize, PSIZE_T lpMaximumWorkingSetSize);
	int GetSystemMetrics(int index);
	bool SystemTimeToFileTime(SYSTEMTIME* st, FILETIME* ft);
	BOOL GetVolumeInformation(
		LPCWSTR  lpRootPathName,
		LPWSTR   lpVolumeNameBuffer,
		DWORD   nVolumeNameSize,
		LPDWORD lpVolumeSerialNumber,
		LPDWORD lpMaximumComponentLength,
		LPDWORD lpFileSystemFlags,
		LPWSTR   lpFileSystemNameBuffer,
		DWORD   nFileSystemNameSize
	);

#define TLS_OUT_OF_INDEXES ((DWORD)0xFFFFFFFF)
	LPVOID TlsGetValue(DWORD index);
	BOOL TlsSetValue(DWORD index, void* value);
	DWORD TlsAlloc();
	BOOL TlsFree(DWORD index);

	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////  unicode  ///////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	wchar_t * wcscpy_s(wchar_t * src, size_t sz, const wchar_t * dest);

	wchar_t * wcscat_s(wchar_t * src, size_t sz, const wchar_t * dest);

	template<size_t size>
	int wcscat_s(wchar_t(&strDestination)[size], const wchar_t * strSource)
	{
		memset(strDestination, 0, size);
		return wcscat_s(strDestination, size, strSource);
	}

	char * strcat_s(char * dst, size_t sz, const char * src);

	int strcpy_s(char*, size_t, const char*);

	template <size_t size>
	int vswprintf_s(wchar_t(&buffer)[size], const wchar_t *format, va_list argptr)
	{
		memset(buffer, 0, size * sizeof(wchar_t));
		return vswprintf(buffer, size, format, argptr);
	}

	int swprintf_s(wchar_t*, size_t, const wchar_t*, ...);

	template<size_t size>
	int swprintf_s(wchar_t(&buffer)[size], const wchar_t * format, ...)
	{
		va_list vlist;
		va_start(vlist, format);
		int ret = vswprintf(buffer, size, format, vlist);
		va_end(vlist);
		return ret;
	}

	int wsprintf(wchar_t *buffer, const wchar_t * format, ...);

	int sprintf_s(char *, size_t, const char*, ...) 
		__attribute__((format(printf, 3, 4)));

	template<size_t size>
	int sprintf_s(char(&buffer)[size], const char * format, ...) 
		__attribute__((format(printf, 2, 3)));
	template<size_t size>
	int sprintf_s(char(&buffer)[size], const char * format, ...)
	{
		va_list vlist;
		va_start(vlist, format);
		int ret = vsnprintf(buffer, size, format, vlist);
		va_end(vlist);
		return ret;
	}

	int swscanf_s(const wchar_t * buffer, const wchar_t * format, ...);

	int sscanf_s(const char*, const char*, ...)
		__attribute__((format(scanf, 2, 3)));

	int _wcsicmp(const wchar_t*, const wchar_t*);

	// splits the path.
	int _wsplitpath_s(const wchar_t * path, wchar_t * drive, size_t driveSz, wchar_t *dir, size_t dirSz,
		wchar_t * fname, size_t nameSz, wchar_t * ext, size_t extSz);

	template<size_t drivesize, size_t dirsize, size_t fnamesize, size_t extsize>
	int _wsplitpath_s(const wchar_t * path, wchar_t(&drive)[drivesize], wchar_t(&dir)[dirsize], wchar_t(&fname)[fnamesize], wchar_t(&ext)[extsize])
	{
		return _wsplitpath_s(path, drive, drivesize, dir, dirsize, fname, fnamesize, ext, extsize);
	}

	// sets a string to lowercase (at most sz chars are treated).
	int _wcslwr_s(wchar_t * str, int sz = 0);
#define _wcslwr(a)	_wcslwr_s(a)

	int _wfopen_s(FILE**, const wchar_t*, const wchar_t*);

	double _wtof(const wchar_t *);
	int _wtoi(const wchar_t *);
	int64_t _wtoi64(const wchar_t*);

	int MultiByteToWideChar(UINT, DWORD, LPCSTR, int, LPWSTR, int);
	int WideCharToMultiByte(UINT, DWORD, LPCWSTR, int, LPSTR, int, LPCSTR, LPBOOL);

	int QueryPerformanceCounter(LARGE_INTEGER*);
	int QueryPerformanceFrequency(LARGE_INTEGER*);

	DWORD GetTickCount();
	ULONGLONG GetTickCount64();
	void GetLocalTime(SYSTEMTIME*);
	void* GetCurrentProcess();
	int GetLastError();
	void SetLastError(int err);

	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////  shared libs  ///////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	int FreeLibrary(HANDLE);
	HINSTANCE LoadLibrary(const wchar_t*);
	void * GetProcAddress(HMODULE, const char*);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	/********************************************************************************************
	 ******** Microsoft Private profile functions (reading and writing '.ini' files)	 ********
	 ********************************************************************************************/
	int GetPrivateProfileString(const wchar_t *, const wchar_t *, const wchar_t *, wchar_t *, int, const wchar_t *);
	int WritePrivateProfileString(const wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *);
	int GetPrivateProfileInt(const wchar_t *, const wchar_t *, int, const wchar_t *);
}
#endif // __linux__
#endif /*_LINUX_FUNCTIONS_H_*/
