#pragma once

#include "Kuro/Renderer/Buffer.h"

namespace Kuro
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		// Inherited via VertexBuffer
		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* data, uint32_t size) override;
		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_RendereID;
		BufferLayout m_Layout;
	};

	// Currently only supports 32-bit index buffers
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RenderID;
		uint32_t m_Count;
	};
}
