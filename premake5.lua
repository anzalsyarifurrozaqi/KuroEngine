include "./Vendor/premake/premake_custumization/solution_items.lua"
include "dependencies.lua"

workspace "Kuro"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"	
	include "Kuro/vendor/GLFW"
	include "Kuro/vendor/Glad"	
	include "Kuro/vendor/ASSIMP"

group ""

group "Core"
	include "Kuro"	
group ""

group "Misc"
	include "Sandbox"
group ""
