
#include "VisNormalMaterial.h"
#include "core/Scene.h"
#include "utils/AssetsPath.h"

namespace hiveGL
{
	std::shared_ptr<CShader> CVisNormalMaterial::m_pShader = nullptr;

	CVisNormalMaterial::CVisNormalMaterial(float vMagnitude, const glm::vec3& vColor) :m_Magnitude(vMagnitude), m_Color(vColor)
	{
		if (m_pShader == nullptr)
			m_pShader = std::make_shared<CShader>(
				CAssetsPath::getAssetsPath() + "\\shaders\\visNormal.vert",
				CAssetsPath::getAssetsPath() + "\\shaders\\visNormal.frag",
				CAssetsPath::getAssetsPath() + "\\shaders\\visNormal.geom"
			);
	}

	void CVisNormalMaterial::use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const
	{
		m_pShader->use();
		m_pShader->setUniform("uMagnitude", m_Magnitude);
		m_pShader->setUniform("uColor", m_Color);
		m_pShader->setUniform("uModel", vNode->getModelMatrix());
		m_pShader->setUniform("uView", vScene->getCamera()->getViewMatrix());
		m_pShader->setUniform("uProjection", vScene->getCamera()->getProjectionMatrix());
	}
}