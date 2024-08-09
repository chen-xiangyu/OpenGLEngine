#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace hiveEngine
{
	class ICamera
	{
	public:
		ICamera();
		~ICamera() = default;

		const glm::mat4& getViewMat() const { return m_ViewMat; }
		const glm::mat4& getProjectionMat() const { return m_ProjectionMat; }

		const glm::vec3& getPosition() const { return m_Position; }
		const glm::vec3& getRight() const { return m_Right; }
		const glm::vec3& getUp() const { return m_Up; }
		void setPosition(const glm::vec3& vPosition);
		void setRight(const glm::vec3& vRight);
		void setUp(const glm::vec3& vUp);

		virtual void scale(float vValue) {};

	protected:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::mat4 m_ProjectionMat = glm::identity<glm::mat4>();

		virtual void _updateProjectionMat() = 0;

	private:
		glm::mat4 m_ViewMat = glm::identity<glm::mat4>();

		void __updateViewMat();
	};
}