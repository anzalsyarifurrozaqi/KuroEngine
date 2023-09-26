#include "engineph.h"
#include "VertexArray.h"
#include "Kuro/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Kuro
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: KURO_CORE_ASSERT(false, "Renderer::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		KURO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
