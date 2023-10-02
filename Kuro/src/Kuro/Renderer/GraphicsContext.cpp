#include "engineph.h"
#include "GraphicsContext.h"
#include "Kuro/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"
namespace Kuro
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: KURO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		KURO_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}
