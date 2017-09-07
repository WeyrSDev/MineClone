#pragma once
#include <GL/glew.h>

class Shader {
public:
	Shader(const char* vertexSrc, const char* fragmentSrc);
	virtual ~Shader();

	void bind();
private:
	GLuint m_program;
};
