workspace "AssemCubeEngine"
    architecture "x64"
    startproject "AssemCube"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "AssemCubeEngine/vendor/GL/include"

include "AssemCubeEngine/vendor/GL"

project "AssemCubeEngine"
    location "AssemCubeEngine"
    kind "sharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-int/" .. outputDir .. "/%{prj.name}")

    pchheader "acpch.h"
    pchsource "AssemCubeEngine/src/acpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
    }

    links 
	{ 
		"GLFW",
		"opengl32.lib"
	}

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"

        defines 
        {
            "AC_PLATFORM_WINDOWS",
            "AC_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/AssemCube/\"")
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AC_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AC_DIST"
        runtime "Release"
        optimize "on"
        
project "AssemCube"
    location "AssemCube"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "AssemCubeEngine/vendor/spdlog/include",
        "AssemCubeEngine/src"
    }

    links
    {
        "AssemCubeEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "AC_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AC_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AC_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "AC_DIST"
        runtime "Release"
        optimize "On"