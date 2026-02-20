
#pragma once

#if !defined(_COM_DECL_) && !defined(FPGA_MANAGER_EXPORTS) && !defined(xFPGA_MANAGER_EXPORTS)
#ifdef _UTSOCK_EXPORT_
#ifdef _WIN32
#define _COM_DECL_ __declspec(dllexport)
#elif defined __linux__
#define _COM_DECL_ __attribute__((visibility ("default")))
#endif // __linux__
#else // _UTSOCK_EXPORT_
#ifdef _WIN32
#define _COM_DECL_ __declspec(dllimport)
#elif defined __linux__
#define _COM_DECL_
#endif // __linux__
#endif // _UTSOCK_EXPORT_
#endif
#if defined(FPGA_MANAGER_EXPORTS) || defined(xFPGA_MANAGER_EXPORTS)
#define _COM_DECL_
#endif

#include "UTDriverCommon.h"

#define SUB_STREAM_STATUS_ID	0x40

_COM_DECL_ bool UTCom_Ping(char *ip, int timeout);
_COM_DECL_ bool UTCom_ArpPing(const char *pIDAddr, int timeout);
_COM_DECL_ bool UTCom_ArpPing(const wchar_t *pIDAddr, int timeout);

class CChainSubStreamAscan_0x0203;

#ifndef COM_DECL_CLASSES
#define COM_DECL_CLASSES
#pragma pack(push, 1)
class _COM_DECL_ CStream_0x0001
{
public:
	CStream_0x0001();
	void Constructor();
public:

public:

	unsigned start:32;
	unsigned size:32;
	unsigned frameId:32;//frame number.
	unsigned settingId:32;
	unsigned subStreamCount:16;
	unsigned version : 4;
	unsigned swTransit : 4;//reserved by the SW.
	unsigned swSubDevId : 7;//reserved by the SW.
	unsigned swStatus : 1;//reserved by the SW.
};
class _COM_DECL_ CStream_0x0002
{//64 bits alignment.
public:
	CStream_0x0002();
	void Constructor();
	operator CStream_0x0001 *();
public:

public:

	unsigned newStart:32;//0xABABAB46
	unsigned size:32;//current size
	unsigned nextSize:32;
	unsigned error:32;
	unsigned swMarge0:32;//reserved by the SW. NextStreamPtr low.
    unsigned digitalInputs:8;
    unsigned maxTemperature:8;
	unsigned swDevId : 8;
	unsigned marge3 : 8;
	unsigned encoder0:32;
    unsigned encoder1:32;
    unsigned encoder2:32;
    unsigned encoder3:32;
    unsigned swMarge2:32;//reserved by the SW. NextStreamPtr high.
    unsigned totalSize:32;
    unsigned swFifoStreamIndex : 16;//reserved by the SW.
	unsigned swMerge : 1;//reserved by the SW.
	unsigned swMergeSent : 1;//reserved by the SW.
	unsigned swSubDevId : 5;//reserved by the SW.
	unsigned swReserved0 : 5;//reserved by the SW.
	unsigned swReserved : 2;//reserved by the SW.
	unsigned setting : 1;
	unsigned fmc : 1;//managed by the FW.
	CStream_0x0001 m_Stream_0x0001;
};

class _COM_DECL_ CSubStreamIO_0x0101
{
public:
	CSubStreamIO_0x0101();
public:

public:
	bool Check() const;

	unsigned id:8;
	unsigned version:8;
	unsigned size:16;
	unsigned timeStampLow:32;
	unsigned timeStampHigh:32;
	unsigned cycle:16;
	unsigned maxTemperature:7;//maximum temperature (unit=). Not supported by all FW.
	unsigned padding0:9;
	unsigned seqLow:32;
	unsigned seqHigh:32;
	unsigned inputs:32;//digital inputs value.
	unsigned edges:32;//edges : which digital input has been updated ?
						//if bit 16 is set to 1 then this is initialisation stream (sent on any updates from "SetRequestIO").
	unsigned encoder1:32;
	unsigned encoder2:32;
};



typedef struct structCscanAmp_0x0102{
		unsigned byAmp:8;//cscan amplitude. Could be signed value, it depends of the GateModeThreshold setting data.
		unsigned gateId:2;//gate identifier (could be: 0=first gate, 1=second gate, 2=third gate, 3=fourth gate).
		unsigned sign:1;//0 byAmp is unsigned, 1 byAmp is signed.
		unsigned AmpOverThreshold:1;//0 if byAmp is under threshold, and 1 if it is over the threshold.
		unsigned TofValidity:1;//0 (no time of flight).
		unsigned IFOldReference:1;//(IFtracking) 1 if old reference time of flight has been used to synchronize the start or the stop.
		unsigned IFNotInitialized:1;//(IFtracking) 1 if the first reference time of flight has been initialized yet (because of acoustic or because of bad setting stop>start).
		unsigned ampDisabled : 1;//1 for example in the case of SW gate if the data is out of ascan window.
		unsigned wAcqId:16;//acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
}structCscanAmp_0x0102;
typedef struct structCscanAmpTof_0x0202{
		unsigned byAmp:8;//cscan amplitude. Could be signed value, it depends of the GateModeThreshold setting data.
		unsigned gateId:2;//gate identifier (could be: 0=first gate, 1=second gate, 2=third gate, 3=fourth gate).
		unsigned sign:1;//0 byAmp is unsigned, 1 byAmp is signed.
		unsigned AmpOverThreshold:1;//0 if byAmp is under threshold, and 1 if it is over the threshold.
		unsigned TofValidity:1;//1 if wTof is valid.
		unsigned IFOldReference:1;//(IFtracking) 1 if old reference time of flight has been used to synchronize the start or the stop.
		unsigned IFNotInitialized:1;//(IFtracking) 1 if the first reference time of flight has been initialized yet (because of acoustic or because of bad setting stop>start).
		unsigned ampDisabled : 1;//1 for example in the case of SW gate if the data is out of ascan window.
		unsigned wAcqIdAmp:16;//acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
		unsigned wTof:16;//cscan time of flight for the same gate.
		unsigned wAcqIdTof:16;//time of flight acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
}structCscanAmpTof_0x0202;
class _COM_DECL_ CSubStreamCscan_0x0X02
{
public:
	CSubStreamCscan_0x0X02();//X=1 or 2.

public:

public:
	bool Check() const;//check consistancy of the sub strem.

	unsigned id:8;
	unsigned version:8;	//could be 1 or 2 (it depends of the setting, parameter RequestCscan with enumeration enumOEMPARequestCscan):
						//1: all cscan gate (amplitude only), packed together in the current sub stream, are for the same cycle number.
						//	 in this case the member "cylce" could used.
						//2: all cscan gate (amplitude + time of flight) of all cycles of the sequence are packed together in the same substream.
						//	 in this case the member "cylce" has no significance.
	unsigned size:16;
	unsigned timeStampLow:32;
	unsigned timeStampHigh:32;
	unsigned cycle:16;//cycle value in case "version" member value is 1, cycle=0xffff in case "version" member value is 2 (not significant in this case).
	unsigned count:15;//count of gates (amplitude only in case of "version" is 1, or amplitude + time of flight in case of "version" is 2).
	unsigned reserved:1;
	unsigned seqLow:32;//sequence number (LOW WORD).
	unsigned seqHigh:32;//sequence number (HIGH WORD).
};
class _COM_DECL_ CSubStreamAscan_0x0103
{
public:
	CSubStreamAscan_0x0103();
public:

public:
	bool Check() const;
	int GetPointCountLimit() const;
	int GetPointCountReal() const;

	//ONLY USEFUL MEMBERS FOR THE USER HAVE COMMENT.
	unsigned id:8;//DWORD[0]
	unsigned version:8;
	unsigned size:16;
	unsigned timeStampLow:32;//DWORD[1]
	unsigned timeStampHigh:32;//DWORD[2]
	unsigned cycle:16;//cycle number. DWORD[3]
	unsigned dataCount:16;//data count (dataCount x dataSize = total data size).
	unsigned src:1;//DWORD[4]
	unsigned dst:1;
	unsigned type:1;
	unsigned error:1;
	unsigned dataSize:4;//size of one data (in bytes), take a look also to member "bitSize".
	unsigned align:4;
	unsigned max:1;//maximum buffer is valid.
	unsigned min:1;//minimum buffer is valid.
	unsigned sat:1;//saturation buffer is valid.
	unsigned sign:1;//sign of maximum and minimum buffer data.
	unsigned bitSize:2;//see enumBitSize
	unsigned dacIFOldReference:1;//(IFtracking of the dac) 1 if old reference time of flight has been used to synchronize the start or the stop.
	unsigned dacIFNotInitialized:1;//(IFtracking of the dac) 1 if the first reference time of flight has been initialized yet.
	unsigned IFOldReference:1;//(IFtracking of the ascan gate) 1 if old reference time of flight has been used to synchronize the start or the stop.
	unsigned IFNotInitialized:1;//(IFtracking of the ascan gate) 1 if the first reference time of flight has been initialized yet.
	unsigned padding0:10;
	unsigned FWAcqIdChannelCycle:16;//acquisition Id for saturation data, see "OEMPA_SetAscanAcqIdChannelCycle". DWORD[5]
	unsigned FWAcqIdChannelScan:16;//acquisition Id for minimum data, see "OEMPA_SetAscanAcqIdChannelScan".
	unsigned FWAcqIdChannelProbe:16;//acquisition Id for maximum data, see "OEMPA_SetAscanAcqIdChannelProbe". DWORD[6]
	unsigned padding1:16;
	unsigned seqLow:32;//sequence number (LOW DWORD) DWORD[7]
	unsigned seqHigh:32;//sequence number (HIGH DWORD) DWORD[8]
};
class _COM_DECL_ CSubStreamAscan_0x0203
{
public:
	CSubStreamAscan_0x0203();
public:

public:
	const CSubStreamAscan_0x0203* GetNextAscan() const;
	bool Check() const;

    unsigned id:8;//DWORD[0]
    unsigned version:8;
    unsigned size:16;
    unsigned deviceId:8;//DWORD[1]
    unsigned marge1:21;
	unsigned swMultiChannel:1;
	unsigned swCheckElementNumber:1;//SW value.
    unsigned swFullMatrixCapture:1;//SW value.
	unsigned element:16;//DWORD[2]
    unsigned maxTemperature:8;
    unsigned digitalInputs:8;
    unsigned encoder0:32;//DWORD[3]
    unsigned encoder1:32;//DWORD[4]
    unsigned encoder2:32;//DWORD[5]
    unsigned encoder3:32;//DWORD[6]
    unsigned marge2:32;//reserved by the SW. DWORD[7]
	unsigned digitalInputs32 : 32;//32 IOs with PIO board (GetSWDeviceOEMPA()->IsPIOBoard()). DWORD[8]
	CSubStreamAscan_0x0103 m_Ascan_0x0103;
};

typedef struct structAscanEx_0x1003
{
	unsigned id : 8;//DWORD[0]
	unsigned version : 8;
	unsigned zero : 16;
	unsigned size1 : 32;//DWORD[1] total size of the substream all included LSB.
	unsigned size2 : 32;//DWORD[2]
	unsigned element_count : 16;//DWORD[3]
	unsigned element_offset : 16;
	unsigned align_bit : 16;//DWORD[4]
	unsigned data_size_bit : 16;
	unsigned data_align_bit : 8;//DWORD[5]
	unsigned marge1 : 24;
} structAscanEx_0x1003;
class _COM_DECL_ CSubStreamAscan_0x1003
{
public:
	CSubStreamAscan_0x1003();
public:

public:
	const void* cGetAscan(int iElementIndex) const;
	CSubStreamAscan_0x1003* GetNextAscanMatrix() const;
	const CSubStreamAscan_0x1003* cGetNextAscanMatrix() const;
	bool Check() const;

	structAscanEx_0x1003 header;//DWORD[0..5]
	DWORD data[48-6];//DWORD[6..37][38..47]
	CSubStreamAscan_0x0203 m_Ascan_0x0203;
};

const int g_iDriverEncoderCountMax = 4;
typedef struct structAcqInfoEx {
	LONG lEncoder[g_iDriverEncoderCountMax];//unit given by the encoder
	double dEncoder[g_iDriverEncoderCountMax];//unit : meter (encoder resolution is taken into account).
	DWORD dwDigitalInputs;
	LONG lMaxTemperature;//0 if not significant (for some FW version or in case IO stream are not sent by the HW).
	LONG lDeviceId;//device identifier
	LONG bMultiChannel;//1 if Multi-Channel is enabled, 0 otherwise.
	LONG bFullMatrixCapture;//1 if FullMatrixCapture is enabled, 0 otherwise.
	LONG lFMCElementIndex;//in case of Full Matrix Capture, this is the element index for the current ascan;
	LONG lComDevId;
	LONG lSubDevId;
	LONG lOffLine;//useful for OEMPA2, real-time or analysis.
}structAcqInfoEx;
typedef struct structFMCElementInfo {
	short iProbeElement;
	short iCycle;
} structFMCElementInfo;
class CHWDeviceOEMPA;


typedef unsigned int arrayFMCElementCount[g_iAssociationSubDeviceCountMax][g_iFWCycleCountMax];
typedef unsigned int arrayFMCElementCountAll[g_iFWCycleCountMax];
class _COM_DECL_ CMatrixAscan_0x1003
{
public:

public:
public:
	CMatrixAscan_0x1003();
	~CMatrixAscan_0x1003();
	CMatrixAscan_0x1003& operator=(const CMatrixAscan_0x1003& a);
	void Reset();

	int GetIndexSequence() const;
	int GetAscanCount() const;
	int GetPointCountLimit() const;	// Use only when all cycles have the same range.
	int GetPointCountReal() const;	// Use only when all cycles have the same range.
	int GetByteSize() const;

	//setting
	const structFMCElementInfo* GetAscanElementInfo(CHWDeviceOEMPA *pHWDeviceOEMPA, int &iAscanCount) const;
	int GetCycleCount() const;
	int GetElementCount(int iSubDeviceId, int iCycleIndex) const;
	int GetProbeElementCount(int iCycleIndex) const;
	int GetElementProbeIndex(int iElementIndex, int iCycleIndex) const;//"iElementIndex" should be in the range [0.."GetElementCount(int iSubDeviceId, int iCycleIndex)"].
	/*
	* Returns various information about a given ascan based on its absolute index in the matrix.
	* The returned point count is the 'real' point count and thus shouldn't be used for pointer arythmetic when manually browsing the matrix.
	*/
	bool GetAscanInfo(int iAscanIndex, int& iSubDeviceId, int& iElementIndex, int& iElementProbeIndex, int& iCycleIndex, unsigned int& uiPointCount) const;
	/*
	* Returns the size(in byte) of a given ascan based on the absolute index in the matrix or for a given cycle.
	* Returns 0 if there is an error.
	* The returned size being the 'real' size, it should not be used for pointer arithmetic when manually browsing the matrix
	* since the ascans in the matrix are padded with zeroes to have a 32 bits alligment.
	*/
	unsigned GetAscanSize(int iAscanIndex) const;
	unsigned GetCycleAscanSize(int iCycle) const;

	bool Lock();
	bool Unlock();
	bool UnlockAll();
	bool IsLocked() const;
	int GetLockCount() const;

	uint64_t GetMatrixSize() const;//full size header + matrix.
	uint64_t GetMatrixDataSize() const;//matrix buffer size only.
	bool GetSequence(ULONGLONG &ullSequence) const;
	bool GetCycle(ULONG &ulCycle) const;//return false in case of multiple cycles.
	const structAcqInfoEx *cGetAcqInfo() const;
	structAcqInfoEx *GetAcqInfo();
	const CSubStreamAscan_0x1003 *GetStreamAscanHeader_0x1003() const;
	bool SetStreamAscanHeader_0x1003(const CSubStreamAscan_0x1003 *pSubStreamAscan_0x1003, const void *pMatrixAscan = NULL);
		//the second parameter is required in the case the header and the data are not contiguous.
	const void* cGetAscan(int iAscanIndex) const;//range 0 to "GetAscanCount()".
	const void* cGetAscan(int iCycleNumber, int iProbeElement) const;	// returns a pointer to the ascan of element 'iProbeElement' in cycle 'iCycleNumber', nullptr if error.

	bool GetLost(LONG &lLostOut) const;
	LONG GetLost() const;
	void ResetLostPtr();
	void UpdateAscanCountFromHeader();
	void SetAscanCount(int iValue);
	void EnableSingleCycle(bool bEnable);
	bool IsSingleCycle() const;
	bool AreHeaderAndDataContiguous() const;
	void SetLost(LONG lLostOut);
private:
	bool m_bSingleCycle;
	int m_iLock;
	structAcqInfoEx m_AcqInfo;
	int m_iSubDeviceCountMax;
	int m_iSubApertureElementCount;
	int m_iIndexSequence;
	int m_iCycleCountMax;
	int m_iAscanCountMax;
	uint64_t m_ullDataSize;
	const arrayFMCElementCount* m_pFMCElementCount;
	const arrayFMCElementCountAll* m_pAscanOffset;
	const arrayFMCElementCountAll* m_pAscanPointCount;
	const DWORD* m_pdwProbeElement;
	const CSubStreamAscan_0x1003 *m_pSubStreamAscan_0x1003;
	const CSubStreamAscan_0x0203 *m_pSubStreamAscan_0x0203;
	const CSubStreamAscan_0x0103 *m_pSubStreamAscan_0x0103;
	const void *m_pMatrixAscan;//in the case the header and the data are not in contiguous.
	int *m_piAssociationLostIn1;
	int *m_piAssociationLostIn2;
	int *m_piAssociationLostOut;
	int m_iAssociationLostOut;
};

typedef void (WINAPI* pCallbackBrowseSubStream)(void *parameter, bool bFMC, const DWORD *pSubStream);
class _COM_DECL_ CChainSubStreamAscan_0x0203
{
public:
	CChainSubStreamAscan_0x0203(bool bFMC = true);
	CChainSubStreamAscan_0x0203(const CChainSubStreamAscan_0x0203 &a);
	CChainSubStreamAscan_0x0203& operator=(const CChainSubStreamAscan_0x0203& a);
	operator CStream_0x0002*();
	operator CSubStreamAscan_0x0203*();

	bool StartSequence(const CStream_0x0002 *pStream);
	bool StartSequence(const CStream_0x0002 *pStream, pCallbackBrowseSubStream func, void *parameter);
	bool StartSequence(const CStream_0x0002 *pStream, CSubStreamAscan_0x0203 *pAscan);
	bool StopSequence(const CStream_0x0002 *pStream, CSubStreamAscan_0x0203 *pAscan);
	CSubStreamAscan_0x0203 *Next(bool &bNextStream);
	bool StartPatch1(CStream_0x0002 *pStreamWrong, const CStream_0x0002 *pPreviousStream);
	void Reset();

	bool bFMC;
	const CSubStreamAscan_0x0203 *pAscan;
	const CStream_0x0002 *pCurrentStream;
	const DWORD *pdwCurrentStreamFlagStop;
	const DWORD *pdwCurrentStreamSubStreamTail;
	const DWORD *pdwCurrentStreamSubStreamHead;
	const CStream_0x0002 *pCurrentSequenceStreamLastStop;
	const CSubStreamAscan_0x0203 *pCurrentSequenceAscanLastStop;
};

class _COM_DECL_ CSubStreamParameters_0x0104
{//single address
public:
	CSubStreamParameters_0x0104();
public:

public:
	bool Check() const;

	unsigned id:8;
	unsigned version:8;
	unsigned size:16;
	unsigned timeStampLow:32;
	unsigned timeStampHigh:32;
	unsigned comId:16;
	unsigned count:16;
	unsigned src:1;
	unsigned dst:1;
	unsigned type:1;//0:data,1:request
	unsigned error:1;
	unsigned dataSize:4;
	unsigned align:4;
	unsigned retransmit:4;
	unsigned boardId : 8;
	unsigned marge :/*16*/8;
};
class _COM_DECL_ CSubStreamParameters_0x0204
{//multiple address
public:
	CSubStreamParameters_0x0204();
public:

public:
	bool Check() const;

	unsigned id:8;
	unsigned version:8;
	unsigned size:16;
	unsigned timeStampLow:32;
	unsigned timeStampHigh:32;
	unsigned comId:16;
	unsigned count:16;
	unsigned src:1;
	unsigned dst:1;
	unsigned type:1;//0:data,1:request
	unsigned error:1;
	unsigned dataSize:4;
	unsigned align:4;
	unsigned retransmit:4;
	unsigned marge:16;
};
class _COM_DECL_ CSubStreamParameters_0x0304
{//multiple address
public:
	CSubStreamParameters_0x0304();
public:

public:
	bool Check() const;

	unsigned id:8;
	unsigned version:8;
	unsigned size:16;
};
class _COM_DECL_ CSubStreamPadding_0x04
{//multiple address
public:
	CSubStreamPadding_0x04(bool bRequest);
public:

public:
	bool Check() const;

	unsigned id:8;
	unsigned version:8;
	unsigned size:16;
};
class _COM_DECL_ CSubStreamParameters_0x10
{//single address
public:
	CSubStreamParameters_0x10();
public:

public:
	bool Check() const;

	unsigned id:8;
	unsigned size:24;
	unsigned timeStampLow:32;
	unsigned timeStampHigh:32;
	unsigned count:32;
	unsigned src:1;
	unsigned dst:1;
	unsigned type:1;//0:data,1:request
	unsigned error:1;
	unsigned dataSize:4;
	unsigned align:4;
	unsigned retransmit:4;
	unsigned marge:16;
};

// 32bit TOF
typedef struct structCscanAmpTof_0x0502 {
	unsigned gateId : 2;//gate identifier (could be: 0=first gate, 1=second gate, 2=third gate, 3=fourth gate).
	unsigned sign : 1;//0 wAmp is unsigned, 1 wAmp is signed.
	unsigned AmpOverThreshold : 1;//0 if wAmp is under threshold, and 1 if it is over the threshold.
	unsigned TofValidity : 1;//1 if wTof is valid.
	unsigned IFOldReference : 1;//(IFtracking) 1 if old reference time of flight has been used to synchronize the start or the stop.
	unsigned IFNotInitialized : 1;//(IFtracking) 1 if the first reference time of flight has been initialized yet (because of acoustic or because of bad setting stop>start).
	unsigned ampDisabled : 1;//1 for example in the case of SW gate if the data is out of ascan window.
	unsigned multiPeakData : 1;//1 for example in the case of MultiPeak gate peak (except the max peak).
	unsigned reserved2 : 7;
	unsigned GateThreshold : 16;
	signed tofGateStart : 32;
	signed tofGateStop : 32;
	unsigned wAmp : 16;//cscan amplitude. Could be signed value, it depends of the GateModeThreshold setting data.
	unsigned wAcqIdAmp : 16;//acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
	signed dwTof : 32;//cscan time of flight for the same gate.
	unsigned wAcqIdTof : 16;//time of flight acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
	unsigned marge : 16;//32bit alignment.
}structCscanAmpTof_0x0502;

typedef struct structCscanAmpTof_0x0302 {
	unsigned gateId : 2;//gate identifier (could be: 0=first gate, 1=second gate, 2=third gate, 3=fourth gate).
	unsigned sign : 1;//0 wAmp is unsigned, 1 wAmp is signed.
	unsigned AmpOverThreshold : 1;//0 if wAmp is under threshold, and 1 if it is over the threshold.
	unsigned TofValidity : 1;//1 if wTof is valid.
	unsigned IFOldReference : 1;//(IFtracking) 1 if old reference time of flight has been used to synchronize the start or the stop.
	unsigned IFNotInitialized : 1;//(IFtracking) 1 if the first reference time of flight has been initialized yet (because of acoustic or because of bad setting stop>start).
	unsigned ampDisabled : 1;//1 for example in the case of SW gate if the data is out of ascan window.
	unsigned multiPeakData : 1;//1 for example in the case of MultiPeak gate peak (except the max peak).
	unsigned reserved2 : 7;
	unsigned GateThreshold : 16;
	unsigned tofGateStart : 16;
	unsigned tofGateStop : 16;
	unsigned wAmp : 16;//cscan amplitude. Could be signed value, it depends of the GateModeThreshold setting data.
	unsigned wAcqIdAmp : 16;//acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
	unsigned wTof : 16;//cscan time of flight for the same gate.
	unsigned wAcqIdTof : 16;//time of flight acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.

}structCscanAmpTof_0x0302;

class _COM_DECL_ CSubStreamCscan_0x0302
{
public:
	CSubStreamCscan_0x0302();

public:

public:
	bool Check() const;

	unsigned id : 8;
	unsigned version : 8;
	unsigned size : 16;
	unsigned deviceId : 8;
	unsigned maxTemperature : 8;
	unsigned digitalInputs : 16;
	unsigned cycle : 16;//cycle value in case "version" member value is 1, cycle=0xffff in case "version" member value is 2 (not significant in this case).
	unsigned count : 8;
	unsigned marge : 8;
	unsigned encoder0 : 32;
	unsigned encoder1 : 32;
	unsigned encoder2 : 32;
	unsigned encoder3 : 32;
	unsigned marge2 : 32;
	unsigned marge3 : 32;
	unsigned timeStampLow : 32;
	unsigned timeStampHigh : 32;
	unsigned seqLow : 32;//sequence number (LOW WORD).
	unsigned seqHigh : 32;//sequence number (HIGH WORD).
};

typedef struct structCscanAmpTof_0x0402 {
	unsigned gateId : 2;//gate identifier (could be: 0=first gate, 1=second gate, 2=third gate, 3=fourth gate).
	unsigned channelId : 3;//channel identifier, from 0 to 7.
	unsigned sign : 1;//0 byAmp is unsigned, 1 byAmp is signed.
	unsigned AmpOverThreshold : 1;//0 if byAmp is under threshold, and 1 if it is over the threshold.
	unsigned TofValidity : 1;//1 if wTof is valid.
	unsigned IFOldReference : 1;//(IFtracking) 1 if old reference time of flight has been used to synchronize the start or the stop.
	unsigned IFNotInitialized : 1;//(IFtracking) 1 if the first reference time of flight has not been initialized yet (because of acoustic or because of bad setting stop>start).
	unsigned reserved : 6;
	unsigned wAcqIdAmp : 16;//acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
	unsigned dwAmp : 32;//cscan amplitude. Can be signed value, it depends of the GateModeThreshold setting data.
	unsigned wTof : 16;//cscan time of flight for the same gate.
	unsigned wAcqIdTof : 16;//time of flight acquisition identifier (could be used to link the unique gate/cycle cscan data with the setting). But it is not required to use it.
}structCscanAmpTof_0x0402;

class _COM_DECL_ CSubStreamCscan_0x0402
{
public:
	CSubStreamCscan_0x0402();
public:

public:
	bool Check() const;

	unsigned id : 8;
	unsigned version : 8;
	unsigned size : 16;
	unsigned deviceId : 8;
	unsigned marge : 24;
	unsigned marge2 : 16;
	unsigned maxTemperature : 8;
	unsigned digitalInputs : 8;
	unsigned encoder0 : 32;
	unsigned encoder1 : 32;
	unsigned marge3 : 32;
	unsigned marge4 : 32;
	unsigned marge5 : 32;
	unsigned digitalInputs32 : 32;//32 IOs with PIO board (GetSWDeviceOEMPA()->IsPIOBoard()). DWORD[8]
	CSubStreamCscan_0x0X02 m_Cscan_0x0X02;
};

#pragma pack(pop)
#endif //COM_DECL_CLASSES
