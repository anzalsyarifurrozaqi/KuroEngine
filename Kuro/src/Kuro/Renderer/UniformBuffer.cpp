#include "engineph.h"
#include "UniformBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
namespace Kuro
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		KURO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		KURO_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;		
	}
}

