workspace "Kuro"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Kuro/vendor/GLFW/include"
IncludeDir["GLM"] = "Kuro/vendor/GLM"
IncludeDir["Vulkan"] = "Kuro/vendor/Vulkan-Hpp"

group "Dependencies"
    include "Kuro/vendor/GLFW"    

group ""

project "Kuro"
    location "Kuro"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "engineph.h"
    pchsource "Kuro/src/engineph.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/GLM/glm/**.hpp",
        "%{prj.name}/vendor/GLM/glm/**.inl",
        "%{prj.name}/vendor/Vulkan-Hpp/vulkan/**.hpp",
        "%{prj.name}/vendor/Vulkan-Hpp/vulkan/**.c",
        "%{prj.name}/vendor/Vulkan-Hpp/vulkan/**.cppm"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.Vulkan}"

    }

    links
    {
        "GLFW"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "KURO_PLATFORM_WINDOWS",
            "KURO_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/sandbox/\"")
        }
    
    filter "configurations:Debug"
        defines "KURO_DEBUG"
        runtime "Debug"
        optimize "On"
    
    filter "configurations:Release"
        defines "KURO_RELEASE"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        defines "KURO_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"        
    }

    includedirs
    {
        "Kuro/src",        
        "Kuro/vendor/spdlog/include",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.Vulkan}"
    }

    links
    {
        "Kuro"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "KURO_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "KURO_DEBUG"
        runtime "Debug"
        optimize "On"

    filter "configurations:Release"
        defines "KURO_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "KURO_DIST"
        runtime "Release"
        optimize "On"