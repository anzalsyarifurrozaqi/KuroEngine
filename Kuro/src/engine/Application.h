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
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

