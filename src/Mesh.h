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

constexpr VertexData genVertexData(float d1, float d2, float d3, float d4, float d5, float d6)
{
	return { {d1, d2, d3}, d4, {d5, d6}};
}

class Mesh {
public:
	Mesh(const std::vector<VertexData>& vertex, const std::vector<GLuint>& indices);
	~Mesh();

	void bind() const { glBindVertexArray(m_VAO); };
	GLuint getIndicesCount() const { return m_indicesCount; };
private:
	GLuint m_VBO, m_VAO, m_EBO;
	GLuint m_indicesCount;
};
