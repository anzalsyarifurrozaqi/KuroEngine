#pragma once

#ifdef KURO_PLATFORM_WINDOWS
	#ifdef KURO_BUILD_DLL
			#define KURO_API __declspec(dllexport)
		#else
			#define KURO_API __declspec(dllimport)
	#endif // KURO_BUILD_DLL
#else
	#error Game Engine only support windows!

#endif // KURO_PLATFORM_WINDOWS

#ifdef KURO_DEBUG
	#define KURO_ENABLE_ASSERTS
#endif // KURO_DEBUG

#ifdef KURO_ENABLE_ASSERTS
	#define KURO_ASSERT(x, ...) {if(!(x)) {KURO_ERROR("Assertion Failed: {0}", __VA__ARGS); __debugbreak(); }}
	#define KURO_CORE_ASSERT(x, ...) {if(!(x)) { KURO_CORE_ERROR("Assertion Failed: {0}". __VA_ARGS__); __debugbreak(); }}
#else
	#define KURO_ASSERT(x, ...)
	#define KURO_ASSERT(x, ...)
#endif // KURO_ENABLE_ASSERTS

