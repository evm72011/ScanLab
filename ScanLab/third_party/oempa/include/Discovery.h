
#pragma once

#if !defined(_COM_DECL_)
#ifdef _UTSOCK_EXPORT_
#ifdef _WIN32
#define _COM_DECL_ __declspec(dllexport)
#elif defined __linux__
#define _COM_DECL_ __attribute__((visibility ("default")))
#endif // __linux__
#else //_UTSOCK_EXPORT_

#ifdef _WIN32
#define _COM_DECL_ __declspec(dllimport)
#elif defined __linux__
#define _COM_DECL_
#endif // __linux__
#endif //_UTSOCK_EXPORT_

#endif //_COM_DECL_

#ifdef __cplusplus
extern "C" {
#endif

	// Finds what type is the device with address <ip>.
	//The type of device is returned in the <eHW> ouptut argument.
	//only works with PAmini, MC2, MCuF and PAmax.
	//due to different services, including PAmax in the discovery is significantly longer.
	//It is possible to disable PAmax discovery by passing checkPAmax = false;
	// Pinging will add a very small delay if the IP is valid but not pinging will add a very big delay if no.
	//Pass ping = true if you are not sure about the IP address.
	// Use close = false if you want to do the cleanup yourself (i.e., call CleanupDisco() when finished).
	// The call will return false if a communication error occured (and eHW will be set to 'eNoHW').
	_COM_DECL_ bool FindDeviceType(const char* ip, enumHardware& eHW, bool checkPAMax = true, bool ping = false, bool close = true);

	// Optionnal init and cleanup calls. Multiple discoveries are slightly faster if initialization/cleanup is done manually.
	//It will be done automatically in FindDeviceType if not called (and close = true).
	_COM_DECL_ void InitDisco();
	_COM_DECL_ void CleanupDisco();

#ifdef __cplusplus
}
#endif
