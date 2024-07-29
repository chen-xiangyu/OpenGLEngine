
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace hiveGL
{
	CPerspectiveCamera::CPerspectiveCamera() :m_Zoom(45.0f), m_Aspect(1.0f), m_Near(0.1f), m_Far(100.0f)
	{
	}

	void CPerspectiveCamera::_updateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Zoom), m_Aspect, m_Near, m_Far);
	}

	void CPerspectiveCamera::_updateFrustum()
	{
		const float HalfVSide = m_Far * tanf(glm::radians(m_Zoom) * 0.5f);
		const float HalfHSide = HalfVSide * m_Aspect;
		const glm::vec3 FrontMultFar = m_Far * getFront();

		m_Frustum._NearFace = { getWorldPos() + m_Near * getFront(), getFront() };
		m_Frustum._FarFace = { getWorldPos() + FrontMultFar, -getFront() };
		m_Frustum._RightFace = { getWorldPos(), glm::cross(FrontMultFar - getRight() * HalfHSide, getUp()) };
		m_Frustum._LeftFace = { getWorldPos(), glm::cross(getUp(), FrontMultFar + getRight() * HalfHSide) };
		m_Frustum._TopFace = { getWorldPos(), glm::cross(getRight(), FrontMultFar - getUp() * HalfVSide) };
		m_Frustum._BottomFace = { getWorldPos(), glm::cross(FrontMultFar + getUp() * HalfVSide, getRight()) };
	}

	void CPerspectiveCamera::setViewport(int vWidth, int vHeight)
	{
		CCamera::setViewport(vWidth, vHeight);
		setAspect((float)vWidth / (float)vHeight);
	}

	void CPerspectiveCamera::setZoom(float vZoom)
	{
		m_Zoom = vZoom;
		_updateProjectionMatrix();
		_updateFrustum();
	}

	void CPerspectiveCamera::setAspect(float vAspect)
	{
		m_Aspect = vAspect;
		_updateProjectionMatrix();
		_updateFrustum();
	}

	void CPerspectiveCamera::setNear(float vNear)
	{
		m_Near = vNear;
		_updateProjectionMatrix();
		_updateFrustum();
	}

	void CPerspectiveCamera::setFar(float vFar)
	{
		m_Far = vFar;
		_updateProjectionMatrix();
		_updateFrustum();
	}
}