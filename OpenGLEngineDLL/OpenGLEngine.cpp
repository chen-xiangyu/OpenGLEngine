#include "pch.h"
#include "OpenGLEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ConfigInterface.h"
#include "HiveLogger.h"
#include "EngineConfig.h"
#include "AttributesNameMapping.h"
#include "ShaderConfig.h"

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
		__handleInput();
		int CurrentID = m_EditableConfig.getAttribute<int>(WORKING_SHADER_ID).value();
		m_ShaderFacade.setCurrentShader(CurrentID);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_EngineConfig.applyAttributeModifiers();

		m_ShaderFacade.use();
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
	const hiveConfig::CHiveConfig* pShaderConfigList = m_EngineConfig.getSubconfigAt(2);
	int NumShader = pShaderConfigList->getNumSubconfigs();

	const std::vector<std::string> ShaderFiles = {
		"perpixel_shading",
		"pervertex_shading",
	};
	for (int i = 0; i < NumShader; i++)
	{
		std::string t = ShaderFiles[i] + "|" + FILE_NAME;
		std::string ShaderConfigFilename = pShaderConfigList->getAttribute<std::string>(t).value();

		CShaderConfig ShaderConfig;
		ShaderConfig.loadDefaultConfig();
		hiveConfig::EParseResult Status = hiveConfig::hiveParseConfig(ShaderConfigFilename, hiveConfig::EConfigType::XML, &ShaderConfig);

		std::string VertexShader = ShaderConfig.getAttribute<std::string>("vertex_shader|" + SHADER_SOURCE_FILE).value();
		std::string FragmentShader = ShaderConfig.getAttribute<std::string>("fragment_shader|" + SHADER_SOURCE_FILE).value();

		m_ShaderFacade.addShader(VertexShader, FragmentShader);
	}
	
	m_EditableConfig.setAttribute(NUM_SHADER, m_ShaderFacade.getNumShader());
	m_EditableConfig.setAttribute(WORKING_SHADER_ID, 0);
}

void COpenGLEngine::__adjustWindowSize(GLFWwindow* vWindow, int vWidth, int vHeight)
{
	glViewport(0, 0, vWidth, vHeight);
}

void COpenGLEngine::__loadShaderConfig()
{
	m_ShaderFacade.use();

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View = glm::mat4(1.0f);
	float FOV = 45.0f, ZNear = 0.1f, ZFar = 100.f;
	int Width = m_EngineConfig.getAttribute<int>(WINDOW_SETTINGS + "|" + SCREEN_WIDTH).value();
	int Height = m_EngineConfig.getAttribute<int>(WINDOW_SETTINGS + "|" + SCREEN_HEIGHT).value();
	glm::mat4 Projection = glm::perspective(glm::radians(FOV), (float)Width / Height, ZNear, ZFar);
	m_ShaderFacade.setUniformMatrix4fv("Model", Model);
	m_ShaderFacade.setUniformMatrix4fv("View", View);
	m_ShaderFacade.setUniformMatrix4fv("Projection", Projection);

	glm::vec3 Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 Specular = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 Ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	glm::vec3 ViewPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	//glm::vec3 LightDir = glm::vec3(0.0f, 0.0f, 1.0f);
	auto [x, y, z] = m_EngineConfig.getAttribute<std::tuple<double, double, double>>(LIGHT_DIRECTION).value();
	glm::vec3 LightDir = glm::vec3(x, y, z);
	float Shininess = 100.0f;

	m_ShaderFacade.setUniform3fv("Diffuse", Diffuse);
	m_ShaderFacade.setUniform3fv("Specular", Specular);
	m_ShaderFacade.setUniform3fv("Ambient", Ambient);
	m_ShaderFacade.setUniform3fv("ViewPos", ViewPos);
	m_ShaderFacade.setUniform3fv("LightColor", LightColor);
	m_ShaderFacade.setUniform3fv("LightDir", LightDir);
	m_ShaderFacade.setUniformFloat("Shininess", Shininess);
}

void COpenGLEngine::bindAttributeModifier(const std::string& vName, const std::function<std::any()>& vModifier)
{
	m_EngineConfig.bindAttributeModifier(vName, vModifier);
}

void COpenGLEngine::bindInputEvent(const std::string& vName, const std::function<std::map<std::string, std::any>(const CEditableConfig&)> vCallback)
{
	if (vName == "A" || vName == "a")
	{
		m_InputCallbacks.insert(std::make_pair(GLFW_KEY_A, vCallback));
	}
}
void COpenGLEngine::__handleInput()
{
	for (const auto& Item : m_InputCallbacks)
	{
		if (glfwGetKey(m_pWindow, Item.first) == GLFW_PRESS)
		{
			std::map<std::string, std::any> Result = Item.second(m_EditableConfig);
			for (const auto& t : Result)
			{
				if (!m_EditableConfig.isAttributeExisted(t.first))
				{
					HIVE_LOG_ERROR("Fail to set attribute {}, because it is not exist", t.first);
					continue;
				}
				m_EditableConfig.overwriteAttribute(t.first, t.second);
			}
		}
	}
}