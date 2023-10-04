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
		
		//glCreateVertexArrays(1, &VertexArrayID);
		//glBindVertexArray(VertexArrayID);

		//float g_vertex_buffer_data[] = {
		//	-1.0f, -1.0f, 0.0f,
		//	 1.0f, -1.0f, 0.0f,
		//	 0.0f,  1.0f, 0.0f,
		//};
		//
		//glCreateBuffers(1, &vertexbuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
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

			// 1rst attribute buffer : vertices
			//glEnableVertexAttribArray(0);
			//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			//glVertexAttribPointer(
			//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			//	3,                  // size
			//	GL_FLOAT,           // type
			//	GL_FALSE,           // normalized?
			//	0,                  // stride
			//	(void*)0            // array buffer offset
			//);

			// Draw the triangle !
			//glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

			//glDisableVertexAttribArray(0);

			m_Window->OnUpdate();
		}

		// Cleanup VBO
		//glDeleteBuffers(1, &vertexbuffer);
		//glDeleteVertexArrays(1, &VertexArrayID);
		//glDeleteProgram(programID);
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
