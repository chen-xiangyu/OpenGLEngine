#pragma once

#include "camera/PerspCamController.h"

namespace hiveGL
{
	class CArcballController : public CPerspCamController
	{
	public:
		CArcballController();
		CArcballController(glm::vec3 vTargetPos, float vDistance, float vSensitivity);
		void control(const std::shared_ptr<CPerspectiveCamera>& vCamera) override;
		void update(float vDeltaTime) override;
		void onMouseButtonDown(int vKey) override;
		void onMouseButtonUp(int vKey) override;
		void onMouseMove(float vPosX, float vPosY) override;
		void onMouseScroll(float vOffsetX, float vOffsetY) override;
	private:
		void __updateCamera();
		glm::vec3 m_TargetPos;
		float m_Distance;
		float m_Yaw;
		float m_Pitch;
		float m_Sensitivity;
		bool m_IsLeftBtnPressed;
		bool m_IsRightBtnPressed;
		bool m_IsFirst;
	};
}