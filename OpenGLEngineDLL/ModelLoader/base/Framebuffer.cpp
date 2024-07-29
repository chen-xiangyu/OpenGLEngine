
#include "FrameBuffer.h"
#include "HiveLogger.h"
#include "utils/safe.h"

namespace hiveGL
{
	std::shared_ptr<CFrameBuffer> CFrameBuffer::m_pDefaultFrameBuffer = nullptr;

	CFrameBuffer::CFrameBuffer(bool vIsDefault)
		:m_FrameBufferID(0), m_Width(0), m_Height(0), m_TexturesMap{}, m_RenderBuffersMap{}
	{
		if (!vIsDefault) GL_SAFE_CALL(glGenFramebuffers(1, &m_FrameBufferID));
	}

	CFrameBuffer::~CFrameBuffer()
	{
		if (this != m_pDefaultFrameBuffer.get()) GL_SAFE_CALL(glDeleteFramebuffers(1, &m_FrameBufferID));
	}

	void CFrameBuffer::bind(GLenum vTarget) const
	{
		GL_SAFE_CALL(glBindFramebuffer(vTarget, m_FrameBufferID));
		GL_SAFE_CALL(glViewport(0, 0, m_Width, m_Height));
	}

	void CFrameBuffer::unbind(GLenum vTarget) const
	{
		GL_SAFE_CALL(glBindFramebuffer(vTarget, 0));
	}

	void CFrameBuffer::resize(int vWidth, int vHeight)
	{
		m_Width = vWidth;
		m_Height = vHeight;
		for (const auto& Pair : m_TexturesMap)
			Pair.second->resize(vWidth, vHeight, nullptr);
		for (const auto& Pair : m_RenderBuffersMap)
			Pair.second->resize(vWidth, vHeight);
	}

	void CFrameBuffer::setAttachment(GLenum vAttachmentType, const std::shared_ptr<CTexture2D>& vTexture2D, GLint vTextureLevel)
	{
		GL_SAFE_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, vAttachmentType, GL_TEXTURE_2D, vTexture2D->getID(), vTextureLevel));
		m_TexturesMap[vAttachmentType] = vTexture2D;
		m_Width = vTexture2D->getWidth();
		m_Height = vTexture2D->getHeight();
	}

	void CFrameBuffer::setAttachment(GLenum vAttachmentType, const std::shared_ptr<CRenderBuffer>& vRenderBuffer)
	{
		GL_SAFE_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, vAttachmentType, GL_RENDERBUFFER, vRenderBuffer->getID()));
		m_RenderBuffersMap[vAttachmentType] = vRenderBuffer;
		m_Width = vRenderBuffer->getWidth();
		m_Height = vRenderBuffer->getHeight();
	}

	const std::shared_ptr<CTexture2D>& CFrameBuffer::getAttachment(GLenum vAttachmentType)
	{
		return m_TexturesMap[vAttachmentType];
	}

	void CFrameBuffer::setDrawAttachments(const std::vector<GLenum>& vAttachmentsType) const
	{
		GL_SAFE_CALL(glDrawBuffers((GLsizei)vAttachmentsType.size(), vAttachmentsType.data()));
	}

	bool CFrameBuffer::check()
	{
		bool IsComplete = true;
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			IsComplete = false;
			HIVE_LOG_ERROR("Framebuffer is not complete!");
		}
		return IsComplete;
	}

	void CFrameBuffer::setColorBufferEmpty()
	{
		GL_SAFE_CALL(glDrawBuffer(GL_NONE));
		GL_SAFE_CALL(glReadBuffer(GL_NONE));
	}

	const std::shared_ptr<CFrameBuffer>& CFrameBuffer::getDefaultFrameBuffer()
	{
		if (m_pDefaultFrameBuffer == nullptr) m_pDefaultFrameBuffer = std::make_shared<CFrameBuffer>(true);
		return m_pDefaultFrameBuffer;
	}

	void CFrameBuffer::initDefaultFrameBuffer(GLuint vFrameBufferID)
	{
		getDefaultFrameBuffer()->m_FrameBufferID = vFrameBufferID;
	}
}