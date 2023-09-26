#include "engineph.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Kuro
{
	void OpenGLVertexArray::Bind() const
	{
	}

	void OpenGLVertexArray::UnBind() const
	{
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		KURO_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		//glBindVertexArray(m_RendererID);
		//vertexBuffer->Bind();
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
	}
}

