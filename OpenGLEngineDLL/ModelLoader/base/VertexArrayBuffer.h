#pragma once

#include <glad/glad.h>
#include <vector>

namespace hiveGL
{
	class CVertexArrayBuffer
	{
	public:
		CVertexArrayBuffer(
			const std::vector<float>& vVertices,
			const std::vector<int>& vLayout,
			GLenum vDrawMode = GL_TRIANGLES,
			GLenum vUsage = GL_STATIC_DRAW
		);
		CVertexArrayBuffer(
			const std::vector<float>& vVertices,
			const std::vector<unsigned int>& vIndices,
			const std::vector<int>& vLayout,
			GLenum vDrawMode = GL_TRIANGLES,
			GLenum vUsage = GL_STATIC_DRAW
		);
		~CVertexArrayBuffer();
		virtual void draw() const;
	private:
		void __configVertexLayout(const std::vector<int>& vLayout) const;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
		GLsizei m_VerticesCount;
		GLenum m_DrawMode;
	};
}