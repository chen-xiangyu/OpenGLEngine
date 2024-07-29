#pragma once

#include <memory>
#include <unordered_map>
#include <set>
#include <glad/glad.h>
#include "base/Texture2D.h"
#include "base/RenderBuffer.h"

namespace hiveGL
{
	class CFrameBuffer
	{
	public:
		CFrameBuffer(bool vIsDefault = false);
		~CFrameBuffer();
		void bind(GLenum vTarget = GL_FRAMEBUFFER) const;
		void unbind(GLenum vTarget = GL_FRAMEBUFFER) const;
		void resize(int vWidth, int vHeight);
		void setAttachment(GLenum vAttachmentType, const std::shared_ptr<CTexture2D>& vTexture2D, GLint vTextureLevel = 0);
		void setAttachment(GLenum vAttachmentType, const std::shared_ptr<CRenderBuffer>& vRenderBuffer);
		const std::shared_ptr<CTexture2D>& getAttachment(GLenum vAttachmentType);
		void setDrawAttachments(const std::vector<GLenum>& vAttachmentsType) const;
		static bool check();
		static void setColorBufferEmpty();
		static const std::shared_ptr<CFrameBuffer>& getDefaultFrameBuffer();
		static void initDefaultFrameBuffer(GLuint vFrameBufferID = 0);
	private:
		GLuint m_FrameBufferID;
		std::unordered_map<GLenum, std::shared_ptr<CTexture2D>> m_TexturesMap;
		std::unordered_map<GLenum, std::shared_ptr<CRenderBuffer>> m_RenderBuffersMap;
		int m_Width;
		int m_Height;
		static std::shared_ptr<CFrameBuffer> m_pDefaultFrameBuffer;
	};
}