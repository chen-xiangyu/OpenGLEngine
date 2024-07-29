#pragma once
#include<glad/glad.h>
#include "glm/glm.hpp"

namespace hiveEngine {
	constexpr int InfoLength = 512;

	class CShaderUnit {
	public:
		CShaderUnit() = default;
		~CShaderUnit() = default;

		void init(const std::string& vName, const std::string& vVertexFilename, const std::string& vFragmentFilename);
		void use();
		void setUniformModifier(const std::string& vName, const std::function<std::any()>& vModifier);
		std::string getName() const { return m_Name; }

		void setUniform(const std::string& vName, bool vValue) const;
		void setUniform(const std::string& vName, int vValue) const;
		void setUniform(const std::string& vName, float vValue) const;
		void setUniform(const std::string& vName, const glm::mat4& vValue) const;
		void setUniform(const std::string& vName, const glm::vec3& vValue) const;

	private:
		GLuint m_ID;
		std::string m_Name;
		std::map<std::string, std::function<std::any()>> m_UniformModifiers;

		void __checkErrors(GLuint vShaderProgram, const std::string& vType);
		std::string __readShaderCode(const std::string& vFilename);
		GLuint __compileShader(const std::string& vFilename, GLenum vType);
		void __updateUniform();
	};
}
