#include "pch.h"
#include "OpenGLEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ConfigInterface.h"
#include "HiveLogger.h"
#include "EngineConfig.h"
#include "AttributesNameMapping.h"

using namespace hiveEngine;

void COpenGLEngine::init(const std::string& vConfigFilename)
{
	m_EngineConfig.loadDefaultConfig();
	hiveConfig::EParseResult Status = hiveConfig::hiveParseConfig(vConfigFilename, hiveConfig::EConfigType::XML, &m_EngineConfig);
	
	__initGLFW();
	__initWindow();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		HIVE_LOG_ERROR("failed to initialize GLAD.\n");
		return;
	}
	__initShader();

	std::vector<SVertex> Vertices = {
		{{0.5f,  0.5f, -3.0f},   {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{0.5f, -0.5f, -3.0f},   {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f, 1.0f}},
		{{-0.5f, -0.5f, -3.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f, 1.0f}},
		{{-0.5f,  0.5f, -3.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 0.0f, 1.0f}},
	};
	std::vector<unsigned int> Indices = {
		0, 1, 2,
		0, 3, 2
	};

	m_Mesh.loadData(Vertices, Indices);
}

void COpenGLEngine::run()
{
	if (m_pWindow == nullptr) return;

	while (!glfwWindowShouldClose(m_pWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_EngineConfig.applyAttributeModifiers();

		m_Shader.use();
		__loadShaderConfig();
		glBindVertexArray(m_Mesh.getVAO());
		glDrawElements(GL_TRIANGLES, m_Mesh.getNumIndices(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}

void COpenGLEngine::__initGLFW()
{
	glfwInit();

	int Major = m_EngineConfig.getAttribute<int>(GLFW_SETTINGS + "|" + VERSION_MAJOR).value();
	int Minor = m_EngineConfig.getAttribute<int>(GLFW_SETTINGS + "|" + VERSION_MINOR).value();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Minor);

	std::string Profile = m_EngineConfig.getAttribute<std::string>(GLFW_SETTINGS + "|" + PROFILE).value();
	glfwWindowHint(GLFW_OPENGL_PROFILE, ProfileMapping.at(Profile));

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void COpenGLEngine::__initWindow()
{
	int Width = m_EngineConfig.getAttribute<int>(WINDOW_SETTINGS + "|" + SCREEN_WIDTH).value();
	int Height = m_EngineConfig.getAttribute<int>(WINDOW_SETTINGS + "|" + SCREEN_HEIGHT).value();
	std::string Title = m_EngineConfig.getAttribute<std::string>(WINDOW_SETTINGS + "|" + SCREEN_TITLE).value();

	m_pWindow = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
	if (m_pWindow == nullptr)
	{
		HIVE_LOG_ERROR("failed to create GLFW window.");
		glfwTerminate();
		return;
	}

	std::tuple<int, int> InitPosition = m_EngineConfig.getAttribute<std::tuple<int, int>>(WINDOW_SETTINGS + "|" + INIT_POSITION).value();
	glfwSetWindowPos(m_pWindow, std::get<0>(InitPosition), std::get<1>(InitPosition));

	glfwMakeContextCurrent(m_pWindow);

	//glfwSetFramebufferSizeCallback(m_pWindow, __adjustWindowSize);
}

void COpenGLEngine::__initShader()
{
	std::string ShaderConfigFilename = m_EngineConfig.getAttribute<std::string>(SHADER_CONFIG_FILE).value();

	m_ShaderConfig.loadDefaultConfig();
	hiveConfig::EParseResult Status = hiveConfig::hiveParseConfig(ShaderConfigFilename, hiveConfig::EConfigType::XML, &m_ShaderConfig);

	std::string VertexShader = m_ShaderConfig.getAttribute<std::string>("shader_perpixel_shading_vs|" + SHADER_SOURCE_FILE).value();
	std::string FragmentShader = m_ShaderConfig.getAttribute<std::string>("shader_perpixel_shading_fs|" + SHADER_SOURCE_FILE).value();

	m_Shader.init(VertexShader, FragmentShader);
}

void COpenGLEngine::__adjustWindowSize(GLFWwindow* vWindow, int vWidth, int vHeight)
{
	glViewport(0, 0, vWidth, vHeight);
}

void COpenGLEngine::__loadShaderConfig()
{
	m_Shader.use();

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View = glm::mat4(1.0f);
	float FOV = 45.0f, ZNear = 0.1f, ZFar = 100.f;
	int Width = m_EngineConfig.getAttribute<int>(WINDOW_SETTINGS + "|" + SCREEN_WIDTH).value();
	int Height = m_EngineConfig.getAttribute<int>(WINDOW_SETTINGS + "|" + SCREEN_HEIGHT).value();
	glm::mat4 Projection = glm::perspective(glm::radians(FOV), (float)Width / Height, ZNear, ZFar);
	m_Shader.setUniformMatrix4fv("Model", Model);
	m_Shader.setUniformMatrix4fv("View", View);
	m_Shader.setUniformMatrix4fv("Projection", Projection);

	glm::vec3 Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 Specular = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 Ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	glm::vec3 ViewPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	//glm::vec3 LightDir = glm::vec3(0.0f, 0.0f, 1.0f);
	auto [x, y, z] = m_EngineConfig.getAttribute<std::tuple<double, double, double>>(LIGHT_DIRECTION).value();
	glm::vec3 LightDir = glm::vec3(x, y, z);
	float Shininess = 100.0f;

	m_Shader.setUniform3fv("Diffuse", Diffuse);
	m_Shader.setUniform3fv("Specular", Specular);
	m_Shader.setUniform3fv("Ambient", Ambient);
	m_Shader.setUniform3fv("ViewPos", ViewPos);
	m_Shader.setUniform3fv("LightColor", LightColor);
	m_Shader.setUniform3fv("LightDir", LightDir);
	m_Shader.setUniformFloat("Shininess", Shininess);
}

void COpenGLEngine::bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier)
{
	m_EngineConfig.bindAttributeModifier(vName, vModifier);
}