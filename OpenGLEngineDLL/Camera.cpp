#include "pch.h"
#include "Camera.h"

using namespace hiveEngine;

ICamera::ICamera()
{
	__updateViewMat();
}

void ICamera::__updateViewMat()
{
	glm::vec3 Front = glm::cross(m_Up, m_Right);
	glm::vec3 Center = m_Position + Front;
	m_ViewMat = glm::lookAt(m_Position, Center, m_Up);
}

void ICamera::setPosition(const glm::vec3& vPosition)
{
	m_Position = vPosition;
	__updateViewMat();
}

void ICamera::setRight(const glm::vec3& vRight)
{
	m_Right = vRight;
	__updateViewMat();
}

void ICamera::setUp(const glm::vec3& vUp)
{
	m_Up = vUp;
	__updateViewMat();
}