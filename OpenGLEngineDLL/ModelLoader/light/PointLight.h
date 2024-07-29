#pragma once

#include "light/Light.h"

namespace hiveGL
{
	class CPointLight : public CLight
	{
	public:
		CPointLight(const glm::vec3& vPosition, const glm::vec3& vDiffuseColor);
		// Inherited via CLight
		glm::vec3 getDiffuseColor() const override { return m_DiffuseColor; }
		glm::vec3 getPosition() const override { return m_Position; }
		glm::vec3 getDirection() const override { return glm::vec3(0.0f, 0.0f, 0.0f); }
	private:
		glm::vec3 m_DiffuseColor;
		glm::vec3 m_Position;
	};
}