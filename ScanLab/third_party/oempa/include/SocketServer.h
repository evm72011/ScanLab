
#pragma once

const int g_iPostListCountMax=200;
class _COM_DECL_ CSocketServer : public CSocket_
{
public:
	CSocketServer();
	~CSocketServer();
	int GetPort() const;
	void SetPort(int iPort);
	void _SetPort(int iPort);
	bool StartListening(int iMaxConnexion = 1, bool bReuseAddr = false, const char *bindIP = NULL);
	bool IsListened() const { return m_bListened; };
	bool StopListening();
	virtual void CommunicationReport(wchar_t* string = NULL);
	virtual void CommunicationReport(char* string = NULL);
	virtual void OnAccept(int nErrorCode) = 0;
	virtual void OnListened(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnTimeOut();

	static bool CheckFreePort(unsigned short &usPort);
	static int GetListFreePort(int iSize, unsigned short *ausList);
	static bool IsListenPortListed(int iPort);

private:
	static bool IsListenPortListed(int iPort, bool bDelete);
	int m_iPort;
	bool m_bListened;
	static DWORD m_dwPortListTickCount;
	static int m_iPortListCount;
	static unsigned short m_usPortList[g_iPostListCountMax];
	static int sGetListFreePort(int iSize, unsigned short *ausList);
#pragma warning( disable : 4251 )
	static std::list<int> g_ListPort;
#pragma warning( default : 4251 )
};
