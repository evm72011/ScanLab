
#pragma once

#include "UTBasicType.h"
#include "UTBasicEnum.h"
#include "UTKernelBasic.h"

#pragma comment(lib,"UTDriverOEMPA.lib")

UTKERNEL_API bool UTKernel_WizardNew(const wchar_t *pName,int &iRootWizardSystemId,int &iRootChannelId);
UTKERNEL_API bool UTKernel_WizardLoad(const wchar_t *pFile,int &iRootWizardSystemId,int &iRootChannelId);
UTKERNEL_API bool UTKernel_WizardSave(int iRootWizardSystemId,int iRootChannelId,const wchar_t *pFile);
UTKERNEL_API bool UTKernel_TextFileSave(int iRootObjectId,enumRootType eObjectType,const wchar_t *pFile);//should not be used if the object have a link with another one, in this case it will be impossible to reload it.
UTKERNEL_API bool UTKernel_FileSave(bool bBinaryFile,int iSize,int *aiRootObjectId,enumRootType *aeObjectType,const wchar_t *pFile);
UTKERNEL_API bool UTKernel_FileLoadText(bool bLoadDisplay,int iObjectCount,int *aiRootObjectId,enumRootType *aeObjectType,wchar_t *pVersionRename,const wchar_t *pFile,int iKernelLanguageIndex,int iFileRootNameIndex,bool bEnableCheck);
UTKERNEL_API int UTKernel_FileLoadBuffer(int iSizeBuffer,char *pBuffer,int iSizeName,wchar_t *pObjectNameList,int iObjectCount,int *aiRootObjectIndex,enumRootType *paeObjectType);
UTKERNEL_API bool UTKernel_FileLoadBuffer(bool bLoadDisplay,int iObjectCount,int *aiRootObjectIndex,enumRootType *aeObjectType,wchar_t *pVersionRename,int iSizeBuffer,char *pBuffer);
UTKERNEL_API bool UTKernel_WizardDelete(int iRootWizardSystemId,int iRootChannelId);
UTKERNEL_API bool UTKernel_WizardUpdate(int iRootWizardSystemId);
UTKERNEL_API bool UTKernel_TextFileSave(int iRootId,const wchar_t *pFile);
//see also the class "CUTKernelFile" to load/save kernel objects.

//private functions
bool UTKernel_TextFileLoad(wchar_t *pFile,int &iRootObjectId,enumRootType &eRootType);
bool UTKernel_LinkWizardSystemAndMonoChannel(int iRootWizardSystemId,int iRootChannelId,int iWizardProbeIndex=0);

#include "UTKernelData.h"
#include "UTKernelRoot.h"
#include "UTKernelAcquisition.h"

#include "UTKernelWizard.h"
#include "UTKernelFile.h"

UTKERNEL_API bool UTKernel_RegisterCallback(pCallbackFunction pFunc,wchar_t *pCallbackComment,enumEvent eEvent,void *pInputParameter,LARGE_INTEGER llInputParameter,LARGE_INTEGER &llCallbackID);
	//this function can be used only with "eEventNew" and "eEventDelete".
UTKERNEL_API bool UTKernel_UnregisterCallback(LARGE_INTEGER &llCallbackID);
UTKERNEL_API LRESULT UTKernel_Callback(enumEvent eEvent,const wchar_t *pPath,int iRootID);

///////////////////////////////////////////////////////////////////////////////////////
// HEADER KERNEL
///////////////////////////////////////////////////////////////////////////////////////
#pragma warning( disable : 4584 )

class CUTWizardFocalLaw;
class CUTPulser;
class CUTGate;
class CUTEncoder;

class UTKERNEL_API_ALIGN _CUTFocalLaw
{
private:
	ULONGLONG m_ullPrivateMemory[597];
protected:

};

class UTKERNEL_API_ALIGN CUTFocalLaw :
	/*virtual*/ public CUTBaseClass,
	public _CUTFocalLaw
{
public:
private:
protected:

public:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTFocalLaw();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTFocalLaw(const CUTFocalLaw &a);
	~CUTFocalLaw();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	int operator=(const CUTFocalLaw &a);
	int WizardUpdate(const CUTWizardFocalLaw &a,const CUTWizardProbe &probe);
	bool operator==(const CUTFocalLaw &a);
	bool operator!=(const CUTFocalLaw &a);

	int SetFocusing(enumFocusing eValue);
	enumFocusing GetFocusing() const;

	int SetFirst(int iIndex);
	int GetFirst() const;

	int SetWedgeDelay(double dValue);//for wedge delay be careful : the center delay is not taken into account!
	double GetWedgeDelay() const;

	int SetSkew(double dValue);
	double GetSkew() const;

	int SetAngle(double dValue);
	double GetAngle() const;

	int SetTofMax(double dValue);//maybe not usefull ! because the center delay is given TimeOfFlight.
	double GetTofMax() const;

	int SetEmergence(double dX,double dY,double dZ);
	void GetEmergence(double &dX,double &dY,double &dZ) const;

	int SetFocal(double dX,double dY,double dZ);
	void GetFocal(double &dX,double &dY,double &dZ) const;

	virtual int vf_SetCount(int iElementCount);//see CUTAcquisitionFocalLaw
	virtual int vf_SetFocalLawCount(int iElementCount,int iFocalLawCount);//virtual because of CUTAcquisitionFocalLaw

public:
	int SetCount(int iElementCount);//see CUTAcquisitionFocalLaw
	int SetFocalLawCount(int iElementCount,int iFocalLawCount);
	int GetCount() const;
	int GetFocalLawCount() const;

	int SetDelay(int iElemIndex,float fDelay);//standard focal law.
	int GetDelay(int iElemIndex,float &fDelay) const;//standard focal law.
	int SetDelay(int iElemIndex,int iFocalLawIndex,float fDelay);
	int GetDelay(int iElemIndex,int iFocalLawIndex,float &fDelay) const;
	int SetArrayDelay(int iSize,float *pfDelay);
	int GetArrayDelay(int iSize,float *pfDelay) const;
	int SetArrayDelay(int iFocalLawIndex,int iSize,float *pfDelay);
	int GetArrayDelay(int iFocalLawIndex,int iSize,float *pfDelay) const;

	int SetElementIndex(int iIndex,int iElement);
	int GetElementIndex(int iIndex,int &iElement) const;

	int SetGain(int iElemIndex,float dValue);//unit is dB, if value <= -200 then the element is not used.
	int GetGain(int iElemIndex,float &dValue) const;
	int SetArrayGain(int iSize,float *pdValue);
	int GetArrayGain(int iSize,float *pdValue) const;

public:

	int SetFocalLawTof(int iFocalLawIndex,double dTof);
	int GetFocalLawTof(int iFocalLawIndex,double &dTof) const;
	int SetArrayFocalLawTof(int iSize,double *pdValue);
	int GetArrayFocalLawTof(int iSize,double *pdValue) const;

	int GetCenterDelay(float &fDelay) const;//main delay for the center point of the aperture.
	int SetCenterDelay(int iFocalLawIndex,float fDelay);//delay for the center point of the aperture.
	int GetCenterDelay(int iFocalLawIndex,float &fDelay) const;
	int SetArrayCenterDelay(int iSize,float *pfValue);
	int GetArrayCenterDelay(int iSize,float *pfValue) const;

	bool SetTRLWedgeDelaySize(int iSize);
	int GetTRLWedgeDelaySize() const;
	bool SetTRLWedgeDelayRef(int iIndex,double dTime);
	bool GetTRLWedgeDelayRef(int iIndex,double &dTime) const;
	bool SetTRLWedgeDelayReal(int iIndex,double dTime);
	bool GetTRLWedgeDelayReal(int iIndex,double &dTime) const;
	bool EnableTRL(bool bEnable);
	bool IsTRLEnabled() const;
	bool SetInterfaceCenterTRL(double dX,double dY,double dZ);
	bool GetInterfaceCenterTRL(double &dX,double &dY,double &dZ) const;


private:
public:

public:
	void SetShot(bool bShot);
	bool IsShot();
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};

class UTKERNEL_API_ALIGN _CUTPulser
{
private:
	ULONGLONG m_ullPrivateMemory[112];
protected:

};

class UTKERNEL_API_ALIGN CUTPulser :
	/*virtual*/ public CUTBaseClass,
	public CUTFocalLaw,
	public _CUTPulser
{
public:
private:
protected:

public:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTPulser();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTPulser(const CUTPulser &a);
	~CUTPulser();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	CUTFocalLaw& cast_CUTFocalLaw();
	CUTFocalLaw* cast_pCUTFocalLaw();
	int operator=(const CUTPulser &a);
	int operator=(const CUTFocalLaw &a);
	bool operator==(const CUTPulser &a);
	bool operator!=(const CUTPulser &a);

	int SetWidth(double dValue);//second
	double GetWidth() const;

	int SetPulseCount(int iValue);//pulser count
	int GetPulseCount() const;

//Trigger of the shot for the next cycle.
	int SetTrigger(enumTrigger eValue);
	enumTrigger GetTrigger() const;

	int SetTimer(double dValue);
	double GetTimer() const;

	int SetEncoder(double dValue);//unit meter.
	double GetEncoder() const;

private:
public:
	virtual bool vf_PostLoad(enumClassID eClassID,CUTFormat *pFormat);
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};

class UTKERNEL_API_ALIGN _CUTAcquisitionInfo
{
private:
	ULONGLONG m_ullPrivateMemory[107];
protected:

};

class UTKERNEL_API_ALIGN CUTAcquisitionInfo :
	public CUTBaseClass,
	public _CUTAcquisitionInfo
{
public:
private:
protected:

public:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTAcquisitionInfo();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTAcquisitionInfo(const CUTAcquisitionInfo &a);
	~CUTAcquisitionInfo();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	int operator=(const CUTAcquisitionInfo &a);
	bool operator==(const CUTAcquisitionInfo &a);
	bool operator!=(const CUTAcquisitionInfo &a);

	bool SetAcqReplayCount(int iCount);
	int GetAcqReplayCount() const;

	bool SetAcqId(int iReplay,wchar_t *pName);
	bool GetAcqId(int iReplay,int iSize,wchar_t *pName) const;
	bool SetAcqId(int iReplay,int iId);
	int GetAcqId(int iReplay) const;

	//By default encoderX and encoderY are used to store data in acquisition buffer,
	//you can also use encoder and add an offset to store data (offset can be different for each focal law).
	//But it is also possible to disable encoder and use a fixed index (offset) to store data.
	//The input eAxis (below) can be 'eX' or 'eY' ('eZ' not used).
	int SetOffset(enumAxis eAxis,int iReplay,float fValue);
	float GetOffset(enumAxis eAxis,int iReplay) const;
	int GetOffsetCount() const;//2 for axis X and axis Y.
	int SetMode(enumAxis eAxis,int iReplay,enumAcquisitionMode_ eAcquisitionMode);
	enumAcquisitionMode_ GetMode(enumAxis eAxis,int iReplay) const;


public:
	void SetAscan(bool bAscan);
	bool IsAscan() const;
	void SetSynchro(bool bEnable);
	bool IsSynchro() const;
	int GetSWOrder() const;
private:
public:
	virtual bool vf_PostLoad(enumClassID eClassID,CUTFormat *pFormat);
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};

class UTKERNEL_API_ALIGN _CUTGate
{
private:
	ULONGLONG m_ullPrivateMemory[583];
protected:

};

class UTKERNEL_API_ALIGN CUTGate :
	/*virtual*/ public CUTBaseClass,
	public _CUTGate
{
public:
private:
protected:

public:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTGate();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTGate(const CUTGate &a);
	~CUTGate();
	int operator=(const CUTGate &a);
	bool operator==(const CUTGate &a);
	bool operator!=(const CUTGate &a);
	CUTAcquisitionInfo& AcqInfo();

	int SetStartStop(double dStart,double dStop);//unit is Second. Safe function because it check only dStart>dStop (less risk of the failure).
	int SetGate(double dStart,double dRange);//unit is Second. Safe function.
	double GetStart() const;
	double GetStop() const;
	//following functions can also be used but it can fail more easily, it is better to use "SetStartStop".
	int SetStart(double dValue);//unit is Second. Be carefull it will failed if startNew>stopOld.
	int SetStop(double dValue);//unit is Second. Be carefull it will failed if stopNew<startOld.

	int SetThreshold(double dValue);//unit is percent.
	double GetThreshold() const;

//for cscan gate only
	int SetModeAmplitude(enumGateModeAmp eModeAmp);
	enumGateModeAmp GetModeAmplitude() const;

	int SetModeTimeOfFlight(enumGateModeTof eModeTof);
	enumGateModeTof GetModeTimeOfFlight() const;

	int SetRectification(enumRectification eRectification);//unit is percent.
	enumRectification GetRectification() const;

//for gate with synchronisation
	int SetStartSyncTof(int iTofInputIndex);//synchronisation with another gate.
	int GetStartSyncTof() const;

	int SetStopSyncTof(int iTofInputIndex);//synchronisation with another gate.
	int GetStopSyncTof() const;

//for Cscan gate only
	int SetSyncTofOutput(int iTofOutputIndex);
	int GetSyncTofOutput() const;

	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	void SetAscan(bool bAscan);
	bool IsAscan() const;
	virtual bool vf_UpdateUserMode(enumUserMode eUserMode);
private:
public:
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};



class UTKERNEL_API_ALIGN _CUTReceiver
{
private:
	ULONGLONG m_ullPrivateMemory[73];
protected:

};

class UTKERNEL_API_ALIGN CUTReceiver :
	/*virtual*/ public CUTBaseClass,
	public CUTFocalLaw,
	public CUTGate,
	public _CUTReceiver
{
public:
private:
protected:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTReceiver();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTReceiver(const CUTReceiver &a);
	~CUTReceiver();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	CUTFocalLaw& cast_CUTFocalLaw();
	int operator=(const CUTReceiver &a);
	int operator=(const CUTFocalLaw &a);
	int operator=(const CUTGate &a);
	bool operator==(const CUTReceiver &a);
	bool operator!=(const CUTReceiver &a);
	CUTGate& operator[](int iGate);//Cscan Gate
	CUTGate& CscanGate(int iGate);//Cscan Gate

//ascan setting
	int SetGainDigital(double dValue);
	double GetGainDigital() const;
	int SetGainAnalog(double dValue);
	double GetGainAnalog() const;

//cscan
	int SetCscanCount(int iSize);
	int GetCscanCount() const;

	int SetCscanGate(int iIndex,CUTGate &value);
	int GetCscanGate(int iIndex,CUTGate &value) const;

private:
public:
	virtual bool vf_PostLoad(enumClassID eClassID,CUTFormat *pFormat);
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};



class UTKERNEL_API_ALIGN _CUTPulserReceiver
{
private:
	ULONGLONG m_ullPrivateMemory[183];
protected:

};

class UTKERNEL_API_ALIGN CUTPulserReceiver :
	/*virtual*/ public CUTBaseClass,
	public CUTPulser,
	public _CUTPulserReceiver
{
public:
private:
protected:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTPulserReceiver();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTPulserReceiver(const CUTPulserReceiver &a);
	~CUTPulserReceiver();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	CUTPulser& Pulser();
	CUTReceiver& Receiver();
	int operator=(const CUTPulserReceiver &a);
	int operator=(const CUTPulser &a);
	bool operator==(const CUTPulserReceiver &a);
	bool operator!=(const CUTPulserReceiver &a);

public:

	int SetReceiverCount(int iCycleCount);
	int GetReceiverCount() const;

	int SetReceiver(int iCycleIndex,const CUTReceiver &value);
	//int GetReceiver(int iCycleIndex,CUTReceiver &value) const;//NOT SAFE (if the output parameter is a static data !!!!!

	int SetDigFreq(int iValue);
	int GetDigFreq() const;

	int SetDigTimeStart(double dValue);//first usefull digitized point (default is 0, no need to specify except for VF).
	int SetDigStart(int iValue);
	double GetDigTimeStart() const;
	int GetDigStart() const;

	int SetDigRange(double dValue);//usefull digitized point count (default is 65535, no need to specify except for VF).
	int SetDigCount(int iValue);
	double GetDigRange() const;
	int GetDigCount() const;

	int SetOrder(bool bEnable);
	bool GetOrder() const;

	int SetOrder(int iCycleIndex,int iCycleOrder);
	int GetOrder(int iCycleIndex,int &iCycleOrder) const;

private:
public:
	virtual bool vf_PostLoad(enumClassID eClassID,CUTFormat *pFormat);
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};



class UTKERNEL_API_ALIGN _CUTScan
{
private:
	ULONGLONG m_ullPrivateMemory[164];
protected:

};

class UTKERNEL_API_ALIGN CUTScan : 
	/*virtual*/ public CUTBaseClass,
	public CUTWizardScan,//CUTWizardScan for pulse/echo
	public _CUTScan
{
public:
private:
protected:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTScan();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTScan(const CUTScan &a);
	~CUTScan();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	CUTWizardScan& cast_CUTWizardScan();
	int operator=(const CUTScan &a);
	bool operator==(const CUTScan &a);
	bool operator!=(const CUTScan &a);
	CUTPulserReceiver& operator[](int iPulserReceiver);

	int SetWizardScanEnable(bool bValue);
	bool IsWizardScanEnable() const;


public:

	int SetGainCount(int iSize);
	int GetGainCount() const;
	int SetGain(int iIndex,float dValue);//unit is dB, if value <= -200 then the element is not used.
	int GetGain(int iIndex,float &dValue) const;
	int SetArrayGain(int iSize,float *pdValue);
	int GetArrayGain(int iSize,float *pdValue) const;

	int SetPulserReceiverCount(int iValue);
	int GetPulserReceiverCount() const;

	int SetPulserReceiver(int iIndex,CUTPulserReceiver &value);
	int GetPulserReceiver(int iIndex,CUTPulserReceiver &value) const;

	int GetReceiverCycleCount() const;
	CUTProbe* GetProbe(bool *pbMultiChannel=NULL);

private:
public:
	virtual bool vf_PostLoad(enumClassID eClassID,CUTFormat *pFormat);
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};



//A probe is used for inspection.
//It can be a phased array or many monotransducer.
class UTKERNEL_API_ALIGN _CUTProbe
{
private:
	ULONGLONG m_ullPrivateMemory[293];
protected:

};

class UTKERNEL_API_ALIGN CUTProbe :
	public CUTBaseClass,
	public _CUTProbe
{
public:
private:
protected:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTProbe();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTProbe(const CUTProbe &a);
	~CUTProbe();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	int operator=(const CUTProbe &a);
	bool operator==(const CUTProbe &a);
	bool operator!=(const CUTProbe &a);
	CUTScan& operator[](int iScan);
	CUTScan& Scan(int iScan);
	CUTScan& Scan();//MonoChannel

	const CUTWizardSystem* cast_cpWizardSystem();
	CUTWizardSystem* cast_pWizardSystem();
	CUTWizardProbe* cast_pWizardProbe(bool bPulse);
	enumWizardProbe GetWizardProbe(bool bPulse);

	bool SetWizardSystemId(bool bPulse,CUTWizardSystem *pWizardSystem,int iIndexWizardProbe);//easy way for the user.
	bool SetWizardSystemId(bool bPulse,wchar_t *pValue);
	int GetWizardSystemId(bool bPulse) const;
	bool GetWizardSystemId(bool bPulse,int iSize,wchar_t *pValue) const;
	int GetWizardSystemId(bool bPulse,int &iWizardProbeId) const;
	int GetWizardProbeIndex(bool bPulse) const;

	int SetHighVoltage(int iValue);
	int GetHighVoltage() const;

	int SetElementCount(int iValue);
	int GetElementCount() const;

	int SetFirst(int iValue);
	int GetFirst() const;

	int SetMode(enumProbeMode eValue);//is it usefull to have a "Pulse" only probe (that is the HW cannot manage reception) ? maybe for special case (driver of driver).
	enumProbeMode GetMode() const;

	int SetScanCount(int iValue);
	int GetScanCount() const;

	int SetScan(int iIndex,CUTScan &value);
	int GetScan(int iIndex,CUTScan &value) const;

	int SetPulserReceiverCount(int iScanIndex,int iPulserSize,int *aiReceiverCycleCount);//set the count of pulser and for each one the count of receiver cycle.
	int GetReceiverCycleCount() const;

	bool UpdateStatusRequired();//automatic update or set status to OutOfDate
	void UpdateScan();
	int SetWizardSystemUpdateAuto(bool bValue);
	bool IsWizardSystemUpdateAuto() const;

	int SetNextAfterLastIsFirst(bool bEnable);//case eLinear1D_NextAfterLastIsFirst
	bool IsNextAfterLastIsFirst() const;//case eLinear1D_NextAfterLastIsFirst

private:
public:
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};


class CUTChannels;

class UTKERNEL_API_ALIGN _CParametersAcquisition
{
private:
	ULONGLONG m_ullPrivateMemory[22];
protected:

};

class UTKERNEL_API_ALIGN CParametersAcquisition :
	public _CParametersAcquisition
{
public:

public:
public:
	virtual bool vf_Alloc();
	virtual bool vf_IsAllocated() const;
	virtual bool vf_Free();

public:
	bool DumpInspectionTable(wchar_t *pFileName);
private:

public:
private:
	
};


class UTKERNEL_API_ALIGN _CUTChannels
{
private:
	ULONGLONG m_ullPrivateMemory[390];
protected:

};

class UTKERNEL_API_ALIGN CUTChannels :
	public limitCUTChannels,
	public CUTKernelRoot,
	public CUTData,
	public CParametersAcquisition,
	public _CUTChannels
{
public:
private:
public:

public:
public:
	CUTChannels(bool bMultiChannel,bool bUTParameters,bool bTemporary,bool bStatic);
	CUTChannels(bool bTemporary=false,bool bStatic=false);
	CUTChannels(const CUTChannels &a);
	~CUTChannels();
	CUTKernelRoot* cast_pCUTKernelRoot();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	int operator=(const CUTChannels &a);
	bool operator==(const CUTChannels &a);
	bool operator!=(const CUTChannels &a);
	CUTProbe& operator[](int iProbeIndex);//a reference ('CUTProbe& operator[]') can be used only if the low level 'CUTProbe::vf_operator=' is used to check eveything, otherwise 'CUTProbe* operator[]' should be used.
	CUTProbe& Probe(int iProbeIndex);//a reference ('CUTProbe& operator[]') can be used only if the low level 'CUTProbe::vf_operator=' is used to check eveything, otherwise 'CUTProbe* operator[]' should be used.
	CUTProbe& Probe();//MonoChannel
	bool IsMultiChannels() const;//for this object only.
	bool IsUTParameters() const;
	static bool IsDefaultMultiChannels();//default value in configuration file.
	static bool IsDefaultUTParameters();//default value in configuration file.
	static void SetDefaultMultiChannels(bool bEnable);//"CSWDeviceOEMPA1::EnableMultiChannel" is the same.
	static bool IsMatlabDisplayScanReceptionEnabled();
	static void EnableMatlabDisplayScanReception(bool bEnable);
	static bool IsMatlabDisplaySystemEnabled();
	static void EnableMatlabDisplaySystem(bool bEnable);
	void SaveResults(bool bEnable);
	bool IsSavedResults();
	bool LinkWizardProbe(int iChannelProbeIndex,int iRootWizardSystemId,int iWizardProbeIndex);//to link with a wizard probe easily.
	bool LinkWizardProbe(int iChannelProbeIndex,CUTWizardSystem *pWizard,int iWizardProbeIndex);//to link with a wizard probe easily.
	bool LinkWizardProbe(bool bEmission,int iChannelProbeIndex,CUTWizardSystem *pWizard,int iWizardProbeIndex);//to link separately the emission with a wizard probe easily.

//root ID management.
	bool SetID(int iRootID);//to connect with a preexisting data in kernel database.
	bool FreeID();//to disconnect the data with the kernel database.
	bool SetName(const wchar_t *pName,int iRootID=-1);//to register this new data in the kernel database.
	virtual bool vf_SetID(int iRootID);//to connect with a preexisting data in kernel database.
	virtual bool vf_FreeID();//to disconnect the data with the kernel database.
	virtual bool vf_SetName(const wchar_t *pName,int iRootID=-1);//to register this new data in the kernel database.

public:

//Setting
	CUTProbe* AddProbe();
	CUTProbe* GetProbe(int iIndex);
	bool RemoveProbe(int iIndex);
	int ProbeCountIncrement();
	int ProbeCountDecrement();
	int GetProbeCount() const;

	int SetScan(int iProbeIndex,int iScanCount,int *aiPulserCount);//set the count of pulser and for each one the count of receiver cycle.
	bool SetSWGateOrder(int &iAscanCount,int &iCscanCount);

	int SetProbe(int iIndex,CUTProbe &value);
	int GetProbe(int iIndex,CUTProbe &value) const;

#ifdef KERNEL_API_HWDEVICE
#endif //KERNEL_API_HWDEVICE
	virtual enumRootType vf_GetRootType() const;

public:
	enumRootType GetRootType() const;
	virtual int vf_EventSystem(enumEvent eEvent,int iRootID,enumRootType eRoot,const wchar_t *pName,wchar_t *pNameOld);
private:
public:
	virtual int vf_GetSizeLimit();
	virtual bool vf_WriteLimit(int iSize,char *pBuffer,int iOffset);
	virtual bool vf_ReadLimit(int iSize,char *pBuffer,int iOffset);
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};


class CUTModule;
class UTKERNEL_API_ALIGN _CUTModule
{
private:
	ULONGLONG m_ullPrivateMemory[162];
protected:

};

class UTKERNEL_API_ALIGN CUTModule :
	public CUTBaseClass,
	public _CUTModule
{
public:
private:
protected:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTModule();
#endif //CONSTRUCTOR_NO_PARAMETER

	~CUTModule();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	int operator=(const CUTModule &a);
	bool operator==(const CUTModule &a);
	bool operator!=(const CUTModule &a);

	int SetName(wchar_t *pName);
	bool GetName(int iSize,wchar_t *pName) const;

	//BE CAREFULL this item is not shared between different instances of the same root ID object !
	int SetLanguage(const wchar_t *pName);
	bool GetLanguage(int iSize,wchar_t *pName) const;

	int SetCompilation(wchar_t *pValue);
	bool GetCompilation(int iSize,wchar_t *pValue) const;

	int SetVersion(enumVersionType eVersionType,wchar_t *pVersion);
	bool GetVersion(enumVersionType eVersionType,int iSize,wchar_t *pVersion) const;

	int SetVersion(enumVersionType eVersionType,enumVersionWord eVersion,WORD wValue);
	WORD GetVersion(enumVersionType eVersionType,enumVersionWord eVersion) const;

	static bool GetVersion(wchar_t *pVersion,WORD &wMajorMSWord,WORD &wMajorLSWord,WORD &wMinorMSWord,WORD &wMinorLSWord);
	static bool SetVersion(WORD wMajorMSWord,WORD wMajorLSWord,WORD wMinorMSWord,WORD wMinorLSWord,int iSize,wchar_t *pVersion);

	int SetProduct(const wchar_t *pName);
	bool GetProduct(int iSize,wchar_t *pName) const;

	int SetCompany(const wchar_t *pName);
	bool GetCompany(int iSize,wchar_t *pName) const;

private:
public:
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};



class UTKERNEL_API_ALIGN _CUTPreference
{
private:
	ULONGLONG m_ullPrivateMemory[361];
protected:

};

class UTKERNEL_API_ALIGN CUTPreference :
	public limitCUTPreference,
	public CUTKernelRoot,
	public _CUTPreference
{
public:
private:
public:

public:
public:
#ifdef CONSTRUCTOR_NO_PARAMETER
	CUTPreference();
#endif //CONSTRUCTOR_NO_PARAMETER

	CUTPreference(const CUTPreference &a);
	~CUTPreference();
	CUTKernelRoot* cast_pCUTKernelRoot();
	CUTBaseClass *cast_pCUTBaseClass();
	const CUTBaseClass& const_cast_CUTBaseClass() const;
	static CUTPreference* GetCurrentPreference();//only one object for all processes.
	int operator=(const CUTPreference &a);
	bool operator==(const CUTPreference &a);
	bool operator!=(const CUTPreference &a);
	CUTModule& operator[](int iIndex);

	bool SetID(int iRootID);//to connect with a preexisting data in kernel database.
	bool SetName(const wchar_t *pName,int iRootID=-1);//to register this new data in the kernel database.
	bool FreeID();//to disconnect the data with the kernel database.
	virtual bool vf_SetID(int iRootID);//to connect with a preexisting data in kernel database.
	virtual bool vf_SetName(const wchar_t *pName,int iRootID=-1);//to register this new data in the kernel database.
	virtual bool vf_FreeID();//to disconnect the data with the kernel database.

public:

	int SetUserMode(enumUserMode eUserMode);
	enumUserMode GetUserMode();

	int SetPassword(wchar_t *pPassword);
	//bool GetPassword(int iSize,wchar_t *pPassword);

	int SetDeviceDefaultHardware(enumHardware eHW);
	enumHardware GetDeviceDefaultHardware() const;
	int SetCommonKeepAlive(bool bEnable);
	bool GetCommonKeepAlive() const;
	int SetDeviceAutoDisconnect(bool bEnable);
	bool GetDeviceAutoDisconnect() const;
	int SetDefaultSetupAuto(bool bEnable);
	bool GetDefaultSetupAuto() const;
	int SetCommonUnlockEnableShot(bool bEnable);
	bool GetCommonUnlockEnableShot() const;
	int SetMonitorAutoListen(bool bEnable);
	bool GetMonitorAutoListen() const;
	int SetCustomFilterAutoRun(bool bEnable);
	bool GetCustomFilterAutoRun() const;

	int SetAcqStatusTimer(double dTime);
	double GetAcqStatusTimer() const;
	int EnableAcqStatus(bool bEnable);
	bool IsAcqStatusEnabled() const;

	bool AddDeviceCount(int iCount);
	int SetConnectedDeviceCount(int iCount);
	int GetConnectedDeviceCount() const;

	int GetModuleCount();

	int SetVersion(enumVersionType eVersionType,wchar_t *pModuleName,wchar_t *pVersion);
	bool GetVersion(enumVersionType eVersionType,wchar_t *pModuleName,int iSize,wchar_t *pVersion) const;
	int SetVersion(enumVersionType eVersionType,wchar_t *pModuleName,enumVersionWord eVersion,WORD wValue);
	WORD GetVersion(enumVersionType eVersionType,wchar_t *pModuleName,enumVersionWord eVersion) const;

	int UpdateCurrentProcessModuleList();
	bool Add(const CUTModule &a);
	static bool GetKernelModule(bool bFullPathName,int iSize,wchar_t *pName);
	static void GetKernelFixedFileInfo(VS_FIXEDFILEINFO &fixedFileInfo);

	bool GetCompilationOption(int iSize,wchar_t *pValue) const;

private:
public:
	virtual int vf_GetSizeLimit();
	virtual bool vf_WriteLimit(int iSize,char *pBuffer,int iOffset);
	virtual bool vf_ReadLimit(int iSize,char *pBuffer,int iOffset);
	virtual enumRootType vf_GetRootType() const;

public:
	enumRootType GetRootType() const;
	virtual bool vf_PostLoad(enumClassID eClassID,CUTFormat *pFormat);
	virtual void vf_UpdateClass(enumClassID eClassID);
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);

public:
private:
	
};

#pragma warning( default : 4584 )
