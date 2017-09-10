#pragma once
#include <vector>

#include "Mesh.hpp"

namespace MeshUtil
{
	VertexData createVertexData(glm::vec3 pos, float light, glm::vec2 texCoords);

	void pushFace(std::vector<VertexData>& vertex, std::vector<GLuint>& indices, glm::vec3 point, glm::vec3 right, glm::vec3 down,
		glm::vec2 texInit, glm::vec2 texSize, float light);
};
