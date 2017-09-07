#include <stdio.h>
#include <stdexcept>

#include "util/FilePaths.hpp"
#include "Shader.hpp"
#include "util/Files.hpp"

Shader::Shader() : m_program(0)
{ }

Shader::Shader(const char* vertex, const char* fragment)
{
	create(vertex, fragment);
}

void Shader::create(const char* vertex, const char* fragment)
{
	std::string vertexSrc = getFileSrc(std::string(shaderPath) + vertex);
	std::string fragmentSrc = getFileSrc(std::string(shaderPath) + fragment);

	GLchar* vSrc = (GLchar*) vertexSrc.c_str();
	GLchar* fSrc = (GLchar*) fragmentSrc.c_str();
	int success;
	char infoLog[512];
	
	//Load vertex
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSrc, 0);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Error compiling vertex shader\n%s\n", infoLog);

		throw std::invalid_argument("Cannot compile shader");
	}

	//Load fragment
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fSrc, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("Error compiling fragment shader\n%s\n", infoLog);

		throw std::invalid_argument("Cannot compile shader");
	}

	//Linking both shaders and creating program
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_transformMatrix = glGetUniformLocation(m_program, "transformMatrix");
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::bind()
{
	glUseProgram(m_program);
}


void Shader::setTransformMatrix(glm::mat4 matrix)
{
	glUniformMatrix4fv(m_transformMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
}
