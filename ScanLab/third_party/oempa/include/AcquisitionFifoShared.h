
#pragma once

#define OEMPA2_MASTER_SLAVE

class CAcquisitionFifo;
class CHWDevice;
class CHWDeviceOEMPA;

#ifdef _WIN64

class DRIVER_OEMPA_API_ALIGN _CAcquisitionFifo
{
private:
	ULONGLONG m_ullPrivateMemory[145];
protected:

};
class DRIVER_OEMPA_API_ALIGN CAcquisitionFifo : public _CAcquisitionFifo
{
public:
	CAcquisitionFifo(enumAcquisitionFifo eFifo,bool bDataCopy,CHWDeviceOEMPA *pHWDeviceOEMPA,const wchar_t *pCfgSection);
	~CAcquisitionFifo();

	bool WriteAcquisitionData(pCallbackWriteAcquisitionData pWriteData, BYTE *pBuffer, int64_t i64BufferSize, int64_t &i64FileSize);
	bool ReadAcquisitionData(pCallbackReadAcquisitionData pReadData, BYTE *pBuffer, int64_t i64BufferSize, int64_t &i64FileSize);

	enumAcquisitionFifo GetFifo();//return the type of the fifo.
	bool IsEnabled();//Fifo has been allocated.
	bool Alloc(int iCycleCountMax, int64_t iBufferByteSize);//to enable the fifo, should be called just after the constructor of "CHWDeviceOEMPA1".
		//"iCycleCountMax": maximum cycle count in the fifo (in case of AscanFifo maximum ascan count).
		//"iBufferByteSize": maximum buffer size to store all datas (ascan or cscan or IO).
		//Example:	iCycleCountMax=8    iBufferByteSize=1024+8*4=1056 (ascan header is 8 DWORDs)
		//			you can store 8 ascan of 128 BYTES each, OR 4 ascan of 256 BYTES each.
	bool GetAlloc(int &iDataCountMax, int64_t &iBufferByteSize);//get allocation sizes.
	bool Desalloc();
	bool IsEmpty();
	bool IsAlmostFull();

	//count of data in the fifo.
	int GetCount() const;//count of data in the fifo.
	int GetLost() const;//count of lost data (new input data but the fifo was full so old data has been lost to save new data).
	int64_t GetTotalCount() const;//total data count that have been inputed of the fifo.
	int64_t GetTotalByteCount() const;//total byte count that have been inputed of the fifo.
	void ResetCounters();
	bool RemoveAll();//remove all data, can fail in the case the fifo is accessed at the same time than the priority input thread.
	bool RemoveTail();//remove the oldest data in the fifo, can fail in the case the data is accessed at the same time than the priority input thread.
	bool RemoveItem(int iItem);//remove the specified item and previous ones, -1 means the oldest data in the fifo (same than "RemoveTail"). Can fail in the case the data is accessed at the same time than the priority input thread.
	bool DumpFifoStatus(const wchar_t *wcFileName);//debug purpose.
	bool InitChain(int iSubDevId, CAcquisitionFifo* &pFifoSlave);
	bool InitChain(int iSubDevId, CAcquisitionFifo* pMaster, CAcquisitionFifo* pSlave);

	//Output sub-stream from the fifo. The input parameter is the index of the data in the Fifo. This input parameter "iItem" is retrieved by others functions.
	//"bPeek": false to remove the data from the fifo or true to keep the data inside the fifo.
	//			if "bPeek=true" then the function "RemoveTail" or "RemoveItem" should be called.
	//"iItem": index of the item in the fifo, -1 means the last data.
	bool OutAscan(int iItem,bool bPeek,structAcqInfoEx* &pAcqInfo,CStream_0x0001* &pStreamHeader,CSubStreamAscan_0x0103* &pAscanHeader,void* &pBufferMax,void* &pBufferMin,void* &pBufferSat);
	bool OutAscan2(int iItem,bool bPeek,CStream_0x0002* &pStreamHeader,CSubStreamAscan_0x0203* &pAscanHeader,void* &pBufferMax,void* &pBufferMin,void* &pBufferSat);
	bool OutCscan(int iItem,bool bPeek,structAcqInfoEx* &pAcqInfo,CStream_0x0001* &pStreamHeader,const CSubStreamCscan_0x0X02* &pCscanHeader,const structCscanAmp_0x0102* &pBufferAmp, const structCscanAmpTof_0x0202* &pBufferAmpTof);
	bool OutIO(int iItem,bool bPeek,CStream_0x0001* &pStreamHeader,const CSubStreamIO_0x0101* &pIOHeader);
	bool OutIO(int iItem,bool bPeek,structAcqInfoEx* &pAcqInfo,CStream_0x0001* &pStreamHeader,const CSubStreamIO_0x0101* &pIOHeader);

	//Functions to retrieve index of the sub-stream in the fifo for the specified cycle or the specified sequence/cycle.
	//For the following functions: "iFMCElement" and "iStartItem" should be -1 by default.
	//"iFMCElement" is used only for FMC mode, this is the pulser element, -1 means the parameter is not used.
	//"iStartItem" is the last item from which the search is done, -1 means the parameter is not used.
	//"iCycle" if -1 then the first cycle of the sequence is returned.
	//FIFO means FirstInFirstOut.
	//LIFO means LastInFirstOut.
	int GetFifoItem(LONGLONG sequence, int iCycle, int iFMCElement, int iStartItem);//return -1 if the required sequence/cycle is not found, otherwise the index of the sub-stream.
	int GetFifoItem(int iCycle, int iFMCElement, int iStartItem);//(for the first sequence in the fifo) return -1 if the required cycle is not found, otherwise the index of the sub-stream.
	int GetLifoItem(LONGLONG sequence, int iCycle, int iFMCElement, int iStartItem);//return -1 if the required sequence/cycle is not found, otherwise the index of the sub-stream.
	int GetLifoItem(int iCycle, int iFMCElement, int iStartItem);//(for the last sequence in the fifo) return -1 if the required cycle is not found, otherwise the index of the sub-stream.
	//Functions to retrieve index of any data in the fifo.
	int GetItemLimit(int &iIndexTail, int &iIndexHead);//the return value is the same than "GetCount", output parameter "iIndexTail" is the index of the oldest data in the fifo, output parameter "iIndexHead" is the index of the next input data that will be saved in the fifo.
	void IncrementItemIndex(int &iIndex);//function to increment the index from the Tail (oldest input in the fifo) to the Head (last data in the fifo).
	void DecrementItemIndex(int &iIndex);//function to decrement the index from the Head to the Tail.

	//To input new sub-stream in the fifo, this function is called by the driver.
	bool InFifoSubStream(BYTE *pSubStreamData,int iSubStreamDataSize,structAcqInfoEx &acqInfo,const CStream_0x0001 *pStreamHeader);//"iSubStreamDataSize" is the total size of the sub stream (header + data).
	bool InFifoSubStream2(BYTE *pSubStreamData,int iSubStreamDataSize,const CStream_0x0002 *pStreamHeader);//"iSubStreamDataSize" is the total size of the sub stream (header + data).
	bool InFifoSubStreams2(int iSubStreamCount,BYTE *pSubStreamData,int iSubStreamDataSize,const CStream_0x0002 *pStreamHeader);//should be contiguous data. "iSubStreamDataSize" is the total size of the sub stream (header + data).
	BYTE *GetSubStreamItem(int iItem,int &iSubStreamDataSize,structAcqInfoEx* &pAcqInfo,CStream_0x0001* &pStreamHeader,BYTE &byVersion);

	//To input new sub-stream in the fifo, this function is called by the driver.
	BYTE* InFifoLockStream(int iStreamDataSize, int &iItem, bool &bFifoFull, int &iFifoStreamTail);//"iStreamDataSize" is the total size of the stream (header + sub-streams).
	bool InFifoUnlockStream(int iItem);//"iStreamDataSize" is the total size of the stream (header + sub-streams).
	DWORD *GetStreamItem(int iItem,int &iStreamDataSize);
	//Output stream from the fifo. The input parameter is the index of the data in the Fifo.
	//"bPeek": false to remove the data from the fifo or true to keep the data inside the fifo.
	//			if "bPeek=true" then the function "RemoveTail" or "RemoveItem" should be called.
	//"iItem": index of the item in the fifo, -1 means the last data.
	bool OutStream(int iItem,bool bPeek,void* &pStream, int &iStreamDataSize);

	//The integrated thread is launched automatically by the driver, so the user dont have to call the following functions:
	bool IsRunning();//Is the integrated thread running.
	bool Start(int iType, void* pCallback, LPTHREAD_START_ROUTINE lpStartAddress, PVOID ThreadParameter);
	bool Stop();
	void ResetProcess();
	bool SetThreadPriority(int nPriority);//input parameter is explained explanation see documentation of "SetThreadPriority".
	bool CreateEvent(int iDeviceId);
	bool CreateEvent(wchar_t *pName);
	HANDLE GetEvent();

	int _CheckCycleFMC(int iCycle,structAcqInfoEx &acqInfo);//if FMC is disabled it returns the input parameter "iCycle" otherwise it returns the absolute cycle index taking into account the pulser element (via "acqInfo.lFMCElementIndex").
	void AddFifoLost(int iLostCount);
	DWORD GetExit();
	void Exit();
	void PauseOutput(bool bEnable);
	void PauseInput(bool bEnable);
public:
private:

public:
};
#else //_WIN64
class DRIVER_OEMPA_API_ALIGN _CAcquisitionFifo
{
private:
	ULONGLONG m_ullPrivateMemory[145];
private:

};
class DRIVER_OEMPA_API_ALIGN CAcquisitionFifo : public _CAcquisitionFifo
{
public:
	CAcquisitionFifo();
	~CAcquisitionFifo();
};
#endif //_WIN64
