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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "KURO_PLATFORM_WINDOWS",
            "KURO_BUILD_DLL"
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
        "Kuro/vendor/spdlog/include"
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