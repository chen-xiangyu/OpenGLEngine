#pragma once

#include <vector>
#include <string>
#include <functional>
#include "Transform.h"
#include "Model.h"

namespace hiveGL
{
	class CNode
	{
	public:
		CNode(const std::string& vNodeName = "");
		const std::string& getNodeName() const { return m_NodeName; }
		glm::mat4 getModelMatrix() const { return m_ModelMatrix; }
		const std::vector<std::shared_ptr<CModel>>& getModels() const { return m_Models; }
		const std::vector<std::shared_ptr<CNode>>& getChildNodes() const { return m_ChildNodes; }
		void addModel(const std::shared_ptr<CModel>& vModel) { m_Models.push_back(vModel); }
		void clearChilds() { m_ChildNodes.clear(); }
		void addChild(const std::shared_ptr<CNode>& vNode);
		void setPosition(const glm::vec3& vPosition);
		void setRotation(const glm::vec3& vRotation);
		void setScale(const glm::vec3& vScale);
		void setNodeName(const std::string& vNodeName) { m_NodeName = vNodeName; }
		glm::mat3 getNormalMatrix() const;
		const CTransform& getTransform() const { return m_Transform; }
		static void traverse(const std::shared_ptr<CNode>& vRootNode, std::function<void(const std::shared_ptr<CNode>&)> vFuncTraverse);
	private:
		void __updateModelMatrix();
		std::string m_NodeName;
		CTransform m_Transform;
		glm::mat4 m_ModelMatrix;
		CNode* m_ParentNode; // dangerous
		std::vector<std::shared_ptr<CModel>> m_Models;
		std::vector<std::shared_ptr<CNode>> m_ChildNodes;
	};
}