#include "pch.h"
#include "MouseHandler.h"

using namespace hiveEngine;
void CMouseHandler::bindCallbackToWindow(GLFWwindow* vWindow)
{
	glfwSetWindowUserPointer(vWindow, this);
	glfwSetCursorPosCallback(vWindow, [](GLFWwindow* vWindow, double vXPos, double vYPos) {
		static_cast<CMouseHandler*>(glfwGetWindowUserPointer(vWindow))->__bindCursorCallback(vWindow, vXPos, vYPos);
		});
	glfwSetMouseButtonCallback(vWindow, [](GLFWwindow* vWindow, int vButton, int vAction, int vMods){
		static_cast<CMouseHandler*>(glfwGetWindowUserPointer(vWindow))->__bindMouseButtonCallback(vWindow, vButton, vAction, vMods);
		});
	glfwSetScrollCallback(vWindow, [](GLFWwindow* vWindow, double vOffsetX, double vOffsetY) {
		static_cast<CMouseHandler*>(glfwGetWindowUserPointer(vWindow))->__bindMouseScrollCallback(vWindow, vOffsetX, vOffsetY);
		});
}

int CMouseHandler::registerMouseMovedCallback(const MouseMovedCallback& vCallback)
{
	_ASSERTE(vCallback);
	m_MouseMovedCallbacks.insert(std::make_pair(m_MouseMovedCallbackID, vCallback));

	return	m_MouseMovedCallbackID++;
}

int CMouseHandler::registerMouseBottonClickedCallback(const MouseBottonClickedCallback& vCallback)
{
	_ASSERTE(vCallback);
	m_MouseButtonClickedCallbacks.insert(std::make_pair(m_MouseButtonClickedCallbackID, vCallback));
	
	return m_MouseButtonClickedCallbackID++;
}

int CMouseHandler::registerMouseScrolledCallback(const MouseScrolledCallback& vCallback)
{
	_ASSERTE(vCallback);
	m_MouseScrolledCallbacks.insert(std::make_pair(m_MouseScrolledCallbackID, vCallback));

	return m_MouseScrolledCallbackID++;
}

void CMouseHandler::unregisterMouseMovedCallbackByID(int vID)
{
	if (m_MouseMovedCallbacks.find(vID) != m_MouseMovedCallbacks.end())
	{
		m_MouseMovedCallbacks.erase(vID);
	}
}

void CMouseHandler::unregisterMouseBottonClickedCallbackByID(int vID)
{
	if (m_MouseButtonClickedCallbacks.find(vID) != m_MouseButtonClickedCallbacks.end())
	{
		m_MouseButtonClickedCallbacks.erase(vID);
	}
}

void CMouseHandler::unregisterMouseScrolledCallbackByID(int vID)
{
	if (m_MouseScrolledCallbacks.find(vID) != m_MouseScrolledCallbacks.end())
	{
		m_MouseScrolledCallbacks.erase(vID);
	}
}

void CMouseHandler::__bindCursorCallback(GLFWwindow* vWindow, double vXPos, double vYPos)
{
	for (const auto& Item : m_MouseMovedCallbacks)
	{
		Item.second(vXPos, vYPos);
	}
}

void CMouseHandler::__bindMouseButtonCallback(GLFWwindow* vWindow, int vButton, int vAction, int vMods)
{
	for (const auto& Item : m_MouseButtonClickedCallbacks)
	{
		Item.second(vButton, vAction, vMods);
	}
}

void CMouseHandler::__bindMouseScrollCallback(GLFWwindow* vWindow, double vOffsetX, double vOffsetY)
{
	for (const auto& Item : m_MouseScrolledCallbacks)
	{
		Item.second(vOffsetX, vOffsetY);
	}
}
