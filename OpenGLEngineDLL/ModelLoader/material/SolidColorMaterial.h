
#pragma once

#include "material/Material.h"
#include "base/Shader.h"

namespace hiveGL
{
	class CSolidColorMaterial : public CMaterial
	{
	public:
		CSolidColorMaterial(const glm::vec3& vColor);
		// Inherited via CMaterial
		void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const override;
	private:
		glm::vec3 m_Color;
		static std::shared_ptr<CShader> m_pShader;
	};
}