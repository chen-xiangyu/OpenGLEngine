#pragma once
#include "ModelLoader/modelLoader.h"

namespace hiveEngine
{
	class CGLTFModel
	{
	public:
		CGLTFModel() = default;
		~CGLTFModel() = default;

		void loadGLTFModel(const std::string& vPath, const std::shared_ptr<hiveGL::CMaterial>& vMaterial);
		void draw() const;

	private:
		std::shared_ptr<hiveGL::CNode> mRootNode = nullptr;

		void __renderNode(const std::shared_ptr<hiveGL::CNode> vNode) const;
		void __renderModel(const std::shared_ptr<hiveGL::CModel> vModel) const;
		void __renderScene(const std::shared_ptr<hiveGL::CNode>& vNode) const;
	};
}