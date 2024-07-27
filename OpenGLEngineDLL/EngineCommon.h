#pragma once
#include <map>
#include <GLFW/glfw3.h>

namespace hiveEngine
{
	enum class EKeyType : unsigned int
	{
		KEY_A,
		KEY_B,
	};

	enum class EKeyStatus : unsigned int
	{
		PRESS,
	};

	const std::map<EKeyType, GLuint> KeyTypeMapping = {
		{EKeyType::KEY_A, GLFW_KEY_A},
		{EKeyType::KEY_B, GLFW_KEY_B},
	};

	const std::map<EKeyStatus, GLuint> KeyStatusMapping = {
		{EKeyStatus::PRESS, GLFW_PRESS},
	};
}