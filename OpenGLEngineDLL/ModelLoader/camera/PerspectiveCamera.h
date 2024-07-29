#pragma once

#include "camera/Camera.h"

namespace hiveGL
{
	class CPerspectiveCamera : public CCamera
	{
	public:
		CPerspectiveCamera();
		// Inherited via CCamera
		void _updateProjectionMatrix() override;
		void _updateFrustum() override;
		void setViewport(int vWidth, int vHeight) override;
		float getZoom() const { return m_Zoom; }
		float getAspect() const { return m_Aspect; }
		float getNear() const { return m_Near; }
		float getFar() const { return m_Far; }
		void setZoom(float vZoom);
		void setAspect(float vAspect);
		void setNear(float vNear);
		void setFar(float vFar);
	private:
		float m_Zoom;
		float m_Aspect;
		float m_Near;
		float m_Far;
	};
}

