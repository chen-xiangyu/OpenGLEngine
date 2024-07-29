#include "pch.h"
#include "ShaderManager.h"

using namespace hiveEngine;

void CShaderManager::addShader(const std::string& vVertexFilename, const std::string& vFragmentFilename)
{
	auto Shader = std::make_shared<CShaderUnit>();
	//Shader->init(vVertexFilename, vFragmentFilename);
	m_ShaderList.push_back(Shader);
}

std::shared_ptr<CShaderUnit> CShaderManager::getShader(unsigned int vID)
{
	if (vID < m_ShaderList.size())
	{
		return m_ShaderList[vID];
	}
	return nullptr;
}

size_t CShaderManager::getNumShader() const
{
	return m_ShaderList.size();
}