project "Kuro"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "engineph.h"
    pchsource "src/engineph.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"		
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",		
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		-- "%{IncludeDir.SPIRV-Cross}",
		"%{IncludeDir.VulkanSDK}"
    }

	links
	{
		"GLFW",
		"Glad",
		"SPIRV-Cross",
		"opengl32.lib",
		"%{Library.ShaderC}"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
			-- "%{Library.WinSock}",
			-- "%{Library.WinMM}",
			-- "%{Library.WinVersion}",
			-- "%{Library.BCrypt}",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "KURO_DEBUG"
		staticruntime "off"
		runtime "Debug"
		symbols "on"

		links
		{
			-- "%{Library.ShaderC_Debug}",
			-- "%{Library.SPIRV_Cross_Debug}",
			-- "%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "KURO_RELEASE"
		staticruntime "off"
		runtime "Release"
		optimize "on"

		links
		{
			-- "%{Library.ShaderC_Release}",
			-- "%{Library.SPIRV_Cross_Release}",
			-- "%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Dist"
		defines "KURO_DIST"
		staticruntime "off"
		runtime "Release"
		optimize "on"

		links
		{
			-- "%{Library.ShaderC_Release}",
			-- "%{Library.SPIRV_Cross_Release}",
			-- "%{Library.SPIRV_Cross_GLSL_Release}"
        }
