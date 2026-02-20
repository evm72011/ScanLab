
#pragma once

#ifdef UTKERNEL_EXPORTS
#ifndef UTKERNEL_API
#ifdef _WIN32
#define UTKERNEL_API __declspec(dllexport)
#define UTKERNEL_API_ALIGN __declspec(dllexport) __declspec(align(8))
#endif	// _WIN32
#ifdef __linux__
#define UTKERNEL_API __attribute__((visibility ("default")))
#define UTKERNEL_API_ALIGN __attribute__((visibility ("default"))) __attribute__((aligned(8)))
#endif // __linux__
#endif // !UTKERNEL_API
#else // UTKERNEL_EXPORTS
#ifndef UTKERNEL_API
#ifdef _WIN32
#define UTKERNEL_API __declspec(dllimport)
#define UTKERNEL_API_ALIGN __declspec(dllimport) __declspec(align(8))
#endif // _WIN32
#ifdef __linux__
#define UTKERNEL_API
#define UTKERNEL_API_ALIGN __attribute__((aligned(8)))
#endif // __linux__
#endif // !UTKERNEL_API
#endif // UTKERNEL_EXPORTS

