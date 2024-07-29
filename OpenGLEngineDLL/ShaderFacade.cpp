#include "pch.h"
#include "ShaderFacade.h"

using namespace hiveEngine;

void CShaderFacade::addShader(const std::string& vVertexFilename, const std::string& vFragmentFilename)
{
	m_ShaderManager.addShader(vVertexFilename, vFragmentFilename);
	if (m_pCurrentShader == nullptr)
	{
		m_pCurrentShader = m_ShaderManager.getShader(0);
	}
}

void CShaderFacade::setCurrentShader(unsigned int vID)
{
	std::shared_ptr<CShaderUnit> t = m_ShaderManager.getShader(vID);
	if (t == nullptr)
	{
		HIVE_LOG_ERROR("Fail to set current shader by ID = {}", vID);
		return;
	}
	m_pCurrentShader = t;
}

void CShaderFacade::use()
{
	__applyToCurrentShader([](CShaderUnit* vShader) {
		vShader->use();
	});
}

size_t CShaderFacade::getNumShader() const
{
	return m_ShaderManager.getNumShader();
}

void CShaderFacade::setUniformBool(const std::string& vName, bool vValue) const
{
	__applyToCurrentShader([&](CShaderUnit* vShader) {
		vShader->setUniformBool(vName, vValue);
	});
}

void CShaderFacade::setUniformInt(const std::string& vName, int vValue) const
{
	__applyToCurrentShader([&](CShaderUnit* vShader) {
		vShader->setUniformInt(vName, vValue);
	});
}

void CShaderFacade::setUniformFloat(const std::string& vName, float vValue) const
{
	__applyToCurrentShader([&](CShaderUnit* vShader) {
		vShader->setUniformFloat(vName, vValue);
	});
}

void CShaderFacade::setUniformMatrix4fv(const std::string& vName, const glm::mat4& vValue) const
{
	__applyToCurrentShader([&](CShaderUnit* vShader) {
		vShader->setUniformMatrix4fv(vName, vValue);
	});
}

void CShaderFacade::setUniform3fv(const std::string& vName, const glm::vec3& vValue) const
{
	__applyToCurrentShader([&](CShaderUnit* vShader) {
		vShader->setUniform3fv(vName, vValue);
	});
}