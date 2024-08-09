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
		{WORKING_RENDER_ALGORITHM, hiveConfig::EConfigDataType::ATTRIBUTE_STRING},
		{IS_TRACKBALL, hiveConfig::EConfigDataType::ATTRIBUTE_BOOL},
	};
	for (const auto& Item : Attributes)
	{
		_defineAttribute(Item.first, Item.second);
	}
}

void CEditableConfig::__loadDefaultConfigV()
{
	std::map<std::string, std::any> DefaultValue = {
		//{WORKING_RENDER_ALGORITHM, ""},
	};
	for (const auto& Item : DefaultValue)
	{
		setAttribute(Item.first, Item.second);
	}
}

bool CEditableConfig::bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier)
{
	if (!isAttributeExisted(vName))
	{
		HIVE_LOG_ERROR("Failed to bind, attribute {} is not existed", vName);
		return false;
	}
	m_Modifiers.insert(std::make_pair(vName, vModifier));
	return true;
}

void CEditableConfig::applyAttributeModifiers()
{
	for (const auto& Item : m_Modifiers)
	{
		overwriteAttribute(Item.first, Item.second());
	}
}