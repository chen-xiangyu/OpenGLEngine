#pragma once
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <any>

namespace hiveEngine {
	class CAttributeValidator {
	public:
		CAttributeValidator() = default;
		~CAttributeValidator() = default;

		template <typename T>
		using ValidateRegulation = std::function<bool(const T&)>;

		template <typename T>
		//void registerValidateRegulation(std::string& vAttributeName, ValidateRegulation<T> vValidateRegulation)
		void registerValidateRegulation(const std::string& vAttributeName, const std::function<bool(const T&)>& vValidateRegulation)
		{
			m_AttributeValidateRegulation[vAttributeName] = [vValidateRegulation](const std::any& value)->bool {
				return vValidateRegulation(std::any_cast<const T&>(value));
			};
			m_AttributeType[vAttributeName] = typeid(T);

			// TODO 写到log里面，校验规则注册成功
			std::cout << "Validate regulation for attribute " << vAttributeName << " registered successfully." << std::endl;
		}

		template <typename T>
		bool validateAttribute(const std::string& vAttributeName, const T& vAttributeValue)
		{
			if (m_AttributeValidateRegulation.find(vAttributeName) != m_AttributeValidateRegulation.end())
			{
				if (m_AttributeType[vAttributeName] == typeid(T))
				{
					// TODO 写到log里面，校验规则应用成功
					std::cout << "Validate regulation for attribute " << vAttributeName << " applied successfully." << std::endl;

					return m_AttributeValidateRegulation[vAttributeName](vAttributeValue);
				}
				else
				{
					// TODO 写到log里面，参数类型不匹配
					std::cout << "Attribute type not match at attribute " << vAttributeName << "." << std::endl;
					return false;
				}
			}
			else
			{
				// TODO 写到log里面，没有找到对应参数校验规则
				std::cout << "No validate regulation for attribute " << vAttributeName << " found." << std::endl;
				return false;
			}
		}

	private:
		std::map<std::string, std::function<bool(const std::any&)>> m_AttributeValidateRegulation;
		std::map<std::string, std::type_index> m_AttributeType;
	};
}