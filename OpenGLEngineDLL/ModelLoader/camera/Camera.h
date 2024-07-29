#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <base/Framebuffer.h>
#include <culling/Frustum.h>

namespace hiveGL
{
	class CCamera
	{
	public:
		CCamera();
		const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::vec3& getWorldPos() const { return m_Position; }
		const glm::vec3& getFront() const { return m_Front; }
		const glm::vec3& getUp() const { return m_Up; }
		const glm::vec3& getRight() const { return m_Right; }
		const glm::vec3& getWorldUp() const { return m_WorldUp; }
		const glm::vec4& getSolidColor() const { return m_SolidColor; }
		void setWorldPos(const glm::vec3& vPosition);
		void setFront(const glm::vec3& vFront);
		void setWorldUp(const glm::vec3& vWorldUp);
		void setSolidColor(const glm::vec4& vSolidColor) { m_SolidColor = vSolidColor; }
		const std::shared_ptr<CFrameBuffer>& getFrameBuffer() const { return m_pFrameBuffer; }
		virtual void setViewport(int vWidth, int vHeight) { m_pFrameBuffer->resize(vWidth, vHeight); }
		const SFrustum& getFrustum() const { return m_Frustum; }
	protected:
		virtual void _updateProjectionMatrix() {}
		virtual void _updateFrustum() {}
		glm::mat4 m_ProjectionMatrix;
		std::shared_ptr<CFrameBuffer> m_pFrameBuffer;
		SFrustum m_Frustum;
	private:
		void __updateViewMatrix();
		void __updateCameraVectors();
		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		glm::vec4 m_SolidColor;
	};
}