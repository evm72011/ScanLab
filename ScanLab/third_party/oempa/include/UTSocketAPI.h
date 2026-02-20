
#pragma once

class CUTSocketAPI;


class _COM_DECL_ _CUTSocketAPI
{
private:
	ULONGLONG m_ullPrivateMemory[153];
public:
	_CUTSocketAPI(bool bEnableListen, int iListenPort, CUTSocketAPI *pSocketAPI);

};

class _COM_DECL_ CUTSocketAPI : public _CUTSocketAPI
{
public:
	CUTSocketAPI(bool bEnableListen, int iListenPort);

	//listen port (if enabled)
	bool StartListen();
	void CloseListen();
	int SetListenPort(int iPort);
	int GetListenPort();

	virtual void OnListenClose(int nErrorCode);
	virtual void OnListened(int nErrorCode);
	virtual void OnAccept(int nErrorCode);

	//socket
	bool Connect(wchar_t* lpszHostAddress, UINT nHostPort, bool bPing = false, bool bDisplayError = true);
	bool IsConnected();
	void Close();
	int Send(const void* lpBuf, int nBufLen, int nFlags = 0);

	virtual void OnUTStream(char* data, int size, bool copy = true);
	virtual void OnConnect(int nErrorCode);
	virtual void OnConnected(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	int GetReceiverBufferSize();
	bool SetReceiverBufferSize(int iBufferSize);
	int GetTransmitterBufferSize();
	bool SetTransmitterBufferSize(int iBufferSize);

	//all
	virtual void CommunicationReport(wchar_t* string = NULL);
	virtual void CommunicationReport(char* string = NULL);
};

