#include "pch.h"
#include "KeyboardHandler.h"

using namespace hiveEngine;

std::map<int, CKeyboardHandler::KeyPressedCallback>  CKeyboardHandler::m_KeyPressedCallbacks;
int CKeyboardHandler::m_KeyPressedCallbackID = 0;

void CKeyboardHandler::bindCallbackToWindow(GLFWwindow* vWindow)
{
	glfwSetWindowUserPointer(vWindow, this);

	//glfwSetKeyCallback(vWindow, [](GLFWwindow* vWindow, int vKey, int vScancode, int vAction, int vMods) {
	//	static_cast<CKeyboardHandler*>(glfwGetWindowUserPointer(vWindow))->__bindKeyCallback(vWindow, vKey, vScancode, vAction, vMods);
	//	});
	glfwSetKeyCallback(vWindow, __bindKeyCallback);
}

int CKeyboardHandler::registerKeyPressedCallback(const KeyPressedCallback& vCallback)
{
	_ASSERTE(vCallback);
	m_KeyPressedCallbacks.insert(std::make_pair(m_KeyPressedCallbackID, vCallback));

	return	m_KeyPressedCallbackID++;
}

void CKeyboardHandler::unregisterKeyPressedCallbackByID(int vID)
{
	if (m_KeyPressedCallbacks.find(vID) != m_KeyPressedCallbacks.end())
	{
		m_KeyPressedCallbacks.erase(vID);
	}
}

void CKeyboardHandler::__bindKeyCallback(GLFWwindow* vWindow, int vKey, int vScancode, int vAction, int vMods)
{
	for (const auto& Item : m_KeyPressedCallbacks)
	{
		Item.second(vKey, vScancode, vAction, vMods);
	}
}