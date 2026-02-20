
#pragma once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DRIVER_OEMMC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DRIVER_OEMMC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DRIVER_OEMMC_EXPORTS
#ifdef _WIN32
#define DRIVER_OEMMC_API __declspec(dllexport)
#define DRIVER_OEMMC_API_ALIGN __declspec(dllexport) __declspec(align(8))
#elif defined __linux__
#define DRIVER_OEMMC_API __attribute__((visibility ("default")))
#define DRIVER_OEMMC_API_ALIGN __attribute__((visibility ("default"))) __attribute__((aligned(8)))
#endif // __linux__
#else
#ifdef _WIN32

#define DRIVER_OEMMC_API __declspec(dllimport)
#define DRIVER_OEMMC_API_ALIGN __declspec(dllimport) __declspec(align(8))
#elif defined __linux__
#define DRIVER_OEMMC_API 
#define DRIVER_OEMMC_API_ALIGN __attribute__((aligned(8)))
#endif // __linux__
#ifndef _NO_AUTO_INCLUDE_
#pragma comment(lib,"UTDriverOEMMC.lib")
#endif //_NO_AUTO_INCLUDE_
#endif

#ifndef _DRIVER_OEMMC_
#define _DRIVER_OEMMC_
#endif
#define DRIVER_OEMMCuF

#include "AcquisitionFifo.h"
#include "UTDriverCommon.h"

const int g_iOEMMCTemperatureSensorCountMax = 4;
const int g_iOEMMCHumiditySensorCountMax = 4;


class CSWDevice;
class CNode;
class CUTDevCommunication;



class CHWDeviceOEMMC;

typedef bool (WINAPI *pOEMMC_ReadFileWriteHW)(CHWDeviceOEMMC *pOEMPA, const wchar_t *pFileName, enumAcquisitionState eAcqState);
typedef bool (WINAPI *pOEMMC_ReadFileWriteHWs)(int iCount, CHWDeviceOEMMC **apHWDeviceOEMPA, const wchar_t *pFileName, enumAcquisitionState eAcqState);
typedef bool (WINAPI *pOEMMC_ReadFileWriteHW256)(CHWDeviceOEMMC *pMaster, CHWDeviceOEMMC *pSlave, wchar_t *pFileNameMaster, wchar_t *pFileNameSlave);
typedef bool (WINAPI* pOEMMC_ReadHWWriteFile2)(CHWDeviceOEMMC* pOEMPA, const wchar_t* pFileName, enumAcquisitionState eAcqState);
typedef bool (WINAPI *pOEMMC_CreateDefaultSetupFile)(CHWDeviceOEMMC *pHWDeviceOEMPA, enumSetupFileType eFileType, wchar_t *wcLoadDefaultSetup);
typedef bool (WINAPI *pOEMMC_LoadCalibrationSetup)(CHWDeviceOEMMC *pHWDeviceOEMPA, bool bCheck,
	float fWidth, float fStart, float fRange, float fGainAnalog, double dGainDigital,
	const wchar_t *wcCalibrationFileInput, const wchar_t *wcCalibrationFileOutput,
	double dFMCTimeSlotFactor, int &iCalibrationPointCount, double &dAcquisitionTime);

DRIVER_OEMMC_API void WINAPI OEMMC_SetReadFileWriteHW(pOEMMC_ReadFileWriteHW pFunc);
DRIVER_OEMMC_API void WINAPI OEMMC_SetReadFileWriteHW256(pOEMMC_ReadFileWriteHW256 pFunc);
DRIVER_OEMMC_API void WINAPI OEMMC_SetReadHWWriteFile2(pOEMMC_ReadHWWriteFile2 pFunc);
DRIVER_OEMMC_API void WINAPI OEMMC_SetCreateDefaultSetupFile(pOEMMC_CreateDefaultSetupFile pFunc);
DRIVER_OEMMC_API void WINAPI OEMMC_SetLoadCalibrationSetup(pOEMMC_LoadCalibrationSetup pFunc);
DRIVER_OEMMC_API void WINAPI OEMMC_SetLoadCalibrationSetup256(pOEMMC_LoadCalibrationSetup pFunc);




class DRIVER_OEMMC_API_ALIGN _CSWDeviceOEMMC

{
private:
	ULONGLONG m_ullPrivateMemory[7518];
protected:

};

class DRIVER_OEMMC_API_ALIGN CSWDeviceOEMMC :
	public _CSWDeviceOEMMC,
	public CSWDeviceOEMPA
{
public:
	CSWDeviceOEMMC(CHWDeviceOEMMC *pHWDeviceOEMPA, enumCommunication eCommunication);
	/*CSWDeviceOEMMC(CHWDeviceOEMMC *pHWDeviceOEMPA, enumCommunication eCommunication, enumMCType mcType);
	CSWDeviceOEMMC(CHWDeviceOEMMC *pHWDeviceOEMPA, enumCommunication eCommunication, bool IsMC2);*/
	~CSWDeviceOEMMC();
	int operator=(const CSWDeviceOEMMC &a);
	bool operator==(const CSWDeviceOEMMC &a) const;
	bool operator!=(const CSWDeviceOEMMC &a) const;

	virtual const wchar_t *GetConnectedName() const;//useful for multiprocess

	virtual bool IsPulserEnabled();

	virtual bool SetAddress(const wchar_t *pValue);
	virtual const wchar_t* GetAddress(int iSubDevId = 0) const;
	//ethernet
	virtual bool SetIPAddress(const wchar_t *pValue);
	virtual bool GetIPAddress(wchar_t *pValue, int iSize) const;
	virtual const wchar_t* GetIPAddress() const;

	virtual bool SetPort(unsigned short usValue);
	virtual bool _SetPort(unsigned short usValue);//same than "SetPort", required because of the preprocessor definition in "WinSpool.h": "#define SetPort SetPortW"
	virtual bool GetPort(unsigned short &usValue) const;

protected:

public:
//USB3
	virtual bool IsUSB3Connected();
	virtual CUTUsb3Device *GetUSB3Device();

protected:

public:
	virtual bool GetSerialNumber(wchar_t *pSN, int iSize) const;

protected:

public:
	virtual bool GetSystemType(wchar_t *pType, int iSize) const;
	virtual int GetRXBoardCount() const;
	virtual enumMCType GetMCType() const;
	/*
	* Returns the max high voltage value for this device.
	* -1 (0xffffffff) means that the high voltage control is disabled.
	*/
	virtual DWORD GetHighVoltageMax() const;
protected:

public:
	virtual int GetMultipleDeviceCountMax() const;
	virtual int GetApertureCountMax() const;//to get the maximum element count of an aperture.
	virtual int GetElementCountMax() const;//to get the maximum element count of the system (in case of mux).
	virtual int GetPACycleCountMax() const;//to get the maximum cycle count for standard phased array.
	virtual int GetFMCCycleCountMax() const;//to get the maximum cycle count for FMC.
	int GetApertureCountMax(WORD wSystemType) const;
	int GetElementCountMax(WORD wSystemType) const;

	virtual const double dGetClockPeriod() const;//second
	virtual const float fGetClockPeriod() const;//second
	virtual const LONG lGetClockFrequency() const;//Hz

	virtual const float fFocussingDelayStepEmission() const;//second
	virtual const float fFocussingDelayStepReception() const;//second

	virtual WORD GetFirmwareId() const;
	virtual DWORD GetAWGFirmwareId() const;
protected:

public:

	virtual int GetCycleCountMax() const;
	virtual bool IsFullMatrixCapture() const;//FMC could be enabled or disabled.
	virtual bool IsFullMatrixCaptureReadWrite() const;//FMC bit could be Read/Write or Read only (for old FMC FW: FMC bit is not read only).
	virtual bool GetFMCElement(int &iElementStart, int &iElementStop, int &iElementStep) const;
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
	virtual bool IsNegativeSquarePulseAvailable() const;
protected:
#ifdef FMC_PASSCODE_MINI
#endif // FMC_PASSCODE_MINI

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

protected:

public:
	bool SetDACCountMax(int iDACCountMax);
	int GetDACCountMax();
	bool SetDDFCountMax(int iDDFCountMax);
	int GetDDFCountMax();

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

	virtual bool SetExternalResetEncoder1(enumDigitalInput eDigitalInput);
	virtual bool GetExternalResetEncoder1(enumDigitalInput &eDigitalInput) const;
	virtual bool SetExternalResetEncoder2(enumDigitalInput eDigitalInput);
	virtual bool GetExternalResetEncoder2(enumDigitalInput &eDigitalInput) const;

	virtual bool SetExternalTimestampReset(enumDigitalInput eDigitalInput);
	virtual bool GetExternalTimestampReset(enumDigitalInput &eDigitalInput) const;

	virtual bool SetExternalEncoderReset(enumDigitalInput eDigitalInput);
	virtual bool GetExternalEncoderReset(enumDigitalInput &eDigitalInput);

	virtual bool SetExternalTrackingReset(enumDigitalInput eDigitalInput);
	virtual bool GetExternalTrackingReset(enumDigitalInput &eDigitalInput);

	virtual bool SetMappingOutput(int iOutputIndex, enumOEMPAMiniMappingDigitalIO eMapping);
	virtual bool GetMappingOutput(int iOutputIndex, enumOEMPAMiniMappingDigitalIO &eMapping) const;
	// Don't use the two functions below.
	virtual bool SetMappingOutput(int iOutputIndex, enumOEMPAMappingDigitalOutput eMapping);
	virtual bool GetMappingOutput(int iOutputIndex, enumOEMPAMappingDigitalOutput &eMapping) const;

	virtual bool ResetDigitalInput(enumDigitalInput eDigitalInput);

	virtual bool SetRequestCscan(enumOEMPARequestCscan eRequest);
	virtual enumOEMPARequestCscan GetRequestCscan() const;

	virtual bool SetEncoderDebouncer(double dTime);
	virtual double GetEncoderDebouncer() const;

	virtual WORD GetDigitalInput() const;//return the general purpose digital inputs state coming from the HW (binary value).
	virtual DWORD GetDigitalInput32() const;//return the general purpose digital inputs state coming from the HW (binary value). Works for both PIO and MIO. Only for MC2 and MCuF.

	virtual bool SetDigitalDebouncer(double dTime);
	virtual double GetDigitalDebouncer() const;

	virtual bool SetMultiSystemDebouncer(double dTime);
	virtual double GetMultiSystemDebouncer() const;

	virtual bool ResetEncoder();

	//following function can be used while pulser are off.
	virtual bool GetTemperatureCount(int &iBoardCount, int &iSensorCountMax) const;//SensorCount is not the same for each board.
	virtual bool GetHumidityCount(int &iBoardCount, int &iSensorCountMax) const;//SensorCount is not the same for each board.
	virtual bool GetTemperatureSensorCount(int iBoardIndex, int &iSensorCount) const;//SensorCount is not the same for each board.
	virtual bool GetHumiditySensorCount(int iBoardIndex, int &iSensorCount) const;//SensorCount is not the same for each board.
	virtual int GetTemperature(int iBoardIndex, int iSensorIndex, float &fValue) const;
	virtual int SetArrayTemperature(int iBoardIndex, int iSensorCount, float *pfValue);
	virtual int GetArrayTemperature(int iBoardIndex, int iSensorCount, float *pfValue) const;
	//following function can be used while pulser are on.
	virtual bool GetTemperatureMax(float &fValue);
protected:

public:
	virtual bool IsIOBoardEnabled() const;
	virtual bool IsOEMMCEnabled() const;//value in the flash (different than value in the register).
	virtual BYTE GetFlashUSB3Version() const;
	virtual DWORD GetFWUSB3Version() const;
	virtual bool EnableUSB3(bool bEnable);
	virtual bool IsUSB3Enabled() const;
	virtual DWORD GetMBOptions() const;
	virtual enumOEMPAAnalogBandwidth GetAnalogBandwidth() const;
	virtual bool IsPIOBoard() const;
	virtual int GetIOCountMax() const;

	virtual bool GetEmbeddedVersion(CSWDeviceOEMPA::structVersion &version) const;
	virtual bool GetOptionsCom(CSWDeviceOEMPA::structOptionsCom &optionsCom) const;
	virtual bool GetOptionsTCP(CSWDeviceOEMPA::structOptionsTCP &optionsTCP) const;
	virtual bool GetOptionsFlash(CSWDeviceOEMPA::structOptionsFlash &optionsFlash) const;
	virtual int GetPasscodeCount() const;
	virtual bool GetPasscode(int iIndex, DWORD &dwPasscode) const;
	virtual double GetMaximumThroughput() const;//Unit is Bytes/second.
	bool IsPowerDownEnabled() const;

	virtual bool IsCycleOrderSupported() const;
	virtual bool IsAWGPulseEnabled() const;
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
	virtual bool GetCscanTimeOfFlightCorrection(int iCycle, BYTE &byDecimation, float &fAscanStart);//decimation range is 1..16.
	virtual bool SetCscanTimeOfFlightCorrection(int iCycle, BYTE byDecimation, float fAscanStart);//decimation range is 1..16.

	virtual double GetFWAscanRecoveryTime();
	virtual double GetFMCSubCycleRecoveryTime();
	virtual double GetFMCCycleRecoveryTime();

	virtual DWORD GetHWTimeLimitation();
	virtual char cGetHWTimeLimitation();

protected:
	virtual double vf_GetFWClockPeriod() const;
	virtual bool vf_DumpPerformance();
private:
public:

public:
	virtual DWORD GetFWOption() const;
	virtual DWORD GetSettingId();
	virtual bool GetErrorCountString(wchar_t *wcString, int iSize) const;
	virtual bool vf_GetTransitSharedMemory(int64_t &i64BufferSize);
};


class DRIVER_OEMMC_API_ALIGN _CHWDeviceOEMMC

{
private:
	ULONGLONG m_ullPrivateMemory[8916];
protected:

};

class CSWDeviceOEMMC;

//LOW LEVEL CLASS TO ACCESS THE HARDWARE
class DRIVER_OEMMC_API_ALIGN CHWDeviceOEMMC :
	public CHWDeviceOEMPA,
	public _CHWDeviceOEMMC
{
public:
	CHWDeviceOEMMC();	// Default constructor, will only work for MC2 atm.
	CHWDeviceOEMMC(bool isMC2);	// MC2 and MCµ have different comm for the moment, it is required to input the hardware at device creation.
	CHWDeviceOEMMC(enumHardware eHW);
	CHWDeviceOEMMC(const wchar_t *pFlashFile);//to emulate a specific HW system.
	virtual ~CHWDeviceOEMMC();

	CHWDeviceOEMMC *GetHWDeviceOEMPA();
	CSWDeviceOEMMC *GetSWDeviceOEMPA();
	const CSWDeviceOEMMC *cGetSWDeviceOEMPA() const;
	virtual enumHardware vf_GetHardware() const;

	virtual bool GetDigitalInput(DWORD *pdwData);//reading the current state of digital inputs
	bool GetDigitalInput_32(DWORD *pdwData);//reading the current state of digital inputs

	bool IsFlashSWSection();//to check that the flash SW section has been read from the hardware without error.

	// User persistent data. Returns false if non applicable to current device.
	// Store 'size' bytes of custom data in flash memory. Maximum 64kB.
	// Warning: the flash memory will be erased before any write operation. It is the user's responsibility to read and back up the data before writing.
	virtual bool SetUserData(const unsigned char* buffer, size_t size);
	// Get custom data from flash memory. 'size' bytes will be read from memory and stored into 'buffer'. 
	// If fewer data was previously written the excendent is filled with 0xFF.
	virtual bool GetUserData(unsigned char* buffer, size_t size);

//FW members (those parameters are inside the HW board)
//before using them you need to lock the device : see member functions of "CHWDevice"
//(the communication link with the HW is shared between all threads, only one at a time can lock it)

protected:

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
	virtual bool IsMiniV2();	//SW //ToDo: check if this has to be moved in CSWDeviceOEMMC
	bool IsDacVgaEnabled();	//SW
protected:

public:
	virtual bool DisableUSB3(bool bDisable);
	virtual bool GetUSB3Disabled(bool *pbDisable);

protected:

public:
	bool GetApertureCountMax(int *piCount);//to get the maximum element count of an aperture (request to the HW).
	bool GetElementCountMax(int *piCount);//to get the maximum element count of the system (in case of mux, request to the HW).
		//Output parameters
		//	piCount : maximum aperture size.

	virtual bool GetTemperatureSensor(int iIndexBoard, int iIndexSensor, WORD *pwTemperature);//FW parameter
	virtual bool GetTemperatureSensor(int iIndexBoard, int iIndexSensor, short *psTemperature);//signed value, you should use this one for mini.
							//iIndexBoard: 0=ComBoard, 1=first RX board, 2=second RX board, 3=third RX board, 4=four RX board.
	virtual bool GetHumiditySensor(int iIndexBoard, int iIndexSensor, WORD *pwTemperature);
	virtual bool GetTemperatureMaxHW(int iSubDevId, short* psTemperature);
	virtual bool SetTemperatureAlarm(BYTE &byWarning, BYTE &byAlarm);
	virtual bool GetTemperatureAlarm(BYTE *pbyWarning, BYTE *pbyAlarm);
protected:

public:
	//[[deprecated]]
	virtual bool EnableFMC(bool bEnable);//return false if the FW does not support the FMC feature (old FMC FW and FW for which FMC is not supported).
	virtual bool GetEnableFMC(bool *pbEnable);//return false if the FW does not support the FMC feature (old FMC FW and FW for which FMC is not supported).
	//[[deprecated]]
	virtual bool SetFMCElement(int &iElementStart, int &iElementStop, int &iElementStep);
	//[[deprecated]]
	virtual bool GetFMCElement(int *piElementStart, int *piElementStop, int *piElementStep);
	//[[deprecated]]
	virtual bool SetFMCElementStart(int &iElementIndex);
	//[[deprecated]]
	virtual bool GetFMCElementStart(int *piElementIndex);
	//[[deprecated]]
	virtual bool SetFMCElementStop(int &iElementIndex);
	//[[deprecated]]
	virtual bool GetFMCElementStop(int *piElementIndex);
	//[[deprecated]]
	virtual bool SetReceptionGainsFMC256(int iCycle, DWORD adwHWAperture[2 * g_iOEMPAApertureDWordCount], float *pfGain);
protected:

public:
	virtual bool ResetTimeStamp();

	virtual bool ResetEncoder(int iEncoderIndex);//same than "SetEncoder(iEncoderIndex,0)".
	virtual bool SetEncoder(int iEncoderIndex, double &dValue);//unit=meter
	virtual bool SetEncoder(int iEncoderIndex, DWORD &dwValue);//unit=encoder step
	virtual bool GetEncoderPosition(int iEncoderIndex, LONG* plCounts, double* pdPosition);//unit=encoder steps, meter
	virtual bool SetEncoderType(enumEncoderType &eEncoder1Type, enumEncoderType &eEncoder2Type);
	virtual bool GetEncoderType(enumEncoderType *peEncoder1Type, enumEncoderType *peEncoder2Type);
protected:

public:

	virtual bool EnableAscan(bool bAscan);//to enable Ascan acquisition that will be sent by the FW to the SW.
	virtual bool GetEnableAscan(bool *pbAscan);
protected:

public:

		//Cscan time of flight : you have frist to define gates (see "SetGateXXX").
	virtual bool EnableCscanTof(bool bCscanTof);//to enable Cscan time of flight acquisition that will be sent by the FW to the SW.
	virtual bool GetEnableCscanTof(bool *pbCscanTof);
protected:

public:

	virtual bool SetAscanBitSize(enumBitSize eBitSize);//Ascan data size.
	virtual bool GetAscanBitSize(enumBitSize *peBitSize);
	virtual bool CheckAscanBitSize(enumBitSize &eBitSize);
protected:

public:

	virtual bool SetAscanRequest(enumAscanRequest eAscanRequest);
	virtual bool GetAscanRequest(enumAscanRequest *peAscanRequest);
protected:

public:

		//This function "SetAscanRequestFrequency" can be used when you dont want to receive all Ascan
		//(to decrease the throughput) see also the function "SetAscanRequest".
		//Be careful if you want to set the Pulse Repetition Rate, please refer to function "SetTimeSlot".
	virtual bool SetAscanRequestFrequency(double &dValue);
	virtual bool GetAscanRequestFrequency(double *pdValue);
	virtual bool CheckAscanRequestFrequency(double &dValue);
protected:

public:

	virtual bool SetCycleCount(int &lCycleCount);//to write the cycle count.
	virtual bool GetCycleCount(int *plCycleCount);//to read the cycle count.
	virtual bool CheckCycleCount(int &iCycleIndex);//to check the cycle count (minimum value, maximum value).
	bool CheckOEMMCChannel(int channel);
	bool SetDACCountMax(LONG &lDACCountMax);
	bool GetDACCountMax(LONG *plDACCountMax);
	bool SetDDFCountMax(LONG &lDDFCountMax);
	bool GetDDFCountMax(LONG *plDDFCountMax);
#ifdef _WIN32
	bool SetDACCountMax(int &iDACCountMax);
	bool GetDACCountMax(int *piDACCountMax);
	bool SetDDFCountMax(int &iDDFCountMax);
	bool GetDDFCountMax(int *piDDFCountMax);
#endif // _WIN32  
protected:
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
protected:

public:

		//It is better to use following function (unit is meter), previously you have to set the resolution ("GetSWEncoder(int iEncoder)->SetResolution()").
	virtual bool SetTriggerEncoderStep(double &dStep);//unit=meter
	virtual bool GetTriggerEncoderStep(double *pdStep);//unit=meter
	//than those functions (if you want to manage by yourself the encoder resolution).
	virtual bool SetTriggerEncoderStep(DWORD &dwStep);//unit=encoder step
	virtual bool GetTriggerEncoderStep(DWORD *pdwStep);//unit=encoder step
	//for some of the FW version a floating point value is available (see function "CSWDeviceOEMMC::IsEncoderDecimal"):
	virtual bool SetTriggerEncoderStepFloat(structEncoderStepFloat &stStep);
	virtual bool GetTriggerEncoderStepFloat(structEncoderStepFloat *pstStep);//unit=encoder step
protected:

public:

	virtual bool SetSignalTriggerHighTime(double &dTime);
	virtual bool GetSignalTriggerHighTime(double *pdTime);
	virtual double GetSignalTriggerHighTimeMin();
protected:

public:

	virtual bool SetRequestIO(enumOEMPARequestIO eRequest);
	virtual bool GetRequestIO(enumOEMPARequestIO *peRequest);
protected:

public:

	virtual bool SetRequestIODigitalInputMask(int &iMaskFalling, int &iMaskRising);
	virtual bool GetRequestIODigitalInputMask(int *piMaskFalling, int *piMaskRising);
	virtual bool CheckRequestDigitalInputMask(int &iMask);

protected:

public:

	virtual bool SetFilter(enumOEMPAFilterIndex eFilterIndex, WORD &wScale, short wValue[g_iOEMMCFilterCoefficientMax]);
	virtual bool GetFilter(enumOEMPAFilterIndex eFilterIndex, WORD *pwScale, short wValue[g_iOEMMCFilterCoefficientMax]);
protected:

public:

	virtual bool SetEncoderWire1(int iEncoderIndex, enumDigitalInput eDigitalInput);//int iEncoderIndex : 0 for first encoder, 1 for second encoder.
	virtual bool SetEncoderWire2(int iEncoderIndex, enumDigitalInput eDigitalInput);
	virtual bool SetExternalTriggerCycle(enumDigitalInput eDigitalInput);
	virtual bool SetExternalTriggerSequence(enumDigitalInput eDigitalInput);
	virtual bool SetExternalResetEncoder1(enumDigitalInput eDigitalInput);
	virtual bool SetExternalResetEncoder2(enumDigitalInput eDigitalInput);
	virtual bool SetExternalTimestampReset(enumDigitalInput eDigitalInput);//MERGE_PAMINI_PAMAX_MC =0;?
	virtual bool SetExternalEncoderReset(enumDigitalInput eDigitalInput);	// reset both encoders.
	virtual bool SetExternalTrackingReset(enumDigitalInput eDigitalInput);
	virtual bool GetEncoderWire1(int iEncoderIndex, enumDigitalInput *peDigitalInput);
	virtual bool GetEncoderWire2(int iEncoderIndex, enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTriggerCycle(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTriggerSequence(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalResetEncoder1(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalResetEncoder2(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTimestampReset(enumDigitalInput *peDigitalInput);//MERGE_PAMINI_PAMAX_MC =0;?
	virtual bool GetExternalEncoderReset(enumDigitalInput *peDigitalInput);
	virtual bool GetExternalTrackingReset(enumDigitalInput *peDigitalInput);

	virtual bool ResetDigitalInput(enumDigitalInput eDigitalInput);
protected:

public:

	virtual bool SetDigitalOutput(int iIndex, enumOEMPAMiniMappingDigitalIO eMappingDigitalOutput);
	virtual bool GetDigitalOutput(int iIndex, enumOEMPAMiniMappingDigitalIO *peMappingDigitalOutput);
	virtual bool SetDigitalOutput(int iIndex, enumOEMPAMappingDigitalOutput eMappingDigitalOutput);
	virtual bool GetDigitalOutput(int iIndex, enumOEMPAMappingDigitalOutput *peMappingDigitalOutput);
protected:

public:

protected:

public:

	virtual bool SetEncoderDebouncer(double &dValue);
	virtual bool GetEncoderDebouncer(double *pdValue);
	virtual bool CheckEncoderDebouncer(double &dValue);
protected:

public:

	virtual bool SetDigitalDebouncer(double &dValue);
	virtual bool GetDigitalDebouncer(double *pdValue);
	virtual bool CheckDigitalDebouncer(double &dValue);
protected:

public:

	virtual bool SetMultiSystemDebouncer(double &dValue);
	virtual bool GetMultiSystemDebouncer(double *pdValue);
	virtual bool CheckMultiSystemDebouncer(double &dValue);
protected:

public:

	virtual bool SetAnalogBandwidth(enumOEMPAAnalogBandwidth &eAnalogBandwidth);
	virtual bool GetAnalogBandwidth(enumOEMPAAnalogBandwidth *peAnalogBandwidth);
protected:

public:

	virtual bool SetFlushTimer(double &dTimer);
	virtual bool CheckStreamTimer(double &dTimer);
protected:

public:
	// Sets the probe frequency, used for MC2 full-dynamic. Unit is Hertz.
	bool SetProbeFrequency(double &freqInHertz);
	bool GetProbeFrequency(double *freqInHertz);
protected:

public:

#ifdef CYCLE_ORDERING
	virtual bool EnableCycleOrder(bool bEnable);
	virtual bool GetCycleOrderEnable(bool *pbEnable);
	virtual bool SetCycleOrder(int iCycleOrderCount, int *piCycleOrder);
	virtual bool GetCycleOrder(int iCycleOrderCount, int *piCycleOrderCount, int *piCycleOrder);
	virtual bool GetCycleOrder(int iCycleOrderCount, int* piCycleOrderCount, structCallbackArrayInt1D& callbackArrayInt1D);
protected:

public:
#endif //CYCLE_ORDERING
	//[[deprecated]]
	virtual bool SetGainDigital(int iCycle, double &dGain);//to write the amplification.
	//[[deprecated]]
	virtual bool GetGainDigital(int iCycle, double *pdGain);//to read the amplification.
	virtual bool CheckGainDigital(double &dGain, int iCycle = -1);//to check the amplification value (minimum, maximum, step).

	// Functions to handle MC channels.
	/*!
	 * \brief Set the digital gain for a set of channels.
	 * \param[in] iCycle: cycle number for which to set the gains.
	 * \param[in] iChannelCount: sizes of the arrays 'piChannels' and 'pdGain'.
	 * \param[in] piChannel: pointer to an array of channel to change the digital gain.
	 * \param[in] pdGain: pointer to an array of gains to be applied to the inputted channels (dB).
	 * 
	 * For single channel function, see bool SetGainDigital(int iCycle, int iChannel, double &dGain)
	 */
	virtual bool SetGainDigital(int iCycle, int iChannelCount, int *piChannels, double *pdGain);

	/*!
	 * \brief Get the digital gain for a set of channels.
	 * \param[in] iCycle: cycle number for which to get the gains.
	 * \param[in] iArraySize: size of the array 'pdGain'.
	 * \param[out] piChannelCount: pointer to hold the number of gains written in 'pdGain'.
	 * \param[out] pdGain: pointer to an array to hold the gain values for each channel (dB).
	 *
	 * The gain at index 0 will be the one of the first defined channel, not necessarily channel 0.
	 * For single channel function, see bool GetGainDigital(int iCycle, int iChannel, double *pdGain)
	 */
	virtual bool GetGainDigital(int iCycle, int iArraysize, int *piChannelCount, double *pdGain);

	/*!
	 * \brief Set the digital gain for a given channel.
	 * \param[in] iCycle: cycle number for which to set the gain.
	 * \param[in] iChannel: channel for which to apply the digital gain.
	 * \param[in] dGain: gain value to be applied (dB).
	 */
	virtual bool SetGainDigital(int iCycle, int iChannel, double &dGain);

	/*!
	 * \brief Get the digital gain for a given channel.
	 * \param[in] iCycle: cycle number for which to get the gain.
	 * \param[in] iChannel: channel for which to get the digital gain.
	 * \param[out] dGain: pointer to hold the gain value (dB).
	 */
	virtual bool GetGainDigital(int iCycle, int iChannel, double *pdGain);
protected:
protected:
	virtual bool TranslateGainDigital(structNotificationOption &optionNotification, double &dGain, LONG &lHWDataParameter);
	virtual void TranslateGainDigital(LONG lHWDataParameter, double& dGain);
public:

public:

	//SubSequence
	bool DisableSubSequenceTable();
	bool SetSubSequenceTableEncoder(int iSubSequenceCycleCount, int *aiCycleStart, int *aiCycleStop, int iSubSequenceStepCount, DWORD *adwStep);
	bool GetSubSequenceTableEncoder(int iSubSequenceCycleMaxCount, int *aiCycleStart, int *aiCycleStop, int *piSubSequenceCycleCount, int iSubSequenceStepMaxCount, DWORD *adwStep, int *piSubSequenceStepCount);
	bool SetSubSequenceTableEncoder(int iSubSequenceCycleCount, int *aiCycleStart, int *aiCycleStop, int iSubSequenceStepCount, float *afStep);
	bool GetSubSequenceTableEncoder(int iSubSequenceCycleMaxCount, int *aiCycleStart, int *aiCycleStop, int *piSubSequenceCycleCount, int iSubSequenceStepMaxCount, float *afStep, int *piSubSequenceStepCount);
	bool SetSubSequenceTableGate(int iSubSequenceCycleCount, int *aiCycleStart, int *aiCycleStop, int iSubSequenceTofCount, float *afTof);
	bool GetSubSequenceTableGate(int iSubSequenceCycleMaxCount, int *aiCycleStart, int *aiCycleStop, int *piSubSequenceCycleCount, int iSubSequenceTofMaxCount, float *afTof, int *piSubSequenceTofCount);
	bool SetSubSequenceAverage(int &iAverage);
	bool GetSubSequenceAverage(int *piAverage);
public:

public:

	//[[deprecated]]
	virtual bool SetBeamCorrection(int iCycle, float &fGain);
	//[[deprecated]]
	virtual bool GetBeamCorrection(int iCycle, float *pfGain);
	virtual bool CheckBeamCorrection(float &fGain);
	// Functions to handle MC channels.
	/*!
	 * \brief Set the beam correction for a set of channels.
	 * \param[in] iCycle: cycle number for which to set the corrections.
	 * \param[in] iChannelCount: sizes of the arrays 'piChannels' and 'pfGain'.
	 * \param[in] piChannel: pointer to an array of channel to change the correction.
	 * \param[in] pfGain: pointer to an array of gains to be applied to the inputted channels (dB).
	 *
	 * For single channel function, see SetBeamCorrection(int iCycle, int iChannel, float &fGain)
	 */
	virtual bool SetBeamCorrection(int iCycle, int iChannelCount, int *piChannels, float *pfGain);

	/*!
	 * \brief Get the beam correction for a set of channels.
	 * \param[in] iCycle: cycle number for which to get the corrections.
	 * \param[in] iArraySize: size of the array 'pfGain'.
	 * \param[out] piChannelCount: pointer to hold the number of gains written in 'pfGain'.
	 * \param[out] pfGain: pointer to an array to hold the gain values for each channel (dB).
	 *
	 * The gain at index 0 will be the one of the first defined channel, not necessarily channel 0.
	 * For single channel function, see bool GetBeamCorrection(int iCycle, int iChannel, float *pfGain)
	 */
	virtual bool GetBeamCorrection(int iCycle, int iArraysize, int *piChannelCount, float *pfGain);

	/*!
	 * \brief Set the beam correction for a given channel.
	 * \param[in] iCycle: cycle number for which to set the correction.
	 * \param[in] iChannel: channel for which to apply the correction.
	 * \param[in] fGain: gain value to be applied (dB).
	 */
	virtual bool SetBeamCorrection(int iCycle, int iChannel, float &fGain);

	/*!
	 * \brief Get the beam correction for a given channel.
	 * \param[in] iCycle: cycle number for which to get the correction.
	 * \param[in] iChannel: channel for which to get the digital correction.
	 * \param[out] pfGain: pointer to hold the gain value (dB).
	 */
	virtual bool GetBeamCorrection(int iCycle, int iChannel, float *pfGain);
	virtual bool SetBeamCorrection(int iCycle, int iChannel, bool& bEnable);
	virtual bool GetBeamCorrection(int iCycle, int iChannel, bool* pbEnable);
public:

public:

	//[[deprecated("Use bool EnableDAC(int iCycle, int iChannel, bool bEnable) instead.")]]
	virtual bool EnableDAC(int iCycle, bool &bEnable);
	//[[deprecated("Use bool GetEnableDAC(int iCycle, int iChannel, bool *pbEnable) instead.")]]
	virtual bool GetEnableDAC(int iCycle, bool *pbEnable);

	// Functions to handle MC channels.
	/*!
	 * \brief Enable DAC (digital TCG) for a given channel.
	 * \param[in] iCycle: cycle number for which to enable the DAC.
	 * \param[in] iChannel: channel for which to enable the DAC.
	 * \param[in] bEnable: enable (true) or disable (false) DAC for this channel.
	 */
	virtual bool EnableDAC(int iCycle, int iChannel, bool &bEnable);

	/*!
	 * \brief Get the beam correction for a given channel.
	 * \param[in] iCycle: cycle number for which to get the correction.
	 * \param[in] iChannel: channel for which to get the digital correction.
	 * \param[out] pbEnable: pointer to hold the state of the DAC for this channel.
	 */
	virtual bool GetEnableDAC(int iCycle, int iChannel, bool *pbEnable);
	virtual bool CheckDACSlope(double &fTime, float &fSlope);
	virtual bool CheckDACGain(float &fGain);
	virtual bool CheckDACCount(int &iCount);
public:

public:

	//[[deprecated]]
	virtual bool SetAscanRectification(int iCycle, enumRectification eRectification);
	//[[deprecated]]
	virtual bool GetAscanRectification(int iCycle, enumRectification *peRectification);
	// Functions to handle MC channels.
	/*!
	 * \brief Set the ascan rectification for a set of channels.
	 * \param[in] iCycle: cycle number for which to set the rectifications.
	 * \param[in] iChannelCount: sizes of the arrays 'piChannels' and 'peRectification'.
	 * \param[in] piChannel: pointer to an array of channel to change the rectification.
	 * \param[in] peRectification: pointer to an array of rectification mode.
	 *
	 * For possible rectification values see enumRectification.
	 * For single channel function, see bool SetAscanRectification(int iCycle, int iChannel, enumRectification eRectification).
	 */
	virtual bool SetAscanRectification(int iCycle, int iChannelCount, int *piChannels, enumRectification *peRectification);

	/*!
	 * \brief Get the ascan rectification for a set of channels.
	 * \param[in] iCycle: cycle number for which to get the rectifications.
	 * \param[in] iArraySize: size of the array 'peRectification'.
	 * \param[out] piChannelCount: pointer to hold the number of gains written in 'peRectification'.
	 * \param[out] peRectification: pointer to an array to hold the rectification mode for each channel.
	 *
	 * The rectification at index 0 will be the one of the first defined channel, not necessarily channel 0.
	 * For possible rectification values see enumRectification.
	 * For single channel function, see bool GetAscanRectification(int iCycle, int iChannel, enumRectification *peRectification).
	 */
	virtual bool GetAscanRectification(int iCycle, int iArraysize, int *piChannelCount, enumRectification *peRectification);

	/*!
	 * \brief Set the ascan rectification for a given channel.
	 * \param[in] iCycle: cycle number for which to set the rectification.
	 * \param[in] iChannel: channel for which to apply the rectification.
	 * \param[in] eRectification: rectification mode to be applied.
	 *
	 * For possible rectification values see enumRectification.
	 */
	virtual bool SetAscanRectification(int iCycle, int iChannel, enumRectification eRectification);

	/*!
	 * \brief Get the ascan rectification for a given channel.
	 * \param[in] iCycle: cycle number for which to get the rectification.
	 * \param[in] iChannel: channel for which to get the digital rectification.
	 * \param[out] peRectification: pointer to hold the rectification mode for this channel.
	 *
	 * For possible rectification values see enumRectification.
	 */
	virtual bool GetAscanRectification(int iCycle, int iChannel, enumRectification *peRectification);
public:

public:

	//[[deprecated]]
	virtual bool SetAscanStart(int iCycle, double &dStart);
	//[[deprecated]]
	virtual bool GetAscanStart(int iCycle, double *pdStart);
	virtual bool CheckAscanStart(double &dStart);
	// Functions to handle MC channels.
	/*!
	 * \brief Set the ascan start for a set of channels.
	 * \param[in] iCycle: cycle number for which to set the ascan starts.
	 * \param[in] iChannelCount: sizes of the arrays 'piChannels' and 'pdStart'.
	 * \param[in] piChannel: pointer to an array of channel to change the start.
	 * \param[in] pdStart: pointer to an array of ascan starts.
	 *
	 * For single channel function, see SetAscanStart(int iCycle, int iChannel, double &dStart).
	 */
	virtual bool SetAscanStart(int iCycle, int iChannelCount, int *piChannels, double *pdStart);

	/*!
	 * \brief Get the ascan start for a set of channels.
	 * \param[in] iCycle: cycle number for which to get the starts.
	 * \param[in] iArraySize: size of the array 'pdStart'.
	 * \param[out] piChannelCount: pointer to hold the number of gains written in 'pdStart'.
	 * \param[out] pdStart: pointer to an array to hold the ascan start for each channel.
	 *
	 * The start at index 0 will be the one of the first defined channel, not necessarily channel 0.
	 * For single channel function, see bool GetAscanStart(int iCycle, int iChannel, double *pdStart).
	 */
	virtual bool GetAscanStart(int iCycle, int iArraysize, int *piChannelCount, double *pdStart);

	/*!
	 * \brief Set the ascan start for a given channel.
	 * \param[in] iCycle: cycle number for which to set the ascan start.
	 * \param[in] iChannel: channel for which to apply the ascan start.
	 * \param[in] dStart: start to be applied.
	 */
	virtual bool SetAscanStart(int iCycle, int iChannel, double &dStart);

	/*!
	 * \brief Get the ascan start for a given channel.
	 * \param[in] iCycle: cycle number for which to get the ascan start.
	 * \param[in] iChannel: channel for which to get the digital ascan start.
	 * \param[out] pdStart: pointer to hold the ascan start for this channel.
	 */
	virtual bool GetAscanStart(int iCycle, int iChannel, double *pdStart);
public:
#ifdef POUR_MEMOIRE
#endif //POUR_MEMOIRE

public:

	//[[deprecated]]
	virtual bool SetAscanRange(int iCycle, double &dRange,/*output only*/enumCompressionType &eCompressionType,/*output only*/LONG &lPointCount,/*output only*/LONG &lPointFactor);//point count is automatically calculated from the digitizing clock.
			//Input is the range, this function determines the point count, the digitizing frequency is the default HW clock (normally 100 MHz).
	//[[deprecated]]
	virtual bool SetAscanRangeWithFactor(int iCycle, double &dRange, enumCompressionType &eCompressionType,/*in/out*/LONG &lPointFactor,/*output only*/LONG &lPointCount);
	//Inputs are range + factor, this function determines the point count.
	//two compressions are available:
	//	"eCompression": compression with minimum and maximum.
	//	"eDecimation": compression fixed digitizing frequency (no minimum and maximum).
	//DigitizingFrequency = clock x lPointFactor / 256
	//normally clock=100 MHz
	//"lPointFactor" range is 1 to 256.
	//[[deprecated]]
	virtual bool SetAscanRangeWithCount(int iCycle, double &dRange,/*in/out (check)*/enumCompressionType &eCompressionType,/*in/out (check)*/LONG &lPointCount,/*output only*/LONG &lPointFactor);
	//[[deprecated]]
	virtual bool GetAscanRange(int iCycle, double *pdRange, enumCompressionType *peCompressionType, LONG *plPointCount, LONG *plPointFactor);
	virtual bool CheckAscanRange(double &dRange);
	virtual bool CheckPointCount(LONG &lPointCount);
	virtual bool CheckPointCount(LONG& lPointCount, enumBitSize eAscanBitSize);
	virtual bool CheckPointFactor(LONG &lPointFactor);
	virtual bool CheckAscanRangeWithCount(double &dRange, enumCompressionType &eCompressionType, LONG &lPointCount);
	virtual bool GetSamplingFrequency(enumCompressionType eCompressionType, LONG lPointFactor, double &dSamplingFrequency/*Hertz*/);
	// Functions to handle MC channels.
	// Single channel
	/*!
	 * \brief Set the ascan range for a given channel.
	 * \param[in] iCycle: cycle number for which to set the ascan range.
	 * \param[in] iChannel: channel for which to apply the ascan range.
	 * \param[in,out] dRange: range to be applied.
	 * \param[out] eCompressionType: will be 'eCompression' with this function.
	 * \param[out] lPointCount: calculated from range and digitizing clock.
	 * \param[out] lPointFactor: will be 1 with this function.
	 */
	virtual bool SetAscanRange(int iCycle, int iChannel, double &dRange,/*output only*/enumCompressionType &eCompressionType,/*output only*/LONG &lPointCount,/*output only*/LONG &lPointFactor);//point count is automatically calculated from the digitizing clock.

	/*!
	 * \brief Set the ascan range, compression type and compression factor for a given channel.
	 * \param[in] iCycle: cycle number for which to set the ascan range.
	 * \param[in] iChannel: channel for which to apply the ascan range.
	 * \param[in,out] dRange: range to be applied.
	 * \param[in] eCompressionType: Compression type to be applied.
	 * \param[out] lPointCount: calculated from range, compression factor and digitizing clock.
	 * \param[in,out] lPointFactor: compression factor to be used. See decription below for more information.
	 *
	 * This function should be used with decimation, to set compression see SetAscanRangeWithCount().
	 * PointFactor and compression mode explanation:
	 *	In "compression", the maximum values of the signal are kept in the Max
	 *		Buffer, and the minimum values in the Min Buffer,
	 *		but there is distortion in the resulting signals.
	 *		The resulting sampling frequency is 100*n/256 MHz, with n=[1;256]
	 *	In "decimation", the frequency structure of the signal is kept,
	 *		but the maximum and minimum of the signal can be lost.
	 *		The resulting sampling frequency is 100/n MHz, with n=[1;256]
	 */
	virtual bool SetAscanRangeWithFactor(int iCycle, int iChannel, double &dRange, enumCompressionType &eCompressionType,/*in/out*/LONG &lPointFactor,/*output only*/LONG &lPointCount);

	/*!
	 * \brief Set the ascan range, compression type and compression factor for a given channel.
	 * \param[in] iCycle: cycle number for which to set the ascan range.
	 * \param[in] iChannel: channel for which to apply the ascan range.
	 * \param[in,out] dRange: range to be applied.
	 * \param[in] eCompressionType: Compression type to be applied.
	 * \param[out] lPointFactor: calculated from range, point count and digitizing clock. See decription below for more information.
	 * \param[int,out] lPointCount: point count to be applied (number of samples returned).
	 *
	 * This function should be used with compression, to set decimation see SetAscanRangeWithFactor().
	 * PointFactor and compression mode explanation:
	 *	In "compression", the maximum values of the signal are kept in the Max
	 *		Buffer, and the minimum values in the Min Buffer,
	 *		but there is distortion in the resulting signals.
	 *		The resulting sampling frequency is 100*n/256 MHz, with n=[1;256]
	 *	In "decimation", the frequency structure of the signal is kept,
	 *		but the maximum and minimum of the signal can be lost.
	 *		The resulting sampling frequency is 100/n MHz, with n=[1;256]
	 */
	virtual bool SetAscanRangeWithCount(int iCycle, int iChannel, double &dRange,/*in/out (check)*/enumCompressionType &eCompressionType,/*in/out (check)*/LONG &lPointCount,/*output only*/LONG &lPointFactor);

	/*!
	 * \brief Get the ascan range, compression type, compression factor and point count for a given channel.
	 * \param[in] iCycle: cycle number for which to get the ascan range.
	 * \param[in] iChannel: channel for which to get the ascan range.
	 * \param[out] pdRange: pointer to hold the range.
	 * \param[out] peCompressionType: pointer to hold the compression type.
	 * \param[out] plPointCount: pointer to hold the point count.
	 * \param[out] plPointFactor: pointer to hold the compression factor. See decription below for more information.
	 *
	 * PointFactor and compression mode explanation:
	 *	In "compression", the maximum values of the signal are kept in the Max
	 *		Buffer, and the minimum values in the Min Buffer,
	 *		but there is distortion in the resulting signals.
	 *		The resulting sampling frequency is 100*n/256 MHz, with n=[1;256]
	 *	In "decimation", the frequency structure of the signal is kept,
	 *		but the maximum and minimum of the signal can be lost.
	 *		The resulting sampling frequency is 100/n MHz, with n=[1;256]
	 */
	virtual bool GetAscanRange(int iCycle, int iChannel, double *pdRange, enumCompressionType *peCompressionType, LONG *plPointCount, LONG *plPointFactor);

	// Channel list
	/*!
	 * \brief Set the ascan range for a given set of channels.
	 * \param[in] iCycle: cycle number for which to set the ascan ranges.
	 * \param[in] iChannelCount: size of the 'piChannels' array.
	 * \param[in] piChannels: channel list for which to apply the ascan ranges.
	 * \param[in] pdRange: range list to be applied.
	 * \param[out] peCompressionType: will be 'eCompression' with this function.
	 * \param[out] plPointCount: calculated from range and digitizing clock.
	 * \param[out] plPointFactor: will be 1 with this function.
	 */
	virtual bool SetAscanRange(int iCycle, int iChannelCount, int *piChannels, double *pdRange,/*output only*/enumCompressionType *peCompressionType,/*output only*/LONG *plPointCount,/*output only*/LONG *plPointFactor);

	// The following 2 functions should be used only if 'peCompressionType' is the same for all channels.
	/*!
	 * \brief Set the ascan range, compression type and compression factor for a given set of channels.
	 * \param[in] iCycle: cycle number for which to set the ascan ranges.
	 * \param[in] iChannelCount: size of the 'piChannels' array.
	 * \param[in] piChannels: channel list for which to apply the ascan ranges.
	 * \param[in,out] pdRange: range list to be applied.
	 * \param[in] peCompressionType: Compression type to be applied.
	 * \param[out] plPointCount: calculated from range, compression factor and digitizing clock.
	 * \param[in,out] plPointFactor: compression factor to be used. See decription below for more information.
	 *
	 * This function should be used with decimation, to set compression see SetAscanRangeWithCount().
	 * PointFactor and compression mode explanation:
	 *	In "compression", the maximum values of the signal are kept in the Max
	 *		Buffer, and the minimum values in the Min Buffer,
	 *		but there is distortion in the resulting signals.
	 *		The resulting sampling frequency is 100*n/256 MHz, with n=[1;256]
	 *	In "decimation", the frequency structure of the signal is kept,
	 *		but the maximum and minimum of the signal can be lost.
	 *		The resulting sampling frequency is 100/n MHz, with n=[1;256]
	 */
	virtual bool SetAscanRangeWithFactor(int iCycle, int iChannelCount, int *piChannels, double *pdRange,/*output only*/enumCompressionType *peCompressionType,/*in/out*/LONG *plPointFactor,/*output only*/LONG *plPointCount);

	/*!
	 * \brief Set the ascan range, compression type and compression factor for a given set of channels.
	 * \param[in] iCycle: cycle number for which to set the ascan ranges.
	 * \param[in] iChannelCount: size of the 'piChannels' array.
	 * \param[in] piChannels: channel list for which to apply the ascan ranges.
	 * \param[in,out] pdRange: range list to be applied.
	 * \param[in] peCompressionType: Compression type to be applied.
	 * \param[out] plPointFactor: calculated from range, point count and digitizing clock. See decription below for more information.
	 * \param[int,out] plPointCount: point count to be applied (number of samples returned).
	 *
	 * This function should be used with compression, to set decimation see SetAscanRangeWithFactor().
	 * PointFactor and compression mode explanation:
	 *	In "compression", the maximum values of the signal are kept in the Max
	 *		Buffer, and the minimum values in the Min Buffer,
	 *		but there is distortion in the resulting signals.
	 *		The resulting sampling frequency is 100*n/256 MHz, with n=[1;256]
	 *	In "decimation", the frequency structure of the signal is kept,
	 *		but the maximum and minimum of the signal can be lost.
	 *		The resulting sampling frequency is 100/n MHz, with n=[1;256]
	 */
	virtual bool SetAscanRangeWithCount(int iCycle, int iChannelCount, int *piChannels, double *pdRange,/*in/out (check)*/enumCompressionType *peCompressionType,/*in/out (check)*/LONG *plPointCount,/*output only*/LONG *plPointFactor);

	/*!
	 * \brief Get the ascan range, compression type, compression factor and point count for a given channel.
	 * \param[in] iCycle: cycle number for which to get the ascan ranges.
	 * \param[in] iArraysize: size of the 'piChannels' array.
	 * \param[out] piChannelCount: pointer to hold the number of channels defined for this cycles, that is the number of values put in the arrays 'pdRange', 'peCompressionType', 'plPointCount' and 'plPointFactor' by this function.
	 * \param[out] pdRange: array to hold the ranges.
	 * \param[out] peCompressionType: array to hold the compression types.
	 * \param[out] plPointCount: array to hold the point counts.
	 * \param[out] plPointFactor: array to hold the compression factors. See decription below for more information.
	 *
	 * PointFactor and compression mode explanation:
	 *	In "compression", the maximum values of the signal are kept in the Max
	 *		Buffer, and the minimum values in the Min Buffer,
	 *		but there is distortion in the resulting signals.
	 *		The resulting sampling frequency is 100*n/256 MHz, with n=[1;256]
	 *	In "decimation", the frequency structure of the signal is kept,
	 *		but the maximum and minimum of the signal can be lost.
	 *		The resulting sampling frequency is 100/n MHz, with n=[1;256]
	 */
	virtual bool GetAscanRange(int iCycle, int iArraysize, int *piChannelCount, double *pdRange, enumCompressionType *peCompressionType, LONG *plPointCount, LONG *plPointFactor);
public:

public:

	//[[deprecated]]
	virtual bool SetFilterIndex(int iCycle, enumOEMPAFilterIndex eFilterIndex);
	//[[deprecated]]
	virtual bool GetFilterIndex(int iCycle, enumOEMPAFilterIndex *peFilterIndex);
	// Functions to handle MC channels.
	virtual bool SetFilterIndex(int iCycle, int iChannelCount, int *piChannels, enumOEMPAFilterIndex *peFilterIndex);
	virtual bool GetFilterIndex(int iCycle, int iArraysize, int *piChannelCount, enumOEMPAFilterIndex *peFilterIndex);
	virtual bool SetFilterIndex(int iCycle, int iChannel, enumOEMPAFilterIndex &eFilterIndex);
	virtual bool GetFilterIndex(int iCycle, int iChannel, enumOEMPAFilterIndex *peFilterIndex);
public:

public:

	virtual bool SetTimeSlot(int iCycle, double &dTimeSlot);
	virtual bool GetTimeSlot(int iCycle, double *pdTimeSlot);
	virtual bool CheckTimeSlot(double &dTimeSlot);
	double GetTimeSlotMinimumCompression(DWORD channels, enumBitSize eAscanBitSize, LONG* pointCounts, LONG* starts, LONG* ranges, LONG* wedgesE, LONG* wedgesR);
	double GetTimeSlotMinimumDecimation(DWORD channels, enumBitSize eAscanBitSize, LONG* pointFactors, LONG* starts, LONG* ranges, LONG* wedgesE, LONG* wedgesR);
	virtual double vf_GetRecoveryTime(DWORD channels, enumBitSize eAscanBitSize, enumCompressionType* eCompressionTypes, LONG* pointCounts, LONG* pointFactors, LONG* ranges);
	virtual double vf_GetMinTimeSlotRecovery(DWORD channels, enumBitSize eAscanBitSize, enumCompressionType* eCompressionTypes, LONG* pointCounts, LONG* pointFactors, LONG* starts, LONG* ranges, LONG* wedgesE, LONG* wedgesR);
	virtual double vf_GetMinTimeSlotRecovery(structCheckRecoveryTimePA *pRecoveryTimePA);
	virtual double vf_GetMaxRangeRecovery(structCheckRecoveryTimePA* pRecoveryTimePA);
	//FMC SubTimeSlot management
	virtual bool SetFMCSubTimeSlotAcqReplay(int iCycle, double dAscanStart, double dAscanRange, double &dTimeSlot);//easy function to use
	virtual bool GetFMCTimeLimitation(double dAscanStart, double dAscanRange, double dTimeSlot, double &dTimeSlotMin, double &dHWAcqSubTimeSlotMin, double &dReplaySubTimeSlotMin, double &dReplaySubTimeSlotOptimizedForThroughput);
	virtual bool GetFMCTimeLimitation(int iFMCSubCycleCount, double dAscanStart, double dAscanRange, double dTimeSlot, double &dTimeSlotMin, double &dHWAcqSubTimeSlotMin, double &dReplaySubTimeSlotMin, double &dReplaySubTimeSlotOptimizedForThroughput);
	virtual int GetFMCSubTimeSlotCount();
	//instead to call "SetFMCSubTimeSlotAcq" and "SetFMCSubTimeSlotReplay" you can call "SetFMCSubTimeSlotAcqReplay" which is easier to use.
	virtual bool SetFMCSubTimeSlotAcq(int iCycle, double &dSubTimeSlot);
	virtual bool SetFMCSubTimeSlotReplay(int iCycle, double &dSubTimeSlot);
	virtual bool GetFMCSubTimeSlotAcq(int iCycle, double *pdSubTimeSlot);
	virtual bool GetFMCSubTimeSlotReplay(int iCycle, double *pdSubTimeSlot);
public:
protected:
	virtual bool TranslateTimeSlot(structNotificationOption &optionNotification, double &dTimeSlot, DWORD &dwHWDataParameter);
	virtual bool TranslateTimeSlot(DWORD &dwHWDataParameter, double &dTimeSlot);
public:

public:

	//[[deprecated]]
	virtual bool SetAscanAcqIdChannelProbe(int iCycle, WORD &wID);
	//[[deprecated]]
	virtual bool GetAscanAcqIdChannelProbe(int iCycle, WORD *pwID);
	// Functions to handle MC channels.
	virtual bool SetAscanAcqIdChannelProbe(int iCycle, int iChannelCount, int *piChannels, WORD *pwID);
	virtual bool GetAscanAcqIdChannelProbe(int iCycle, int iArraysize, int *piChannelCount, WORD *pwID);
	virtual bool SetAscanAcqIdChannelProbe(int iCycle, int iChannel, WORD &wID);
	virtual bool GetAscanAcqIdChannelProbe(int iCycle, int iChannel, WORD *pwID);
public:

public:

	//[[deprecated]]
	virtual bool SetAscanAcqIdChannelScan(int iCycle, WORD &wID);
	//[[deprecated]]
	virtual bool GetAscanAcqIdChannelScan(int iCycle, WORD *pwID);
	// Functions to handle MC channels.
	virtual bool SetAscanAcqIdChannelScan(int iCycle, int iChannelCount, int *piChannels, WORD *pwID);
	virtual bool GetAscanAcqIdChannelScan(int iCycle, int iArraysize, int *piChannelCount, WORD *pwID);
	virtual bool SetAscanAcqIdChannelScan(int iCycle, int iChannel, WORD &wID);
	virtual bool GetAscanAcqIdChannelScan(int iCycle, int iChannel, WORD *pwID);
public:

public:

	//[[deprecated]]
	virtual bool SetAscanAcqIdChannelCycle(int iCycle, WORD &wID);
	//[[deprecated]]
	virtual bool GetAscanAcqIdChannelCycle(int iCycle, WORD *pwID);
	// Functions to handle MC channels.
	virtual bool SetAscanAcqIdChannelCycle(int iCycle, int iChannelCount, int *piChannels, WORD *pwID);
	virtual bool GetAscanAcqIdChannelCycle(int iCycle, int iArraysize, int *piChannelCount, WORD *pwID);
	virtual bool SetAscanAcqIdChannelCycle(int iCycle, int iChannel, WORD &wID);
	virtual bool GetAscanAcqIdChannelCycle(int iCycle, int iChannel, WORD *pwID);
public:

public:

	virtual bool EnableAscanMaximum(int iCycle, bool bEnable);
	virtual bool GetEnableAscanMaximum(int iCycle, bool *pbEnable);
public:

public:

	virtual bool EnableAscanMinimum(int iCycle, bool bEnable);
	virtual bool GetEnableAscanMinimum(int iCycle, bool *pbEnable);
public:

public:

	virtual bool EnableAscanSaturation(int iCycle, bool bEnable);
	virtual bool GetEnableAscanSaturation(int iCycle, bool *pbEnable);
public:

public:

	//[[deprecated]]
	virtual bool SetGateModeThreshold(int iCycle, int iGate, bool bEnable, double dThresholdPercent, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification);
	//[[deprecated]]
	virtual bool SetGateModeThreshold(int iCycle, int iGate, bool &bEnable, enumGateModeAmp &eGateModeAmp, enumGateModeTof &eGateModeTof, enumRectification &eGateRectification, double &dThresholdPercent);
	//[[deprecated]]
	virtual bool GetGateModeThreshold(int iCycle, int iGate, bool *pbEnable, enumGateModeAmp *peGateModeAmp, enumGateModeTof *peGateModeTof, enumRectification *peGateRectification, double *pdThresholdPercent);
	//[[deprecated]]
	virtual bool CheckGateModeThreshold(bool &bEnable, enumGateModeAmp &eGateModeAmp, enumGateModeTof &eGateModeTof, enumRectification &eGateRectification, double &dThresholdPercent);
	// Functions to handle MC channels.
	virtual bool SetGateModeThreshold(int iCycle, int iChannel, int iGate, bool &bEnable, enumGateModeAmp &eGateModeAmp, enumGateModeTof &eGateModeTof, enumRectification &eGateRectification, double &dThresholdPercent);
	virtual bool SetGateModeThreshold(int iCycle, int iChannel, int iGate, bool bEnable, double dThresholdPercent, enumGateModeAmp eGateModeAmp, enumGateModeTof eGateModeTof, enumRectification eGateRectification);
	virtual bool GetGateModeThreshold(int iCycle, int iChannel, int iGate, bool *pbEnable, enumGateModeAmp *peGateModeAmp, enumGateModeTof *peGateModeTof, enumRectification *peGateRectification, double *pdThresholdPercent);
public:

public:

	//[[deprecated]]
	virtual bool SetGateStart(int iCycle, int iGate, double &dStart);
	//[[deprecated]]
	virtual bool GetGateStart(int iCycle, int iGate, double *pdStart);
	//[[deprecated]]
	virtual bool CheckGateStart(double &dStart);
	// Functions to handle MC channels.
	virtual bool SetGateStart(int iCycle, int iChannel, int iGate, double &dStart);
	virtual bool GetGateStart(int iCycle, int iChannel, int iGate, double *pdStart);
public:

public:

	//[[deprecated]]
	virtual bool SetGateStop(int iCycle, int iGate, double &dStop);
	//[[deprecated]]
	virtual bool GetGateStop(int iCycle, int iGate, double *pdStop, bool *pbWidth = NULL);
	//[[deprecated]]
	virtual bool CheckGateStop(double &dStop);
	virtual bool CheckGateStartStop(double &dStart, double &dStop);
	// Functions to handle MC channels.
	virtual bool SetGateStop(int iCycle, int iChannel, int iGate, double &dStop);
	virtual bool GetGateStop(int iCycle, int iChannel, int iGate, double *pdStop, bool *pbWidth = NULL);
public:

public:

	//[[deprecated]]
	virtual bool SetGateAcqIDAmp(int iCycle, int iGate, WORD &wID);
	//[[deprecated]]
	virtual bool GetGateAcqIDAmp(int iCycle, int iGate, WORD *pwID);
	//[[deprecated]]
	virtual bool SetGateAcqIDTof(int iCycle, int iGate, WORD &wID);
	//[[deprecated]]
	virtual bool GetGateAcqIDTof(int iCycle, int iGate, WORD *pwID);
	// Functions to handle MC channels.
	virtual bool SetGateAcqIDAmp(int iCycle, int iChannel, int iGate, WORD &wID);
	virtual bool GetGateAcqIDAmp(int iCycle, int iChannel, int iGate, WORD *pwID);
	virtual bool SetGateAcqIDTof(int iCycle, int iChannel, int iGate, WORD &wID);
	virtual bool GetGateAcqIDTof(int iCycle, int iChannel, int iGate, WORD *pwID);
public:

public:

	//[[deprecated]]
	virtual bool SetTrackingGateStart(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	//[[deprecated]]
	virtual bool GetTrackingGateStart(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex);
	//[[deprecated]]
	virtual bool SetSWTrackingGateStartFromHW(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	//[[deprecated]]
	virtual bool GetSWTrackingGateStartFromHW(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex);
	//[[deprecated]]
	virtual bool SetTrackingGateStop(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	//[[deprecated]]
	virtual bool GetTrackingGateStop(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex);
	//[[deprecated]]
	virtual bool SetSWTrackingGateStopFromHW(int iCycle, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	//[[deprecated]]
	virtual bool GetSWTrackingGateStopFromHW(int iCycle, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex);
	//[[deprecated]]
	virtual bool SetTrackingAscan(int iCycle, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	//[[deprecated]]
	virtual bool GetTrackingAscan(int iCycle, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex);
	//[[deprecated]]
	virtual bool SetTrackingDac(int iCycle, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex);
	//[[deprecated]]
	virtual bool GetTrackingDac(int iCycle, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingGateIndex);
	// Functions to handle MC channels.
	virtual bool SetTrackingGateStart(int iCycle, int iChannel, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool GetTrackingGateStart(int iCycle, int iChannel, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);
	virtual bool SetTrackingGateStop(int iCycle, int iChannel, int iGate, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool GetTrackingGateStop(int iCycle, int iChannel, int iGate, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);

	/*!
	 * \brief Set the DAC tracking for a given channel.
	 *
	 * The DAC of the channel 'iChannel' of cycle 'iCycle' will be synchronised on 
	 * the gate 'iTrackingGateIndex' of channel 'iTrackingChannelIndex' of cycle 'iTrackingCycleIndex'.
	 *
	 * \param[in] iCycle: cycle number for which to set the DAC tracking.
	 * \param[in] iChannel: channel for which to set the DAC tracking.
	 * \param[in] bEnable: enable/disable DAC tracking for this channel.
	 * \param[in,out] iTrackingCycleIndex: cycle of the gate to be synchronized on.
	 * \param[in,out] iTrackingChannelIndex: channel of the gate to be synchronized on.
	 * \param[in,out] iTrackingGateIndex: index of the gate to be synchronized on.
	 */
	virtual bool SetTrackingDac(int iCycle, int iChannel, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool GetTrackingDac(int iCycle, int iChannel, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);
	virtual bool SetTrackingAscan(int iCycle, int iChannel, bool &bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool GetTrackingAscan(int iCycle, int iChannel, bool *pbEnable, int *piTrackingCycleIndex, int *piTrackingChannelIndex, int *piTrackingGateIndex);
	virtual bool CheckTracking(bool bEnable, int &iTrackingCycleIndex, int &iTrackingChannelIndex, int &iTrackingGateIndex);
	virtual bool CheckTracking(bool bEnable, int &iTrackingCycleIndex, int &iTrackingGateIndex) { return true; };
	virtual bool ResetTrackingTable();//this is called automatically when the IF tracking of one gate is updated.
public:

public:
	// Bipolar high voltage control, positive = [25; 100], negative = [-100; -25], abs(negative) >= positive. Unit is Volt.
	virtual bool SetHighVoltageBipolar(int &positive, int &negative);
	virtual bool GetHighVoltageBipolar(int *positive, int *negative);
	// Capacitive (negative) high voltage control, voltage = [25; 400]. Unit is Volt. Negative values in the same range are also valid.
	virtual bool SetHighVoltage(int &voltage);
	virtual bool GetHighVoltage(int* voltage);
public:

public:
	/*!
	 * \brief Set the analog gain.
	 * \param[in] iCycle: cycle number for which to set the analog gain (ignored for MC2).
	 * \param[in,out] fGain: analog gain to be applied.
	 *
	 * This function should be used with MCu, MC-H and MC-NOV.
	 * For the MC2, the analog gain is common to all cycles, see SetGainAnalog(float &fGain).
	 * If used with MC2, the 'iCycle' argument is ignored.
	 */
	virtual bool SetGainAnalog(int iCycle, float &fGain);

	/*!
	 * \brief Get the analog gain.
	 * \param[in] iCycle: cycle number for which to get the analog gain (ignored for MC2).
	 * \param[out] pfGain: pointer to hold the analog gain.
	 *
	 * This function should be used with MCu, MC-H and MC-NOV.
	 * For the MC2, the analog gain is common to all channel, see SetGainAnalog(float &fGain).
	 * If used with MC2, the 'iCycle' argument is ignored.
	 */
	virtual bool GetGainAnalog(int iCycle, float *pfGain);

	/*!
	 * \brief Set the analog gain.
	 * \param[in,out] fGain: analog gain to be applied.
	 *
	 * This function should be used with MC2.
	 * For the MCu, MC-H and MC-NOV, the analog gain is a per cycle setting,
	 * see SetGainAnalog(int iCycle, float &fGain).
	 * If used with MCu, MC-H or MC-NOV, the gain will only be applied to cycle 0.
	 */
	virtual bool SetGainAnalog(float &fGain);

	/*!
	 * \brief Set the analog gain.
	 * \param[out] pfGain: pointer to hold the analog gain.
	 *
	 * This function should be used with MC2.
	 * For the MCu, MC-H and MC-NOV, the analog gain is a per cycle setting,
	 * see SetGainAnalog(int iCycle, float &fGain).
	 * If used with MCu, MC-H or MC-NOV, the will always get the gain of cycle 0.
	 */
	virtual bool GetGainAnalog(float *pfGain);

	virtual bool CheckGainAnalog(float &fGain);
public:

public:

public:
#ifdef POUR_MEMOIRE
#endif // POUR_MEMOIRE

public:

	//[[deprecated]]
	virtual bool SetEmissionWedgeDelay(int iCycle, int iCycleCount, double &dWedgeDelay);//"iCycleCount"=cycle count.
	//[[deprecated]]
	virtual bool GetEmissionWedgeDelay(int iCycle, int iCountMax, double *pdWedgeDelay);
	//[[deprecated]]
	virtual bool SetReceptionWedgeDelay(int iCycle, int iCycleCount, double &dWedgeDelay);
	//[[deprecated]]
	virtual bool GetReceptionWedgeDelay(int iCycle, int iCountMax, double *pdWedgeDelay);
	virtual bool CheckWedgeDelay(double &dWedgeDelay);
	// Functions to handle MC channels.
	virtual bool SetEmissionWedgeDelay(int iCycle, int iChannelCount, int *piChannels, double *pdWedgeDelay);
	virtual bool GetEmissionWedgeDelay(int iCycle, int iArraysize, int *piChannelCount, double *pdWedgeDelay);
	virtual bool SetEmissionWedgeDelaySingleChannel(int iCycle, int iChannel, double &dWedgeDelay);
	virtual bool GetEmissionWedgeDelaySingleChannel(int iCycle, int iChannel, double *pdWedgeDelay);
	virtual bool SetReceptionWedgeDelay(int iCycle, int iChannelCount, int *piChannels, double *pdWedgeDelay);
	virtual bool GetReceptionWedgeDelay(int iCycle, int iArraysize, int *piChannelCount, double *pdWedgeDelay);
	virtual bool SetReceptionWedgeDelaySingleChannel(int iCycle, int iChannel, double &dWedgeDelay);
	virtual bool GetReceptionWedgeDelaySingleChannel(int iCycle, int iChannel, double *pdWedgeDelay);
public:

public:

	//[[deprecated]]
	static bool SetAllElementEnable(bool bEnable, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	//[[deprecated]]
	static bool SetElementEnable(int iChannel, bool bEnable, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	//[[deprecated]]
	static bool GetElementEnable(int iChannel, const DWORD adwHWAperture[g_iOEMPAApertureDWordCount], bool &bEnable);
	static bool SetAllElementEnable(bool bEnable, int iOEMPAApertureDWordCount, DWORD *pdwHWAperture);
	static bool SetElementEnable(int iChannel, bool bEnable, int iOEMPAApertureDWordCount, DWORD *pdwHWAperture);
	static bool GetElementEnable(int iChannel, int iOEMPAApertureDWordCount, const DWORD *pdwHWAperture, bool &bEnable);

//OLD STYLE FUNCTIONS (limited to 128 elements).
	//APERTURE DEFINITION : 2 cases.
	virtual bool IsMultiplexer();//this function can be used to know if a multiplexer (16:128 or 32:128) is included in the system.
	//Case of a system with a multiplexer (16:128 or 32:128), please use following functions:
	//	multiplexer case: if emission and reception have same aperture:
	//[[deprecated]]
	virtual bool SetMultiplexerEnable(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	//[[deprecated]]
	virtual bool GetMultiplexerEnable(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	//	multiplexer case: if emission and reception aperture are different:
	//	(you cannot have more than 32 elements in case of a 32/128 and 16 elements in case of a 16/128).
	//[[deprecated]]
	virtual bool SetMultiplexerEnable(int iCycle, DWORD adwHWApertureEmission[g_iOEMPAApertureDWordCount], DWORD adwHWApertureReception[g_iOEMPAApertureDWordCount]);
	//[[deprecated]]
	virtual bool GetMultiplexerEnable(int iCycle, DWORD adwHWApertureEmission[g_iOEMPAApertureDWordCount], DWORD adwHWApertureReception[g_iOEMPAApertureDWordCount]);
	//[[deprecated]]
	virtual bool CheckMultiplexerAperture(DWORD adwHWApertureEmission[g_iOEMPAApertureDWordCount], DWORD adwHWApertureReception[g_iOEMPAApertureDWordCount]);//to check that emission and reception apertures are coherent.

	//for compatibility with the 1.1.5.4 version
	virtual bool SetEmissionEnable(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetEmissionEnable(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool SetReceptionEnable(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetReceptionEnable(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
public:

public:

	//for compatibility with the 1.1.5.4 version
	virtual bool SetEmissionDelays(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float *pfDelay);
	virtual bool SetEmissionDelays(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	virtual bool SetEmissionWidth(int iCycle, int iChannelIndex, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float &fWidth);
	virtual bool SetEmissionWidths(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float *pfWidth);
	virtual bool SetEmissionWidths(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], structCallbackArrayFloat1D &callbackArrayFloat1D);
	//[[deprecated]]
	virtual bool SetReceptionGain(int iCycle, int iElementIndex, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float &fGain);
	//[[deprecated]]
	virtual bool SetReceptionGains(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float *pfGain);
	//[[deprecated]]
	virtual bool SetReceptionGains(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], structCallbackArrayFloat1D &callbackArrayFloat1D);
	//[[deprecated]]
	virtual bool SetReceptionDelays(int iCycle, int iLineSize, int &iFocalCount, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float *pfDelay);
	//[[deprecated]]
	virtual bool SetReceptionDelays(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.
	//[[deprecated]]
	virtual bool GetReceptionNormalisationDelayAv(bool bEmission, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float &fDelay);
	//[[deprecated]]
	virtual bool SetReceptionDelays(int iCycle, int iLineSize, int &iFocalCount, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], float *pfDelay, float *pfDelayOffset);
	//[[deprecated]]
	virtual bool SetReceptionDelays(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount], structCallbackArrayFloat2D &callbackArrayFloat2D, float *pfDelayOffset);//Size1 = element size, Size2 = DDF size.

//NEW STYLE FUNCTIONS (no limitation for the aperture).
	//[[deprecated]]
	virtual bool SetMultiplexerEnable(int iCycle, int iEltCntEmission, int iEltCntReception, int *piEltListEmission, int *piEltListReception);
	//[[deprecated]]
	virtual bool GetMultiplexerEnable(int iCycle, int iApertureSize, DWORD *pdwApertureEmission, DWORD *pdwApertureReception);
	//[[deprecated]]
	virtual bool CheckMultiplexerAperture(int iEltCntEmission, int iEltCntReception, int *piEltListEmission, int *piEltListReception);//to check that emission and reception apertures are coherent.
	//[[deprecated]]
	virtual bool SetMultiplexerEnable(int iCycle, int iElementCount, int *piElementList);

	/*!
	 * \brief Enable negative pulse channels.
	 * \param[in] iCycle: cycle number for which to set bipolar settings.
	 * \param[in] iChannelCount: number of elements in the array 'piChannelList'.
	 * \param[in] piChannelList: list of channels for which to enable negative pulse.
	 */
	virtual bool SetEmissionEnable(int iCycle, int iChannelCount, int *piChannelList);

	/*!
	 * \brief Get enabled negative pulses.
	 * Return the list of enabled negative channels for a given cycle.
	 * \param[in] iCycle: cycle number for which to get bipolar pulses.
	 * \param[in] iChannelCountMax: size of the array 'piChannelList'.
	 * \param[out] piChannelCount: optionnal, pointer to hold the number of elements enabled (and put in 'piChannelList').
	 * \param[out] piChannelList: pointer to an array that will be filled with enabled channels.
	*/
	virtual bool GetEmissionEnable(int iCycle, int iChannelCountMax, int *piChannelCount, int *piChannelList);
	virtual bool GetEmissionEnable(int iCycle, int iChannelCountMax, structCallbackArrayInt1D& callbackArrayInt1D);

	/*!
	 * \brief Get enabled negative pulses.
	 * Return the enabled negative channels for a given cycle in a 'bitfield' form, one bit per channel.
	 * \param[in] iCycle: cycle number for which to get bipolar pulses.
	 * \param[in] iArraySize: size of the array 'pdwAperture'.
	 * \param[out] piChannelCount: optionnal, pointer to hold the number of elements enabled.
	 * \param[out] pdwAperture: pointer to a DWORD array in which bits representing enabled channels will be set to 1.
	*/
	virtual bool GetEmissionEnable(int iCycle, int iArraySize, int *piChannelCount, DWORD *pdwAperture);	// To have elem count and aperture in a single call, for medium level.

	/*!
	 * Disable negative pulsers for a given cycle,
	 * same effect than SetEmissionEnable(cycle, 0, nullptr).
	 */
	virtual bool DisableEmission(int iCycle);
	/*!
	 * \brief Enable receiver channels.
	 * \param[in] iCycle: cycle number for which to set receiver channels.
	 * \param[in] iChannelCount: number of elements in the array 'piChannelList'.
	 * \param[in] piChannelList: list of channels to set as receivers.
	 */
	virtual bool SetReceptionEnable(int iCycle, int iChannelCount, int *piChannelList);
	/*!
	 * \brief Get enabled receiver channels.
	 * \param[in] iCycle: cycle number for which to get receive channels.
	 * \param[in] iChannelCountMax: size of the array 'piChannelList'.
	 * \param[out] piChannelCount: optionnal, pointer to hold the number of elements enabled (and put in 'piChannelList').
	 * \param[out] piChannelList: pointer to an array that will be filled with enabled receiver channels.
	*/
	virtual bool GetReceptionEnable(int iCycle, int iChannelCountMax, int *piChannelCount, int *piChannelList);
	virtual bool GetReceptionEnable(int iCycle, int iChannelCountMax, structCallbackArrayInt1D& callbackArrayInt1D);

	/*!
	 * \brief Enable bipolar pulses and set bipolar settings for enabled channels.
	 *
	 * Enable bipolar pulses for a given set of channels.
	 * 'piPulseCountList', 'pfPulseWidthList', 'pfPulsePeriodList' can be NULL to only enable/disable channels.
	 * Enabling a bipolar channel without setting the pulse width, count and period will result in undefined behavior.
	 * WARNING: This function will set the setting 'pulse delay' to zero.
	 * If you want to have a non zero delay, please use bool SetEmissionBipolarDelay(int iCycle, int iChannel, float &fPulseDelay) after this one,
	 * or bool SetEmissionEnableBipolar(int iCycle, int iChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList, float *pfPulseDelayList).
	 *
	 * \param[in] iCycle: cycle number for which to enable bipolar pulses.
	 * \param[in] iChannelCount: number of channels to enable in the array 'piChannelList'.
	 * \param[in] piChannelList: pointer to an array of channel to enable bipolar pulse.
	 * \param[in] iPulseCount: optionnal, number of pulses.
	 * \param[in] fPulseWidth: optionnal, width of a pulse in second.
	 * \param[in] fPulsePeriod: optionnal, period duration in second.
	 */
	virtual bool SetEmissionEnableBipolar(int iCycle, int iChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList);
	virtual bool SetEmissionEnableBipolar(int iCycle, int iChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList, float *pfPulseDelayList);

	/*!
	 * \brief Get enabled bipolar pulses and bipolar settings.
	 * \param[in] iCycle: cycle number for which to get bipolar pulses.
	 * \param[in] iArraySize: size of the array 'piChannelList'.
	 * \param[out] piCount: optionnal, pointer to hold the number of elements enabled (and put in 'piChannelList').
	 * \param[out] piChannelList: pointer to an array that will be filled with enabled elements.
	 * \param[out] iPulseCount: optionnal, pointer to an array that will be filled with numbers of pulses.
	 * \param[out] fPulseWidth: optionnal, pointer to an array that will be filled with pulses widths (second).
	 * \param[out] fPulsePeriod: optionnal, pointer to an array that will be filled with periods durations (second).
	*/
	virtual bool GetEmissionEnableBipolar(int iCycle, int iArraySize, int *piChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList);
	virtual bool GetEmissionEnableBipolar(int iCycle, int iArraySize, int *piChannelCount, int *piChannelList, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList, float *pfPulseDelayList);

	/*!
	 * \brief Get enabled bipolar pulses and bipolar settings.
	 *
	 * Return the enabled negative channels for a given cycle in a 'bitfield' form, one bit per channel.
	 *
	 * \param[in] iCycle: cycle number for which to get bipolar pulses.
	 * \param[in] iChannelCountMax: size of the arrays 'piPulseCountList', 'pfPulseWidthList' and 'pfPulsePeriodList'.
	 * \param[out] piCount: optionnal, pointer to hold the number of elements enabled.
	 * \param[out] pdwAperture: pointer to an 'aperture' (single DWORD) that will be filled with enabled elements.
	 * \param[out] iPulseCount: optionnal, pointer to an array that will be filled with numbers of pulses.
	 * \param[out] fPulseWidth: optionnal, pointer to an array that will be filled with pulses widths (second).
	 * \param[out] fPulsePeriod: optionnal, pointer to an array that will be filled with periods durations (second).
	*/
	virtual bool GetEmissionEnableBipolar(int iCycle, int iChannelCountMax, int *piChannelCount, DWORD *pdwAperture, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList);
	virtual bool GetEmissionEnableBipolar(int iCycle, int iChannelCountMax, int *piChannelCount, DWORD *pdwAperture, int *piPulseCountList, float *pfPulseWidthList, float *pfPulsePeriodList, float *pfPulseDelayList);

	// Wrappers "old style", probably better to remove them if not used in driver code (or medium level).
	virtual bool SetEmissionEnableBipolar(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);
	virtual bool GetEmissionEnableBipolar(int iCycle, DWORD adwHWAperture[g_iOEMPAApertureDWordCount]);

	/*!
	 * \brief Enable bipolar pulses.
	 * Enable bipolar pulses for a given set of channels. 
	 * Enabling a bipolar channel without setting the pulse width, count and period will result in undefined behavior.
	 * Use SetEmissionBipolarPulse() to set pulse width, count and period.
	 * \param[in] iCycle: cycle number for which to enable bipolar pulses.
	 * \param[in] iChannelCount: number of channels to enable in the array 'piChannelList'.
	 * \param[in] piChannelList: pointer to an array of channel to enable bipolar pulse.
	 */
	virtual bool SetEmissionEnableBipolar(int iCycle, int iChannelCount, int *piChannelList);

	/*!
	 * \brief Get enabled bipolar pulses.
	 * Return the list of enabled bipolar channels for a given cycle.
	 * To also retrieve the bipolar settings (pulse width, count and period), use GetEmissionBipolarPulse().
	 * \param[in] iCycle: cycle number for which to get bipolar pulses.
	 * \param[in] iArraySize: size of the array 'piChannelList'.
	 * \param[out] piCount: optionnal, pointer to hold the number of elements enabled (and put in 'piChannelList').
	 * \param[out] piChannelList: pointer to an array that will be filled with enabled elements.
	*/
	virtual bool GetEmissionEnableBipolar(int iCycle, int iArraySize, int *piCount, int *piChannelList);

	/*!
	 * Disable bipolar pulsers for MC2 for a given cycle, 
	 * same effect than SetEmissionEnableBipolar(cycle, 0, nullptr, nullptr, nullptr, nullptr).
	 */
	virtual bool DisableEmissionBipolar(int iCycle);

	/*!
	 * \brief Set bipolar settings.
	 *
	 * Won't enable or disable the channel for pulse, only for settings (pulse width, count and period). 
	 * Use SetEmissionEnableBipolar() to enable channels.
	 * WARNING: This function will set the setting 'pulse delay' to zero.
	 * If you want to have a non zero delay, please use bool SetEmissionBipolarDelay(int iCycle, int iChannel, float &fPulseDelay) after this one,
	 * or bool SetEmissionBipolarPulse(int iCycle, int iChannel, int &iPulseCount, float &fPulseWidth, float &fPulsePeriod, float &fPulseDelay)
	 *
	 * \param[in] iCycle: cycle number for which to set bipolar settings.
	 * \param[in] iChannel: channel number for which to set bipolar settings.
	 * \param[in,out] iPulseCount: number of pulses.
	 * \param[in,out] fPulseWidth: width of a pulse in second.
	 * \param[in,out] fPulsePeriod: period duration in second.
	 */
	virtual bool SetEmissionBipolarPulse(int iCycle, int iChannel, int &iPulseCount, float &fPulseWidth, float &fPulsePeriod);

	/*!
	 * \brief Get bipolar settings.
	 * \param[in] iCycle: cycle number for which to get bipolar settings.
	 * \param[in] iChannel: channel number for which to get bipolar settings.
	 * \param[out] iPulseCount: number of pulses.
	 * \param[out] fPulseWidth: width of a pulse in second.
	 * \param[out] fPulsePeriod: period duration in second.
	 */
	virtual bool GetEmissionBipolarPulse(int iCycle, int iChannel, int *iPulseCount, float *fPulseWidth, float *fPulsePeriod);

	virtual bool SetEmissionBipolarPulse(int iCycle, int iChannel, int &iPulseCount, float &fPulseWidth, float &fPulsePeriod, float &fPulseDelay);
	virtual bool GetEmissionBipolarPulse(int iCycle, int iChannel, int *iPulseCount, float *fPulseWidth, float *fPulsePeriod, float *pfPulseDelay);

	virtual bool SetEmissionBipolarDelay(int iCycle, int iChannel, float &fPulseDelay);
	virtual bool GetEmissionBipolarDelay(int iCycle, int iChannel, float *pfPulseDelay);

	/*!
	 * \brief Enable single receive channel.
	 * \param[in] iCycle: cycle number for which to enable receiver channel.
	 * \param[in] iChannel: Channel to enable/disable for this cycle.
	 * \param[in] bEnable: Enable (true) or disable (false) the inputted channel.
	 */
	virtual bool SetReceptionEnable(int iCycle, int iChannel, bool bEnable);

	/*!
	 * \brief Get the state of a single receive channel.
	 * \param[in] iCycle: cycle number for which to get the receive channel state.
	 * \param[in] iChannel: Channel to get the state.
	 * \param[out] bEnable: state of the channel.
	 */
	virtual bool GetReceptionEnable(int iCycle, int iChannel, bool *bEnable);

	/*!
	 * \brief Enable single negative pulse channel.
	 * \param[in] iCycle: cycle number for which to enable negative pulse channel.
	 * \param[in] iChannel: Channel to enable/disable for this cycle.
	 * \param[in] bEnable: Enable (true) or disable (false) the inputted channel.
	 */
	virtual bool SetEmissionEnable(int iCycle, int iChannel, bool bEnable);

	/*!
	 * \brief Get the state of a single negative pulse channel.
	 * \param[in] iCycle: cycle number for which to get the negative pulse channel state.
	 * \param[in] iChannel: Channel to get the state.
	 * \param[out] bEnable: state of the channel.
	 */
	virtual bool GetEmissionEnable(int iCycle, int iChannel, bool *bEnable);

	/*!
	 * \brief Enable single bipolar pulse channel.
	 * \param[in] iCycle: cycle number for which to enable bipolar pulse channel.
	 * \param[in] iChannel: Channel to enable/disable for this cycle.
	 * \param[in] bEnable: Enable (true) or disable (false) the inputted channel.
	 */
	virtual bool SetEmissionEnableBipolar(int iCycle, int iChannel, bool bEnable);

	/*!
	 * \brief Get the state of a single bipolar pulse channel.
	 * \param[in] iCycle: cycle number for which to get the bipolar pulse channel state.
	 * \param[in] iChannel: Channel to get the state.
	 * \param[out] bEnable: state of the channel.
	 */
	virtual bool GetEmissionEnableBipolar(int iCycle, int iChannel, bool *bEnable);

	bool GetEnableAWG(bool *pbEnable);
	bool EnableAWG(bool &enable);
	bool SetEmissionEnableAWG(int iCycle, int iChannelCount, int *piChannelList);
	bool GetEmissionEnableAWG(int iCycle, int iArraySize, int *piCount, int *piChannelList);
	bool SetEmissionEnableAWG(int iCycle, int iChannelCount, int *piChannelList, int *piShapeIndexList, float *pfTimeResolutionList, float *pfPulseDelayList);
	bool SetEmissionAWGIndexAndDelay(int iCycle, int iChannel, int &iIndex, float &fTimeResolution, float &fPulseDelay);
	bool SetEmissionAWGIndex(int iCycle, int iChannel, int &iIndex, float &fTimeResolution);
	bool GetEmissionAWGIndex(int iCycle, int iChannel, int *piIndex, float *pfTimeResolution);
	bool SetEmissionAWGDelay(int iCycle, int iChannel, float &fPulseDelay);
	bool GetEmissionAWGDelay(int iCycle, int iChannel, float *pfPulseDelay);

	// Wizard functions for predefined waveforms.
	// Fs: Sampling Frequency of the AWG signal, typically Fs = 10 * F0 for burst, unipolar and bipolar. For Chirp and gaussian, duration = Nt * Fs.
	// Nt: Number of states for the AWG shape. Typically Nt = Fs / F0 * Nper for burst, unipolar and bipolar. For Chirp and gaussian, duration = Nt * Fs.
	// F0: MHZ, central probe frequency.
	// Nper: number of cycles for burst and bipolar.
	// phi: can be left to 0.
	// upSampK:
	// double duration = (Nt - 1) / Fs;
	//if (burst || bipolar)
	//		duration = Nper / F0;
	//if (unipolar)
	//		duration = 1 / F0;
	//double T03s = duration / 1024;	// timeResolution (us).
	//int T03sInt = (int)ceil(T03s * 1e3);
	//if (T03sInt == 0)
	//	T03sInt = 5;	// minimum value is 5ns.
	//while (T03sInt % 5)
	//	++T03sInt;		// must be a multiple of 5ns (step).
	//T03s = T03sInt * 1e-3;	// convert back to us.
	//upSampK = 1 / (Fs * T03s);
	// pulseDurationMin: should be 0.01
	// ampMin: minium amplitude of the signal to be digitized. Typically 0.1
	// index: the MC2 can store up to 16 different AWG shapes that can then be associated to a channel and a cycle (see the SetEmissionAWGIndex function above).
	bool GenerateAWGBurstMC2(double Fs, int Nt, double F0, int Nper, double phi, double upSampK, double pulseDurationMin, double ampMin, int index = 0);
	bool GenerateAWGChirpMC2(double Fs, int Nt, double F1, double F2, double phi, double upSampK, double pulseDurationMin, double ampMin, int index = 0);
	bool GenerateAWGGaussMC2(double Fs, int Nt, double F0, double BWR, double phi, double upSampK, double pulseDurationMin, double ampMin, int index = 0);
	bool GenerateAWGUnipolarMC2(double Fs, int Nt, double F0, double upSampK, double pulseDurationMin, double ampMin, int index = 0);
	bool GenerateAWGBipolarMC2(double Fs, int Nt, double F0, int Nper, double dutyCycle, double upSampK, double pulseDurationMin, double ampMin, int index = 0);

	bool GenerateAWGBurstMC2(double Fs, int Nt, double F0, int Nper, double phi, double upSampK, double pulseDurationMin, double ampMin, float& fOutTimeResolution, int index = 0);
	bool GenerateAWGChirpMC2(double Fs, int Nt, double F1, double F2, double phi, double upSampK, double pulseDurationMin, double ampMin, float& fOutTimeResolution, int index = 0);
	bool GenerateAWGGaussMC2(double Fs, int Nt, double F0, double BWR, double phi, double upSampK, double pulseDurationMin, double ampMin, float& fOutTimeResolution, int index = 0);
	bool GenerateAWGUnipolarMC2(double Fs, int Nt, double F0, double upSampK, double pulseDurationMin, double ampMin, float& fOutTimeResolution, int index = 0);
	bool GenerateAWGBipolarMC2(double& Fs, int& Nt, double& F0, int Nper, double dutyCycle, double& upSampK, double pulseDurationMin, double ampMin, float& fOutTimeResolution, int index = 0);
	
	// Custom waveforms.
	/*
		output buffer must be at least nbPoint x upSampK long.
	*/
	bool GenerateAWGCustomMC2(double *pointList, int nbPoint, double Fs, double upSampK, double pulseDurationMin, double ampMin, int index = -1);
public:

public:

	virtual bool SetEmissionDelay(int iCycle, int iChannel, float &fDelay);
	virtual bool GetEmissionDelay(int iCycle, int iChannel, float *pfDelay);
	virtual bool SetEmissionDelays(int iCycle, int iChannelCount, int *piChannelList, float *pfDelay);
	virtual bool GetEmissionDelays(int iCycle, int &iChannelCountMax, int *piChannelCount, float *pfDelay);
	virtual bool SetEmissionDelays(int iCycle, int iChannelCount, int *piChannelList, structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	virtual bool GetEmissionDelays(int iCycle, int &iChannelCountMax, structCallbackArrayFloat1D &callbackArrayFloat1D);//Size = element size.
	virtual bool SetEmissionWidth(int iCycle, int iChannel, float &fWidth);
	virtual bool GetEmissionWidth(int iCycle, int iChannel, float *pfWidth);
	virtual bool SetEmissionWidths(int iCycle, int iChannelCount, int *piChannelList, float *pfWidth);
	virtual bool GetEmissionWidths(int iCycle, int &iChannelCountMax, int *piChannelCount, float *pfWidth);
	//[[deprecated]]
	virtual bool SetEmissionWidths(int iCycle, int iChannelCount, int *piChannelList, structCallbackArrayFloat1D &callbackArrayFloat1D);
	//[[deprecated]]
	virtual bool GetEmissionWidths(int iCycle, int &iChannelCountMax, structCallbackArrayFloat1D &callbackArrayFloat1D);
	//[[deprecated]]
	virtual bool SetReceptionGains(int iCycle, int iElementCount, int *piElementList, float *pfGain);
	//[[deprecated]]
	virtual bool GetReceptionGains(int iCycle, int &iElementCountMax, int *piElementCount, float *pfGain);
	//[[deprecated]]
	virtual bool SetReceptionGains(int iCycle, int iElementCount, int *piElementList, structCallbackArrayFloat1D &callbackArrayFloat1D);
	//[[deprecated]]
	virtual bool GetReceptionGains(int iCycle, int &iElementCountMax, structCallbackArrayFloat1D &callbackArrayFloat1D);
	//[[deprecated]]
	virtual bool SetReceptionDelays(int iCycle, int &iFocalCount, int iElementCount, int *piElementList, float *pfDelay);
	//[[deprecated]]
	virtual bool GetReceptionDelays(int iCycle, int iLineSize, int &iElementCountMax, int &iFocalCountMax, int *piElementCount, int *piFocalCount, float *pfDelay);
	//[[deprecated]]
	virtual bool SetReceptionDelays(int iCycle, int iElementCount, int *piElementList, structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.
	//[[deprecated]]
	virtual bool GetReceptionDelays(int iCycle, int &iElementCountMax, int &iFocalCountMax, structCallbackArrayFloat2D &callbackArrayFloat2D);//Size1 = element size, Size2 = DDF size.

	//[[deprecated]]
	virtual bool SetReceptionFocusing(int iCycle, int &iFocalCount, double *pdFocalTof);
	//[[deprecated]]
	virtual bool GetReceptionFocusing(int iCycle, int &iFocalCountMax, int *piFocalCount, double *pdFocalTof);
	//[[deprecated]]
	virtual bool SetReceptionFocusing(int iCycle, structCallbackArrayDouble1D &callbackArrayDouble1D);
	//[[deprecated]]
	virtual bool GetReceptionFocusing(int iCycle, int &iFocalCountMax, structCallbackArrayDouble1D &callbackArrayDouble1D);
	//[[deprecated]]
	virtual bool SetReceptionFocusing(int iCycle, int &iFocalCount, double *pdFocalTof, float &fCenterDelayE, float &fCenterDelayR);
	//[[deprecated]]
	virtual bool GetReceptionFocusing(int iCycle, int &iFocalCountMax, int *piFocalCount, double *pdFocalTof, float *pfCenterDelayE, float *pfCenterDelayR);
	//[[deprecated]]
	virtual bool SetReceptionFocusing(int iCycle, structCallbackArrayDouble1D &callbackArrayDouble1D, float &fCenterDelayE, float &fCenterDelayR);
	//[[deprecated]]
	virtual bool GetReceptionFocusing(int iCycle, int &iFocalCountMax, structCallbackArrayDouble1D &callbackArrayDouble1D, float *pfCenterDelayE, float *pfCenterDelayR);
	//[[deprecated]]
	virtual bool GetReceptionNormalisationDelayAv(bool bEmission, int iElementCount, int *piElementList, float &fDelay);
	//[[deprecated]]
	virtual bool EnableDDF(int iCycle, bool bEnable);
	virtual bool GetEnableDDF(int iCycle, bool *pbEnable);
	//[[deprecated]]
	virtual bool EnableDDF(int iCycle, enumFocusing &eFocusing);
	virtual bool GetEnableDDF(int iCycle, enumFocusing *peFocusing);

	//[[deprecated]]
	virtual bool CheckFocalTimeOfFlight(double &dDelay);
	//[[deprecated]]
	virtual bool CheckReceptionGain(float &fGain);
	//[[deprecated]]
	virtual bool CheckReceptionDelay(float &fDelay);
	virtual bool CheckEmissionWidth(float &fWidth);
	virtual bool CheckEmissionDelay(float &fDelay);
	virtual DWORD GetSWBaseAddress();
public:

public:
	//[[deprecated]]
	virtual bool EnableMultiHWChannelAcquisition(int iCycle, int iCycleCount, bool bEnable);
	//[[deprecated]]
	virtual bool GetEnableMultiHWChannelAcquisition(int iCycle, bool *pbEnable);
	//[[deprecated]]
	virtual bool SetMultiHWChannelAcqDecimation(int iCycle, unionOEMMCDecimation &hwAcqDecimation);
	//[[deprecated]]
	virtual bool GetMultiHWChannelAcqDecimation(int iCycle, unionOEMMCDecimation *hwAcqDecimation);
	//[[deprecated]]
	virtual bool GetMultiHWChannelAcqDecimation(int iCycle, structCallbackArrayByte1D &callbackArrayByte1D);
	//[[deprecated]]
	virtual bool SetMultiHWChannelAcqWriteStart(int iCycle, int iAcqElement, int iStartCount, float *pfStart);
	//[[deprecated]]
	virtual bool GetMultiHWChannelAcqWriteStart(int iCycle, int &iStartCountMax, int *piStartCount, float *pfStart);
	//[[deprecated]]
	virtual bool SetMultiHWChannelAcqWriteStart(int iCycle, int iAcqElement, int iStartCount, structCallbackArrayFloat1D &callbackArrayFloat1D);//Size1 = element size.
	//[[deprecated]]
	virtual bool GetMultiHWChannelAcqWriteStart(int iCycle, int &iStartCountMax, structCallbackArrayFloat1D &callbackArrayFloat1D);//Size1 = element size.
	//[[deprecated]]
	virtual double GetMultiHWChannelRangeMax();//unit us.

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

	virtual void vf_WaitForClassSend();
	virtual bool TestFWMemoryCycle(int iCycleCount, DWORD dwData);
	virtual bool TestFWMemoryFilter(int iFilterCount, DWORD dwData);

	virtual bool EnablePowerDown(bool bEnable);
	virtual bool GetEnablePowerDown(bool *bEnable);
public:

public:
	//<<PARAMETERS MANAGEMENT FUNCTIONS : END>>

public://don't use following functions
	virtual bool vf_GetStringId(wchar_t *stringId, int iSize);
	virtual bool vf_UpdateEncoder(int iEncoder);//1.1.5.4w
	virtual bool vf_UpdateFilter(int iFilter);//1.1.5.4w
	virtual bool vf_FreeDigitalInput(enumFeatureDigitalInput eIndexDigitalInputNew);//1.1.5.4w
	virtual bool vf_PreEnablePulser(bool bEnable);
	virtual bool vf_SetCommunication(enumCommunication eCommunication);
	virtual bool vf_LoadCfgFile();
	virtual bool vf_ReLoadCfgFile();
	virtual bool vf_SetStandby(bool bLockOrUnlock, enumAcquisitionState &eAcqState);
	virtual bool vf_SetStandbyNoFlush(bool standby);
	virtual bool vf_PostSetStandby(bool bLockOrUnlock, enumAcquisitionState &eAcqState);
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
	static bool sIsPowerDownEnabled();
	static void sEnablePowerDown(bool bEnable);
	bool IsFullDynamicEnabled();
	// enable20dBAttenuator: only if 'bEnable' == false, will enable/disable the 20dB attenuator in the same call.
	bool EnableFullDynamic(bool bEnable, bool enable20dBAttenuator = true);
	bool Is20dBAttenuiatorEnabled();
	bool Enable20dBAttenuator(bool bEnable);

private:
public:
	virtual bool vf_AddressMapping(bool bSWToHW, DWORD dwAddressIn, DWORD &dwAddressOut);

private:
public:
	bool IsGainCorrectionTableEnabled();

public://DO NOT CALL FOLLOWING RESERVED FUNCTIONS
public:
	virtual void* ProcessSWGate(void *_pDrvCom, void *pAcquisitionParameter, const CStream_0x0002 *pStreamHeader, const CSubStreamAscan_0x0203 *pSubStreamAscan_0x0203, const void *pBufferMax, const void *pBufferMin, const void *pBufferSat);
	virtual bool ProcessIOAscan(int iDevice, void *pAcquisitionParameter, pTypeAcquisitionAscan_0x00010103 pAcquisitionAscan_0x00010103, LONG &lLastAscanIndex);
	virtual bool ProcessIOCscan(int iDevice, void *pAcquisitionParameter, pTypeAcquisitionCscan_0x00010X02 pAcquisitionCscan_0x00010X02, LONG &lLastCscanIndex);
	virtual bool ProcessIOAscanCscan(int iDevice, void* pAcquisitionParameter, LONG& lLastCscanIndex, LONG& lLastAscanIndex);
	virtual bool swIsFMCCycleDependent() const;
	virtual bool vf_OnMasterConnected(int iMasterDigitalExternalSequence, int iMasterDigitalExternalCycle, int iSlaveDigitalExternalSequence, int iSlaveDigitalExternalCycle);
	virtual bool vf_OnSlaveConnected(int iMasterDigitalExternalSequence, int iMasterDigitalExternalCycle, int iSlaveDigitalExternalSequence, int iSlaveDigitalExternalCycle);
	virtual bool vf_OnSlaveDisconnected(bool bPostProcess);
	virtual bool vf_SWReset();
	virtual bool vf_GetSockBufferSize(int &iSizeSend, int &iSizeReceive);
	virtual bool vf_LockDevice(enumAcquisitionState &eAcqState);
	virtual bool vf_RouteLockDevice(enumAcquisitionState eAcqState);
	virtual bool vf_UnlockDevice(enumAcquisitionState eAcqStateIn, int iCheckConsistancy, enumAcquisitionState &eAcqState);
	virtual bool vf_FlushDevice();
	virtual bool vf_ResetSequence();
	virtual bool vf_SetTimeStamp(int iValue);//0=restart,1=reset,2=stop on next standby.
	virtual bool vf_SetTimeStamp(ULONGLONG &ullTimeStamp);
	virtual bool vf_GetTimeStamp(ULONGLONG *pullTimeHW);
	virtual bool vf_CheckGateIndex(int &iGate);
	virtual bool EnablePulser(bool bShot);
	virtual bool GetEnablePulser(bool *pbShot);//ask hw as for others functions.
	virtual bool EnablePulser(bool bShot, bool bDisableCallback);
	virtual bool GetFWId();
	virtual bool SetFWOptionsMask(const wchar_t *pPasscode, CUTDevCommunication *pDevCom = NULL);
	virtual void ResetFWOptions();
	virtual int GetFlashSWSectionSize();
	virtual bool GetFlashSWSection(char *pBuffer, int iSize);
	virtual int swGetApertureCountMax() const;//to get the maximum element count of an aperture (SW function, the HW does not send answer).
	virtual int swGetElementCountMax() const;//to get the maximum element count of the system (SW function, the HW does not send answer).
	virtual int swGetCycleCountMax();
	virtual bool SetHardwareLink(enumHardwareLink &eHardwareLink, int iDigitalExternalSequence, int iDigitalExternalCycle);
	virtual bool GetHardwareLink(enumHardwareLink *peHardwareLink, int *piDigitalExternalSequence, int *piDigitalExternalCycle);
	virtual bool swIsFullMatrixCapture() const;
	virtual bool SetFilterScale(enumOEMPAFilterIndex eFilterIndex, WORD &wScale);
	virtual bool SetFilterCoefficient(enumOEMPAFilterIndex eFilterIndex, int iIndex, short &wValue);
	virtual bool GetFilterScale(enumOEMPAFilterIndex eFilterIndex, WORD *pwScale);
	virtual bool GetFilterCoefficient(enumOEMPAFilterIndex eFilterIndex, int iIndex, short *pwValue);
	virtual bool SetDAC(int iCycle, int &iCount, double *pdTime, float *pfPrm, structCallbackArrayFloatDac *pCallbackArray, int iStringErrorSize, wchar_t *pStringError);//safe : check between the different points of the DAC is peformed.
	virtual bool SetDAC(int iCycle, int &iCount, double *pdTime, float *pfPrm, float fAnalogGain, int iCountVGA, double *pdTimeVGA, float *pfGainVGA, structCallbackArrayFloatDac *pCallbackArray, int iStringErrorSize, wchar_t *pStringError);//safe : check between the different points of the DAC is peformed.
	virtual bool GetDAC(bool bSlope, int iCycle, int &iCountMax, int *piCount, double *pdTime, float *pfPrm, structCallbackArrayFloatDac *pCallbackArray);
	virtual bool GetDAC(bool bSlope, int iCycle, int &iCountMax, int *piCount, double *pdTime, float *pfPrm, int *piCountVGA, double *pdTimeVGA, float *pfGainVGA, structCallbackArrayFloatDac *pCallbackArray);
	virtual bool SetDAC(int iCycle, int iChannel, int &iCount, double *pdTime, float *pfPrm, structCallbackArrayFloatDac *pCallbackArray, int iStringErrorSize, wchar_t *pStringError);//safe : check between the different points of the DAC is peformed.
	virtual bool GetDAC(bool bSlope, int iCycle, int iChannel, int &iCountMax, int *piCount, double *pdTime, float *pfPrm, structCallbackArrayFloatDac *pCallbackArray);
	virtual bool vf_CheckSetupTime(structNotificationOption &optionNotification, bool bCheckValue, int iCycle, enumCheckSetupTime eType, void* val, LONG *lPoint);
	virtual bool vf_CheckSetupTime(structNotificationOption& optionNotification, bool bCheckValue, int iCycle, int iChannel, enumCheckSetupTime eType, void* val, LONG* lPoint);
	virtual bool SetRequestCscan(enumOEMPARequestCscan &eRequest);
	virtual bool GetRequestCscan(enumOEMPARequestCscan *peRequest);
#ifndef OEMMC_MB_MEMORY_DDR3_BASE_ADDR
#endif // OEMPAMINIMAX_MB_MEMORY_DDR3_BASE_ADDR

public:
};

#ifndef DRIVER_OEMMC2_API
#define DRIVER_OEMMC2_API
using CSWDeviceOEMMC2 = CSWDeviceOEMMC;
class DRIVER_OEMMC_API_ALIGN CHWDeviceOEMMC2 : public CHWDeviceOEMMC
{
public:
	CHWDeviceOEMMC2();
};
#endif //DRIVER_OEMMC2_API

#ifndef DRIVER_OEMMCU_API
#define DRIVER_OEMMCU_API
using CSWDeviceOEMMCu = CSWDeviceOEMMC;
class DRIVER_OEMMC_API_ALIGN CHWDeviceOEMMCu : public CHWDeviceOEMMC
{
public:
	CHWDeviceOEMMCu();
};
#endif //DRIVER_OEMMCU_API

#ifndef DRIVER_OEMMCUF_API
#define DRIVER_OEMMCUF_API
using CSWDeviceOEMMCuF = CSWDeviceOEMMC;
class DRIVER_OEMMC_API_ALIGN CHWDeviceOEMMCuF : public CHWDeviceOEMMC
{
public:
	CHWDeviceOEMMCuF();
};
#endif //DRIVER_OEMMCUF_API
