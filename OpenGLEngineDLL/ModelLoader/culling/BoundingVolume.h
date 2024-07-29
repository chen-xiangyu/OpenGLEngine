#pragma once

#include "Frustum.h"
#include "core/Transform.h"

namespace hiveGL
{
	class CBoundingVolume
	{
	public:
		virtual bool isOnFrustum(const SFrustum& vFrustum, const CTransform& vTransform) const = 0;
	};
}