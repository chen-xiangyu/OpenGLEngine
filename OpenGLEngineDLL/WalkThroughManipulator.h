#pragma once
#include "CameraManipulator.h"

namespace hiveEngine
{
	class CWalkThroughManipulator : public ICameraManipulator
	{
	public:
		CWalkThroughManipulator() = default;
		~CWalkThroughManipulator() = default;

		void onMouseMove(float vPosX, float vPosY) override;
		void onMouseScroll(float vOffsetY) override;
		void onKeyboard(int vKey, int vAction, int vMods) override;

	private:
		float m_LastX = 0;
		float m_LastY = 0;
		bool m_IsFirst = true;
		std::map<int, bool> m_KeyStatus;
		float m_Patch = 0.0f;

		void __changePitch(float vAngle);
		void __changeYaw(float vAngle);
		void __translateCamera();
	};
}