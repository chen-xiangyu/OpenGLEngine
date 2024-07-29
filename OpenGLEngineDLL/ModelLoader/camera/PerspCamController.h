#pragma once

#include "utils/InputHandler.h"
#include "camera/PerspectiveCamera.h"

namespace hiveGL
{
	class CPerspCamController : public CInputHandler
	{
	public:
		virtual void control(const std::shared_ptr<CPerspectiveCamera>& vCamera) { m_pCamera = vCamera; }
		void onViewportChange(int vWidth, int vHeight) override { m_pCamera->setViewport(vWidth, vHeight); }
		virtual void update(float vDeltaTime) {}
	protected:
		std::shared_ptr<CPerspectiveCamera> m_pCamera;
	};
}