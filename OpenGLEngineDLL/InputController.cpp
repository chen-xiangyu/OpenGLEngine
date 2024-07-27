#include "pch.h"
#include "InputController.h"

using namespace hiveEngine;

void CInputController::bindInputEvent(const KeyEventType& vKeyEvent, const std::function<std::map<std::string, std::any>(const CEditableConfig&)> vCallback)
{
	SKeyCallback t = { vCallback, std::chrono::steady_clock::now() };
	m_InputCallbacks.insert(std::make_pair(vKeyEvent, t));
}

void CInputController::handleInput(GLFWwindow* vWindow, CEditableConfig& vEditableConfig)
{
	std::chrono::steady_clock::time_point NowTime = std::chrono::steady_clock::now();

	for (auto& Item : m_InputCallbacks)
	{
		auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>(NowTime - Item.second._LastTime).count();
		if (Duration < m_InputIntervalMS) continue;

		Item.second._LastTime = NowTime;

		KeyEventType Event = Item.first;
		if (glfwGetKey(vWindow, KeyTypeMapping.at(Event.first)) == KeyStatusMapping.at(Event.second))
		{
			std::map<std::string, std::any> Result = Item.second._Callback(vEditableConfig);
			for (const auto& t : Result)
			{
				if (!vEditableConfig.isAttributeExisted(t.first))
				{
					HIVE_LOG_ERROR("Fail to set attribute {}, because it is not exist", t.first);
					continue;
				}
				vEditableConfig.overwriteAttribute(t.first, t.second);
			}
		}
	}
}