#include "engineph.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Kuro
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: KURO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
		}

		KURO_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& verteSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: KURO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, verteSrc, fragmentSrc);
		}

		KURO_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		KURO_CORE_INFO("ShaderLibrary::Add");
		KURO_CORE_ASSERT(!Exist(name), "Shader already exists!");
		m_Shader[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		KURO_CORE_INFO("ShaderLibrary::Add");
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		KURO_CORE_INFO("ShaderLibrary::Load");		
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		KURO_CORE_INFO("ShaderLibrary::Load");
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		KURO_CORE_INFO("ShaderLibrary::Get");
		return m_Shader[name];
	}

	bool ShaderLibrary::Exist(const std::string& name) const
	{
		KURO_CORE_INFO("ShaderLibrary::Exist");
		return m_Shader.find(name) != m_Shader.end();
	}

}
