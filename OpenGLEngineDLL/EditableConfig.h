#pragma once
#include "HiveConfig.h"

namespace hiveEngine
{
	const std::string NUM_SHADER = "NUM_SHADER";
	const std::string WORKING_RENDER_ALGORITHM = "WORKING_RENDER_ALGORITHM";

	class CEditableConfig : public hiveConfig::CHiveConfig
	{
	public:
		CEditableConfig();
		~CEditableConfig() = default;

		bool bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier);
		void applyAttributeModifiers();

	private:
		std::map<std::string, std::function<std::any()>> m_Modifiers;

		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}

