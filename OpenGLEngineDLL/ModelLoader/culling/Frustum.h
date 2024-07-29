#pragma once

#include <glm/glm.hpp>

namespace hiveGL
{
	struct SPlane
	{
	public:
		SPlane() = default;
		SPlane(const glm::vec3& vPoint, const glm::vec3& vNormal)
			:_Normal(glm::normalize(vNormal)), _Distance(glm::dot(vNormal, vPoint))
		{}
		float getSignedDistanceToPlane(const glm::vec3& vPoint) const
		{
			return glm::dot(_Normal, vPoint) - _Distance;
		}
	public:
		glm::vec3 _Normal;
		float _Distance;
	};

	struct SFrustum
	{
		SPlane _TopFace;
		SPlane _BottomFace;
		SPlane _RightFace;
		SPlane _LeftFace;
		SPlane _FarFace;
		SPlane _NearFace;
	};
}