#include "pch.h"
#include "Camera.h"

using namespace hiveEngine;

ICamera::ICamera()
{
	__updateViewMat();
}

void ICamera::__updateViewMat()
{
	m_ViewMat = glm::lookAt(m_EyePos, m_EyePos + m_Lookat, m_Up);
}

void ICamera::setEyePosition(const glm::vec3& vEyePos)
{
	m_EyePos = vEyePos;
	__updateViewMat();
}

void ICamera::setRight(const glm::vec3& vRight)
{
	m_Right = vRight;
	m_Lookat = glm::cross(m_Up, m_Right);
	__updateViewMat();
}

void ICamera::setUp(const glm::vec3& vUp)
{
	m_Up = vUp;
	m_Lookat = glm::cross(m_Up, m_Right);
	__updateViewMat();
}

//*******************************************************
//Function:
void ICamera::setLookat(const glm::vec3& vLookat)
{
	m_Lookat = vLookat;
	m_Right = glm::cross(m_Lookat, m_Up);
	__updateViewMat();
}