#include "pch.h"
#include "../OpenGLEngineDLL/OpenGLEngine.h"

#include <cmath>
#include <chrono>

// 获取当前时间的秒数
double getCurrentTimeSeconds() {
	auto now = std::chrono::system_clock::now();
	auto now_seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
	auto epoch = now_seconds.time_since_epoch();
	return static_cast<double>(epoch.count());
}

std::tuple<double, double, double> changeLightDir()
{
    double radius = 0.5;

    // 圆周运动的速度（角速度）
    double angularSpeed = 1.0; // 每秒弧度

    // 获取当前时间的秒数
    double time = getCurrentTimeSeconds();

    // 计算当前角度
    double angle = angularSpeed * time;

    // 计算 x 和 y 坐标
    double x = radius * std::cos(angle);
    double y = radius * std::sin(angle);

    // z 坐标保持不变
    double z = 0.0;

    return std::make_tuple(x, z, y);
}
int main()
{
	std::cout << "hello world\n";
	hiveEngine::COpenGLEngine Engine;
	Engine.init("OpenGLConfig.xml");
	Engine.bindAttributeModifier("LIGHT_DIRECTION", changeLightDir);
	Engine.run();
	return 0;
}
