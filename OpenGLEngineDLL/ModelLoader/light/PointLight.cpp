
#include "PointLight.h"

namespace hiveGL
{
	CPointLight::CPointLight(const glm::vec3& vPosition, const glm::vec3& vDiffuseColor)
		:m_Position(vPosition), m_DiffuseColor(vDiffuseColor)
	{
	}
}