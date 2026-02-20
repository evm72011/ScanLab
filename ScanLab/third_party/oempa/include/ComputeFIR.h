
#pragma once
#define _cplusplus		//Currently, this function only supports C++

#ifdef _cplusplus
#define EXTERN_C extern "C"		//Inform _declspec that variables may be defined external to the dll
#else
#define EXTERN_C

#endif


#ifdef COMPUTEFIR_EXPORTS								//When debugging, COMPUTEFIR_EXPORTS is defined, setting _declspec to dllexport
#define COMPUTEFIR_API EXTERN_C __declspec(dllexport)
#else //		//If called from another application, set _declspec to import
#define COMPUTEFIR_API EXTERN_C __declspec(dllimport)
#endif


typedef enum {eLowPass=0,eHighPass=1,eBandPass=2,eBandReject=3} enumFilterBand;
const int g_iDEFAULT_ORDER_FIR = 64;
const int g_iDEFAULT_ORDER_FIR_HW = 34;
const int g_iMC_ORDER_FIR = 32;
const int g_iMC_ORDER_FIR_HW = 18;

namespace CComputeFIR
{
COMPUTEFIR_API double GetSampleFrequency();
COMPUTEFIR_API void SetSampleFrequency(double dValue);

//Main function for calculating FIR coefficients (order=64, sample frequency=50 MHz, use computeFIRcoefficientsKaiser32_50MHz for OEMMC)
COMPUTEFIR_API bool computeFIRcoefficientsKaiser64_50MHz(double att, enumFilterBand eBand, double fc1, double fc2, short int hk[g_iDEFAULT_ORDER_FIR_HW], WORD &wScaleCoef, int FNameSize, char *FName);
//Function for calculating FIR coefficients for OEMMC (order=32, sample frequency=50 MHz)
COMPUTEFIR_API bool computeFIRcoefficientsKaiser32_50MHz(double att, enumFilterBand eBand, double fc1, double fc2, short int hk[g_iMC_ORDER_FIR_HW], WORD& wScaleCoef, int FNameSize, char* FName);
//-----------------------------------------------------------------------
	// PARAMETERS:
	// att			: attenuation of the stop band in dB
	// eBand		: type of filter {eLowPass=0,eHighPass=1,eBandPass=2,eBandReject=3}
	// fc1			: cut-off frequency 1 (unit=MHz)
	// fc2			: cut-off frequency 2 (effective for all types of filters, unit=MHz)
	// hk			: output coefficients
	// wScaleCoef	: output scaling coefficient (integer).
	// FNameSize	: input size of output buffer FName.
	// FName		: output filter description name (string)
	//-----------------------------------------------------------------------
COMPUTEFIR_API bool _computeFIRcoefficientsKaiser64_50MHz(double att, enumFilterBand eBand, double fc1, double fc2, short int hk[g_iDEFAULT_ORDER_FIR], int ScaleCoefSize, char *ScaleCoef, int FNameSize, char *FName);
COMPUTEFIR_API bool _computeFIRcoefficientsKaiser32_50MHz(double att, enumFilterBand eBand, double fc1, double fc2, short int hk[g_iMC_ORDER_FIR], int ScaleCoefSize, char* ScaleCoef, int FNameSize, char* FName);
	// PARAMETERS:
	// att			: attenuation of the stop band in dB
	// eBand		: type of filter {eLowPass=0,eHighPass=1,eBandPass=2,eBandReject=3}
	// fc1			: cut-off frequency 1 (unit=MHz)
	// fc2			: cut-off frequency 2 (effective for all types of filters, unit=MHz)
	// hk			: output coefficients
	// ScaleCoefSize: input size of output buffer ScaleCoef.
	// ScaleCoef	: output scaling coefficient (string) first function
	// FNameSize	: input size of output buffer FName.
	// FName		: output filter description name (string)
COMPUTEFIR_API bool computeFIRcoefficientsKaiser(double att, enumFilterBand eBand, int order, double fs, double fc1, double fc2, double *h);

//Check-functions to ensure input is of proper form
COMPUTEFIR_API bool CheckInputCutoff(enumFilterBand eBand, double fc1, double fc2);

};

