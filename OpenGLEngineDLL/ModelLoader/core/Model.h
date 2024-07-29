#pragma once

#include <memory>
#include "base/VertexArrayBuffer.h"
#include "material/Material.h"

namespace hiveGL
{
	class CModel
	{
	public:
		CModel(const std::shared_ptr<CVertexArrayBuffer>& vVAO, const std::shared_ptr<CMaterial>& vMaterial)
			:m_pVAO(vVAO), m_pMaterial(vMaterial) {}
		const std::shared_ptr<CVertexArrayBuffer>& getVAO() const { return m_pVAO; }
		const std::shared_ptr<CMaterial>& getMaterial() const { return m_pMaterial; }
	private:
		std::shared_ptr<CVertexArrayBuffer> m_pVAO;
		std::shared_ptr<CMaterial> m_pMaterial;
	};
}