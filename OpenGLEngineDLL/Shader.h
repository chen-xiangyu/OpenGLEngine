#pragma once

#include<glad/glad.h>
#include "glm/glm.hpp"

namespace hiveEngine {
	class CShader {
	public:
		CShader() = default;
		~CShader() = default;

		void init(const std::string vertexPath, const std::string fragmentPath); 

		unsigned int getID(); // ��ȡ��ɫ��ID

		void use(); // ʹ����ɫ������

		void setBoolUniform(const std::string& name, bool value) const; // ����bool���͵�uniform����

		void setIntUniform(const std::string& name, int value) const; // ����int���͵�uniform����

		void setFloatUniform(const std::string& name, float value) const; // ����float���͵�uniform����

		void setUniformMatrix4fv(const std::string& name, glm::mat4 value) const;

		void setUniform3fv(const std::string& name, glm::vec3 value) const;

	private:
		unsigned int m_ID;
		void checkCompileErrors(unsigned int shader, std::string type);

		std::string getVertexShaderCode(const std::string vertexPath);

		std::string getFragmentShaderCode(const std::string fragmentPath);

		unsigned int compileShader(const std::string shaderCode, GLenum shaderType);

		unsigned int createShaderProgram(const std::string vertexShaderCode, const std::string fragmentShaderCode);
	};
}
