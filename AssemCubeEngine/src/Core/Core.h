#pragma once

#include <memory>

#ifdef AC_PLATFORM_WINDOWS
#if AC_DYNAMIC_LINK
	#ifdef AC_BUILD_DLL
		#define AC_API __declspec(dllexport)
	#else 
		#define AC_API __declspec(dllimport)
	#endif
#else
	#define AC_API
#endif
#else 
	#error AssemCube only supports Windows!
#endif

#ifdef AC_ENABLE_ASSERTS
#define AC_ASSERT(x, ...) { if(!(x)) { AC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define AC_CORE_ASSERT(x, ...) { if(!(x)) { AC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define AC_ASSERT(x, ...)
#define AC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define AC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ac {
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;
}