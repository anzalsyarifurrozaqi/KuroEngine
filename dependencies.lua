
-- Kuro Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Kuro/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Kuro/vendor/glm"
IncludeDir["Glad"] = "%{wks.location}/Kuro/vendor/Glad/include"
IncludeDir["stb"] = "%{wks.location}/Kuro/vendor/stb/"
IncludeDir["ASSIMP"] = "%{wks.location}/Kuro/vendor/ASSIMP/include"
-- IncludeDir["assimp_contrib"] = "%{wks.location}/Kuro/vendor/assimp/contrib"
-- IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

-- LibraryDir = {}
-- LibraryDir["assimp"] = "%{wks.location}/Kuro/vendor/assimp/lib/%{cfg.buildcfg}"

-- Library = {}
-- Library["assimp"] = "%{LibraryDir.assimp}/assimp-vc143-mtd.lib"

-- LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
