#include "pch.h"
#include "GLTFModel.h"

using namespace hiveEngine;

void CGLTFModel::loadGLTFModel(const std::string& vPath, const std::shared_ptr<hiveGL::CMaterial>& vMaterial)
{
    mRootNode = hiveGL::loader::loadModel(vPath, vMaterial);
}

void CGLTFModel::draw() const
{
    __renderScene(mRootNode);
}

void CGLTFModel::__renderNode(const std::shared_ptr<hiveGL::CNode> vNode) const
{
    if (!vNode) return;

    glm::mat4 modelMatrix = vNode->getModelMatrix();

    for (const auto& model : vNode->getModels()) {
        __renderModel(model);
    }
}

void CGLTFModel::__renderModel(const std::shared_ptr<hiveGL::CModel> vModel) const
{
    vModel->getVAO()->draw();
}

void CGLTFModel::__renderScene(const std::shared_ptr<hiveGL::CNode>& vRootNode) const
{
    auto renderFunc = [&](const std::shared_ptr<hiveGL::CNode>& vNode) {
        __renderNode(vNode);
    };

    hiveGL::CNode::traverse(vRootNode, renderFunc);
}