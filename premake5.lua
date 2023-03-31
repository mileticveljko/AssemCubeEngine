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
IncludeDir["GLFW"] = "AssemCubeEngine/vendor/GLFW_V/include"
IncludeDir["glad"] = "AssemCubeEngine/vendor/glad/include"
IncludeDir["ImGui"] = "AssemCubeEngine/vendor/imguiV"
IncludeDir["glm"] = "AssemCubeEngine/vendor/glm"

group "Dependencies"
    include "AssemCubeEngine/vendor/GLFW_V"
    include "AssemCubeEngine/vendor/glad"
    include "AssemCubeEngine/vendor/imguiV"
group ""

project "AssemCubeEngine"
    location "AssemCubeEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-int/" .. outputDir .. "/%{prj.name}")

    pchheader "acpch.h"
    pchsource "AssemCubeEngine/src/acpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines 
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links 
	{ 
		"GLFW",
        "glad",
        "ImGui",
		"opengl32.lib"
	}

    filter "system:windows"
        systemversion "latest"

        defines 
        {
            "AC_PLATFORM_WINDOWS",
            "AC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
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
    staticruntime "on"

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
        "AssemCubeEngine/src",
        "AssemCubeEngine/vendor",
        "%{IncludeDir.glm}"
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
        symbols "on"

    filter "configurations:Release"
        defines "AC_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "AC_DIST"
        runtime "Release"
        optimize "on"