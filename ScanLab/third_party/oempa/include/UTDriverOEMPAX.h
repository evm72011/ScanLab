
#pragma once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DRIVER_OEMPAX_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DRIVER_OEMPAX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DRIVER_OEMPAX_EXPORTS
#ifdef _WIN32
#define DRIVER_OEMPAX_API __declspec(dllexport)
#define DRIVER_OEMPAX_API_ALIGN __declspec(dllexport) __declspec(align(8))
#elif defined __linux__
#define DRIVER_OEMPAX_API __attribute__((visibility ("default")))
#define DRIVER_OEMPAX_API_ALIGN __attribute__((visibility ("default"))) __attribute__((aligned(8)))
#endif // __linux__
#else
#ifdef _WIN32

#define DRIVER_OEMPAX_API __declspec(dllimport)
#define DRIVER_OEMPAX_API_ALIGN __declspec(dllimport) __declspec(align(8))
#elif defined __linux__
#define DRIVER_OEMPAX_API 
#define DRIVER_OEMPAX_API_ALIGN __attribute__((aligned(8)))
#endif // __linux__
#ifndef _NO_AUTO_INCLUDE_
#ifdef _DRIVER_11XY_
#pragma comment(lib,"UTKernelDriverOEMPAX.lib")
#else //_DRIVER_11XY_
#pragma comment(lib,"UTDriverOEMPAX.lib")
#endif //_DRIVER_11XY_
#endif //_NO_AUTO_INCLUDE_
#endif


#ifndef _DRIVER_OEMPAX_
#define _DRIVER_OEMPAX_
#endif

#ifdef _DRIVER_11XY_
#ifndef _DRIVER_11XY_OEMPAX_
#error Did you include "UTKernelDriver.h" instead of "UTDriverOEMPA.h"?
#endif
#endif //_DRIVER_11XY_


#include "AcquisitionFifo.h"
#include "UTDriverCommon.h"


class CSWDevice;
class CNode;
class CUTDevCommunication;



class CHWDeviceOEMPAX;
class CHWDeviceOEMPAX;

typedef bool (WINAPI *pOEMPAX_ReadFileWriteHW)(CHWDeviceOEMPAX *pOEMPA,const wchar_t *pFileName,enumAcquisitionState eAcqState);
typedef bool (WINAPI *pOEMPAX_ReadFileWriteHWs)(int iCount, CHWDeviceOEMPAX **apHWDeviceOEMPA, const wchar_t *pFileName, enumAcquisitionState eAcqState);
typedef bool (WINAPI *pOEMPAX_ReadFileWriteHW256)(CHWDeviceOEMPAX *pMaster,CHWDeviceOEMPAX *pSlave,wchar_t *pFileNameMaster,wchar_t *pFileNameSlave);
typedef bool (WINAPI *pOEMPAX_CreateDefaultSetupFile)(CHWDeviceOEMPAX *pHWDeviceOEMPA, enumSetupFileType eFileType, wchar_t *wcLoadDefaultSetup);
typedef bool (WINAPI *pOEMPAX_LoadCalibrationSetup)(	CHWDeviceOEMPAX *pHWDeviceOEMPA,bool bCheck,
													float fWidth,float fStart,float fRange,float fGainAnalog,double dGainDigital,
													const wchar_t *wcCalibrationFileInput,const wchar_t *wcCalibrationFileOutput,
													double dFMCTimeSlotFactor,int &iCalibrationPointCount,double &dAcquisitionTime);

DRIVER_OEMPAX_API void WINAPI OEMPAX_SetReadFileWriteHW(pOEMPAX_ReadFileWriteHW pFunc);
DRIVER_OEMPAX_API void WINAPI OEMPAX_SetReadFileWriteHWs(pOEMPAX_ReadFileWriteHWs pFunc);
DRIVER_OEMPAX_API void WINAPI OEMPAX_SetReadFileWriteHW256(pOEMPAX_ReadFileWriteHW256 pFunc);
DRIVER_OEMPAX_API void WINAPI OEMPAX_SetCreateDefaultSetupFile(pOEMPAX_CreateDefaultSetupFile pFunc);
DRIVER_OEMPAX_API void WINAPI OEMPAX_SetLoadCalibrationSetup(pOEMPAX_LoadCalibrationSetup pFunc);
DRIVER_OEMPAX_API void WINAPI OEMPAX_SetLoadCalibrationSetup256(pOEMPAX_LoadCalibrationSetup pFunc);




class DRIVER_OEMPAX_API_ALIGN _CSWDeviceOEMPAX
{
private:
	ULONGLONG m_ullPrivateMemory[800];
protected:

};

class DRIVER_OEMPAX_API_ALIGN CSWDeviceOEMPAX :
	public _CSWDeviceOEMPAX,
#ifdef _DRIVER_11XY_
	public CSWDeviceOEM
#else //_DRIVER_11XY_
	public CSWDeviceOEMPA
#endif //_DRIVER_11XY_
{
public:
#ifdef _DRIVER_11XY_
#include "Struct_SWDeviceOEMPA.h"
#include "11XY\SWDeviceOEMPA1.h"
#endif //_DRIVER_11XY_
	CSWDeviceOEMPAX(CHWDeviceOEMPAX *pHWDeviceOEMPA);
	~CSWDeviceOEMPAX();
	int operator=(const CSWDeviceOEMPAX &a);
	bool operator==(const CSWDeviceOEMPAX &a) const;
	bool operator!=(const CSWDeviceOEMPAX &a) const;

	virtual const wchar_t *GetConnectedName() const;//useful for multiprocess

	virtual bool IsPulserEnabled();

	virtual bool SetAddress(const wchar_t *pValue);
	virtual const wchar_t* GetAddress(int iSubDevId = 0) const;
//ethernet
	virtual bool SetIPAddress(const wchar_t *pValue);
	virtual bool GetIPAddress(wchar_t *pValue,int iSize) const;
	virtual const wchar_t* GetIPAddress() const;

	virtual bool SetPort(unsigned short usValue);
	virtual bool _SetPort(unsigned short usValue);//same than "SetPort", required because of the preprocessor definition in "WinSpool.h": "#define SetPort SetPortW"
	virtual bool GetPort(unsigned short &usValue) const;

private:

public:
//USB3
	virtual bool IsUSB3Connected();
	virtual CUTUsb3Device *GetUSB3Device();

private:

public:
	virtual bool GetSerialNumber(wchar_t *pSN,int iSize) const;

private:

public:
	virtual bool GetSystemType(wchar_t *pType,int iSize) const;

	virtual int GetRXBoardCount() const;
private:

public:
	virtual int GetApertureCountMax() const;//to get the maximum element count of an aperture.
	virtual int GetElementCountMax() const;//to get the maximum element count of the system (in case of mux).
	virtual int GetPACycleCountMax() const;//to get the maximum cycle count for standard phased array.
	virtual int GetFMCCycleCountMax() const;//to get the maximum cycle count for FMC.

	virtual const double dGetClockPeriod() const;//second
	virtual const float fGetClockPeriod() const;//second
	virtual const LONG lGetClockFrequency() const;//Hz

	virtual const float fFocussingDelayStepEmission() const;//second
	virtual const float fFocussingDelayStepReception() const;//second

	virtual WORD GetFirmwareId() const;
	virtual DWORD GetAWGFirmwareId() const;
private:
	virtual int GetApertureCountMax(WORD wSystemType) const;
	virtual int GetElementCountMax(WORD wSystemType) const;

public:

	virtual int GetCycleCountMax() const;
	virtual bool IsFullMatrixCapture() const;//FMC could be enabled or disabled.
	virtual bool IsFullMatrixCaptureReadWrite() const;//FMC bit could be Read/Write or Read only (for old FMC FW: FMC bit is not read only).
	virtual bool GetFMCElement(int &iElementStart,int &iElementStop,int &iElementStep) const;
	virtual bool IsMultiHWChannelSupported() const;
	virtual bool IsTemperatureAlarmSupported() const;
	virtual bool IsMultiHWChannelEnabled() const;
	virtual bool IsMatrixAvailable() const;
	virtual bool IsLabviewAvailable() const;
	virtual bool IsTpacquisitionAvailable() const;
	virtual bool IsWTSWAvailable() const;
	virtual bool IsMatlabAvailable() const;
	virtual bool IsEncoderDecimal() const;
	virtual bool IsFMCElementStepSupported() const;
	virtual bool IsFMCSubTimeSlotPerCycleSupported() const;
	virtual bool IsAWGSupported() const;
private:

public:

	virtual bool SetKeepAlive(enumKeepAlive eKeepAlive);
	virtual enumKeepAlive GetKeepAlive() const;

	virtual bool EnableAscan(bool bEnable);
	virtual bool IsAscanEnabled() const;

	virtual bool SetAscanBitSize(enumBitSize eBitSize);
	virtual enumBitSize GetAscanBitSize() const;

	virtual bool SetAscanRequest(enumAscanRequest eAscanRequest);
	virtual enumAscanRequest GetAscanRequest() const;

	virtual bool SetAscanRequestFrequency(double dFreq);//Hz
	virtual bool GetAscanRequestFrequency(double &dFreq) const;

	virtual bool EnableCscanTof(bool bEnable);
	virtual bool IsCscanTofEnabled() const;

	virtual bool SetTriggerMode(enumOEMPATrigger eTrig);
	virtual bool EnableSubSequenceEncoder(bool bEnable);
	virtual bool IsSubSequenceEncoderEnabled() const;
	virtual bool EnableSubSequenceGate(bool bEnable);
	virtual bool IsSubSequenceGateEnabled() const;

	virtual bool SetTriggerEncoderStep(double dStep);
	virtual bool GetTriggerEncoderStep(double &dStep) const;

	virtual bool SetSignalTriggerHighTime(double dTime);
	virtual double GetSignalTriggerHighTime() const;

	virtual bool SetRequestIO(enumOEMPARequestIO eRequest);
	virtual enumOEMPARequestIO GetRequestIO() const;

	virtual bool SetRequestIODigitalInputMaskRising(int iMask);
	virtual bool GetRequestIODigitalInputMaskRising(int &iMask) const;

	virtual bool SetRequestIODigitalInputMaskFalling(int iEvent);
	virtual bool GetRequestIODigitalInputMaskFalling(int &iEvent) const;

	virtual bool SetExternalTriggerCycle(enumDigitalInput eDigitalInput);
	virtual bool GetExternalTriggerCycle(enumDigitalInput &eDigitalInput) const;

	virtual bool SetExternalTriggerSequence(enumDigitalInput eDigitalInput);
	virtual bool GetExternalTriggerSequence(enumDigitalInput &eDigitalInput) const;

	virtual bool SetMappingOutput(int iOutputIndex,enumOEMPAMappingDigitalOutput eMapping);
	virtual bool GetMappingOutput(int iOutputIndex,enumOEMPAMappingDigitalOutput &eMapping) const;
	virtual bool SetMappingOutput(int iOutputIndex, enumOEMPAMiniMappingDigitalIO eMapping) { return false; }
	virtual bool GetMappingOutput(int iOutputIndex, enumOEMPAMiniMappingDigitalIO &eMapping) const { return false; }

	virtual bool SetRequestCscan(enumOEMPARequestCscan eRequest);
	virtual enumOEMPARequestCscan GetRequestCscan() const;

	virtual bool SetEncoderDebouncer(double dTime);
	virtual double GetEncoderDebouncer() const;

	virtual WORD GetDigitalInput() const;//return the general purpose digital inputs state coming from the HW (binary value).

	virtual bool SetDigitalDebouncer(double dTime);
	virtual double GetDigitalDebouncer() const;

	virtual bool SetMultiSystemDebouncer(double dTime);
	virtual double GetMultiSystemDebouncer() const;

	virtual bool ResetEncoder();

	//following function can be used while pulser are off.
	virtual bool GetTemperatureCount(int &iBoardCount,int &iSensorCountMax) const;//SensorCount is not the same for each board.
	virtual bool GetTemperatureSensorCount(int iBoardIndex,int &iSensorCount) const;//SensorCount is not the same for each board.
	virtual int GetTemperature(int iBoardIndex,int iSensorIndex,float &fValue) const;
	virtual int SetArrayTemperature(int iBoardIndex,int iSensorCount,float *pfValue);
	virtual int GetArrayTemperature(int iBoardIndex,int iSensorCount,float *pfValue) const;
	//following function can be used while pulser are on.
	virtual bool GetTemperatureMax(float &fValue);
private:

public:
	virtual bool IsIOBoardEnabled() const;
	virtual bool IsOEMMCEnabled() const;//value in the flash (different than value in the register).
	virtual BYTE GetFlashUSB3Version() const;
	virtual DWORD GetFWUSB3Version() const;
	virtual bool EnableUSB3(bool bEnable);
	virtual bool IsUSB3Enabled() const;
	virtual DWORD GetMBOptions() const;
	virtual enumOEMPAAnalogBandwidth GetAnalogBandwidth() const;

	virtual bool GetEmbeddedVersion(CSWDeviceOEMPA::structVersion &version) const;
	virtual bool GetOptionsCom(CSWDeviceOEMPA::structOptionsCom &optionsCom) const;
	virtual bool GetOptionsTCP(CSWDeviceOEMPA::structOptionsTCP &optionsTCP) const;
	virtual bool GetOptionsFlash(CSWDeviceOEMPA::structOptionsFlash &optionsFlash) const;
	virtual int GetPasscodeCount() const;
	virtual bool GetPasscode(int iIndex,DWORD &dwPasscode) const;
	virtual double GetMaximumThroughput() const;//Unit is Bytes/second.

	//calibration management
	virtual bool IsSubSequenceAverageSupported() const;
	virtual bool IsTimeOffsetSupported() const;
	//The calibration time offset is internally added to RecoveryTimes.
	virtual bool SetTimeOffset(float fTimeOffset);
	virtual float GetTimeOffset();//current value used to correct time axis.

	virtual void EnableEmissionDeadElement(bool bEnable);
	virtual bool IsEmissionDeadElementEnabled();
	virtual void ResetEmissionDeadElements();
	virtual bool SetEmissionDeadElements(int iElementSize, bool* pbEnable);
	virtual bool SetEmissionDeadElement(int iElementIndex, bool bEnable);
	virtual bool GetEmissionDeadElements(int iElementCountMax, int& iElementCount, int* iElementList);
	virtual void EnableReceptionDeadElement(bool bEnable);
	virtual bool IsReceptionDeadElementEnabled();
	virtual bool IsReceptionDeadElement(int iElementIndex);
	virtual void ResetReceptionDeadElements();
	virtual bool SetReceptionDeadElements(int iElementSize, bool* pbEnable);
	virtual bool SetReceptionDeadElement(int iElementIndex, bool bEnable);
	virtual bool GetReceptionDeadElements(int iElementCountMax, int& iElementCount, int* iElementList);
	virtual void EnableNormalisationEmission(bool bEnable);
	virtual void EnableNormalisationReception(bool bEnable);
	virtual bool IsNormalisationEmissionEnabled();
	virtual bool IsNormalisationReceptionEnabled();
	virtual bool SetNormalisationEmissionDelay(int iElementIndex, float fDelay);
	virtual bool SetNormalisationReceptionDelay(int iElementIndex, float fDelay);
	virtual bool SetNormalisationEmissionDelays(int iElementSize, float* pfDelay);
	virtual bool SetNormalisationReceptionDelays(int iElementSize, float* pfDelay);

	//For OEM-MC or OEM-PA (VF).
	virtual void EnablePulserDuringReplay(bool bEnable);
	virtual bool IsPulserDuringReplayEnabled();
	virtual bool EnableCscanTimeOfFlightCorrection(bool bEnable);
	virtual bool IsCscanTimeOfFlightCorrectionEnabled();
	virtual bool GetCscanTimeOfFlightCorrection(int iCycle,BYTE &byDecimation,float &fAscanStart);//decimation range is 1..16.
	virtual bool SetCscanTimeOfFlightCorrection(int iCycle,BYTE byDecimation,float fAscanStart);//decimation range is 1..16.

	virtual double GetFWAscanRecoveryTime();
	virtual double GetFMCSubCycleRecoveryTime();
	virtual double GetFMCCycleRecoveryTime();

	virtual DWORD GetHWTimeLimitation();
	virtual char cGetHWTimeLimitation();
private:
	virtual double vf_GetFWClockPeriod() const;
private:
public:

public:
	virtual DWORD GetSettingId();
};


class DRIVER_OEMPAX_API_ALIGN _CHWDeviceOEMPAX
{
private:
	ULONGLONG m_ullPrivateMemory[2245];
protected:

};

class CSWDeviceOEMPAX;

//LOW LEVEL CLASS TO ACCESS THE HARDWARE
class DRIVER_OEMPAX_API_ALIGN CHWDeviceOEMPAX :
#ifdef _DRIVER_11XY_
	public CHWDeviceOEM,
#else //_DRIVER_11XY_
	public CHWDeviceOEMPA,
#endif //_DRIVER_11XY_
	public _CHWDeviceOEMPAX
{
public:
#ifdef _DRIVER_11XY_
	virtual CHWDeviceOEMPAX *GetMatchedDeviceOempa();//link to the matched device (an OEMPA 64:64a could be matched with an OEMPA 64:64b to build an OEMPA 128:128).
	virtual CHWDeviceOEMPAX *GetMatched256DeviceOempa(int iModuleIndex);
	bool PerformCalibration(float &fDelayCorrectionMax,float &fTimeOffset);//In case of calibration error you can display the reporting file (see "CSWDeviceOEMPA1::GetCalibrationFileReport").
				//output parameter "fDelayCorrectionMax" maximum correction delay in second
				//output parameter "fTimeOffset" call "SetTimeOffset" with this value to correct it.
	bool UpdateCalibration();//check only with the display.
#endif //_DRIVER_11XY_
public:
	virtual bool ProcessIOAscan(int iDevice,void *pAcquisitionParameter,pTypeAcquisitionAscan_0x00010103 pAcquisitionAscan_0x00010103,LONG &lLastAscanIndex);
	virtual bool ProcessIOCscan(int iDevice,void *pAcquisitionParameter,pTypeAcquisitionCscan_0x00010X02 pAcquisitionCscan_0x00010X02,LONG &lLastCscanIndex);
	virtual bool vf_OnMasterConnected(int iMasterDigitalExternalSequence, int iMasterDigitalExternalCycle, int iSlaveDigitalExternalSequence, int iSlaveDigitalExternalCycle);
	virtual bool vf_OnSlaveConnected(int iMasterDigitalExternalSequence, int iMasterDigitalExternalCycle, int iSlaveDigitalExternalSequence, int iSlaveDigitalExternalCycle);
	virtual bool vf_OnSlaveDisconnected(bool bPostProcess);
	virtual bool vf_SWReset();
	virtual bool vf_GetSockBufferSize(int &iSizeSend, int &iSizeReceive);
	virtual bool vf_CheckSetupTime(structNotificationOption &optionNotification, bool bCheckValue, int iCycle, enumCheckSetupTime eType, void* val, LONG *lPoint);
	virtual double vf_GetMinTimeSlotRecovery(structCheckRecoveryTimePA *pRecoveryTimePA);
	virtual double vf_GetMinTimeSlotRecovery(DWORD channels, enumBitSize eAscanBitSize, enumCompressionType* eCompressionTypes, LONG* pointCounts, LONG* pointFactors, LONG* starts, LONG* ranges, LONG* wedgesE, LONG* wedgesR);
	virtual double vf_GetMaxRangeRecovery(structCheckRecoveryTimePA* pRecoveryTimePA);
	virtual bool vf_ResetSequence();
	virtual bool vf_SetTimeStamp(int iValue);//0=restart,1=reset,2=stop on next standby.
	virtual bool vf_SetTimeStamp(ULONGLONG &ullTimeStamp);
	virtual bool vf_GetTimeStamp(ULONGLONG *pullTimeHW);
	virtual bool vf_CheckGateIndex(int &iGate);

public:
	CHWDeviceOEMPAX();
	CHWDeviceOEMPAX(const wchar_t *pFlashFile);//to emulate a specific HW system.
	virtual ~CHWDeviceOEMPAX();

	CHWDeviceOEMPAX *GetHWDeviceOEMPA();
	CSWDeviceOEMPAX *GetSWDeviceOEMPA();
	const CSWDeviceOEMPAX *cGetSWDeviceOEMPA() const;
	virtual enumHardware vf_GetHardware() const;

	virtual bool GetDigitalInput(DWORD *pdwData);//reading the current state of digital inputs

	//ToDo move this function to CSWDeviceOEMPAX
	bool IsFlashSWSection();//to check that the flash SW section has been read from the hardware without error.

//FW members (those parameters are inside the HW board)
//before using them you need to lock the device : see member functions of "CHWDevice"
//(the communication link with the HW is shared between all threads, only one at a time can lock it)

public:
	virtual bool EnablePulser(bool bShot);
	virtual bool GetEnablePulser(bool *pbShot);//ask hw as for others functions.
	virtual bool EnablePulser(bool bShot,bool bDisableCallback);

public:

//<<PARAMETERS MANAGEMENT FUNCTIONS : BEGIN>>
//All those functions return true in case of no error and false in case of error.

	virtual bool GetFWId(WORD *pwFWId);//to get the device version.
	virtual bool dwGetFWId(DWORD *pdwFWId);//to get the device version.
	virtual bool GetFWOptions(DWORD *pdwFWOptions);
	bool GetOptionsCom(CSWDeviceOEMPA::structOptionsCom *pOptionsCom);
	bool GetOptionsTCP(CSWDeviceOEMPA::structOptionsTCP *pOptionsTCP);
	bool GetOptionsFlash(CSWDeviceOEMPA::structOptionsFlash *pOptionsFlash);
	bool GetEmbeddedVersion(CSWDeviceOEMPA::structVersion *pVersion);
public:
	virtual void ResetFWOptions();
	virtual bool GetFWId();
	virtual bool SetFWOptionsMask(const wchar_t *pPasscode, CUTDevCommunication *pDevCom = NULL);
	virtual int GetFlashSWSectionSize();
	virtual bool GetFlashSWSection(char *pBuffer,int iSize);

public:
	virtual bool DisableUSB3(bool bDisable);
	virtual bool GetUSB3Disabled(bool *pbDisable);

public:
	virtual int swGetApertureCountMax() const;//to get the maximum element count of an aperture (SW function, the HW does not send answer).
	virtual int swGetElementCountMax() const;//to get the maximum element count of the system (SW function, the HW does not send answer).
	virtual int swGetCycleCountMax();

public:
	bool GetApertureCountMax(int *piCount);//to get the maximum element count of an aperture (request to the HW).
	bool GetElementCountMax(int *piCount);//to get the maximum element count of the system (in case of mux, request to the HW).
		//Output parameters
		//	piCount : maximum aperture size.

	virtual bool GetTemperatureSensor(int iIndexBoard,int iIndexSensor,WORD *pwTemperature);//FW parameter
	virtual bool GetTemperatureSensor(int iIndexBoard, int iIndexSensor, short *psTemperature);//signed values, usefull for mini and Com board of PA1.
							//iIndexBoard: 0=ComBoard, 1=first RX board, 2=second RX board, 3=third RX board, 4=four RX board.
	virtual bool GetTemperatureMaxHW(int iSubDevId, short* psTemperature);
	virtual bool SetTemperatureAlarm(BYTE &byWarning,BYTE &byAlarm);
	virtual bool GetTemperatureAlarm(BYTE *pbyWarning,BYTE *pbyAlarm);
public:

public:

public:
	virtual bool SetHardwareLink(enumHardwareLink &eHardwareLink,int iDigitalExternalSequence,int iDigitalExternalCycle);
	virtual bool GetHardwareLink(enumHardwareLink *peHardwareLink,int *piDigitalExternalSequence,int *piDigitalExternalCycle);

public:
	virtual bool EnableFMC(bool bEnable);//return false if the FW does not support the FMC feature (old FMC FW and FW for which FMC is not supported).
	virtual bool GetEnableFMC(bool *pbEnable);//return false if the FW does not support the FMC feature (old FMC FW and FW for which FMC is not supported).
	//you can use the following functions in any case (step equal or different to 1):
	virtual bool SetFMCElement(int &iElementStart,int &iElementStop,int &iElementStep);
	virtual bool GetFMCElement(int *piElementStart,int *piElementStop,int *piElementStep);
	//you can use the following functions only if the step is 1:
	virtual bool SetFMCElementStart(int &iElementIndex);
	virtual bool GetFMCElementStart(int *piElementIndex);
	virtual bool SetFMCElementStop(int &iElementIndex);
	virtual bool GetFMCElementStop(int *piElementIndex);
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

	virtual bool ResetTimeStamp();

	virtual bool ResetEncoder(int iEncoderIndex);//same than "SetEncoder(iEncoderIndex,0)".
	virtual bool SetEncoder(int iEncoderIndex,double &dValue);//unit=meter
	virtual bool SetEncoder(int iEncoderIndex,DWORD &dwValue);//unit=encoder step
	virtual bool GetEncoderPosition(int iEncoderIndex, LONG* plCounts, double* pdPosition);//unit=encoder steps, meter
	virtual bool SetEncoderType(enumEncoderType &eEncoder1Type,enumEncoderType &eEncoder2Type);
	virtual bool GetEncoderType(enumEncoderType *peEncoder1Type,enumEncoderType *peEncoder2Type);
public:

public:

	virtual bool EnableAscan(bool bAscan);//to enable Ascan acquisition that will be sent by the FW to the SW.
	virtual bool GetEnableAscan(bool *pbAscan);
public:

public:

	//Cscan time of flight : you have frist to define gates (see "SetGateXXX").
	virtual bool EnableCscanTof(bool bCscanTof);//to enable Cscan time of flight acquisition that will be sent by the FW to the SW.
	virtual bool GetEnableCscanTof(bool *pbCscanTof);
public:

public:

	virtual bool SetAscanBitSize(enumBitSize eBitSize);//Ascan data size.
	virtual bool GetAscanBitSize(enumBitSize *peBitSize);
	virtual bool CheckAscanBitSize(enumBitSize &eBitSize);
public:

public:

	virtual bool SetAscanRequest(enumAscanRequest eAscanRequest);
	virtual bool GetAscanRequest(enumAscanRequest *peAscanRequest);
public:

public:

	//This function "SetAscanRequestFrequency" can be used when you dont want to receive all Ascan
	//(to decrease the throughput) see also the function "SetAscanRequest".
	//Be careful if you want to set the Pulse Repetition Rate, please refer to function "SetTimeSlot".
	virtual bool SetAscanRequestFrequency(double &dValue);
	virtual bool GetAscanRequestFrequency(double *pdValue);
	virtual bool CheckAscanRequestFrequency(double &dValue);
public:

public:

	virtual bool SetCycleCount(int &lCycleCount);//to write the cycle count.
	virtual bool GetCycleCount(int *plCycleCount);//to read the cycle count.
	virtual bool CheckCycleCount(int &iCycleCount);//to check the cycle count (minimum value, maximum value).
public:
#ifdef _WIN32
#endif // _WIN32

public:

	virtual bool SetTriggerMode(enumOEMPATrigger &eTrig);
	virtual bool GetTriggerMode(enumOEMPATrigger *peTrig);
	//In case of the mode "eEncoder" an additional mode is required:
	virtual bool SetEncoderDirection(enumOEMPAEncoderDirection &eEncoderDirection);
	virtual bool GetEncoderDirection(enumOEMPAEncoderDirection *peEncoderDirection);
	//In case of SW trigger you have also to call the following functions:
	virtual bool SWTrigger_Sequence();
	virtual bool SWTrigger_Cycle(int iCycleCount);
	virtual bool SWTrigger_ResetFWCurrentCycle();
public:

public:

	//It is better to use following function (unit is meter), previously you have to set the resolution ("GetSWEncoder(int iEncoder)->SetResolution()").
	virtual bool SetTriggerEncoderStep(double &dStep);//unit=meter
	virtual bool GetTriggerEncoderStep(double *pdStep);//unit=meter
	//than those functions (if you want to manage by yourself the encoder resolution).
	virtual bool SetTriggerEncoderStep(DWORD &dwStep);//unit=encoder step
	virtual bool GetTriggerEncoderStep(DWORD *pdwStep);//unit=encoder step
	//for some of the FW version a floating point value is available (see function "CSWDeviceOEMPAX::IsEncoderDecimal"):
	virtual bool SetTriggerEncoderStepFloat(structEncoderStepFloat &stStep);
	virtual bool GetTriggerEncoderStepFloat(structEncoderStepFloat *pstStep);//unit=encoder step
public:

public:

	virtual bool SetSignalTriggerHighTime(double &dTime);
	virtual bool GetSignalTriggerHighTime(double *pdTime);
	virtual double GetSignalTriggerHighTimeMin();
public:

public:

	virtual bool SetRequestIO(enumOEMPARequestIO eRequest);
	virtual bool GetRequestIO(enumOEMPARequestIO *peRequest);
public:

public:

	virtual bool SetRequestIODigitalInputMask(int &iMaskFalling,int &iMaskRising);
	virtual bool GetRequestIODigitalInputMask(int *piMaskFalling,int *piMaskRising);
	virtual bool CheckRequestDigitalInputMask(int &iMask);

public:

public:

	virtual bool SetFilter(enumOEMPAFilterIndex eFilterIndex,WORD &wScale,short wValue[g_iOEMPAFilterCoefficientMax]);
	virtual bool GetFilter(enumOEMPAFilterIndex eFilterIndex,WORD *pwScale,short wValue[g_iOEMPAFilterCoefficientMax]);
public:
	virtual bool SetFilterScale(enumOEMPAFilterIndex eFilterIndex,WORD &wScale);
	virtual bool SetFilterCoefficient(enumOEMPAFilterIndex eFilterIndex,int iIndex,short &wValue);
	virtual bool GetFilterScale(enumOEMPAFilterIndex eFilterIndex,WORD *pwScale);
	virtual bool GetFilterCoefficient(enumOEMPAFilterIndex eFilterIndex,int iIndex,short *pwValue);

public:

	virtual bool SetEncoderWire1(int iEncoderIndex,enumDigitalInput eDigitalInput);//int iEncoderIndex : 0 for first encoder, 1 for second encoder.
	virtual bool SetEncoderWire2(int iEncoderIndex,enumDigitalInput eDigitalInput);
	virtual bool SetExternalTriggerCycle(enumDigitalInput eDigitalInput);
	virtual bool SetExternalTriggerSequence(enumDigitalInput eDigitalInput);
	virtual bool GetEncoderWire1(int iEncoderIndex,enumDigitalInput *peDigitalInput);
	virtual bool GetEncoderWire2(int iEncoderIndex,enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTriggerCycle(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTriggerSequence(enumDigitalInput *peDigitalInput);
public:

public:

	virtual bool SetDigitalOutput(int iIndex,enumOEMPAMappingDigitalOutput eMappingDigitalOutput);
	virtual bool GetDigitalOutput(int iIndex,enumOEMPAMappingDigitalOutput *peMappingDigitalOutput);
	virtual bool SetDigitalOutput(int iIndex, enumOEMPAMiniMappingDigitalIO eMappingDigitalOutput) { return false; }
	virtual bool GetDigitalOutput(int iIndex, enumOEMPAMiniMappingDigitalIO *peMappingDigitalOutput) { return false; }
public:

public:

public:
	virtual bool SetRequestCscan(enumOEMPARequestCscan &eRequest);
	virtual bool GetRequestCscan(enumOEMPARequestCscan *peRequest);

public:

	virtual bool SetEncoderDebouncer(double &dValue);
	virtual bool GetEncoderDebouncer(double *pdValue);
	virtual bool CheckEncoderDebouncer(double &dValue);
public:

public:

	virtual bool SetDigitalDebouncer(double &dValue);
	virtual bool GetDigitalDebouncer(double *pdValue);
	virtual bool CheckDigitalDebouncer(double &dValue);
public:

public:

	virtual bool SetMultiSystemDebouncer(double &dValue);
	virtual bool GetMultiSystemDebouncer(double *pdValue);
	virtual bool CheckMultiSystemDebouncer(double &dValue);
public:

public:

	virtual bool SetAnalogBandwidth(enumOEMPAAnalogBandwidth &eAnalogBandwidth);
	virtual bool GetAnalogBandwidth(enumOEMPAAnalogBandwidth *peAnalogBandwidth);
public:

public:

	//static bool WINAPI CheckGain(double &dGain,float &fBeamCorrection,int &iDACCountMax,int &iDACCount,float *pfDACSlope,float *pfDACTime);
	virtual bool SetGainDigital(int iCycle,double &dGain);//to write the amplification.
	virtual bool GetGainDigital(int iCycle,double *pdGain);//to read the amplification.
	virtual bool CheckGainDigital(double &dGain, int iCycle = -1);//to check the amplification value (minimum, maximum, step).
public:
protected:
	virtual bool TranslateGainDigital(structNotificationOption &optionNotification, double &dGain, LONG &lHWDataParameter);//to check the amplification value (minimum, maximum, step).
	virtual void TranslateGainDigital(LONG lHWDataParameter, double &dGain);
public:

public:

	//SubSequence
	bool DisableSubSequenceTable();
	bool SetSubSequenceTableEncoder(int iSubSequenceCycleCount,int *aiCycleStart,int *aiCycleStop,int iSubSequenceStepCount,DWORD *adwStep);
	bool GetSubSequenceTableEncoder(int iSubSequenceCycleMaxCount,int *aiCycleStart,int *aiCycleStop,int *piSubSequenceCycleCount,int iSubSequenceStepMaxCount,DWORD *adwStep,int *piSubSequenceStepCount);
	bool SetSubSequenceTableEncoder(int iSubSequenceCycleCount,int *aiCycleStart,int *aiCycleStop,int iSubSequenceStepCount,float *afStep);
	bool GetSubSequenceTableEncoder(int iSubSequenceCycleMaxCount,int *aiCycleStart,int *aiCycleStop,int *piSubSequenceCycleCount,int iSubSequenceStepMaxCount,float *afStep,int *piSubSequenceStepCount);
	bool SetSubSequenceTableGate(int iSubSequenceCycleCount,int *aiCycleStart,int *aiCycleStop,int iSubSequenceTofCount,float *afTof);
	bool GetSubSequenceTableGate(int iSubSequenceCycleMaxCount,int *aiCycleStart,int *aiCycleStop,int *piSubSequenceCycleCount,int iSubSequenceTofMaxCount,float *afTof,int *piSubSequenceTofCount);
	bool SetSubSequenceAverage(int &iAverage);
	bool GetSubSequenceAverage(int *piAverage);
public:

public:

	virtual bool SetBeamCorrection(int iCycle,float &fGain);
	virtual bool GetBeamCorrection(int iCycle,float *pfGain);
	virtual bool CheckBeamCorrection(float &fGain);
public:

public:

	virtual bool EnableDAC(int iCycle,bool &bEnable);
	virtual bool GetEnableDAC(int iCycle,bool *pbEnable);
	virtual bool CheckDACSlope(double &fTime,float &fSlope);
	virtual bool CheckDACGain(float &fGain);
	virtual bool CheckDACCount(int &iCount);
public:
	virtual bool SetDAC(int iCycle,int &iCount,double *pdTime,float *pfPrm,structCallbackArrayFloatDac *pCallbackArray,int iStringErrorSize,wchar_t *pStringError);//safe : check between the different points of the DAC is peformed.
	virtual bool SetDAC(int iCycle, int &iCount, double *pdTime, float *pfPrm, float fAnalogGain, int iCountVGA, double *pdTimeVGA, float *pfGainVGA, structCallbackArrayFloatDac *pCallbackArray, int iStringErrorSize, wchar_t *pStringError) { return false; };//safe : check between the different points of the DAC is peformed.
	virtual bool GetDAC(bool bSlope,int iCycle,int &iCountMax,int *piCount,double *pdTime,float *pfPrm,structCallbackArrayFloatDac *pCallbackArray);
	virtual bool GetDAC(bool bSlope, int iCycle, int &iCountMax, int *piCount, double *pdTime, float *pfPrm, int *piCountVGA, double *pdTimeVGA, float *pfGainVGA, structCallbackArrayFloatDac *pCallbackArray) { return false; };

public:

	virtual bool SetAscanRectification(int iCycle,enumRectification eRectification);
	virtual bool GetAscanRectification(int iCycle,enumRectification *peRectification);
public:

public:

	virtual bool SetAscanStart(int iCycle,double &dStart);
	virtual bool GetAscanStart(int iCycle,double *pdStart);
	virtual bool CheckAscanStart(double &dStart);
public:

public:

	virtual bool SetAscanRange(int iCycle,double &dRange,/*output only*/enumCompressionType &eCompressionType,/*output only*/LONG &lPointCount,/*output only*/LONG &lPointFactor);//point count is automatically calculated from the digitizing clock.
			//Input is the range, this function determines the point count, the digitizing frequency is the default HW clock (normally 100 MHz).
	virtual bool SetAscanRangeWithFactor(int iCycle,double &dRange,enumCompressionType &eCompressionType,/*in/out*/LONG &lPointFactor,/*output only*/LONG &lPointCount);
			//Inputs are range + factor, this function determines the point count.
			//two compressions are available:
			//	"eCompression": compression with minimum and maximum.
			//	"eDecimation": compression fixed digitizing frequency (no minimum and maximum).
			//DigitizingFrequency = clock x lPointFactor / 256
			//normally clock=100 MHz
			//"lPointFactor" range is 1 to 256.
	virtual bool SetAscanRangeWithCount(int iCycle,double &dRange,/*in/out (check)*/enumCompressionType &eCompressionType,/*in/out (check)*/LONG &lPointCount,/*output only*/LONG &lPointFactor);
	virtual bool GetAscanRange(int iCycle,double *pdRange,enumCompressionType *peCompressionType,LONG *plPointCount,LONG *plPointFactor);
	virtual bool CheckAscanRange(double &dRange);
	virtual bool CheckPointCount(LONG &lPointCount);
	virtual bool CheckPointCount(LONG& lPointCount, enumBitSize eAscanBitSize);
	virtual bool CheckPointFactor(LONG &lPointFactor);
	virtual bool CheckAscanRangeWithCount(double &dRange,enumCompressionType &eCompressionType,LONG &lPointCount);
	virtual bool GetSamplingFrequency(enumCompressionType eCompressionType,LONG lPointFactor,double &dSamplingFrequency/*Hertz*/);
public:
#ifdef _OEMPAX_DECIMATION_TIME_CORRECTION_
#endif //_OEMPAX_DECIMATION_TIME_CORRECTION_

public:

	virtual bool SetFilterIndex(int iCycle,enumOEMPAFilterIndex eFilterIndex);
	virtual bool GetFilterIndex(int iCycle,enumOEMPAFilterIndex *peFilterIndex);
public:

public:

	virtual bool SetTimeSlot(int iCycle,double &dTimeSlot);
	virtual bool GetTimeSlot(int iCycle,double *pdTimeSlot);
	virtual bool CheckTimeSlot(double &dTimeSlot);
	//FMC SubTimeSlot management
	virtual bool SetFMCSubTimeSlotAcqReplay(int iCycle,double dAscanStart,double dAscanRange,double &dTimeSlot);//easy function to use
	virtual bool GetFMCTimeLimitation(double dAscanStart,double dAscanRange,double dTimeSlot,double &dTimeSlotMin,double &dHWAcqSubTimeSlotMin,double &dReplaySubTimeSlotMin,double &dReplaySubTimeSlotOptimizedForThroughput);
	virtual bool GetFMCTimeLimitation(int iFMCSubCycleCount,double dAscanStart,double dAscanRange,double dTimeSlot,double &dTimeSlotMin,double &dHWAcqSubTimeSlotMin,double &dReplaySubTimeSlotMin,double &dReplaySubTimeSlotOptimizedForThroughput);
	virtual int GetFMCSubTimeSlotCount();
	//instead to call "SetFMCSubTimeSlotAcq" and "SetFMCSubTimeSlotReplay" you can call "SetFMCSubTimeSlotAcqReplay" which is easier to use.
	virtual bool SetFMCSubTimeSlotAcq(int iCycle,double &dSubTimeSlot);
	virtual bool SetFMCSubTimeSlotReplay(int iCycle,double &dSubTimeSlot);
	virtual bool GetFMCSubTimeSlotAcq(int iCycle,double *pdSubTimeSlot);
	virtual bool GetFMCSubTimeSlotReplay(int iCycle,double *pdSubTimeSlot);
public:
protected:
	virtual bool TranslateTimeSlot(structNotificationOption &optionNotification, double &dTimeSlot, DWORD &dwHWDataParameter);
	virtual bool TranslateTimeSlot(DWORD &dwHWDataParameter, double &dTimeSlot);
public:

public:

	virtual bool SetAscanAcqIdChannelProbe(int iCycle,WORD &wID);
	virtual bool GetAscanAcqIdChannelProbe(int iCycle,WORD *pwID);
public:

public:

	virtual bool SetAscanAcqIdChannelScan(int iCycle,WORD &wID);
	virtual bool GetAscanAcqIdChannelScan(int iCycle,WORD *pwID);
public:

public:

	virtual bool SetAscanAcqIdChannelCycle(int iCycle,WORD &wID);
	virtual bool GetAscanAcqIdChannelCycle(int iCycle,WORD *pwID);
public:

public:

	virtual bool EnableAscanMaximum(int iCycle,bool bEnable);
	virtual bool GetEnableAscanMaximum(int iCycle,bool *pbEnable);
public:

public:

	virtual bool EnableAscanMinimum(int iCycle,bool bEnable);
	virtual bool GetEnableAscanMinimum(int iCycle,bool *pbEnable);
public:

public:

	virtual bool EnableAscanSaturation(int iCycle,bool bEnable);
	virtual bool GetEnableAscanSaturation(int iCycle,bool *pbEnable);
public:

public:

	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool bEnable,double dThresholdPercent,enumGateModeAmp eGateModeAmp,enumGateModeTof eGateModeTof,enumRectification eGateRectification);
	virtual bool SetGateModeThreshold(int iCycle,int iGate,bool &bEnable,enumGateModeAmp &eGateModeAmp,enumGateModeTof &eGateModeTof,enumRectification &eGateRectification,double &dThresholdPercent);
	virtual bool GetGateModeThreshold(int iCycle,int iGate,bool *pbEnable,enumGateModeAmp *peGateModeAmp,enumGateModeTof *peGateModeTof,enumRectification *peGateRectification,double *pdThresholdPercent);
	virtual bool CheckGateModeThreshold(bool &bEnable,enumGateModeAmp &eGateModeAmp,enumGateModeTof &eGateModeTof,enumRectification &eGateRectification,double &dThresholdPercent);
public:

public:

	virtual bool SetGateStart(int iCycle,int iGate,double &dStart);
	virtual bool GetGateStart(int iCycle,int iGate,double *pdStart);
	virtual bool CheckGateStart(double &dStart);
public:

public:

	virtual bool CheckGateStartStop(double &dStart,double &dStop);
	virtual bool SetGateStop(int iCycle,int iGate,double &dStop);
	virtual bool GetGateStop(int iCycle,int iGate,double *pdStop,bool *pbWidth = NULL);
	virtual bool CheckGateStop(double &dStop);
public:

public:

	virtual bool SetGateAcqIDAmp(int iCycle,int iGate,WORD &wID);
	virtual bool GetGateAcqIDAmp(int iCycle,int iGate,WORD *pwID);
	virtual bool SetGateAcqIDTof(int iCycle,int iGate,WORD &wID);
	virtual bool GetGateAcqIDTof(int iCycle,int iGate,WORD *pwID);
public:

public:

	virtual bool SetTrackingGateStart(int iCycle,int iGate,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex);
	virtual bool GetTrackingGateStart(int iCycle,int iGate,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex);
	virtual bool SetSWTrackingGateStartFromHW(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex) { return false; }
	virtual bool GetSWTrackingGateStartFromHW(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex) { return false; }
	virtual bool SetTrackingGateStop(int iCycle,int iGate,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex);
	virtual bool GetTrackingGateStop(int iCycle,int iGate,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex);
	virtual bool SetSWTrackingGateStopFromHW(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex) { return false; }
	virtual bool GetSWTrackingGateStopFromHW(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex) { return false; }
	virtual bool SetTrackingAscan(int iCycle,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex);
	virtual bool GetTrackingAscan(int iCycle,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex);
	virtual bool SetTrackingDac(int iCycle,bool &bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex);
	virtual bool GetTrackingDac(int iCycle,bool *pbEnable,int *piTrackingCycleIndex,int *piTrackingGateIndex);
	virtual bool CheckTracking(bool bEnable,int &iTrackingCycleIndex,int &iTrackingGateIndex);
	virtual bool ResetTrackingTable();//this is called automatically when the IF tracking of one gate is updated.
public:

public:

	virtual bool SetGainAnalog(int iCycle,float &fGain);
	virtual bool GetGainAnalog(int iCycle,float *pfGain);
	virtual bool CheckGainAnalog(float &fGain);
public:

public:

public:

public:

	//For some of the following functions the CycleCount is required
	//(it should be the total cycle count of the sequence).
	virtual bool SetEmissionWedgeDelay(int iCycle,int iCycleCount,double &dWedgeDelay);//"iCycleCount"=cycle count.
	virtual bool GetEmissionWedgeDelay(int iCycle,int iCountMax,double *pdWedgeDelay);
	virtual bool SetReceptionWedgeDelay(int iCycle,int iCycleCount,double &dWedgeDelay);
	virtual bool GetReceptionWedgeDelay(int iCycle,int iCountMax,double *pdWedgeDelay);
	virtual bool CheckWedgeDelay(double &dWedgeDelay);
public:

public:

	static bool SetAllElementEnable(bool bEnable,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	static bool SetElementEnable(int iElement,bool bEnable,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	static bool GetElementEnable(int iElement,const DWORD adwHWAperture[g_iOEMPAApertureDWordCount],bool &bEnable);

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
	//Case of a system (16:16, 32:32, 64:64 etc...) without a multiplexer, then please use the NEW STYLE FUNCTIONS.

	//for compatibility with the 1.1.5.4 version
	virtual bool SetEmissionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetEmissionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool SetReceptionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetReceptionEnable(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
public:

public:

	//for compatibility with the 1.1.5.4 version
	virtual bool SetEmissionDelays(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfDelay);
	virtual bool SetEmissionDelays(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	virtual bool SetEmissionWidth(int iCycle,int iElementIndex,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float &fWidth);
	virtual bool SetEmissionWidths(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfWidth);
	virtual bool SetEmissionWidths(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool SetReceptionGain(int iCycle,int iElementIndex,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float &fGain);
	virtual bool SetReceptionGains(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfGain);
	virtual bool SetReceptionGains(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool SetReceptionDelays(int iCycle,int iLineSize,int &iFocalCount,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfDelay);
	virtual bool SetReceptionDelays(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.
	virtual bool GetReceptionNormalisationDelayAv(bool bEmission,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float &fDelay);
	virtual bool SetReceptionDelays(int iCycle,int iLineSize,int &iFocalCount,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float *pfDelay,float *pfDelayOffset);
	virtual bool SetReceptionDelays(int iCycle,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],structCallbackArrayFloat2D &callbackArrayFloat2D,float *pfDelayOffset);//Size1 = element size, Size2 = DDF size.

//NEW STYLE FUNCTIONS (no limitation for the aperture).
	virtual bool SetEmissionEnable(int iCycle,int iElementCount,int *piElementList);
	virtual bool GetEmissionEnable(int iCycle,int iElementCountMax,int *piElementCount,int *piElementList);
	virtual bool SetReceptionEnable(int iCycle,int iElementCount,int *piElementList);
	virtual bool GetReceptionEnable(int iCycle,int iElementCountMax,int *piElementCount,int *piElementList);

	virtual bool SetEmissionDelays(int iCycle,int iElementCount,int *piElementList,float *pfDelay);
	virtual bool GetEmissionDelays(int iCycle,int &iElementCountMax,int *piElementCount,float *pfDelay);
	virtual bool SetEmissionDelays(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	virtual bool GetEmissionDelays(int iCycle,int &iElementCountMax,structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	//virtual bool SetEmissionWidth(int iCycle,int iElementIndex,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float &fWidth)=0;
	virtual bool SetEmissionWidths(int iCycle,int iElementCount,int *piElementList,float *pfWidth);
	virtual bool GetEmissionWidths(int iCycle,int &iElementCountMax,int *piElementCount,float *pfWidth);
	virtual bool SetEmissionWidths(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool GetEmissionWidths(int iCycle,int &iElementCountMax,structCallbackArrayFloat1D &callbackArrayFloat1D);
	//virtual bool SetReceptionGain(int iCycle,int iElementIndex,DWORD adwHWAperture[g_iOEMPAApertureDWordCount],float &fGain)=0;
	virtual bool SetReceptionGains(int iCycle,int iElementCount,int *piElementList,float *pfGain);
	virtual bool GetReceptionGains(int iCycle,int &iElementCountMax,int *piElementCount,float *pfGain);
	virtual bool SetReceptionGains(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool GetReceptionGains(int iCycle,int &iElementCountMax,structCallbackArrayFloat1D &callbackArrayFloat1D);
	virtual bool SetReceptionDelays(int iCycle,int &iFocalCount,int iElementCount,int *piElementList,float *pfDelay);
	virtual bool GetReceptionDelays(int iCycle,int iLineSize,int &iElementCountMax,int &iFocalCountMax,int *piElementCount,int *piFocalCount,float *pfDelay);
	virtual bool SetReceptionDelays(int iCycle,int iElementCount,int *piElementList,structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.
	virtual bool GetReceptionDelays(int iCycle,int &iElementCountMax,int &iFocalCountMax,structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.

	virtual bool SetReceptionFocusing(int iCycle,int &iFocalCount,double *pdFocalTof);
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,int *piFocalCount,double *pdFocalTof);
	virtual bool SetReceptionFocusing(int iCycle,structCallbackArrayDouble1D &callbackArrayDouble1D);
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,structCallbackArrayDouble1D &callbackArrayDouble1D);
	virtual bool SetReceptionFocusing(int iCycle,int &iFocalCount,double *pdFocalTof,float &fCenterDelayE,float &fCenterDelayR);
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,int *piFocalCount,double *pdFocalTof,float *pfCenterDelayE,float *pfCenterDelayR);
	virtual bool SetReceptionFocusing(int iCycle,structCallbackArrayDouble1D &callbackArrayDouble1D,float &fCenterDelayE,float &fCenterDelayR);
	virtual bool GetReceptionFocusing(int iCycle,int &iFocalCountMax,structCallbackArrayDouble1D &callbackArrayDouble1D,float *pfCenterDelayE,float *pfCenterDelayR);
	virtual bool GetReceptionNormalisationDelayAv(bool bEmission,int iElementCount,int *piElementList,float &fDelay);
	virtual bool EnableDDF(int iCycle,bool bEnable);
	virtual bool GetEnableDDF(int iCycle,bool *pbEnable);
	virtual bool EnableDDF(int iCycle,enumFocusing &eFocusing);
	virtual bool GetEnableDDF(int iCycle,enumFocusing *peFocusing);

	virtual bool CheckFocalTimeOfFlight(double &dDelay);
	virtual bool CheckEmissionWidth(float &fWidth);
	virtual bool CheckReceptionGain(float &fGain);
	virtual bool CheckEmissionDelay(float &fDelay);
	virtual bool CheckReceptionDelay(float &fDelay);
	virtual DWORD GetSWBaseAddress();
public:
#ifdef _OEMPAX_DECIMATION_TIME_CORRECTION_
#endif //_OEMPAX_DECIMATION_TIME_CORRECTION_

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

	virtual bool SetSettingId(DWORD dwSettingId);
	virtual bool GetSettingId(DWORD *pdwSettingId);//ask hw as for others functions.
	DWORD swGetSettingId();//ask sw (boolean memory image resident in computer) instead of hw.
public:

public:

	//in case of Ethernet, KeepAlive is useful to prevent communication deadlock
	//but if the developper stay a LONG time inside a breakpoint it will break the socket.
	virtual bool SetKeepAlive(enumKeepAlive eKeepAlive);
	virtual bool GetKeepAlive(enumKeepAlive *peKeepAlive);//ask hw as for others functions.
public:

public:

	//calibration management
	virtual bool SetTimeOffset(float &fTime);
	virtual bool GetTimeOffset(float *pfTime);
public:

public:

	virtual bool TestFWMemoryCycle(int iCycleCount,DWORD dwData);
	virtual bool TestFWMemoryFilter(int iFilterCount,DWORD dwData);
//<<PARAMETERS MANAGEMENT FUNCTIONS : END>>

public://don't use following functions
	virtual bool vf_GetStringId(wchar_t *stringId,int iSize);
	virtual bool vf_UpdateEncoder(int iEncoder);//1.1.5.4w
	virtual bool vf_UpdateFilter(int iFilter);//1.1.5.4w
	virtual bool vf_FreeDigitalInput(enumFeatureDigitalInput eIndexDigitalInputNew);//1.1.5.4w
	virtual bool vf_SetCommunication(enumCommunication eCommunication);
	virtual bool vf_LoadCfgFile();
	virtual bool vf_ReLoadCfgFile();
	virtual bool vf_SetStandby(bool bLockOrUnlock, enumAcquisitionState &eAcqState);
	bool ReadStatusRegister();

	ULONGLONG GetAcqSizeAscan();
	ULONGLONG GetAcqSizeCscan();
	ULONGLONG GetAcqSizeIO();
	void ResetAcqSize();
public:
public:
private:

public:
public:

private:
public:

private:
};
