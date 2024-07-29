
#include "Scene.h"

namespace hiveGL
{
	CScene::CScene() :m_pRootNode(std::make_shared<CNode>("ROOT")), m_pCamera(nullptr), m_pLight(nullptr)
	{
	}
}