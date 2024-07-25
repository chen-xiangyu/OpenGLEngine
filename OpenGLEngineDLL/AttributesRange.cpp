#include "pch.h"
#include "AttributesRange.h"

using namespace hiveEngine;

const std::set<std::pair<int, int>> CVersionRange::m_Versions = {
	{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4},
	{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
};
const std::pair<int, int> CVersionRange::m_DefaultValue = { 3, 3 };

const std::set<std::string> CProfileRange::m_Profiles = {
	"GLFW_OPENGL_CORE_PROFILE",
	"GLFW_OPENGL_COMPAT_PROFILE",
	"GLFW_OPENGL_ANY_PROFILE"
};
const std::string CProfileRange::m_DefaultValue = "GLFW_OPENGL_CORE_PROFILE";

const std::pair<int, int> CScreenSizeRange::m_DefaultValue = { 800, 600 };