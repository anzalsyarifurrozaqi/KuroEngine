#include "engineph.h"
#include "OpenGLTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Kuro
{
	namespace Utils {

		static GLenum KuroImageFormatToGLDataFormat(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::RGB8:					return GL_RGB;
			case ImageFormat::RGBA8:				return GL_RGBA;
			case ImageFormat::RGBA16F:				return GL_RGBA16F;
			case ImageFormat::DEPTH_COMPONENT24:	return GL_DEPTH_COMPONENT24;
			}

			KURO_CORE_ASSERT(false, "Unknown Image Format");
			return 0;
		}

		static GLenum KuroImageFormatToGLInternalFormat(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::RGB8:					return GL_RGB8;
			case ImageFormat::RGBA8:				return GL_RGBA8;
			case ImageFormat::RGBA16F:				return GL_RGBA16F;
			case ImageFormat::DEPTH_COMPONENT24:	return GL_DEPTH_COMPONENT24;
			}

			KURO_CORE_ASSERT(false, "Unknown Image Format");
			return 0;
		}

		static int GetNumMipMapLevels2D(int width, int height)
		{
			int levels = 1;
			while ((width | height) >> levels)
				levels += 1;
			return levels;
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& specification)
		: m_Specification(specification), m_Width(m_Specification.Width), m_Height(m_Specification.Height)
	{
		m_InternalFormat = Utils::KuroImageFormatToGLInternalFormat(m_Specification.Format);
		m_DataFormat = Utils::KuroImageFormatToGLDataFormat(m_Specification.Format);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MAX_LEVEL, 0);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;
		int numMipmaps = 0;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}

		if (data)
		{
			m_IsLoaded = true;

			m_Width = width;
			m_Height = height;


			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			KURO_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

			numMipmaps = Utils::GetNumMipMapLevels2D(width, height);
			
			glTextureStorage2D(m_RendererID, numMipmaps, internalFormat, m_Width, m_Height);
			glTextureSubImage2D(m_RendererID, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);						

			glGenerateTextureMipmap(m_RendererID);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAX_LEVEL, numMipmaps);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free((void*)data);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		KURO_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}
