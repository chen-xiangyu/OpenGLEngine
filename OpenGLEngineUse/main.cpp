#include "pch.h"
#include "../OpenGLEngineDLL/OpenGLEngine.h"

#include <cmath>
#include <chrono>

// ��ȡ��ǰʱ�������
double getCurrentTimeSeconds() {
	auto now = std::chrono::system_clock::now();
	auto now_seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
	auto epoch = now_seconds.time_since_epoch();
	return static_cast<double>(epoch.count());
}

std::tuple<double, double, double> changeLightDir()
{
    double radius = 0.5;

    // Բ���˶����ٶȣ����ٶȣ�
    double angularSpeed = 1.0; // ÿ�뻡��

    // ��ȡ��ǰʱ�������
    double time = getCurrentTimeSeconds();

    // ���㵱ǰ�Ƕ�
    double angle = angularSpeed * time;

    // ���� x �� y ����
    double x = radius * std::cos(angle);
    double y = radius * std::sin(angle);

    // z ���걣�ֲ���
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
