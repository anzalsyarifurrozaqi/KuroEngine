#pragma once

#include "Core.h"

namespace Kuro
{
	class KURO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		inline static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

