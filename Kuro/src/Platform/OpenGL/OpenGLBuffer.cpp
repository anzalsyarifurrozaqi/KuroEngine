#include "engineph.h"
#include "OpenGLBuffer.h"
#include "Kuro/Core/Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
namespace Kuro
{
	////////////////////////////////////////////////////
	// VERTEX BUFFER///////////////////////////////////
	//////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(VertexData* vertexData, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertexData, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	////////////////////////////////////////////////////
	// INDEX BUFFER////////////////////////////////////
	//////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(ImageFormat formatColor, ImageFormat formatDepth)
	{
		KURO_CORE_TRACE("OpenGLFrameBuffer::OpenGLFrameBuffer");
		glCreateFramebuffers(1, &m_RendererID);
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());		
		glfwGetFramebufferSize(window, &m_Width, &m_Height);		
		
		if (formatColor != ImageFormat::None)
		{
			m_TexColor = Texture2D::Create(TextureSpecification{ .Width = (uint32_t) m_Width, .Height = (uint32_t) m_Height, .Format = formatColor });
			glTextureParameteri(m_TexColor->GetRendererID(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(m_TexColor->GetRendererID(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0, m_TexColor->GetRendererID(), 0);
		}

		if (formatDepth != ImageFormat::None)
		{
			m_TextDepth = Texture2D::Create(TextureSpecification{ .Width = (uint32_t) m_Width, .Height = (uint32_t) m_Height, .Format = formatDepth });
			const GLfloat border[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			glTextureParameterfv(m_TextDepth->GetRendererID(), GL_TEXTURE_BORDER_COLOR, border);
			glTextureParameteri(m_TextDepth->GetRendererID(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTextureParameteri(m_TextDepth->GetRendererID(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glNamedFramebufferTexture(m_RendererID, GL_DEPTH_ATTACHMENT, m_TextDepth->GetRendererID(), 0);
		}

		const GLenum status = glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER);				

		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			KURO_CORE_ERROR("OpenGL Frame Buffer Failed!");
			KURO_CORE_ASSERT(false, status);
		}
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::SetData()
	{
		glClearNamedFramebufferfv(m_RendererID, GL_COLOR, 0, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
		glClearNamedFramebufferfi(m_RendererID, GL_DEPTH_STENCIL, 0, 1.0f, 0);
	}
	
	void OpenGLFrameBuffer::BindTexture() const
	{
		glBindTextureUnit(0, m_TexColor->GetRendererID());
	}
}
