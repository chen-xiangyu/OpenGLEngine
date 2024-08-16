#pragma once
#include <GLFW/glfw3.h>

namespace hiveEngine
{
	class CKeyboardHandler
	{
	private:
		using KeyPressedCallback = std::function<void(int, int, int, int)>;

	public:
		CKeyboardHandler() = default;
		~CKeyboardHandler() = default;

		void bindCallbackToWindow(GLFWwindow* vWindow);

		int registerKeyPressedCallback(const KeyPressedCallback& vCallback);
		void unregisterKeyPressedCallbackByID(int vID);

	private:
		static std::map<int, KeyPressedCallback> m_KeyPressedCallbacks;
		static int m_KeyPressedCallbackID;

		static void __bindKeyCallback(GLFWwindow* vWindow, int vKey, int vScancode, int vAction, int vMods);
	};
}