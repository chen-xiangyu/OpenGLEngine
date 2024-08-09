#include "pch.h"
#include "WalkThroughManipulator.h"
#include <GLFW/glfw3.h>

using namespace hiveEngine;

void CWalkThroughManipulator::onMouseMove(float vPosX, float vPosY)
{
	if (m_IsFirst)
	{
		m_LastX = vPosX;
		m_LastY = vPosY;
		m_IsFirst = false;
	}
	float OffsetX = vPosX - m_LastX;
	float OffsetY = m_LastY - vPosY;
	m_LastX = vPosX;
	m_LastY = vPosY;

	__changeYaw(-OffsetX * m_Sensitvity);
	__changePitch(OffsetY * m_Sensitvity);
}

void CWalkThroughManipulator::onMouseScroll(float vOffsetY)
{
	m_pCamera->scale(vOffsetY * m_ScaleSpeed);
}

void CWalkThroughManipulator::onKeyboard(int vKey, int vAction, int vMods)
{
	if (vAction == GLFW_REPEAT) return;

	m_KeyStatus[vKey] = vAction == GLFW_PRESS ? true : false;
	__translateCamera();
}

void CWalkThroughManipulator::__changePitch(float vAngle)
{
	m_Patch += vAngle;
	if (m_Patch > 89.0f || m_Patch < -89.0f)
	{
		m_Patch -= vAngle;
		return;
	}

	glm::mat4 Mat = glm::rotate(glm::mat4(1.0f), glm::radians(vAngle), m_pCamera->getRight());
	m_pCamera->setUp(Mat * glm::vec4(m_pCamera->getUp(), 0.0f));
}

void CWalkThroughManipulator::__changeYaw(float vAngle)
{
	glm::mat4 Mat = glm::rotate(glm::mat4(1.0f), glm::radians(vAngle), glm::vec3(0.0f, 1.0f, 0.0f));

	m_pCamera->setRight(Mat * glm::vec4(m_pCamera->getRight(), 0.0f));
	m_pCamera->setUp(Mat * glm::vec4(m_pCamera->getUp(), 0.0f));
}

void CWalkThroughManipulator::__translateCamera()
{
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 Position = m_pCamera->getPosition();
	glm::vec3 Right = m_pCamera->getRight();
	glm::vec3 Front = glm::cross(m_pCamera->getUp(), Right);

	if (m_KeyStatus[GLFW_KEY_A]) Direction -= Right;
	if (m_KeyStatus[GLFW_KEY_D]) Direction += Right;
	if (m_KeyStatus[GLFW_KEY_W]) Direction += Front;
	if (m_KeyStatus[GLFW_KEY_S]) Direction -= Front;

	if (glm::length(Direction) > 0)
	{
		Direction = glm::normalize(Direction);
		Position += Direction * m_MoveSpeed;
		m_pCamera->setPosition(Position);
	}
}