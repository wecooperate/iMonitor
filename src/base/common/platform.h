//******************************************************************************
/*++
	FileName:		platform.h
	Description:

--*/
//******************************************************************************
#ifndef __platform_5439dcbd_cff5_473e_911c_b76c7dee25a0__
#define __platform_5439dcbd_cff5_473e_911c_b76c7dee25a0__
//******************************************************************************
#ifdef __ANDROID__
#define OS_ANDROID 1
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if defined(TARGET_OS_OSX) && TARGET_OS_OSX
#define OS_MACOSX 1
#endif
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define OS_IOS 1
#endif
#elif defined(__linux__)
#define OS_LINUX 1
#elif defined(_WIN32)
#define OS_WIN 1
#elif defined(__GNUC__)
#define OS_LINUX 1
#else
#error Not Support
#endif
//******************************************************************************
#if OS_WIN
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif
//******************************************************************************
#ifdef BASE_EXPORT
#define BASE_API DLL_EXPORT
#else
#define BASE_API
#endif
//******************************************************************************
#ifdef _DEBUG
#ifndef DEBUG
#define DEBUG
#endif
#endif
//******************************************************************************
#ifndef DCHECK
#include <assert.h>
#define DCHECK(condition) assert(condition);
#endif
//******************************************************************************
#ifdef DEBUG
#define DEBUG_EXPORT extern "C" DLL_EXPORT
#else
#define DEBUG_EXPORT inline
#endif
//******************************************************************************
#include <stdint.h>
#include <stdarg.h>
#include <assert.h>
//******************************************************************************
#if OS_WIN
#include "platform/windows.h"
#endif
//******************************************************************************
#ifdef min
#undef min
#undef max
#endif
//******************************************************************************
using std::min;
using std::max;
//******************************************************************************
#endif
