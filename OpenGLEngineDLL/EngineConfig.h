#pragma once
#include "HiveConfig.h"
#include "AttributeValidator.h"

namespace hiveEngine
{
	const std::string OPENGL_ENGINE = "OPENGL_ENGINE";

	const std::string GLFW_SETTINGS = "GLFW_SETTINGS";
	const std::string VERSION_MAJOR = "VERSION_MAJOR";
	const std::string VERSION_MINOR = "VERSION_MINOR";
	const std::string PROFILE = "PROFILE";

	const std::string WINDOW_SETTINGS = "WINDOW_SETTINGS";
	const std::string SCREEN_WIDTH = "WIDTH";
	const std::string SCREEN_HEIGHT = "HEIGHT";
	const std::string SCREEN_TITLE = "TITLE";
	const std::string INIT_POSITION = "INIT_POSITION";

	const std::string SHADER_CONFIG_FILE = "SHADER_CONFIG_FILE";

	const std::string GLTF_FILE = "GLTF_FILE";

	class CEngineConfig : public hiveConfig::CHiveConfig
	{
	public:
		CEngineConfig();
		~CEngineConfig() = default;

		bool bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier);
		void applyAttributeModifiers();

		void validateAttributes();

		//void correctVersion();
		//void correctProfile();
		//void correctScreenSize();

	private:
		std::map<std::string, std::function<std::any()>> m_Modifiers;
		CAttributeValidator m_Validator;

		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


