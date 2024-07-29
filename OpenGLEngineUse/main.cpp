#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGLEngineDLL/OpenGLEngine.h"

double getCurrentTimeMilliseconds();
glm::vec3 changeLightDir();

//std::map<std::string, std::any> changeShader(const hiveEngine::CEditableConfig& vConfig);

const std::string ShaderName = "perpixel_shading";
const std::map<std::string, std::function<std::any()>> UniformMap = {
	{"Model", []() -> glm::mat4 {
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::scale(Model, glm::vec3((0.1f, 0.1f, 0.1f))); // Ëõ·Å
		Model = glm::rotate(Model, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Ðý×ª
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

int main()
{
	hiveEngine::COpenGLEngine Engine;
	Engine.init("OpenGLConfig.xml");

	for (auto& Item : UniformMap)
	{
		Engine.setUniformToShader(ShaderName, Item.first, Item.second);
	}

    //hiveEngine::KeyEventType Event = { hiveEngine::EKeyType::KEY_A, hiveEngine::EKeyStatus::PRESS };
    //Engine.bindInputEvent(Event, changeShader);

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

//std::map<std::string, std::any> changeShader(const hiveEngine::CEditableConfig& vConfig)
//{
//    int NumShader = vConfig.getAttribute<int>("NUM_SHADER").value();
//    int CurrentID = vConfig.getAttribute<int>("WORKING_SHADER_ID").value();
//
//    return { {"WORKING_SHADER_ID", (CurrentID + 1) % NumShader} };
//}