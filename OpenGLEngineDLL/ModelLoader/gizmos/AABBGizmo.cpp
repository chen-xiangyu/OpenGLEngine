
#include "AABBGizmo.h"
#include "material/SolidColorMaterial.h"

namespace hiveGL
{
	CAABBGizmo::CAABBGizmo(const std::shared_ptr<CAABB>& vAABB) :m_pAABB(vAABB)
	{
		setNodeName("AABB Gizmo");
		const auto& pVAO = __createVAO();
		const auto& pModel = std::make_shared<CModel>(pVAO, std::make_shared<CSolidColorMaterial>(glm::vec3(0.0f, 1.0f, 0.0f)));
		addModel(pModel);
	}

	std::shared_ptr<CVertexArrayBuffer> CAABBGizmo::__createVAO()
	{
		const auto& Min = m_pAABB->getMin();
		const auto& Max = m_pAABB->getMax();
		std::vector<float> Vertices = {
			Min.x, Min.y, Min.z,
			Max.x, Min.y, Min.z,
			Max.x, Max.y, Min.z,
			Min.x, Max.y, Min.z,
			Min.x, Min.y, Max.z,
			Max.x, Min.y, Max.z,
			Max.x, Max.y, Max.z,
			Min.x, Max.y, Max.z
		};
		std::vector<unsigned int> Indices = {
			0, 1, 1, 2, 2, 3, 3, 0,
			4, 5, 5, 6, 6, 7, 7, 4,
			0, 4, 1, 5, 2, 6, 3, 7
		};
		return std::make_shared<CVertexArrayBuffer>(Vertices, Indices, std::vector<int>{3}, GL_LINES);
	}
}