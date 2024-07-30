#include "pch.h"
#include "RenderManager.h"

using namespace hiveEngine;

void CRenderManager::setUniformToShader(const std::string& vShaderName, const std::string& vUniformName, const std::function<std::any()>& vModifier)
{
	for (auto& Item : m_RenderAlgorithms)
	{
		if (Item.second->isContainShader(vShaderName))
		{
			Item.second->setUniformToShader(vShaderName, vUniformName, vModifier);
			break;
		}
	}
}

void CRenderManager::addRenderAlgorithm(const std::string& vName, const std::shared_ptr<IRenderAlgorithm>& vAlgorithm)
{
	m_RenderAlgorithms.insert(std::make_pair(vName, vAlgorithm));
	if (m_pCurrentAlgorithm == nullptr)
	{
		m_pCurrentAlgorithm = m_RenderAlgorithms[vName];
		m_pCurrentAlgorithm->init();
	}
}

void CRenderManager::render(const CGLTFModel& vModel)
{
	if (m_pCurrentAlgorithm == nullptr)
	{
		HIVE_LOG_ERROR("Fail to render, because no render algorithm");
		return;
	}
	m_pCurrentAlgorithm->render(vModel);
}

bool CRenderManager::changeRenderAlgorithm(const std::string& vAlgorithmName)
{
	if (m_RenderAlgorithms.find(vAlgorithmName) != m_RenderAlgorithms.end())
	{
		m_pCurrentAlgorithm = m_RenderAlgorithms[vAlgorithmName];
		m_pCurrentAlgorithm->init();
		return true;
	}
	return false;
}