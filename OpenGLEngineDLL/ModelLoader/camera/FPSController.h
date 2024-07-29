#pragma once

#include "camera/PerspCamController.h"

namespace hiveGL
{
	class CFPSController : public CPerspCamController
	{
	public:
		CFPSController();
		CFPSController(float vSensitivity, float vSpeed);
		void control(const std::shared_ptr<CPerspectiveCamera>& vCamera) override;
		void update(float vDeltaTime) override;
		void onKeyDown(int vKey) override;
		void onKeyUp(int vKey) override;
		void onMouseButtonDown(int vKey) override;
		void onMouseButtonUp(int vKey) override;
		void onMouseMove(float vPosX, float vPosY) override;
		void onMouseScroll(float vOffsetX, float vOffsetY) override;
	private:
		void __updateFpsCamera();
		float m_Yaw;
		float m_Pitch;
		float m_Speed;
		float m_Sensitivity;
		bool m_IsLeftBtnPressed;
		bool m_IsFirst;
		bool m_IsKeyPressedA;
		bool m_IsKeyPressedD;
		bool m_IsKeyPressedW;
		bool m_IsKeyPressedS;
		bool m_IsKeyPressedQ;
		bool m_IsKeyPressedE;
	};
}
