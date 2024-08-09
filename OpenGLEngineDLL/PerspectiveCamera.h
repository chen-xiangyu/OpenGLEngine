#pragma once
#include "Camera.h"
#include <glm/glm.hpp>

namespace hiveEngine
{
	class CPerspectiveCamera : public ICamera
	{
	public:
		CPerspectiveCamera();
		~CPerspectiveCamera() = default;

		void setFov(float vFov);
		void setAspect(float vAspect);
		void setZNear(float vZNear);
		void setZFar(float vZFar);

		void scale(float vValue) override;

	protected:
		void _updateProjectionMat() override;

	private:
		float m_Fov = 45.0f;
		float m_Aspect = 800.0f / 600.0f;
		float m_ZNear = 0.1f;
		float m_ZFar = 100.0f;
	};
}