
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

#if !defined(INT8_MIN) || defined(__linux__)
#include <stdint.h>
#else
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

#ifdef WIN_ERR_EXPORTS
#ifndef WIN_ERR_API
#ifdef _WIN32
#define WIN_ERR_API __declspec(dllexport)
#elif defined __linux__
#define WIN_ERR_API  __attribute__((visibility ("default")))
#endif // __linux__
#endif //WIN_ERR_API
#else
#ifndef WIN_ERR_API
#ifdef _WIN32
#define WIN_ERR_API __declspec(dllimport)
#elif defined __linux__
#define WIN_ERR_API
#endif	// __linux__
#endif //WIN_ERR_API
#endif

WIN_ERR_API bool GetKernelPathExe(const wchar_t *wcFileName,int iSize,wchar_t *wcPathExe);
WIN_ERR_API bool GetKernelMsgBoxCmd(int iSize,wchar_t *pText);
WIN_ERR_API const wchar_t* GetKernelMsgBoxCmd();
WIN_ERR_API bool SetKernelMsgBoxCmd(const wchar_t *pText);
WIN_ERR_API bool GetKernelMsgBoxText(int iSize,wchar_t *pText);
WIN_ERR_API const wchar_t* GetKernelMsgBoxText();
WIN_ERR_API bool SetKernelMsgBoxText(const wchar_t *pText);
WIN_ERR_API bool GetKernelMsgBoxTitle(int iSize,wchar_t *pText);
WIN_ERR_API const wchar_t* GetKernelMsgBoxTitle();
WIN_ERR_API bool SetKernelMsgBoxTitle(const wchar_t *pText);
WIN_ERR_API HWND GetKernelMsgBoxHwnd();
WIN_ERR_API void SetKernelMsgBoxHwnd(HWND hWnd);
WIN_ERR_API LONG GetKernelMsgBoxType();
WIN_ERR_API void SetKernelMsgBoxType(LONG alSharedKernelMsgBoxType);
WIN_ERR_API LONG GetKernelMsgBoxReturn();
WIN_ERR_API void SetKernelMsgBoxReturn(LONG alSharedKernelMsgBoxReturn);
WIN_ERR_API int AllocKernelMsgBoxReturn2Index();
WIN_ERR_API void DesallocKernelMsgBoxReturn2Index(int iIndex);
WIN_ERR_API LONG GetKernelMsgBoxReturn2(int iIndex);
WIN_ERR_API void SetKernelMsgBoxReturn2(int iIndex, LONG alSharedKernelMsgBoxReturn);
WIN_ERR_API HWND GetKernelMsgBoxHwndDebug();
WIN_ERR_API void SetKernelMsgBoxHwndDebug(HWND hWnd);


