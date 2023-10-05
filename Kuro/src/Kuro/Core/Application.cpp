#include "engineph.h"
#include "Application.h"
#include "Kuro/Core/Log.h"

#include "Kuro/Events/ApplicationEvent.h"
#include "Kuro/Utils/PlatformUtils.h"

#include "Kuro/Renderer/Renderer.h"

#include <glad/glad.h>

namespace Kuro
{
	Application* Application::s_Instance = nullptr;

	GLuint VertexArrayID;
	GLuint vertexbuffer;

	Application::Application()
	{
		KURO_CORE_ASSERT(!s_Instance, "Application Already Exist!");
		s_Instance = this;
		m_Window = Window::Create(WindowProps("Kuro Engine"));
		m_Window->SetEventCallback(KURO_BIND_EVENT_FN(OnEvent));

		Renderer::Init();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{			
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(KURO_BIND_EVENT_FN(Application::OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(KURO_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{		
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			//m_Minimized = true;
			return false;
		}

		//m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}
