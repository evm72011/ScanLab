
#pragma once

typedef bool (WINAPI* pCallbackSetSize)(struct structCallbackArrayFloat1D *pCallbackArray, int iSize);
typedef bool (WINAPI* pCallbackSetData)(struct structCallbackArrayFloat1D *pCallbackArray, int iIndex, float fData);
typedef bool (WINAPI* pCallbackGetSize)(struct structCallbackArrayFloat1D *pCallbackArray, int &iSize);
typedef bool (WINAPI* pCallbackGetData)(struct structCallbackArrayFloat1D *pCallbackArray, int iIndex, float &fData);
typedef struct structCallbackArrayFloat1D
{
	void *apParameter[g_iCallbackArrayParameterCountMax];
	pCallbackSetSize pSetSize;
	pCallbackSetData pSetData;
	pCallbackGetSize pGetSize;
	pCallbackGetData pGetData;
} structCallbackArrayFloat1D;

typedef bool (WINAPI* pCallbackSetSizeInt)(struct structCallbackArrayInt1D* pCallbackArray, int iSize);
typedef bool (WINAPI* pCallbackSetDataInt)(struct structCallbackArrayInt1D* pCallbackArray, int iIndex, int iData);
typedef bool (WINAPI* pCallbackGetSizeInt)(struct structCallbackArrayInt1D* pCallbackArray, int& iSize);
typedef bool (WINAPI* pCallbackGetDataInt)(struct structCallbackArrayInt1D* pCallbackArray, int iIndex, int& iData);
typedef struct structCallbackArrayInt1D
{
	void* apParameter[g_iCallbackArrayParameterCountMax];
	pCallbackSetSizeInt pSetSize;
	pCallbackSetDataInt pSetData;
	pCallbackGetSizeInt pGetSize;
	pCallbackGetDataInt pGetData;
} structCallbackArrayInt1D;

typedef bool (WINAPI* pCallbackSetSizeDouble)(struct structCallbackArrayDouble1D *pCallbackArray, int iSize);
typedef bool (WINAPI* pCallbackSetDataDouble)(struct structCallbackArrayDouble1D *pCallbackArray, int iIndex, double fData);
typedef bool (WINAPI* pCallbackGetSizeDouble)(struct structCallbackArrayDouble1D *pCallbackArray, int &iSize);
typedef bool (WINAPI* pCallbackGetDataDouble)(struct structCallbackArrayDouble1D *pCallbackArray, int iIndex, double &fData);
typedef struct structCallbackArrayDouble1D
{
	void *apParameter[g_iCallbackArrayParameterCountMax];
	pCallbackSetSizeDouble pSetSize;
	pCallbackSetDataDouble pSetData;
	pCallbackGetSizeDouble pGetSize;
	pCallbackGetDataDouble pGetData;
} structCallbackArrayDouble1D;

typedef bool (WINAPI* pCallbackSetSize2)(struct structCallbackArrayFloat2D *pCallbackArray, int iSize1, int iSize2);
typedef bool (WINAPI* pCallbackSetData2)(struct structCallbackArrayFloat2D *pCallbackArray, int iIndex1, int iIndex2, float fData);
typedef bool (WINAPI* pCallbackGetSize2)(struct structCallbackArrayFloat2D *pCallbackArray, int &iSize1, int &iSize2);
typedef bool (WINAPI* pCallbackGetData2)(struct structCallbackArrayFloat2D *pCallbackArray, int iIndex1, int iIndex2, float &fData);
typedef struct structCallbackArrayFloat2D
{
	void *apParameter[g_iCallbackArrayParameterCountMax];
	pCallbackSetSize2 pSetSize;
	pCallbackSetData2 pSetData;
	pCallbackGetSize2 pGetSize;
	pCallbackGetData2 pGetData;
} structCallbackArrayFloat2D;

typedef bool (WINAPI* pCallbackSetSizeDac)(struct structCallbackArrayFloatDac *pCallbackArray, int iSize);
typedef bool (WINAPI* pCallbackSetDataDac)(struct structCallbackArrayFloatDac *pCallbackArray, int iIndex, double dTime, float fSlope);
typedef bool (WINAPI* pCallbackGetSizeDac)(struct structCallbackArrayFloatDac *pCallbackArray, int &iSize);
typedef bool (WINAPI* pCallbackGetDataDac)(struct structCallbackArrayFloatDac *pCallbackArray, int iIndex, double &dTime, float &fSlope);
typedef bool (WINAPI* pCallbackSetSizeDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int iSize);
typedef bool (WINAPI* pCallbackSetDataDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int iIndex, double dTime, float fSlope);
typedef bool (WINAPI* pCallbackGetSizeDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int &iSize);
typedef bool (WINAPI* pCallbackGetDataDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int iIndex, double &dTime, float &fSlope);
typedef struct structCallbackArrayFloatDac
{
	void *apParameter[g_iCallbackArrayParameterCountMax];
	pCallbackSetSizeDac	pSetSize;
	pCallbackSetDataDac pSetData;
	pCallbackGetSizeDac	pGetSize;
	pCallbackGetDataDac pGetData;
	pCallbackSetSizeDacVga pSetSizeAnalog;
	pCallbackSetDataDacVga pSetDataAnalog;
	pCallbackGetSizeDacVga pGetSizeAnalog;
	pCallbackGetDataDacVga pGetDataAnalog;
} structCallbackArrayFloatDac;

//typedef bool (WINAPI* pCallbackSetSizeDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int iSize);
//typedef bool (WINAPI* pCallbackSetDataDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int iIndex, double dTime, float fSlope);
//typedef bool (WINAPI* pCallbackGetSizeDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int &iSize);
//typedef bool (WINAPI* pCallbackGetDataDacVga)(struct structCallbackArrayFloatDac *pCallbackArray, int iIndex, double &dTime, float &fSlope);
//typedef struct structCallbackArrayFloatDac
//{
//	void *apParameter[g_iCallbackArrayParameterCountMax];
//	pCallbackSetSizeDac pSetSizeDigital;
//	pCallbackSetDataDac pSetDataDigital;
//	pCallbackGetSizeDac pGetSizeDigital;
//	pCallbackGetDataDac pGetDataDigital;
//	pCallbackSetSizeDacVga pSetSizeAnalog;
//	pCallbackSetDataDacVga pSetDataAnalog;
//	pCallbackGetSizeDacVga pGetSizeAnalog;
//	pCallbackGetDataDacVga pGetDataAnalog;
//} structCallbackArrayFloatDac;

typedef bool (WINAPI* pCallbackSetSizeByte1D)(struct structCallbackArrayByte1D *pCallbackArray, int iSize);
typedef bool (WINAPI* pCallbackSetDataByte1D)(struct structCallbackArrayByte1D *pCallbackArray, int iIndex, BYTE byData);
typedef bool (WINAPI* pCallbackGetSizeByte1D)(struct structCallbackArrayByte1D *pCallbackArray, int &iSize);
typedef bool (WINAPI* pCallbackGetDataByte1D)(struct structCallbackArrayByte1D *pCallbackArray, int iIndex, BYTE &byData);
typedef struct structCallbackArrayByte1D
{
	void *apParameter[g_iCallbackArrayParameterCountMax];
	pCallbackSetSizeByte1D pSetSize;
	pCallbackSetDataByte1D pSetData;
	pCallbackGetSizeByte1D pGetSize;
	pCallbackGetDataByte1D pGetData;
} structCallbackArrayByte1D;

const int g_iOEMDACCountMax = 64;
const int g_iOEMApertureElementCountMax = 16 * g_iOEMPABoardCountMax;
const int g_iOEMDecimationCountMax = 2 * 16 * g_iOEMPABoardCountMax;
class CHWDeviceOempa1;

typedef struct structDecimation {
	unsigned lsb : 4;
	unsigned msb : 4;
	//comment about the values:
	//	0 => decimation of 1 = no decimation.
	//	1 => decimation of 2 (digitizing frequency is divided by 2).
	//	...
	//	15 => decimation of 16 (digitizing frequency is divided by 16).
}structDecimation;
typedef union unionDecimation {
	structDecimation data;
	BYTE byte;
}unionDecimation;
typedef union unionOEMMCDecimation {
	unsigned char byte[g_iOEMDecimationCountMax / 2];
	ULONG dword[g_iOEMDecimationCountMax / (2 * sizeof(ULONG))];
	uint64_t ulonglong[g_iOEMDecimationCountMax / (2 * sizeof(uint64_t))];
}unionOEMMCDecimation;

typedef struct strutOEMPACycleCscanBits {
	unsigned valid : 1;//
	unsigned AmpOverThreshold : 1;//0 if byAmp is under threshold, and 1 if it is over the threshold.
	unsigned TofValidity : 1;//1 if wTof is valid.
	unsigned IFOldReference : 1;//(IFtracking) 1 if old reference time of flight has been used to synchronize the start or the stop.
	unsigned IFNotInitialized : 1;//(IFtracking) 1 if the first reference time of flight has been initialized yet (because of acoustic or because of bad setting stop>start).
}strutOEMPACycleCscanBits;
typedef struct structOEMPACycleCscan
{
	strutOEMPACycleCscanBits bits;
	short sAmp;
	// 32bit TOF
	//short sTof;
	int iTof;
	unsigned int uMultiPeakCount;
	bool MultiPeakAmpOverThreshold[g_uAmpMultiPeakCountMax];//0 if byAmp is under threshold, and 1 if it is over the threshold.
	int iMultiPeakTofs[g_uAmpMultiPeakCountMax];
	short sMultiPeakAmps[g_uAmpMultiPeakCountMax];
}structOEMPACycleCscan;

typedef struct structOEMPATracking
{
	bool enable;
	char gateId;
	short cycleId;
	char channelId;
}structOEMPATracking;
typedef struct structOEMPAGateTrack
{
	structOEMPATracking start;
	structOEMPATracking stop;
	enumGateTarget startGateType;
	enumGateTarget stopGateType;
}structOEMPAGateTrack;
typedef struct structOEMPACycleGateEnable
{
	unsigned enable : 1;//FW gate enable.
	unsigned start : 1;//FW start is valid.
	unsigned stop : 1;//FW stop is valid.
	unsigned threshold : 1;//FW threshold is valid.
	unsigned width : 1;
	unsigned marge : 3;
}structOEMPACycleGateEnable;
typedef struct structOEMPACycleGate
{
	enumGateTarget eTarget;//should be moved to "structCycleParameter".
	structOEMPACycleGateEnable enable;
	BYTE modeAmp;
	BYTE modeTof;
	BYTE rectif;
	LONG lStartFW;//FW digitizing clock.
	LONG lStopFW;//FW digitizing clock.
	float fThreshold;
	WORD acqIdAmp;
	WORD acqIdTof;
	structOEMPAGateTrack track;
	unsigned int multiPeakCountMax;
	long multiPeakExclusionInterval;
}structOEMPACycleGate;

#ifdef CYCLE_ORDERING
typedef struct structOEMPACycleParameterAscanInfo {
	unsigned ascanBitSize : 4;
	unsigned _signed : 1;
	unsigned marge : 3;
} structOEMPACycleParameterAscanInfo;
#ifndef TAG_STRUCTSUBCYCLEORDER
#define TAG_STRUCTSUBCYCLEORDER \
	unsigned subcycle : 8;\
	unsigned marge : 5;\
	unsigned bFirst : 1;\
	unsigned bLast : 1;\
	unsigned bNotFMC : 1;//unsigned marge2 : 1;//required to be sure that this is not FMC.
#endif //TAG_STRUCTSUBCYCLEORDER
typedef struct structSubCycleOrder {
	TAG_STRUCTSUBCYCLEORDER
} structSubCycleOrder;
typedef union unionSubCycleOrder {
	structSubCycleOrder order;
	WORD word;
} unionSubCycleOrder;
typedef struct structCycleOrder {
	TAG_STRUCTSUBCYCLEORDER
	unsigned cycle : 16;
} structCycleOrder;
typedef union unionCycleOrder {
	structCycleOrder order;
	DWORD dword;
} unionCycleOrder;
typedef union unionOEMPACycleParameterAscanPtr {
	void *pVoid;
	char *pChar;
	BYTE *pByte;
	short *pShort;
	WORD *pWord;
} unionOEMPACycleParameterAscanPtr;
#endif //CYCLE_ORDERING

typedef struct structCycleParameter
{
	DWORD dwTimeSlot;//FW digitizing clock.
	float fAnalogCompensation[g_iOEMPAApertureElementCountMax];
	float afRxGain[g_iOEMPAApertureElementCountMax];//required to manage analog gain linearity.
	float fPulseWidthMax;
	float fBeamCorrection;
	float fGainAnalog;
	float fThroughput;
	LONG lWedgeDelayE;
	LONG lWedgeDelayR;
	LONG lGainDigital;
	LONG lDacGainMin;
	LONG lDacGainMax;
	LONG lDacTimeMin;
	LONG lDacTimeMax;
	BYTE byDACPointCount;
	BYTE byDDFPointCount;
	BYTE byStreamMode;
	bool bDACEnable;
	bool bDDFEnable;
	bool bEnableCorrection;//"BeamCorrection" UT parameter could be enabled or disabled.
	bool bSelectionEnabled;//useful for example in case of calibration to select the list of cycles.
	bool bCalibrationEnabled;
	bool bUpsampling;//Upsampling enabled for this cycle.
	bool bReducedStart;//Start was reduced (and range extended). For upsampling.
	double dAscanStartOrig;//useful if start has been changed because of upsampling.
	LONG lAScanStart;//useful to get the real gate start for SW gates.
	LONG lAScanRange;//useful to check minimum time-slot.
	LONG lPointCount;
	LONG lPointFactor;//useful to compute the real start/stop for SW gates.
	BYTE byFilterIndex;//usefull for PAµ, merged with dig and ana gains.
	WORD wMaxId;//usefull for PAµ, merged with min id.
	WORD wMinId;//usefull for PAµ, merged with max id.
	WORD wSatId;//usefull for PAµ, merged with point count.
	enumCompressionType eCompType;//same as above.
	enumRectification eRectification;//useful to check if SW gate rectification is meaningful
	structOEMPACycleCscan lastValid[g_iOEMPAGateCountMax];//IF tracking table equivalent.
	structOEMPACycleGate gate[g_iOEMPAGateCountMax];
	structOEMPACycleCscan swCscan[g_iOEMPAGateCountMax];
	structOEMPACycleCscan hwCscan[g_iOEMPAGateCountMax];
	structOEMPACycleCscan maxCscan[g_iOEMPAGateCountMax];
#ifdef CYCLE_ORDERING
	structOEMPACycleParameterAscanInfo ascanFieldsInfo;
	BYTE byAscanCount;
	structSubCycleOrder ascanFields;//WORD
	WORD wAscanPointCount;
	WORD marge1;
	LONG *pAscan;//long is better for the average of WORD (at least WORD to average char).
#endif //CYCLE_ORDERING
	structOEMPATracking trackingDac;
	structOEMPATracking trackingAscan;
}structCycleParameter;
typedef struct structCycleParameterMC
{
	DWORD dwTimeSlot;//FW digitizing clock.

	float fPulseWidthMax[g_iOEMMCApertureElementCountMax];
	float fBeamCorrection[g_iOEMMCApertureElementCountMax];
	float fAnalogCompensation[g_iOEMMCApertureElementCountMax];
	float fGainAnalog;
	float fThroughput[g_iOEMMCApertureElementCountMax];
	float fThroughputTotal;
	LONG lWedgeDelayE[g_iOEMMCApertureElementCountMax];
	LONG lWedgeDelayR[g_iOEMMCApertureElementCountMax];
	LONG lGainDigital[g_iOEMMCApertureElementCountMax];
	LONG lDacGainMin[g_iOEMMCApertureElementCountMax];
	LONG lDacGainMax[g_iOEMMCApertureElementCountMax];
	LONG lDacTimeMin[g_iOEMMCApertureElementCountMax];
	LONG lDacTimeMax[g_iOEMMCApertureElementCountMax];
	BYTE byDACPointCount[g_iOEMMCApertureElementCountMax];
	bool bDACEnable[g_iOEMMCApertureElementCountMax];
	bool bEnableCorrection[g_iOEMMCApertureElementCountMax];//"BeamCorrection" UT parameter could be enabled or disabled.
	bool bSelectionEnabled;//useful for example in case of calibration to select the list of cycles.
	bool bCalibrationEnabled;
	bool bUpsampling;//Upsampling enabled for this cycle.
	bool bReducedStart;//Start was reduced (and range extended). For upsampling.
	double dAscanStartOrig[g_iOEMMCApertureElementCountMax];//useful if start has been changed because of upsampling.
	LONG lAScanStart[g_iOEMMCApertureElementCountMax];//useful to get the real gate start for SW gates.
	LONG lAScanRange[g_iOEMMCApertureElementCountMax];//useful to check minimum time-slot.
	LONG lPointCount[g_iOEMMCApertureElementCountMax];
	LONG lPointFactor[g_iOEMMCApertureElementCountMax];//useful to compute the real start/stop for SW gates.
	enumCompressionType eCompType[g_iOEMMCApertureElementCountMax];//same as above.
	enumRectification eRectification[g_iOEMMCApertureElementCountMax];//useful to check if SW gate rectification is meaningful
	structOEMPACycleCscan lastValid[g_iOEMMCApertureElementCountMax][g_iOEMPAGateCountMax];//IF tracking table equivalent. for MC2 gate tracking.
	structOEMPACycleGate gate[g_iOEMMCApertureElementCountMax][g_iOEMPAGateCountMax];	// for MC2 gate tracking.
	structOEMPACycleCscan swCscan[g_iOEMMCApertureElementCountMax][g_iOEMPAGateCountMax];
	structOEMPACycleCscan hwCscan[g_iOEMMCApertureElementCountMax][g_iOEMPAGateCountMax];
	structOEMPACycleCscan maxCscan[g_iOEMMCApertureElementCountMax][g_iOEMPAGateCountMax];
#ifdef CYCLE_ORDERING
	structOEMPACycleParameterAscanInfo ascanFieldsInfo;
	BYTE byAscanCount;
	structSubCycleOrder ascanFields;//WORD
	WORD wAscanPointCount;
	WORD marge1;
	LONG* pAscan;//long is better for the average of WORD (at least WORD to average char).
#endif //CYCLE_ORDERING
	structOEMPATracking trackingDac[g_iOEMMCApertureElementCountMax];
	structOEMPATracking trackingAscan[g_iOEMMCApertureElementCountMax];
	bool bRxEnabled[g_iOEMMCApertureElementCountMax];
	bool bTxEnabled[g_iOEMMCApertureElementCountMax];
}structCycleParameterMC;
typedef struct structCycleParameterPA
{
	bool bMaximum;
	bool bMinimum;
	bool bSaturation;
	DWORD dwScaling;
	DWORD adwPulserCount[g_iAssociationSubDeviceCountMax];
	DWORD adwRxAprture[g_iOEMPAminiApertureDWordCount * g_iAssociationSubDeviceCountMax];
	ULONGLONG ullTxEnable;	// for PAµ that has merged tx/rx enable. ULONGLONG in case we also want it for others.
	ULONGLONG ullRxEnable;
	WORD awPulseDelay[g_iOEMPAApertureElementCountMaxPerBoard];	// only needed for PAmicro rn.
	WORD awPulseWidth[g_iOEMPAApertureElementCountMaxPerBoard];	// only needed for PAmicro rn.
	WORD awRcvrDelay[g_iOEMPAmicroFocalCountMax][g_iOEMPAApertureElementCountMaxPerBoard];	// only needed for PAmicro rn.
	WORD awRcvrGain[g_iOEMPAApertureElementCountMaxPerBoard];	// only needed for PAmicro rn.
}structCycleParameterPA;

typedef enum enumCycleCscan { eCscanHW, eCscanSW, eCscanHWmax } enumCycleCscan;

