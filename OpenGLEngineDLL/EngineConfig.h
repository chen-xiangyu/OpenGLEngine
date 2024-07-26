#pragma once
#include "HiveConfig.h"

namespace hiveEngine
{
	class CEngineConfig : public hiveConfig::CHiveConfig
	{
	public:
		CEngineConfig();
		~CEngineConfig() = default;

		bool bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier);
		void applyAttributeModifiers();

		void correctVerson();
		void correctProfile();
		void correctScreenSize();

	private:
		std::map<std::string, std::function<std::any()>> m_Modifiers;

		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


