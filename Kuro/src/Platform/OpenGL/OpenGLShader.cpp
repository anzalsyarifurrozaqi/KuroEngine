#include "engineph.h"
#include "OpenGLShader.h"
#include "Kuro/Core/Timer.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

//#include <shaderc/shaderc.hpp>
#include <fstream>
#include <filesystem>
//#include "spirv_cross/spirv_cross.hpp"
//#include "spirv_cross/spirv_glsl.hpp"

namespace Kuro
{
	namespace Utils {

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			if (type == "fragment" || type == "pixel")
				return GL_FRAGMENT_SHADER;
			if (type == "geometry")
				return GL_GEOMETRY_SHADER;

			KURO_CORE_ASSERT(false, "Unknown shader type!");
			return 0;
		}

		//static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		//{
		//	switch (stage)
		//	{
		//	case GL_VERTEX_SHADER:   return shaderc_glsl_vertex_shader;
		//	case GL_FRAGMENT_SHADER: return shaderc_glsl_fragment_shader;
		//	}
		//	KURO_CORE_ASSERT(false);
		//	return (shaderc_shader_kind)0;
		//}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			}
			KURO_CORE_ASSERT(false);
			return nullptr;
		}

		static const char* GetCacheDirectory()
		{
			// TODO: make sure the assets directory is valid
			return "assets/cache/shader/opengl";
		}

		static void CreateCacheDirectoryIfNeeded()
		{
			std::string cacheDirectory = GetCacheDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directories(cacheDirectory);
		}

		static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:    return ".cached_opengl.vert";
			case GL_FRAGMENT_SHADER:  return ".cached_opengl.frag";
			}
			KURO_CORE_ASSERT(false);
			return "";
		}

		static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:    return ".cached_vulkan.vert";
			case GL_FRAGMENT_SHADER:  return ".cached_vulkan.frag";
			}
			KURO_CORE_ASSERT(false);
			return "";
		}
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		Utils::CreateCacheDirectoryIfNeeded();

		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);

		{
			Timer timer;			
			CompileOpenGLShader(shaderSources);
			CreateProgram();
			KURO_CORE_WARN("Shader creation took {0} ms", timer.ElapseMillis());
		}

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		
		CompileOpenGLShader(sources);
		CreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}	

	void OpenGLShader::Bind() const
	{
		//KURO_CORE_INFO("OpenGLShader::Bind");
		//KURO_CORE_TRACE("ProgramId : {}", m_RendererID);

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		KURO_CORE_INFO("OpenGLShader::UnBind");
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		KURO_CORE_INFO("OpenGLShader::SetInt");
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		KURO_CORE_INFO("OpenGLShader::SetIntArray");
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		KURO_CORE_INFO("OpenGLShader::SetFloat");
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		KURO_CORE_INFO("OpenGLShader::SetFloat2");
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		KURO_CORE_INFO("OpenGLShader::SetFloat3");
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		KURO_CORE_INFO("OpenGLShader::OpenGLShader");
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		//KURO_CORE_INFO("OpenGLShader::SetMat4");
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		KURO_CORE_INFO("OpenGLShader::UploadUniformInt");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		KURO_CORE_INFO("OpenGLShader::UploadUniformIntArray");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		KURO_CORE_INFO("OpenGLShader::UploadUniformFloat");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		KURO_CORE_INFO("OpenGLShader::UploadUniformFloat2");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		KURO_CORE_INFO("OpenGLShader::UploadUniformFloat3");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		KURO_CORE_INFO("OpenGLShader::UploadUniformFloat4");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		KURO_CORE_INFO("OpenGLShader::UploadUniformMat3");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		//KURO_CORE_INFO("OpenGLShader::UploadUniformMat4");
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		KURO_CORE_INFO("OpenGLShader::ReadFile");

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				KURO_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			KURO_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		KURO_CORE_INFO("OpenGLShader::PreProcess");
		
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); // Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); // End of shader type declaration line
			KURO_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; // Start of shader type name (after "#type" keyword)
			std::string type = source.substr(begin, eol - begin);
			KURO_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); // Start of shader code after shader type declaration line
			KURO_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); // Start of next shader type declaration line

			shaderSources[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::CompileOpenGLShader(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		KURO_CORE_INFO("OpenGLShader::CompileOrGetOnpenGLBinaries");		
		GLuint program = glCreateProgram();

		auto& shaderData = m_OpenGLShader;
		shaderData.clear();
		for (auto&& [stage, source] : shaderSources)
		{
			const GLuint shader = glCreateShader(stage);
			const char* shaderSource = source.c_str();
			glShaderSource(shader, 1, &shaderSource, nullptr);
			glCompileShader(shader);

			GLint isCompiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());
				KURO_CORE_ERROR(infoLog.data());
				KURO_CORE_ASSERT(false);

				glDeleteShader(shader);
			}

			glAttachShader(program, shader);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			KURO_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_FilePath, infoLog.data());

			glDeleteProgram(program);
		}

		m_RendererID = program;
	}

	void OpenGLShader::CreateProgram()
	{
		KURO_CORE_INFO("OpenGLShader::CreateProgram");
	}
}
