#pragma once

#include "PlatformDetection.h"

#include <memory>

#ifdef KURO_DEBUG
	#if defined(KURO_PLATFORM_WINDOWS)
		#define KURO_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif // defined(KURO_PLATFORM_WINDOWS)
	#define KURO_ENABLE_ASSERTS
#else
	#define KURO_DEBUGBREAK()
#endif // KURO_DEBUG

#define BIT(x) (1 << x)

#define KURO_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Kuro
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Log.h"
#include "Assert.h"
