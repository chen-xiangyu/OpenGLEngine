
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace hiveGL
{
	CCamera::CCamera() :
		m_Position(0.0f, 0.0f, 0.0f),
		m_Front(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f), m_Right(1.0f, 0.0f, 0.0f), m_WorldUp(0.0f, 1.0f, 0.0f),
		m_ViewMatrix{}, m_ProjectionMatrix{}, m_SolidColor(0.2f, 0.3f, 0.3f, 1.0f),
		m_pFrameBuffer(CFrameBuffer::getDefaultFrameBuffer())
	{
		__updateCameraVectors();
		__updateViewMatrix();
		_updateProjectionMatrix();
	}

	void CCamera::setWorldPos(const glm::vec3& vPosition)
	{
		m_Position = vPosition;
		__updateViewMatrix();
		_updateFrustum();
	}

	void CCamera::setFront(const glm::vec3& vFront)
	{
		m_Front = vFront;
		__updateCameraVectors();
		__updateViewMatrix();
		_updateFrustum();
	}

	void CCamera::setWorldUp(const glm::vec3& vWorldUp)
	{
		m_WorldUp = vWorldUp;
		__updateCameraVectors();
		__updateViewMatrix();
		_updateFrustum();
	}

	void CCamera::__updateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void CCamera::__updateCameraVectors()
	{
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}