
-- Kuro Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Kuro/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Kuro/vendor/glm"
IncludeDir["Glad"] = "%{wks.location}/Kuro/vendor/Glad/include"
IncludeDir["SPIRV-Cross"] = "%{wks.location}/Kuro/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
-- LibraryDir["mono"] = "%{wks.location}/Hazel/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}
Library["ShaderC"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
-- Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

-- Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
-- Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

-- Windows
-- Library["WinSock"] = "Ws2_32.lib"
-- Library["WinMM"] = "Winmm.lib"
-- Library["WinVersion"] = "Version.lib"
-- Library["BCrypt"] = "Bcrypt.lib"