
-- Kuro Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Kuro/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Kuro/vendor/glm"
IncludeDir["Glad"] = "%{wks.location}/Kuro/vendor/Glad/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"