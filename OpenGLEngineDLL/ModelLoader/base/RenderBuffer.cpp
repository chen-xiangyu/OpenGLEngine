
#include "RenderBuffer.h"
#include "utils/safe.h"

namespace hiveGL
{
	CRenderBuffer::CRenderBuffer(int vWidth, int vHeight, GLenum vInternalformat)
		:m_RenderBufferID{ 0 }, m_Internalformat(vInternalformat), m_Width(0), m_Height(0)
	{
		GL_SAFE_CALL(glGenRenderbuffers(1, &m_RenderBufferID));
		resize(vWidth, vHeight);
	}

	CRenderBuffer::~CRenderBuffer()
	{
		GL_SAFE_CALL(glDeleteRenderbuffers(1, &m_RenderBufferID));
	}

	void CRenderBuffer::resize(int vWidth, int vHeight)
	{
		m_Width = vWidth;
		m_Height = vHeight;
		GL_SAFE_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID));
		GL_SAFE_CALL(glRenderbufferStorage(GL_RENDERBUFFER, m_Internalformat, m_Width, m_Height));
	}
}