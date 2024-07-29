#pragma once

#include <glm/glm.hpp>

namespace hiveGL
{
	class CLight
	{
	public:
		virtual glm::vec3 getDiffuseColor() const = 0;
		virtual glm::vec3 getPosition() const = 0;
		virtual glm::vec3 getDirection() const = 0;
	};
}
