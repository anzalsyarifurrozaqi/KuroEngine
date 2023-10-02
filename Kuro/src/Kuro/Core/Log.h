#pragma once

#include "Kuro/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

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

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

template <typename OStream, typename T>
inline OStream& operator<<(OStream& os, std::remove_reference_t<T>& value)
{
	if constexpr (std::is_same_v<std::decay_t<T>, const unsigned char*>) 
	{
		const unsigned char* s = value;
		return os << reinterpret_cast<const char*>(s);
	}
	else 
	{
		return os << std::forward<T>(value);
	}
}

// Core Log Macros
#define KURO_CORE_TRACE(...)			::Kuro::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KURO_CORE_INFO(...)				::Kuro::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KURO_CORE_WARN(...)				::Kuro::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KURO_CORE_ERROR(...)			::Kuro::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KURO_CORE_CRITICAL(...)			::Kuro::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define KURO_TRACE(...)					::Kuro::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KURO_INFO(...)					::Kuro::Log::GetClientLogger()->info(__VA_ARGS__)
#define KURO_WARN(...)					::Kuro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KURO_ERROR(...)					::Kuro::Log::GetClientLogger()->error(__VA_ARGS__)
#define KURO_CRITICAL(...)				::Kuro::Log::GetClientLogger()->critical(__VA_ARGS__)
