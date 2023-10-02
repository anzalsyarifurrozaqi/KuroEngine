#pragma once

#include "Kuro/Core/Base.h"
#include "Kuro/Events/Event.h"
#include "Kuro/Events/ApplicationEvent.h"
#include "Kuro/Events/KeyEvent.h"

#include "Window.h"
#include "Kuro/Core/LayerStack.h"

namespace Kuro
{
	class Application
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
		float m_LastFrameTime = 0.0f;

		std::unique_ptr<Window> m_Window;
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		// test
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBufer;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

