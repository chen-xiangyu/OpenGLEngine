
#include "Texture2D.h"
#include "tinygltf/stb_image.h"
#include <HiveLogger.h>
#include "utils/safe.h"

namespace hiveGL
{
	CTexture2D::CTexture2D(const std::string& vTexturePath, bool vFlipY)
		:m_TextureID(0), m_InternalFormat(0), m_Format(0), m_DataType(0), m_Width(0), m_Height(0)
	{

		GL_SAFE_CALL(glGenTextures(1, &m_TextureID));

		stbi_set_flip_vertically_on_load(vFlipY);
		int Width, Height, NrChannels;
		unsigned char* pData = stbi_load(vTexturePath.c_str(), &Width, &Height, &NrChannels, 0);
		if (pData)
		{
			GLenum Format;
			if (NrChannels == 1) Format = GL_RED;
			else if (NrChannels == 3) Format = GL_RGB;
			else if (NrChannels == 4) Format = GL_RGBA;
			else {
				Format = GL_RGB;
				HIVE_LOG_WARNING("Texture channels cannot support, which is {}, path is {}", NrChannels, vTexturePath);
			}
			m_InternalFormat = Format;
			m_Format = Format;
			m_DataType = GL_UNSIGNED_BYTE;
			resize(Width, Height, pData);
			generateMipmap();
		}
		else
		{
			HIVE_LOG_ERROR("Failed to load texture: {}", vTexturePath);
		}
		stbi_image_free(pData);
	}

	CTexture2D::CTexture2D(int vWidth, int vHeight, GLenum vInternalFormat, GLenum vFormat, GLenum vDataType)
		:m_TextureID(0), m_InternalFormat(vInternalFormat), m_Format(vFormat), m_DataType(vDataType), m_Width(0), m_Height(0)
	{
		GL_SAFE_CALL(glGenTextures(1, &m_TextureID));
		resize(vWidth, vHeight, nullptr);
	}

	void CTexture2D::bind() const
	{
		GL_SAFE_CALL(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}

	void CTexture2D::resize(int vWidth, int vHeight, const GLvoid* vPixels)
	{
		m_Width = vWidth;
		m_Height = vHeight;
		bind();
		GL_SAFE_CALL(glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, vWidth, vHeight, 0, m_Format, m_DataType, vPixels));
	}

	void CTexture2D::setParameters(GLenum vName, GLint vValue)
	{
		GL_SAFE_CALL(glTexParameteri(GL_TEXTURE_2D, vName, vValue));
	}

	void CTexture2D::setParameters(GLenum vName, const GLfloat* vValue)
	{
		GL_SAFE_CALL(glTexParameterfv(GL_TEXTURE_2D, vName, vValue));
	}

	void CTexture2D::generateMipmap()
	{
		GL_SAFE_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	}
}