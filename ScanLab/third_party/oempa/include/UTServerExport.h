
#pragma once

#ifdef DRIVER_SERVER_EXPORTS

#ifndef ROUTE_DEVICE_API
#ifdef _WIN32
#define ROUTE_DEVICE_API __declspec(dllexport)
#define ROUTE_DEVICE_API_ALIGN __declspec(dllexport) __declspec(align(8))
#elif defined __linux__
#define ROUTE_DEVICE_API __attribute__((visibility ("default")))
#define ROUTE_DEVICE_API_ALIGN __attribute__((visibility ("default"))) __attribute__((aligned(8)))
#endif // __linux__
#endif

#else

#ifdef NO_ROUTE_DEVICE_API

#define ROUTE_DEVICE_API
#define ROUTE_DEVICE_API_ALIGN

#else

#ifndef ROUTE_DEVICE_API
#ifdef _WIN32
#define ROUTE_DEVICE_API __declspec(dllimport)
#define ROUTE_DEVICE_API_ALIGN __declspec(dllimport)
#elif defined __linux__
#define ROUTE_DEVICE_API
#define ROUTE_DEVICE_API_ALIGN __attribute__((aligned(8)))
#endif // __linux__
#endif

#endif

#endif

