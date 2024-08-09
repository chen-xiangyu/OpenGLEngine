#include "pch.h"
#include "TrackBallManipulator.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace hiveEngine;

void CTrackBallManipulator::onMouseMove(float vPosX, float vPosY)
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

	if (m_IsMouseLeftPressed)
	{
		__changeYaw(-OffsetX * m_Sensitvity);
		__changePitch(OffsetY * m_Sensitvity);
	}

	if (m_IsMouseRightPressed)
	{
		__translateCamera(OffsetX * m_MoveSpeed, OffsetY * m_MoveSpeed);
	}
}

void CTrackBallManipulator::onMouseButton(int vButton, int vAction, int vMods)
{
	bool IsPress = vAction == GLFW_PRESS ? true : false;

	if (vButton == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_IsMouseLeftPressed = IsPress;
	}
	else if (vButton == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		m_IsMouseMiddlePressed = IsPress;
	}
	else if (vButton == GLFW_MOUSE_BUTTON_RIGHT)
	{
		m_IsMouseRightPressed = IsPress;
	}
}

void CTrackBallManipulator::onMouseScroll(float vOffsetY)
{
	m_pCamera->scale(vOffsetY * m_ScaleSpeed);
}

void CTrackBallManipulator::__changePitch(float vAngle)
{
	glm::mat4 Mat = glm::rotate(glm::mat4(1.0f), glm::radians(vAngle), m_pCamera->getRight());

	m_pCamera->setPosition(Mat * glm::vec4(m_pCamera->getPosition(), 1.0f));
	m_pCamera->setUp(Mat * glm::vec4(m_pCamera->getUp(), 0.0f));
}

void CTrackBallManipulator::__changeYaw(float vAngle)
{
	glm::mat4 Mat = glm::rotate(glm::mat4(1.0f), glm::radians(vAngle), glm::vec3(0.0f, 1.0f, 0.0f));

	m_pCamera->setPosition(Mat * glm::vec4(m_pCamera->getPosition(), 1.0f));
	m_pCamera->setRight(Mat * glm::vec4(m_pCamera->getRight(), 0.0f));
	m_pCamera->setUp(Mat * glm::vec4(m_pCamera->getUp(), 0.0f));
}

void CTrackBallManipulator::__translateCamera(float vOffsetX, float vOffsetY)
{
	glm::vec3 Position = m_pCamera->getPosition();

	Position += m_pCamera->getRight() * vOffsetX;
	Position += m_pCamera->getUp() * vOffsetY;
	m_pCamera->setPosition(Position);
}