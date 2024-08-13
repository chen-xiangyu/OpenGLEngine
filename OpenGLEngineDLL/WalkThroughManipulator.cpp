#include "pch.h"
#include "WalkThroughManipulator.h"
#include <GLFW/glfw3.h>

using namespace hiveEngine;

void CWalkThroughManipulator::onMouseMovedV(float vPosX, float vPosY)
{
	_ASSERTE(m_pCamera);
	if (m_IsCursorFirstEnter)
	{
		m_CursorPosX = vPosX;
		m_CursorPosY = vPosY;
		m_IsCursorFirstEnter = false;
	}
	float OffsetX = vPosX - m_CursorPosX;
	float OffsetY = vPosY - m_CursorPosY;
	m_CursorPosX = vPosX;
	m_CursorPosY = vPosY;

	__changeYaw(-OffsetX * m_Sensitvity);
	__changePitch(-OffsetY * m_Sensitvity);
}

void CWalkThroughManipulator::onMouseScrolledV(float vOffsetY)
{
	_ASSERTE(m_pCamera);
	m_pCamera->scale(vOffsetY * m_ScaleSpeed);
}

void CWalkThroughManipulator::onKeyPressedV(int vKey, int vAction, int vMods)
{
	_ASSERTE(m_pCamera);
	if (vAction == GLFW_REPEAT) return;

	m_KeyStatus[vKey] = vAction == GLFW_PRESS ? true : false;
	__translateCamera();
}

void CWalkThroughManipulator::__changePitch(float vAngle)
{
	m_Pitch += vAngle;
	if (m_Pitch > m_MaxPitch || m_Pitch < m_MinPitch)
	{
		m_Pitch -= vAngle;
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

	glm::vec3 EyePos = m_pCamera->getEyePosition();
	glm::vec3 Right = m_pCamera->getRight();
	glm::vec3 Lookat = m_pCamera->getLookat();

	if (m_KeyStatus[GLFW_KEY_A]) Direction -= Right;
	if (m_KeyStatus[GLFW_KEY_D]) Direction += Right;
	if (m_KeyStatus[GLFW_KEY_W]) Direction += Lookat;
	if (m_KeyStatus[GLFW_KEY_S]) Direction -= Lookat;

	if (glm::length(Direction) > 0)
	{
		Direction = glm::normalize(Direction);
		EyePos += Direction * m_MoveSpeed;
		m_pCamera->setEyePosition(EyePos);
	}
}