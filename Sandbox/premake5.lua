project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Kuro/vendor/spdlog/include",
        "%{wks.location}/Kuro/src",		
		"%{wks.location}/Kuro/vendor",
		"%{IncludeDir.glm}"		
	}

	links
	{
		"Kuro"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "KURO_DEBUG"
		staticruntime "off"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KURO_RELEASE"		
		staticruntime "off"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KURO_DIST"		
		staticruntime "off"
		runtime "Release"
		optimize "on"
