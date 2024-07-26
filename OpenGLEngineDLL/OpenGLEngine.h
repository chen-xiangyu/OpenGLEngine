#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EngineConfig.h"
#include "ShaderFacade.h"
#include "Mesh.h"

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

	private:
		GLFWwindow* m_pWindow = nullptr;
		CEngineConfig m_EngineConfig;
		CShaderFacade m_ShaderFacade;
		CMesh m_Mesh;

		void __initGLFW();
		void __initWindow();
		void __adjustWindowSize(GLFWwindow* vWindow, int vWidth, int vHeight);
		void __initShader();
		void __loadShaderConfig();
	};
}


