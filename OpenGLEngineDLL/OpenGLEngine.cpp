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
#include "ForwardRender.h"
#include "DeferredRender.h"

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
	//__initShader();
	std::string Filename;
	Filename = m_EngineConfig.getAttribute<std::string>(SHADER_CONFIG_FILE).value();
	__initRenderAlgorithm(Filename);

	Filename = m_EngineConfig.getAttribute<std::string>(GLTF_FILE).value();
	m_Model.loadGLTFModel(Filename, nullptr);
}

void COpenGLEngine::run()
{
	if (m_pWindow == nullptr) return;
	m_RenderAlgorithms["PerpixelShading"]->init();
	while (!glfwWindowShouldClose(m_pWindow))
	{
		m_InputController.handleInput(m_pWindow, m_EditableConfig);
		//int CurrentID = m_EditableConfig.getAttribute<int>(WORKING_SHADER_ID).value();
		//m_ShaderFacade.setCurrentShader(CurrentID);
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//m_EngineConfig.applyAttributeModifiers();

		//m_ShaderFacade.use();
		//__loadShaderConfig();
		//m_Model.draw();
		m_RenderAlgorithms["PerpixelShading"]->render(m_Model);

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

	glfwSetFramebufferSizeCallback(m_pWindow, __adjustWindowSize);
}

void COpenGLEngine::__initShader()
{
	const hiveConfig::CHiveConfig* pShaderConfigList = m_EngineConfig.getSubconfigAt(2);
	size_t NumShader = pShaderConfigList->getNumSubconfigs();

	const std::vector<std::string> ShaderFiles = {
		"perpixel_shading",
		"pervertex_shading",
	};
	for (int i = 0; i < NumShader; i++)
	{
		//std::string t = ShaderFiles[i] + "|" + FILE_NAME;
		std::string t = ShaderFiles[i] + "|" + "FILE_NAME";
		std::string ShaderConfigFilename = pShaderConfigList->getAttribute<std::string>(t).value();

		CShaderConfig ShaderConfig;
		ShaderConfig.loadDefaultConfig();
		hiveConfig::EParseResult Status = hiveConfig::hiveParseConfig(ShaderConfigFilename, hiveConfig::EConfigType::XML, &ShaderConfig);

		std::string VertexShader = ShaderConfig.getAttribute<std::string>("vertex_shader|" + SHADER_SOURCE_FILE).value();
		std::string FragmentShader = ShaderConfig.getAttribute<std::string>("fragment_shader|" + SHADER_SOURCE_FILE).value();

		m_ShaderFacade.addShader(VertexShader, FragmentShader);
	}
	
	m_EditableConfig.setAttribute(NUM_SHADER, (int)m_ShaderFacade.getNumShader());
	m_EditableConfig.setAttribute(WORKING_SHADER_ID, 0);
}

void COpenGLEngine::__initRenderAlgorithm(const std::string& vFilename)
{
	CShaderConfig ShaderConfig;
	ShaderConfig.loadDefaultConfig();
	hiveConfig::EParseResult Status = hiveConfig::hiveParseConfig(vFilename, hiveConfig::EConfigType::XML, &ShaderConfig);

	int AlgorithmNum = ShaderConfig.getNumSpecifiedSubconfigs(RENDER_ALGORITHM);
	std::cout << AlgorithmNum << "\n";
	for (int i = 0; i < AlgorithmNum; i++)
	{
		hiveConfig::CHiveConfig* pAlgorithmConfig = ShaderConfig.fetchSpecifiedSubconfigAt(RENDER_ALGORITHM, i);
		std::string AlgorithmName = pAlgorithmConfig->getName();

		std::string AlgorithmType = pAlgorithmConfig->getAttribute<std::string>(RENDER_TYPE).value();

		std::shared_ptr<IRenderAlgorithm> pRenderAlgorithm; 
		
		if (AlgorithmType == "forward_render")
		{
			pRenderAlgorithm = std::make_shared<CForwardRender>();
		}
		else if (AlgorithmType == "deferred_render")
		{
			pRenderAlgorithm = std::make_shared<CDeferredRender>();
		}
		int RenderPassNum = pAlgorithmConfig->getNumSpecifiedSubconfigs(RENDER_PASS);
		for (int j = 0; j < RenderPassNum; j++)
		{
			hiveConfig::CHiveConfig* pPassConfig = pAlgorithmConfig->fetchSpecifiedSubconfigAt(RENDER_PASS, j);
			std::string RenderPassName = pPassConfig->getName();

			std::string VSXMLName = pPassConfig->getAttribute<std::string>(VERTEX_SHADER).value();
			std::string FSXMLName = pPassConfig->getAttribute<std::string>(FRAGMENT_SHADER).value();
			std::string VSXMLPath = std::format("{}|{}", VSXMLName, SHADER_SOURCE_FILE);
			std::string FSXMLPath = std::format("{}|{}", FSXMLName, SHADER_SOURCE_FILE);

			std::string VSFilename = ShaderConfig.getAttribute<std::string>(VSXMLPath).value();
			std::string FSFilename = ShaderConfig.getAttribute<std::string>(FSXMLPath).value();

			pRenderAlgorithm->addShader(RenderPassName, VSFilename, FSFilename);
		}
		m_RenderAlgorithms.insert(std::make_pair(AlgorithmName, pRenderAlgorithm));
	}
	for (auto Item : m_RenderAlgorithms)
	{
		std::cout << Item.first << " " << Item.second->getNumShaders() << "\n";
	}
}

void COpenGLEngine::__adjustWindowSize(GLFWwindow* vWindow, int vWidth, int vHeight)
{
	glViewport(0, 0, vWidth, vHeight);
}

void COpenGLEngine::__loadShaderConfig()
{
	m_ShaderFacade.use();

	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::scale(Model, glm::vec3((0.1f, 0.1f, 0.1f))); // ����
	Model = glm::rotate(Model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // ��ת
	Model = glm::translate(Model, glm::vec3(0.0f, 0.3f, 6.0f));
	//glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, -3.0f));
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

void COpenGLEngine::bindInputEvent(const KeyEventType& vKeyEvent, const std::function<std::map<std::string, std::any>(const CEditableConfig&)> vCallback)
{
	m_InputController.bindInputEvent(vKeyEvent, vCallback);
}

void COpenGLEngine::setUniformToShader(const std::string& vShaderName, const std::string& vUniformName, const std::function<std::any()>& vModifier)
{
	for (auto& Item : m_RenderAlgorithms)
	{
		if (Item.second->isContainShader(vShaderName))
		{
			Item.second->setUniformToShader(vShaderName, vUniformName, vModifier);
			break;
		}
	}
}