
#pragma once
#include "UTServerCommon.h"
#include "myMFC.h"
#include "_Socket.h"
#include "SocketServer.h"

#include "UTServerExport.h"
#include "win_stub.h"
#include <list>
#ifdef _WIN32
#include <conio.h>  
#define DEBUG_LABVIEW
#endif // _WIN32
#ifdef __linux__
#include <string>
#endif

class CUTServer;
typedef enum enumServerCommand{ eCmdServerSelect, eCmdServerTransit, eCmdServerCustom } enumServerCommand;
typedef int (*pTypeServerCallback)(CUTServer *pServer, enumServerCommand eCmd, wchar_t *wcCmdLine, char *pOutput, int iOutputSize);

const int g_iRouteIsConnected = 2;
const int g_iAcceptSocketTimeOut = 5000;
const int g_iDeviceManagerCountMax = 16;
const int g_iSocketManagerDeviceCountMax = g_iSharedDeviceMax;

class CSocket_;
class CUTServer;
class CUTClient;
class CHWDeviceOEMPA;
class CServerManager;
class CDeviceManager;
class CFtpClientCmd;

typedef enum enumServerManagerErrorCounters {
	eServerManagerError_Connection,
	eServerManagerError_Pulser,
	eServerManagerError_StreamError,
	eServerManagerError_AscanLoss,
	eServerManagerError_CscanLoss,
	eServerManagerError_EncoderLoss,
	eServerManagerError_SWLoss,
	eServerManagerError_Test,
	eServerManagerError_FifoLossAscan,
	eServerManagerError_FifoLossCscan,
	eServerManagerError_FifoLossIO,
	eServerManagerError_FifoLossStream,
	eServerManagerError_Last
}enumServerManagerErrorCounters;

typedef enum enumServerManagement
{
	eNewSocketClient,
	eNewSocketData,
	eNewSocketAccepted,
	eNewSocketRejected
} enumServerManagement;
typedef struct structServerManagement
{
	enumServerManagement eServerManagement;
	CUTServer *pServer;
	CSocket_ *pSocket;
} structServerManagement;
typedef bool (*pTypeServerManagement)(structServerManagement *);
ROUTE_DEVICE_API void RegisterServerManagement(pTypeServerManagement func);
ROUTE_DEVICE_API pTypeServerManagement GetServerManagement();
#ifndef DRIVER_SERVER_EXPORTS
extern "C" ROUTE_DEVICE_API bool RouteServer(structDataRouteServer *, DWORD dwTimeOutStepMs, int iTimeOutCount, bool &bTimeOut);
#endif //DRIVER_SERVER_EXPORTS


typedef struct structCheckReturnedValues
{
	bool check;
	int64_t value;
}structCheckReturnedValues;



class ROUTE_DEVICE_API CSystem
{
public:
	static bool TryLock();
	static bool Lock(DWORD dwTryTimeOutMs = 0);
	static bool Unlock();
	static bool IsLocked();
	static int GetState();
	static bool WaitInitEnd(DWORD dwTimeOutMs = 0);
public:

public:
private:
	static LONG m_lSytemMutex;
	static DWORD m_dwSytemMutexThreadId;
	static DWORD m_dwSytemMutexCount;
	static int g_iSytemState;
	static DWORD m_dwInitThreadId;
};

class CTransitSocket;
class ROUTE_DEVICE_API _CServerManager
{
private:
	ULONGLONG m_ullPrivateMemory[212];
public:
	_CServerManager();

};
class ROUTE_DEVICE_API CServerManager : public _CServerManager, public CSocketServer
{
public:
	CServerManager();
	~CServerManager();
	static bool IsService();
	static CServerManager* GetDefault();
	static bool IsAOSServiceRunning();
	static bool RegisterMeAsServerChild(int iMyServerPort, int iParentPort = 0);//"iParentPort=0" for the default service.
	static bool UnregisterMeAsServerChild();
	static bool GetRegisteredServerChildList(int iParentPort, wchar_t *list, int size);//"iParentPort=0" for the default service.
	void SetSocketName(wchar_t *wcName);

	bool UpdateServerPortFromCmdLine(wchar_t *wcCommandLine = NULL);//"/serverport=value" => "SetDefaultServerPort(value)".
	unsigned short GetServerPort();
	static unsigned short GetDefaultServerPort();
	static bool SetDefaultServerPort(unsigned short usPort);//Sometimes the real listen port could be a little bit different.
	bool IsSharedMemory();

	int Set(int iPort);//return the real port number.
	void Get(int &iPort);
	static bool CheckServerAlived(CUTServer *pServer);
	static CUTServer *GetServerByName(const wchar_t *wcName);
	static CUTServer *GetServer(CUTServer *pServer);
public:

public:
	static CUTServer *GetServerParent();
	static int GetServerParentPort();
	static int GetServerCount();

	bool StartListening();
	bool StartListening(bool bReuseAddr, bool bSharedMemory = true);
	bool IsListening();
	static DWORD GetTelnetSessionTimeOut();
	static bool StartTelnetApplication(bool bRemoteServer, int iTelnetMode);
	static bool IsTelnetSessionEnabled(DWORD dwTimeOutMs = GetTelnetSessionTimeOut());
	static bool WaitingForTelnetSession(DWORD dwTimeOutMs = GetTelnetSessionTimeOut());

	static int sGetServerCount();
	static void sCloseServerAll();

	bool OnCommandLine(char *cMsg, int size);
	bool OnPreCommandAtomic(bool bEnter, wchar_t *wcMsg, int iMsgSize);
	bool OnPostCommandAtomic(bool bEnter, bool bProcessed, const wchar_t *wcMsg);
	int SendAllServer(CUTServer* pExcept, const void *buf, int size, int flags = 0);
	int ProcessAllServer(CUTServer* pExcept, bool bEnter, void *buf, int size, int flags = 0);

#ifndef OEMPA_SERVICE
	void SetAcceptTransit(CUTServer *pServer, int iDeviceId, int iAcceptTimeOut, structAcceptSocketOptions &options);
	CUTServer *GetAcceptTransit(bool bPeek, int &iAcceptTimeOut, structAcceptSocketOptions *pOptions, LONG &lAcceptCount, LONG &lAcceptIndex);
	void SetAcceptTransits(CUTServer *pServer, int iDeviceCount, int iDeviceId, int iAcceptTimeOut, structAcceptSocketOptions &options, uint64_t ui64Mask);

	CHWDeviceOEMPA* OEMPA_NewDevice(enumHardware eHW);
	bool LoadCustomizedOEMPA();
#endif //OEMPA_SERVICE

	static bool StartupScriptStartup();
	static char* StartupScriptStartup(char *cmd);
	static char* StartupScriptStartup(wchar_t *cmd);
	static bool IsScriptStartupLoaded();

	static CUTServer *GetTelnetDebugTrace();
	static bool Trace(const wchar_t *wcMsg, unionRouteDataOptionsIn in = g_DefaultRouteDataOptionsIn);
	static bool Trace(const char *cMsg, unionRouteDataOptionsIn in = g_DefaultRouteDataOptionsIn);
	static bool IsTrace();

	static DWORD GetWPRThreadId();
	bool TestWPR();
	static int ErrorCountersData(enumServerManagerErrorCounters item, UINT64 value);

	static void RejectSameServerName(bool bEnable);
	static bool IsSameServerNameRejected();
#ifndef OEMPA_SERVICE
#endif //OEMPA_SERVICE
#ifndef OEMPA_SERVICE
#endif //OEMPA_SERVICE
protected:
#ifndef OEMPA_SERVICE
#endif //OEMPA_SERVICE
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void TSocketReport(wchar_t *string);
	virtual void TSocketReport(char *string);
	virtual void OnListened(int nErrorCode);
	virtual void OnTimeOut();
#ifndef OEMPA_SERVICE
#endif //OEMPA_SERVICE
#ifndef OEMPA_SERVICE
#endif //OEMPA_SERVICE

public:
};

#ifndef OEMPA_SERVICE
class ROUTE_DEVICE_API_ALIGN _CClientManager
{
private:
	ULONGLONG m_ullPrivateMemory[196];
public:
	_CClientManager();

};

class ROUTE_DEVICE_API CClientManager : public _CClientManager
{
public:
	CClientManager();
	~CClientManager();
	static CClientManager* GetDefault();

	bool UpdateRouteFromCmdLine();//"/route=IP:port" => IP will be the IP address of the remote server, port will be the default port.
	bool UpdateRouteFromCmdLine(wchar_t *wcRoute);
	bool Connect(const wchar_t *wcClientName, DWORD dwTimeOut = 250);
		//iFeedbackLocalServerPort=0 => no feedback client.
	bool ConnectByHWAddress(const wchar_t *wcHWIPAddress, const wchar_t *wcClientName, DWORD dwTimeOut = 250);
	bool IsConnected();
	bool Disconnect();
	int SendCmd(const wchar_t *wcClientName, const wchar_t *wcCmdLine, int iCmdLineSize, DWORD dwTimeOutStepMs, int iTimeOutCount, int64_t aiData[g_iDriverServerDataCountMax], wchar_t *wcStringOut = NULL, int iStringSize = 0);
		//"SendCmdLine" the default server is the single connected server.
	int GetRemotePortConnected(const wchar_t *wcClientName);//return 0 if not connected otherwise the connected remote server port.
	int GetRemotePortDefault();
	void SetFeedbackName(const wchar_t *wcName);
	const wchar_t *GetFeedbackName();
	const wchar_t *GetIPAddress();
	static const wchar_t* StartLocalRootServer(const wchar_t *csCmdLine, wchar_t *csConsoleTitle);
	static bool IsLocalIPAddress(const wchar_t *wcIPAddress);
public:
protected:

public:
};
#else //OEMPA_SERVICE
class _CClientManager
{
public:
	int x;
};
class CClientManager
{
public:
	int x;
};
#endif //OEMPA_SERVICE

class ROUTE_DEVICE_API CDeviceRoute
{
public:
	//device route table management.
	static int GetCount();
	static bool LoadFile(const wchar_t *wcFileName);
	static bool PushFront(wchar_t *wcDeviceAddress, wchar_t *wcRemoteServerIP);
	static void ResetServer();
	static bool GetRemoteServer(int iIndex, wchar_t *wcDeviceAddress, int iDeviceAddressSize, wchar_t *wcRemoteServerIP, int iRemoteIPSize);
	static bool GetRemoteServer(wchar_t *wcDeviceAddress, wchar_t *wcRemoteServerIP, int iRemoteIPSize, wchar_t *wcOriginRemoteDriverIP, int iOriginRemoteIPSize);
	static bool UpdatePort(wchar_t *wcRemoteServerIP, int iRemoteIPSize, int iPort);
	static bool UpdateRemoteServerPort(wchar_t *wcRemoteServerIP, int iPort);
	static void DisplayRoute(CUTServer *pServer, char *cMsg, int iSize);

	static void ResetClient();
	static bool AddClient(int iDeviceId, const wchar_t *serverip);
	static bool RemoveClient(int iDeviceId);
	static bool GetRemoteClient(int iDeviceId, int ipsize, wchar_t *serverip);
public:
private:

public:
};



typedef bool(*TypeRegisterIsTraceFilterAtomic)(const wchar_t *wcMsg);
class ROUTE_DEVICE_API _CUTServer
{
private:
	ULONGLONG m_ullPrivateMemory[1345];
public:
	_CUTServer(CUTServer *pThis);
	~_CUTServer();

};
typedef enum enumUTParameterType{eUTDouble, eUTFloat, eUTInt, eUTString, eUTDoubleInt, eUTArrayDouble, eUTArrayFloat, eUTArrayInt} enumUTParameterType;
class ROUTE_DEVICE_API CUTServer : public _CUTServer, public CSocket_
{
protected:
	typedef enum enumOEMPACycleParameter {
		eNoCycleParameter, eCycleParameterAll, eCycleParameterGateAll, eCycleParameterCscanAll, eCycleParameterPulserAll, eCycleParameterReceiverAll,
		eCycleParameterTimeSlot, eCycleParameterPulserCount,
		eCycleParameterGainDigital, eCycleParameterGainAnalog, eCycleParameterBeamCorrection,
		eCycleParameterPulseWidthMax_, eCycleParameterDacEnable_, eCycleParameterDacCount_,
		eCycleParameterDacGainMin_, eCycleParameterDacGainMax_,
		eCycleParameterDacTimeMin_, eCycleParameterDacTimeMax_,
		eCycleParameterDacCycleId_, eCycleParameterDacGateId_,
		eCycleParameterWedgeDelayE_, eCycleParameterWedgeDelayR_, eCycleParameterThroughput,
		eCycleParameterEnableCorrection, eCycleParameterSelect, eCycleParameterCalibration,
		eCycleParameterTrackingAscan_, eCycleParameterTrackingDac_,
		eCycleParameterAscanStart_, eCycleParameterAscanRange_,
		eCycleParameterPointCount_, eCycleParameterPointFactor_, eCycleParameterDecimation_,
		eCycleParameterGateEnable, eCycleParameterGateStart, eCycleParameterGateStop,
		eCycleParameterGateThreshold, eCycleParameterGateModeAmp, eCycleParameterGateModeTof,
		eCycleParameterGateRectif, eCycleParameterGateTrackingStartCycleId, eCycleParameterGateTrackingStartGateId,
		eCycleParameterGateTrackingStopCycleId, eCycleParameterGateTrackingStopGateId,
		eCycleParameterCscanAmp, eCycleParameterCscanTof, eCycleParameterCscanValid,
		eCycleParameterPulserElement, eCycleParameterPulserWidth, eCycleParameterPulserDelay,
		eCycleParameterReceiverElement, eCycleParameterReceiverGain, eCycleParameterReceiverDelay,
		eCycleParameterLast
	} enumOEMPACycleParameter;
public:
	CUTServer();
	~CUTServer();

	bool Create();
	bool ConnectTCP(const wchar_t* lpszHostAddress, UINT nHostPort, bool bPing, bool bDisplayError);
	bool ConnectTCP(const char* lpszHostAddress, UINT nHostPort, bool bPing, bool bDisplayError);
	bool IsConnected() const;
	int mySend(const void *buf, int size, ULONGLONG traceOptions = g_DefaultTraceIn);
	bool ProcessCommandLine(char *msg, int iSize, CUTServer *pServerInOut = NULL, char *pBufferOut = NULL, int iBufferOut = 0);
	static void EnableCommandStandby(bool bStandby);
	static bool IsCommandStandbyEnabled();

	virtual void OnAccept(int nErrorCode);
	virtual void OnConnected(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual bool IsSend64(const void* lpBuf, int64_t nBufLen, int nFlags, int64_t &iRet);
	virtual void OnSend(int nErrorCode);
	virtual void CommunicationReport(wchar_t* string = NULL);
	virtual void CommunicationReport(char* string = NULL);
	virtual void OnReceive(int nErrorCode);
	virtual bool OnCommandLine(bool bEnter, char *cMsg, int size, wchar_t *wcBuffer, int iSizeBuffer);
				//return false if the command has been processed,
				//in this case both "OnPreCommandAtomic" and "OnPostCommandAtomic" will not be called.
	virtual bool OnPreCommandAtomic(bool bEnter, wchar_t *wcMsg, int iMsgSize);
				//process the atomic command before the default processing of the base class.
	virtual bool OnPostCommandAtomic(bool bEnter, bool bProcessed, const wchar_t *wcMsg);
				//process the atomic command if it has not been processed by the default processing of the base class, this function returns true if the command has been processed, false otherwise.
	virtual void OnEnterCommandLine(bool bEnter, const wchar_t *cMsg);
	virtual void OnLeaveCommandLine(bool bEnter);
	virtual bool OnThreadExit();

	static bool IsTraceFilterAtomic(const wchar_t *wcMsg);//return true to disable trace.
	static void RegisterTraceFilterAtomic(TypeRegisterIsTraceFilterAtomic func);

	bool ProcessCommandDefault(bool bEnter, const wchar_t *wcMsg);
	void ProcessCommandFtp(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandData(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandLibrary(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandServer(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandScript(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandGeneral(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandSafe(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandWPR(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
#ifndef OEMPA_SERVICE
	void ProcessCommandStatus(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandFifo(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandDevice(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandDeviceOEMPA(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandDeviceOEMPAs(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
	void ProcessCommandDeviceDebug(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);
#endif //OEMPA_SERVICE
	void ProcessCommandRemote(wchar_t *wcMsg, int iSizeBuffer, bool &bProcess);

	bool ProcessRemoteCommand(char *cmd, int iSize);
	bool ProcessCommandBoolean(const wchar_t *wcStringId, const wchar_t *wcMsg, bool &bProcess, bool &bValue, bool *pbSet = NULL);
	bool ProcessCommandBoolean2(const char *cStringId, const char *cMsg, bool &bProcess, bool &bValue, bool *pbSet);
	bool ProcessCommandInt(const wchar_t *wcStringId, const wchar_t *wcMsg, bool &bProcess, int &iValue, bool *pbSet);
	bool ProcessCommandInt64(const wchar_t *wcStringId, const wchar_t *wcMsg, bool &bProcess, int64_t &i64Value, bool *pbSet);
	bool ProcessCommandDWORD(const wchar_t *wcStringId, const wchar_t *wcMsg, bool &bProcess, DWORD &dwValue, bool *pbSet);
	bool ProcessCommandDWORD2(const char *wcStringId, const char *cMsg, bool &bProcess, DWORD &dwValue, bool *pbSet);
	bool ProcessCommandIndexId(const wchar_t *wcStringId, int iIndexMin, int iIndexMax, const wchar_t *wcMsg, bool &bProcess, int &iIndexId);
	bool ProcessCommandBYTEHexa(const wchar_t *wcStringId, const wchar_t *wcMsg, bool &bProcess, BYTE &byValue, bool *pbSet);
	bool ProcessCommandULONGLONGHexa(const wchar_t *wcStringId, const wchar_t *wcMsg, bool &bProcess, ULONGLONG &ullValue, bool *pbSet);
#ifndef OEMPA_SERVICE
	void ProcessCommandCycle(char *cMsg, int iMsgSize, int iCycleCount, double dFWClockPeriod, const structCycleParameter *pData, const structCycleParameterPA *pDataPA, int iCycleIndex);
	void ProcessCommandGate(char *cMsg, int iMsgSize, int iGateId, double dFWClockPeriod, const structOEMPACycleGate *pGate);
	void GetCycleParameterFromString(const wchar_t *wcString, enumOEMPACycleParameter &eCycleParameter);
	bool UpdateClassCycle(CHWDeviceOEMPA *pHWDeviceOEMPA, structCycleParameter *pData, structCycleParameterPA *pDataPA, const wchar_t *wcString, wchar_t *wcMsg, char *cMsg, int iSize, int iCycleCount, int iIndexMin, int iIndexMax, enumUTParameterType eType, bool &bProcess);
	bool SetClassCycleParameter(CHWDeviceOEMPA *pHWDeviceOEMPA, structCycleParameter *pData, structCycleParameter *pParameter, structCycleParameterPA *pDataPA, structCycleParameterPA *pParameterPA, char *cMsg, int iSize, int iCount, int iIndexMin, int iIndexMax, enumOEMPACycleParameter eCycleParameter, int iGateId, int iCscanGate, enumCycleCscan eCscan, bool &bOutOfRange);
	bool GetClassCycleParameter(CHWDeviceOEMPA *pHWDeviceOEMPA, structCycleParameter *pData, structCycleParameterPA *pDataPA, char *cMsg, int iSize, bool bAllFields, int iCount, int iIndexMin, int iIndexMax, enumOEMPACycleParameter eCycleParameter, int iGateId, int iCscanGate, enumCycleCscan eCscan);
	bool UpdateHWCycle(CHWDeviceOEMPA *pHWDeviceOEMPA, structCycleParameter *pData, const wchar_t *wcString, wchar_t *wcMsg, char *cMsg, int iSize, const char *cUnit, float fReadUnitFactor, int iCycleCount, int iIndexMin, int iIndexMax, enumUTParameterType eType, bool bRequestHW, bool &bProcess);
	bool UpdateCycleGate(CHWDeviceOEMPA *pHWDeviceOEMPA, wchar_t *wcMsg);
	bool UpdateArrayIndex(wchar_t* &wcMsg, int iMin, int iMax, int &iIndex);
	bool UpdateArrayIndexList(wchar_t* &wcMsg, int iMax, int &iIndexMin, int &iIndexMax, bool &bWithField);
	bool UpdateArrayHexa(wchar_t* &wcMsg, int64_t &value);
	bool TransitSocket(wchar_t *wcMsg, CHWDeviceOEMPA *pHWDeviceOEMPA, bool bAllDevices);
#endif //OEMPA_SERVICE

	bool iSetData(int iIndex, int64_t value);
	int64_t iGetData(int iIndex=0);
	void dSetData(double value);
	double dGetData();
	void sSetData(const wchar_t* value);
	const wchar_t* sGetData();
	int GetCountIn();
	void ResetCountIn();
	int GetCountOut();

	void SetServerList(CServerManager *ptr);
	int GetCurrentDeviceId();
	int GetCycleIndex();
	int GetGateIndex();

	bool iSendAndWaitData(HANDLE apSharedEvent, char *cmd, DWORD dwTimeOutStepMs, int iTimeOutCount, bool &bTimeOut, int iCheckSize = 0, structCheckReturnedValues *checkReturnedValues = NULL, double *pdProcessTime = NULL);
	static int GetCommandCount(char *cmd);
	static int GetReturnCount(char *cmd);
	static int GetReturnCount(wchar_t *cmd);
	static bool Next(wchar_t* wcMsg, wchar_t* &wcCopy, int &iSizeCopy);

	bool IsServer();
	bool IsDriver();
	bool IsReturned();
	bool IsClassServer() const;
	static bool sDump(const wchar_t *line, int size, unionRouteDataOptionsIn in);
	static bool sDump(const char *line, int size, unionRouteDataOptionsIn in);
	void DirectSendString(const char *string);
	void DirectSendString(const wchar_t *string);
	void PostponeSendString(const char *string);
	void ReturnSendString(bool bRet, int iRet, char *pMsg);

	static void SetServerCallback(pTypeServerCallback func);
	static pTypeServerCallback GetServerCallback();

#ifndef OEMPA_SERVICE
	bool CheckAccept(CServerManager *pDriverListener, int iDeviceId);
	int GetHWDeviceOEMPASelection(CHWDeviceOEMPA **apHWDeviceOEMPA, int iSize);//return -1 if the size is not enough.
	int GetHWDeviceOEMPACalibrationSelection(CHWDeviceOEMPA **apHWDeviceOEMPA, int iSize);//return -1 if the size is not enough.
#endif //OEMPA_SERVICE
	CServerManager *GetServerList();
	void SetClassName(const wchar_t* cMsg);
	const wchar_t* GetClassName() const;
	bool SetName(const wchar_t* wcMsg);
	const wchar_t* GetName() const;
	float GetTemperatureMax(CHWDeviceOEMPA *pHWDeviceOEMPA);

	CUTServer *GetServerForward();
	bool SetServerForward(CUTServer *pServer);
	void EnablePrompt(bool bEnable);
	void SetQuit(bool bQuit);
	static bool IsTraceIn();
	static bool IsTraceOut();
	static void EnableTraceIn(bool bEnable);
	static void EnableTraceOut(bool bEnable);
	static bool IsLogFileEnabled();
	static bool IsTraceMini();
	static void EnableTraceMini(bool bEnable);
	static bool IsTraceCustom();
	static void EnableTraceCustom(bool bEnable);
	void DumpStatusFifo();

#ifndef OEMPA_SERVICE
	int GetSelectedCount();
	int GetSelectedCount(CHWDeviceOEMPA **apHWDeviceOEMPA, int iSize);
	static int GetTemperatureMaxCount();
	static void SetTemperatureMaxCount(int iValue);
#endif //OEMPA_SERVICE
	bool SafeDeleteMe(DWORD dwDelayMs = 10);

	static bool SetRemoteName(wchar_t *wcRemoteName);

public:
#ifndef OEMPA_SERVICE
#endif //OEMPA_SERVICE
private:
#ifndef OEMPA_SERVICE
#endif //OEMPA_SERVICE
public:

public:
};

const int g_iPortIncrementCountMax = 4;
const int g_iClientStringSize = 10 * 1024;
class CUTClient;
class ROUTE_DEVICE_API _CUTClient
{
private:
	ULONGLONG m_ullPrivateMemory[4346];
public:
	_CUTClient(CUTClient *pClient, wchar_t *wcRemoteServerIP, bool bText);
	_CUTClient(CUTClient *pClient, const wchar_t *wcRemoteServerIP, bool bText);
	~_CUTClient();

};
class ROUTE_DEVICE_API CUTClient : public _CUTClient, public CUTServer
{
public:
	CUTClient(wchar_t *wcRemoteServerIP, bool bDriver = false, bool bText = true);
	CUTClient(const wchar_t *wcRemoteServerIP, bool bDriver = false, bool bText = true);
	~CUTClient();

	static void Reset();
	static bool Connect(bool bOnlyViaSharedMemory, int iPortOrigin, wchar_t *wcRemoteServerIP, int iPortIncrementCount, int &iPortOut, unsigned short port[g_iPortIncrementCountMax], DWORD dwTimeOut = 250);
	bool Connect(DWORD dwTimeOut = 250);
	bool ProcessCommand(CUTServer *pServer, char *cmd, int iSize);

	static int GetClientCount();
	static CUTClient* GetClient(int iIndex);
	static CUTClient* GetClientDriver(int iIndex);
	static CUTClient* GetClient(const wchar_t *wcRemoteServerIP);
	static CUTClient* GetClient(const wchar_t *wcRemoteServerIP, int iPortIncrementCount, int &iPortOrigin);
	static CUTClient* GetClientByName(const wchar_t *wcName);
	static void ListClientThreadIds(CUTServer *_pServer);
	static bool EraseClient(CUTClient *pClient);

	const wchar_t *GetRemoteIP();
	bool IsLocalIP();

	virtual void OnPrompt(char *cString);//called when the prompt has been received (command process end).
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnected(int nErrorCode);
	virtual bool OnReceived(const wchar_t *wcMsg);//if the answered has not been processed then the user can process it, this function returns true if the command has been processed, false otherwise.
	virtual bool OnReceivedLine(char *cMsg, int size);
	void ResetCmdPrompt();
	bool IsCmdPrompt();

	int mySend(const void *buf, int size, int flags = 0);
	bool iSendAndWaitData(char *cmd, DWORD dwTimeOutStepMs, int iTimeOutCount, bool &bTimeOut, int iCheckSize, structCheckReturnedValues *checkReturnedValues, wchar_t *wcStringOut = NULL, int iStringSize = 0);
	void UpdateRemoteDriverIP(wchar_t *wcRemoteServerIP, int iPort);
	int64_t iGetData(int iIndex);
	int GetCountIn();
	const wchar_t *sGetData();

	bool IsRemoteServiceEnabled();

	static bool IsTraceClientIn();
	static bool IsTraceClientOut();
	static void EnableTraceClientIn(bool bEnable);
	static void EnableTraceClientOut(bool bEnable);
public:
private:

public:
};

#ifndef OEMPA_SERVICE
typedef void (WINAPI *TypeDeviceManagerUpdate)(int iDevice, CHWDeviceOEMPA *pHWDeviceOEMPA);
class ROUTE_DEVICE_API _CDeviceManager
{
private:
	ULONGLONG m_ullPrivateMemory[3332];
public:
	_CDeviceManager();

};
class ROUTE_DEVICE_API CDeviceManager : public _CDeviceManager
{
public:
	CDeviceManager();
	~CDeviceManager();

	double GetThroughputStream(int iDevice);
	double GetThroughputAscan(int iDevice);
	double GetThroughputCscan(int iDevice);
	double GetThroughputIO(int iDevice);
	bool TryEnter();
	void Enter();
	void Leave();
	void UpdateStart();
	void UpdateStop(DWORD dwTime);

	void RegisterDeviceTickCount(CHWDeviceOEMPA *pHWDeviceOEMPA);
	void UnregisterDeviceTickCount(CHWDeviceOEMPA *pHWDeviceOEMPA);
	uint64_t GetDeviceTickCount(int iDeviceId);

	bool DisableAllPulser();

	static void SetUpdateStart(TypeDeviceManagerUpdate func);
	static void SetUpdateStop(TypeDeviceManagerUpdate func);

	bool IsThreadRunning() const;
	DWORD GetThreadId() const;

	static DWORD GetTimerMs();//millisecond.
	static void SetTimerMs(DWORD dwTimer);//minimum 10 ms.
	static CDeviceManager *GetDeviceManager();
	bool Start();
	bool Stop();
public:
private:

public:
};
#else //OEMPA_SERVICE
class _CDeviceManager
{
public:
	int x;
};
class CDeviceManager
{
public:
	int x;
};
#endif //OEMPA_SERVICE

class ROUTE_DEVICE_API _CFtpClientData
{
private:
	ULONGLONG m_ullPrivateMemory[331];
public:
	_CFtpClientData();

};
class ROUTE_DEVICE_API CFtpClientData : public _CFtpClientData, public CUTServer
{
public:
	CFtpClientData();
	~CFtpClientData();

	bool FileOpen(wchar_t *wcFileName, bool bWrite);
	bool FileClose();
	bool IsFileOpened();
	void EnableConsole(bool bEnable);
	void EnableFile(bool bEnable);
	bool IsConsoleEnabled();
	bool IsFileEnabled();
	bool FileSend(CFtpClientCmd *manager);

	virtual void OnReceive(int nErrorCode);
public:
private:

public:
};

class ROUTE_DEVICE_API _CFtpClientCmd
{
private:
	ULONGLONG m_ullPrivateMemory[2054];
public:
	_CFtpClientCmd(CUTServer *pServer);

};
class ROUTE_DEVICE_API CFtpClientCmd : public _CFtpClientCmd, public CUTServer
{
public:
	CFtpClientCmd(CUTServer *pServer);
	~CFtpClientCmd();

	virtual void OnReceive(int nErrorCode);
	void EnableStandby(bool bEnable);
	bool IsStandbyEnabled();
	int Send(char* lpBuf, int nBufLen);
	int _Send(char* lpBuf, int nBufLen);
	void SetSleepMs(int iSleep);
	int GetSleepMs();
	int Getch(char *buffer, int iBufferSize);
	void ResetOpeningDataConnection();
	void ResetTransferComplete();
	void ResetFileReceiveComplete();
	void ResetDataSocket();
	int IsDataPortValid();
	bool IsLoggedIn();
	bool IsOpeningDataConnection();
	bool IsTransferComplete();
	bool IsFileReceiveComplete();
	bool ConnectSocketData();
	bool DisconnectSocketData();
	void Abort();

	bool FileOpen(wchar_t *wcFileName, bool bWrite);
	bool FileClose();
	bool IsFileOpened();
	void EnableConsole(bool bEnable);
	void EnableFile(bool bEnable);
	bool IsConsoleEnabled();
	bool IsFileEnabled();
	bool FileSend();

	CUTServer *GetDriverServer();
public:
private:

public:
};

class ROUTE_DEVICE_API_ALIGN _CUTMemory
{
private:
	ULONGLONG m_ullPrivateMemory[72];
public:
	_CUTMemory();

};

class ROUTE_DEVICE_API CUTMemory : public _CUTMemory
{
public:
	CUTMemory();
	~CUTMemory();

	void SetSharedMemoryName(wchar_t *wcName);
	bool IsSharedMemory();
	int64_t GetSharedMemorySize();
	int64_t GetSharedMemorySize(int64_t iData);
	bool OpenSharedMemory(int64_t i64SharedMemorySize);
	bool CreateSharedMemory(int64_t i64SharedMemorySize);
	bool DesallocSharedMemory();

	bool SetSharedData(int iByteOffset, void *pData, int iDataSize);
	bool GetSharedData(int iByteOffset, void *pData, int iDataSize);
	bool SetSharedData(int iByteOffset, DWORD dwData);
	DWORD GetSharedData(int iByteOffset);
	const DWORD *pGetSharedData(int iByteOffset) const;
private:
};
