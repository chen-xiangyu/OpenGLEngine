#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include "glm/glm.hpp"

namespace hiveEngine {
	class CShader {
	public:
		CShader() = default;
		~CShader() = default;

		void init(const std::string vertexPath, const std::string fragmentPath); // ���캯�������ڶ�ȡ��ɫ���ļ���������ɫ��

		unsigned int getID(); // ��ȡ��ɫ��ID

		void use(); // ʹ����ɫ������

		void setBoolUniform(const std::string& name, bool value) const; // ����bool���͵�uniform����

		void setIntUniform(const std::string& name, int value) const; // ����int���͵�uniform����

		void setFloatUniform(const std::string& name, float value) const; // ����float���͵�uniform����

		void setUniformMatrix4fv(const std::string& name, glm::mat4 value) const;

		void setUniform3fv(const std::string& name, glm::vec3 value) const;

	private:
		unsigned int ID; // ��ɫ��ID
		void checkCompileErrors(unsigned int shader, std::string type); // ��������ɫ���Ĵ���

		std::string getVertexShaderCode(const std::string vertexPath); // ��ȡ������ɫ������

		std::string getFragmentShaderCode(const std::string fragmentPath); // ��ȡƬ����ɫ������

		unsigned int compileShader(const std::string shaderCode, GLenum shaderType); // ������ɫ��

		unsigned int createShaderProgram(const std::string vertexShaderCode, const std::string fragmentShaderCode); // ������ɫ������
	};
}

#endif SHADER_H