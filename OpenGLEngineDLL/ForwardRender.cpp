#include "pch.h"
#include "ForwardRender.h"
#include <GLFW/glfw3.h>

using namespace hiveEngine;

void CForwardRender::init()
{
	glEnable(GL_DEPTH_TEST);
}

void CForwardRender::render(const CGLTFModel& vModel)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_Shaders[0].use();
	vModel.draw();
}