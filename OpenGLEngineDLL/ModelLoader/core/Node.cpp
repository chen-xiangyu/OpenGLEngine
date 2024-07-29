
#include "Node.h"
#include <queue>

namespace hiveGL
{
	CNode::CNode(const std::string& vNodeName)
		:m_NodeName(vNodeName), m_Transform{}, m_Models{}, m_ChildNodes{}, m_ParentNode{ nullptr }, m_ModelMatrix{}
	{
		__updateModelMatrix();
	}

	void CNode::addChild(const std::shared_ptr<CNode>& vNode)
	{
		m_ChildNodes.push_back(vNode);
		vNode->m_ParentNode = this;
		vNode->__updateModelMatrix();
	}

	void CNode::setPosition(const glm::vec3& vPosition)
	{
		m_Transform.setPosition(vPosition);
		__updateModelMatrix();
	}

	void CNode::setRotation(const glm::vec3& vRotation)
	{
		m_Transform.setRotation(vRotation);
		__updateModelMatrix();
	}

	void CNode::setScale(const glm::vec3& vScale)
	{
		m_Transform.setScale(vScale);
		__updateModelMatrix();
	}

	glm::mat3 CNode::getNormalMatrix() const
	{
		return glm::transpose(glm::inverse(glm::mat3(m_ModelMatrix)));
	}

	void CNode::traverse(const std::shared_ptr<CNode>& vRootNode, std::function<void(const std::shared_ptr<CNode>&)> vFuncTraverse)
	{
		std::queue<std::shared_ptr<CNode>> QueueNodes;
		QueueNodes.push(vRootNode);
		while (!QueueNodes.empty())
		{
			const auto& pCurrNode = QueueNodes.front();
			vFuncTraverse(pCurrNode);
			QueueNodes.pop();
			for (const auto& pNode : pCurrNode->m_ChildNodes)
				QueueNodes.push(pNode);
		}
	}

	void CNode::__updateModelMatrix()
	{
		if (m_ParentNode == nullptr) m_ModelMatrix = m_Transform.getModelMatrix();
		else m_ModelMatrix = m_ParentNode->getModelMatrix() * m_Transform.getModelMatrix();
		for (const auto& pChild : m_ChildNodes)
		{
			pChild->__updateModelMatrix();
		}
	}
}