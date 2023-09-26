#pragma once

#include "Kuro/Renderer/RenderCommand.h"

namespace Kuro
{
	class Renderer
	{
	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
