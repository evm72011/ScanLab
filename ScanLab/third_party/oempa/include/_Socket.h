

#pragma once

#if !defined(_COM_DECL_)
#ifdef _UTSOCK_EXPORT_
#ifdef _WIN32
	#define _COM_DECL_ __declspec(dllexport)
#elif defined __linux__
	#define _COM_DECL_ __attribute__((visibility ("default")))
#endif // __linux__
#else //_UTSOCK_EXPORT_

#ifdef _WIN32
	#define _COM_DECL_ __declspec(dllimport)
#elif defined __linux__
	#define _COM_DECL_
#endif // __linux__
#endif //_UTSOCK_EXPORT_

#endif //_COM_DECL_


#ifdef _WIN32
#include <winsock2.h>
#endif //_WIN32
#ifdef __linux__
#include <netinet/in.h>
#endif // __linux__

#include <list>

#define FW_STREAM_MAX_SIZE_MASK	0x00ffffff

class CTListeningSocket;
_COM_DECL_ bool GetMultiByteToWideChar(const char* cbInput, myCString &strOutput);
_COM_DECL_ wchar_t* GetMultiByteToWideChar(char* cbInput = NULL);

const unsigned short TIMEOUT_RECEIVE_PROCESSING = 5000;
const unsigned short EVENT_TIMEOUT = 200;

class CMyList;
class CSocket_;
typedef void (*pTypeDumpSocket)(int iType, int iIndex, LPVOID pParam, CSocket_ *pSocket);

enum enumSendBlockingMode
{
	eNonBlocking = 0,
	eBlocking = 1,
	eNonBlockingList = 2,
	eNonBlockingLost = 3
};

class CWinThread;
class CSocketServer;
#ifdef DEBUG_THREAD_CLASS
class CThreadPerf;
//class X_COM_DECL_ _CThreadPerf
class _CThreadPerf
{
public:
	_CThreadPerf();

};
//class _COM_DECL_ CThreadPerf : public _CThreadPerf
class CThreadPerf : public _CThreadPerf
{
public:
	CThreadPerf();
	~CThreadPerf();
	CThreadPerf& operator=(const CThreadPerf& p);

	void Init();
	bool Update(int index);
	double GetAllAverage();
	double GetAcqAverage();
	double GetAcqPeak1();
	double GetAcqPeak8();
	void Close();

};
#endif //DEBUG_THREAD_CLASS

class _COM_DECL_ CSocket_
{
	friend class CSocketServer;

public:
	CSocket_(bool bTCP);
	virtual ~CSocket_();
	static BOOL Init_sockets();
	static void Clean_sockets();
	static void PreClean_sockets(DWORD dwTimeOutMs);
	static void GetFirstConnectionTime(LARGE_INTEGER &llLocalFrequency,LARGE_INTEGER &llTimeStampStart);
	bool IsTCP();
	bool IsUDP();

	BOOL Create(UINT nSocketPort = 0, int iMaxListenConnexion = 0, bool bReuseAddr = false, const char *bindIP = NULL);
	BOOL ConnectTCP(const wchar_t* lpszHostAddress, UINT nHostPort, bool bPing, bool bDisplayError);
	BOOL ConnectTCP(const char* lpszHostAddress, UINT nHostPort, bool bPing, bool bDisplayError);
	BOOL ConnectUDP(const wchar_t* lpszAddress, UINT nPort, UINT nPortHost, bool bDisplayError);
	BOOL GetPeerName(myCString& rPeerAddress, UINT& rPeerPort);
	BOOL GetPeerName(int iPeerAddressSize, char* rPeerAddress, UINT& rPeerPort);
	BOOL GetSockName(myCString& rPeerAddress, UINT& rPeerPort);
	BOOL GetSockName(int iPeerAddressSize, char* rPeerAddress, UINT& rPeerPort);
	BOOL GetSockOpt(int nOptionName, void* lpOptionValue = NULL, int* lpOptionLen = NULL, int nLevel = SOL_SOCKET);
	BOOL SetSockOpt(int nOptionName, const void* lpOptionValue, int nOptionLen, int nLevel = SOL_SOCKET);
	BOOL Accept(CSocketServer* rSocket = NULL);
	BOOL IOCtl(LONG lCommand, DWORD* lpArgument = NULL);
	int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	int ReceiveWSA(LPWSABUF lpBuf, DWORD* nbRecv, DWORD nFlags = 0, int bufCnt = 1);
	int Send(const void* lpBuf, int nBufLen, int nFlags, int* piLastError);
	int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	int send(const void* lpBuf, int nBufLen, int nFlags = 0);
	int64_t Send64(const void* lpBuf, int64_t nBufLen, int nFlags=0, int* piLastError=NULL);
	int SendStreamWithTimeStamp(LARGE_INTEGER &llTimeStamp, const void* pStreamData = NULL, int iStreamSize = 0);
	bool IsSent();
	BOOL SetBlockingMode(bool bBlocking);
	BOOL IsValid();
	BOOL Listen(int iMaxConnexion);
	void Close();
	bool IsClosed();
	bool IsClosePending()const ;
	bool IsOnClosePending() const;
	bool IsConnected() const;
	bool IsListening() const;
	int GetListenPort() const;//usefull for socket on the same computer to know the base port.
	int GetOnSendStatus(LARGE_INTEGER &llSendDelay);
	void ResetOnSendStatus();
	bool SetSendBlockingMode(enumSendBlockingMode eMode, DWORD dwSleepTimeMs = 0);
	void GetSendBlockingMode(enumSendBlockingMode &eMode, DWORD &dwSleepTimeMs);
	void GetSendBlockingMode(DWORD &dwSentSumMax, DWORD &dwSentCountMax);
	void ResetSendBlockingMode();
	void GetSendBlockingModeCurrent(DWORD &dwSendCurrentSumMax, DWORD &dwSendCurrentCountMax);
	void SetThreadPriority(int nPriority);
	int GetThreadPriority();
	DWORD GetThreadId();
	HANDLE GetThread();
	static void sSetSendSleepTime(DWORD dwSleepTimeMs);
	static DWORD sGetSendSleepTime();
	static void sSetSendSleepCountMax(DWORD dwSleepCountMaxMs);
	static DWORD sGetSendSleepCountMax();

	SOCKET m_hSocket;
	bool m_bTCP;
	bool m_bAutoDelete;
	bool m_bDestructor;
	LONGLONG m_ullCounterRecv;
	LONGLONG m_llFD_WRITE;
	ULONGLONG m_ullCounterSendWSA;
	ULONGLONG m_ullCounterSendWSASize;
	ULONGLONG m_ullCounterSendWSASent;
	ULONGLONG m_ullCounterSendWSASleep;
	LARGE_INTEGER m_liCounterSendWSAError;
	ULONGLONG m_ullCounterSendWSAWouldBlocked;
	char m_cSocketClassName[64];
	char m_cSocketName[64];
	char m_cMAC[32];
	UINT m_uiEvent;
#ifdef DEBUG_THREAD_CLASS
	CThreadPerf m_ThreadPerf;
#endif //DEBUG_THREAD_CLASS

	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual bool IsSend64(const void* lpBuf, int64_t nBufLen, int nFlags, int64_t &iRet);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnConnected(int nErrorCode);
	virtual void OnListened(int nErrorCode);
	virtual void OnTimeOut();
	virtual bool OnThreadExit();//It is forbidden to delete the socket from inside this function, just return true to auto-delete the object after returning this function.
	virtual void CommunicationReport(wchar_t* string = NULL);
	virtual void CommunicationReport(char* string);

	//error reporting
	void SetReportFileError(wchar_t* cbFileName = NULL);
	void SetReportFileError(char* cbFileName = NULL);
	const wchar_t *GetReportFileError() const;
	void CommunicationReport(myCString *string = NULL);
	void CommunicationReport(int iCode, int* piError = NULL);
	void ReportLastError(int* piError = NULL);
	void ReportLastError(int& iError, myCString &string);
	int GetReceiverBufferSize();
	bool SetReceiverBufferSize(int iBufferSize);
	int GetTransmitterBufferSize();
	bool SetTransmitterBufferSize(int iBufferSize);
	bool SetTcpNoDelay(bool bEnable);
	bool GetTcpNoDelay();

	bool CloseSocket();
	bool StopSocket();
	static int sDumpList(int iType, LPVOID pParam, pTypeDumpSocket func);
	bool EnableReuseAddr(bool bEnable);
	bool IsReuseAddrEnabled();
	bool SetLinger(bool bEnable, struct linger *pLinger);
	bool GetLinger(struct linger *pLinger);
	void EnableAutoDelete(bool bEnable);
protected:
	bool m_bIsConnected;
private:
	BOOL Bind(const int port, const char *ip);
	BOOL ShutDown(int nHow = SD_SEND);
	static DWORD WINAPI ThreadSocket(LPVOID pParam);
	bool StartSocket(UINT uiEvent, UINT nPriority);
	bool GetEvent(WSANETWORKEVENTS &netEvents);

	HANDLE m_hThread;//protected by "m_CriticalSectionStop"
	DWORD m_nThreadID;
	WSAEVENT m_wsaEvent;//protected by "m_CriticalSection"
	DWORD m_dwThreadExit;//protected by "m_CriticalSection"
	myCString m_strReportErrorFileName;
	CRITICAL_SECTION m_TraceLogOutCriticalSection;
	CRITICAL_SECTION m_CriticalSection, m_CriticalSectionStop;
	CRITICAL_SECTION m_CriticalSectionSend;
	int m_iReceiverBufferSize;
	BOOL m_bReceiverKeepAlive;
	int m_iListenPort;//usefull for socket on the same computer to know the base port.
	bool m_bOnClosePending;
	bool m_bClosePending;
	bool m_bListen;
	int m_iOnSendError;
	enumSendBlockingMode m_eSendBlockingMode;
	DWORD m_dwSendSleepTimeMs;//m_dwSendBlockingSleepTimeMs
	LARGE_INTEGER m_llSendDelay;
	CMyList* m_pSendWaitingDataList;
	CMyList* m_pSendWaitingSizeList;
	DWORD m_dwSentSumMax;
	DWORD m_dwSentCountMax;
	sockaddr_in m_UDPRecv;
	static DWORD g_dwSendSleepTimeMs;
	static int g_iSendSleepCountMax;
#pragma warning( disable : 4251 )
	static std::list<CSocket_ *> m_ListSocket;
#pragma warning( default : 4251 )
};

