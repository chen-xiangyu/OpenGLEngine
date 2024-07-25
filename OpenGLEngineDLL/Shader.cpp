#include "pch.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

using namespace hiveEngine;

void CShader::init(std::string vVertexPath, std::string vFragmentPath) {
	std::string VertexShaderCode, FragmentShaderCode;
	unsigned int VertexShader, FragmentShader;

	VertexShaderCode = getVertexShaderCode(vVertexPath);
	FragmentShaderCode = getFragmentShaderCode(vFragmentPath);

	m_ID = createShaderProgram(VertexShaderCode, FragmentShaderCode);

}

unsigned int CShader::compileShader(const std::string shaderCode, GLenum shaderType) {
	unsigned int shader;
	shader = glCreateShader(shaderType);
	const char* shaderCodeChar = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderCodeChar, NULL);
	glCompileShader(shader);
	checkCompileErrors(shader, "SHADER");

	return shader;
}

unsigned int CShader::createShaderProgram(const std::string vertexShaderCode, const std::string fragmentShaderCode) {
	unsigned int vertexShader, fragmentShader, shaderProgram;

	vertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
	fragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkCompileErrors(shaderProgram, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void CShader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[512];
	std::string compileMessage;

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			compileMessage = "ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog + "\n";

			// TODO print error message to log
			std::cout << compileMessage << std::endl;
		}
		else
		{
			compileMessage = type + " shader compiled successfully";
			// TODO print success message to log

			std::cout << compileMessage << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			compileMessage = "ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog + "\n";

			//TODO print error message to log
			std::cout << compileMessage << std::endl;
			std::cout << "finish" << std::endl;
		}
		else
		{
			compileMessage = "Shader program linked successfully";
			// TODO print success message to log

			std::cout << compileMessage << std::endl;
		}
	}
}

std::string CShader::getVertexShaderCode(const std::string vVertexPath) {
	std::string VertexShaderCode;
	std::ifstream VertexShaderFile;

	VertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		VertexShaderFile.open(vVertexPath);
		std::stringstream VertexShaderStream;
		VertexShaderStream << VertexShaderFile.rdbuf();
		VertexShaderFile.close();
		VertexShaderCode = VertexShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		// TODO print error message to log
		std::cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return VertexShaderCode;
}

std::string CShader::getFragmentShaderCode(const std::string vFragmentPath) {
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderFile;

	FragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		FragmentShaderFile.open(vFragmentPath);
		std::stringstream FragmentShaderStream;
		FragmentShaderStream << FragmentShaderFile.rdbuf();
		FragmentShaderFile.close();
		FragmentShaderCode = FragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		// TODO print error message to log
		std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return FragmentShaderCode;
}

unsigned int CShader::getID()
{
	return m_ID;
}

void CShader::use()
{
	glUseProgram(m_ID);
}

void CShader::setBoolUniform(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void CShader::setIntUniform(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void CShader::setFloatUniform(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void CShader::setUniformMatrix4fv(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void CShader::setUniform3fv(const std::string& name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}