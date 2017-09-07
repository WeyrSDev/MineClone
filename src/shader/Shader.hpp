#pragma once
#include <GL/glew.h>

#include "util/Matrices.hpp"

class Shader {
public:
	Shader();
	Shader(const char* vertex, const char* fragment);
	
	virtual ~Shader();
	
	void setTransformMatrix(glm::mat4 matrix);
	void create(const char* vertex, const char* fragment);
	void bind();
private:
	GLuint m_program;
	GLuint m_transformMatrix;
};
