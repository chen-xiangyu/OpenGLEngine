#pragma once
#include "HiveConfig.h"

namespace hiveEngine
{
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


