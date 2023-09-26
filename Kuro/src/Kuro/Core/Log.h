#pragma once

#include "Kuro/Core/Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace Kuro
{
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define KURO_CORE_TRACE(...)			::Kuro::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KURO_CORE_INFO(...)				::Kuro::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KURO_CORE_WARN(...)				::Kuro::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KURO_CORE_ERROR(...)			::Kuro::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KURO_CORE_FATAL(...)			::Kuro::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define KURO_TRACE(...)					::Kuro::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KURO_INFO(...)					::Kuro::Log::GetClientLogger()->info(__VA_ARGS__)
#define KURO_WARN(...)					::Kuro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KURO_ERROR(...)					::Kuro::Log::GetClientLogger()->error(__VA_ARGS__)
#define KURO_FATAL(...)					::Kuro::Log::GetClientLogger()->fatal(__VA_ARGS__)
