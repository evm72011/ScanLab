
#pragma once

#ifdef SHARED_ENCODER
#else //SHARED_ENCODER
const int g_iSharedEncoderMaxCount = 32;
#endif //SHARED_ENCODER
typedef struct structAcquisitionEncoder{
	structAcquisitionEncoder(){m_dwDigitalInputs=0;memset(bEncoderHW,0,sizeof(bEncoderHW));memset(bEncoderSW,0,sizeof(bEncoderSW));for(int i=0;i<g_iSharedEncoderMaxCount;i++){lEncoderHW[i]=0;fEncoderSW[i]=0.0;}};
	DWORD m_dwDigitalInputs;//digital inputs.
	bool bEncoderHW[g_iSharedEncoderMaxCount];//true if "lEncoderHW" has been updated.
	bool bEncoderSW[g_iSharedEncoderMaxCount];//true if "fEncoderSW" has been updated.
	LONG lEncoderHW[g_iSharedEncoderMaxCount];//take into account resolution.
	float fEncoderSW[g_iSharedEncoderMaxCount];//take into account internal synchronisation.
}structAcquisitionEncoder;


class UTKERNEL_API_ALIGN _CUTMutex
{
private:
	ULONGLONG m_ullPrivateMemory[71];
protected:

};

class UTKERNEL_API_ALIGN CUTMutex :
	public _CUTMutex
{
public:
public:

public:
	bool Lock();
	bool Unlock();
	bool TryLock();
	bool TryLock(DWORD dwTimeOut,bool &bLockedByOtherProcess);
	bool IsLocked();
	bool Lock(DWORD dwTimeOut,DWORD *pdwWaitResult,bool *pbLockedByOtherProcess);
	int GetCount(DWORD dwThreadId);
	int GetCount();
private:

public:
};

typedef struct structUTDataSharedHeader
{
	DWORD m_dwAllocatedSize;
	DWORD dwMutexCommonThreadId;
	LONG lMutexCommonCount;
	DWORD dwMutex2CommonThreadId;
	LONG lMutex2CommonCount;
} structUTDataSharedHeader;

typedef struct structUTDataMainHeader
{
	int m_iHeaderSize;
	int m_iDataSize;
	int m_iID;
	int m_iDataSizeCurrent;
	LONGLONG m_llUpdateDataCount;
	LONGLONG m_llUpdateHeaderCount;
} structUTDataMainHeader;

typedef struct structUTDataHeader
{
	structUTDataMainHeader main;
	structUTDataSharedHeader shared;
} structUTDataHeader;

class CUTDataGeneric;
class UTKERNEL_API_ALIGN _CUTKernelDataHeader
{
private:
	ULONGLONG m_ullPrivateMemory[2];
protected:

};

class UTKERNEL_API_ALIGN CUTKernelDataHeader :
	protected structUTDataHeader,
	public _CUTKernelDataHeader
{
public:
public:
	virtual bool vf_SetHeaderSize(int iSize);
	virtual bool vf_SetDataSize(int iSize);
	virtual int vf_GetDataSize();
	virtual bool vf_SetDataSizeCurrent(int iSize);
	virtual bool vf_Lock(DWORD dwTimeOut=INFINITE,DWORD *pdwWaitResult=NULL,bool *pbLockOtherProcess=NULL);
	virtual bool vf_Unlock();
private:
protected:

public:
private:
	
};

class CUTKernelData;
class UTKERNEL_API_ALIGN _CUTKernelData
{
private:
	ULONGLONG m_ullPrivateMemory[169];
public:

};

class UTKERNEL_API_ALIGN CUTKernelData :
	public CUTKernelDataHeader,
	public CUTMutex,
	public _CUTKernelData
{
public:

public:
public:
	virtual bool vf_Alloc();//first set the name.
	virtual bool vf_Free();
	virtual bool vf_AllocThisBuffer();
	virtual bool vf_FreeThisBuffer();

public:
	bool IsAllocated() const;

public:
	bool _GetID(int &iID) const;
	virtual bool vf_SetHeaderSize(int iSize);
	virtual bool vf_SetDataSize(int iSize);
	virtual bool vf_Lock(DWORD dwTimeOut=INFINITE,DWORD *pdwWaitResult=NULL,bool *pbLockOtherProcess=NULL);
	virtual bool vf_Unlock();

public:
	bool Lock(DWORD dwTimeOut=INFINITE,DWORD *pdwWaitResult=NULL);
	bool Unlock();

	LPVOID GetHeaderBuffer();
	LPVOID GetDataBuffer();

public:
	void GetGenericDataAccess(enumDataType &eDataType,enumGenericAccess &eGenericAccess);
	enumDataType GetDataType();
	enumGenericAccess GetGenericAccess();

//overwrite : no need to specify size and sign.
	//array slow access : index check and lock is used.
	bool SetData(void *pBuffer,int iSize,int iByteOffset);
	bool GetData(void *pBuffer,int iSize,int iByteOffset);

	//array quick access : no index check and lock is not used.
	void SetQuickData(void *pBuffer,int iSize,int iByteOffset);
	void GetQuickData(void *pBuffer,int iSize,int iByteOffset);

//generic function : quick data access and easy to use.
	bool GetGenericData(void *pBuffer,int iByteOffset);
	void GetGenericQuickData(void *pBuffer,int iByteOffset);
	bool GetGenericArrayData(void *pBuffer,int iBufferCount,int iDataCount,int iByteOffset,int iDataIndexStep);
	bool GetGenericQuickArrayData(void *pBuffer,int iBufferCount,int iDataCount,int iByteOffset,int iDataIndexStep);
	bool ResetGenericData();//take into account the process (overwrite, minimum or maximum).
	bool SetGenericData(void *pBuffer);
	bool SetGenericData(void *pBuffer,int iByteOffset);
	void SetGenericQuickData(void *pBuffer,int iByteOffset);
	bool SetGenericArrayData(void *pBuffer,int iCount,int iByteOffset,int iDataIndexStep,enumArrayParamAccess eArrayParamAccess,bool *pbParamAccess);
	bool SetGenericQuickArrayData(void *pBuffer,int iCount,int iByteOffset,int iDataIndexStep,enumArrayParamAccess eArrayParamAccess,bool *pbParamAccess);
	bool SetGenericQuickArrayData(void *pBuffer,int iCount,int *aiByteOffset,enumArrayParamAccess eArrayParamAccess,bool *pbParamAccess);

public:

	bool SetGenericBitwiseMask(DWORD dwBitwiseMask);
	bool GetGenericBitwiseMask(DWORD &dwBitwiseMask);
private:

public:
private:
	
};

class UTKERNEL_API_ALIGN _CUTDataGeneric
{
private:
	ULONGLONG m_ullPrivateMemory[34];
public:

};


class UTKERNEL_API_ALIGN CUTDataGeneric :
	public CUTKernelData,
	public _CUTDataGeneric
{
public:

public:
public:
	CUTDataGeneric();
	~CUTDataGeneric();
	CUTKernelData* cast_pCUTKernelData();

	bool SetDataAxisCount(	int iAxisCount,//could be 1, 2, 3 or 4 ('eA','eX','eY','eZ').
						int64_t *aiAxisCount//point count on each axis.
						);
	bool GetDataAxisCount(	int iAxisCountIn,//input : could be 1, 2, 3 or 4 ('eA','eX','eY','eZ').
						int64_t *aiAxisCount,//input/output point count on each axis.
						int &iAxisCountOut//output.
						);

	bool SetDataFormat(bool bZoom,int64_t iViewZoomLeft,int64_t iViewZoomRight,enumDataType eDataType);
	void GetDataFormat(bool &bZoom,int64_t &iZoomViewLeft,int64_t &iZoomViewRight,enumDataType &eDataType);
	bool SetBitwiseFormat(int iBitwiseByte);//usefull only for WORD and DWORD bitwise data.
	bool GetBitwiseFormat(int &iBitwiseByte);
	//access for 8 bits palette views
	bool GetGenericZoomInUChar(void* pDataIn,unsigned char *pDataOut);
	bool GetGenericZoomOutUChar(unsigned char* pDataIn,void* pDataOut);
	bool GetGenericArrayZoomInUChar(int iCount,void* pDataIn,unsigned char *pDataOut);
	bool GetGenericArrayZoomOutUChar(int iCount,unsigned char* pDataIn,void* pDataOut);

	bool GetIndex(int iIndexX,int &iIndex);
	bool GetIndex(int iIndexX,int iIndexY,int &iIndex);
	bool GetIndex(int iIndexX,int iIndexY,int iIndexZ,int &iIndex);

	bool GetByteOffset(int iDataCount,bool *abInRange,int *aiIndexX,int *aiByteOffset);
	bool GetByteOffset(int iDataCount,bool *abInRange,int *aiIndexX,int *aiIndexY,int *aiByteOffset);
	bool GetByteOffset(int iDataCount,bool *abInRange,int *aiIndexX,int *aiIndexY,int *aiIndexZ,int *aiByteOffset);

public:

	__inline bool GetByteOffset(int iIndexX,int &iByteOffset);
	__inline bool GetByteOffset(int iIndexX,int iIndexY,int &iByteOffset);
	__inline bool GetByteOffset(int iIndexX,int iIndexY,int iIndexZ,int &iByteOffset);

	__inline int GetQuickByteOffset(int iIndexX);
	__inline int GetQuickByteOffset(int iIndexX,int iIndexY);
	__inline int GetQuickByteOffset(int iIndexX,int iIndexY,int iIndexZ);

	__inline bool DataLock();
	__inline bool DataUnlock();
	__inline DWORD Index2DTo1D(int iIndexX,int iIndexY);
	__inline void Index1DTo2D(DWORD dwIndex1D,int &iIndexX,int &iIndexY);
	bool HistoricIncrement(DWORD dwIndex1D);
	bool HistoricAdd(int iIndexCount,bool *aiInRange,int *aiIndex1D);
	bool HistoricAdd(int iIndexCount,bool *aiInRange,int *aiIndexX,int *aiIndexY);

public:
	bool HistoricDecrement(DWORD &dwIndex1D);
	int HistoricRemove(int iIndexCount,int *aiIndex1D);
	int HistoricRemove(int iIndexCount,int *aiIndexX,int *aiIndexY);
	void UpdateHistoricCount();
	LONGLONG GetHistoricCount(bool &bRefreshRequired);

	int GetDataBufferByteSize();//data buffer data size.
	int GetDataBitSize() const;
	__inline int GetDataByteSize() const;
	__inline int GetDataZByteSize() const;

private:

public:
};

