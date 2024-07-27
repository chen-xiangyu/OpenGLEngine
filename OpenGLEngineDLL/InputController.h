#pragma once
#include <GLFW/glfw3.h>
#include "EngineCommon.h"
#include "EditableConfig.h"

namespace hiveEngine
{
	typedef std::pair<EKeyType, EKeyStatus> KeyEventType;

	struct SKeyCallback
	{
		std::function<std::map<std::string, std::any>(const CEditableConfig&)> _Callback;
		std::chrono::steady_clock::time_point _LastTime;
	};

	class CInputController
	{
	public:
		CInputController() = default;
		~CInputController() = default;

		void bindInputEvent(const KeyEventType& vKeyEvent, const std::function<std::map<std::string, std::any>(const CEditableConfig&)> vCallback);
		void handleInput(GLFWwindow* vWindow, CEditableConfig& vConfig);

	private:
		std::map<KeyEventType, SKeyCallback> m_InputCallbacks;
		const int m_InputIntervalMS = 100;

	};
}