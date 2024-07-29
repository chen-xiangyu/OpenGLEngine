#pragma once

#include "BoundingVolume.h"

namespace hiveGL
{
	class CAABB : public CBoundingVolume
	{
	public:
		CAABB(const glm::vec3& vMin, const glm::vec3& vMax) :m_Min(vMin), m_Max(vMax) {}
		const glm::vec3& getMin() const { return m_Min; }
		const glm::vec3& getMax() const { return m_Max; }
		// Inherited via CBoundingVolume
		bool isOnFrustum(const SFrustum& vFrustum, const CTransform& vTransform) const override { return false; }
	private:
		glm::vec3 m_Min;
		glm::vec3 m_Max;
	};
}