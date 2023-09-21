#pragma once

#include "Core.h"

#include "engine/event/Event.h"

namespace Kuro
{
	class KURO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		inline static Application& Get() { return *s_Instance; }
		//inline static Window& GetWindow() { return *m_Window; }
	private:
		static Application* s_Instance;
		bool m_Running = true;

		//std::unique_ptr<Window> m_Window;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

