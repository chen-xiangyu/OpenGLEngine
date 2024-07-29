
#include "FPSController.h"
#include "HiveLogger.h"

namespace hiveGL
{
	CFPSController::CFPSController():
	m_Yaw(-90.0f),m_Pitch(0.0f),m_Sensitivity(0.1f),
	m_IsLeftBtnPressed(false),m_IsFirst(true),m_Speed(50.0f),
	m_IsKeyPressedA(false), m_IsKeyPressedD(false), m_IsKeyPressedW(false), 
	m_IsKeyPressedS(false), m_IsKeyPressedQ(false), m_IsKeyPressedE(false)
	{}

	CFPSController::CFPSController(float vSensitivity, float vSpeed):
		m_Yaw(-90.0f), m_Pitch(0.0f), m_Sensitivity(vSensitivity),
		m_IsLeftBtnPressed(false), m_IsFirst(true), m_Speed(vSpeed),
		m_IsKeyPressedA(false), m_IsKeyPressedD(false), m_IsKeyPressedW(false),
		m_IsKeyPressedS(false), m_IsKeyPressedQ(false), m_IsKeyPressedE(false)
	{}

	void CFPSController::control(const std::shared_ptr<CPerspectiveCamera>& vCamera)
	{
		CPerspCamController::control(vCamera);
		__updateFpsCamera();
	}
	void CFPSController::onKeyDown(int vKey)
	{
		if (vKey == HIVE_KEY_A) {
			m_IsKeyPressedA = true;
		}
		if (vKey == HIVE_KEY_D) {
			m_IsKeyPressedD = true;
		}
		if (vKey == HIVE_KEY_W) {
			m_IsKeyPressedW = true;
		}
		if (vKey == HIVE_KEY_S) {
			m_IsKeyPressedS= true;
		}
		if (vKey == HIVE_KEY_Q) {
			m_IsKeyPressedQ= true;
		}
		if (vKey == HIVE_KEY_E) {
			m_IsKeyPressedE= true;
		}
		
	}

	void CFPSController::onKeyUp(int vKey)
	{
		if (vKey == HIVE_KEY_A) {
			m_IsKeyPressedA = false;
		}
		if (vKey == HIVE_KEY_D) {
			m_IsKeyPressedD = false;
		}
		if (vKey == HIVE_KEY_W) {
			m_IsKeyPressedW = false;
		}
		if (vKey == HIVE_KEY_S) {
			m_IsKeyPressedS = false;
		}
		if (vKey == HIVE_KEY_Q) {
			m_IsKeyPressedQ = false;
		}
		if (vKey == HIVE_KEY_E) {
			m_IsKeyPressedE = false;
		}
	}

	void CFPSController::onMouseButtonDown(int vKey)
	{
		if (vKey == HIVE_MOUSE_BUTTON_LEFT) m_IsLeftBtnPressed = true;
	}

	void CFPSController::onMouseButtonUp(int vKey)
	{
		if (vKey == HIVE_MOUSE_BUTTON_LEFT)
		{
			m_IsLeftBtnPressed = false;
			m_IsFirst = true;
		}
	}
	void CFPSController::update(float vDeltaTime)
	{
		
		float Velocity = m_Speed * vDeltaTime;
		glm::vec3 Position = m_pCamera->getWorldPos();
		if (m_IsKeyPressedA)
		{
			Position -= Velocity * m_pCamera->getRight();
			m_pCamera->setWorldPos(Position);
		}
		if (m_IsKeyPressedD)
		{
			Position += Velocity * m_pCamera->getRight();
			m_pCamera->setWorldPos(Position);
		}
		if (m_IsKeyPressedW)
		{
			Position += Velocity * m_pCamera->getFront();
			m_pCamera->setWorldPos(Position);
		}
		if (m_IsKeyPressedS)
		{
			Position -= Velocity * m_pCamera->getFront();
			m_pCamera->setWorldPos(Position);
		}
		if (m_IsKeyPressedQ)
		{
			Position += Velocity * m_pCamera->getUp();
			m_pCamera->setWorldPos(Position);
		}
		if (m_IsKeyPressedE)
		{
			Position -= Velocity * m_pCamera->getUp();
			m_pCamera->setWorldPos(Position);
		}
		
	}
	void CFPSController::onMouseMove(float vPosX, float vPosY)
	{

		if (!m_IsLeftBtnPressed) return;
		static float LastPosX, LastPosY;
		if (m_IsFirst)
		{
			LastPosX = vPosX;
			LastPosY = vPosY;
			m_IsFirst = false;
			return;
		}
		float DeltaX = vPosX - LastPosX;
		float DeltaY = vPosY - LastPosY;
		LastPosX = vPosX;
		LastPosY = vPosY;
		m_Yaw += DeltaX * m_Sensitivity;
		m_Pitch -= DeltaY * m_Sensitivity;
		if (m_Pitch > 89.0f) m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;
		__updateFpsCamera();
	}

	void CFPSController::onMouseScroll(float vOffsetX, float vOffsetY)
	{
		float m_Zoom = m_pCamera->getZoom();
		m_Zoom -= (float)vOffsetY;
		if (m_Zoom < 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom > 45.0f)
			m_Zoom = 45.0f;
		m_pCamera->setZoom(m_Zoom);
	}
	void CFPSController::__updateFpsCamera() 
	{
		glm::vec3 Front{};
		Front.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		Front.y = glm::sin(glm::radians(m_Pitch));
		Front.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		Front = glm::normalize(Front);
		m_pCamera->setFront(Front);
	}
}