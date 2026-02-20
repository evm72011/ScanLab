
#pragma once

#if !defined(_COM_DECL_)
#ifdef _UTSOCK_EXPORT_
#ifdef _WIN32
	#define _COM_DECL_ __declspec(dllexport)
#elif defined __linux__
	#define _COM_DECL_	__attribute__((visibility ("default")))
#endif // __linux__
#else //_UTSOCK_EXPORT_
#ifdef _WIN32
	#define _COM_DECL_ __declspec(dllimport)
#elif defined __linux__
	#define _COM_DECL_
#endif // __linux__
#endif //_UTSOCK_EXPORT_

#endif //_COM_DECL_

#ifndef WITHOUT_USB3	// Conditionnal compilation without USB3 and all dependencies it adds.
#define _USB3_
#if defined(_USB3_)
#define _USB3_DECL_
#endif
#endif // WITHOUT_USB3




class _COM_DECL_ CUTUsb3Device
{
public:
	int GetStreamSizeEx() const;
	DWORD GetVersion() const;
	bool IsConnected() const;
	void Reset();
	void EnableEmulator(double dTimeSlot);
	bool GetSerialNumber(int iSize,char *cSerial);
	virtual bool GetSerialNumber(int iSize,wchar_t *wcSerial);
	bool GetFlashSerialNumber(int iSize,char *cSerial);
	virtual bool GetFlashSerialNumber(int iSize,wchar_t *wcSerial);
public:
	virtual void OnLostCountUSB3(int iLostCount)=0;
	virtual void OnUTStream(char* data = NULL, int size = 0)=0;
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnConnected(int nErrorCode);
	virtual void CommunicationReport(wchar_t* string)=0;
	virtual void CommunicationReport(char* string)=0;
private:
#ifdef _USB3_DECL_
#else
#endif

public:
};


