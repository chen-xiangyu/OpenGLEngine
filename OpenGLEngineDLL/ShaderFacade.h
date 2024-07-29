#pragma once
#include "HiveLogger.h"
#include "ShaderUnit.h"
#include "ShaderManager.h"

namespace hiveEngine
{
	class CShaderFacade
	{
	public:
		CShaderFacade() = default;
		~CShaderFacade() = default;

		void addShader(const std::string& vVertexFilename, const std::string& vFragmentFilename);
		void setCurrentShader(unsigned int vID);
		void use();
		size_t getNumShader() const;

		void setUniformBool(const std::string& vName, bool vValue) const;
		void setUniformInt(const std::string& vName, int vValue) const;
		void setUniformFloat(const std::string& vName, float vValue) const;
		void setUniformMatrix4fv(const std::string& vName, const glm::mat4& vValue) const;
		void setUniform3fv(const std::string& vName, const glm::vec3& vValue) const;

	private:
		CShaderManager m_ShaderManager;
		std::shared_ptr<CShaderUnit> m_pCurrentShader = nullptr;

		template<typename Func>
		void __applyToCurrentShader(Func&& vFunc) const
		{
			if (m_pCurrentShader == nullptr)
			{
				HIVE_LOG_ERROR("Fail to use shader, because it is null");
				return;
			}
			vFunc(m_pCurrentShader.get());
		}
	};
}
