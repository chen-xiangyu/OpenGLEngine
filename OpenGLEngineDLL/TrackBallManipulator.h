#pragma once
#include "CameraManipulator.h"

namespace hiveEngine
{
	class CTrackBallManipulator : public ICameraManipulator
	{
	public:
		CTrackBallManipulator() = default;
		~CTrackBallManipulator() = default;

		void onMouseMovedV(float vPosX, float vPosY) override;
		void onMouseButtonClickedV(int vButton, int vAction, int vMods) override;
		void onMouseScrolledV(float vOffsetY) override;

	private:
		float m_CursorPosX = 0;
		float m_CursorPosY = 0;
		bool m_IsCursorFirstEnter = false;
		bool m_IsMouseLeftDown = false;
		bool m_IsMouseRightDown = false;

		float m_ScaleSpeed = 0.05f;

		void __changePitch(float vAngle);
		void __changeYaw(float vAngle);
		void __translateCamera(float vOffsetX, float vOffsetY);
	};
}