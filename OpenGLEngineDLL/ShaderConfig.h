#pragma once
#include "HiveConfig.h"

namespace hiveEngine
{
	const std::string SHADER = "SHADER";
	const std::string SHADER_SOURCE_FILE = "SHADER_SOURCE_FILE";

	const std::string RENDER_ALGORITHM = "RENDER_ALGORITHM";
	const std::string RENDER_TYPE = "RENDER_TYPE";
	const std::string RENDER_PASS = "RENDER_PASS";
	const std::string VERTEX_SHADER = "VERTEX_SHADER";
	const std::string FRAGMENT_SHADER = "FRAGMENT_SHADER";

	class CShaderConfig : public hiveConfig::CHiveConfig
	{
	public:
		CShaderConfig();
		~CShaderConfig() = default;

	private:
		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


