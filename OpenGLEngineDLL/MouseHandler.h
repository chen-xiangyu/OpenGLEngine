#pragma once
#include <GLFW/glfw3.h>

namespace hiveEngine
{
	class CMouseHandler
	{
	private:
		using MouseMovedCallback = std::function<void(int, int)>;
		using MouseBottonClickedCallback = std::function<void(int, int, int)>;
		using MouseScrolledCallback = std::function<void(int, int)>;

	public:
		CMouseHandler() = default;
		~CMouseHandler() = default;

		void bindCallbackToWindow(GLFWwindow* vWindow);

		int registerMouseMovedCallback(const MouseMovedCallback& vCallback);
		int registerMouseBottonClickedCallback(const MouseBottonClickedCallback& vCallback);
		int registerMouseScrolledCallback(const MouseScrolledCallback& vCallback);

		void unregisterMouseMovedCallbackByID(int vID);
		void unregisterMouseBottonClickedCallbackByID(int vID);
		void unregisterMouseScrolledCallbackByID(int vID);

	private:
		static std::map<int, MouseMovedCallback> m_MouseMovedCallbacks;
		static std::map<int, MouseBottonClickedCallback> m_MouseButtonClickedCallbacks;
		static std::map<int, MouseScrolledCallback> m_MouseScrolledCallbacks;

		static int m_MouseMovedCallbackID;
		static int m_MouseButtonClickedCallbackID;
		static int m_MouseScrolledCallbackID;

		static void __bindCursorCallback(GLFWwindow* vWindow, double vXPos, double vYPos);
		static void __bindMouseButtonCallback(GLFWwindow* vWindow, int vButton, int vAction, int vMods);
		static void __bindMouseScrollCallback(GLFWwindow* vWindow, double vOffsetX, double vOffsetY);
	};
}