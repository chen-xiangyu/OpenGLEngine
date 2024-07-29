
#include "SolidColorMaterial.h"
#include "core/Scene.h"
#include "utils/AssetsPath.h"

namespace hiveGL
{
	std::shared_ptr<CShader> CSolidColorMaterial::m_pShader{nullptr};

	CSolidColorMaterial::CSolidColorMaterial(const glm::vec3& vColor) :m_Color(vColor)
	{
		if (m_pShader == nullptr)
		{
			std::string Dir = CAssetsPath::getAssetsPath() + "\\shaders\\";
			m_pShader = std::make_shared<CShader>(Dir + "solidColor.vert", Dir + "solidColor.frag");
		}
	}

	void CSolidColorMaterial::use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const
	{
		m_pShader->use();
		m_pShader->setUniform("uModel", vNode->getModelMatrix());
		m_pShader->setUniform("uView", vScene->getCamera()->getViewMatrix());
		m_pShader->setUniform("uProjection", vScene->getCamera()->getProjectionMatrix());
		m_pShader->setUniform("uColor", m_Color);
	}
}