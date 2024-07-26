#include "pch.h"
#include "EngineConfig.h"
#include <GLFW/glfw3.h>
#include "Factory.h"
#include "CommonMicro.h"
#include "HiveLogger.h"
#include "AttributesNameMapping.h"
#include "AttributesRange.h"

using namespace hiveEngine;

_REGISTER_NORMAL_PRODUCT(CEngineConfig, "ENGINE_CONFIG")

CEngineConfig::CEngineConfig()
{
	_overwriteProductSig("ENGINE_CONFIG");
	__defineAttributesV();
}

void CEngineConfig::__defineAttributesV()
{
	std::map<std::string, hiveConfig::EConfigDataType> Attributes = {
		{OPENGL_ENGINE, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},
		{GLFW_SETTINGS, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},
		{WINDOW_SETTINGS, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},

		{VERSION_MAJOR, hiveConfig::EConfigDataType::ATTRIBUTE_INT},
		{VERSION_MINOR, hiveConfig::EConfigDataType::ATTRIBUTE_INT},
		{PROFILE, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},
		{SCREEN_WIDTH, hiveConfig::EConfigDataType::ATTRIBUTE_INT},
		{SCREEN_HEIGHT, hiveConfig::EConfigDataType::ATTRIBUTE_INT},
		{SCREEN_TITLE, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},
		{INIT_POSITION, hiveConfig::EConfigDataType::ATTRIBUTE_VEC2I},

		{SHADER_CONFIG_FILE, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},
		{LIGHT_DIRECTION, hiveConfig::EConfigDataType::ATTRIBUTE_VEC3F},

	};
	for (const auto& Item : Attributes)
	{
		_defineAttribute(Item.first, Item.second);
	}
}

void CEngineConfig::__loadDefaultConfigV()
{
	std::map<std::string, std::any> DefaultValue = {
		{VERSION_MAJOR, 4},
		{VERSION_MINOR, 3},
		{PROFILE, std::string("GLFW_OPENGL_CORE_PROFILE")},
		{SCREEN_WIDTH, 800},
		{SCREEN_HEIGHT, 600},
		{SCREEN_TITLE, std::string("Learn OpenGL")},
		{INIT_POSITION, std::tuple<int, int>(100, 200)},
		{LIGHT_DIRECTION, std::tuple<double, double, double>(0.0, 0.0, 1.0)},
	};
	for (const auto& Item : DefaultValue)
	{
		setAttribute(Item.first, Item.second);
	}
}

bool CEngineConfig::bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier)
{
	if (!isAttributeExisted(vName))
	{
		HIVE_LOG_ERROR("Failed to bind, attribute {} is not existed", vName);
		return false;
	}
	m_Modifiers.insert(std::make_pair(vName, vModifier));
	return true;
}

void CEngineConfig::applyAttributeModifiers()
{
	for (const auto& Item : m_Modifiers)
	{
		overwriteAttribute(Item.first, Item.second());
	}
}

void CEngineConfig::validateAttributes()
{
	//m_Validator.registerValidateRegulation<int>(VERSION_MAJOR, [](const int& vValue) -> bool {
	//	return true;
	//});

}

//void CEngineConfig::correctVersion()
//{
//	int Major = getAttribute<int>(VERSION_MAJOR).value();
//	int Minor = getAttribute<int>(VERSION_MINOR).value();
//
//	if (!CVersionRange::isCorrect(std::make_pair(Major, Minor)))
//	{
//		std::pair<int, int> t = CVersionRange::getDefaultValue();
//		overwriteAttribute(VERSION_MAJOR, t.first);
//		overwriteAttribute(VERSION_MINOR, t.second);
//	}
//}
//
//void CEngineConfig::correctProfile()
//{
//	std::string t = getAttribute<std::string>(PROFILE).value();
//
//	if (!CProfileRange::isCorrect(t))
//	{
//		t = CProfileRange::getDefaultValue();
//		overwriteAttribute(PROFILE, t);
//	}
//}
//
//void CEngineConfig::correctScreenSize()
//{
//	int Width = getAttribute<int>(SCREEN_WIDTH).value();
//	int Height = getAttribute<int>(SCREEN_HEIGHT).value();
//
//	if (!CScreenSizeRange::isCorrect(std::make_pair(Width, Height)))
//	{
//		std::pair<int, int> t = CScreenSizeRange::getDefaultValue();
//		overwriteAttribute(SCREEN_WIDTH, t.first);
//		overwriteAttribute(SCREEN_HEIGHT, t.second);
//	}
//}