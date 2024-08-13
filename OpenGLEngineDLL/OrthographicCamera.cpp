#include "pch.h"
#include "OrthographicCamera.h"

using namespace hiveEngine;

COrthographicCamera::COrthographicCamera()
{
	_updateProjectionMat();
}

void COrthographicCamera::scale(float vValue)
{
	m_Scale += vValue;
	_updateProjectionMat();
}

void COrthographicCamera::_updateProjectionMat()
{
	float Scale = std::pow(2.0f, m_Scale);
	m_ProjectionMat = glm::ortho(m_Left * Scale, m_Right * Scale, m_Bottom * Scale, m_Top * Scale, m_Near, m_Far);
}

void COrthographicCamera::setLeft(float vLeft) 
{
	m_Left = vLeft; 
	_updateProjectionMat();
}

void COrthographicCamera::setRight(float vRight)
{ 
	m_Right = vRight; 
	_updateProjectionMat();
}

void COrthographicCamera::setTop(float vTop) 
{
	m_Top = vTop; 
	_updateProjectionMat();
}

void COrthographicCamera::setBottom(float vBottom) 
{
	m_Bottom = vBottom; 
	_updateProjectionMat();
}

void COrthographicCamera::setNear(float vNear)
{ 
	m_Near = vNear;
	_updateProjectionMat();
}

void COrthographicCamera::setFar(float vFar)
{ 
	m_Far = vFar; 
	_updateProjectionMat();
}