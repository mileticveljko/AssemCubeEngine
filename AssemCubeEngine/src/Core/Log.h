#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ac
{
	class AC_API Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define AC_CORE_TRACE(...)	::ac::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AC_CORE_INFO(...)	::ac::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AC_CORE_WARN(...)	::ac::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AC_CORE_ERROR(...)	::ac::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AC_CORE_FATAL(...)	::ac::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define AC_TRACE(...)		::ac::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AC_INFO(...)		::ac::Log::GetClientLogger()->info(__VA_ARGS__)
#define AC_WARN(...)		::ac::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AC_ERROR(...)		::ac::Log::GetClientLogger()->error(__VA_ARGS__)
#define AC_FATAL(...)		::ac::Log::GetClientLogger()->fatal(__VA_ARGS__)
