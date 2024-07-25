#include "pch.h"
#include "ShaderConfig.h"
#include "AttributesNameMapping.h"

using namespace hiveEngine;

_REGISTER_NORMAL_PRODUCT(CShaderConfig, "SHADER_CONFIG")

CShaderConfig::CShaderConfig()
{
	_overwriteProductSig("SHADER_CONFIG");
	__defineAttributesV();
}

void CShaderConfig::__defineAttributesV()
{
	std::map<std::string, hiveConfig::EConfigDataType> Attributes = {
		{SHADER, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},
		{SHADER_SOURCE_FILE, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},
		{RENDER_ALGORITHM, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},
		{RENDER_PASS, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},
		{VERTEX_SHADER, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},
		{FRAGMENT_SHADER, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},

	};
	for (const auto& Item : Attributes)
	{
		_defineAttribute(Item.first, Item.second);
	}
}

void CShaderConfig::__loadDefaultConfigV()
{

}