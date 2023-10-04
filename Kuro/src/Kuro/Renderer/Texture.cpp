#include "engineph.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
namespace Kuro
{
	Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	KURO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(specification);
		}
				
		KURO_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string* path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	KURO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		KURO_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}
