#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EngineConfig.h"
#include "EditableConfig.h"
#include "ShaderFacade.h"
#include "InputController.h"
#include "GLTFModel.h"
#include "RenderManager.h"

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
		
		void __initGLFW();
		void __initWindow();
		static void __adjustWindowSize(GLFWwindow* vWindow, int vWidth, int vHeight);
		//void __initShader();
		void __initRenderAlgorithm(const std::string& vFilename);
		//void __loadShaderConfig();
	};
}


