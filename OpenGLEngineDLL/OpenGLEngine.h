#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EngineConfig.h"
#include "EditableConfig.h"
#include "ShaderFacade.h"
#include "Mesh.h"
#include "EngineCommon.h"

#ifdef OPENGL_ENGINE_EXPORTS
#define OPENGL_ENGINE_API __declspec(dllexport)
#else
#define OPENGL_ENGINE_API __declspec(dllimport)
#endif

namespace hiveEngine
{
	typedef std::pair<EKeyType, EKeyStatus> KeyEventType;

	class OPENGL_ENGINE_API COpenGLEngine
	{
	public:
		COpenGLEngine() = default;
		~COpenGLEngine() = default;

		void init(const std::string& vConfigFilename);
		void run();
		void bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier);
		void bindInputEvent(const KeyEventType& vKeyEvent, const std::function<std::map<std::string, std::any>(const CEditableConfig&)> vCallback);

	private:
		GLFWwindow* m_pWindow = nullptr;
		CEngineConfig m_EngineConfig;
		CEditableConfig m_EditableConfig;
		CShaderFacade m_ShaderFacade;
		CMesh m_Mesh;

		std::map<KeyEventType, std::function<std::map<std::string, std::any>(const CEditableConfig&)>> m_InputCallbacks;

		void __initGLFW();
		void __initWindow();
		void __adjustWindowSize(GLFWwindow* vWindow, int vWidth, int vHeight);
		void __initShader();
		void __loadShaderConfig();
		void __handleInput();
	};
}


