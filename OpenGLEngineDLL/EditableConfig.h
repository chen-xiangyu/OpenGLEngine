#pragma once
#include "HiveConfig.h"

namespace hiveEngine
{
	const std::string NUM_SHADER = "NUM_SHADER";
	const std::string WORKING_SHADER_ID = "WORKING_SHADER_ID";

	class CEditableConfig : public hiveConfig::CHiveConfig
	{
	public:
		CEditableConfig();
		~CEditableConfig() = default;

	private:
		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}

