#pragma once

#include<vector>

#include<GL/glew.h>
#include<SFML/OpenGL.hpp>
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>

struct VertexData {
	glm::vec3 pos;
	float light;
	glm::vec2 txtCoords;
};

class Mesh {
public:
	Mesh();
	Mesh(const std::vector<VertexData>& vertex, const std::vector<GLuint>& indices);
	~Mesh();

	Mesh(Mesh&& mesh);
	Mesh& operator=(Mesh&& mesh);
	
	Mesh(Mesh& mesh) = delete;
	Mesh& operator=(Mesh& mesh) = delete;

	void destroy();
	void create(const std::vector<VertexData>& vertex, const std::vector<GLuint>& indices);
	void bind() const { glBindVertexArray(m_VAO); };
	GLuint getIndicesCount() const { return m_indicesCount; };
private:
	GLuint m_VBO, m_VAO, m_EBO;
	GLuint m_indicesCount;
};
