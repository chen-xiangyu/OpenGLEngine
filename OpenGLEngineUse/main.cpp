#include "pch.h"
#include "../OpenGLEngineDLL/OpenGLEngine.h"

double getCurrentTimeMilliseconds();
std::tuple<double, double, double> changeLightDir();

std::map<std::string, std::any> changeShader(const hiveEngine::CEditableConfig& vConfig);

int main()
{
	hiveEngine::COpenGLEngine Engine;
	Engine.init("OpenGLConfig.xml");
	Engine.bindAttributeModifier("LIGHT_DIRECTION", changeLightDir);
    Engine.bindInputEvent("A", changeShader);
	Engine.run();
	return 0;
}

double getCurrentTimeMilliseconds()
{
    auto Now = std::chrono::steady_clock::now();
    auto Duration = Now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(Duration).count();
}

std::tuple<double, double, double> changeLightDir()
{
    double Radius = 1.0, AngularSpeed = 0.001;
    double Time = getCurrentTimeMilliseconds();
    double Angle = AngularSpeed * Time;

    double X = Radius * std::cos(Angle);
    double Z = Radius * abs(std::sin(Angle));
    double Y = 0.0;

    return std::make_tuple(X, Y, Z);
}

std::map<std::string, std::any> changeShader(const hiveEngine::CEditableConfig& vConfig)
{
    int NumShader = vConfig.getAttribute<int>("NUM_SHADER").value();
    int CurrentID = vConfig.getAttribute<int>("WORKING_SHADER_ID").value();

    return { {"WORKING_SHADER_ID", (CurrentID + 1) % NumShader} };
}