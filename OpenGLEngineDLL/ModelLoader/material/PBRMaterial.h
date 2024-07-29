#pragma once

#include "material/Material.h"
#include "base/Shader.h"

namespace hiveGL
{
	class CPBRMaterial : public CMaterial
	{
	public:
		CPBRMaterial(const glm::vec3& vAlbedo, float vMetallic, float vRoughness, float vAo, bool vIsDeferred = false);
		// Inherited via CMaterial
		void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const override;
		const glm::vec3& getAlbedo() const { return m_Albedo; }
		float getRoughness() const { return m_Roughness; }
		float getMetallic() const { return m_Metallic; }
		float getAo() const { return m_Ao; }
		void setAlbedo(const glm::vec3& vAlbedo) { m_Albedo = vAlbedo; }
		void setRoughness(float vRoughness) { m_Roughness = vRoughness; }
		void setMetallic(float vMetallic) { m_Metallic = vMetallic; }
		void setAo(float vAo) { m_Ao = vAo; }
	private:
		static std::shared_ptr<CShader> m_pForwardShader;
		static std::shared_ptr<CShader> m_pDeferredShader;
		glm::vec3 m_Albedo;
		float m_Metallic;
		float m_Roughness;
		float m_Ao;
		bool m_IsDeferred;
	};
}