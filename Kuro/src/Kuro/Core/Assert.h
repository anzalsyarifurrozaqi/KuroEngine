#pragma once

#ifdef KURO_ENABLE_ASSERTS
	#define KURO_ASSERT(x, ...) {if(!(x)) { KURO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define KURO_CORE_ASSERT(x, ...) {if(!(x)) { KURO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define KURO_ASSERT(x, ...)
	#define KURO_CORE_ASSERT(x, ...)
#endif // KURO_ENABLE_ASSERTS
