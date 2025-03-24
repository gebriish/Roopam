#include "shader.hpp"
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace Rpm {

void _check_compile_errors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, 0L, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, 0L, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void shaderLoadGlslFromSource(Shader& shader, const char* vertexSource, const char* fragmentSource) {
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, 0L);
	glCompileShader(vertex);
	_check_compile_errors(vertex, "VERTEX");
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, 0L);
	glCompileShader(fragment);
	_check_compile_errors(fragment, "FRAGMENT");
	shader.Id = glCreateProgram();
	glAttachShader(shader.Id, vertex);
	glAttachShader(shader.Id, fragment);
	glLinkProgram(shader.Id);
	_check_compile_errors(shader.Id, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void shaderLoadGlsl(Shader& shader, const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure &e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	shaderLoadGlslFromSource(shader, vShaderCode, fShaderCode);
}

void shaderUseProgram(const Shader& shader) {
	glUseProgram(shader.Id);
}

void shaderDeleteProgram(const Shader& shader) {
	glDeleteProgram(0);
}

void shaderUploadInt(const Shader& program, const char* name, int v) {
	glUniform1i(glGetUniformLocation(program.Id, name), v);
}

void shaderUploadIntArray(const Shader& program, const char* name, int* v, int size) {
	glUniform1iv(glGetUniformLocation(program.Id, name), size, v);
}

void shaderUploadFloat(const Shader& program, const char* name, float v) {
	glUniform1f(glGetUniformLocation(program.Id, name), v);
}

void shaderUploadFloat2(const Shader& program, const char* name, float x, float y) {
	glUniform2f(glGetUniformLocation(program.Id, name), x, y);
}

void shaderUploadFloat3(const Shader& program, const char* name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(program.Id, name), x, y, z);
}

void shaderUploadFloat4(const Shader& program, const char* name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(program.Id, name), x, y, z, w);
}

void shaderUploadFloatArray(const Shader& program, const char* name, const float* array, int size) {
	glUniform1fv(glGetUniformLocation(program.Id, name), size, array);
}

void shaderUploadMat4(const Shader& program, const char* name, const float* mat) {
	GLint location = glGetUniformLocation(program.Id, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, mat);
}

}
