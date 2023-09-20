#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Kuro
{
	class KURO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
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