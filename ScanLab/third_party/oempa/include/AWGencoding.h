
#pragma once
#include "UTDriverOEMPAExport.h"

//--------------------------------------------------------------------------------------------------------------//
// Function to generate an unipolar signal with Nt points
// Fs[In]: sampling frequency (MHz)
// Nt[In]: number of points, Nt = (Fs / F0) * Nper.
// F0[In]: center frequency (MHz)
// x[Out]: output signal with Nt points
DRIVER_OEMPA_API void generateUnipolarPulse(double Fs, int Nt, double F0, double* x);
DRIVER_OEMPA_API void generateUnipolarPulse(double Fs, int Nt, double F0, int* x);

//--------------------------------------------------------------------------------------------------------------//
// Function to generate a bipolar signal with Nt points
// Fs[In]: sampling frequency (MHz)
// Nt[In]: number of points, Nt = (Fs / F0) * Nper.
// F0[In]: center frequency (MHz)
// Nper[In]: number of cycles.
// x[Out]: output signal with Nt points
DRIVER_OEMPA_API void generateBipolarPulse(double Fs, int Nt, double F0, double* x);
DRIVER_OEMPA_API void generateBipolarPulse(double Fs, int Nt, double F0, int Nper, double* x);
DRIVER_OEMPA_API void generateBipolarPulse(double Fs, int Nt, double F0, int Nper, double dutyCycle, double* x);
DRIVER_OEMPA_API void generateBipolarPulse(double Fs, int Nt, double F0, int* x);
DRIVER_OEMPA_API void generateBipolarPulse(double Fs, int Nt, double F0, int Nper, int* x);
DRIVER_OEMPA_API void generateBipolarPulse(double Fs, int Nt, double F0, int Nper, double dutyCycle, int* x);

//--------------------------------------------------------------------------------------------------------------//
// Function to generate a burst signal with Nt points
// Fs[In]: sampling frequency (MHz)
// Nt[In]: number of points, Nt = (Fs / F0) * Nper.
// F0[In]: center frequency (MHz)
// Nper[In]: number of periods
// phi[In]: phase shift (rad)
// x[Out]: output signal with Nt points
DRIVER_OEMPA_API void generateBurst(double Fs, int Nt, double F0, int Nper, double phi, double *x);

//--------------------------------------------------------------------------------------------------------------//
// Function to generate a Chirp signal with Nt points
// Fs[In]: sampling frequency (MHz)
// Nt[In]: number of points 
// F1[In]: lower-bound frequency (MHz)
// F2[In]: higher-bound frequency (MHz)
// phi[In]: phase shift (rad)
// x[Out]: output signal with Nt points
DRIVER_OEMPA_API void generateChirp(double Fs, int Nt, double F1, double F2, double phi, double *x);

//--------------------------------------------------------------------------------------------------------------//
// Function to generate a Gaussian signal with Nt points
// Fs[In]: sampling frequency (MHz)
// Nt[In]: number of points 
// F0[In]: center frequency (MHz)
// BWR[In]: bandwidth ratio (%)
// phi[In]: phase shift (rad)
// x[Out]: output signal with Nt points
DRIVER_OEMPA_API void generateGaussian(double Fs, int Nt, double F0, double BWR, double phi, double *x);

