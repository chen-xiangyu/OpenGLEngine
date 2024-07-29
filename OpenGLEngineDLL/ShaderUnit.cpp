#include "pch.h"
#include "ShaderUnit.h"
#include <glm/gtc/type_ptr.hpp>

using namespace hiveEngine;

void CShaderUnit::init(const std::string& vVertexFilename, const std::string& vFragmentFilename)
{
	GLuint VertexShader = __compileShader(vVertexFilename, GL_VERTEX_SHADER);
	GLuint FragmentShader = __compileShader(vFragmentFilename, GL_FRAGMENT_SHADER);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, VertexShader);
	glAttachShader(m_ID, FragmentShader);

	glLinkProgram(m_ID);
	__checkErrors(m_ID, "PROGRAM");

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

GLuint CShaderUnit::__compileShader(const std::string& vFilename, GLenum vType)
{
	GLuint Shader = glCreateShader(vType);

	std::string ShaderCode = __readShaderCode(vFilename);
	const char* ShaderCodeChar = ShaderCode.c_str();

	glShaderSource(Shader, 1, &ShaderCodeChar, NULL);
	glCompileShader(Shader);
	__checkErrors(Shader, "SHADER");

	return Shader;
}

void CShaderUnit::__checkErrors(GLuint vShaderProgram, const std::string& vType)
{
	int IsSuccess = false;
	char InfoLog[InfoLength];

	if (vType == "SHADER")
	{
		glGetShaderiv(vShaderProgram, GL_COMPILE_STATUS, &IsSuccess);
		if (!IsSuccess)
		{
			glGetShaderInfoLog(vShaderProgram, InfoLength, NULL, InfoLog);
			HIVE_LOG_ERROR("ERROR::SHADER::COMPILATION_FAILED: {}", InfoLog);
		}
		else
		{
			HIVE_LOG_INFO("Shader compiled successfully");
		}
	}
	else if (vType == "PROGRAM")
	{
		glGetProgramiv(vShaderProgram, GL_LINK_STATUS, &IsSuccess);
		if (!IsSuccess)
		{
			glGetProgramInfoLog(vShaderProgram, InfoLength, NULL, InfoLog);
			HIVE_LOG_ERROR("ERROR::PROGRAM_LINKING_ERROR: {}", InfoLog);
		}
		else
		{
			HIVE_LOG_INFO("Program linked successfully");
		}
	}
}

std::string CShaderUnit::__readShaderCode(const std::string& vFilename)
{
	std::string ShaderCode;
	std::ifstream ShaderFile;
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		ShaderFile.open(vFilename);
		std::stringstream ShaderStream;
		ShaderStream << ShaderFile.rdbuf();
		ShaderFile.close();
		ShaderCode = ShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		HIVE_LOG_ERROR("ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ: {}", e.what());
	}

	return ShaderCode;
}

void CShaderUnit::use()
{
	glUseProgram(m_ID);
}

void CShaderUnit::setUniformBool(const std::string& vName, bool vValue) const
{
	glUniform1i(glGetUniformLocation(m_ID, vName.c_str()), (int)vValue);
}

void CShaderUnit::setUniformInt(const std::string& vName, int vValue) const
{
	glUniform1i(glGetUniformLocation(m_ID, vName.c_str()), vValue);
}

void CShaderUnit::setUniformFloat(const std::string& vName, float vValue) const
{
	glUniform1f(glGetUniformLocation(m_ID, vName.c_str()), vValue);
}

void CShaderUnit::setUniformMatrix4fv(const std::string& vName, const glm::mat4& vValue) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, vName.c_str()), 1, GL_FALSE, glm::value_ptr(vValue));
}

void CShaderUnit::setUniform3fv(const std::string& vName, const glm::vec3& vValue) const
{
	glUniform3fv(glGetUniformLocation(m_ID, vName.c_str()), 1, glm::value_ptr(vValue));
}