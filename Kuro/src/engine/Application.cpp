#include "engineph.h"
#include "Application.h"
#include "engine/Log.h"

#include "engine/event/ApplicationEvent.h"

namespace Kuro
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		KURO_CORE_ASSERT(!s_Instance, "Application Already Exist!");
		s_Instance = this;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			KURO_CORE_TRACE(e);
		}
		while (true);
	}
}
