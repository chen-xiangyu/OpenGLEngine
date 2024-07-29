#pragma once

#include <string>
#include "base/Texture.h"

namespace hiveGL
{
	class CTexture2D : public CTexture
	{
	public:
		CTexture2D(const std::string& vTexturePath, bool vFlipY = false);
		CTexture2D(int vWidth, int vHeight, GLenum vInternalFormat, GLenum vFormat, GLenum vDataType);
		// Inherited via CTexture
		GLuint getID() const override { return m_TextureID; }
		void bind() const override;
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		void resize(int vWidth, int vHeight, const GLvoid* vPixels = nullptr);
		static void setParameters(GLenum vName, GLint vValue);
		static void setParameters(GLenum vName, const GLfloat* vValue);
		static void generateMipmap();
	private:
		GLuint m_TextureID;
		GLenum m_InternalFormat;
		GLenum m_Format;
		GLenum m_DataType;
		int m_Width, m_Height;
	};
}