#include "pch.h"
#include "CameraManipulator.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace hiveEngine;

void ICameraManipulator::setCamera(ICamera* vCamera)
{
	_ASSERTE(vCamera);
	m_pCamera = vCamera; 
}

void ICameraManipulator::setSensitivity(float vSensitivity)
{
	_ASSERTE(vSensitivity > 0);
	m_Sensitvity = vSensitivity; 
}

void ICameraManipulator::setMoveSpeed(float vMoveSpeed)
{ 
	_ASSERTE(vMoveSpeed > 0);
	m_MoveSpeed = vMoveSpeed; 
}