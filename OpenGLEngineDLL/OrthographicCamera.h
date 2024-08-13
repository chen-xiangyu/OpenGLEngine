#pragma once
#include "Camera.h"
#include <glm/glm.hpp>

namespace hiveEngine
{
	class COrthographicCamera : public ICamera
	{
	public:
		COrthographicCamera();
		~COrthographicCamera() = default;

		void setLeft(float vLeft);
		void setRight(float vRight);
		void setTop(float vTop);
		void setBottom(float vBottom);
		void setNear(float vNear);
		void setFar(float vFar);

		void scale(float vValue) override;

	protected:
		void _updateProjectionMat() override;

	private:
		float m_Left = -1.0f;
		float m_Right = 1.0f;
		float m_Top = 1.0f;
		float m_Bottom = -1.0f;
		float m_Near = 0.1f;
		float m_Far = 20.0f;
		float m_Scale = 1.0f;
	};
}