
#pragma once
#include "UTDriverOEMPAExport.h"
#ifdef _WIN32
#include "WTypes.h"  
#endif // _WIN32
#include "limits.h"
#include "UTKernelMessageBox.h"

#if !defined(__WARN__)
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __WARN__ __FILE__ "(" __STR1__(__LINE__) ") : Warning user: "
#endif //__WARN__

#define UTKernel_SetConfigurationFile			SetRootProgramDataFileCfgKernel
#define UTKernel_GetConfigurationFile			GetRootProgramDataFileCfgKernel
#define UTKernel_GetFolderDataFilesOEMPA		GetRootProgramDataSubFolderOEMPA
#define	UTKernel_GetFolderDataFiles				GetRootProgramDataSubFolderKey
#define UTKernel_SetFolderDataFiles				SetRootProgramDataSubFolderKey

const DWORD g_dwSharedNull=0xffffffff;
const LONGLONG g_llDummyCallback=0xffffffffffffffff;

DRIVER_OEMPA_API UINT UTKernel_RegisterWindowMessage();
DRIVER_OEMPA_API bool ListProcessModules(const wchar_t *pModuleNameSearch,const wchar_t *pPathSearch,int iPathSize,wchar_t *pPathFound,int iModuleNameSize,wchar_t *pModuleName);
DRIVER_OEMPA_API bool IsValidThreadID(DWORD dwThreadID);
#ifdef OLD_CFGKERNEL
DRIVER_OEMPA_API bool CreateFolderDataCfg(DWORD dwProductVersionLS, DWORD dwProductVersionMS, int iSize, wchar_t *pRootProgramDataFolder, int iSizeCfg, wchar_t *pRootProgramDataSubFolderCfg);
DRIVER_OEMPA_API bool CreateFolderDataFiles(DWORD dwProductVersionLS,DWORD dwProductVersionMS,int iSize,wchar_t *pFolderData);
DRIVER_OEMPA_API bool CreateFolderDataFilesSubFolder(const wchar_t *pSubFolder,int iSize,wchar_t *pFolderData);
DRIVER_OEMPA_API bool CreateFolderDataFilesOEMPA(int iSize,wchar_t *pFolderData);
DRIVER_OEMPA_API bool CreateFolderDataFilesToolbox(int iSize,wchar_t *pFolderData);
#else //OLD_CFGKERNEL
DRIVER_OEMPA_API bool CreateRootProgramDataSubFolder(const wchar_t *pSubFolder);
#endif //OLD_CFGKERNEL
DRIVER_OEMPA_API bool UTKernel_GetFolderFromFileName(const wchar_t *wcUTKernelPathExe,int iSize,wchar_t *wcUTKernelPrivateProfile);
DRIVER_OEMPA_API bool UTKernel_GetFileVersionInfo(	wchar_t *wcUTKernelPathExe,VS_FIXEDFILEINFO &fixedFileInfo,
									wchar_t *wcProductName,int iSizeProduct,wchar_t *wcCompanyName,int iSizeCompany);
//Change configuration file name and folder. Only available on Linux.
DRIVER_OEMPA_API bool SetRootProgramDataFileCfgKernel(const wchar_t* wcNewPath);

DRIVER_OEMPA_API BYTE GetSharedByte(BYTE volatile* pData);
DRIVER_OEMPA_API BYTE SetSharedByte(BYTE volatile* pData, BYTE byValue);
DRIVER_OEMPA_API int GetSharedInt(int volatile* pData);
DRIVER_OEMPA_API int SetSharedInt(int volatile* pData, int iValue);
DRIVER_OEMPA_API LONG GetSharedLong(LONG volatile* pData);
DRIVER_OEMPA_API LONG SetSharedLong(LONG volatile* pData,LONG lValue);
DRIVER_OEMPA_API LONG IncrementSharedLong(LONG volatile* pData);
DRIVER_OEMPA_API LONG DecrementSharedLong(LONG volatile* pData);
DRIVER_OEMPA_API float GetSharedFloat(float volatile* pData);
DRIVER_OEMPA_API float SetSharedFloat(float volatile* pData,float fValue);

#ifdef _WIN64
DRIVER_OEMPA_API LONGLONG GetSharedLongLong(LONGLONG volatile* pData);
DRIVER_OEMPA_API LONGLONG SetSharedLongLong(LONGLONG volatile* pData,LONGLONG lValue);
DRIVER_OEMPA_API LONGLONG IncrementSharedLongLong(LONGLONG volatile* pData);
DRIVER_OEMPA_API LONGLONG DecrementSharedLongLong(LONGLONG volatile* pData);
#endif //_WIN64

DRIVER_OEMPA_API bool EnterSharedMutex(LONG volatile* pMutex,LONG volatile* pMutexThreadId,DWORD dwSleepTime,DWORD dwSleepCount);
DRIVER_OEMPA_API bool TryEnterSharedMutex(LONG volatile* pMutex,LONG volatile* pMutexThreadId);
DRIVER_OEMPA_API bool LeaveSharedMutex(LONG volatile* pMutex,LONG volatile* pMutexThreadId);
DRIVER_OEMPA_API bool EnterSharedMutexWithCount(LONG volatile* pMutex,LONG volatile* pMutexThreadId,LONG volatile* pMutexCount,DWORD dwSleepTime,DWORD dwSleepCount);
DRIVER_OEMPA_API bool TryEnterSharedMutexWithCount(LONG volatile* pMutex,LONG volatile* pMutexThreadId,LONG volatile* pMutexCount);
DRIVER_OEMPA_API bool LeaveSharedMutexWithCount(LONG volatile* pMutex,LONG volatile* pMutexThreadId,LONG volatile* pMutexCount);
DRIVER_OEMPA_API bool EnterSharedMutexWithCount(DWORD dwThreadId, LONG volatile* pMutex, LONG volatile* pMutexThreadId, LONG volatile* pMutexCount, DWORD dwSleepTime, DWORD dwSleepCount);
DRIVER_OEMPA_API bool TryEnterSharedMutexWithCount(DWORD dwThreadId, LONG volatile* pMutex, LONG volatile* pMutexThreadId, LONG volatile* pMutexCount);
DRIVER_OEMPA_API bool LeaveSharedMutexWithCount(DWORD dwThreadId, LONG volatile* pMutex, LONG volatile* pMutexThreadId, LONG volatile* pMutexCount);

DRIVER_OEMPA_API long GetDeviceSWLoopCountMax(int iDeviceId);
DRIVER_OEMPA_API long SetDeviceSWLoopCountMax(int iDeviceId, long lCount);
DRIVER_OEMPA_API long IncrementDeviceSWLoopCountMax(int iDeviceId);
DRIVER_OEMPA_API long DecrementDeviceSWLoopCountMax(int iDeviceId);

DRIVER_OEMPA_API long GetDeviceSWThreadCountMax(int iDeviceId);
DRIVER_OEMPA_API long SetDeviceSWThreadCountMax(int iDeviceId, long lCount);
DRIVER_OEMPA_API long IncrementDeviceSWThreadCountMax(int iDeviceId);
DRIVER_OEMPA_API long DecrementDeviceSWThreadCountMax(int iDeviceId);

DRIVER_OEMPA_API bool LockDeviceSWMutex(int iDeviceId, DWORD dwThreadId, DWORD dwSleepTime, DWORD dwSleepCount);
DRIVER_OEMPA_API bool TryLockDeviceSWMutex(int iDeviceId, DWORD dwThreadId);
DRIVER_OEMPA_API bool UnlockDeviceSWMutex(int iDeviceId, DWORD dwThreadId);
DRIVER_OEMPA_API long GetDeviceSWMutexLockCount(int iDeviceId, DWORD dwThreadId);

DRIVER_OEMPA_API bool LockDeviceSWHWMutex(int iDeviceId, DWORD dwThreadId, DWORD dwSleepTime, DWORD dwSleepCount);
DRIVER_OEMPA_API bool TryLockDeviceSWHWMutex(int iDeviceId, DWORD dwThreadId);
DRIVER_OEMPA_API bool UnlockDeviceSWHWMutex(int iDeviceId, DWORD dwThreadId);
DRIVER_OEMPA_API long GetDeviceHWMutexLockCount(int iDeviceId, DWORD dwThreadId);

DRIVER_OEMPA_API bool RegisterDeviceThreadId(int iDeviceId, DWORD dwThreadId, wchar_t *wcTraceComment);
DRIVER_OEMPA_API bool UnregisterDeviceThreadId(int iDeviceId, DWORD dwThreadId, wchar_t *wcTraceComment);

DRIVER_OEMPA_API bool EnterSharedMutexWithCount2(LONG volatile* pMutex,LONG volatile* pMutexThreadId,LONG volatile* pMutexCount,DWORD dwSleepTime,DWORD dwSleepCount,ULONGLONG &ullStartTime,ULONGLONG &ullMaxWaitingTime,ULONGLONG &ullTotalWaitingTime,bool bBreak);
DRIVER_OEMPA_API bool TryEnterSharedMutexWithCount2(LONG volatile* pMutex,LONG volatile* pMutexThreadId,LONG volatile* pMutexCount,ULONGLONG &ullStartTime,ULONGLONG &ullMaxWaitingTime,ULONGLONG &ullTotalWaitingTime,bool bBreak);
DRIVER_OEMPA_API bool LeaveSharedMutexWithCount2(LONG volatile* pMutex,LONG volatile* pMutexThreadId,LONG volatile* pMutexCount,ULONGLONG ullStartTime,ULONGLONG &ullMaxProcessingTime,bool bBreak);

DRIVER_OEMPA_API bool AtomToString(bool bDelete,ATOM hAtom,int iSize,wchar_t *string);
DRIVER_OEMPA_API bool StringToAtom(const wchar_t *string,ATOM &hAtom);

DRIVER_OEMPA_API void UTKernel_Trace(const wchar_t *pString);
DRIVER_OEMPA_API void UTKernel_SystemTrace(const wchar_t *pString);

DRIVER_OEMPA_API bool UTKernel_FileSave(const wchar_t *pFileName,const wchar_t *pSection,const wchar_t *pKey,const wchar_t *pValue);
DRIVER_OEMPA_API bool UTKernel_FileLoad(const wchar_t *pFileName,const wchar_t *pSection,const wchar_t *pKey,int iSize,wchar_t *pValue);

DRIVER_OEMPA_API int UTKernel_GetHexaSize(wchar_t *pValue);
DRIVER_OEMPA_API bool UTKernel_HexaToLongLong(wchar_t separator,wchar_t *pValue,int64_t &llValue);
DRIVER_OEMPA_API wchar_t* UTKernel_HexaToLongLong(wchar_t separator,wchar_t *pValue,int64_t &llValue,bool &bResult);
DRIVER_OEMPA_API wchar_t* UTKernel_HexaToLongLong(bool bDecimal,wchar_t separator,wchar_t *pValue,int64_t &llValue,bool &bResult);

DRIVER_OEMPA_API void UTDebug_New(void *pointer,int iBufferSize,int iSizeof,const char *pFile,int iLine);
DRIVER_OEMPA_API void UTDebug_Free(void *pointer,int iBufferSize,int iSizeof,const char *pFile,int iLine);

DRIVER_OEMPA_API const wchar_t* GetRootProgramDataFolder();
DRIVER_OEMPA_API const wchar_t* GetRootProgramDataSubFolderCfg();
DRIVER_OEMPA_API const wchar_t* GetRootProgramDataSubFolderOEMPA();
DRIVER_OEMPA_API const wchar_t* GetRootProgramDataSubFolderKey(const wchar_t *pSubFolder);
DRIVER_OEMPA_API const wchar_t* GetRootProgramDataFileCfgKernel();
DRIVER_OEMPA_API void SetRootProgramDataSubFolderKey(const wchar_t *pSubFolder, const wchar_t *pFolder);
#ifdef ODL_CFGKERNEL
DRIVER_OEMPA_API const wchar_t* GetApplicationFolder();
#endif //ODL_CFGKERNEL
DRIVER_OEMPA_API const wchar_t* GetApplicationName();
DRIVER_OEMPA_API const wchar_t* GetApplicationExeFolder();
DRIVER_OEMPA_API void UTKernel_SetTraceGlobalFileName(wchar_t *pFilePath);//global file trace is shared with others.
DRIVER_OEMPA_API bool UTKernel_GetTraceGlobalFileName(int iSize,wchar_t *pFilePath);


DRIVER_OEMPA_API bool UTKernel_EnableTraceGlobal(bool bEnable);//first you need to set the file name "UTKernel_SetGlobalTraceFileName".
DRIVER_OEMPA_API bool UTKernel_IsTraceGlobalEnabled();

DRIVER_OEMPA_API LONG lround2(double x);
DRIVER_OEMPA_API int64_t llRound(double x);
DRIVER_OEMPA_API void UTKernel_CheckMemory();

