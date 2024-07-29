#pragma once

#include <memory>
#include "core/Node.h"
#include "camera/Camera.h"
#include "light/Light.h"

namespace hiveGL
{
	class CScene
	{
	public:
		CScene();
		const std::shared_ptr<CNode>& getRootNode() const { return m_pRootNode; }
		const std::shared_ptr<CCamera>& getCamera() const { return m_pCamera; }
		const std::shared_ptr<CLight>& getLight() const { return m_pLight; }
		void setCamera(const std::shared_ptr<CCamera>& vCamera) { m_pCamera = vCamera; }
		void setLight(const std::shared_ptr<CLight>& vLight) { m_pLight = vLight; }
	private:
		std::shared_ptr<CNode> m_pRootNode;
		std::shared_ptr<CCamera> m_pCamera;
		std::shared_ptr<CLight> m_pLight;
	};
}