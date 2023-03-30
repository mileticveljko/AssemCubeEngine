#pragma once

#ifdef AC_PLATFORM_WINDOWS
	#ifdef AC_BUILD_DLL
		#define AC_API __declspec(dllexport)
	#else 
		#define AC_API __declspec(dllimport)
	#endif
#else 
	#error AssemCube only supports Windows!
#endif

#define BIT(x) (1<<x)
