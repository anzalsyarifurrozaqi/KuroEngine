#include "engineph.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Kuro
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case Kuro::RendererAPI::API::None: KURO_CORE_ASSERT(false, "Renderer::None is currently not supported!"); return nullptr;
			case Kuro::RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		KURO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
