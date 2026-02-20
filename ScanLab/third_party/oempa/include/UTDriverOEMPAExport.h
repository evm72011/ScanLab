
#pragma once

#ifdef DRIVER_OEMPA_EXPORTS
#ifndef DRIVER_OEMPA_API
#ifdef _WIN32
#define DRIVER_OEMPA_API __declspec(dllexport)
#define DRIVER_OEMPA_API_ALIGN __declspec(dllexport) __declspec(align(8))
#elif defined __linux__
#define DRIVER_OEMPA_API __attribute__((visibility ("default")))
#define DRIVER_OEMPA_API_ALIGN __attribute__((visibility ("default"))) __attribute__((aligned(8)))
#endif // __linux__
#endif
#else

#ifndef DRIVER_OEMPA_API
#ifdef _WIN32
#define DRIVER_OEMPA_API __declspec(dllimport)
#define DRIVER_OEMPA_API_ALIGN __declspec(dllimport) __declspec(align(8))
#elif defined __linux__
#define DRIVER_OEMPA_API
#define DRIVER_OEMPA_API_ALIGN __attribute__((aligned(8)))
#endif // __linux__
#endif
#ifndef KERNEL_DRIVER_EXPORTS

#ifndef _NO_AUTO_INCLUDE_
#ifdef _DRIVER_11XY_
#error DRIVER_11XY is obsolete
#pragma comment(lib,"UTKernelDriver.lib")
#else //_DRIVER_11XY_
#pragma comment(lib,"UTDriverOEMPA.lib")
#endif //_DRIVER_11XY_
#endif //_NO_AUTO_INCLUDE_
#endif
#endif


