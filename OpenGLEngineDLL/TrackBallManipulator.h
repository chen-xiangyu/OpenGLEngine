#pragma once
#include "CameraManipulator.h"

namespace hiveEngine
{
	class CTrackBallManipulator : public ICameraManipulator
	{
	public:
		CTrackBallManipulator() = default;
		~CTrackBallManipulator() = default;

		void onMouseMove(float vPosX, float vPosY) override;
		void onMouseButton(int vButton, int vAction, int vMods) override;
		void onMouseScroll(float vOffsetY) override;

	private:
		float m_LastX = 0;
		float m_LastY = 0;
		bool m_IsMouseLeftPressed = false;
		bool m_IsMouseRightPressed = false;
		bool m_IsMouseMiddlePressed = false;
		bool m_IsFirst = true;

		void __changePitch(float vAngle);
		void __changeYaw(float vAngle);
		void __translateCamera(float vOffsetX, float vOffsetY);
	};
}