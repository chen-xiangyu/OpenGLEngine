#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGLEngineDLL/OpenGLEngine.h"

double getCurrentTimeMilliseconds();
glm::vec3 changeLightDir();

std::map<std::string, std::any> changeShader(const hiveEngine::CEditableConfig& vConfig);
std::map<std::string, std::any> changeManipulator(const hiveEngine::CEditableConfig& vConfig);

const std::string PerpixelShaderName = "perpixel_shading";
const std::string PervertexShaderName = "pervertex_shading";
const std::map<std::string, std::function<std::any()>> ForwardUniformMap = {
	{"Model", []() -> glm::mat4 {
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::scale(Model, glm::vec3((0.1f, 0.1f, 0.1f))); // 缩放
		Model = glm::rotate(Model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 旋转
		Model = glm::translate(Model, glm::vec3(0.0f, -3.3f, 10.0f));
		return Model;
	}},
	{"Diffuse", []() -> glm::vec3 {
		return glm::vec3(0.8f, 0.8f, 0.8f);
	}},
	{"Specular", []() -> glm::vec3 {
		return glm::vec3(0.1f, 0.1f, 0.1f);
	}},
	{"Ambient", []() -> glm::vec3 {
		return glm::vec3(0.3f, 0.3f, 0.3f);
	}},
	{"ViewPos", []() -> glm::vec3 {
		return glm::vec3(0.0f, 0.0f, 1.0f);
	}},
	{"LightColor", []() -> glm::vec3 {
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}},
	{"LightDir", changeLightDir},
	{"Shininess", []() -> float {
		return 100.0f;
	}},
};

const std::string DeferredGeometryShaderName = "geometry_pass";
const std::string DeferredLightingShaderName = "lighting_pass";
const std::map<std::string, std::function<std::any()>> DeferredGeometryUniformMap = {
	{"Model", []() -> glm::mat4 {
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::scale(Model, glm::vec3((0.1f, 0.1f, 0.1f))); // 缩放
		Model = glm::rotate(Model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // 旋转
		return Model;
	}},
	{"View", []() -> glm::mat4 {
		return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, -3.0f));
	}},
	{"Projection", []() -> glm::mat4 {
		float FOV = 45.0f, ZNear = 0.1f, ZFar = 100.f;
		int Width = 800, Height = 600;
		return glm::perspective(glm::radians(FOV), (float)Width / Height, ZNear, ZFar);
	}},
};

const std::map<std::string, std::function<std::any()>> DeferredLightingUniformMap = {
	{"Ambient", []() -> glm::vec3 {
		return glm::vec3(0.3f, 0.3f, 0.3f);
	}},
	{"ViewPos", []() -> glm::vec3 {
		return glm::vec3(0.0f, 0.0f, 1.0f);
	}},
	{"LightColor", []() -> glm::vec3 {
		return glm::vec3(1.0f, 1.0f, 1.0f);
	}},
	{"LightDir", changeLightDir},
	{"Shininess", []() -> float {
		return 100.0f;
	}},
};

int main()
{
	hiveEngine::COpenGLEngine Engine;
	Engine.init("OpenGLConfig.xml");

	for (auto& Item : ForwardUniformMap)
	{
		Engine.setUniformToShader(PerpixelShaderName, Item.first, Item.second);
		Engine.setUniformToShader(PervertexShaderName, Item.first, Item.second);
	}

	for (auto& Item : DeferredGeometryUniformMap)
	{
		Engine.setUniformToShader(DeferredGeometryShaderName, Item.first, Item.second);
	}
	for (auto& Item : DeferredLightingUniformMap)
	{
		Engine.setUniformToShader(DeferredLightingShaderName, Item.first, Item.second);
	}

	// 绑定事件
	hiveEngine::KeyEventType Event = { hiveEngine::EKeyType::KEY_B, hiveEngine::EKeyStatus::PRESS };
	Engine.bindInputEvent(Event, changeManipulator);

	// 方案1
	//Engine.bindInputEvent(Event, changeShader);

	// 方案 2
	//std::vector<std::string> AlgorithmName = { "PerpixelShading", "PervertexShading" };
	//int Index = 0;
	//Engine.bindInputEvent(Event, [&](const hiveEngine::CEditableConfig& vConfig) -> std::map<std::string, std::any> {
	//	Index = (Index + 1) % AlgorithmName.size();
	//	Engine.changeRenderAlgorithm(AlgorithmName[Index]);
	//	return {};
	//	});


	Engine.run();
	return 0;
}

double getCurrentTimeMilliseconds()
{
    auto Now = std::chrono::steady_clock::now();
    auto Duration = Now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(Duration).count();
}

glm::vec3 changeLightDir()
{
    float Radius = 1.0f, AngularSpeed = 0.002f;
    double Time = getCurrentTimeMilliseconds();
    float Angle = AngularSpeed * Time;

    float X = Radius * std::cos(Angle);
    float Z = Radius * abs(std::sin(Angle));
    float Y = 1.0f;

	return glm::vec3(X, Y, Z);
}

std::map<std::string, std::any> changeShader(const hiveEngine::CEditableConfig& vConfig)
{
	static std::vector<std::string> AlgorithmNames = { 
		"PerpixelShading", 
		"PervertexShading",
		//"DeferredShading",
	};
	static int Index = 0;
	Index = (Index + 1) % AlgorithmNames.size();
	
    return { {"WORKING_RENDER_ALGORITHM", AlgorithmNames[Index]} };
}

std::map<std::string, std::any> changeManipulator(const hiveEngine::CEditableConfig& vConfig)
{
	bool IsTrackBall = vConfig.getAttribute<bool>("IS_TRACKBALL").value();
	return { {"IS_TRACKBALL", !IsTrackBall} };
}