#include "pch.h"
#include "../OpenGLEngineDLL/OpenGLEngine.h"

int main()
{
	std::cout << "hello world\n";
	hiveEngine::COpenGLEngine Engine;
	Engine.init("OpenGLConfig.xml");
	Engine.run();
	return 0;
}