
#pragma once

#ifdef DRIVER_OEMPA_API
#include "UTKernelStream.h"
#else //DRIVER_OEMPA_API
#include "UTKernelStream.h"
#endif //DRIVER_OEMPA_API



#ifdef FPGA_MANAGER_EXPORTS

#ifdef _WIN32
#define FPGA_MANAGER_API __declspec(dllexport)
#define FPGA_MANAGER_API_ALIGN __declspec(dllexport) __declspec(align(8))
#elif defined __linux__
#define FPGA_MANAGER_API __attribute__((visibility ("default")))
#define FPGA_MANAGER_API_ALIGN __attribute__((visibility ("default"))) __attribute__((aligned(8)))
#endif // _WIN32 / __linux__

#else //FPGA_MANAGER_EXPORTS

#ifdef _WIN32
#define FPGA_MANAGER_API __declspec(dllimport)
#define FPGA_MANAGER_API_ALIGN __declspec(dllimport) __declspec(align(8))
#elif defined __linux__
#define FPGA_MANAGER_API
#define FPGA_MANAGER_API_ALIGN __attribute__((aligned(8)))
#endif // _WIN32 / __linux__

#ifdef _WIN32
#define EN_RESULT		int
#define ETransferStatus	int
#define en_uint32		unsigned int
#define en_byte			unsigned char    
#endif // _WIN32

struct structTransferInfo;
class CTransferApi;

#endif //FPGA_MANAGER_EXPORTS

enum enumOEMPA2AcquisitionMode {eRealTime,ePostProcessing};

class CFpgaManager;
class CSequenceAscanList;
class CAcquisitionFifo;

typedef void* (*pCallbackFpgaManagerStream)(int iSubDevIndex, void *pCallbackAcquisitionInputParameter, char *data, int size, int iNextStreamSize);
typedef void *(*pTypeGetFifoBufferPtr)(CAcquisitionFifo *pFifo);

class FPGA_MANAGER_API_ALIGN CFpgaManagerSimulator
{
public:
	static bool CreateTestStream(bool bFMC, int &iByteSize);
	static BYTE* GetStreamSimulator(int &iByteCount);
private:
	static bool UpdateTestStreamFMC();
	static bool UpdateTestStreamPA();
	static DWORD g_dwTestStream_0x0001[1526];
	static char* g_TestStream;
	static int g_iTestStreamSize;
	static bool g_bTestFMC;
};
typedef struct structPerformanceCounters
{
	int iCallbackPrevious;
	double dCallbackDeltaTime;
	int iCallbackCurrent;
	int iCallbackCount;
	int iFifoStreamIndex;
	double dTimeRequested;
	DWORD dwSizeRequested;
	double dTimeReceived;
	DWORD dwSizeReceived;
	DWORD dwSizeCurrent;
	DWORD dwSizeNext;
	DWORD dwSizeTotal;
	DWORD dwStreamFrameId;
	DWORD dwPacketFrameId;
	DWORD dwMaxTemperature;
	DWORD error;
	LONG lEncoder1;
	DWORD dwUnexpectedData;
	ETransferStatus eStatus;
	EN_RESULT eError;
}structPerformanceCounters;
typedef enum enumErrorCounters {
	eConnection,
	eAcquisition,
	eStreamError,
	eStreamLoss,
	eUnexpectedData,
	eFrameLoss
}enumErrorCounters;
typedef struct structErrorCounters
{
	double dTimeStamp;
	enumErrorCounters error;
	UINT64 ui64Value;
}structErrorCounters;

class FPGA_MANAGER_API_ALIGN _CFpgaManager
{
private:
	ULONGLONG m_ullPrivateMemory[283];
friend class CFpgaManager;
public:
	_CFpgaManager(const wchar_t *wcFpgaManagerPath, CFpgaManager *pFpgaManager, void *pDevCom, int iTransferCountMax, bool bFrame, bool bEthernet, bool bMemoryMap, bool bEmulator, bool bPostponeEmulator);
	~_CFpgaManager();
protected:

};

class FPGA_MANAGER_API_ALIGN CFpgaManager : public _CFpgaManager
{
friend class CFpgaManagerPCIe;
friend class CFpgaManagerUDP;
	enum enumCheckStreamFormat{ eOk, eBadStart, eBadStop};
public:
	CFpgaManager(const wchar_t *wcFpgaManagerPath, void *pDevCom, int iTransferCountMax, bool bFrame, bool bEthernet, bool bMemoryMap, bool bEmulator, bool bPostponeEmulator);
	~CFpgaManager();
	const wchar_t* GetFpgaManagerVersion();

	bool WriteFifoData(pCallbackWriteAcquisitionData pWriteData, BYTE *pBuffer, int64_t i64BufferSize, int64_t &i64FileSize);
	bool ReadFifoData(pCallbackReadAcquisitionData pReadData, BYTE *pBuffer, int64_t i64BufferSize, int64_t &i64FileSize);

	void EnableDisplayTrace(bool bEnable);
	void EnableFWNullStreamACK(bool bEnable);
	bool IsDisplayTraceEnabled();
	int GetSlaveCount();
	ULONGLONG GetStreamDataSize() const;
	int GetTemperature() const;
	static void SetOnLineTimeStep(double dValue);//unit second.
	static double GetOnLineTimeStep();
	static void SetOnLineSequenceCount(int iValue);
	static int GetOnLineSequenceCount();
	ULONGLONG GetStreamDataSize(int iSubDevIndex) const;
	int GetTemperature(int iSubDevIndex) const;
	void EnableFrame(bool bEnable);
	bool IsFrameEnabled() const;
	bool IsConnected() const;
	bool SetTransferCountMax(int iCount);
	int GetTransferCountMax() const;
	bool IsDebugWriteEnabled() const;//1.2.0.1d
	bool EnableDebugWrite(bool bEnable);//1.2.0.1d
	bool IsEmulator() const;
public:
	virtual void __stdcall callback(const EN_RESULT error, CTransferApi* transfer_p)=0;
	virtual bool WriteTransferCount(int iTransferCount)=0;
	virtual bool Connect(bool bNotify);
	virtual bool Disconnect();
	virtual bool Desalloc();
	virtual bool EnableAcquisitionHW(bool bEnable);
	virtual bool PrepareAcquisitionEnd(bool bEnable);
	virtual bool IsReplayEnabled();
	virtual void SetNext(CFpgaManager *pSlave);
	virtual void SetMaster(CFpgaManager *pMaster) = 0;
	virtual bool EnableAcquisition(bool bEnable);
	virtual int Dump();
#ifdef OEMPA2_MASTER_SLAVE
	virtual bool GetFWSlaveAddress(int iSlaveIndex, int iSizeMax, wchar_t *pIPAddress);
#endif //OEMPA2_MASTER_SLAVE
protected:
	virtual bool EnablePulser(bool bEnable);
	virtual bool EnableReplay(bool bEnable);
	virtual void CheckAddressRange(bool bWrite,DWORD dwAddress,int iCount,bool &bBurst)=0;
	virtual DWORD ConvertAddressToDevice(DWORD dwAddress)=0;
	virtual DWORD ConvertAddressFromDevice(DWORD dwAddress)=0;
	virtual bool Reset();
	virtual bool CheckStream(structTransferInfo *pTransfer, char *pBuffer, int iBufferSize, int &iNextStreamSize);
	virtual int ReadFirstStreamSize()=0;
	virtual EN_RESULT RunStreamReception(int iCurrentStreamSize);
	virtual EN_RESULT ReceiveStream(int iCallbackPrevious, int iCallbackCurrent, char *pBuffer, int iStreamSize, bool &bStopFifo)=0;
	virtual bool CheckStreamError(DWORD dwError);
	virtual void Dispatch(char *pBuffer, int iBufferSize)=0;
	virtual bool ProcessStreamOnLine();
	virtual bool ProcessStreamOffLine(bool bAcquisitionEnd);

public:
public:
	const wchar_t *GetDumpFile() const;
	void DumpFlush();
	bool DumpStream(bool bHexadecimal, int iSubDevId, const CStream_0x0002* pStream, int iStreamSize=0);//iStreamSize is required if the stream is not consistant.
	bool DumpAscan(bool bHexadecimal, int iSubDevId, int FrameId, int64_t llSequence, const CSubStreamAscan_0x0203* pAscan);
	bool DumpErrors();
	virtual bool Write(DWORD dwAddress, DWORD dwData);
	virtual bool WriteCount(int iCount, DWORD dwAddress, DWORD *pdwData);
	virtual bool Read(int iCount, DWORD dwAddress, DWORD *pdwData);
	bool IsAcquisitionHWEnabled();
	bool OneShotWPR();
};

class FPGA_MANAGER_API_ALIGN _CFpgaManagerPCIe
{
private:
	ULONGLONG m_ullPrivateMemory[9570349];
friend class CFpgaManagerPCIe;
public:
	_CFpgaManagerPCIe();
protected:

};

class FPGA_MANAGER_API_ALIGN CFpgaManagerPCIe : public CFpgaManager, public _CFpgaManagerPCIe
{
friend class CSequenceAscanList;
public:
	CFpgaManagerPCIe(const wchar_t *wcFpgaManagerPath, void *pDevCom, bool bEmulator=false);
	~CFpgaManagerPCIe();

	bool WriteFifoData(pCallbackWriteAcquisitionData pWriteData, BYTE *pBuffer, int64_t i64BufferSize, int64_t &i64FileSize);
	bool ReadFifoData(pCallbackReadAcquisitionData pReadData, BYTE *pBuffer, int64_t i64BufferSize, int64_t &i64FileSize);

	bool SetMode(enumOEMPA2AcquisitionMode eMode);
	enumOEMPA2AcquisitionMode GetMode();
	void SetCallbackAcquisitionInputParameter(void *pCallbackInputParameter);
	bool RegisterCallbackAcquisitionStream(pCallbackFpgaManagerStream func);
	void EnableOnLineDisplay(bool bEnable);
	bool IsOnLineDisplayEnabled();
	uint64_t GetOffLineAscanListCount();
	uint64_t GetOffLineAscanListIndex();
	void SetOffLineAscanListCount(uint64_t uiOffLineAscanListCount);
	void SetOffLineAscanListIndex(uint64_t uiOffLineAscanListIndex);
	virtual bool EnableAcquisitionHW(bool bEnable);
	virtual bool IsReplayEnabled();
	bool WriteStreamSimulator(int iByteCount, BYTE *pStream);
	bool EnableSimulator(bool bEnable);

public:
#ifdef OEMPA2_MASTER_SLAVE
#endif //OEMPA2_MASTER_SLAVE
	virtual void SetNext(CFpgaManager *pSlave);
	virtual void SetMaster(CFpgaManager *pMaster);
	virtual bool Connect();
	virtual bool PrepareAcquisitionEnd(bool bEnable);
	virtual bool WriteTransferCount(int iTransferCount);
	virtual void __stdcall callback(const EN_RESULT error, CTransferApi* transfer_p);
	virtual int Dump(bool bHexadecimal, bool bSubStreamChained);
#ifdef OEMPA2_MASTER_SLAVE
	virtual bool GetFWSlaveAddress(int iSlaveIndex, int iSizeMax, wchar_t *wcAddress);
#endif //OEMPA2_MASTER_SLAVE
private:
	virtual bool EnableReplay(bool bEnable);
	virtual int ReadFirstStreamSize();
	virtual bool EnableAcquisition(bool bEnable);
	virtual bool Reset();
	virtual void CheckAddressRange(bool bWrite,DWORD dwAddress,int iCount,bool &bBurst);
	virtual DWORD ConvertAddressToDevice(DWORD dwAddress);
	virtual DWORD ConvertAddressFromDevice(DWORD dwAddress);
	virtual EN_RESULT RunStreamReception(int iCurrentStreamSize);
	virtual EN_RESULT ReceiveStream(int iCallbackPrevious, int iCallbackCurrent, char *pBuffer, int iStreamSize, bool &bStopFifo);
	virtual bool CheckStreamError(DWORD dwError);
	virtual bool ProcessStreamOnLine();
	virtual bool ProcessStreamOffLine(bool bAcquisitionEnd);
	virtual void Dispatch(char *pBuffer, int iBufferSize);
	virtual bool CheckStream(structTransferInfo *pTransfer, char *pBuffer, int iBufferSize, int &iNextStreamSize);

public:
public:
	int64_t GetSequenceCount(int64_t &llSequenceMin, int64_t &llSequenceMax);
	bool GetSequenceAscanList(int64_t llSequence, bool &bCheckSequenceError, CSequenceAscanList &sequenceAscanList);

	const CStream_0x0002 *GetStreamByFrame(int iSubDevId, int iFrame);
	const CStream_0x0002 *GetStreamFifoIndex(int iSubDevId, int iFifoStreamIndex);
	bool DumpAscanList(int iSubDevId);
	bool DumpAllHexadecimal(int iSubDevId);
	bool DumpPerformance(int iSubDevId);
};

class FPGA_MANAGER_API_ALIGN _CFpgaManagerUDP
{
private:
	ULONGLONG m_ullPrivateMemory[1176];
friend class CFpgaManagerUDP;
public:
	_CFpgaManagerUDP();
protected:

};

class FPGA_MANAGER_API_ALIGN CFpgaManagerUDP : public CFpgaManager, public _CFpgaManagerUDP
{
public:
	CFpgaManagerUDP(const wchar_t *wcFpgaManagerPath, void *pDevCom);//, bool bEmulator);
	~CFpgaManagerUDP();

	virtual bool Connect();
	virtual bool EnableAcquisitionHW(bool bEnable);
	void SetFirstStreamSize(int iFirstStreamSize);
	int GetFirstStreamSize();

	virtual bool WriteTransferCount(int iTransferCount);
	virtual void __stdcall callback(const EN_RESULT error, CTransferApi* transfer_p);
	virtual int Dump();
	const CStream_0x0002 *GetStreamByFrame(int iFrameId);
	const CStream_0x0002 *GetStreamFifoIndex(int iFifoStreamIndex, int &iStreamSize);
	bool DumpPerformance();
	bool DumpAscanList();
	bool DumpAllHexadecimal();

	int GetUDPMaxUniScpPacketSize(bool bStream);
	int GetUDPMaxUniScpPendingPackets(bool bStream);
	int GetUDPUniScpUpPktRate(bool bStream);
	int GetUDPOperationMode(bool bStream);
	int GetUDPUniScpKeepAliveTimeout(bool bStream);
	int GetUDPMaxOpenMmTransfers(bool bStream);
	int GetUDPMaxMmCommandSize(bool bStream);
	int GetUDPMaxMmResponseSize(bool bStream);
	void SetUDPMaxUniScpPacketSize(bool bStream, int iValue);
	void SetUDPMaxUniScpPendingPackets(bool bStream, int iValue);
	void SetUDPUniScpUpPktRate(bool bStream, int iValue);
	void SetUDPOperationMode(bool bStream, int iValue);
	void SetUDPUniScpKeepAliveTimeout(bool bStream, int iValue);
	void SetUDPMaxOpenMmTransfers(bool bStream, int iValue);
	void SetUDPMaxMmCommandSize(bool bStream, int iValue);
	void SetUDPMaxMmResponseSize(bool bStream, int iValue);
	bool ResetFW();
	void EnableFlushTimer(bool bEnable);
	virtual bool Disconnect();
public:
	virtual void SetMaster(CFpgaManager *pMaster);
	virtual bool PrepareAcquisitionEnd(bool bEnable);
private:
#ifdef POUR_MEMOIRE
#endif //POUR_MEMOIRE
	virtual bool EnablePulser(bool bEnable);
	virtual bool CheckStream(structTransferInfo *pTransfer, char *pBuffer, int iBufferSize, int &iNextStreamSize);
	virtual int ReadFirstStreamSize();
	virtual void CheckAddressRange(bool bWrite,DWORD dwAddress,int iCount,bool &bBurst);
	virtual DWORD ConvertAddressToDevice(DWORD dwAddress);
	virtual DWORD ConvertAddressFromDevice(DWORD dwAddress);
	virtual EN_RESULT RunStreamReception(int iCurrentStreamSize);
	virtual EN_RESULT ReceiveStream(int iCallbackPrevious, int iCallbackCurrent, char *pBuffer, int iStreamSize, bool &bStopFifo);
	virtual void Dispatch(char *pBuffer, int iBufferSize);
	virtual bool ProcessStreamOffLine(bool bAcquisitionEnd);

public:
};



class FPGA_MANAGER_API_ALIGN _CSequenceAscanList
{
private:
	ULONGLONG m_ullPrivateMemory[75];
public:
	_CSequenceAscanList(CFpgaManagerPCIe *pThis);
	~_CSequenceAscanList();


};

class FPGA_MANAGER_API_ALIGN CSequenceAscanList : public _CSequenceAscanList
{
//Functions defined with the keyword with const means that the internal index
//is not modified internally it means that a copy of this object is used if required).
//For exampe "GetAscanList(...) const" means you can still call "NextAscan" or "NextSequence"
//as if "GetAscanList" have not been called.
friend class CFpgaManagerPCIe;
public:
	CSequenceAscanList(CFpgaManagerPCIe *pThis);
	CSequenceAscanList& operator=(const CSequenceAscanList& a);

//Before calling any of the API functions (real time or off line),
//you have first to call the function "SetSequenceNumber":
	bool SetSequenceNumber(int64_t &llSequence);//If the something is wrong with the requested sequence then the "llSequence" can be modified with the greater available sequence.
												//If the acquisition is enabled, dont handle the minimum sequence ("llSequenceMin" returned by "GetSequenceCount")
												//because this sequence will be overwritten soon by a new coming from the HW.
	int64_t GetSequenceNumber() const;
	int NextSequence(); //Returns 1 if the next sequence number is available (if something is wrong with the next sequence number then it can return 2 if the next next is right).
						//Returns 0 if no new sequence is available yet.
	//You can get the available sequence range with the following function:
	int64_t GetSequenceCount(int64_t &llSequenceMin, int64_t &llSequenceMax) const;

//Real time API functions.
	const CSubStreamAscan_0x0203* GetAscan() const;//current ascan (for the specified sequence).
	const CStream_0x0002* GetStream() const;//current stream (the stream inside which the ascan has been sent by the HW).
	bool NextAscan();//To browse all ascan inside the sequence (first cycle 0 element 0, cycle 0 element 1, cycle 0 element N, cycle 1 element 0 etc...). Return false if no more data.
	bool ReInit();//to browse the same whole sequence one more time from the beginning.
	bool _Init();//to browse the same whole sequence one more time from the beginning.
	int GetAscanList(int iAscanOutSize, const CSubStreamAscan_0x0203 **apAscanOut, int *aiSubDeviceIdOut) const;//return the ascan count and the list of the ascans.
	int GetStreamList(int iStreamOutSize, const CStream_0x0002 **apStreamOut, int *aiSubDeviceIdOut) const;//return the stream count and the list of the streams.
	//special function to process contiguous ascan at once.
	int GetContiguousAscanCount();//get the ascan count that are contiguous (for the same sequence).
	bool NextContiguousAscan();//get next contiguous ascans.
	//<<<< SOON >>>> setting information from acquisition data
	//int GetCycleCount() const;
	//int GetElementCount(int iCycle) const;//-1 if FMC is not enabled.

//Off line API functions (callable after acquisition end).
	const CSubStreamAscan_0x0203* GetAscan(int iElement, int iCycle, const CStream_0x0002** ppStream=NULL) const;
	bool DumpStream(bool bHexadecimal) const;
	bool DumpAscan(bool bHexadecimal) const;
	//setting information from acquisition data.
	int _GetAscanCount() const;
	int _GetStreamCount() const;
	int _GetCycleCount() const;
	int _GetElementCount(int iCycle) const;//-1 if FMC is not enabled.
public:
private:

public:
};
