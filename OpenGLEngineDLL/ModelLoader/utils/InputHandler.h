#pragma once

namespace hiveGL
{
	class CInputHandler
	{
	public:
		virtual void onViewportChange(int vWidth, int vHeight) {}
		virtual void onKeyDown(int vKey) {}
		virtual void onKeyUp(int vKey) {}
		virtual void onMouseButtonDown(int vKey) {}
		virtual void onMouseButtonUp(int vKey) {}
		virtual void onMouseMove(float vPosX, float vPosY) {}
		virtual void onMouseScroll(float vOffsetX, float vOffsetY) {}
	};

	constexpr auto HIVE_MOUSE_BUTTON_LEFT = 1;
	constexpr auto HIVE_MOUSE_BUTTON_RIGHT = 2;
	constexpr auto HIVE_MOUSE_BUTTON_MIDDLE = 4;
	constexpr auto HIVE_MOUSE_BUTTON_BACK = 8;
	constexpr auto HIVE_MOUSE_BUTTON_FORWARD = 16;
	constexpr auto HIVE_KEY_W = 87;
	constexpr auto HIVE_KEY_S = 83;
	constexpr auto HIVE_KEY_A = 65;
	constexpr auto HIVE_KEY_D = 68;
	constexpr auto HIVE_KEY_Q = 81;
	constexpr auto HIVE_KEY_E = 69;

	
}