#pragma once

#include "core/Node.h"
#include "base/VertexArrayBuffer.h"
#include "culling/AABB.h"

namespace hiveGL
{
	class CAABBGizmo : public CNode
	{
	public:
		CAABBGizmo(const std::shared_ptr<CAABB>& vAABB);
	private:
		std::shared_ptr<CVertexArrayBuffer> __createVAO();
		std::shared_ptr<CAABB> m_pAABB;
	};
}