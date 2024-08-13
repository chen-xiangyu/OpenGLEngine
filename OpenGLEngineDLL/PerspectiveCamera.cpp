#include "pch.h"
#include "PerspectiveCamera.h"

using namespace hiveEngine;

CPerspectiveCamera::CPerspectiveCamera()
{
	_updateProjectionMat();
}

void CPerspectiveCamera::_updateProjectionMat()
{
	m_ProjectionMat = glm::perspective(glm::radians(m_Fov), m_Aspect, m_ZNear, m_ZFar);
}

void CPerspectiveCamera::scale(float vValue)
{
	glm::vec3 Lookat = getLookat();
	glm::vec3 EyePos = getEyePosition();
	EyePos += vValue * Lookat;
	setEyePosition(EyePos);
}

void CPerspectiveCamera::setFov(float vFov)
{
	m_Fov = vFov;
	_updateProjectionMat();
}

void CPerspectiveCamera::setAspect(float vAspect)
{
	m_Aspect = vAspect;
	_updateProjectionMat();
}

void CPerspectiveCamera::setZNear(float vZNear)
{
	m_ZNear = vZNear;
	_updateProjectionMat();
}

void CPerspectiveCamera::setZFar(float vZFar)
{
	m_ZFar = vZFar;
	_updateProjectionMat();
}