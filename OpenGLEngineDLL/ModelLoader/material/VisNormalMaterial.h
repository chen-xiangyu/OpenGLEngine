#pragma once

#include "material/Material.h"
#include "base/Shader.h"

namespace hiveGL
{
	class CVisNormalMaterial : public CMaterial
	{
	public:
		CVisNormalMaterial(float vMagnitude = 0.1f, const glm::vec3& vColor = glm::vec3(0.0f, 1.0f, 0.0f));
		// Inherited via CMaterial
		void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const override;
	private:
		static std::shared_ptr<CShader> m_pShader;
		float m_Magnitude;
		glm::vec3 m_Color;
	};
}