#include "pch.h"
#include "EditableConfig.h"

using namespace hiveEngine;

_REGISTER_NORMAL_PRODUCT(CEditableConfig, "EDITABLE_CONFIG")

CEditableConfig::CEditableConfig()
{
	_overwriteProductSig("EDITABLE_CONFIG");
	__defineAttributesV();
}

void CEditableConfig::__defineAttributesV()
{
	std::map<std::string, hiveConfig::EConfigDataType> Attributes = {
		{NUM_SHADER, hiveConfig::EConfigDataType::ATTRIBUTE_INT},
		{WORKING_SHADER_ID, hiveConfig::EConfigDataType::ATTRIBUTE_INT},
	};
	for (const auto& Item : Attributes)
	{
		_defineAttribute(Item.first, Item.second);
	}
}

void CEditableConfig::__loadDefaultConfigV()
{

}