#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include "glm/glm.hpp"

namespace hiveEngine {
	class CShader {
	public:
		CShader() = default;
		~CShader() = default;

		void init(const std::string vertexPath, const std::string fragmentPath); // 构造函数，用于读取着色器文件并编译着色器

		unsigned int getID(); // 获取着色器ID

		void use(); // 使用着色器程序

		void setBoolUniform(const std::string& name, bool value) const; // 设置bool类型的uniform变量

		void setIntUniform(const std::string& name, int value) const; // 设置int类型的uniform变量

		void setFloatUniform(const std::string& name, float value) const; // 设置float类型的uniform变量

		void setUniformMatrix4fv(const std::string& name, glm::mat4 value) const;

		void setUniform3fv(const std::string& name, glm::vec3 value) const;

	private:
		unsigned int ID; // 着色器ID
		void checkCompileErrors(unsigned int shader, std::string type); // 检查编译着色器的错误

		std::string getVertexShaderCode(const std::string vertexPath); // 获取顶点着色器代码

		std::string getFragmentShaderCode(const std::string fragmentPath); // 获取片段着色器代码

		unsigned int compileShader(const std::string shaderCode, GLenum shaderType); // 编译着色器

		unsigned int createShaderProgram(const std::string vertexShaderCode, const std::string fragmentShaderCode); // 创建着色器程序
	};
}

#endif SHADER_H