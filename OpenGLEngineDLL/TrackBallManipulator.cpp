#include "pch.h"
#include "TrackBallManipulator.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace hiveEngine;

void CTrackBallManipulator::onMouseMovedV(float vPosX, float vPosY)
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

	if (m_IsMouseLeftDown)
	{
		__changeYaw(-OffsetX * m_Sensitvity);
		__changePitch(-OffsetY * m_Sensitvity);
	}

	if (m_IsMouseRightDown)
	{
		__translateCamera(OffsetX * m_MoveSpeed, -OffsetY * m_MoveSpeed);
	}
}

void CTrackBallManipulator::onMouseButtonClickedV(int vButton, int vAction, int vMods)
{
	_ASSERTE(m_pCamera);
	bool IsPress = vAction == GLFW_PRESS ? true : false;

	if (vButton == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_IsMouseLeftDown = IsPress;
	}
	else if (vButton == GLFW_MOUSE_BUTTON_RIGHT)
	{
		m_IsMouseRightDown = IsPress;
	}
}

void CTrackBallManipulator::onMouseScrolledV(float vOffsetY)
{
	_ASSERTE(m_pCamera);
	m_pCamera->scale(vOffsetY * m_ScaleSpeed);
}

void CTrackBallManipulator::__changePitch(float vAngle)
{
	glm::mat4 Mat = glm::rotate(glm::mat4(1.0f), glm::radians(vAngle), m_pCamera->getRight());

	m_pCamera->setEyePosition(Mat * glm::vec4(m_pCamera->getEyePosition(), 1.0f));
	m_pCamera->setUp(Mat * glm::vec4(m_pCamera->getUp(), 0.0f));
}

void CTrackBallManipulator::__changeYaw(float vAngle)
{
	glm::mat4 Mat = glm::rotate(glm::mat4(1.0f), glm::radians(vAngle), glm::vec3(0.0f, 1.0f, 0.0f));

	m_pCamera->setEyePosition(Mat * glm::vec4(m_pCamera->getEyePosition(), 1.0f));
	m_pCamera->setRight(Mat * glm::vec4(m_pCamera->getRight(), 0.0f));
	m_pCamera->setUp(Mat * glm::vec4(m_pCamera->getUp(), 0.0f));
}

void CTrackBallManipulator::__translateCamera(float vOffsetX, float vOffsetY)
{
	glm::vec3 EyePos = m_pCamera->getEyePosition();

	EyePos += m_pCamera->getRight() * vOffsetX;
	EyePos += m_pCamera->getUp() * vOffsetY;
	m_pCamera->setEyePosition(EyePos);
}