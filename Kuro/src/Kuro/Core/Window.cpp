#include "engineph.h"
#include "Kuro/Core/Window.h"

#ifdef KURO_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif // KURO_PLATFORM_WINDOWS

namespace Kuro
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef KURO_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		KURO_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif // KURO_PLATFORM_WINDOWS
	}
}
