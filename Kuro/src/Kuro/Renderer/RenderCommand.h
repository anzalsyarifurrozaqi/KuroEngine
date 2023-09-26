#pragma once

#include "Kuro/Renderer/RendererAPI.h"

namespace Kuro
{
	class RenderCommand
	{
	public:
		static Scope<RendererAPI> s_RendererAPI;
	};
}

