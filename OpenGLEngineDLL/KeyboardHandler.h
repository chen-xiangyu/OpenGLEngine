#pragma once
#include <GLFW/glfw3.h>
#include "Singleton.h"

namespace hiveEngine
{
	class CKeyboardHandler : public hiveCommon::CSingleton<CKeyboardHandler>
	{
		friend class hiveCommon::CSingleton<CKeyboardHandler>;
	private:
		using KeyPressedCallback = std::function<void(int, int, int, int)>;

		CKeyboardHandler() = default;
		~CKeyboardHandler() = default;

	public:
		void bindCallbackToWindow(GLFWwindow* vWindow);

		int registerKeyPressedCallback(const KeyPressedCallback& vCallback);
		void unregisterKeyPressedCallbackByID(int vID);

	private:
		static std::map<int, KeyPressedCallback> m_KeyPressedCallbacks;
		static int m_KeyPressedCallbackID;

		static void __bindKeyCallback(GLFWwindow* vWindow, int vKey, int vScancode, int vAction, int vMods);
	};
}