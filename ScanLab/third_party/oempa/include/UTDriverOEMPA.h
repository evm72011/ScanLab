
#pragma once
#include "Common.h"
#include "win_stub.h"
#include "UTBasicEnum.h"
#include "UTBasicType.h"
#include "UTUsbDevice.h"			//USB connection
#include "UTServerCommon.h"
#include <list>
#include <string>	// required to use "std::wstring" on VS 2022.
#include <oaidl.h>

#include "UTKernelStream.h"			//acquisition  management : definition of stream coming from FW to SW.
#include "UTDriverOEMPAExport.h"
#include "UTDriverOEMPASystem.h"
#define VIRTUAL_ENCODERSTEPFLOAT
#ifdef VIRTUAL_ENCODERSTEPFLOAT
#include "UTDriverCommon.h"  
#endif // VIRTUAL_ENCODERSTEPFLOAT

enum enumMCType {
	eMC2, eMCu, eMCNOV, eMCH, eMCuF, eNotMC
};
typedef enum enumAcquisitionMode { eAcqHW = 0, eAcqHWAutoStop = 1, eAcqHWContinuous = 2, eAcqSWReplay = 3 } enumAcquisitionMode;
typedef enum enumCheckSetupGain {	eCheckSetupGain_dXGainDigital, eCheckSetupGain_fXBeamCorrection, eCheckSetupGain_fXDacMinMax,
									eCheckSetupGain_dXGainTotal, eCheckSetupGain_bXCheckBeamCorrection, eCheckSetupGain_bXCheckDac,
									eCheckSetupGain_Last
								} enumCheckSetupGain;
typedef enum enumCheckSetupTime {	eCheckSetupTime_PA_eXAscanBitSize, eCheckSetupTime_MC_eXAscanBitSize, eCheckSetupTime_dXTimeSlot,
									eCheckSetupTime_diTestThroughput,
									eCheckSetupTime_dXAscanStart, eCheckSetupTime_dXAscanRange,
									eCheckSetupTime_dlAscanRangeWithPointCount, eCheckSetupTime_dlAscanRangeWithPointFactor,
									eCheckSetupTime_dXWedgeDelayE, eCheckSetupTime_dXWedgeDelayR,
									eCheckSetupTime_dXAscanTime, eCheckSetupTime_dXDacTime,
									eCheckSetupTime_dCheckGateStart0, eCheckSetupTime_dCheckGateStart1,
									eCheckSetupTime_dCheckGateStart2, eCheckSetupTime_dCheckGateStart3,
									eCheckSetupTime_dCheckGateStop0, eCheckSetupTime_dCheckGateStop1,
									eCheckSetupTime_dCheckGateStop2, eCheckSetupTime_dCheckGateStop3,
									eCheckSetupTime_dCheckGateWidth0, eCheckSetupTime_dCheckGateWidth1,
									eCheckSetupTime_dCheckGateWidth2, eCheckSetupTime_dCheckGateWidth3,
									eCheckSetupTime_ddLimitsSWGate,
									eCheckSetupTime_structXCheckTrackingAscan, eCheckSetupTime_structXCheckTrackingDac,
									eCheckSetupTime_structXCheckTrackingGateStart0, eCheckSetupTime_structXCheckTrackingGateStart1,
									eCheckSetupTime_structXCheckTrackingGateStart2, eCheckSetupTime_structXCheckTrackingGateStart3,
									eCheckSetupTime_structXCheckTrackingGateStop0, eCheckSetupTime_structXCheckTrackingGateStop1,
									eCheckSetupTime_structXCheckTrackingGateStop2, eCheckSetupTime_structXCheckTrackingGateStop3,
									eCheckSetupTime_Last
								} enumCheckSetupTime;
typedef struct structCheckRecoveryTimePA {
									enumBitSize eAscanBitSize;
									enumCompressionType eCompressionType;
									long lPointCount;
									long lPointFactor;
									double dStart;
									double dRange;
									double dTimeSlot;
									double dWedgeDelayE;
									double dWedgeDelayR;
									int iRecvCount;
									bool bDDF;
								} structCheckRecoveryTimePA;
typedef void (*pCallbackHWMemory)(CHWDevice *pHWDevice, DWORD addr, DWORD data, int size);
typedef void (*pmCallbackHWMemory)(CHWDevice *pHWDevice, int iSubDevIndex, DWORD addr, DWORD data, int size);

struct structNotificationOption;
class DRIVER_OEMPA_API CNotificationItem {
public:
	CNotificationItem();
	CNotificationItem(const wchar_t *wcMsg);
	~CNotificationItem();
	CNotificationItem& operator=(const CNotificationItem& a);
	CNotificationItem& operator=(const structNotificationOption& a);
	bool operator==(const CNotificationItem& a) const;
	bool operator!=(const CNotificationItem& a) const;
	bool Equal(const CNotificationItem& a) const;
	bool Equal(const CNotificationItem* a) const;
	bool EqualVariant(const VARIANT &a, const VARIANT &b) const;

#pragma warning( disable : 4251 )
	std::wstring msg;
#pragma warning( default : 4251 )
	int iDeviceId;
	int iCycle;
	int iChannel;
	int iGate;
	bool bError;//if not: it's a warning.
	bool bValue;
	bool bMin;
	bool bMax;
	VARIANT value;
	VARIANT min;
	VARIANT max;
	DWORD dwThreadId;
	DWORD dwTickCount;
};
typedef struct DRIVER_OEMPA_API structNotificationOption {
	friend class CHWDevice;
	structNotificationOption();
	structNotificationOption(bool _bCorrection);
	structNotificationOption(bool _bCorrection, int _iCycle);
	structNotificationOption(bool _bCorrection, int _iCycle, int _iChannel);
	structNotificationOption(bool _bCorrection, int _iCycle, int _iChannel, int _iGate);
	bool IsCalledFromUnlockDevice() { return bCalledFromUnlockDevice; }

	bool bFillListError;
	bool bFillListWarning;
	bool bCorrection;
private:
	bool bCalledFromUnlockDevice;
public:
	int iCycle;
	int iChannel;
	int iGate;
	std::list<CNotificationItem> *pListError;
	std::list<CNotificationItem> *pListWarning;
} structNotificationOption;

/////////////////////////////////////////////////////////////////////////////////////////
#include "UTBasicEnum.h"
#include "UTDriverTypes.h"
/////////////////////////////////////////////////////////////////////////////////////////

DRIVER_OEMPA_API const wchar_t* WINAPI OEMPA_GetVersion();
DRIVER_OEMPA_API DWORD WINAPI OEMPA_GetVersionMajor();
DRIVER_OEMPA_API DWORD WINAPI OEMPA_GetVersionMinor();
DRIVER_OEMPA_API const char OEMPA_GetVersionLetter();
class CHWDevice;
class CUTDevCommunication;

class DRIVER_OEMPA_API_ALIGN _CUTDeviceStream
{
private:
	ULONGLONG m_ullPrivateMemory[6];
public:
	_CUTDeviceStream();
	_CUTDeviceStream(DWORD *pdwData,int iSize, bool copy = true);

};

//This class can be used to manage communication stream and sub stream.
class DRIVER_OEMPA_API_ALIGN CUTDeviceStream : public _CUTDeviceStream
{
public:
	CUTDeviceStream();
	CUTDeviceStream(char* data, int size, bool copy = true);
	CUTDeviceStream(char* data, int size,int i);
	~CUTDeviceStream();

	void RemoveAll();
	bool IsBuilt() const;
	bool UpdateComId(WORD wComId,int iRetransmit,WORD wMarge=0);

	int GetSize() const;
	bool BuildSwap(int iIndexStart,int iIndexStop,int iIndexEnd);
	int BuildGrow(DWORD dwData);
	int BuildGrow(int iCount,DWORD *pdwData);
	bool BuildUpdate(int iIndex,DWORD dwData);
	bool BuildUpdate(int iIndex,int iCount,DWORD *pdwData);

	//build stream for simulation
	bool BuildAscan(int iCount,int iByteSize,const char *pBuf);//test purpose
	bool BuildText(const char *pText);
	bool Build(const char *pBuf,int iSize, bool copy = true);

	//to find each sub stream inside the stream
	const DWORD *GetStream();
	const DWORD *GetSubStreamFirst(int &iSubStreamCount,DWORD &dwSettingId,int &iIndexSubStream,bool &bText,enumSubStreamId &byID,BYTE &byVersion,WORD &wByteSize);
	const DWORD *GetSubStreamNext(int &iIndexSubStream,enumSubStreamId &byID,BYTE &byVersion,WORD &wByteSize);
	const char* GetText() const;
	int GetSubStreamCount() const;
	bool IsTextMultiple(const char *cFirstString);
	bool GetTextData(const char* &pStream, int &iIndex, int &iTextSize, wchar_t *wcText, int iTextSizeIn, char *pDataOut, int iDataSizeIn, int &iDataSizeOut);

	//to send the stream by the driver.
	int Send(CHWDevice *pHWDevice);
protected:
private:

public:
};

class CSWDevice;
class CDevDispatch;
class CUTSocket;
class CTimerProcess;

class DRIVER_OEMPA_API_ALIGN _CUTMonitorSocketManager
{
private:
	ULONGLONG m_ullPrivateMemory[18];
protected:

};

class DRIVER_OEMPA_API_ALIGN CUTMonitorSocketManager :	public _CUTMonitorSocketManager
{
public:
protected:

public:
	CUTMonitorSocketManager();
	~CUTMonitorSocketManager();

	bool IsConnected(int iSubDevId);
	int GetCountBadStopFlag();
	void EnableBadStopFlagCorrection(bool bEnable);
	bool IsBadStopFlagCorrectionEnabled();
	void SetBadStopFlagMsgCount(int iCount);
	int GetBadStopFlagMsgCount();

	bool InitCscanSW();
	bool AddSizeCscanSW(int iGateSWCount);
	bool AddSizeCscanSW2(int iGateSWCount);
	bool AllocCscanSW();
	bool AddCscanSW(CSubStreamCscan_0x0302 &cscan_0x0302, structCscanAmpTof_0x0302 aData_0x0302[g_iOEMPAGateCountMax]);
	bool AddCscanSW(CSubStreamCscan_0x0302 &cscan_0x0302, structCscanAmpTof_0x0502 aData_0x0502[g_iOEMPAGateCountMax]);
	bool SendCscanSW();

	bool IsIO();
	bool IsAscan();
	bool IsCscan();
	bool IsCscanSW();
	bool IsParametersSWToHW();//write
	bool IsParametersHWToSW();//read
	bool IsAcknowledgment();

	void EnableIO(bool bEnable);
	void EnableAscan(bool bEnable);
	void EnableCscan(bool bEnable);
	void EnableCscanSW(bool bEnable);
	void EnableParametersSWToHW(bool bEnable);//write
	void EnableParametersHWToSW(bool bEnable);//read
	void EnableAcknowledgment(bool bEnable);
	void EnableParametersHWToSWAndNotifyApplication(bool bEnable);//read

	bool OnTextStream(int iSubDevId, const char *pText);

protected:
private:

public:
};

class DRIVER_OEMPA_API_ALIGN _CUTMonitorMainManager
{
private:
	ULONGLONG m_ullPrivateMemory[75];
protected:

};

class DRIVER_OEMPA_API_ALIGN CUTMonitorMainManager :
	public _CUTMonitorMainManager
{
private:

// Construction
public:
protected:

public:
	CUTMonitorMainManager(CUTMonitorSocketManager *pMonitorSocket);
	~CUTMonitorMainManager();

	bool Start(int iPort, int iMaxConnection);
	bool ConnectMonitorSubDev(int iSubDevId);
	bool IsStarted() const;
	DWORD GetSocketThreadId();
	bool RemoteMonitorConnect(int iSubDevId, int iMonitorHWBufferSize);
	bool RemoteMonitorBreakpoint();
	void ResetRemoteMonitorBreakpoint();

protected:

public:
// Attributes

// Overridable callbacks
protected:
	void OnClose(int nErrorCode);
	void CommunicationReport(wchar_t *string);
	void CommunicationReport(char *string);
	void OnListened(int nErrorCode);
	void OnAccept(int iSubDevId, int nErrorCode);

// Implementation
public:
};
/////////////////////////////////////////////////////////////////////////////////////////


class CDeviceMonitor;
class CMDeviceMonitor;
class CSWDevice;
class CUTKernelDevice;
class CSWEncoder;

class DRIVER_OEMPA_API_ALIGN _CSWEncoder
{
private:
	ULONGLONG m_ullPrivateMemory[20];
protected:

};

class DRIVER_OEMPA_API_ALIGN CSWEncoder :
	public _CSWEncoder
{
private:

public:
public:
	CSWEncoder(CSWDevice *pSWDevice);
	~CSWEncoder();
	int operator=(const CSWEncoder &a);
	bool operator==(const CSWEncoder &a) const;
	bool operator!=(const CSWEncoder &a) const;

//setting part
	bool Enable(bool bEnabled);//value could be negative if encoder need to be inverted.
	bool IsEnabled() const;

	bool lSetResolution(LONG lResolution);//this function is only for integer type resolution (the resolution divider is equal to 1).
	bool lSetResolution(LONG lResolution,DWORD dwDivider);//divider is useful for a double type resolution encoder. DoubleResolution=Resolution/Divider.
	LONG lGetResolution() const;
	DWORD GetDivider() const;
	bool dSetResolution(double dResolution);//it is the same than to call "ConvertResolution(dResolution,lResolution,dwDivider);" followed by "SetResolution(lResolution,dwDivider)"
	double dGetResolution() const;
	static bool ConvertResolution(double &dResolution,LONG &lResolution,DWORD &dwDivider);

	bool SetUnit(enumUnit eUnit);
	enumUnit GetUnit() const;

	bool SetType(enumEncoderType eEncoderType);
	enumEncoderType GetType() const;

	bool SetDigitalInput(enumFeatureDigitalInput eEncoderInput,enumDigitalInput eDigitalInput);
	enumDigitalInput GetDigitalInput(enumFeatureDigitalInput eEncoderInput) const;

//acquisition part
	bool SetSpeedDistance(double dValue);
	bool GetSpeedDistance(double &dValue) const;

	bool SetInspectionHWValue(int iValue);
	int GetInspectionHWValue() const;
	bool SetInspectionSWValue(double dValue);
	double GetInspectionSWValue() const;

	bool SetInspectionSpeed(double dValue);
	double GetInspectionSpeed() const;

	bool SetInspectionLength(double dValue);
	double GetInspectionLength() const;

	bool SetInspectionCount(int iValue);
	int GetInspectionCount() const;

private:

public:

private:
private:

public:
private:
};


enum CUTErrorType {
	CUTError_base,
	CUTError_communication_system_call,
	CUTError_communication_bad_data,
	CUTError_communication_keep_alive,
	CUTError_communication_driver_internal,
	CUTError_initialization_flash,
	CUTError_initialization_other,
	CUTError_settings_out_of_bound,
	CUTError_settings_not_permitted,
	CUTError_settings_invalid_operation,
	CUTError_settings_input_changed,	// This is not an error. It can be thrown by setter functions and tells an in/out argument change should be accounted by user app.
	CUTError_runtime_system_call,
	CUTError_runtime_driver_internal,
	CUTError_missed_data_encoder,
	CUTError_missed_data_frame
};
class DRIVER_OEMPA_API_ALIGN CUTError {
public:
	virtual const char * what() const;
	virtual const DWORD GetCode() const;	// Valid only for system_call error types, set to the corresponding return or errno value.
	virtual const CUTErrorType GetType() const;
	virtual const bool IsCustomData() const;
	virtual const double GetCustomData() const;
	CUTError();
};
class CHWDeviceOEMPA;
typedef DWORD(*pTypeCallbackError)(CHWDeviceOEMPA *pOEMPA, void* pAcqParam, const CUTError &error);


class DRIVER_OEMPA_API_ALIGN _CSWDevice
{
private:
	ULONGLONG m_ullPrivateMemory[664];
protected:

};

class DRIVER_OEMPA_API_ALIGN CSWDevice : public _CSWDevice
{
public:
protected:

public:
public:
	CSWDevice(CHWDevice *pHWDevice,enumHardware eDefaultHW,enumCommunication eCommunication);
	~CSWDevice();
	int operator=(const CSWDevice &a);
	bool operator==(const CSWDevice &a);
	bool operator!=(const CSWDevice &a);
	CSWEncoder *GetSWEncoder(int iEncoderIndex);
	const CSWEncoder *cGetSWEncoder(int iEncoderIndex) const;
	CHWDevice *GetHWDevice();
	const CHWDevice *cGetHWDevice() const;

//root ID management.
	bool SetBoardName(const wchar_t *pName);//to register this new data in the kernel database.
	bool GetBoardName(int iSize,wchar_t *pName);
protected:

public:

//Setting

	bool SetHardware(enumHardware eHW);
	enumHardware GetHardware() const;

	enumHardwareLink GetHardwareLink() const;
	/*!
	 * \brief Returns the state of the software link for this device.
	 * 
	 * See enum enumHardwareLink.
	 */
	enumHardwareLink GetSoftwareLink() const;
	/*!
	 * \brief Returns the device ID of the master. -1 if there is no master.
	 * 
	 * You can retrieve a pointer to the CHWDevice of the master with the 
	 * following function: static CHWDevice *GetHWDevice(int iDeviceId).
	 */
	int GetMasterDeviceIdSW();
	/*!
	 * \brief Link this device as a slave to another device.
	 * \param[in] iMasterId: device ID of the master device.
	 * 
	 * On success the software link of this device will be set to eSlave and 
	 * the software link of the master device will be set to eMaster.
	 * This function will fail if called on a master device, you have to unlink all 
	 * its slaves first, see SlaveConnectSW(int iMasterId). It will also fail if 
	 * 'iMasterId' device is a slave, you have to unlink it first.
	 * If this device was already linked to another master device, it is unlinked and 
	 * linked to the new master automatically.
	 */
	bool SlaveConnectSW(int iMasterId);
	/*!
	 * \brief Unlink this device.
	 * 
	 * Software link will be set to eUnlinked.
	 * If this was the last slave, the linked master device is also set to unlinked.
	 */
	bool SlaveDisconnectSW();
	/*!
	 * \brief Enables/Disables IO dispatch from master to slave(s).
	 * \param[in] bEnable: enable (true) or disable (false) IO dispatch.
	 * 
	 * This function will fail if called on an unlinked device.
	 * To link a device see bool SlaveConnectSW(int iMasterId).
	 * To get the link of a device see enumHardwareLink GetSoftwareLink() const.
	 * When called on a master, the IO dispatch is also enabled/disabled for all linked slaves.
	 * When called on a slave, the IO dispatch is also enabled/disabled for the master.
	 */
	bool EnableSWDispatchIO(bool bEnable);
	/*!
	 * \brief Returns the state of the SW dispatch IO.
	 */
	bool IsSWDispatchIO();

	bool SetCommunication(enumCommunication eCommunication);
	enumCommunication GetCommunication() const;

	bool GetConfigurationFilePath(bool bFlashName,wchar_t *pPathName,int iSize);//to find the configuration file path.
	bool GetConfigurationFilePath(wchar_t *pPathName,int iSize);//to find the configuration file path.

	bool GetSetupFileDefault(enumSetupFileType eFile, int iSize, wchar_t *wcFile);
	bool SetSetupFileCurrent(const wchar_t *wcFile);
	bool GetSetupFileCurrent(int iSize,wchar_t *wcFile);
	bool SetDriverSubFolder(const wchar_t *wcFile);//1.2.0.1e
	bool GetDriverSubFolder(int iSize,wchar_t *wcFile);//1.2.0.1e
	bool GetElementFile(int iSize,wchar_t *wcFile);//Dead elements.

	bool SetAcquisitionFlush(enumAcquisitionFlush eAcquisitionFlush);
	enumAcquisitionFlush GetAcquisitionFlush() const;

	bool SetConnectionState(enumConnectionState eConnection,bool bDisplayErrorMsg);
	enumConnectionState GetConnectionState() const;//for MatchedDevices: this function called for the master takes also into account the slave.
	bool IsConnected() const;//for MatchedDevices: this function called for the master takes also into account the slave.

	bool CheckProcessId();//only one process have ownership of the driver.

	bool SetCfgStatus(enumUpdateStatus eUpdateStatus);
	enumUpdateStatus GetCfgStatus() const;

	int SetStreamCount(int iCount);
	int GetStreamCount() const;
	int SetStreamDataSize(uint64_t ui64DataSize);
	uint64_t GetStreamDataSize() const;
	uint64_t GetStreamAscanSize() const;
	uint64_t GetStreamCscanSize() const;
	uint64_t GetStreamIOSize() const;
	int SetStreamRetransmit(int iCount);
	int GetStreamRetransmit() const;
	int SetStreamError(int iCount);
	int GetStreamError() const;

	int GetLostCountAscan() const;
	int SetLostCountAscan(int iDataLostCount);
	DWORD *GetLostCountAscanPtr();
	int GetLostCountCscan() const;
	int SetLostCountCscan(int iDataLostCount);
	int GetLostCountEncoder() const;
	int SetLostCountEncoder(int iDataLostCount);
	int GetLostCountUSB3() const;
	int SetLostCountUSB3(int iDataLostCount);
	int GetLostCountFifo(enumAcquisitionFifo eFifo) const;//data (ascan, cscan or IO) lost because the output speed to get data is too low.
	int GetErrorCountUSB3() const;
	int SetErrorCountUSB3(int iDataErrorCount);
	int GetLostCountPCIe() const;
	int SetLostCountPCIe(int iDataLostCount);
	int GetErrorCountPCIe() const;
	int SetErrorCountPCIe(int iDataErrorCount);
	int SetLostCountSocket(int iDataLostCount);
	int GetLostCountSocket() const;
	DWORD *GetLostCountSocketPtr();
	int SetLostCountUnexpectedPacket(int iDataLostCount);
	int GetLostCountUnexpectedPacket() const;
	DWORD *GetLostCountUnexpectedPacketPtr();
	int SetLostCountPacketFrameNumber(int iDataLostCount);
	int GetLostCountPacketFrameNumber() const;
	DWORD *GetLostCountPacketFrameNumberPtr();
	int GetStreamFormatError() const;
	int SetStreamFormatError(int iErrorCount);
	int SetErrorCountSocket(int iDataLostCount);
	int GetErrorCountSocket() const;
	int SetLostAssociation(int iDataLostCount);
	int GetLostAssociation() const;
	void ResetCounters();
	void DispatchCounters();

	//bool SetEncoderCount(int iCount);//0 1 or 2.
	int GetEncoderEnabledCount() const;
	void swProcessEncoder(structAcqInfoEx &acqInfo);

	bool EnablePulser(bool bEnable);
	bool IsPulserEnabled() const;

	int GetMaxCycleCount();//cycle count in the HW.

	void EnableSelection(bool bEnable);
	bool IsSelected();

protected:
	virtual bool IsInitFWMemory();

public:

	//Class "CHWDevice": current (for this device only)
	bool SetLockDisableShot(bool bDisable);
	bool GetLockDisableShot() const;
	bool SetUnlockEnableShot(bool bEnable);
	bool GetUnlockEnableShot() const;

	//Class "CHWDevice": in software configuration file (used as default for all devices)
	static bool SetLockDefaultDisablePulser(bool bDisable);
	static bool GetLockDefaultDisablePulser();
	static bool SetUnlockDefaultEnablePulser(bool bEnable);
	static bool GetUnlockDefaultEnablePulser();

	//Class "CSWDevice": functions management.
	void SetSWDeviceAcquisitionState(bool bLockNotUnlock, enumAcquisitionState eAcq);
	enumAcquisitionState GetSWDeviceAcquisitionState(bool bLockNotUnlock) const;
	void SetSWDeviceCheckSetupConsistancy(bool bLockNotUnlock, int iCheckSetupConsistancy);
	int GetSWDeviceCheckSetupConsistancy(bool bLockNotUnlock) const;

	bool SetAcqSpeedAscan(double dSpeed);
	double GetAcqSpeedAscan() const;
	bool SetAcqSpeedCscan(double dSpeed);
	double GetAcqSpeedCscan() const;
	bool SetAcqSpeedIO(double dSpeed);
	double GetAcqSpeedIO() const;

	void EnableAscanEncoder(bool bEnable);
	bool IsAscanEncoderEnabled();

	static void SetCallbackError(pTypeCallbackError func);
	static void EnableErrorReporting(bool enable);
	static bool IsErrorReportingEnabled();
	static void EnableMissedEncoderReporting(bool enable);
	static bool IsMissedEncoderReportingEnabled();
	static void EnableMissedFrameReporting(bool enable);
	static bool IsMissedFrameReportingEnabled();

	static void WriteCfgBool(const wchar_t *pSection,const wchar_t *pKey,bool bValue);
	static bool ReadCfgBool(const wchar_t *pSection,const wchar_t *pKey,bool bDefault,bool &bCreate);
	static int ReadCfgInt(const wchar_t *pSection,const wchar_t *pKey,int iDefault,bool &bCreate);
	static int ReadCfgInt(const wchar_t *pSection,const wchar_t *pKey,int iDefault);
	static void WriteCfgInt(const wchar_t *pSection,const wchar_t *pKey,int iValue);
	static void WriteCfgString(const wchar_t *pSection,const wchar_t *pKey,wchar_t *pValue);
	static bool ReadCfgString(const wchar_t *pSection,const wchar_t *pKey,const wchar_t *pDefault,wchar_t *pValue,int iSize,bool &bCreate);
	static DWORD ReadCfgDWordHexa(const wchar_t *pSection, const wchar_t *pKey, DWORD dwDefault, DWORD dwMin, DWORD dwMax, bool &bCreate);
	static void WriteCfgDWordHexa(const wchar_t *pSection, const wchar_t *pKey, DWORD dwValue);
	static DWORD ReadCfgDWord(const wchar_t *pSection, const wchar_t *pKey, DWORD dwDefault, DWORD dwMin, DWORD dwMax, bool &bCreate);
	static void WriteCfgDWord(const wchar_t *pSection, const wchar_t *pKey, DWORD dwValue);
	static double ReadCfgDouble(const wchar_t *pSection, const wchar_t *pKey, double dDefault, double dMin, double dMax, bool &bCreate);
	static void WriteCfgDouble(const wchar_t *pSection, const wchar_t *pKey, double dValue);
	static float ReadCfgFloat(const wchar_t *pSection, const wchar_t *pKey, float fDefault, float fMin, float fMax, bool &bCreate);
	static void WriteCfgFloat(const wchar_t *pSection, const wchar_t *pKey, float fDefault);
	static bool ReadCfgHexULONGLONG(const wchar_t *pSection, const wchar_t *pKey, ULONGLONG ullDefault, bool &bCreate, ULONGLONG &ullValue);
	static void WriteCfgHexULONGLONG(const wchar_t *pSection, const wchar_t *pKey, ULONGLONG ullDefault);
protected:

public:
};

/////////////////////////////////////////////////////////////////////////////////////////

class CHWDeviceOEMPA;

class DRIVER_OEMPA_API_ALIGN _CSWFilterOEMPA
{
private:
	ULONGLONG m_ullPrivateMemory[70];
public:

};

class DRIVER_OEMPA_API_ALIGN CSWFilterOEMPA : public _CSWFilterOEMPA
{
public:
protected:

public:
public:
	CSWFilterOEMPA();
	~CSWFilterOEMPA();
	int operator=(const CSWFilterOEMPA &a);
	bool operator==(const CSWFilterOEMPA &a) const;
	bool operator!=(const CSWFilterOEMPA &a) const;

	//easy way to use filter (predefined filters)
	bool SetFilter(enumOEMPAFilter eFilter);
	bool GetFilter(enumOEMPAFilter &eFilter) const;
	bool SetTitle(const wchar_t *pComment);//useful for custom filter.
	bool GetTitle(wchar_t *pComment,int iSize) const;

	//custom filter coefficient: functions used by the "CustomFilter" software.
	bool SetScale(WORD wScale);
	bool GetScale(WORD &wScale) const;
	bool SetCoefficientCount(int iCoefficientCount);
	bool GetCoefficientCount(int &iCoefficientCount) const;
	bool SetCoefficient(int iCoefficientIndex,short wValue);
	bool GetCoefficient(int iCoefficientIndex,short &wValue) const;
	bool SetFilter(WORD wScale,short *wValue/*[g_iOEMPAFilterCoefficientMax]*/,bool bUpdateHardware=true);//if you want to update all hardware filter, it is quicker to call "CSWDeviceOEMPA1::UpdateAllFilter" at the end and before to call "SetFilter" with "bUpdateHardware=false" for all filters.
	bool GetFilter(WORD &wScale,short *wValue/*[g_iOEMPAFilterCoefficientMax]*/) const;
	bool SetArrayCoefficient(int iCoefficientCount,short *pwValue);
	bool GetArrayCoefficient(int iCoefficientCount,short *pwValue) const;

	void SetSampleFrequency(double dValue);
	double GetSampleFrequency() const;
protected:

public:
};

class DRIVER_OEMPA_API_ALIGN _CSWDeviceOEMPA

{
private:
	ULONGLONG m_ullPrivateMemory[432];
public:

};

class DRIVER_OEMPA_API_ALIGN CSWDeviceOEMPA : public _CSWDeviceOEMPA, public CSWDevice
{
//pure virtual function have to be instantiated for each device.
public:
#ifndef _DRIVER_11XY_
#include "Struct_SWDeviceOEMPA.h"
#endif //_DRIVER_11XY_

	CSWDeviceOEMPA(CHWDevice *pHWDevice,enumHardware eDefaultHW,enumCommunication eCommunication);
	~CSWDeviceOEMPA();
	void Constructor(int iFilterCount,enumOEMPAFilter eFilter,int iCoefficientCount,short *psDefaultFilter,wchar_t *pDefaultTitle);

	static bool SetDefaultHardware(enumHardware eHW);
	static enumHardware GetDefaultHardware();

	virtual const wchar_t *GetConnectedName() const=0;//useful for multiprocess

	CSWFilterOEMPA& Filter(int iFilterIndex);
	virtual int GetFilterCount();

	virtual bool IsPulserEnabled();

//To manage address of connection
//Example in case of ethernet: "192.168.1.11:5001"
	virtual bool SetAddress(const wchar_t *pValue)=0;
	virtual const wchar_t* GetAddress(int iSubDevId = 0) const=0;

//USB3
	virtual bool IsUSB3Connected();
	virtual CUTUsb3Device *GetUSB3Device();

	virtual bool GetSerialNumber(wchar_t *pSN,int iSize) const=0;
	virtual bool GetSystemType(wchar_t *pType,int iSize) const=0;
	virtual int GetRXBoardCount() const;
	virtual enumMCType GetMCType();
	/*
	* Returns the max high voltage value for this device.
	* -1 (0xffffffff) means that the high voltage control is disabled.
	*/
	virtual DWORD GetHighVoltageMax() const;

	virtual int GetApertureCountMax() const=0;//to get the maximum element count of an aperture.
	virtual int GetElementCountMax() const=0;//to get the maximum element count of the system (in case of mux).
	virtual int GetPACycleCountMax() const=0;//to get the maximum cycle count for standard phased array.
	virtual int GetFMCCycleCountMax() const=0;//to get the maximum cycle count for FMC.

	virtual const double dGetClockPeriod() const=0;//second
	virtual const float fGetClockPeriod() const=0;//second
	virtual const LONG lGetClockFrequency() const=0;//Hz

	virtual const float fFocussingDelayStepEmission() const=0;//second
	virtual const float fFocussingDelayStepReception() const=0;//second

	virtual WORD GetFirmwareId() const=0;
	virtual DWORD GetAWGFirmwareId() const=0;

	virtual int GetCycleCountMax() const=0;
	virtual bool IsFullMatrixCapture() const=0;//FMC could be enabled or disabled.
	virtual bool IsFullMatrixCaptureReadWrite() const=0;//FMC bit could be Read/Write or Read only (for old FMC FW: FMC bit is not read only).
	virtual bool GetFMCElement(int &iElementStart,int &iElementStop,int &iElementStep) const=0;
	virtual bool IsMultiHWChannelSupported() const;
	virtual bool IsTemperatureAlarmSupported() const=0;
	virtual bool IsMultiHWChannelEnabled() const;
	virtual bool IsMatrixAvailable() const=0;
	virtual bool IsLabviewAvailable() const=0;
	virtual bool IsTpacquisitionAvailable() const=0;
	virtual bool IsWTSWAvailable() const=0;
	virtual bool IsMatlabAvailable() const=0;
	virtual bool IsTFMAvailable() const;
	virtual bool IsEncoderDecimal() const=0;
	virtual bool IsFMCElementStepSupported() const=0;
	virtual bool IsFMCSubTimeSlotPerCycleSupported() const=0;
	virtual bool IsAWGSupported() const = 0;
	virtual bool IsNegativeSquarePulseAvailable() const;

	virtual bool SetKeepAlive(enumKeepAlive eKeepAlive)=0;
	virtual enumKeepAlive GetKeepAlive() const=0;

	virtual bool EnableAscan(bool bEnable)=0;
	virtual bool IsAscanEnabled() const=0;

	virtual bool SetAscanBitSize(enumBitSize eBitSize)=0;
	virtual enumBitSize GetAscanBitSize() const=0;

	virtual bool SetAscanRequest(enumAscanRequest eAscanRequest)=0;
	virtual enumAscanRequest GetAscanRequest() const=0;

	virtual bool SetAscanRequestFrequency(double dFreq)=0;//Hz
	virtual bool GetAscanRequestFrequency(double &dFreq) const=0;

	virtual bool EnableCscanTof(bool bEnable)=0;
	virtual bool IsCscanTofEnabled() const=0;

	virtual bool SetCycleCount(int iCount);
	virtual int GetCycleCount() const;

protected:
	virtual int GetApertureCountMax(WORD wSystemType) const = 0;
	virtual int GetElementCountMax(WORD wSystemType) const = 0;
	virtual bool IsInitFWMemory();

public:

	virtual bool SetTriggerMode(enumOEMPATrigger eTrig);
	virtual enumOEMPATrigger GetTriggerMode() const;
	virtual bool EnableSubSequenceEncoder(bool bEnable);
	virtual bool IsSubSequenceEncoderEnabled() const;
	virtual bool EnableSubSequenceGate(bool bEnable);
	virtual bool IsSubSequenceGateEnabled() const;

	virtual bool SetTriggerEncoderStep(double dStep)=0;
	virtual bool GetTriggerEncoderStep(double &dStep) const=0;

	virtual bool SetSignalTriggerHighTime(double dTime)=0;
	virtual double GetSignalTriggerHighTime() const=0;

	virtual bool SetRequestIO(enumOEMPARequestIO eRequest)=0;
	virtual enumOEMPARequestIO GetRequestIO() const=0;

	virtual bool SetRequestIODigitalInputMaskRising(int iMask)=0;
	virtual bool GetRequestIODigitalInputMaskRising(int &iMask) const=0;

	virtual bool SetRequestIODigitalInputMaskFalling(int iEvent)=0;
	virtual bool GetRequestIODigitalInputMaskFalling(int &iEvent) const=0;

	virtual bool SetExternalTriggerCycle(enumDigitalInput eDigitalInput)=0;
	virtual bool GetExternalTriggerCycle(enumDigitalInput &eDigitalInput) const=0;

	virtual bool SetExternalTriggerSequence(enumDigitalInput eDigitalInput)=0;
	virtual bool GetExternalTriggerSequence(enumDigitalInput &eDigitalInput) const=0;

	virtual bool SetExternalResetEncoder1(enumDigitalInput eDigitalInput);
	virtual bool GetExternalResetEncoder1(enumDigitalInput &eDigitalInput) const;
	virtual bool SetExternalResetEncoder2(enumDigitalInput eDigitalInput);
	virtual bool GetExternalResetEncoder2(enumDigitalInput &eDigitalInput) const;

	virtual bool SetExternalTimestampReset(enumDigitalInput eDigitalInput);
	virtual bool GetExternalTimestampReset(enumDigitalInput &peDigitalInput) const;

	virtual bool SetExternalEncoderReset(enumDigitalInput eDigitalInput);
	virtual bool GetExternalEncoderReset(enumDigitalInput &peDigitalInput) const;

	virtual bool SetExternalTrackingReset(enumDigitalInput eDigitalInput);
	virtual bool GetExternalTrackingReset(enumDigitalInput &peDigitalInput) const;

	virtual bool SetMappingOutput(int iOutputIndex,enumOEMPAMappingDigitalOutput eMapping)=0;
	virtual bool GetMappingOutput(int iOutputIndex,enumOEMPAMappingDigitalOutput &eMapping) const=0;
	virtual bool SetMappingOutput(int iOutputIndex, enumOEMPAMiniMappingDigitalIO eMapping) = 0;
	virtual bool GetMappingOutput(int iOutputIndex, enumOEMPAMiniMappingDigitalIO &eMapping) const = 0;

	virtual bool SetRequestCscan(enumOEMPARequestCscan eRequest)=0;
	virtual enumOEMPARequestCscan GetRequestCscan() const=0;

	virtual bool SetEncoderDebouncer(double dTime)=0;
	virtual double GetEncoderDebouncer() const=0;

	virtual WORD GetDigitalInput() const=0;//return the general purpose digital inputs state coming from the HW (binary value).
	virtual DWORD GetDigitalInput32() const;//return the general purpose digital inputs state coming from the HW (binary value). Works for both PIO and MIO. Only for MC2 and MCuF.

	virtual bool SetDigitalDebouncer(double dTime)=0;
	virtual double GetDigitalDebouncer() const=0;

	virtual bool SetMultiSystemDebouncer(double dTime)=0;
	virtual double GetMultiSystemDebouncer() const=0;

	virtual bool ResetEncoder()=0;

	//following function can be used while pulser are off.
	virtual bool GetTemperatureCount(int &iBoardCount,int &iSensorCountMax) const=0;//SensorCount is not the same for each board.
	virtual bool GetHumidityCount(int& iBoardCount, int& iSensorCountMax) const;//SensorCount is not the same for each board.
	virtual bool GetTemperatureSensorCount(int iBoardIndex,int &iSensorCount) const=0;//SensorCount is not the same for each board.
	virtual bool GetHumiditySensorCount(int iBoardIndex, int& iSensorCount) const;//SensorCount is not the same for each board.
	virtual int GetTemperature(int iBoardIndex,int iSensorIndex,float &fValue) const=0;
	virtual int SetArrayTemperature(int iBoardIndex,int iSensorCount,float *pfValue)=0;
	virtual int GetArrayTemperature(int iBoardIndex,int iSensorCount,float *pfValue) const=0;
	//following function can be used while pulser are on.
	virtual bool GetTemperatureMax(float &fValue)=0;

	virtual bool IsIOBoardEnabled() const=0;
	virtual bool IsOEMMCEnabled() const;//value in the flash (different than value in the register).
	virtual double GetPulserPowerMax() const;//Unit Watt
	virtual double GetPulserPowerCurrent() const;//Unit Watt (in case of association: max of all subdevices).
	virtual double GetPulserPowerSubDevice(int iSubDevice = -1) const;//Unit Watt, -1 means all subdevices (sum).
	virtual BYTE GetFlashUSB3Version() const;
	virtual DWORD GetFWUSB3Version() const;
	virtual bool EnableUSB3(bool bEnable);
	virtual bool IsUSB3Enabled() const;
	virtual DWORD GetMBOptions() const;
	virtual enumOEMPAAnalogBandwidth GetAnalogBandwidth() const;
	virtual bool IsSeparatedMux() const;
	virtual bool IsPIOBoard() const;
	virtual int GetIOCountMax() const;
	virtual bool IsSwitchMux() const;

#ifndef _DRIVER_11XY_
	virtual bool GetEmbeddedVersion(structVersion &version) const;
	virtual bool GetOptionsCom(structOptionsCom &optionsCom) const;
	virtual bool GetOptionsTCP(structOptionsTCP &optionsTCP) const;
	virtual bool GetOptionsFlash(structOptionsFlash &optionsFlash) const;
#endif //_DRIVER_11XY_
	virtual int GetPasscodeCount() const=0;
	virtual bool GetPasscode(int iIndex,DWORD &dwPasscode) const=0;
	virtual double GetMaximumThroughput() const=0;//Unit is Bytes/second.
	double GetThroughput() const;//Unit is Bytes/second.

	virtual bool UpdateAllFilter();//to update all hardware filters at the same time.

	static void EnableMultiChannel(bool bEnable);//you need to restart the sw to take the new value in account. "CUTChannels::SetDefaultMultiChannels" is the same.
	static bool IsMultiChannelEnabled();
	static void EnableLoadDefaultSetup(bool bEnable);//you need to restart the sw to take the new value in account. "CUTPreference::SetDefaultSetupAuto" is the same.
	static bool IsLoadDefaultSetupEnabled();

	virtual bool IsCycleOrderSupported() const;
	virtual bool IsAWGPulseSupported() const;
	virtual bool IsAWGPulseEnabled() const;
	//calibration management
	virtual bool IsSubSequenceAverageSupported() const;
	virtual bool IsTimeOffsetSupported() const;
	virtual bool EnableAlignment(bool bEnable);
	virtual float GetCalibrationAlignment();//maximum correction.
	virtual float GetCalibrationOffset();//required value after calibration has been performed.
	virtual bool IsCalibrationPerformed();//same than "IsAlignmentPerformed"
	virtual bool IsAlignmentPerformed();
	virtual bool IsAlignmentEnabled();
	virtual bool ResetAlignment();

	virtual void SetCalibrationParameters(float fWidth,float fStart,float fRange,float fGainAnalog,double dGainDigital);
	virtual void GetCalibrationParameters(float &fWidth,float &fStart,float &fRange,float &fGainAnalog,double &dGainDigital);
	virtual void SetCalibrationFileReport(const wchar_t *wcFileReport);
	virtual bool GetCalibrationFileReport(int iSizeMax,wchar_t *wcFileReport);

	//The calibration time offset is internally added to RecoveryTimes.
	virtual bool SetTimeOffset(float fTimeOffset)=0;
	virtual float GetTimeOffset()=0;//current value used to correct time axis.

	virtual double GetPulserPower(int iCycleCount, structCycleParameter *aCycleParameter, structCycleParameterPA *aCycleParameterPA, int *piSubDevId = NULL) const;//Unit Watt

	virtual void EnableEmissionDeadElement(bool bEnable) = 0;
	virtual bool IsEmissionDeadElementEnabled() = 0;
	virtual void ResetEmissionDeadElements() = 0;
	virtual bool SetEmissionDeadElements(int iElementSize, bool* pbEnable) = 0;
	virtual bool SetEmissionDeadElement(int iElementIndex, bool bEnable) = 0;
	virtual bool GetEmissionDeadElements(int iElementCountMax, int& iElementCount, int* iElementList) = 0;
	virtual void EnableReceptionDeadElement(bool bEnable) = 0;
	virtual bool IsReceptionDeadElementEnabled() = 0;
	virtual bool IsReceptionDeadElement(int iElementIndex) = 0;
	virtual void ResetReceptionDeadElements() = 0;
	virtual bool SetReceptionDeadElements(int iElementSize, bool* pbEnable) = 0;
	virtual bool SetReceptionDeadElement(int iElementIndex, bool bEnable) = 0;
	virtual bool GetReceptionDeadElements(int iElementCountMax, int& iElementCount, int* iElementList) = 0;
	virtual void EnableNormalisationEmission(bool bEnable) = 0;
	virtual void EnableNormalisationReception(bool bEnable) = 0;
	virtual bool IsNormalisationEmissionEnabled() = 0;
	virtual bool IsNormalisationReceptionEnabled() = 0;
	virtual bool SetNormalisationEmissionDelay(int iElementIndex, float fDelay) = 0;
	virtual bool SetNormalisationReceptionDelay(int iElementIndex, float fDelay) = 0;
	virtual bool SetNormalisationEmissionDelays(int iElementSize, float* pfDelay) = 0;
	virtual bool SetNormalisationReceptionDelays(int iElementSize, float* pfDelay) = 0;
	virtual bool IsReceptionDeadElementFifoOutEnabled();
	virtual bool IsReceptionDeadElementFifoOut(int iElementIndex);

	//For OEM-MC or OEM-PA (VF).
	virtual void EnablePulserDuringReplay(bool bEnable)=0;
	virtual bool IsPulserDuringReplayEnabled()=0;
	virtual bool EnableCscanTimeOfFlightCorrection(bool bEnable)=0;
	virtual bool IsCscanTimeOfFlightCorrectionEnabled()=0;
	virtual bool GetCscanTimeOfFlightCorrection(int iCycle,BYTE &byDecimation,float &fAscanStart)=0;//decimation range is 1..16.
	virtual bool SetCscanTimeOfFlightCorrection(int iCycle,BYTE byDecimation,float fAscanStart)=0;//decimation range is 1..16.

	virtual double GetFWAscanRecoveryTime();
	virtual double GetFMCSubCycleRecoveryTime();
	virtual double GetFMCCycleRecoveryTime();

	virtual bool Enable256(bool bEnable);
	virtual bool Is256Enabled() const;

	virtual DWORD GetHWTimeLimitation()=0;
	virtual char cGetHWTimeLimitation()=0;

	virtual DWORD GetSettingId()=0;

	virtual bool GetErrorCountString(wchar_t *wcString, int iSize) const;
	virtual bool vf_GetTransitSharedMemory(int64_t &i64BufferSize);

	void ConvertPointCount(int iCycle, long &lValue);
	
	bool SetGateStart(int iCycle, int iGate, double dStart);
	bool SetGateStart(int iCycle, int iChannel, int iGate, double dStart);
	bool SetGateStart(int iCycle, int iGate, double dStart, enumGateTarget eTarget);
	bool GetGateStart(int iCycle, int iGate, double &dStart);
	bool GetGateStart(int iCycle, int iGate, double &dStart, enumGateTarget &eTarget);
	bool GetGateStart(int iCycle, int iChannel, int iGate, double& dStart);
	bool SetGateWidth(int iCycle, int iGate, double dWidth);
	bool SetGateWidth(int iCycle, int iGate, double dWidth, enumGateTarget eTarget);
	bool GetGateWidth(int iCycle, int iGate, double &dWidth);
	bool GetGateWidth(int iCycle, int iGate, double &dWidth, enumGateTarget &eTarget);
	bool GetGateWidth(int iCycle, int iGate, bool &bWidth);
	bool SetGateStop(int iCycle, int iGate, double dStop);
	bool SetGateStop(int iCycle, int iChannel, int iGate, double dStop);
	bool SetGateStop(int iCycle, int iGate, double dStop, enumGateTarget eTarget);
	bool GetGateStop(int iCycle, int iGate, double &dStop);
	bool GetGateStop(int iCycle, int iChannel, int iGate, double &dStop);
	bool GetGateStop(int iCycle, int iGate, double &dStop, enumGateTarget &eTarget);
	bool SetGateModeThreshold(int iCycle, int iGate, bool bEnable, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification, double dThresholdPercent);
	bool SetGateModeThreshold(int iCycle, int iGate, bool bEnable, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification, double dThresholdPercent, unsigned int uMultiPeakCountMax, double dMultiPeakExclusionInterval);
	bool SetGateModeThreshold(int iCycle, int iChannel, int iGate, bool bEnable, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification, double dThresholdPercent);
	bool SetGateModeThreshold(int iCycle, int iGate, bool bEnable, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification, double dThresholdPercent, enumGateTarget eTarget);
	bool SetGateModeThreshold(int iCycle, int iGate, bool bEnable, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification, double dThresholdPercent, enumGateTarget eTarget, unsigned int uMultiPeakCountMax, double dMultiPeakExclusionInterval);
	bool GetGateModeThreshold(int iCycle, int iGate, bool &bEnable, enumGateModeAmp &eGateModeAmp, enumGateModeTof &eGateModeTof, enumRectification &eGateRectification, double &dThresholdPercent);
	bool GetGateModeThreshold(int iCycle, int iGate, bool& bEnable, enumGateModeAmp& eGateModeAmp, enumGateModeTof& eGateModeTof, enumRectification& eGateRectification, double& dThresholdPercent, unsigned int& uMultiPeakCountMax, double& dMultiPeakExclusionInterval);
	bool GetGateModeThreshold(int iCycle, int iGate, bool &bEnable, enumGateModeAmp &eGateModeAmp, enumGateModeTof &eGateModeTof, enumRectification &eGateRectification, double &dThresholdPercent, enumGateTarget &eTarget);
	bool GetGateModeThreshold(int iCycle, int iGate, bool& bEnable, enumGateModeAmp& eGateModeAmp, enumGateModeTof& eGateModeTof, enumRectification& eGateRectification, double& dThresholdPercent, enumGateTarget& eTarget, unsigned int& uMultiPeakCountMax, double& dMultiPeakExclusionInterval);
	bool GetGateModeThreshold(int iCycle, int iChannel, int iGate, bool& bEnable, enumGateModeAmp& eGateModeAmp, enumGateModeTof& eGateModeTof, enumRectification& eGateRectification, double& dThresholdPercent);
	bool SetGateAcqIDAmp(int iCycle, int iGate, WORD wID);
	bool GetGateAcqIDAmp(int iCycle, int iGate, WORD& wID);
	bool SetGateAcqIDTof(int iCycle, int iGate, WORD wID);
	bool GetGateAcqIDTof(int iCycle, int iGate, WORD& wID);
	bool SetTrackingGateStart(int iCycle, int iGate, bool bEnable, int iTrackingCycleIndex, int iTrackingGateIndex);
	bool SetTrackingGateStart(int iCycle, int iChannel, int iGate, bool bEnable, int iTrackingCycleIndex, int iTrackingChannelIndex, int iTrackingGateIndex);
	bool GetTrackingGateStart(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	bool GetTrackingGateStart(int iCycle, int iChannel, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	bool GetTrackingGateStart(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex, enumGateTarget &source);
	bool SetSWTrackingGateStartFromHW(int iCycle, int iGate, bool bEnable, int iTrackingCycleIndex, int iTrackingGateIndex);
	bool SetTrackingGateStop(int iCycle, int iGate, bool bEnable, int iTrackingCycleIndex, int iTrackingGateIndex);
	bool SetTrackingGateStop(int iCycle, int iChannel, int iGate, bool bEnable, int iTrackingCycleIndex, int iTrackingChannelIndex, int iTrackingGateIndex);
	bool GetTrackingGateStop(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	bool GetTrackingGateStop(int iCycle, int iChannel, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	bool SetSWTrackingGateStopFromHW(int iCycle, int iGate, bool bEnable, int iTrackingCycleIndex, int iTrackingGateIndex);
	bool ResetTrackingTable();
	bool SetTrackingDac(int iCycle, bool bEnable, int iTrackingCycleIndex, int iTrackingGateIndex);
	bool SetTrackingDac(int iCycle, int iChannel, bool bEnable, int iTrackingCycleIndex, int iTrackingChannelIndex, int iTrackingGateIndex);
	bool GetTrackingDac(int iCycle, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	bool GetTrackingDac(int iCycle, int iChannel, bool& bEnable, int& iTrackingCycleIndex, int& iTrackingChannelIndex, int& iTrackingGateIndex);
	bool SetTrackingAscan(int iCycle, bool bEnable, int iTrackingCycleIndex, int iTrackingGateIndex);
	bool SetTrackingAscan(int iCycle, int iChannel, bool bEnable, int iTrackingCycleIndex, int iTrackingChannelIndex, int iTrackingGateIndex);
	bool GetTrackingAscan(int iCycle, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	bool GetTrackingAscan(int iCycle, int iChannel, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);

	bool EnableSelection(int iCycleIndex, bool bEnable);
	bool IsSelectionEnabled(int iCycleIndex, bool &bEnable) const;

	bool EnableCalibration(int iCycleIndex, bool bEnable);
	bool IsCalibrationEnabled(int iCycleIndex, bool &bEnable) const;

	bool SetBeamCorrection(int iCycle, float fValue);
	bool GetBeamCorrection(int iCycle, float &fValue) const;
	bool SetBeamCorrection(int iCycle, int iChannel, float fValue);
	bool GetBeamCorrection(int iCycle, int iChannel, float& fValue) const;
	bool SetBeamCorrection(int iCycleIndex, bool bEnable);
	bool SetBeamCorrection(int iCycleIndex, int iChannel, bool bEnable);
	bool GetBeamCorrection(int iCycleIndex, bool &bEnable) const;
	bool GetBeamCorrection(int iCycleIndex, int iChannel, bool &bEnable) const;
	bool ResetBeamCorrection(int iCycleIndex);

	const structCycleParameter *cGetCycleParameter(int &iSize) const;
	const structCycleParameterMC *cGetCycleParameterMC(int &iSize) const;
	const structCycleParameterPA *cGetCycleParameterPA(int &iSize) const;

	void EnableCscan(enumCycleCscan eCscan, bool bEnable);
	bool IsCscanEnabled(enumCycleCscan eCscan) const;
	void ResetCscan(enumCycleCscan eCscan, int iCycle, int iGate);

	bool SetAscanStart(int iCycle, double dStart);
	bool SetAscanStart(int iCycle, int iChannel, double dStart);
	bool SetAscanRange(int iCycle, double dRange);
	bool SetAscanRange(int iCycle, int iChannel, double dRange);
	bool SetEmissionWedgeDelay(int iCycle, double dWedgeDelay);
	bool SetEmissionWedgeDelay(int iCycle, int iChannel, double dWedgeDelay);
	bool SetReceptionWedgeDelay(int iCycle, double dWedgeDelay);
	bool SetReceptionWedgeDelay(int iCycle, int iChannel, double dWedgeDelay);

	bool GetAscanStart(int iCycle, double &dStart);
	bool GetAscanStart(int iCycle, int iChannel, double &dStart);
	bool GetAscanRange(int iCycle, double &dRange);
	bool GetAscanRange(int iCycle, int iChannel, double &dRange);
	bool GetEmissionWedgeDelay(int iCycle, double &dWedgeDelay);
	bool GetEmissionWedgeDelay(int iCycle, int iChannel, double &dWedgeDelay);
	bool GetReceptionWedgeDelay(int iCycle, double &dWedgeDelay);
	bool GetReceptionWedgeDelay(int iCycle, int iChannel, double &dWedgeDelay);

#ifdef CYCLE_ORDERING
	bool EnableCycleOrder(bool bEnable);
	bool IsCycleOrderEnabled();
	bool SetCycleOrder(int iCycleOrderCount, int *piCycleOrder);
	bool GetCycleOrder(int iCycleOrderCountIn, int &iCycleOrderCountOut, int *piCycleOrder);
	bool EnableAveraging(bool bEnable);
	bool IsAveragingEnabled();
#endif //CYCLE_ORDERING
	/*
	* \brief Enable/disable envelope processing.
	* 
	* For advanced settings see bool EnableEnvelope(bool bEnable, float zeroPad = 0, enumSimdDataType eDataType = eAVX, unsigned iThreadCount = 1, int position = -1);
	* The complexity of the envelope algorithm is O(N . logN).
	* 
	* \param[in] bEnable: true = enabled, false = disabled.
	*/
	bool EnableEnvelope(bool bEnable);
	/*
	* \brief Enable/disable envelope processing.
	* 
	* To optimize the throughput it is possible to parallelize the envelope computation using SIMD instructions and multiple threads.
	* Today (02/2025) AVX512 is only available on AMD processors and doesn't provide much improvement over AVX unless very high data througput (typically above 300 MB/s).
	* Up to 16 threads can be used to compute the envelope but the performance gain is not linear with the number of threads and the gain above 8 threads is marginal.
	* Tested on AMD Ryzen 9 7950X3D.
	* 
	* Multiple post processing tasks can be active at the same time, if it is the case 
	* they will be chained and the output buffer will be the input buffer of the next task if applicable.
	* 
	* \param[In] zeroPad: amount of zeroes (pointCount * zeroPad) appended to the signal when processing the envelope. 0 <= zeroPad <= 1. 
	* \param[In] eDataType: size of the simd vector for parallel processing, eFloat: 1, eSSE: 4, eAVX: 8, eAVX512: 16 parallel ascans.
	* \param[In] iThreadCount: number of threads used to compute the envelope. Max 16 threads.
	* \param[In] position: position of this task in the task list. -1 means the last position.
	*/
	bool EnableEnvelope(bool bEnable, float zeroPad, enumSimdDataType eDataType = eAVX, unsigned iThreadCount = 1, int position = -1);
	bool IsEnvelopeEnabled();
	/*
	* \brief Enable/disable software gates.
	*
	* For advanced settings see bool EnableSWGates(bool bEnable, enumSimdDataType eDataType = eAVX, unsigned iThreadCount = 1, int position = -1);
	*
	* \param[in] bEnable: true = enabled, false = disabled.
	*/
	bool EnableSWGates(bool bEnable);
	bool EnableSWGates(bool bEnable, enumSimdDataType eDataType = eAVX, unsigned iThreadCount = 1, int position = -1);
	bool IsSWGatesEnabled();
	/*
	* \brief Enable/disable software upsampling.
	*
	* For advanced settings see bool EnableUpsampling(bool bEnable, int upsamplingFactor, enumSimdDataType eDataType = eFloat, unsigned iThreadCount = 1, int position = -1);
	* Allows to increase the frequency of the signal by a given factor.
	* The base frequency is 100MHz in phased array and 50MHz in FMC mode.
	* This function only allows multiple of the base frequency as upsampled frequency.
	* It is possible to reduce the base frequency by enabling decimation in the firmware to achieve intermediate values 
	*	(e.g. decimate to 50MHz and upsample with a factor of 5 for 250MHz).
	* The complexity of the upsampling algorithm is linear with the number of points in the ascan and the upsampling factor.
	*
	* \param[in] bEnable: true = enabled, false = disabled.
	* \param[in] upsamplingFactor: upsampling factor. Frequency = base frequency * upsampling factor.
	*/
	bool EnableUpsampling(bool bEnable, unsigned upsamplingFactor);
	bool EnableUpsampling(bool bEnable, unsigned upsamplingFactor, enumSimdDataType eDataType = eFloat, unsigned iThreadCount = 1, int position = -1);
	bool IsUpsamplingEnabled();
	/* 
	* Release memory and threads used for post processing tasks such as the envelope. 
	* Disabling all tasks only pauses the process, use this function to release the memory.
	*/
	void StopPostProcessing();
	/*
	* \brief Sets the data type for all post processing tasks.
	*
	* SIMD data types allows processing of multiple ascans in parallel to increase efficiency.
	* By default the most advanced instruction set will be selected when enabling a post processing task.
	* The function will return false and have no effect if the data type is not supported by the processor.
	* Possible values are:
	*	eFloat: 1 ascan
	*	eSSE:	4 ascans
	*	eAVX:	8 ascans
	*	eAVX512: 16 ascans (only available on modern AMD processors).
	*
	* \param[in] eDataType: size of the simd vector for parallel processing.
	*/
	bool SetPostProcessingDataType(enumSimdDataType eDataType);
	/*
	* \brief Sets the number of parallel threads for all post processing tasks.
	*
	* Modern CPUs have multiple processors that can efficiently parallelize high complexity algorithms.
	* By default 8 workers threads are cerated when enabling a post processing task.
	* This number can be increased up to 16 if your CPU has enough cores, having more threads than CPU cores won't increase the efficiency.
	*
	* \param[in] iThreadCount: number of parallel threads, range is 1 to 16.
	*/
	bool SetPostProcessingThreadCount(unsigned iThreadCount);
protected:
#ifdef CYCLE_ORDERING
#endif //CYCLE_ORDERING
	virtual double vf_GetFWClockPeriod() const;
	virtual bool vf_DumpPerformance();
#ifdef GAIN_ANALOG_CORRECTION_TABLE
#endif //GAIN_ANALOG_CORRECTION_TABLE

public:
	enumAcquisitionMode GetAcquisitionMode();
	ULONGLONG GetReplaySequenceBreakpoint();
	ULONGLONG GetReplaySequenceLast();
	virtual bool vf_SetAcquisitionMode(enumAcquisitionMode eMode);
	bool SetReplaySequenceBreakpoint(ULONGLONG ullSequence);
	bool SetReplaySequenceLast(ULONGLONG ullSequence);
	void UpdatePulserPower();
	bool CheckPulserPower(int *piSubDeviceId = NULL);
	bool SetPulserPowerMax(WORD wPulserPowerMax);
	const structOEMPACycleGate *cGetCycleGate(int iCycleIndex) const;
	const structOEMPACycleCscan *cGetCycleCscan(enumCycleCscan eType, int iCycleIndex) const;
	bool UpdateCycleParameter(CHWDeviceOEMPA *pHWDeviceOEMPA, int iCycleIndex);
	bool UpdateCycleParameter2(CHWDeviceOEMPA *pHWDeviceOEMPA, int iCycleIndex, const structCycleParameter &params);//MERGE_PAMINI_PAMAX_MC weird
	structCycleParameter *GetCycleParameter(int &iSize);
	structCycleParameterMC *GetCycleParameterMC(int &iSize);
	structCycleParameterPA *GetCycleParameterPA(int &iSize);
	structOEMPACycleGate *GetCycleGate(int iCycleIndex);
	structOEMPACycleCscan *GetCycleCscan(enumCycleCscan eType, int iCycleIndex);

	float Convert(double dValue, double dStep, float fStep);
	DWORD ConvertTimeDoubleToDword(double dValue) const;
	long ConvertTimeDoubleToLong(double dValue) const;
	double ConvertTimeDwordToDouble(DWORD dwValue) const;
	double ConvertTimeLongToDouble(long lValue) const;
	struct structProcessGate {
		long lGateStart;
		long lGateStop;
		long lGateThreshold;
		bool bValid;
	};
	int ProcessAscanCscan(enumRectification eGateRectification, enumBitSize eSize, int cycle, int array_size, const void* pAscan, CSubStreamCscan_0x0302 *pHeader, structCscanAmpTof_0x0302 aData[g_iOEMPAGateCountMax]);
	// 32bit TOF
	int ProcessAscanCscan(enumRectification eGateRectification, enumBitSize eSize, int cycle, int array_size, const void* pAscan, CSubStreamCscan_0x0302 *pHeader, structCscanAmpTof_0x0502 aData[g_iOEMPAGateCountMax]);
	int ProcessAscan(enumRectification eGateRectification, enumBitSize eSize, int cycle, int array_size, const void* pAscan, structProcessGate aGate[g_iOEMPAGateCountMax]);//long alGateStart[g_iOEMPAGateCountMax], long alGateStop[g_iOEMPAGateCountMax], long alGateThreshold[g_iOEMPAGateCountMax]);
	int ProcessAscanSigned0(enumRectification eGateRectification, enumBitSize eSize, int cycle, int array_size, const void* pAscan, structProcessGate aGate[g_iOEMPAGateCountMax]);//long alGateStart[g_iOEMPAGateCountMax], long alGateStop[g_iOEMPAGateCountMax], long alGateThreshold[g_iOEMPAGateCountMax]);
	int ProcessAscanSigned1(enumRectification eGateRectification, enumBitSize eSize, int cycle, int array_size, const void* pAscan, structProcessGate aGate[g_iOEMPAGateCountMax]);//long alGateStart[g_iOEMPAGateCountMax], long alGateStop[g_iOEMPAGateCountMax], long alGateThreshold[g_iOEMPAGateCountMax]);
	int ProcessAscanUnsigned(enumRectification eGateRectification, enumBitSize eSize, int cycle, int array_size, const void* pAscan, structProcessGate aGate[g_iOEMPAGateCountMax]);//long alGateStart[g_iOEMPAGateCountMax], long alGateStop[g_iOEMPAGateCountMax], long alGateThreshold[g_iOEMPAGateCountMax]);
#ifdef CYCLE_ORDERING
	bool ProcessAscanAveraging(int iSigned, enumBitSize eBitSize, int cycle, structSubCycleOrder wSubCycle, int array_size, void* &pAscan/*input/output*/);
#endif //CYCLE_ORDERING

	int GetSWGateCount(int cycle);

	bool SetCustomData(int index, DWORD dwCustom);
	bool GetCustomData(int index, DWORD &dwCustom);
	int GetSlaveListFromRemoteId(short sSlaveListIn[], short sSlaveListOut[]);

	static LRESULT WINAPI CallbackUpdatedBase(int iStep, void *pThis, DWORD &dwNextSleep);//return 0 to stop the thread, otherwise 1 in this case dwNextSleep is also an output parameter.
	static LRESULT WINAPI CallbackUpdatedCycle(int iStep, void *pThis, DWORD &dwNextSleep);//return 0 to stop the thread, otherwise 1 in this case dwNextSleep is also an output parameter.
	DWORD GetUpdateId(bool bLocal);
	bool BaseClassReceive(DWORD dwClassId, DWORD *pdwStream, int iStreamSize);
	bool BaseClassSend(bool bForce, DWORD dwClassId, int iCycle = -1, int iCycleCount = 1);
	void ForceClassSend();
	static bool g_bTraceCSWDeviceOEMPASend;
	static bool g_bTraceCSWDeviceOEMPARecv;
	static bool g_bTraceCSWDeviceOEMPAPost;
public:
//xUSER_HEADER_START
};

/////////////////////////////////////////////////////////////////////////////////////////
class CAcquisitionFifo;
typedef enum enumDriverExchangeType {
	eDEStandalone,
	eDEDriver,
	eDEApplication
} enumDriverExchangeType;

class DRIVER_OEMPA_API_ALIGN _CHWDevice
{
private:
	ULONGLONG m_ullPrivateMemory[18773];

public:
	_CHWDevice(CHWDevice *pThis, enumHardware eDefaultHardware, enumCommunication eCommunication, int iMaxConnection);
	~_CHWDevice();


};

class DRIVER_OEMPA_API_ALIGN CHWDevice : public _CHWDevice
{
public:
	CHWDevice();
	~CHWDevice();

public:
	CSWDevice *GetSWDevice();
	const CSWDevice *cGetSWDevice() const;
	int GetDeviceId();
	int GetRemoteDeviceId();
	static int sGetDeviceIdFromRemoteId(int iRemoteDeviceId);
	void SetRemoteDeviceId(int iDeviceId, enumDriverExchangeType eDiverExchangeType);
	bool IsDiverExchangeType(enumDriverExchangeType eDiverExchangeType);
	enumDriverExchangeType GetDiverExchangeType();
	static int GetSWAccessId();
	static void SetSWAccessId(int iSWAccessId);
	static WORD GetSWAccessMask();
	static bool SetSWAccessMask(WORD wMask, bool bAck = true);
	static void SetSWAccessMask2(WORD wMask);
	static bool GetSWAccessReturn();
	static void SetSWAccessReturn(bool bReturn);
	static bool IsSWAccessDenied();
	static bool IsSWAccessGranted();
	static bool IsSWAccessGrantedOnlyForMe();
	static bool EnterSWAccess(WORD &wSWAccessMask);
	static bool LeaveSWAccess(WORD wSWAccessMask);
	static bool IsSWAccessEntered();
	static void WaitForClassSend();
	static short GetKeepAliveMode(enumHardware eHW);
	static void SetKeepAliveMode(enumHardware eHW, short sKeepAliveMode);
	virtual void vf_WaitForClassSend();

	static char sIsSetupChecked(enumHardware eHW);
	static void sCheckSetup(enumHardware eHW, char cValue);
	static char sIsSetupTimeChecked(enumCheckSetupTime eCheck);
	static void sCheckSetupTime(enumCheckSetupTime eCheck, char cValue);
	char IsSetupTimeChecked(enumCheckSetupTime eCheck) const;
	void CheckSetupTime(enumCheckSetupTime eCheck, char cValue);
	static char sIsSetupGainChecked(enumCheckSetupGain eCheck);
	static void sCheckSetupGain(enumCheckSetupGain eCheck, char cValue);
	static char sIsSetupTrackingChecked();
	static void sCheckSetupTracking(char cValue);
	static char sIsDacTimeChecked(enumHardware eHW);
	static void sCheckDacTime(enumHardware eHW, char cValue);

	static CHWDevice *GetHWDevice(int iDeviceId);//returns the device only for the current process.
	static bool IsHWDevice(int iDeviceId);//for all processes.
	virtual enumHardware vf_GetHardware() const;
	virtual bool vf_GetMonitorInitString(bool bMonitor, char *cInit, int iSize);
	void SetDerivedClass(wchar_t *pClassName,void *pDerivedClass);
	void GetDerivedClass(int iClassNameSize,wchar_t *pClassName,void* &pDerivedClass);
	void SetMainThreadPriority(int nPriority);
	void SetTransitThreadPriority(int iIndex, int nPriority);
public:

public:
	static bool RouteTrace(const char *msg, unionRouteDataOptionsIn in = g_DefaultRouteDataOptionsIn);
	static bool RouteTrace(const wchar_t *msg, unionRouteDataOptionsIn in = g_DefaultRouteDataOptionsIn);
	static bool RouteTraceMini(const wchar_t *msg, unionRouteDataOptionsIn in = g_DefaultRouteDataOptionsIn);
	static int RouteMsgBox(const wchar_t *msg, const wchar_t *pTitle, UINT nType, int iTimeOut);
	static bool IsRemoteClientConnected();
	static bool IsRemoteServerConnected();
	bool IsDeviceRoutedViaRemoteServer();

	CHWDevice *GetMatchedDevice();//link to the matched device (an OEMPA 64:64a could be matched with an OEMPA 64:64b to build an OEMPA 128:128).
	const CHWDevice *cGetMatchedDevice() const;//link to the matched device (an OEMPA 64:64a could be matched with an OEMPA 64:64b to build an OEMPA 128:128).
	enumHardwareLink GetMatchedDeviceHwLink() const;//is the matched device a slave or a master ?
	//1.1.5.4a to manage the 256:256 with four 64:64 (64:64A, 64:64B, 64:64C, 64:64D).
	CHWDevice *GetMatched256Device();
	void *GetMatched256DeviceOEMPA();
	const CHWDevice *cGetMatched256Device() const;
	enumHardwareLink GetMatched256DeviceHwLink() const;

//MultiSystem management start (shared functions between applications)
	enumHardwareLink GetHardwareLink() const;//link
	int GetMasterDeviceId() const;//to get the master device id, return -1 if the device is not a slave.
	static int sGetMasterDeviceId(int iDeviceId);
	bool GetHardwareLinkIOCable(int &iDigitalSequence,int &iDigitalCycle);//digital input for slave and digital output for master.

	//FUNCTION to call before connection (this information is registered in the default setup OEMPA file)
	bool SetDefaultHwLink(enumHardwareLink eHardwareLink,bool &bPreviousMasterUnregistered);//define the default link for this device (default link before connection).
													//Only one master could be defined between all devices.
													//output "bPreviousMasterUnregistered" : return false if no error, return true to notify that previou master have been unregistered (only one master is possible).
	bool SetDefaultHwLinkIOCable(enumHardwareLink eHardwareLink,int iDigitalExternalSequence,int iDigitalExternalCycle,bool &bPreviousMasterUnregistered);//define the default link for this device (default link before connection).
													//Only one master could be defined between all devices.
													//output "bPreviousMasterUnregistered" : return false if no error, return true to notify that previou master have been unregistered (only one master is possible).
	enumHardwareLink GetDefaultHwLink() const;
	bool IsDefaultHwLinkEnabled() const;//return false if device connection and initialisation has been done and true otherwise.
	bool GetDefaultHwLinkIOCable(int &iDigitalSequence,int &iDigitalCycle);//digital input for slave and digital output for master.

	//FUNCTION to call after connection
	//DO NOT CALL LockDevice/UnlockDevice to call following:
	bool SlaveConnect(int iMasterDeviceId);//connect current unlinked device to the specified master or unlinked device (that should be conncted).
	bool SlaveConnectIOCable(int iMasterDeviceId, int iMasterDigitalExternalSequence, int iMasterDigitalExternalCycle, int iSlaveDigitalExternalSequence, int iSlaveDigitalExternalCycle);//connect with an external IO cable to the specified master or unlinked device (that should be connected).
	bool SlaveDisconnect();//disconnect current slave device.

	//static information functions : called from any application on any device.
	static const int GetDeviceCountMax();//return the maximum count of device that can be managed.
	static const int GetDeviceCount();//return the current device count that have been instantiated.
	static bool IsConnected(int iDeviceId);//for MatchedDevices: master and slave are managed independently.
	static bool GetDefaultHwLink(int iDeviceId,enumHardwareLink &eHardwareLink);//read the default link (used before connection with the device).
	static bool GetDefaultHwLinkIOCable(int iDeviceId,int &iDigitalSequence,int &iDigitalCycle);//digital input for slave and digital output for master.
	static enumHardwareLink GetHardwareLink(int iDeviceId);//read the current link state (after connection with the device).
	static int GetMasterDeviceId(int iSlaveDeviceId);//to get the master device id, return -1 if the device is not a slave.
	static int GetSlaveCount(int iMasterDeviceId);//return -1 if the device is not a master.
	static int GetSlaveDeviceId(int iMasterDeviceId,int iListSize,int *piDeviceIdList);//return the list of slaves of the master.
	static bool GetHardwareLinkIOCable(int iDeviceId,int &iDigitalSequence,int &iDigitalCycle);//digital input for slave and digital output for master.
	static bool ReadBoardName(int iDeviceId,wchar_t *stringId,int iSize);
	static bool ReadCommunicationName(int iDeviceId,wchar_t *stringId,int iSize);
	static int GetMonitorPort(int iDeviceId);

	static bool GetMatchedDeviceHwLink(int iDeviceId,enumHardwareLink &eMatchedDeviceHwLink,int &iMatchedDeviceId);
	static void EnableMatchedDeviceHwLink(bool bEnable);//enable matched device (at connection time).
	static bool IsMatchedDeviceHwLinkEnabled();
	//1.1.5.4a to manage the 256:256 with four 64:64 (64:64a, 64:64b, 64:64c, 64:64d).
	static bool GetMatched256DeviceHwLink(int iDeviceId,enumHardwareLink &eMatchedDeviceHwLink,int &iMatchedDeviceId);

	static void EnableGlobalPersistent(bool bEnable);
	static bool IsGlobalPersistentEnabled();
	static void EnableCommonKeepAlive(bool bEnable);
	static bool IsCommonKeepAliveEnabled();
	static void SetCommonLockDisableShot(bool bDisable);
	static bool GetCommonLockDisableShot();
	static void SetCommonUnlockEnableShot(bool bEnable);
	static bool GetCommonUnlockEnableShot();

	//LockDevice/UnlockDevice is required to call following:
	bool SetTimeStamp(bool bReset,bool bStopNextStandby);//to synchronize time stamp of device chain.
									//bReset=true: reset the time stamp.
									//bReset=false: set the hardware time stamp equal to the computer time stamp.
									//bStopNextStandby=true: to be able to read time stamp on the next standby (good precision).
									//bStopNextStandby=false: it willnot be possible to read time stamp on the next standby (bad precision).
	bool GetTimeStamp(/*in/out*/int &iSystemCount,ULONGLONG &ullTimeSW,ULONGLONG *pullTimeHW/*[iSystemCount]*/);
//MultiSystem management end

public:
//--------------------------------------------------------------------------------
//Device low level management
	//Those function can be used to receive acquisition data.
	bool SetAcquisitionParameter(void *pParameter);//first parameter of the callback acquisition function.
	void* GetAcquisitionParameter();
	bool SetAcquisitionAscan_0x00010103(pTypeAcquisitionAscan_0x00010103 pProcess);
	pTypeAcquisitionAscan_0x00010103 GetAcquisitionAscan_0x00010103();
	bool SetAcquisitionCscan_0x00010X02(pTypeAcquisitionCscan_0x00010X02 pProcess);
	pTypeAcquisitionCscan_0x00010X02 GetAcquisitionCscan_0x00010X02();
	bool SetAcquisitionIO_0x00010101(pTypeAcquisitionIO_0x00010101 pProcess,bool bDigitalEdgesOnly=true);
	pTypeAcquisitionIO_0x00010101 GetAcquisitionIO_0x00010101(bool &bDigitalEdgesOnly);
	bool SetAcquisitionIO_1x00010101(pTypeAcquisitionIO_1x00010101 pProcess,bool bDigitalEdgesOnly=true);
	pTypeAcquisitionIO_1x00010101 GetAcquisitionIO_1x00010101(bool &bDigitalEdgesOnly);
	bool SetAcquisitionStream(pTypeAcquisitionStream pProcess);
	pTypeAcquisitionStream GetAcquisitionStream();
	bool SetAcquisitionStreamNotification(pTypeAcquisitionStreamNotification pProcess);
	pTypeAcquisitionStreamNotification GetAcquisitionStreamNotification();
	bool SetAcquisitionAscan_0x00020203(pTypeAcquisitionAscan_0x00020203 pProcess);
	pTypeAcquisitionAscan_0x00020203 GetAcquisitionAscan_0x00020203();
	bool SetAcquisitionAscanCscan_0x00020203_0x0302(pTypeAcquisitionAscanCscan_0x00020203_0x0302 pProcess);
	pTypeAcquisitionAscanCscan_0x00020203_0x0302 GetAcquisitionAscanCscan_0x00020203_0x0302();
	bool SetAcquisitionAscan_0x00021003(pTypeAcquisitionAscan_0x00021003 pProcess);
	pTypeAcquisitionAscan_0x00021003 GetAcquisitionAscan_0x00021003();
	// 32bit TOF
	bool SetAcquisitionAscanCscan_0x00030203_0x0302(pTypeAcquisitionAscanCscan_0x00030203_0x0302 pProcess);
	pTypeAcquisitionAscanCscan_0x00030203_0x0302 GetAcquisitionAscanCscan_0x00030203_0x0302();
	bool SetAcquisitionCscan_0x00020402(pTypeAcquisitionCscan_0x00020402 pProcess);
	pTypeAcquisitionCscan_0x00020402 GetAcquisitionCscan_0x00020402();

	bool SetAcquisitionMode(int iAcquisitionMode);
	int GetAcquisitionMode();

	CAcquisitionFifo *GetAcquisitionFifo(enumAcquisitionFifo eFifo);

	bool SetAcquisitionInfo(pTypeAcquisitionInfo pProcess);
	pTypeAcquisitionInfo GetAcquisitionInfo();
	const std::list<CNotificationItem> *cGetLastNotificationList(bool bError) const;
	bool IsStatusSWCriticalError() const;
	bool IsStatusSWPreviousCrash() const;
	bool UpdateStatusSW();
	void ResetStatusSW(bool bInit = false, bool bPreviousCrash = false);//to be able to force pulser enabling, be careful device behavior could be not reliable.
	void SetStatusSWAcqState(bool bReset, bool bCheckRealTimeHW, enumAcquisitionState eAcqState);
	DWORD GetStatusSW(int iSubDevId);
	bool IsStatusSWInitFromHW(int iSubDevId) const;
	void SetStatusSWError(BYTE byCriticalError);
	void SetStatusSWSetupLoaded(bool bLoaded);
	bool IsStatusSWSetupLoaded() const;
	void ResetLastNotificationList(bool bError);
	bool IsRealTimeHWChecked() const;

	static bool SetCallbackNotification(pTypeCallbackNotification pProcess);
	static pTypeCallbackNotification GetCallbackNotification();
	static int BrowseCallbackNotification();//the CallbackNotification function is called for each CHWDevice instance.

	bool IsDriverEncoderManagementEnabled();
	void EnableDriverEncoderManagement(bool bEnable);

//lock/unlock the device
//you have to lock the device before to use its functions (for example "SetStandby" function).
//(the communication link with the HW is shared between all threads, only one at a time
//can lock it)
	enum enumCheckSetupConsistancy {	eCheckOff = 0, eUnlockCheckSetupHW = 1, eUnlockUpdateSetupSW = 2, eSetupLoaded = 4, eLockCheckRealTimeHW = 8,
										eCheckDisplayError = 16, eCheckDisplayWarning = 32, eFillListError = 64, eFillListWarning = 128, eNoResetFlagResumePulser = 256,
										eSetupReadback = 1024//ljr max1024
									};
	static const int g_iLockCheckSetupConsistancy = eFillListError | eFillListWarning | eCheckDisplayError | eCheckDisplayWarning;
	static const int g_iUnlockCheckSetupConsistancy = eUnlockCheckSetupHW | eUnlockUpdateSetupSW | eFillListError | eFillListWarning | eCheckDisplayError | eCheckDisplayWarning;
	bool LockDevice(enumAcquisitionState eAcqState = eAcqDefault, int iCheckSetupConsistancy = g_iLockCheckSetupConsistancy | eLockCheckRealTimeHW);//use "eAcqOff" to disable shot pulse.
					//eAcqDefault is used to read the value from the configuration file.
					//return true if no error and false in case of communication error.
	bool UnlockDevice(enumAcquisitionState eAcqState = eAcqDefault, int iCheckSetupConsistancy = g_iUnlockCheckSetupConsistancy);//use "eAcqOn" to enable shot pulse again.
					//eAcqDefault is used to read the value from the configuration file.
					//return true if no issue otherwise return false in the following cases:
					//- communication error.
					//- new setup check error (returns true in case of no new error).
					//- 'eAcqOn' has been requested but setup check error still detected (new or old).
	bool IsDeviceLocked(DWORD dwThreadId = 0);//in case of multiple systems, check that all are locked.
	bool IsDeviceUnlocked(DWORD dwThreadId = 0);//in case of multiple systems, check that all are unlocked.
	int GetDeviceLockCount(DWORD dwThreadId);
	DWORD GetSettingId();

//management of the device (can be called after device has been locked).
	static const int g_iFlushCheckSetupConsistancy = eUnlockCheckSetupHW | eFillListError | eFillListWarning | eCheckDisplayError | eCheckDisplayWarning;
	bool Flush(int iCheckSetupConsistancy = g_iFlushCheckSetupConsistancy);//return true if no error and false in case of communication error.

	bool CheckSetup(int iCheckSetupConsistancy);//examples: "CheckSetup(eUnlockCheckSetupHW)", "CheckSetup(eUnlockUpdateSetupSW)".

//Don't use those very low level functions, they are reserved for advanced user.
	int GetCommunicationErrorCount();
	//single
	bool WriteHW(DWORD dwAddress,DWORD dwData,int iSize);
	bool WriteHW(int iCount,DWORD dwAddress,const DWORD *pdwData,int iSize);
	bool ReadHW(DWORD dwAddress,DWORD *pdwData,int iSize);
	bool ReadHW(int iCount,DWORD dwAddress,DWORD *pdwData,int iSize);
	bool ReadSW(int iCount, DWORD dwAddress, DWORD *pdwData, int iSize);
	bool vReadSW(int iCount, DWORD dwAddress, DWORD *pdwData, bool *pbValid, int iSize);
	bool vReadSW(int iCount, const DWORD *pdwAddress, DWORD *pdwData, bool *pbValid, int iSize);
	bool GetSizeHW(DWORD dwAddress, int &iSize);
	bool EnablePersistent(bool bEnable, wchar_t *wcSubSection = NULL);
	bool IsPersistentEnabled(wchar_t *wcSubSection = NULL);
	static bool SetCallbackHWMemory(pCallbackHWMemory _pCallbackHWMemory);
	static pCallbackHWMemory GetCallbackHWMemory();
	static bool mSetCallbackHWMemory(pmCallbackHWMemory _pmCallbackHWMemory);
	static pmCallbackHWMemory mGetCallbackHWMemory();
	bool ClearAllWrite();//ljr max1024
	bool ClearWrite();//ljr max1024
	bool RemoveAllWrite();//ljr max1024
	bool RemoveWrite();//ljr max1024
	//multiple
	bool mWriteHW(int iSubDevIndex,DWORD dwAddress,DWORD dwData,int iSize);
	bool mWriteHW(int iSubDevIndex,int iCount,DWORD dwAddress,const DWORD *pdwData,int iSize);
	bool mReadHW(int iSubDevIndex,DWORD dwAddress,DWORD *pdwData,int iSize);
	bool mReadHW(int iSubDevIndex,int iCount,DWORD dwAddress,DWORD *pdwData,int iSize);
	bool mReadSW(int iSubDevIndex, int iCount, DWORD dwAddress, DWORD *pdwData, int iSize);
	bool vmReadSW(int iSubDevIndex, int iCount, DWORD dwAddress, DWORD *pdwData, bool *pbValid, int iSize);
	bool vmReadSW(int iSubDevIndex, int iCount, const DWORD *pdwAddress, DWORD *pdwData, bool *pbValid, int iSize);
	bool mClearWrite(int iSubDevIndex);//ljr max1024
	bool mRemoveWrite(int iSubDevIndex);//ljr max1024
	char IsConnectionShortcutEnabled();//ljr max1024
public:
	virtual bool vf_CheckSetupHW(enumAcquisitionState &eAcqState, structNotificationOption &optionNotification);
	virtual bool vf_CheckSetupHW_MC(enumAcquisitionState &eAcqState, structNotificationOption &optionNotification);
	virtual bool vf_UpdateSetupSW(int iStep, int iCheckConsistancy, structNotificationOption &optionNotification);
	virtual bool vf_AddressMapping(bool bSWToHW, DWORD dwAddressIn, DWORD &dwAddressOut);
	virtual bool vf_LockDevice(enumAcquisitionState &eAcqState);
	virtual bool vf_RouteLockDevice(enumAcquisitionState eAcqState);
	virtual bool vf_UnlockDevice(enumAcquisitionState eAcqStateIn, int iCheckConsistancy, enumAcquisitionState &eAcqState);
	virtual bool vf_FlushDevice();
	virtual bool vf_WriteStatusSW(int iSubDevId);
	virtual bool vf_ReadStatusSW(int iSubDevId);
	virtual DWORD vf_GetSWDeviceOEMPAUpdateId(bool bLocal);

public:
	void InitStatusSW(int iSubDevId, LONG lValue);
	static bool SetAllElementEnable(bool bEnable,int iSize,DWORD *pdwHWAperture);
	static bool SetElementEnable(int iElement,bool bEnable,int iSize,DWORD *pdwHWAperture);
	static bool GetElementEnable(int iElement,int iSize,const DWORD *pdwHWAperture,bool &bEnable);

public:
	bool IsCallbackStandbyEnabled();
	void EnableCallbackStandby(bool bEnable);
	bool IsCallbackEnabled();
	void EnableCallback(bool bEnable);
	void _EnableCallback(bool bEnable);
	bool IsCallbackEnabled(bool bFeedbackDriver);
	bool IsFeedbackDriverEnabled();
	void EnableFeedbackDriver(bool bFeedbackDriver);
	int GetSubDeviceCountTarget() const;
	void SetSubDeviceCountTarget(int iSubDeviceCount);

public:

public:
public://don't use following functions
	void ResetSubDeviceCount();
	int GetSubDeviceCount() const;
	bool GetCommunicationName(wchar_t *stringId,int iSize);
	virtual bool vf_SetAcquisitionFlush(enumAcquisitionFlush eAcquisitionFlush);
	virtual enumAcquisitionFlush vf_GetAcquisitionFlush() const;
	virtual bool vf_UpdateEncoder(int iEncoder)=0;//1.1.5.4w
	virtual bool vf_UpdateFilter(int iFilter)=0;//1.1.5.4w
	virtual bool vf_FreeDigitalInput(enumFeatureDigitalInput eIndexDigitalInputNew)=0;//1.1.5.4w
	virtual bool vf_EnablePulser(bool bEnable);
	virtual bool vf_PreEnablePulser(bool bEnable);
	virtual bool vf_PostEnablePulser(bool bEnable);
	virtual bool vf_SetCommunication(enumCommunication eCommunication);
	virtual bool vf_LoadCfgFile();
	virtual bool vf_ReLoadCfgFile(){return false;};//=0;
	virtual bool vf_SetStandby(bool bLockOrUnlock, enumAcquisitionState &eAcqState);
	virtual bool vf_SetStandbyNoFlush(bool standby);
	virtual bool vf_SetStandby(bool bEnter, bool bLock, enumAcquisitionState eAcqState);//ljr max1024
	virtual bool vf_PostSetStandby(bool bLockOrUnlock, enumAcquisitionState &eAcqState);
	const bool *GetDestructorCalled() const;//value of this pointer is false as soon as the desctructor has been called.
	bool SetSubDeviceIndex(int iSubDevId);
	int GetSubDeviceIndex() const;//-1 means all.
public:
public:
public:
	virtual bool vf_OnMasterConnected(int iMasterDigitalExternalSequence, int iMasterDigitalExternalCycle, int iSlaveDigitalExternalSequence, int iSlaveDigitalExternalCycle);
	virtual bool vf_OnMasterDisconnected(bool bSingleIOBoard);
	virtual bool vf_OnSlaveConnected(int iMasterDigitalExternalSequence, int iMasterDigitalExternalCycle, int iSlaveDigitalExternalSequence, int iSlaveDigitalExternalCycle);
	virtual bool vf_OnSlaveDisconnected(bool bPostProcess);
	virtual bool vf_SWReset();
	virtual bool vf_OnMasterConnectedFpgaManager();
	virtual bool vf_OnSlaveConnectedFpgaManager();
	virtual bool vf_ResetSequence() { return false; };//=0;
	virtual bool vf_SetTimeStamp(int iValue)/*0=restart,1=reset,2=stop on next standby.*/ { return false; };//=0;
	virtual bool vf_SetTimeStamp(ULONGLONG &ullTimeStamp) { return false; };//=0;
	virtual bool vf_GetTimeStamp(ULONGLONG *pullTimeHW) { return false; };//=0;
	virtual CHWDevice* vf_AllocMatchedDevice();
	virtual bool vf_DesallocMatchedDevice();
	virtual CHWDevice* vf_AllocMatched256Device();
	virtual bool vf_DesallocMatched256Device();
#ifdef _WIN64
	virtual CAcquisitionFifo *vf_GetAcquisitionFifo(enumAcquisitionFifo eFifo) = 0;
	virtual int vf_GetLostCountFifo(enumAcquisitionFifo eFifo) const = 0;
#endif //_WIN64
protected:
public:

public:
};


/////////////////////////////////////////////////////////////////////////////////////////

class CHWDeviceOEMPA;
struct structIOManager;

typedef struct structInitFifos
{
	bool bFifoDataCopySubStream;
	BYTE byStreamVersion;
	int iMaxConnection;
	const wchar_t *pFifoCfgSection;
}structInitFifos;

class DRIVER_OEMPA_API_ALIGN _CHWDeviceOEMPA
{
private:
	ULONGLONG m_ullPrivateMemory[727];
public:

};

class DRIVER_OEMPA_API_ALIGN CHWDeviceOEMPA :
	public _CHWDeviceOEMPA,
	public CHWDevice
{
private:
public:

public:
public:
	//1.2.1.0o float fIn,fOut;
	CHWDeviceOEMPA(enumHardware eDefaultHW, enumCommunication eCommunication, int iMaxConnection);
	CHWDeviceOEMPA(	enumHardware eDefaultHW, enumCommunication eCommunication,
					structInitFifos initFifos);
	virtual ~CHWDeviceOEMPA();

	//MultiProcess management begin
	static bool IsMultiProcessRegistered();
	static bool RegisterMultiProcess(const wchar_t *wcProcessName);//call this function before instantiating any device.
	static bool UnregisterMultiProcess();
	static bool IsMultiProcessConnected(wchar_t *wcAddress,DWORD &dwProcessId);//call this function to know if another process has been already connected with the device.
				//Input "wcAddress": (IP) address of the device.
				//Output "dwProcessId": process ID of the process that has already been connected with the device.
				//return true if any other process has already been connected with the device, false otherwise.
	static bool DisconnectMultiProcess(wchar_t *wcAddress,DWORD dwProcessId);//call this function to disconnect the device of another process (.
				//Input "wcAddress": (IP) address of the device.
				//Input "dwProcessId": process ID of the process that has already been connected with the device.
				//return true if the device has been disconnected, false otherwise.
	static int GetMultiProcessCount();//to get the count of other process that has been registered with function "RegisterMultiProcess".
	static bool GetMultiProcessInfo(int iIndex,DWORD &dwProcessId,int iSize,wchar_t *wcProcessName);//to get information of other process that has been registered with function "RegisterMultiProcess".
	//MultiProcess management end

	//IO management
	static void ResetIO(structIOManager *ioManager);
	static bool AddIO(structIOManager *ioManager,CSubStreamIO_0x0101 *pIO_0x00010101);
	static bool GetIO(structIOManager *ioManager,int iDevice,uint64_t ullTimeStamp,uint64_t ullSequence,LONG lCycle,bool &bTooEarly,bool &bTooLate,LONG lEncoder[g_iDriverEncoderCountMax],DWORD &dwDigitalInput,LONG &lMaxTemperature,LONG &lLastAscanIndex);

public:
public:
	virtual bool vf_CheckGateIndex(int &iGate);
	virtual bool vf_AllocAscanMatrix(uint64_t ui64SequenceByteSize, uint64_t &ui64MemorySize);
	virtual CAcquisitionFifo *vf_GetAcquisitionFifo(enumAcquisitionFifo eFifo);
	virtual int vf_GetLostCountFifo(enumAcquisitionFifo eFifo) const;
	virtual void* ProcessSWGate(void *_pDevCom, void *pAcquisitionParameter, const CStream_0x0002 *pStreamHeader, const CSubStreamAscan_0x0203 *pSubStreamAscan_0x0203, const void *pBufferMax, const void *pBufferMin, const void *pBufferSat);
	virtual void UpdateResetIOAscan();
	virtual void ResetIOAscan();
	virtual bool AddIOAscan(int iIndexSubStream,const CStream_0x0001 *pStreamHeader,CSubStreamAscan_0x0103 *pAscan_0x00010103);
	virtual bool AddIOAscan(int iIndexSubStream, const CStream_0x0002 *pStreamHeader, CSubStreamAscan_0x0203 *pAscan_0x00020203);
	virtual bool ProcessIOAscan(int iDevice,void *pAcquisitionParameter,pTypeAcquisitionAscan_0x00010103 pAcquisitionAscan_0x00010103,LONG &lLastAscanIndex)=0;
	virtual void UpdateResetIOCscan();
	virtual void ResetIOCscan();
	virtual bool AddIOCscan(CHWDevice* pThis,int iIndexSubStream,const CStream_0x0001 *pStreamHeader,CSubStreamCscan_0x0X02 *pCscan_0x00010X02);
	virtual bool AddIOCscan(CHWDevice* pThis, int iIndexSubStream, const CStream_0x0002* pStreamHeader, CSubStreamCscan_0x0402* pCscan_0x00020402);
	virtual bool ProcessIOCscan(int iDevice,void *pAcquisitionParameter,pTypeAcquisitionCscan_0x00010X02 pAcquisitionCscan_0x00010X02,LONG &lLastCscanIndex)=0;
	virtual bool AddIOAscanCscan(CHWDevice* pThis, int iIndexSubStream, const CStream_0x0002* pStreamHeader, CSubStreamAscan_0x0203* pAscan_0x00020203, CSubStreamCscan_0x0402* pCscan_0x00020402);	// add to the ascan queue, better to have only one since streams are mixed.
	virtual bool ProcessIOAscanCscan(int iDevice, void* pAcquisitionParameter, LONG& lLastCscanIndex, LONG& lLastAscanIndex);
	virtual bool swIsFMCCycleDependent() const;
	virtual bool swSetFMCElement(int iStart,int iStop);
	virtual bool swSetFMCElement(int iStart,int iStop,int iStep);
	virtual bool swSetFMCElementStart(int iStart);
	virtual bool swSetFMCElementStep(int iStep);
	virtual bool swSetFMCElementStop(int iStop);
	virtual bool swUpdateFMCElementCount();
	virtual int swGetFMCElementStart() const;
	virtual int swGetFMCElementStep() const;
	virtual int swGetFMCElementStop() const;
	virtual const structFMCElementInfo* vf_GetFMCAscanElementInfo(int &iAscanCount) const;
	virtual bool vf_CheckCycleIndex(int &iCycle);
	virtual bool vf_CheckChannelIndex(int& iChannel);

public:

	virtual CSWDeviceOEMPA *GetSWDeviceOEMPA();
	virtual CSWEncoder *GetSWEncoder(int iEncoder);//same than "CHWDevice::GetSWDevice()->CSWDevice::GetSWEncoder(int iEncoder)", but quicker.

	virtual bool GetDigitalInput(DWORD *pdwData)=0;//reading the current state of digital inputs

	//flash management
	static bool GetFlashItem(const wchar_t *strFlashFile,const wchar_t *pItemName,int iValueSize,wchar_t *pValue);
	static bool GetFlashItemBasic(const wchar_t *strFlashFile,const wchar_t *pItemName,int iValueSize,wchar_t *pValue);
	static bool SetFlashItem(const wchar_t *strFlashFile,const wchar_t *pItemName,const wchar_t *pValue);

	// User persistent data. Returns false if non applicable to current device.
	// Store 'size' bytes of custom data in flash memory. Maximum 64kB.
	// Warning: the flash memory will be erased before any write operation. It is the user's responsibility to read and back up the data before writing.
	virtual bool SetUserData(const unsigned char* buffer, size_t size);
	// Get custom data from flash memory. 'size' bytes will be read from memory and stored into 'buffer'. 
	// If fewer data was previously written the excendent is filled with 0xFF.
	virtual bool GetUserData(unsigned char* buffer, size_t size);

	//Valid only for OEMPA1 (64:64A and 64:64B, not valid for 64:64C and 64:64D).
	virtual bool Enable256(bool bEnable);
	virtual bool GetEnable256(bool *pbEnable);

//FW members (those parameters are inside the HW board)
//before using them you need to lock the device : see member functions of "CHWDevice"
//(the communication link with the HW is shared between all threads, only one at a time can lock it)

public:
	virtual bool EnablePulser(bool bShot);
	virtual bool GetEnablePulser(bool *pbShot)=0;//ask hw as for others functions.
	virtual bool EnablePulser(bool bShot,bool bDisableCallback);
	virtual bool swIsPulserEnabled();
	virtual bool swIsStandbyOff();//Same as above but set after the standby was changed.

public:

//<<PARAMETERS MANAGEMENT FUNCTIONS : BEGIN>>
//All those functions return true in case of no error and false in case of error.

	virtual bool GetFWId(WORD *pwFWId)=0;//to get the device version.
	virtual bool dwGetFWId(DWORD *pdwFWId)=0;//to get the device version.
	virtual bool GetFWOptions(DWORD *pdwFWOptions)=0;
	virtual bool IsMiniV2()/* = 0;*/ { return false; }
	virtual bool GetAWGFWId(DWORD* pdwFWId);
public:
	virtual DWORD GetFWMask();
	virtual void ResetFWOptions()=0;
	virtual bool GetFWId()=0;
	virtual DWORD GetFWOptionsMask();
	virtual bool GetFWOptions();
	virtual bool SetFWOptionsMask(const wchar_t *pPasscode, CUTDevCommunication *pDevCom = NULL)=0;
	virtual int GetFlashSWSectionSize()=0;
	virtual bool GetFlashSWSection(char *pBuffer,int iSize)=0;

public:
	virtual bool DisableUSB3(bool bDisable);
	virtual bool GetUSB3Disabled(bool *pbDisable);

public:
	virtual int swGetApertureCountMax() const=0;//to get the maximum element count of an aperture (SW function, the HW does not send answer).
	virtual int swGetElementCountMax() const=0;//to get the maximum element count of the system (SW function, the HW does not send answer).
	virtual int swGetCycleCountMax()=0;

public:

	virtual bool GetTemperatureSensor(int iIndexBoard,int iIndexSensor,WORD *pwTemperature)=0;//FW parameter
	virtual bool GetTemperatureSensor(int iIndexBoard,int iIndexSensor,short *psTemperature)=0;//signed values, usefull for mini and Com board of PA1/2.
							//iIndexBoard: 0=ComBoard, 1=first RX board, 2=second RX board, 3=third RX board, 4=four RX board.
	virtual bool GetHumiditySensor(int iIndexBoard, int iIndexSensor, WORD* pwTemperature);
	virtual bool GetTemperatureMaxHW(int iSubDevId, short* psTemperature) = 0;
	virtual bool SetTemperatureAlarm(BYTE &byWarning,BYTE &byAlarm)=0;
	virtual bool GetTemperatureAlarm(BYTE *pbyWarning,BYTE *pbyAlarm)=0;

public:
	virtual bool SetHardwareLink(enumHardwareLink &eHardwareLink,int iDigitalExternalSequence,int iDigitalExternalCycle)=0;
	virtual bool GetHardwareLink(enumHardwareLink *peHardwareLink,int *piDigitalExternalSequence,int *piDigitalExternalCycle)=0;

public:
	virtual bool EnableFMC(bool bEnable)=0;//return false if the FW does not support the FMC feature (old FMC FW and FW for which FMC is not supported).
	virtual bool GetEnableFMC(bool *pbEnable)=0;//return false if the FW does not support the FMC feature (old FMC FW and FW for which FMC is not supported).
	//you can use the following functions in any case (step equal or different to 1):
	virtual bool SetFMCElement(int &iElementStart,int &iElementStop,int &iElementStep)=0;
	virtual bool GetFMCElement(int *piElementStart,int *piElementStop,int *piElementStep)=0;
	//you can use the following functions only if the step is 1:
	virtual bool SetFMCElementStart(int &iElementIndex)=0;
	virtual bool GetFMCElementStart(int *piElementIndex)=0;
	virtual bool SetFMCElementStop(int &iElementIndex)=0;
	virtual bool GetFMCElementStop(int *piElementIndex)=0;
	virtual bool SetReceptionGainsFMC256(int iCycle,DWORD adwHWAperture[2*g_iOEMPAApertureDWordCount],float *pfGain);
public:
	virtual bool swIsFullMatrixCapture() const;
	virtual bool swIsMultiHWChannelSupported() const;
	virtual bool swIsMultiHWChannelEnabled() const;

public:

	virtual bool EnableMultiHWChannel(bool bEnable);//return false if the FW does not support the MultiChannel feature.
	virtual bool GetEnableMultiHWChannel(bool *pbEnable);//return false if the FW does not support the MultiChannel feature.
public:

public:

	virtual bool ResetTimeStamp()=0;

	virtual bool ResetEncoder(int iEncoderIndex)=0;//same than "SetEncoder(iEncoderIndex,0)".
	virtual bool SetEncoder(int iEncoderIndex,double &dValue)=0;//unit=meter
	virtual bool SetEncoder(int iEncoderIndex,DWORD &dwValue)=0;//unit=encoder step
	virtual bool GetEncoderPosition(int iEncoderIndex, LONG* plCounts, double* pdPosition)=0;//unit=meter
	virtual bool SetEncoderType(enumEncoderType &eEncoder1Type,enumEncoderType &eEncoder2Type)=0;
	virtual bool GetEncoderType(enumEncoderType *peEncoder1Type,enumEncoderType *peEncoder2Type)=0;

	virtual bool EnableAscan(bool bAscan)=0;//to enable Ascan acquisition that will be sent by the FW to the SW.
	virtual bool GetEnableAscan(bool *pbAscan)=0;

	//Cscan time of flight : you have frist to define gates (see "SetGateXXX").
	virtual bool EnableCscanTof(bool bCscanTof)=0;//to enable Cscan time of flight acquisition that will be sent by the FW to the SW.
	virtual bool GetEnableCscanTof(bool *pbCscanTof)=0;
public:

public:

	virtual bool SetAscanBitSize(enumBitSize eBitSize)=0;//Ascan data size.
	virtual bool GetAscanBitSize(enumBitSize *peBitSize)=0;
	virtual bool CheckAscanBitSize(enumBitSize &eBitSize) = 0;
public:

public:

	virtual bool SetAscanRequest(enumAscanRequest eAscanRequest)=0;
	virtual bool GetAscanRequest(enumAscanRequest *peAscanRequest)=0;
public:

public:

	//This function "SetAscanRequestFrequency" can be used when you dont want to receive all Ascan
	//(to decrease the throughput) see also the function "SetAscanRequest".
	//Be careful if you want to set the Pulse Repetition Rate, please refer to function "SetTimeSlot".
	virtual bool SetAscanRequestFrequency(double &dValue)=0;
	virtual bool GetAscanRequestFrequency(double *pdValue)=0;
	virtual bool CheckAscanRequestFrequency(double &dValue)=0;
public:

public:

	virtual bool SetCycleCount(int &lCycleCount)=0;//to write the cycle count.
	virtual bool GetCycleCount(int *plCycleCount)=0;//to read the cycle count.
	virtual bool CheckCycleCount(int &iCycleCount)=0;//to check the cycle count (minimum value, maximum value).
public:

public:

	virtual bool SetTriggerMode(enumOEMPATrigger &eTrig)=0;
	virtual bool GetTriggerMode(enumOEMPATrigger *peTrig)=0;
	//In case of the mode "eEncoder" an additional mode is required:
	virtual bool SetEncoderDirection(enumOEMPAEncoderDirection &eEncoderDirection)=0;
	virtual bool GetEncoderDirection(enumOEMPAEncoderDirection *peEncoderDirection)=0;
	//In case of SW trigger you have also to call the following functions:
	virtual bool SWTrigger_Sequence();
	virtual bool SWTrigger_Cycle(int iCycleCount);
	virtual bool SWTrigger_ResetFWCurrentCycle();
public:

public:

	//It is better to use following function (unit is meter), previously you have to set the resolution ("GetSWEncoder(int iEncoder)->SetResolution()").
	virtual bool SetTriggerEncoderStep(double &dStep)=0;//unit=meter
	virtual bool GetTriggerEncoderStep(double *pdStep)=0;//unit=meter
	//than those functions (if you want to manage by yourself the encoder resolution).
	virtual bool SetTriggerEncoderStep(DWORD &dwStep)=0;//unit=encoder step
	virtual bool GetTriggerEncoderStep(DWORD *pdwStep)=0;//unit=encoder step
	//for some of the FW version a floating point value is available (see function "CSWDeviceOEMPA1::IsEncoderDecimal"):
#ifdef VIRTUAL_ENCODERSTEPFLOAT
	virtual bool SetTriggerEncoderStepFloat(structEncoderStepFloat &stStep) = 0;
	virtual bool GetTriggerEncoderStepFloat(structEncoderStepFloat *pstStep) = 0;//unit=encoder step
#endif // VIRTUAL_ENCODERSTEPFLOAT
public:

public:

	virtual bool SetSignalTriggerHighTime(double &dTime)=0;
	virtual bool GetSignalTriggerHighTime(double *pdTime)=0;
	virtual double GetSignalTriggerHighTimeMin()=0;
public:

public:

	virtual bool SetRequestIO(enumOEMPARequestIO eRequest)=0;
	virtual bool GetRequestIO(enumOEMPARequestIO *peRequest)=0;
public:

public:

	virtual bool SetRequestIODigitalInputMask(int &iMaskFalling,int &iMaskRising)=0;
	virtual bool GetRequestIODigitalInputMask(int *piMaskFalling,int *piMaskRising)=0;
	virtual bool CheckRequestDigitalInputMask(int &iMask)=0;

public:

public:

	static bool GetFilterCoefficient(enumOEMPAFilter eFilter,WORD &wScale,WORD wValue[g_iOEMPAFilterCoefficientMax]);
	static bool FindFilterCoefficient(WORD wScale,const short wValue[g_iOEMPAFilterCoefficientMax],enumOEMPAFilter &eFilter);
	// For the new MC series.
	static bool GetFilterCoefficientMC(enumOEMPAFilter eFilter, WORD& wScale, WORD wValue[g_iOEMMCFilterCoefficientMax]);
	static bool FindFilterCoefficientMC(WORD wScale, const short wValue[g_iOEMMCFilterCoefficientMax], enumOEMPAFilter& eFilter);
	virtual bool SetFilter(enumOEMPAFilterIndex eFilterIndex,WORD &wScale,short wValue[g_iOEMPAFilterCoefficientMax])=0;
	virtual bool GetFilter(enumOEMPAFilterIndex eFilterIndex,WORD *pwScale,short wValue[g_iOEMPAFilterCoefficientMax])=0;
public:
	virtual bool SetFilterScale(enumOEMPAFilterIndex eFilterIndex,WORD &wScale)=0;
	virtual bool SetFilterCoefficient(enumOEMPAFilterIndex eFilterIndex,int iIndex,short &wValue)=0;
	virtual bool GetFilterScale(enumOEMPAFilterIndex eFilterIndex,WORD *pwScale)=0;
	virtual bool GetFilterCoefficient(enumOEMPAFilterIndex eFilterIndex,int iIndex,short *pwValue)=0;

public:

	virtual bool SetEncoderWire1(int iEncoderIndex,enumDigitalInput eDigitalInput)=0;//int iEncoderIndex : 0 for first encoder, 1 for second encoder.
	virtual bool SetEncoderWire2(int iEncoderIndex,enumDigitalInput eDigitalInput)=0;
	virtual bool SetExternalTriggerCycle(enumDigitalInput eDigitalInput)=0;
	virtual bool SetExternalTriggerSequence(enumDigitalInput eDigitalInput)=0;
	virtual bool SetExternalResetEncoder1(enumDigitalInput eDigitalInput);
	virtual bool SetExternalResetEncoder2(enumDigitalInput eDigitalInput);
	virtual bool SetExternalTimestampReset(enumDigitalInput eDigitalInput);//MERGE_PAMINI_PAMAX_MC =0;?
	virtual bool SetExternalEncoderReset(enumDigitalInput eDigitalInput);	// reset both encoders.
	virtual bool SetExternalTrackingReset(enumDigitalInput eDigitalInput);
	virtual bool GetEncoderWire1(int iEncoderIndex,enumDigitalInput *peDigitalInput)=0;
	virtual bool GetEncoderWire2(int iEncoderIndex,enumDigitalInput *peDigitalInput)=0;
	virtual bool GetExternalTriggerCycle(enumDigitalInput *peDigitalInput)=0;
	virtual bool GetExternalTriggerSequence(enumDigitalInput *peDigitalInput)=0;
	virtual bool GetExternalResetEncoder1(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalResetEncoder2(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTimestampReset(enumDigitalInput *peDigitalInput);//MERGE_PAMINI_PAMAX_MC =0;?
	virtual bool GetExternalEncoderReset(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTrackingReset(enumDigitalInput *peDigitalInput);

	virtual bool ResetDigitalInput(enumDigitalInput eDigitalInput);
public:
	virtual bool SettingFreeAllDigitalInput();

public:

	virtual bool SetDigitalOutput(int iIndex,enumOEMPAMappingDigitalOutput eMappingDigitalOutput)=0;
	virtual bool GetDigitalOutput(int iIndex,enumOEMPAMappingDigitalOutput *peMappingDigitalOutput)=0;
	virtual bool SetDigitalOutput(int iIndex, enumOEMPAMiniMappingDigitalIO eMappingDigitalOutput)=0;
	virtual bool GetDigitalOutput(int iIndex, enumOEMPAMiniMappingDigitalIO *peMappingDigitalOutput)=0;

public:

public:

	virtual bool SetEncoderDebouncer(double &dValue)=0;
	virtual bool GetEncoderDebouncer(double *pdValue)=0;
	virtual bool CheckEncoderDebouncer(double &dValue)=0;
public:

public:

	virtual bool SetDigitalDebouncer(double &dValue)=0;
	virtual bool GetDigitalDebouncer(double *pdValue)=0;
	virtual bool CheckDigitalDebouncer(double &dValue)=0;
public:

public:

	virtual bool SetMultiSystemDebouncer(double &dValue)=0;
	virtual bool GetMultiSystemDebouncer(double *pdValue)=0;
	virtual bool CheckMultiSystemDebouncer(double &dValue)=0;
public:

public:

	virtual bool SetAnalogBandwidth(enumOEMPAAnalogBandwidth &eAnalogBandwidth)=0;
	virtual bool GetAnalogBandwidth(enumOEMPAAnalogBandwidth *peAnalogBandwidth)=0;
public:

public:

	virtual bool SetFlushTimer(double& dTimer);
	virtual bool CheckStreamTimer(double& dTimer);

#ifdef CYCLE_ORDERING
	virtual bool EnableCycleOrder(bool bCycleOrderEnable);
	virtual bool GetCycleOrderEnable(bool *pbCycleOrderEnable);
	virtual bool CheckCycleOrder(int iCycleCount, int iCycleOrderCount, int *piCycleOrder);
	virtual bool SetCycleOrder(int iCycleOrderCount, int *piCycleOrder);
	virtual bool GetCycleOrder(int iCycleOrderCount, int *piCycleOrderCount, int *piCycleOrder);
	virtual bool GetCycleOrder(int iCycleOrderCount, int* piCycleOrderCount, structCallbackArrayInt1D& callbackArrayInt1D);
#endif //CYCLE_ORDERING
	virtual bool SetPulseType(enumPulseType ePulseType);
	virtual bool GetPulseType(enumPulseType* pePulseType);

	//static bool WINAPI CheckGain(double &dGain,float &fBeamCorrection,int &iDACCountMax,int &iDACCount,float *pfDACSlope,float *pfDACTime);
	virtual bool SetGainDigital(int iCycle,double &dGain)=0;//to write the amplification.
	virtual bool GetGainDigital(int iCycle,double *pdGain)=0;//to read the amplification.
	virtual bool CheckGainDigital(double &dGain, int iCycle = -1)=0;//to check the amplification value (minimum, maximum, step).
	virtual bool CheckSetupGainDigital(structNotificationOption &optionNotification, int iCycle, double &dGain);
public:
protected:
	virtual bool TranslateGainDigital(structNotificationOption &optionNotification, double &dGain, LONG &lHWDataParameter) = 0;
	virtual void TranslateGainDigital(LONG lHWDataParameter, double &dGain) = 0;
public:

public:
	// Functions to handle MC channels.
	virtual bool SetGainDigital(int iCycle, int iChannelCount, int *piChannels, double *pdGain);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetGainDigital(int iCycle, int iArraysize, int *piChannelCount, double *pdGain);
	virtual bool SetGainDigital(int iCycle, int iChannel, double &dGain);
	virtual bool GetGainDigital(int iCycle, int iChannel, double *pdGain);

	virtual bool SetBeamCorrection(int iCycle,float &fGain)=0;
	virtual bool GetBeamCorrection(int iCycle,float *pfGain)=0;
	virtual bool CheckBeamCorrection(float &fGain)=0;
	virtual bool CheckSetupBeamCorrection(structNotificationOption &optionNotification, int iCycle, float &fGain);
	virtual bool SetBeamCorrection(int iCycle, bool &bEnable);
	virtual bool GetBeamCorrection(int iCycle, bool *pbEnable);
	// Functions to handle MC channels.
	virtual bool SetBeamCorrection(int iCycle, int iChannelCount, int *piChannels, float *pfGain);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetBeamCorrection(int iCycle, int iArraysize, int *piChannelCount, float *pfGain);
	virtual bool SetBeamCorrection(int iCycle, int iChannel, float &fGain);
	virtual bool GetBeamCorrection(int iCycle, int iChannel, float *pfGain);
	virtual bool SetBeamCorrection(int iCycle, int iChannel, bool& bEnable);
	virtual bool GetBeamCorrection(int iCycle, int iChannel, bool* pbEnable);
public:

public:

	virtual bool SetDACSlope(int iCycle,int &iCount,double *pdTime,float *pfSlope);
	virtual bool SetDACSlope(int iCycle,int &iCount,double *pdTime,float *pfSlope,int iStringErrorSize,wchar_t *pStringError);//this function give more information about the error.
	virtual bool GetDACSlope(int iCycle,int &iCountMax,int *piCount,double *pdTime,float *pfSlope);
	virtual bool SetDACSlope(int iCycle,int &iCountMax,structCallbackArrayFloatDac &callbackArray);
	virtual bool SetDACSlope(int iCycle,int &iCountMax,structCallbackArrayFloatDac &callbackArray,int iStringErrorSize,wchar_t *pStringError);//this function give more information about the error.
	virtual bool GetDACSlope(int iCycle,int &iCountMax,structCallbackArrayFloatDac &callbackArray);

	virtual bool SetDACGain(bool bAutoStop,int iCycle,int &iCount,double *pdTime,float *pfGain);//bAutoStop : true to automatically add a point to return the gain to 0dB.
	virtual bool GetDACGain(int iCycle,int &iCountMax,int *piCount,double *pdTime,float *pfGain);
	virtual bool SetDACGain(bool bAutoStop,int iCycle,int &iCountMax,structCallbackArrayFloatDac &callbackArray);//bAutoStop : true to automatically add a point to return the gain to 0dB.
	virtual bool GetDACGain(int iCycle,int &iCountMax,structCallbackArrayFloatDac &callbackArray);

	// Functions to handle MC channels.
	virtual bool SetDACSlope(int iCycle, int iChannel, int &iCount, double *pdTime, float *pfSlope, int iStringErrorSize, wchar_t *pStringError);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetDACSlope(int iCycle, int iChannel, int &iCountMax, int *piCount, double *pdTime, float *pfSlope);
	virtual bool SetDACGain(bool bAutoStop, int iCycle, int iChannel, int &iCount, double *pdTime, float *pfGain);//bAutoStop : true to automatically add a point to return the gain to 0dB.
	virtual bool GetDACGain(int iCycle, int iChannel, int &iCountMax, int *piCount, double *pdTime, float *pfGain);
	virtual bool SetDACSlope(int iCycle, int iChannel, int &iCountMax, structCallbackArrayFloatDac &callbackArray);
	virtual bool SetDACSlope(int iCycle, int iChannel, int &iCountMax, structCallbackArrayFloatDac &callbackArray, int iStringErrorSize, wchar_t *pStringError);//this function give more information about the error.
	virtual bool GetDACSlope(int iCycle, int iChannel, int &iCountMax, structCallbackArrayFloatDac &callbackArray);
	virtual bool SetDACGain(bool bAutoStop, int iCycle, int iChannel, int &iCountMax, structCallbackArrayFloatDac &callbackArray);//bAutoStop : true to automatically add a point to return the gain to 0dB.
	virtual bool GetDACGain(int iCycle, int iChannel, int &iCountMax, structCallbackArrayFloatDac &callbackArray);

	virtual bool EnableDAC(int iCycle,bool &bEnable)=0;
	virtual bool GetEnableDAC(int iCycle,bool *pbEnable)=0;
	virtual bool CheckDACSlope(double &fTime,float &fSlope)=0;
	virtual bool CheckDACGain(float &fGain) = 0;
	virtual bool CheckDACCount(int &iCount)=0;
	virtual bool CheckSetupDac(structNotificationOption &optionNotification, int iCycle, float &fGain);
	virtual bool CheckSetupDacTime(structNotificationOption &optionNotification, int iCycle, float &fTime);
	virtual bool CheckSetupDacTime(structNotificationOption &optionNotification, int iCycle, double &dTime);
	// Functions to handle MC channels.
	virtual bool EnableDAC(int iCycle, int iChannel, bool &bEnable);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetEnableDAC(int iCycle, int iChannel, bool *pbEnable);
public:
	virtual bool SetDAC(int iCycle,int &iCount,double *pdTime,float *pfPrm,structCallbackArrayFloatDac *pCallbackArray,int iStringErrorSize,wchar_t *pStringError)=0;//safe : check between the different points of the DAC is peformed.
	virtual bool SetDAC(int iCycle,int &iCount,double *pdTime,float *pfPrm, float fAnalogGain, int iCountVGA, double *pdTimeVGA, float *pfGainVGA,structCallbackArrayFloatDac *pCallbackArray,int iStringErrorSize,wchar_t *pStringError)=0;//safe : check between the different points of the DAC is peformed.
	virtual bool GetDAC(bool bSlope,int iCycle,int &iCountMax,int *piCount,double *pdTime,float *pfPrm,structCallbackArrayFloatDac *pCallbackArray)=0;
	virtual bool GetDAC(bool bSlope,int iCycle,int &iCountMax,int *piCount,double *pdTime,float *pfPrm, int *piCountVGA, double *pdTimeVGA, float *pfGainVGA,structCallbackArrayFloatDac *pCallbackArray)=0;
	virtual bool SetDAC(int iCycle, int iChannel, int &iCount, double *pdTime, float *pfPrm, structCallbackArrayFloatDac *pCallbackArray, int iStringErrorSize, wchar_t *pStringError);//safe : check between the different points of the DAC is peformed. //MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetDAC(bool bSlope, int iCycle, int iChannel, int &iCountMax, int *piCount, double *pdTime, float *pfPrm, structCallbackArrayFloatDac *pCallbackArray);//MERGE_PAMINI_PAMAX_MC renaming?

public:

	virtual bool SetAscanRectification(int iCycle,enumRectification eRectification)=0;
	virtual bool GetAscanRectification(int iCycle,enumRectification *peRectification)=0;
	// Functions to handle MC channels.
	virtual bool SetAscanRectification(int iCycle, int iChannelCount, int *piChannels, enumRectification *peRectification);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetAscanRectification(int iCycle, int iArraysize, int *piChannelCount, enumRectification *peRectification);
	virtual bool SetAscanRectification(int iCycle, int iChannel, enumRectification eRectification);
	virtual bool GetAscanRectification(int iCycle, int iChannel, enumRectification *peRectification);
public:

public:

	virtual bool SetAscanStart(int iCycle,double &dStart)=0;
	virtual bool GetAscanStart(int iCycle,double *pdStart)=0;
	virtual bool CheckAscanStart(double &dStart) = 0;
	// Functions to handle MC channels.
	virtual bool SetAscanStart(int iCycle, int iChannelCount, int *piChannels, double *pdStart);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetAscanStart(int iCycle, int iArraysize, int *piChannelCount, double *pdStart);
	virtual bool SetAscanStart(int iCycle, int iChannel, double &dStart);
	virtual bool GetAscanStart(int iCycle, int iChannel, double *pdStart);
public:

public:

	virtual bool SetAscanRange(int iCycle,double &dRange,/*output only*/enumCompressionType &eCompressionType,/*output only*/LONG &lPointCount,/*output only*/LONG &lPointFactor)=0;//point count is automatically calculated from the digitizing clock.
			//Input is the range, this function determines the point count, the digitizing frequency is the default HW clock (normally 100 MHz).
	virtual bool SetAscanRangeWithFactor(int iCycle,double &dRange,enumCompressionType &eCompressionType,/*in/out*/LONG &lPointFactor,/*output only*/LONG &lPointCount)=0;
			//Inputs are range + factor, this function determines the point count.
			//two compressions are available:
			//	"eCompression": compression with minimum and maximum.
			//	"eDecimation": compression fixed digitizing frequency (no minimum and maximum).
			//DigitizingFrequency = clock x lPointFactor / 256
			//normally clock=100 MHz
			//"lPointFactor" range is 1 to 256.
	virtual bool SetAscanRangeWithCount(int iCycle,double &dRange,/*in/out (check)*/enumCompressionType &eCompressionType,/*in/out (check)*/LONG &lPointCount,/*output only*/LONG &lPointFactor)=0;
	virtual bool GetAscanRange(int iCycle,double *pdRange,enumCompressionType *peCompressionType,LONG *plPointCount,LONG *plPointFactor)=0;
	// Functions to handle MC channels.
	// Single channel
	virtual bool SetAscanRange(int iCycle, int iChannel, double &dRange,/*output only*/enumCompressionType &eCompressionType,/*output only*/LONG &lPointCount,/*output only*/LONG &lPointFactor);//point count is automatically calculated from the digitizing clock. //MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool SetAscanRangeWithFactor(int iCycle, int iChannel, double &dRange, enumCompressionType &eCompressionType,/*in/out*/LONG &lPointFactor,/*output only*/LONG &lPointCount);
	virtual bool SetAscanRangeWithCount(int iCycle, int iChannel, double &dRange,/*in/out (check)*/enumCompressionType &eCompressionType,/*in/out (check)*/LONG &lPointCount,/*output only*/LONG &lPointFactor);
	virtual bool GetAscanRange(int iCycle, int iChannel, double *pdRange, enumCompressionType *peCompressionType, LONG *plPointCount, LONG *plPointFactor);
	// Channel list
	virtual bool SetAscanRange(int iCycle, int iChannelCount, int *piChannels, double *pdRange,/*output only*/enumCompressionType *peCompressionType,/*output only*/LONG *plPointCount,/*output only*/LONG *plPointFactor);
	// The following 2 functions should be used only if 'peCompressionType' is the same for all channels.
	virtual bool SetAscanRangeWithFactor(int iCycle, int iChannelCount, int *piChannels, double *pdRange,/*output only*/enumCompressionType *peCompressionType,/*in/out*/LONG *plPointFactor,/*output only*/LONG *plPointCount);
	virtual bool SetAscanRangeWithCount(int iCycle, int iChannelCount, int *piChannels, double *pdRange,/*in/out (check)*/enumCompressionType *peCompressionType,/*in/out (check)*/LONG *plPointCount,/*output only*/LONG *plPointFactor);
	virtual bool GetAscanRange(int iCycle, int iArraysize, int *piChannelCount, double *pdRange, enumCompressionType *peCompressionType, LONG *plPointCount, LONG *plPointFactor);//MERGE_PAMINI_PAMAX_MC renaming?

	virtual bool CheckAscanRange(double &dRange)=0;
	virtual bool CheckPointCount(LONG &lPointCount) = 0;
	virtual bool CheckPointCount(LONG &lPointCount, enumBitSize eAscanBitSize) = 0;
	virtual bool CheckPointFactor(LONG &lPointFactor) = 0;
	virtual bool CheckAscanRangeWithCount(double &dRange,enumCompressionType &eCompressionType,LONG &lPointCount)=0;
	virtual bool GetSamplingFrequency(enumCompressionType eCompressionType,LONG lPointFactor,double &dSamplingFrequency/*Hertz*/)=0;
public:
#ifdef _DECIMATION_TIME_CORRECTION_
#endif //_DECIMATION_TIME_CORRECTION_

public:

	virtual bool SetFilterIndex(int iCycle,enumOEMPAFilterIndex eFilterIndex)=0;
	virtual bool GetFilterIndex(int iCycle,enumOEMPAFilterIndex *peFilterIndex)=0;
	// Functions to handle MC channels.
	virtual bool SetFilterIndex(int iCycle, int iChannelCount, int *piChannels, enumOEMPAFilterIndex *peFilterIndex);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetFilterIndex(int iCycle, int iArraysize, int *piChannelCount, enumOEMPAFilterIndex *peFilterIndex);
	virtual bool SetFilterIndex(int iCycle, int iChannel, enumOEMPAFilterIndex &eFilterIndex);
	virtual bool GetFilterIndex(int iCycle, int iChannel, enumOEMPAFilterIndex *peFilterIndex);
public:

public:

	double GetAscanThroughput(double dTimeSlot, LONG lAscanPointCount, enumBitSize eAscanBitSize);//useful data throughput not LAN throughput (data header is not taken into account).
	bool GetThroughputMaximumBitSize(double dTimeSlot, LONG lAscanPointCount, enumBitSize &eAscanBitSize);
	bool GetThroughputMaximumPointCount(double dTimeSlot, LONG &lAscanPointCount, enumBitSize eAscanBitSize);
	bool GetThroughputMinimumTimeSlot(double &dTimeSlot, LONG lAscanPointCount, enumBitSize eAscanBitSize);
	virtual double vf_GetMinTimeSlotRecovery(LONG lAscanPointCount, enumBitSize eAscanBitSize);//Minimum timeSlot for maximum useful data throughput (not LAN throughput, data header is not taken into account).
	virtual double vf_GetMinTimeSlotRecovery(structCheckRecoveryTimePA *pRecoveryTimePA) = 0;
	virtual double vf_GetMinTimeSlotRecovery(DWORD channels, enumBitSize eAscanBitSize, enumCompressionType *eCompressionType, LONG* pointCounts, LONG* pointFactors, LONG* starts, LONG* ranges, LONG* wedgesE, LONG* wedgesR) = 0;
	virtual double vf_GetMaxRangeRecovery(structCheckRecoveryTimePA* pRecoveryTimePA) = 0;

	virtual bool SetTimeSlot(int iCycle,double &dTimeSlot)=0;
	virtual bool GetTimeSlot(int iCycle,double *pdTimeSlot)=0;
	virtual bool CheckTimeSlot(double &dTimeSlot)=0;
	//FMC SubTimeSlot management
	virtual bool SetFMCSubTimeSlotAcqReplay(int iCycle,double dAscanStart,double dAscanRange,double &dTimeSlot)=0;//easy function to use
	virtual bool GetFMCTimeLimitation(double dAscanStart,double dAscanRange,double dTimeSlot,double &dTimeSlotMin,double &dHWAcqSubTimeSlotMin,double &dReplaySubTimeSlotMin,double &dReplaySubTimeSlotOptimizedForThroughput)=0;
	virtual bool GetFMCTimeLimitation(int iFMCSubCycleCount,double dAscanStart,double dAscanRange,double dTimeSlot,double &dTimeSlotMin,double &dHWAcqSubTimeSlotMin,double &dReplaySubTimeSlotMin,double &dReplaySubTimeSlotOptimizedForThroughput)=0;
	virtual int GetFMCSubTimeSlotCount()=0;
	//instead to call "SetFMCSubTimeSlotAcq" and "SetFMCSubTimeSlotReplay" you can call "SetFMCSubTimeSlotAcqReplay" which is easier to use.
	virtual bool SetFMCSubTimeSlotAcq(int iCycle,double &dSubTimeSlot)=0;
	virtual bool SetFMCSubTimeSlotReplay(int iCycle,double &dSubTimeSlot)=0;
	virtual bool GetFMCSubTimeSlotAcq(int iCycle,double *pdSubTimeSlot)=0;
	virtual bool GetFMCSubTimeSlotReplay(int iCycle,double *pdSubTimeSlot)=0;
public:
protected:
	virtual bool TranslateTimeSlot(structNotificationOption &optionNotification, double &dTimeSlot, DWORD &dwHWDataParameter) = 0;
	virtual bool TranslateTimeSlot(DWORD &dwHWDataParameter, double &dTimeSlot) = 0;
public:

public:

	virtual bool SetAscanAcqIdChannelProbe(int iCycle,WORD &wID)=0;
	virtual bool GetAscanAcqIdChannelProbe(int iCycle,WORD *pwID)=0;
	// Functions to handle MC channels.
	virtual bool SetAscanAcqIdChannelProbe(int iCycle, int iChannelCount, int *piChannels, WORD *pwID);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetAscanAcqIdChannelProbe(int iCycle, int iArraysize, int *piChannelCount, WORD *pwID);
	virtual bool SetAscanAcqIdChannelProbe(int iCycle, int iChannel, WORD &wID);
	virtual bool GetAscanAcqIdChannelProbe(int iCycle, int iChannel, WORD *pwID);
public:

public:

	virtual bool SetAscanAcqIdChannelScan(int iCycle,WORD &wID)=0;
	virtual bool GetAscanAcqIdChannelScan(int iCycle,WORD *pwID)=0;
	// Functions to handle MC channels.
	virtual bool SetAscanAcqIdChannelScan(int iCycle, int iChannelCount, int *piChannels, WORD *pwID);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetAscanAcqIdChannelScan(int iCycle, int iArraysize, int *piChannelCount, WORD *pwID);
	virtual bool SetAscanAcqIdChannelScan(int iCycle, int iChannel, WORD &wID);
	virtual bool GetAscanAcqIdChannelScan(int iCycle, int iChannel, WORD *pwID);
public:

public:

	virtual bool SetAscanAcqIdChannelCycle(int iCycle,WORD &wID)=0;
	virtual bool GetAscanAcqIdChannelCycle(int iCycle,WORD *pwID)=0;
	// Functions to handle MC channels.
	virtual bool SetAscanAcqIdChannelCycle(int iCycle, int iChannelCount, int *piChannels, WORD *pwID);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetAscanAcqIdChannelCycle(int iCycle, int iArraysize, int *piChannelCount, WORD *pwID);
	virtual bool SetAscanAcqIdChannelCycle(int iCycle, int iChannel, WORD &wID);
	virtual bool GetAscanAcqIdChannelCycle(int iCycle, int iChannel, WORD *pwID);
public:

public:

	virtual bool EnableAscanMaximum(int iCycle,bool bEnable)=0;
	virtual bool GetEnableAscanMaximum(int iCycle,bool *pbEnable)=0;
public:

public:

	virtual bool EnableAscanMinimum(int iCycle,bool bEnable)=0;
	virtual bool GetEnableAscanMinimum(int iCycle,bool *pbEnable)=0;
public:

public:

	virtual bool EnableAscanSaturation(int iCycle,bool bEnable)=0;
	virtual bool GetEnableAscanSaturation(int iCycle,bool *pbEnable)=0;
public:

public:

	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool bEnable,double dThresholdPercent,enumGateModeAmp eGateModeAmp,enumGateModeTof eGateModeTof,enumRectification eGateRectification)=0;
	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool bEnable,double dThresholdPercent,enumGateModeAmp eGateModeAmp,enumGateModeTof eGateModeTof,enumRectification eGateRectification, unsigned int uMultiPeakCountMax, double dMultiPeakExclusionInterval);
	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool bEnable,double dThresholdPercent,enumGateModeAmp eGateModeAmp,enumGateModeTof eGateModeTof,enumRectification eGateRectification, enumGateTarget eTarget);
	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool bEnable,double dThresholdPercent,enumGateModeAmp eGateModeAmp,enumGateModeTof eGateModeTof,enumRectification eGateRectification, enumGateTarget eTarget, unsigned int uMultiPeakCountMax, double dMultiPeakExclusionInterval);
	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool &bEnable,enumGateModeAmp &eGateModeAmp,enumGateModeTof &eGateModeTof,enumRectification &eGateRectification,double &dThresholdPercent)=0;
	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool& bEnable,enumGateModeAmp& eGateModeAmp,enumGateModeTof& eGateModeTof,enumRectification& eGateRectification,double& dThresholdPercent, unsigned int uMultiPeakCountMax, double dMultiPeakExclusionInterval);
	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool &bEnable,enumGateModeAmp &eGateModeAmp,enumGateModeTof &eGateModeTof,enumRectification &eGateRectification,double &dThresholdPercent, enumGateTarget eTarget);
	virtual bool GetGateModeThreshold(int iCycle,int iGate,bool *pbEnable,enumGateModeAmp *peGateModeAmp,enumGateModeTof *peGateModeTof,enumRectification *peGateRectification,double *pdThresholdPercent)=0;
	virtual bool GetGateModeThreshold(int iCycle,int iGate,bool *pbEnable,enumGateModeAmp *peGateModeAmp,enumGateModeTof *peGateModeTof,enumRectification *peGateRectification,double *pdThresholdPercent, unsigned int* puMultiPeakCountMax, double* pdMultiPeakExclusionInterval);
	virtual bool GetGateModeThreshold(int iCycle,int iGate, enumGateTarget &eTarget,bool *pbEnable,enumGateModeAmp *peGateModeAmp,enumGateModeTof *peGateModeTof,enumRectification *peGateRectification,double *pdThresholdPercent);
	virtual bool GetGateModeThreshold(int iCycle,int iGate, enumGateTarget& eTarget,bool *pbEnable,enumGateModeAmp *peGateModeAmp,enumGateModeTof *peGateModeTof,enumRectification *peGateRectification,double *pdThresholdPercent, unsigned int* puMultiPeakCountMax, double* pdMultiPeakExclusionInterval);
	virtual bool CheckGateModeThreshold(bool &bEnable,enumGateModeAmp &eGateModeAmp,enumGateModeTof &eGateModeTof,enumRectification &eGateRectification,double &dThresholdPercent)=0;
	// Functions to handle MC channels.
	virtual bool SetGateModeThreshold(int iCycle, int iChannel, int iGate, bool &bEnable, enumGateModeAmp &eGateModeAmp, enumGateModeTof &eGateModeTof, enumRectification &eGateRectification, double &dThresholdPercent);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool SetGateModeThreshold(int iCycle, int iChannel, int iGate, bool bEnable, double dThresholdPercent, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification);
	virtual bool GetGateModeThreshold(int iCycle, int iChannel, int iGate, bool *pbEnable, enumGateModeAmp *peGateModeAmp, enumGateModeTof *peGateModeTof, enumRectification *peGateRectification, double *pdThresholdPercent);
public:

public:

	virtual bool SetGateStart(int iCycle,int iGate,double &dStart)=0;
	virtual bool SetGateStart(int iCycle,int iGate,double &dStart, enumGateTarget eTarget);
	virtual bool GetGateStart(int iCycle,int iGate,double *pdStart)=0;
	virtual bool GetGateStart(int iCycle,int iGate, enumGateTarget &eTarget,double *pdStart);
	virtual bool CheckGateStart(double &dStart)=0;
	// Functions to handle MC channels.
	virtual bool SetGateStart(int iCycle, int iChannel, int iGate, double &dStart);
	virtual bool GetGateStart(int iCycle, int iChannel, int iGate, double *pdStart);
public:

public:

	virtual bool CheckGateStartStop(double &dStart,double &dStop)=0;
	virtual bool SetGateStop(int iCycle,int iGate,double &dStop)=0;
	virtual bool SetGateStop(int iCycle,int iGate,double &dStop, enumGateTarget eTarget);
	virtual bool GetGateStop(int iCycle,int iGate,double *pdStop, bool *pbWidth = NULL)=0;
	virtual bool GetGateStop(int iCycle,int iGate, enumGateTarget &eTarget,double *pdStop, bool *pbWidth = NULL);
	virtual bool CheckGateStop(double &dStop)=0;
	// Functions to handle MC channels.
	virtual bool SetGateStop(int iCycle, int iChannel, int iGate, double &dStop);
	virtual bool GetGateStop(int iCycle, int iChannel, int iGate, double *pdStop, bool *pbWidth = NULL);
public:

public:

	virtual bool SetGateWidth(int iCycle, int iGate, double &dWidth);
	virtual bool SetGateWidth(int iCycle, int iGate, double &dWidth, enumGateTarget eTarget);
	virtual bool GetGateWidth(int iCycle, int iGate, double *pdWidth, bool *pbWidth);
	virtual bool GetGateWidth(int iCycle, int iGate, enumGateTarget &eTarget, double *pdWidth, bool *pbWidth);
	virtual bool CheckGateWidth(double &dRange);
	// Functions to handle MC channels.
	virtual bool SetGateWidth(int iCycle, int iChannel, int iGate, double &dWidth);
	virtual bool GetGateWidth(int iCycle, int iChannel, int iGate, double *pdWidth);
public:

public:

	virtual bool SetGateAcqIDAmp(int iCycle,int iGate,WORD &wID)=0;
	virtual bool GetGateAcqIDAmp(int iCycle,int iGate,WORD *pwID)=0;
	virtual bool SetGateAcqIDTof(int iCycle,int iGate,WORD &wID)=0;
	virtual bool GetGateAcqIDTof(int iCycle,int iGate,WORD *pwID)=0;
	// Functions to handle MC channels.
	virtual bool SetGateAcqIDAmp(int iCycle, int iChannel, int iGate, WORD &wID);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetGateAcqIDAmp(int iCycle, int iChannel, int iGate, WORD *pwID);
	virtual bool SetGateAcqIDTof(int iCycle, int iChannel, int iGate, WORD &wID);
	virtual bool GetGateAcqIDTof(int iCycle, int iChannel, int iGate, WORD *pwID);
public:

public:

	virtual bool SetTrackingGateStart(int iCycle,int iGate,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex)=0;
	virtual bool GetTrackingGateStart(int iCycle,int iGate,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex)=0;
	virtual bool SetSWTrackingGateStartFromHW(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex)=0;
	virtual bool GetSWTrackingGateStartFromHW(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex)=0;
	virtual bool SetTrackingGateStop(int iCycle,int iGate,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex)=0;
	virtual bool GetTrackingGateStop(int iCycle,int iGate,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex)=0;
	virtual bool SetSWTrackingGateStopFromHW(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex)=0;
	virtual bool GetSWTrackingGateStopFromHW(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex)=0;
	virtual bool SetTrackingAscan(int iCycle,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex)=0;
	virtual bool GetTrackingAscan(int iCycle,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex)=0;
	virtual bool SetTrackingDac(int iCycle,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex)=0;
	virtual bool GetTrackingDac(int iCycle,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex)=0;
	virtual bool CheckTracking(bool bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex)=0;
	virtual bool ResetTrackingTable()=0;//this is called automatically when the IF tracking of one gate is updated.
	// Functions to handle MC channels.
	virtual bool SetTrackingGateStart(int iCycle, int iChannel, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetTrackingGateStart(int iCycle, int iChannel, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);
	virtual bool SetTrackingGateStop(int iCycle, int iChannel, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool GetTrackingGateStop(int iCycle, int iChannel, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);
	virtual bool SetTrackingAscan(int iCycle, int iChannel, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool GetTrackingAscan(int iCycle, int iChannel, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);
	virtual bool SetTrackingDac(int iCycle, int iChannel, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool GetTrackingDac(int iCycle, int iChannel, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);
public:

public:
	// Bipolar high voltage control, positive = [25; 100], negative = [-100; -25], abs(negative) >= positive. Unit is Volt.
	virtual bool SetHighVoltageBipolar(int &positive, int &negative);//MERGE_PAMINI_PAMAX_MC
	virtual bool GetHighVoltageBipolar(int *positive, int *negative);
	// Capacitive (negative) high voltage control, voltage = [25; 400]. Unit is Volt. Negative values in the same range are also valid.
	virtual bool SetHighVoltage(int &voltage);
	virtual bool GetHighVoltage(int *voltage);//MERGE_PAMINI_PAMAX_MC

	virtual bool SetGainAnalog(int iCycle,float &fGain)=0;
	virtual bool GetGainAnalog(int iCycle,float *pfGain)=0;
	virtual bool CheckGainAnalog(float &fGain) = 0;
	// Functions to handle MC channels.
	virtual bool SetGainAnalog(int iCycle, int iChannel, float &fGain);
	virtual bool GetGainAnalog(int iCycle, int iChannel, float* pfGain);
public:

public:

	//For some of the following functions the CycleCount is required
	//("iCycleCount" should be the total cycle count of the sequence)
	//("pdWedgeDelay" is not an array but a pointer on a single double)
	//("iCountMax" is the maximum vamlue of the cycle count)
	virtual bool SetEmissionWedgeDelay(int iCycle,int iCycleCount,double &dWedgeDelay)=0;//"iCycleCount"=cycle count.
	virtual bool GetEmissionWedgeDelay(int iCycle,int iCountMax,double *pdWedgeDelay)=0;
	virtual bool SetReceptionWedgeDelay(int iCycle,int iCycleCount,double &dWedgeDelay)=0;
	virtual bool GetReceptionWedgeDelay(int iCycle,int iCountMax,double *pdWedgeDelay)=0;
	virtual bool CheckWedgeDelay(double &dWedgeDelay)=0;
	// Functions to handle MC channels.
	virtual bool SetEmissionWedgeDelay(int iCycle, int iChannelCount, int *piChannels, double *pdWedgeDelay);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetEmissionWedgeDelay(int iCycle, int iArraysize, int *piChannelCount, double *pdWedgeDelay);
	virtual bool SetEmissionWedgeDelaySingleChannel(int iCycle, int iChannel, double &dWedgeDelay);
	virtual bool GetEmissionWedgeDelaySingleChannel(int iCycle, int iChannel, double *pdWedgeDelay);
	virtual bool SetReceptionWedgeDelay(int iCycle, int iChannelCount, int *piChannels, double *pdWedgeDelay);
	virtual bool GetReceptionWedgeDelay(int iCycle, int iArraysize, int *piChannelCount, double *pdWedgeDelay);
	virtual bool SetReceptionWedgeDelaySingleChannel(int iCycle, int iChannel, double &dWedgeDelay);
	virtual bool GetReceptionWedgeDelaySingleChannel(int iCycle, int iChannel, double *pdWedgeDelay);
public:

public:

//OLD STYLE FUNCTIONS (limited to 128 elements).
	//APERTURE DEFINITION : 2 cases.
	virtual bool IsMultiplexer();//this function can be used to know if a multiplexer (16:128 or 32:128) is included in the system.
	//Case of a system with a multiplexer (16:128 or 32:128), please use following functions:
	//	multiplexer case: if emission and reception have same aperture:
	virtual bool SetMultiplexerEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetMultiplexerEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	//	multiplexer case: if emission and reception aperture are different:
	//	(you cannot have more than 32 elements in case of a 32/128 and 16 elements in case of a 16/128).
	virtual bool SetMultiplexerEnable(int iCycle,DWORD adwHWApertureEmission[g_iOEMPAApertureDWordCount],DWORD adwHWApertureReception[g_iOEMPAApertureDWordCount]);
	virtual bool GetMultiplexerEnable(int iCycle,DWORD adwHWApertureEmission[g_iOEMPAApertureDWordCount],DWORD adwHWApertureReception[g_iOEMPAApertureDWordCount]);
	virtual bool CheckMultiplexerAperture(DWORD adwHWApertureEmission[g_iOEMPAApertureDWordCount],DWORD adwHWApertureReception[g_iOEMPAApertureDWordCount]);//to check that emission and reception apertures are coherent.
	//Case of a system (16:16, 32:32, 64:64 etc...) without a multiplexer, then please use the following functions:
	virtual bool SetEmissionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetEmissionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool SetReceptionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetReceptionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool SetReceptionMatchedDevicesEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);//usefull for matched devices only.
	virtual bool SetReceptionEnable256(bool bMaster,int iCycle,DWORD adwHWAperture[2*g_iOEMPAApertureDWordCount]);

	virtual bool SetEmissionDelays(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfDelay);
	virtual bool SetEmissionDelays(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool SetEmissionWidths(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfWidth);
	virtual bool SetEmissionWidths(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool SetReceptionGains(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfGain);
	virtual bool SetReceptionGains(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool SetReceptionDelays(int iCycle,int iLineSize,int &iFocalCount,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfDelay);
	virtual bool SetReceptionDelays(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat2D &callbackArrayFloat2D);

//NEW STYLE FUNCTIONS (no limitation for the aperture).
	virtual bool SetMultiplexerEnable(int iCycle, int iEltCntEmission, int iEltCntReception, int *piEltListEmission, int *piEltListReception);
	virtual bool SetMultiplexerEnable(int iCycle, int iApertureSize, DWORD *pdwApertureEmission, DWORD *pdwApertureReception);
	virtual bool GetMultiplexerEnable(int iCycle, int iEltCntEmission, int iEltCntReception, int *piEltListEmission, int *piEltListReception);
	virtual bool GetMultiplexerEnable(int iCycle, int iEltCntEmission, int iEltCntReception, structCallbackArrayInt1D& callbackArrayInt1DEm, structCallbackArrayInt1D& callbackArrayInt1DRec);
	virtual bool GetMultiplexerEnable(int iCycle, int iApertureSize, DWORD *pdwApertureEmission, DWORD *pdwApertureReception);
	virtual bool GetMultiplexerEnable(int iCycle, int iEltCountMaxEmission, int iEltCountMaxReception, int *piEltCountEmission, int *piEltCountReception, int *piEltListEmission, int *piEltListReception);//MERGE_PAMINI_PAMAX_MC
	virtual bool CheckMultiplexerAperture(int iEltCntEmission, int iEltCntReception, int *piEltListEmission, int *piEltListReception);//to check that emission and reception apertures are coherent.

	virtual bool SetEmissionEnable(int iCycle, int iElementCount, int *piElementList);
	virtual bool SetEmissionEnable(int iCycle, int iApertureSize, DWORD *pdwApertureEmission);
	virtual bool GetEmissionEnable(int iCycle, int iElementCountMax, int *piElementCount,int *piElementList);
	virtual bool GetEmissionEnable(int iCycle, int iElementCountMax, structCallbackArrayInt1D& callbackArrayInt1D);
	virtual bool GetEmissionEnable(int iCycle, int iApertureSize, DWORD *pdwApertureEmission);
	virtual bool GetEmissionEnable(int iCycle, int iArraySize, int *piChannelCount, DWORD *pdwAperture);	// To have elem count and aperture in a single call, for medium level.//MERGE_PAMINI_PAMAX_MC
	virtual bool SetReceptionEnable(int iCycle,int iElementCount,int *piElementList);
	virtual bool SetReceptionEnable(int iCycle, int iApertureSize, DWORD *pdwApertureReception);
	virtual bool GetReceptionEnable(int iCycle,int iElementCountMax,int *piElementCount,int *piElementList);
	virtual bool GetReceptionEnable(int iCycle, int iElementCountMax, structCallbackArrayInt1D& callbackArrayInt1D);
	virtual bool GetReceptionEnable(int iCycle, int iApertureSize, DWORD *pdwApertureReception);
	virtual bool DisableEmission(int iCycle);//MERGE_PAMINI_PAMAX_MC

	virtual bool SetEmissionEnableBipolar(int iCycle, int iChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetEmissionEnableBipolar(int iCycle, int iArraySize, int *piChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetEmissionEnableBipolar(int iCycle, int iChannelCountMax, int *piChannelCount, DWORD *pdwAperture, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList);//...
	virtual bool SetEmissionEnableBipolar(int iCycle, int iChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList, float *pfPulseDelayList);
	virtual bool GetEmissionEnableBipolar(int iCycle, int iArraySize, int *piChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList, float *pfPulseDelayList);
	virtual bool GetEmissionEnableBipolar(int iCycle, int iChannelCountMax, int *piChannelCount, DWORD *pdwAperture, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList, float *pfPulseDelayList);
	virtual bool SetEmissionEnableBipolar(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetEmissionEnableBipolar(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool SetEmissionEnableBipolar(int iCycle, int iChannelCount, int *piChannelList);
	virtual bool GetEmissionEnableBipolar(int iCycle, int iArraySize, int *piCount, int *piChannelList);
	virtual bool DisableEmissionBipolar(int iCycle);

	virtual bool SetEmissionBipolarPulse(int iCycle, int iChannel, int &iPulseCount, float &fPulseWidth, float &fPulsePeriod);
	virtual bool GetEmissionBipolarPulse(int iCycle, int iChannel, int *iPulseCount, float *fPulseWidth, float *fPulsePeriod);
	virtual bool SetEmissionBipolarPulse(int iCycle, int iChannel, int &iPulseCount, float &fPulseWidth, float &fPulsePeriod, float &fPulseDelay);
	virtual bool GetEmissionBipolarPulse(int iCycle, int iChannel, int *iPulseCount, float *fPulseWidth, float *fPulsePeriod, float *pfPulseDelay);
	virtual bool SetEmissionBipolarDelay(int iCycle, int iChannel, float &fPulseDelay);//...
	virtual bool GetEmissionBipolarDelay(int iCycle, int iChannel, float *pfPulseDelay);//MERGE_PAMINI_PAMAX_MC renaming?

	virtual bool SetEmissionDelay(int iCycle, int iChannel, float &fDelay);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetEmissionDelay(int iCycle, int iChannel, float *pfDelay);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool SetEmissionDelays(int iCycle,int iElementCount,int *piElementList,float *pfDelay);
	virtual bool GetEmissionDelays(int iCycle,int &iElementCountMax,int *piElementCount,float *pfDelay);
	virtual bool SetEmissionDelays(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	virtual bool GetEmissionDelays(int iCycle,int &iElementCountMax,structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	//virtual bool SetEmissionWidth(int iCycle,int iElementIndex,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float &fWidth);
	virtual bool SetEmissionWidth(int iCycle, int iChannel, float &fWidth);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool GetEmissionWidth(int iCycle, int iChannel, float *pfWidth);//MERGE_PAMINI_PAMAX_MC renaming?
	virtual bool SetEmissionWidths(int iCycle,int iElementCount,int *piElementList,float *pfWidth);
	virtual bool GetEmissionWidths(int iCycle,int &iElementCountMax,int *piElementCount,float *pfWidth);
	virtual bool SetEmissionWidths(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool GetEmissionWidths(int iCycle,int &iElementCountMax,structCallbackArrayFloat1D &callbackArrayFloat1D);
	//virtual bool SetReceptionGain(int iCycle,int iElementIndex,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float &fGain);
	virtual bool SetReceptionGains(int iCycle,int iElementCount,int *piElementList,float *pfGain);
	virtual bool GetReceptionGains(int iCycle,int &iElementCountMax,int *piElementCount,float *pfGain);
	virtual bool SetReceptionGains(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool GetReceptionGains(int iCycle,int &iElementCountMax,structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool SetReceptionDelays(int iCycle,int &iFocalCount,int iElementCount,int *piElementList,float *pfDelay);
	virtual bool GetReceptionDelays(int iCycle,int iLineSize,int &iElementCountMax,int &iFocalCountMax,int *piElementCount,int *piFocalCount,float *pfDelay);
	virtual bool SetReceptionDelays(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.
	virtual bool GetReceptionDelays(int iCycle,int &iElementCountMax,int &iFocalCountMax,structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.

	virtual bool SetReceptionFocusing(int iCycle,int &iFocalCount,double *pdFocalTof)=0;
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,int *piFocalCount,double *pdFocalTof)=0;
	virtual bool SetReceptionFocusing(int iCycle,structCallbackArrayDouble1D &callbackArrayDouble1D)=0;
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,structCallbackArrayDouble1D &callbackArrayDouble1D)=0;
	virtual bool SetReceptionFocusing(int iCycle,int &iFocalCount,double *pdFocalTof,float &fCenterDelayE,float &fCenterDelayR)=0;
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,int *piFocalCount,double *pdFocalTof,float *pfCenterDelayE,float *pfCenterDelayR)=0;
	virtual bool SetReceptionFocusing(int iCycle,structCallbackArrayDouble1D &callbackArrayDouble1D,float &fCenterDelayE,float &fCenterDelayR)=0;
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,structCallbackArrayDouble1D &callbackArrayDouble1D,float *pfCenterDelayE,float *pfCenterDelayR)=0;
	virtual bool GetReceptionNormalisationDelayAv(bool bEmission,int iElementCount,int *piElementList,float &fDelay)=0;
	virtual bool EnableDDF(int iCycle,bool bEnable)=0;
	virtual bool GetEnableDDF(int iCycle,bool *pbEnable)=0;
	virtual bool EnableDDF(int iCycle,enumFocusing &eFocusing)=0;
	virtual bool GetEnableDDF(int iCycle,enumFocusing *peFocusing)=0;
	virtual bool CheckFocalTimeOfFlight(double &dDelay)=0;
	virtual bool CheckEmissionWidth(float &fWidth)=0;
	virtual bool CheckReceptionGain(float &fGain)=0;
	virtual bool CheckEmissionDelay(float &fDelay)=0;
	virtual bool CheckReceptionDelay(float &fDelay)=0;
	virtual DWORD GetSWBaseAddress()=0;
	static void SetDDFTimeOfFlightMiddle(bool bEnable);
	static bool IsDDFTimeOfFlightMiddle();
	static void SetDDFWaveTrackingCorrection(int iEnable);
	static int GetDDFWaveTrackingCorrection();
	static void SetFMCReceptionSimplified(bool bEnable);
	static bool IsFMCReceptionSimplified();
public:
	virtual bool SetEmissionWidths2(int iCycle, DWORD adwHWAperture[g_iOEMPAminiApertureDWordCount * g_iAssociationSubDeviceCountMax], float *pfWidth);
	virtual bool SetEmissionDelays2(int iCycle, DWORD adwHWAperture[g_iOEMPAminiApertureDWordCount * g_iAssociationSubDeviceCountMax], float *pfDelay);
	virtual bool SetReceptionGains2(int iCycle, DWORD adwHWAperture[g_iOEMPAminiApertureDWordCount * g_iAssociationSubDeviceCountMax], float *pfGain);
	virtual bool SetReceptionDelays2(int iCycle, int &iFocalCount, DWORD adwHWAperture[g_iOEMPAminiApertureDWordCount * g_iAssociationSubDeviceCountMax], float *pfDelay);
#ifdef _DECIMATION_TIME_CORRECTION_
#endif //_DECIMATION_TIME_CORRECTION_

public:
	virtual bool EnableMultiHWChannelAcquisition(int iCycle,int iCycleCount,bool bEnable);
	virtual bool GetEnableMultiHWChannelAcquisition(int iCycle,bool *pbEnable);
	virtual bool SetMultiHWChannelAcqDecimation(int iCycle,unionOEMMCDecimation &hwAcqDecimation);
	virtual bool GetMultiHWChannelAcqDecimation(int iCycle,unionOEMMCDecimation *hwAcqDecimation);
	virtual bool GetMultiHWChannelAcqDecimation(int iCycle,structCallbackArrayByte1D &callbackArrayByte1D);
	//A-scan Start is specified for consecutive elements from the first single element #1 (index base 1, no gap between elements).
	virtual bool SetMultiHWChannelAcqWriteStart(int iCycle,int iAcqElement,int iStartCount,float *pfStart);
			//input "iAcqElement": element for which ascan is sent to the computer.
			//input "iStartCount": element count of the array "pfStart".
			//input "pfStart": array of ascan start from the first element probe (element #1, 1 base index).
	virtual bool GetMultiHWChannelAcqWriteStart(int iCycle,int &iStartCountMax,int *piStartCount,float *pfStart);
	virtual bool SetMultiHWChannelAcqWriteStart(int iCycle,int iAcqElement,int iStartCount,structCallbackArrayFloat1D &callbackArrayFloat1D);//Size1 = element size.
	virtual bool GetMultiHWChannelAcqWriteStart(int iCycle,int &iStartCountMax,structCallbackArrayFloat1D &callbackArrayFloat1D);//Size1 = element size.
	virtual double GetMultiHWChannelRangeMax();//unit us.
public:

public:

	virtual bool SetSettingId(DWORD dwSettingId)=0;
	virtual bool GetSettingId(DWORD *pdwSettingId)=0;//ask hw as for others functions.
public:

public:

	//in case of Ethernet, KeepAlive is useful to prevent communication deadlock
	//but if the developper stay a LONG time inside a breakpoint it will break the socket.
	virtual bool SetKeepAlive(enumKeepAlive eKeepAlive)=0;
	virtual bool GetKeepAlive(enumKeepAlive *peKeepAlive)=0;//ask hw as for others functions.
public:

public:

	//calibration management
	virtual bool SetTimeOffset(float &fTime)=0;
	virtual bool GetTimeOffset(float *pfTime)=0;
public:

public:

	virtual bool SetStreamMode(int iCycle, int iMode);
	virtual bool GetStreamMode(int iCycle, int *piMode);

	virtual bool TestFWMemoryCycle(int iCycleCount,DWORD dwData)=0;
	virtual bool TestFWMemoryFilter(int iFilterCount,DWORD dwData)=0;
	virtual bool SetPulserDisabled(bool bDisable);//ljr max1024
	virtual bool GetPulserDisabled(bool *pbDisable);//ljr max1024
//<<PARAMETERS MANAGEMENT FUNCTIONS : END>>

public:
public://don't use following functions

public:
public:

	static void EnableConnectionShortcutWarningDisplay(bool bWarningDisplay);
	static bool IsConnectionShortcutWarningDisplayEnabled();
public:
public:
protected:
public:
	virtual bool vf_CheckSetupHW(enumAcquisitionState &eAcqState, structNotificationOption &optionNotification);
	virtual bool vf_CheckSetupHW_MC(enumAcquisitionState& eAcqState, structNotificationOption& optionNotification);
	virtual bool vf_UpdateSetupSW(int iStep, int iCheckConsistancy, structNotificationOption &optionNotification);
	virtual bool vf_GetSockBufferSize(int &iSizeSend, int &iSizeReceive);
	virtual bool vf_CheckSetupGain(structNotificationOption &optionNotification, bool bCheckValue, int iCycle, enumCheckSetupGain eType, void* val, void* val2);
	virtual bool vf_CheckSetupGain(structNotificationOption &optionNotification, bool bCheckValue, int iCycle, int iChannel, enumCheckSetupGain eType, void* val, void* val2);
	virtual bool vf_CheckSetupTime(structNotificationOption &optionNotification, bool bCheckValue, int iCycle, enumCheckSetupTime eType, void* val, LONG *lPoint);
	virtual bool vf_CheckSetupTime(structNotificationOption &optionNotification, bool bCheckValue, int iCycle, int iChannel, enumCheckSetupTime eType, void* val, LONG *lPoint);
#ifdef _WIN32
	virtual CThreadPerf *vf_GetMergeThreadPerf(int index);
#endif _WIN32

public:
	bool SetChannel(int iChannel);
	int GetChannel();
	static void DisableDisplayFatalErrorCustomizedAPI(bool bDisable);
	static bool IsDisplayFatalErrorCustomizedAPIDisabled();
};
