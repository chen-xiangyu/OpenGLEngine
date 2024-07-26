#pragma once
#include<glad/glad.h>
#include "glm/glm.hpp"

namespace hiveEngine {
	constexpr int InfoLength = 512;

	class CShader {
	public:
		CShader() = default;
		~CShader() = default;

		void init(const std::string& vVertexFilename, const std::string& vFragmentFilename);
		void use();

		void setUniformBool(const std::string& vName, bool vValue) const;
		void setUniformInt(const std::string& vName, int vValue) const;
		void setUniformFloat(const std::string& vName, float vValue) const; 
		void setUniformMatrix4fv(const std::string& vName, const glm::mat4& vValue) const;
		void setUniform3fv(const std::string& vName, const glm::vec3& vValue) const;

	private:
		GLuint m_ID;

		void __checkErrors(GLuint vShaderProgram, const std::string& vType);
		std::string __readShaderCode(const std::string& vFilename);
		GLuint __compileShader(const std::string& vFilename, GLenum vType);
	};
}
