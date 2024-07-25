#pragma once
#include "glm/glm.hpp"

namespace hiveEngine
{
	struct SVertex
	{
		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec3 m_Color;
	};

	class CMesh
	{
	public:
		CMesh();
		~CMesh();

		void loadData(std::vector<SVertex> vVertices, std::vector<unsigned int> vIndices);
		unsigned int getVAO() const { return m_VAO; }
		unsigned int getNumIndices() const { return m_Indices.size(); }

	private:
		std::vector<SVertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;

		void __bindData();
	};
}