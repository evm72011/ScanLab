
#pragma once


const int g_iOEMPAEncoderCountMax = 4;

const int g_iMaxNameLength=48;
const int g_iOEMPAComBoardTemperatureSensorCountMax=3;//max sensor on Com board.
const int g_iOEMPARXBoardTemperatureSensorCountMax=5;//max sensor on RX board.
const int g_iOEMPAMappingDigitalInputMax=6;
const int g_iOEMPA2MappingDigitalInputMax=8;
const int g_iOEMPAMappingDigitalOutputMax=6;
const int g_iOEMPAMiniMappingDigitalInOutMax=8;
const int g_iOEMPAMiniDefaultDigitalInputMax = 6;
const int g_iOEMPAMappingDigitalInOutMax = 32;
const int g_iOEMPAFilterCoefficientMax=34;
const int g_iOEMMCFilterCoefficientMax = 18;
const int g_iCallbackArrayParameterCountMax=12;
const int g_iOEMPAAveragingSubCycleMax=16;
const int g_iOEMMCAwgStateCountMax = 1024;
const int g_iOEMMCAwgShapeCountMax = 16;

class CStream_0x0001;
class CStream_0x0002;
class CSubStreamAscan_0x0103;
class CSubStreamAscan_0x0203;
class CSubStreamAscan_0x1003;
class CMatrixAscan_0x1003;
class CSubStreamCscan_0x0X02;
class CSubStreamCscan_0x0402;
class CSubStreamIO_0x0101;
class CUTChannels;
class CSubStreamCscan_0x0302;

struct structCscanAmp_0x0102;
struct structCscanAmpTof_0x0202;
struct structCscanAmpTof_0x0302;
struct structCscanAmpTof_0x0402;
struct structCscanAmpTof_0x0502;
struct structAcqInfoEx;

typedef UINT (WINAPI *pTypeAcquisitionAscan_0x00010103)(void *pAcquisitionParameter,structAcqInfoEx &acqInfo,const CStream_0x0001 *pStreamHeader,const CSubStreamAscan_0x0103 *pAscanHeader,const void *pBufferMax,const void *pBufferMin,const void *pBufferSat);
	//input parameters
	//- "pAcquisitionParameter" : given by the user (see "CHWDevice::SetAcquisitionParameter").
	//- "pAcqInfo" : encoder values and extra data ("pAcqInfo::pChannels" is reserved for kernel API).
	//		"structAcqInfoEx::lEncoder1" first encoder associated to the other inputs parameters (according that IO stream are sent, it depends of the HW and SW configuration).
	//		"structAcqInfoEx::lEncoder2" second encoder associated to the other inputs parameters (according that IO stream are sent, it depends of the HW and SW configuration).
	//- "pStreamHeader" is a pointer on stream description, useful member is:
	//		"CStream_0x0001::settingId" identifier of the FW parameter set.
	//- "pAscanHeader" is a pointer on data description, useful members are:
	//		"CSubStreamAscan_0x0103::cycle" cycle number (for single acquisition channel), for multiple acquisition channel refer to "pAcqInfo".
	//		"CSubStreamAscan_0x0103::dataCount" data count.
	//		"CSubStreamAscan_0x0103::dataSize" size of one data (in bytes, for max, min and sat buffer).
	//		"CSubStreamAscan_0x0103::max" maximum buffer is valid (pBufferMax is not null).
	//		"CSubStreamAscan_0x0103::min" minimum buffer is valid (pBufferMin is not null).
	//		"CSubStreamAscan_0x0103::sat" saturation buffer is valid (pBufferSat is not null).
	//		"CSubStreamAscan_0x0103::seqLow" sequence number (LOW DWORD).
	//		"CSubStreamAscan_0x0103::seqHigh" sequence number (HIGH DWORD).
	//		"CSubStreamAscan_0x0103::FWAcqIdChannelProbe" probe index of the logical channel (acquisition identifier information), see "OEMPA_SetAscanAcqIdChannelProbe",
	//		"CSubStreamAscan_0x0103::FWAcqIdChannelScan" scan index of the logical channel (acquisition identifier information), see "OEMPA_SetAscanAcqIdChannelScan".
	//		"CSubStreamAscan_0x0103::FWAcqIdChannelCycle" cycle index of the logical channel (acquisition identifier information), see "OEMPA_SetAscanAcqIdChannelCycle".
	//		see comments in "CSubStreamAscan_0x0103" for more information.
	//- "pBufferMax" is the buffer of maximum acquisition data, array of data ("dataSize" is the size of one data).
	//		("CSubStreamAscan_0x0103::dataCount" x "CSubStreamAscan_0x0103::dataSize" is the total size of this buffer .
	//- "pBufferMin" is the buffer of minimum acquisition data, array of data ("dataSize" is the size of one data).
	//		("CSubStreamAscan_0x0103::dataCount" x "CSubStreamAscan_0x0103::dataSize" is the total size of this buffer .
	//- "pBufferSat" is the buffer of saturation acquisition data, array of data ("dataSize" is the size of one data but
	//		only the LSB bit is significant other bits are 0).
	//		("CSubStreamAscan_0x0103::dataCount" x "CSubStreamAscan_0x0103::dataSize" is the total size of this buffer .
typedef UINT (WINAPI *pTypeAcquisitionAscan_0x00020203)(void *pAcquisitionParameter,const CStream_0x0002 *pStreamHeader,const CSubStreamAscan_0x0203 *pAscanHeader,const void *pBufferMax,const void *pBufferMin,const void *pBufferSat);

typedef UINT(WINAPI *pTypeAcquisitionAscan_0x00021003)(void *pAcquisitionParameter, const CMatrixAscan_0x1003 *pMatrixAscan);

typedef UINT (WINAPI *pTypeAcquisitionCscan_0x00010X02)(void *pAcquisitionParameter,structAcqInfoEx &acqInfo,const CStream_0x0001 *pStreamHeader,const CSubStreamCscan_0x0X02 *pCscanHeader,const structCscanAmp_0x0102 *pBufferAmp, const structCscanAmpTof_0x0202 *pBufferAmpTof);
	//input parameters
	//- "pAcquisitionParameter" : given by the user (see "CHWDevice::SetAcquisitionParameter").
	//- "pAcqInfo" : encoder values and extra data ("pAcqInfo::pChannels" is reserved for kernel API).
	//		"structAcqInfoEx::lEncoder1" first encoder associated to the other inputs parameters (according that IO stream are sent, it depends of the HW and SW configuration).
	//		"structAcqInfoEx::lEncoder2" second encoder associated to the other inputs parameters (according that IO stream are sent, it depends of the HW and SW configuration).
	//- "pStreamHeader" is a pointer on stream description, useful member is:
	//		"CStream_0x0001::settingId" identifier of the FW parameter set.
	//- "pCscanHeader" is a pointer on data description, useful members are:
	//		"CSubStreamCscan_0x0X02::version" sub stream type (1: amplitude only, 2 amplitude and time of flight).
	//		"CSubStreamCscan_0x0X02::cycle" cycle number.
	//		"CSubStreamCscan_0x0X02::count" data count.
	//		"CSubStreamCscan_0x0X02::seqLow" sequence number (LOW DWORD).
	//		"CSubStreamCscan_0x0X02::seqHigh" sequence number (HIGH DWORD).
	//		see comments in "CSubStreamCscan_0x0X02" for more information.
	//- "pBufferAmp" is the buffer of cscan amplitude (sub stream version.
	//		this is an array which size is "CSubStreamCscan_0x0X02::count".
	//		NULL in case "CSubStreamCscan_0x0X02::version" is 2 (amplitude and time of flight).
	//- "pBufferAmpTof" is the buffer of cscan amplitude and time of flight.
	//		this is an array which size is "CSubStreamCscan_0x0X02::count".
	//		NULL in case "CSubStreamCscan_0x0X02::version" is 1 (amplitude only).

typedef UINT(WINAPI *pTypeAcquisitionAscanCscan_0x00020203_0x0302)(void *pAcquisitionParameter, structAcqInfoEx &acqInfo, const CStream_0x0002 *pStreamHeader,
								const CSubStreamAscan_0x0203 *pAscanHeader, const void *pBufferMax, const void *pBufferMin, const void *pBufferSat,
								const CSubStreamCscan_0x0302 *pCscanHeader, const structCscanAmpTof_0x0302 *pBufferAmpTof);

typedef UINT(WINAPI *pTypeAcquisitionAscanCscan_0x00030203_0x0302)(void *pAcquisitionParameter, structAcqInfoEx &acqInfo, const CStream_0x0002 *pStreamHeader,
	const CSubStreamAscan_0x0203 *pAscanHeader, const void *pBufferMax, const void *pBufferMin, const void *pBufferSat,
	const CSubStreamCscan_0x0302 *pCscanHeader, const structCscanAmpTof_0x0502 *pBufferAmpTof);

typedef UINT(WINAPI *pTypeAcquisitionCscan_0x00020402)(void *pAcquisitionParameter, structAcqInfoEx &acqInfo, const CStream_0x0002 *pStreamHeader,
	const CSubStreamCscan_0x0402 *pCscanHeader, const structCscanAmpTof_0x0402 *pBufferAmpTof);

typedef UINT (WINAPI *pTypeAcquisitionIO_0x00010101)(void *pAcquisitionParameter,const CStream_0x0001 *pStreamHeader,const CSubStreamIO_0x0101 *pIOHeader);
	//Useful members are (see class "CSubStreamIO_0x0101"):
	//CSubStreamIO_0x0101::encoder1
	//CSubStreamIO_0x0101::encoder2
	//CSubStreamIO_0x0101::inputs	: digital inputs
	//CSubStreamIO_0x0101::edges	: which digital inputs has been updated ?

typedef UINT (WINAPI *pTypeAcquisitionIO_1x00010101)(void *pAcquisitionParameter,structAcqInfoEx &acqInfo,const CStream_0x0001 *pStreamHeader,const CSubStreamIO_0x0101 *pIOHeader);
	//Useful members are (see class "CSubStreamIO_0x0101"):
	//CSubStreamIO_0x0101::encoder1
	//CSubStreamIO_0x0101::encoder2
	//CSubStreamIO_0x0101::inputs	: digital inputs
	//CSubStreamIO_0x0101::edges	: which digital inputs has been updated ?

typedef UINT (WINAPI *pTypeAcquisitionInfo)(void *pAcquisitionParameter,const wchar_t *pInfo);
	//example of input parameter: "HW Error : ..." error reporting by the hardware.

typedef UINT (WINAPI *pTypeAcquisitionStream)(void *pAcquisitionParameter,void *pData,int iSize);
	//This function can be used to receive the whole FW stream (including all ascan, cscan, IO...).
	//OEM-PA1: whole stream from USB3.

typedef UINT (WINAPI *pTypeAcquisitionStreamNotification)(void *pAcquisitionParameter, void *pData, int iSize, bool bEnterOrLeave);
	//This function can be used to receive a notification before stream processing (in that case "bEnterOrLeave" is true)
	//or after stream processing (in that case "bEnterOrLeave" is false).

class CHWDevice;
typedef struct structCallbackNotification{
	void *pAcquisitionParameter;
	pTypeAcquisitionAscan_0x00010103 pAscan_0x00010103;
	pTypeAcquisitionCscan_0x00010X02 pCscan_0x00010X02;
	pTypeAcquisitionIO_0x00010101 pIO_0x00010101;
	pTypeAcquisitionIO_1x00010101 pIO_1x00010101;
	bool bIODigitalEdgesOnly;
	pTypeAcquisitionInfo pInfo;
	pTypeAcquisitionStream pStream;
}structCallbackNotification;
typedef UINT (WINAPI *pTypeCallbackNotification)(CHWDevice *pHWDevice,structCallbackNotification &data);
	//input parameters
	//- "pHWDevice" : driver pontier.
	//- "data" : list of all acquisition callback functions.

typedef struct structAcquisitionCallbacks {
	structAcquisitionCallbacks()
	{
		pAscan1 = NULL;
		pAscan2 = NULL;
		pAscan3 = NULL;
		pAscanCscan = NULL;
		pAscanCscan2 = NULL;
		pCscan1 = NULL;
		pCscan2 = NULL;
		pIO0 = NULL;
		pIO1 = NULL;
		pStream0 = NULL;
		pStream1 = NULL;
		pInfo = NULL;
		pStreamNotification = NULL;
		pReInitChain = NULL;
	};
	pTypeAcquisitionAscan_0x00010103 pAscan1;//iType=0
	pTypeAcquisitionAscan_0x00020203 pAscan2;//iType=1
	pTypeAcquisitionAscanCscan_0x00020203_0x0302 pAscanCscan;//iType=2
	pTypeAcquisitionAscan_0x00021003 pAscan3;
	// 32bit TOF
	pTypeAcquisitionAscanCscan_0x00030203_0x0302 pAscanCscan2;//iType=3?
	pTypeAcquisitionCscan_0x00010X02 pCscan1;//iType=0
	pTypeAcquisitionCscan_0x00020402 pCscan2;
	pTypeAcquisitionIO_0x00010101 pIO0;//iType=0
	pTypeAcquisitionIO_1x00010101 pIO1;//iType=1
	pTypeAcquisitionStream pStream0;//iType=0
	pTypeAcquisitionStream pStream1;//iType=1
	pTypeAcquisitionInfo pInfo;
	pTypeAcquisitionStreamNotification pStreamNotification;
	pTypeAcquisitionStream pReInitChain;
} structAcquisitionCallbacks;

typedef struct structTFM_FlatContact_Linear1D{
									double dProbePitchIn;
									double dXFirstElement;//unit meter
									double dXMin;//unit meter
									double dXMax;//unit meter
									double dZMin;//unit meter
									double dZMax;//unit meter
									int iApertureElementCount;
								}structTFM_FlatContact_Linear1D;
typedef union unionTFMParameters{
									structTFM_FlatContact_Linear1D	flatContactLinear1D;
								}unionTFMParameters;
#ifdef _WIN32
class CThreadPerf;
#endif _WIN32
