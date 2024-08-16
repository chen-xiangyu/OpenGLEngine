#pragma once
#include "Camera.h"

namespace hiveEngine
{
	class ICameraManipulator
	{
	public:
		ICameraManipulator() = default;
		virtual ~ICameraManipulator() = default;

		void setCamera(ICamera* vCamera);
		void setSensitivity(float vSensitivity);
		void setMoveSpeed(float vMoveSpeed);

		virtual void onMouseMovedV(float vXPos, float vYPos) {};
		virtual void onMouseButtonClickedV(int vButton, int vAction, int vMods) {};
		virtual void onMouseScrolledV(float vOffsetX, float vOffsetY) {};
		virtual void onKeyPressedV(int vKey, int vAction, int vMods) {};

	protected:
		ICamera* m_pCamera = nullptr;
		float m_Sensitvity = 0.5f;
		float m_MoveSpeed = 0.01f;

	private:

	};
}