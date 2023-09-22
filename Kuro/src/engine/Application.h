#pragma once

#include "Core.h"
#include "engine/event/Event.h"
#include "engine/event/ApplicationEvent.h"
#include "engine/event/KeyEvent.h"

#include "Window.h"
#include "engine/LayerStack.h"

namespace Kuro
{
	class KURO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		static Application* s_Instance;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::unique_ptr<Window> m_Window;
		bool OnWindowCloseEvent(WindowCloseEvent& e);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

