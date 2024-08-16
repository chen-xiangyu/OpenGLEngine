#pragma once
#include "CameraManipulator.h"

namespace hiveEngine
{
	class CWalkThroughManipulator : public ICameraManipulator
	{
	public:
		CWalkThroughManipulator() = default;
		~CWalkThroughManipulator() = default;

		void onMouseMovedV(float vPosX, float vPosY) override;
		void onMouseScrolledV(float vOffsetX, float vOffsetY) override;
		void onKeyPressedV(int vKey, int vAction, int vMods) override;

	private:
		float m_CursorPosX = 0;
		float m_CursorPosY = 0;
		bool m_IsCursorFirstEnter = true;
		std::map<int, bool> m_KeyStatus;
		float m_Pitch = 0.0f;
		static constexpr float m_MinPitch = -89.0f;
		static constexpr float m_MaxPitch = 89.0f;
		float m_ScaleSpeed = 0.1f;

		void __changePitch(float vAngle);
		void __changeYaw(float vAngle);
		void __translateCamera();
	};
}