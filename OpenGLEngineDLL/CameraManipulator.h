#pragma once
#include "Camera.h"

namespace hiveEngine
{
	class ICameraManipulator
	{
	public:
		ICameraManipulator() = default;
		~ICameraManipulator() = default;

		void setCamera(ICamera* vCamera) { m_pCamera = vCamera; }
		void setSensitivity(float vSensitivity) { m_Sensitvity = vSensitivity; }
		void setMoveSpeed(float vMoveSpeed) { m_MoveSpeed = vMoveSpeed; }

		virtual void onMouseMove(float vXPos, float vYPos) {};
		virtual void onMouseButton(int vButton, int vAction, int vMods) {};
		virtual void onMouseScroll(float vOffsetY) {};
		virtual void onKeyboard(int vKey, int vAction, int vMods) {};

	protected:
		ICamera* m_pCamera = nullptr;
		float m_Sensitvity = 0.5f;
		float m_MoveSpeed = 0.01f;
		float m_ScaleSpeed = 0.1f;

	private:

	};
}