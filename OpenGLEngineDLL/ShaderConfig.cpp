#include "pch.h"
#include "ShaderConfig.h"

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
		{RENDER_TYPE, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},
		{RENDER_PASS, hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG},
		{VERTEX_SHADER, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},
		{FRAGMENT_SHADER, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},

	};
	for (const auto& Item : Attributes)
	{
		_defineAttribute(Item.first, Item.second);
	}
}

void CShaderConfig::__loadDefaultConfigV()
{

}