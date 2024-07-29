
#include "SimplePointCloudMaterial.h"
#include "core/Scene.h"
#include "utils/AssetsPath.h"

namespace hiveGL
{
	std::shared_ptr<CShader> CSimplePointCloudMaterial::m_pShader{ nullptr };

	CSimplePointCloudMaterial::CSimplePointCloudMaterial()
	{
		if (m_pShader == nullptr)
		{
			std::string Dir = CAssetsPath::getAssetsPath() + "\\shaders\\";
			m_pShader = std::make_shared<CShader>(Dir + "simplePointCloud.vert", Dir + "simplePointCloud.frag");
		}
	}

	void CSimplePointCloudMaterial::use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const
	{
		m_pShader->use();
		m_pShader->setUniform("uModel", vNode->getModelMatrix());
		m_pShader->setUniform("uView", vScene->getCamera()->getViewMatrix());
		m_pShader->setUniform("uProjection", vScene->getCamera()->getProjectionMatrix());
	}
}