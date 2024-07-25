#pragma once
#include <string>
#include <GLFW/glfw3.h>

namespace hiveEngine
{
	const std::string OPENGL_ENGINE = "OPENGL_ENGINE";
	const std::string GLFW_SETTINGS = "GLFW_SETTINGS";
	const std::string WINDOW_SETTINGS = "WINDOW_SETTINGS";

	const std::string VERSION_MAJOR = "VERSION_MAJOR";
	const std::string VERSION_MINOR = "VERSION_MINOR";
	const std::string PROFILE = "PROFILE";

	const std::string SCREEN_WIDTH = "WIDTH";
	const std::string SCREEN_HEIGHT = "HEIGHT";
	const std::string SCREEN_TITLE = "TITLE";
	const std::string INIT_POSITION = "INIT_POSITION";

	const std::string SHADER_CONFIG_FILE = "SHADER_CONFIG_FILE";

	const std::string SHADER = "SHADER";
	const std::string SHADER_SOURCE_FILE = "SHADER_SOURCE_FILE";
	const std::string RENDER_ALGORITHM = "RENDER_ALGORITHM";
	const std::string RENDER_PASS = "RENDER_PASS";
	const std::string VERTEX_SHADER = "VERTEX_SHADER";
	const std::string FRAGMENT_SHADER = "FRAGMENT_SHADER";


	const std::map<std::string, unsigned int> ProfileMapping = {
		{"GLFW_OPENGL_CORE_PROFILE", GLFW_OPENGL_CORE_PROFILE},
		{"GLFW_OPENGL_COMPAT_PROFILE", GLFW_OPENGL_COMPAT_PROFILE},
		{"GLFW_OPENGL_ANY_PROFILE", GLFW_OPENGL_ANY_PROFILE},
	};
}
