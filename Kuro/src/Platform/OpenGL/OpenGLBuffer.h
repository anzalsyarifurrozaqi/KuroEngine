#pragma once

#include "Kuro/Renderer/Buffer.h"
#include "Kuro/Renderer/Mesh.h"

#include <glad/glad.h>

namespace Kuro
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(VertexData* vertexData, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		
		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;

		uint32_t GetHandle() const override { return m_RendererID; }

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual  void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
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
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:		
		OpenGLFrameBuffer(ImageFormat formatColor, ImageFormat formatDepth);
		virtual ~OpenGLFrameBuffer();

		void Bind() const override;
		void UnBind() const override;

		void SetData() override;

		void BindTexture() const override;

		virtual Texture2D& GetTextureColor() const override { return *m_TexColor.get(); }
		virtual Texture2D& GetTextureDepth() const override { return *m_TextDepth.get(); }

	private:
		uint32_t m_RendererID;

		Ref<Texture2D> m_TexColor;
		Ref<Texture2D> m_TextDepth;

		int m_Width;
		int m_Height;
	};
}
