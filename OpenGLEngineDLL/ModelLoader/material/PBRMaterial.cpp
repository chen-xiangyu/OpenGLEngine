
#include "PBRMaterial.h"
#include "core/Scene.h"
#include "utils/AssetsPath.h"

namespace hiveGL
{
	std::shared_ptr<CShader>CPBRMaterial::m_pForwardShader = nullptr;
	std::shared_ptr<CShader>CPBRMaterial::m_pDeferredShader = nullptr;

	CPBRMaterial::CPBRMaterial(const glm::vec3& vAlbedo, float vMetallic, float vRoughness, float vAo, bool vIsDeferred)
		:m_Albedo(vAlbedo), m_Metallic(vMetallic), m_Roughness(vRoughness), m_Ao(vAo), m_IsDeferred(vIsDeferred)
	{
		if (!m_IsDeferred && m_pForwardShader == nullptr)
			m_pForwardShader = std::make_shared<CShader>(
				CAssetsPath::getAssetsPath() + "\\shaders\\pbr.vert",
				CAssetsPath::getAssetsPath() + "\\shaders\\pbr.frag"
			);
		if (m_IsDeferred && m_pDeferredShader == nullptr)
			m_pDeferredShader = std::make_shared<CShader>(
				CAssetsPath::getAssetsPath() + "\\shaders\\deferPbr.vert",
				CAssetsPath::getAssetsPath() + "\\shaders\\deferPbr.frag"
			);
	}

	void CPBRMaterial::use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const
	{
		const std::shared_ptr<CShader>& pShader = m_IsDeferred ? m_pDeferredShader : m_pForwardShader;
		pShader->use();
		if (m_IsDeferred)
		{
			pShader->setUniform("uPositionTex", 0);
			pShader->setUniform("uNormalTex", 1);
			pShader->setUniform("uDepthTex", 2);
		}
		else
		{
			pShader->setUniform("uModel", vNode->getModelMatrix());
			pShader->setUniform("uNormalMatrix", vNode->getNormalMatrix());
			pShader->setUniform("uView", vScene->getCamera()->getViewMatrix());
			pShader->setUniform("uProjection", vScene->getCamera()->getProjectionMatrix());
		}
		pShader->setUniform("uAlbedo", m_Albedo);
		pShader->setUniform("uMetallic", m_Metallic);
		pShader->setUniform("uRoughness", m_Roughness);
		pShader->setUniform("uAo", m_Ao);
		pShader->setUniform("uLightPosition", vScene->getLight()->getPosition());
		pShader->setUniform("uLightColor", vScene->getLight()->getDiffuseColor());
		pShader->setUniform("uCamPos", vScene->getCamera()->getWorldPos());
	}
}