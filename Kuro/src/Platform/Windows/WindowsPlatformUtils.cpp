#include "engineph.h"
#include "Kuro/Utils/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace Kuro
{
	float Time::GetTime()
	{
		return glfwGetTime();
	}
}
