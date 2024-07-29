#pragma once

#include <glm/glm.hpp>

namespace hiveGL
{
	class CTransform
	{
	public:
		CTransform();
		CTransform(const glm::vec3& vPosition, const glm::vec3& vRotation, const glm::vec3& vScale);
		const glm::mat4& getModelMatrix() const { return m_ModelMatrix; }
		glm::vec3 getPosition() const { return m_Position; }
		const glm::vec3& getRotation() const { return m_Rotation; }
		const glm::vec3& getScale() const { return m_Scale; }
		void setPosition(const glm::vec3& vPosition);
		void setRotation(const glm::vec3& vRotation);
		void setScale(const glm::vec3& vScale);
	private:
		void __updateModelMatrix();

		glm::mat4 m_ModelMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}