#pragma once
#include <GL/glew.h>

class Shader {
public:
	Shader();
	Shader(const char* vertex, const char* fragment);
	
	virtual ~Shader();
	
	void create(const char* vertex, const char* fragment);
	void bind();
private:
	GLuint m_program;
};
