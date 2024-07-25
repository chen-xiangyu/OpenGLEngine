#pragma once

#include<glad/glad.h>
#include "glm/glm.hpp"

namespace hiveEngine {
	class CShader {
	public:
		CShader() = default;
		~CShader() = default;

		void init(const std::string vertexPath, const std::string fragmentPath); 

		unsigned int getID(); // 获取着色器ID

		void use(); // 使用着色器程序

		void setBoolUniform(const std::string& name, bool value) const; // 设置bool类型的uniform变量

		void setIntUniform(const std::string& name, int value) const; // 设置int类型的uniform变量

		void setFloatUniform(const std::string& name, float value) const; // 设置float类型的uniform变量

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
