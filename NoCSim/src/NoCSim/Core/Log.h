#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace NoCSim {

	class Log
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

// Core log macros
#define NS_CORE_TRACE(...)   ::NoCSim::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NS_CORE_INFO(...)    ::NoCSim::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NS_CORE_WARN(...)    ::NoCSim::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NS_CORE_ERROR(...)   ::NoCSim::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NS_CORE_FATAL(...)   ::NoCSim::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define NS_TRACE(...)   ::NoCSim::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NS_INFO(...)    ::NoCSim::Log::GetClientLogger()->info(__VA_ARGS__)
#define NS_WARN(...)    ::NoCSim::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NS_ERROR(...)   ::NoCSim::Log::GetClientLogger()->error(__VA_ARGS__)
#define NS_FATAL(...)   ::NoCSim::Log::GetClientLogger()->fatal(__VA_ARGS__)

#define NS_ASSERT(x, ...) { if(!(x)) NS_ERROR("Assertion Failed: {0}", __VA_ARGS__); }
#define NS_CORE_ASSERT(x, ...) { if(!(x)) NS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); }
