#include "engineph.h"
#include "Application.h"
#include "engine/Log.h"

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
		while (m_Running);
	}
}
