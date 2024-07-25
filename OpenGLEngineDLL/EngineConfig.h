#pragma once
#include "HiveConfig.h"

namespace hiveEngine
{
	class CEngineConfig : public hiveConfig::CHiveConfig
	{
	public:
		CEngineConfig();
		~CEngineConfig() = default;

		void correctVerson();
		void correctProfile();
		void correctScreenSize();

	private:
		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


