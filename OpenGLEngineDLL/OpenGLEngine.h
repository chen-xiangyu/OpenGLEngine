#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EngineConfig.h"
#include "EditableConfig.h"
#include "ShaderFacade.h"
#include "InputController.h"
#include "GLTFModel.h"
#include "RenderManager.h"
#include "Camera.h"
#include "CameraManipulator.h"
#include "MouseHandler.h"

#ifdef OPENGL_ENGINE_EXPORTS
#define OPENGL_ENGINE_API __declspec(dllexport)
#else
#define OPENGL_ENGINE_API __declspec(dllimport)
#endif

namespace hiveEngine
{
	class OPENGL_ENGINE_API COpenGLEngine
	{
	public:
		COpenGLEngine() = default;
		~COpenGLEngine() = default;

		void init(const std::string& vConfigFilename);
		void run();
		void bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier);
		void bindInputEvent(const KeyEventType& vKeyEvent, const std::function<std::map<std::string, std::any>(const CEditableConfig&)> vCallback);

		void setUniformToShader(const std::string& vShaderName, const std::string& vUniformName, const std::function<std::any()>& vModifier);
		bool changeRenderAlgorithm(const std::string& vAlgorithmName);

	private:
		GLFWwindow* m_pWindow = nullptr;
		CEngineConfig m_EngineConfig;
		CEditableConfig m_EditableConfig;
		CShaderFacade m_ShaderFacade;
		CInputController m_InputController;
		CGLTFModel m_Model;
		CRenderManager m_RenderManager;
		ICamera* m_pCamera = nullptr;
		ICameraManipulator* m_pCameraManipulator = nullptr;
		CMouseHandler m_MouseHandler;
		bool m_IsTrackBall;

		static float m_CursorXPos;
		static float m_CursorYPos;
		static int m_MouseButton;
		static int m_MouseButtonAction;
		static int m_MouseButtonMods;
		static float m_MouseScrollOffset;
		static int m_Key;
		static int m_KeyAction;
		static int m_KeyMods;
		
		void __initGLFW();
		void __initWindow();

		static void __onFramebufferCallback(GLFWwindow* vWindow, int vWidth, int vHeight);
		static void __onCursorCallback(GLFWwindow* vWindow, double vXPos, double vYPos);
		static void __onMouseButtonCallback(GLFWwindow* vWindow, int vButton, int vAction, int vMods);
		static void __onMouseScrollCallback(GLFWwindow* vWindow, double vOffsetX, double vOffsetY);
		static void __onKeyboardCallback(GLFWwindow* vWindow, int vKey, int vScancode, int vAction, int vMods);
		//void __initShader();
		void __initRenderAlgorithm(const std::string& vFilename);
		//void __loadShaderConfig();
	};
}


