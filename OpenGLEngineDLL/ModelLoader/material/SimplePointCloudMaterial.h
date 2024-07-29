#pragma once

#include "material/Material.h"
#include "base/Shader.h"

namespace hiveGL
{
	class CSimplePointCloudMaterial : public CMaterial
	{
	public:
		CSimplePointCloudMaterial();
		// Inherited via CMaterial
		void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) const override;
	private:
		static std::shared_ptr<CShader> m_pShader;
	};
}

