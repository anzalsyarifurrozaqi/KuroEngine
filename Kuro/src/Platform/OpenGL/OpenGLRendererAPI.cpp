#include "engineph.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
namespace Kuro
{
	namespace Utils
	{
		static GLenum GetPolygonMode(PolygonMode polygonMode)
		{
			switch (polygonMode)
			{
			case PolygonMode::LINE:		return GL_LINE;
			case PolygonMode::FILL:		return GL_FILL;
			}


			KURO_CORE_ASSERT(false, "Unknown PolygonMode!");
			return 0;
		}
	}

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:			KURO_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:			KURO_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:				KURO_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	KURO_CORE_TRACE(message); return;
		}

		KURO_CORE_ASSERT(false, "Unknown severity level!");
	}
	void OpenGLRendererAPI::Init()
	{
		KURO_CORE_INFO("OpenGLRendererAPI::Init");

#ifdef KURO_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif // KURO_DEBUG

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(-1.0f, -1.0f);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		KURO_CORE_INFO("OpenGLRendererAPI::SetViewport");
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		//KURO_CORE_INFO("OpenGLRendererAPI::SetClearColor");
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		//KURO_CORE_INFO("OpenGLRendererAPI::Clear");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		//KURO_CORE_INFO("OpenGLRendererAPI::DrawIndexed");
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();				
		
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		//KURO_CORE_INFO("OpenGLRendererAPI::DrawLines");
		//vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}

	void OpenGLRendererAPI::SetLineWidth(float width)
	{
		KURO_CORE_INFO("OpenGLRendererAPI::SetLineWidth");
		glLineWidth(width);
	}
	void OpenGLRendererAPI::SetPolygonMode(PolygonMode polygonMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, Utils::GetPolygonMode(polygonMode));
	}
}
