#include "Mesh.hpp"

#include <stdio.h>

Mesh::Mesh():
	m_VAO(0), m_VBO(0), m_EBO(0), m_indicesCount(0) 
{ }

Mesh::Mesh(const std::vector<VertexData>& vertex, const std::vector<GLuint>& indices)
{
	create(vertex, indices);
}

void Mesh::create(const std::vector<VertexData>& vertex, const std::vector<GLuint>& indices)
{
	m_indicesCount = indices.size();

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	
	//COPY vertex to the GPU
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * vertex.size(), vertex.data(), GL_STATIC_DRAW);

	
	//Vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	//Light
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (4 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
	//Copy indices to the GPU
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}
