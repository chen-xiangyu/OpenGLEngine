#include "pch.h"
#include "RenderAlgorithm.h"

using namespace hiveEngine;

void IRenderAlgorithm::addShader(const std::string& vName, const std::string& vVertexFilename, const std::string& vFragmentFilename)
{
	CShaderUnit  Shader;
	Shader.init(vName, vVertexFilename, vFragmentFilename);
	m_Shaders.push_back(Shader);
}

bool IRenderAlgorithm::isContainShader(const std::string& vShaderName)
{
	for (const auto& Item : m_Shaders)
	{
		if (Item.getName() == vShaderName) return true;
	}
	return false;
}

void IRenderAlgorithm::setUniformToShader(const std::string& vShaderName, const std::string& vUniformName, const std::function<std::any()>& vModifier)
{
	for (auto& Item : m_Shaders)
	{
		if (Item.getName() == vShaderName)
		{
			Item.setUniformModifier(vUniformName, vModifier);
			break;
		}
	}
}