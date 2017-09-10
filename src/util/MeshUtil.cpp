#include "MeshUtil.hpp"

namespace MeshUtil
{
	VertexData createVertexData(glm::vec3 pos, float light, glm::vec2 texCoords)
	{
		return {pos, light, texCoords};
	}

	void pushFace(std::vector<VertexData>& vertex, std::vector<GLuint>& indices, glm::vec3 point,
			glm::vec3 right, glm::vec3 down, glm::vec2 texInit, glm::vec2 texSize, float light)
	{
		glm::vec3 topLeftPos = point;
		glm::vec3 topRightPos = point + right;
		glm::vec3 bottomLeftPos = point + down;
		glm::vec3 bottomRightPos = point + right + down;

		GLuint count = vertex.size();

		vertex.push_back(createVertexData(topLeftPos, light, texInit));
		vertex.push_back(createVertexData(topRightPos, light, texInit + glm::vec2(texSize.x, 0)));
		vertex.push_back(createVertexData(bottomLeftPos, light, texInit + glm::vec2(0, texSize.y)));
		vertex.push_back(createVertexData(bottomRightPos, light, texInit + texSize));

		std::vector<GLuint> newIndices = {
			count, count + 2, count + 1,
			count + 2, count + 3, count + 1
		};

		indices.insert(indices.end(), newIndices.begin(), newIndices.end());
	}
}
