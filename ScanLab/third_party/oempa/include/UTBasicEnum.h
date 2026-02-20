
#pragma once

#define STRING_ARRAY_SIZE	L".count"

const int g_iSlaveCountMax = 32;
const int g_iOEMPADriverCountMax=8;
const unsigned int g_uAmpMultiPeakCountMax = 64;
const int m_iNameSize=27+1;

const int g_iOEMPAApertureDWordCount=4;//4*32=64 elements (with a MUX only, without MUX it is 64 elements).

///////////////////////////////////////////////////////////////////////////////////////
// ENUMERATIONS
///////////////////////////////////////////////////////////////////////////////////////

enum enumSharedEncoder{				eNoSharedEncoder,//encoder is not used.
									eNewSharedEncoder,//new free shared encoder (for example eSharedEncoder00 if it has not been used).
									eSharedEncoder00,
									eSharedEncoder01,
									eSharedEncoder02,
									eSharedEncoder03,
									eSharedEncoder04,
									eSharedEncoder05,
									eSharedEncoder06,
									eSharedEncoder07,
									eSharedEncoder08,
									eSharedEncoder09,
									eSharedEncoder10,
									eSharedEncoder11,
									eSharedEncoder12,
									eSharedEncoder13,
									eSharedEncoder14,
									eSharedEncoder15,
									eSharedEncoder16,
									eSharedEncoder17,
									eSharedEncoder18,
									eSharedEncoder19,
									eSharedEncoder20,
									eSharedEncoder21,
									eSharedEncoder22,
									eSharedEncoder23,
									eSharedEncoder24,
									eSharedEncoder25,
									eSharedEncoder26,
									eSharedEncoder27,
									eSharedEncoder28,
									eSharedEncoder29,
									eSharedEncoder30,
									eSharedEncoder31
						};

enum enumAcquisitionState{			eAcqOff,	//pulse shot is disabled.
									eAcqOn,		//pulse shot is enabled.
									eAcqContinue,//HW state is not modified.
									eAcqDefault//the configuration file is used to stop or start the pulse shot.

									};
enum enumCheckingMode { eCheckDisabled, eCheckLowLevel, eCheckMediumLevel, eCheckBoth };
enum enumHardwareLink{eUnlinked,eMaster,eSlave};
enum enumCommunication{	eNoCommunication,eTCP,ePCIe,eUDP,eUSB };
enum enumConnectionState{	eDisconnected,eConnected };
enum enumUpdateStatus{	eOutOfDate,eUpToDate };
enum enumStreamCommunicationMode{ eSingle,eSort,eFifo };
enum enumHWReadAccessMode{ eNoMemory,eRequestHW,eReadSW };
enum enumAcquisitionFlush{	eAutomatic,ePooling };

enum enumFieldStreamIndex {
		indexStreamFlag =	(int) 0x00000,
		indexStreamSize =	(int) 0x00001,
		indexStreamText =	(int) 0x00002
		};
enum enumSubStreamId {
		idSubStreamIO =			(int) 0x01,
		idSubStreamCscan =		(int) 0x02,
		idSubStreamAscan =		(int) 0x03,
		idSubStreamParameters =	(int) 0x04
		};



//those values are stored in file.
enum enumClassID{	eCUTBaseClass=10,

							eCUTPulser=129,eCUTAcquisitionInfo=130,eCUTGate=131,
							//eCUTCscanGate=132,
							eCUTReceiver=133,eCUTPulserReceiver=134,eCUTScan=135,eCUTProbe=136,eCUTChannels=137,
							eCUTFocalLaw=138,
#ifdef KERNEL_API_HWDEVICE
							eCUTDevice=139,eCUTDeviceMonitor=140,
#endif //KERNEL_API_HWDEVICE
							eCUTAxis=144,
eCUTAcquisitionData=145,
eCUTDisplayScreen=146,eCUTDisplayView=147,eCUTDisplayWindow=148,
eCUTDisplayCursor=149,eCUTDisplayZoom=150,
							eCUTDisplayLayout=151,
							eCUTEncoder=152,

							eCUTWizardProbe=160,eCUTWizardSpecimen=161,eCUTWizardWedge=162,
							eCUTWizardSystem=163,eCUTWizardAperture=164,eCUTWizardVector=165,
							eCUTWizardFocalLaw=166,eCUTWizardScan=167,eCUTWizardAcquisition=168,
							eCUTModule=169,
eCUTChannelsSimulator=170,
							eCUTPreference=171,
							//eCUTReservedForFuture=172,

							eCUTLinkId=180,eCUTKernelListLinkId=181,


							eCUTDeviceOEMPA=240,eCUTFilterOEMPA=241,

							//see also enum "enumRootType".
							eKernelAcquisitionBuffer2=256,
							eLastClassID=512,eMaxClassID=0xffff

							};

enum enumRootType{	eRootTypeUnknown=0,

							
							eRootTypeAxis=eCUTAxis, eRootTypeAcquisitionData=eCUTAcquisitionData,
							eRootTypeDisplayCursor=eCUTDisplayCursor, eRootTypeDisplayZoom=eCUTDisplayZoom, eRootTypeDisplayLayout=eCUTDisplayLayout,
							eRootTypeChannels=eCUTChannels,eRootTypeWizardSystem=eCUTWizardSystem,//eKernelWizardScan=eCUTWizardScan,
							eRootTypeEncoder=eCUTEncoder,eRootTypePreference=eCUTPreference,
#ifdef KERNEL_API_HWDEVICE
							eRootTypeDevice=eCUTDevice,
#endif //KERNEL_API_HWDEVICE
							//eRootTypeReservedForFuture=eCUTReservedForFuture,

							eRootTypeAcquisitionBuffer=256,
							eRootTypePath=384, eRootTypeExtendParameter=385
						};

enum enumVersionType{eVersionFile,eVersionProduct};
enum enumVersionWord{eMajorMSWord,eMajorLSWord,eMinorMSWord,eMinorLSWord};
enum enumUTFormat { eNone, eFileBinary, eFileText, eSharedMemory };
enum enumProperty{eGetComment,eGetPath,eGetRoot,eGetBaseLimit,eCheckLinkId,eSetLinkId,eUpdateFromObject};
enum enumCallback{eCallbackCall,eCallbackWndMessage,eCallbackReplay,eCallbackDone};

#define ACQUISITION_MODE_STANDARD			0x00000001
#define ACQUISITION_MODE_VIAFIFOSTREAM		0x00000002
#define ACQUISITION_MODE_VIAMASTER			0x00000004
#define ACQUISITION_MODE_ASSOCIATION		0x00000008

enum enumBitSize {e8Bits, e14Bits, e16Bits, eLog8Bits};
//PA1 "e14Bits" means "e12Bits"
#define e12Bits			e14Bits
//MC2 "e14Bits" means "e27Bits"
#define e27Bits			e14Bits

enum enumAscanRequest {eAscanAll, eAscanSampled, eBscanOnLine, eAscanVideo=eAscanSampled};
enum enumCompressionType {eCompression,eDecimation};
enum enumGateModeAmp{eAmpAbsolute,eAmpMaximum,eAmpMinimum,eAmpPeakToPeak};
enum enumGateModeTof{eTofAmplitudeDetection,//"AMP's TOF" : where the AMP result has been found, for Peak-Peak--> where Max has been found
							eTofThresholdCross,//"TH cross": first cross of the THRESHOLD  
							eTofZeroFirstAfterThresholdCross,//"ZrA": first time crossed 0 after crossing THRESHOLD
							eTofZeroLastBeforeThresholdCross,//"ZrB": last time crossed 0 before crossing THRESHOLD
							eTofMultiPeak
							};
enum enumGateTarget { eHWSW /*default*/, eHW, eSW };
enum enumGateTracking { eTrackingDefault = 0, eTrackingFromHW = 1 };
enum enumRectification{
						eSigned,			//Rectification: RF --> not rectified, signed value,
						eUnsigned,			//FW --> rectified, unsigned
						eUnsignedPositive,	//HWP --> only positive, unsigned,
						eUnsignedNegative	//HWN --> only negative
						};

enum enumProbeMode{	ePulseEcho,//one probe is used to emit and receive.
							ePulseEchoSeparate,//two probes are on the same element : one to emit and another one to receive.
							ePulseOnly,
							eEchoOnly};
enum enumFocusing{eStandard,eDDF};
enum enumTrigger{
					eTimer,//wait timer before emitting the pulse.
					eEncoderXOneWay,//wait encoder moving (one way only) before emitting the pulse.
					eEncoderXBothWay,//wait mechanical moving (forward or backward) before emitting the pulse.
					eEncoderYOneWay,//wait encoder moving (one way only) before emitting the pulse.
					eEncoderYBothWay,//wait mechanical moving (forward or backward) before emitting the pulse.
					eExternal,//wait external pulse.
					eSoftware//the SW trig the shot.
						};
enum enumFeatureDigitalInput {
	eDigitalInputWire1 = 0,
	eDigitalInputWire2 = 1,
	eDigitalInputEncoder2Wire1 = 2,
	eDigitalInputEncoder2Wire2 = 3,
	eDigitalInputEncoder3Wire1,
	eDigitalInputEncoder3Wire2,
	eDigitalInputEncoder4Wire1,
	eDigitalInputEncoder4Wire2,
	eDigitalInputExternalCycle,
	eDigitalInputExternalSequence,
	eDigitalInputBlanking,
	eDigitalInputPresetRising,
	eDigitalInputSpeed1,
	eDigitalInputSpeed2,
	eDigitalInputEncoder2PresetRising,
	eDigitalInputEncoder3PresetRising,
	eDigitalInputEncoder4PresetRising,
	eDigitalInputExternalTimestampSet,
	eDigitalInputExternalResetEncoder1,
	eDigitalInputExternalResetEncoder2,
	eDigitalInputExternalEncoderReset,
	eDigitalInputExternalTrackingReset,
	eDigitalInputLast
};
typedef enumFeatureDigitalInput enumIndexDigitalInput;

enum enumDigitalInput{
					eDigitalInputOff,
					eDigitalInput01,
					eDigitalInput02,
					eDigitalInput03,
					eDigitalInput04,
					eDigitalInput05,
					eDigitalInput06,
					eDigitalInput07,
					eDigitalInput08,
					eDigitalInput09,
					eDigitalInput10,
					eDigitalInput11,
					eDigitalInput12,
					eDigitalInput13,
					eDigitalInput14,
					eDigitalInput15,
					eDigitalInput16,
					eDigitalInput17,
					eDigitalInput18,
					eDigitalInput19,
					eDigitalInput20,
					eDigitalInput21,
					eDigitalInput22,
					eDigitalInput23,
					eDigitalInput24,
					eDigitalInput25,
					eDigitalInput26,
					eDigitalInput27,
					eDigitalInput28,
					eDigitalInput29,
					eDigitalInput30,
					eDigitalInput31,
					eDigitalInput32
						};
enum enumEncoderType{
					eStaticScan,	//offset are used to store the data (no encoder).
					eEncoderQuadrature,	//encoder are used to store the data (quadrature).
					eEncoderQuadrature4Edges,//encoder are used to store the data (quadrature).
					eEncoderDirectionCount,	//encoder : one signal for the direction and one signal for the count.
					eEncoderForwardBackward,	//encoder : one signal for the forward and one signal for the back.
					eSpeedMeasurement //OnLine.
						};
enum enumInternalMode{
					eInternalOff, //Off.
					eInternalStandAlone,//for one encoder that has not complementary encoder.
					eInternal1,//with two axis, first internal increment.
					eInternal2//with two axis, second internal increment.
						};
enum enumArrayParamAccess{
					eNoParam,
					eParamInput,
					eParamOutput
						};
enum enumGenericAccess{
					eOverwrite,
					eMaximum,
					eMinimum,
					eBitwiseOr,//same than eMaximum (bitwise version).
					eBitwiseAnd//same than eMinimum (bitwise version).
						};
enum enumDataType{
					eBitwiseByte,//bit access, sizeof=1 BYTE (usefull for alarm data type).
					eBitwiseWord,//bit access, sizeof=2 WORD (usefull for alarm data type).
					eBitwiseDword,//bit access, sizeof=4 DWORD (usefull for alarm data type).
					eChar,//char, sizeof=1
					eUChar,//unsigned char, sizeof=1
					eShort,//short, sizeof=2
					eUShort,//unsigned short, sizeof=2
					eLong,//LONG, sizeof=4
					eULong//ULONG, sizeof=4
						};
enum enumAxis{
					eA,//amplitude axis for amplitude data or time of flight data.
					eX,//scan axis
					eY,//index axis
					eZ,//ultrasound axis
					eRho,//used instead of eY with polar coordinate (for cylindar specimen).
					eTheta//used instead of eZ with polar coordinate (for cylindar specimen).
					};

enum enumHistoricIndex{	eIndexX,
									eIndexY,
									eIndexXY,
									eIndexError
									};

enum enumUnit{	eNoUnit,eHexadecimal,ePercent,eMeter,eMilliMeter,eSecond,eMilliSecond,eMicroSecond,eNanoSecond,
						eMeterPerSecond,eRadian,eDegree,eDecibel,eHertz,eKiloHertz,eMegaHertz,eVolt,
						eBytePerSecond,eKiloBytePerSecond,eMegaBytePerSecond,eDegreeCelsius,eLinkRootId,
						eBinary,eStepPerMilliMeter,
						eLastUnit };

enum enumDisplayType{
					eYZ,//Bscan
					eXY,//Cscan
					eXZ,//Dscan
					eProfileZ,//Ascan
					eProfileX,//Profile Cscan
					eProfileY//Profile Cscan
						};

enum enumConfigurationSelection{
	eSave,
	eLoad,
	eDelete
};

enum enumApply{
	eStandby,
	ePending,
	eDone
};

enum enumKeepAlive{
	eKeepAliveOff,
	eKeepAliveHardwareAndComputer,
	eKeepAliveHardwareOnly,
	eKeepAliveComputerOnly
};

///////////////////////////////////////////////////////////////////////

enum enumOEMPATrigger{
	eOEMPAInternal,//encoder and external signals are not used.
	eOEMPAEncoder,//encoder 1 is used for the sequence (cycle is internal).
	eOEMPAExternalCycle,//the next cycle after the last cycle is for the next sequence.
	eOEMPAExternalSequence,//sequence is coming from external pulse (cycle are internal).
	eOEMPAExternalCycleSequence,//cycle and sequence are coming from external signals.
	eOEMPASoftware//the computer trig the device by himself.

};

enum enumOEMPAEncoderDirection{
	eOEMPAUpDown,//pulser is triggered for both directions.
	eOEMPAUpOnly,//pulser is triggered only if encoder goes up.
	eOEMPADownOnly//pulser is triggered only if encoder goes down.

};

enum enumOEMPARequestIO{
	eOEMPANotRequired=0,
	eOEMPAOnCycleOnly,//use this value if you want Ascan with encoder.
	eOEMPAOnSequenceOnly,
	eOEMPAOnDigitalInputOnly,
	eOEMPAOnDigitalInputAndCycle,//use this value if you want Ascan with encoder and digital inputs.
	eOEMPAOnDigitalInputAndSequence

};

// Same filters for MC series but order 32.
enum enumOEMPAFilter{
	eOEMPAFilterCustom,
	eOEMPAHighPassOrder64Cut1Mhz,
	eOEMPAHighPassOrder64Cut2Mhz,
	eOEMPAHighPassOrder64Cut3Mhz,
	eOEMPAHighPassOrder64Cut4Mhz,
	eOEMPAHighPassOrder64Cut5Mhz,
	eOEMPAHighPassOrder64Cut6Mhz,
	eOEMPAHighPassOrder64Cut7Mhz,
	eOEMPAHighPassOrder64Cut8Mhz,
	eOEMPAHighPassOrder64Cut9Mhz,
	eOEMPAHighPassOrder64Cut10Mhz

};

enum enumOEMPAFilterIndex{
	eOEMPAFilterOff,
	eOEMPAFilter1,
	eOEMPAFilter2,
	eOEMPAFilter3,
	eOEMPAFilter4,
	eOEMPAFilter5,
	eOEMPAFilter6,
	eOEMPAFilter7,
	eOEMPAFilter8,
	eOEMPAFilter9,
	eOEMPAFilter10,
	eOEMPAFilter11,
	eOEMPAFilter12,
	eOEMPAFilter13,
	eOEMPAFilter14,
	eOEMPAFilter15

};
const int g_iEnumOEMPAFilterIndexLast=eOEMPAFilter15+1;

enum enumOEMPA2LPFMHz {
	eMHz24_17 = 1,
	eMHz20_83 = 3,
	eMHz18_83 = 5,
	eMHz16_67 = 6,
	eMHz16_11 = 16,
	eMHz15_00 = 8,
	eMHz13_89 = 18,
	eMHz13_33 = 10,
	eMHz12_56 = 20,
	eMHz12_08 = 32,
	eMHz11_11 = 22,
	eMHz10_42 = 34,
	eMHz10_00 = 24,
	eMHz9_42 = 36,
	eMHz8_89 = 26,
	eMHz8_33 = 28,
};
const int LPFMHzEnumToValue[] = { 1, 3, 5, 6, 16, 8, 18, 10, 20, 32, 22, 34, 24, 36, 26, 28 };

enum enumOEMPA2HPFDivider {
	eDiv12,
	eDiv9,
	eDiv6,
	eDiv3
};

enum enumOEMPAMappingDigitalInput{
	eOEMPANotUsed,
	eOEMPAEncoder1A,
	eOEMPAEncoder1B,
	eOEMPAEncoder2A,
	eOEMPAEncoder2B,
	eOEMPAExternalTriggerCycle,
	eOEMPAExternalTriggerSequence,
	eOEMPADigitalInput0,
	eOEMPADigitalInput1,
	eOEMPADigitalInput2,
	eOEMPADigitalInput3,
	eOEMPADigitalInput4,
	eOEMPADigitalInput5,
	eOEMPAResetTrackingTable

};

enum enumOEMPA2MappingDigitalInput {
	eOEMPA2NotUsed,
	eOEMPA2Encoder1A,
	eOEMPA2Encoder1B,
	eOEMPA2Encoder2A,
	eOEMPA2Encoder2B,
	eOEMPA2ExternalTriggerCycle,
	eOEMPA2ExternalTriggerSequence,
	eOEMPA2DigitalInput,
	eOEMPA2Encoder3A = 0xb,
	eOEMPA2Encoder3B,
	eOEMPA2ResetTrackingTable,
	eOEMPA2Encoder4A,
	eOEMPA2Encoder4B

};


enum enumOEMPAMiniMappingDigitalIO {
	eOEMPAMiniNotUsed,
	eOEMPAMiniInEncoder1A,
	eOEMPAMiniInEncoder1B,
	eOEMPAMiniInEncoder2A,
	eOEMPAMiniInEncoder2B,
	eOEMPAMiniInSignalCycle,
	eOEMPAMiniInSignalSequence,
	eOEMPAMiniInDigitalInput,
	eOEMPAMiniInTrackingReset,
	eOEMPAMiniInEncoderReset,
	eOEMPAMiniOutLow,
	eOEMPAMiniOutHigh,
	eOEMPAMiniOutSignalCycle,
	eOEMPAMiniOutSignalSequence,
	eOEMPAMiniOutTemperatureAlarm,
	eOEMPAMiniOutDebouncedIn1 = 0x10,	// There is nothing for 0xF
	eOEMPAMiniOutDebouncedIn2,
	eOEMPAMiniOutDebouncedIn3,
	eOEMPAMiniOutDebouncedIn4,
	eOEMPAMiniOutDebouncedIn5,
	eOEMPAMiniOutDebouncedIn6,
	eOEMPAMiniOutDebouncedIn7,
	eOEMPAMiniOutDebouncedIn8,
	eOEMPAMiniInTimeStampSet,//0x18
	eOEMPAMiniInResetEncoder1,
	eOEMPAMiniInResetEncoder2

};

enum enumOEMPAMappingDigitalOutput {
	eOEMPALow,
	eOEMPAHigh,
	eOEMPASignalCycle,
	eOEMPASignalSequence,
	eOEMPATemperatureAlarm

};

enum enumOEMPARequestCscan{
	eOEMPACycle,
	eOEMPASequence

};

enum enumOEMPAAnalogBandwidth{
	eLow,
	eHigh
};

///////////////////////////////////////////////////////////////////////

enum enumEvent{
					eEventNew=0,//new identifier has been allocated (shared data with single name).
					eEventPostNew=1,//new identifier has been allocated (shared data with single name).
					eEventPreDelete=2,//identifier is going to be desallocated (shared data removed).
					eEventDelete=3,//shared data has been removed.
					eEventReName=4,//an instance has been renamed (identifier has been allocated for shared data).
					eEventAlloc=5,//acquisition buffer : alloc (notification after allocating).
					eEventFree=6,//acquisition buffer : free (notification before releasing).
					eEventTrace=7,//system and user information (debug purpose).
					eEventPreUpdate=8,//a shared data is going to be updated.
					eEventUpdate=9,//a shared data has been updated.
					eEventSave=10,//used to filter "Save()" in shared memory only one is required at the end of all operations.
					eEventLoad=11,
					eEventPostLoad=12,
					eEventLanguage=13,//language has been changed.
					eEventAll=32,//last item, for previous one (check of the path is required for callback registration).
					eEventParametersFWAcqId=33,//update "CUTAcquisitionInfo".
					eEventBufferReqFree=34,//used to dispatch event process to close.
					eEventBufferReqAlloc=35,//used to dispatch event process to open.
					eEventBufferAllocated=36,//notification (acquisition buffer data has been opened). eEventFree 
					eEventBufferFreed=37,//notification (acquisition buffer data has been closed).
					eEventBufferPosition=38,//you will be able to set the acquisition buffer position where to store acquisition data.
					eEventRefreshUpdate=39,//acquisition refresh occured.
					eEventDisplayRootId=40,//display kernel object (RootId is given by lParam).
					eEventDeviceConnected=41,//device connection.
					eEventDeviceDisconnected=42,//device disconnection.
					eEventUser0=256 //user have to use value over this one.
						};

///////////////////////////////////////////////////////////////////////////////////////////////

enum enumSpecimen{
			ePlane,	//the referential point (0,0,0) is on the front surface. X is the mechanical scan axis.
			eDisk, //same than 2D bar
			eBar, //the referential point (0,0,0) is on the axis of the part, the X axis is the main axis of the bar.
			eTube //tube in the future. //same referential than the bar.
			};

enum enumCoordinate{
			eCartesian,//In case of plane specimen cartesian coordinates are used.
							//X : scan axis.
							//Y : index axis (0 is the reference point of the probe).
							//Z : ultrasound path, the probe have a positive value.
			ePolar	//In case of bar or tube specimen polar coordinates are used.
							//X : scan axis.
							//θ : angle (0 is the reference point of the probe).
							//Z : ultrasound path (0 on the bar axis).
			};

enum enumOffsetType{
			eDistance,//In case of plane specimen cartesian coordinates are used.
			eArcLength,//In case of bar or tube the OffsetY could be measured on the bar radius.
			eAngle//In case of bar or tube the OffsetY could be defined with an angle.
			};

enum enumWizardProbe{
			eMono,
			eLinear1D,
			eLinear2D,
			eCustomTRL,
			eCustom,
			eLinear1D_NextAfterLastIsFirst
			};

enum enumAcquisitionWizardMode{
										eCreateAcquisitionDataAndAxis,
										eUseExistingAcquisitionData
								};

enum enumAcquisitionDataType{
										eAscan,
										eCscanAmplitude,
										eCscanTimeOfFlight,
								};

enum enumAcquisitionMode_{	eOffset,//use the distance offset of the focal law.
									eIndex//use the offset as an index.
									};

enum enumAcquisitionDataMode{
										eMerge,		//=> eEncoderAndFocalPoint for X AND/OR Y; eScanOrder for X OR Y.
										eSeparate	//=> eEncoderOnly for X AND/OR Y; 
								};

enum enumAcquisitionEncoderMode {eStatic,
										eEncoderOnly,
										eEncoderAndFocalPoint,
										eScanOrder
								};
enum enumDepthMode {eStandardDepth,eSoundPath,eDepthBeforeBackwall,eDepthAfterBackwall,ePathBeforeProbe,eDepthBigBar,eProjection};
enum enumScanMode { eLinear, eSector, eSpread };
enum enumWave {eLongitudinal,eTransverse};
enum enumScan {	eScanFirst,eScanDepth,eScanAngle,eScanSkew,eScanOffset1,eScanOffset2,
						eScanLast};
				//"eScanApertureCallback" is used to get index list for "eCustom" probe.

//////other private kernel enumerations///////

enum enumReferential{
			eSpecimen=0,//absolute referential (inspection referential).
			eWedge=1,//usefull for bar and tube (tangent on the interface).
			eProbe=2,//referential of the probe, used to define it.
			eReferentialCount
			};

enum enumUserMode{
			eUser,
			eAdvanced,
			eSupervisor
			};

enum enumTFMOptions{ eCPU=0,eGPU=1,eCPU_1Thread=2 };
enum enumTFMParameters{ eTFMOff=0,eFlatContact_Linear1D=1 };
enum enumAcquisitionFifo{ eNoFifo, eFifoAscan, eFifoCscan, eFifoIO, eFifoStream };
enum enumAWGStateOEMMC2 { eOEMMC_AWG_HiZ, eOEMMC_AWG_plus, eOEMMC_AWG_RTZ, eOEMMC_AWG_minus };
enum enumSetupFileType { eNoFileType, eFilePA, eFileFMC, eFileMC1, eFileMC2, eFileMCu, eFileMC2Bipolar };
enum enumSimdDataType {
	eFloat,		/*!< Base implementation, slowest but always available. */
	eSSE,		/*!< Vector of 4 floats, available since 2000 for Intel and AMD processors. */
	eAVX,		/*!< Vector of 8 floats, available from Intel's Sandy Bridge (Q1 2011) and AMD's Bulldozer (Q4 2011) microarchitectures. */
	eAVX512		/*!< Vector of 16 floats, available for some Intel's microarchitecture from 2017 (Skylake) to 2021 (Rocket Lake) and AMD Zen 4 and 5 (2022 to now). */
};
enum enumPulseType { eBipolar, eUnipolar };

/////////////////////////////////////////////////////////////////
