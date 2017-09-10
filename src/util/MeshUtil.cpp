#include "MeshUtil.hpp"
#include <stdio.h>

namespace MeshUtil
{
	VertexData createVertexData(glm::vec3 pos, float light, glm::vec2 texCoords)
	{
		return {pos, light, texCoords};
	}

	void pushFace(MeshData& data, glm::vec3 point,
			glm::vec3 right, glm::vec3 down, glm::vec2 texInit, glm::vec2 texSize, float light)
	{
		glm::vec3 topLeftPos = point;
		glm::vec3 topRightPos = point + right;
		glm::vec3 bottomLeftPos = point + down;
		glm::vec3 bottomRightPos = point + right + down;

		GLuint count = data.vertex.size();

		data.vertex.push_back(createVertexData(topLeftPos, light, texInit));
		data.vertex.push_back(createVertexData(topRightPos, light, texInit + glm::vec2(texSize.x, 0)));
		data.vertex.push_back(createVertexData(bottomLeftPos, light, texInit + glm::vec2(0, texSize.y)));
		data.vertex.push_back(createVertexData(bottomRightPos, light, texInit + texSize));

		std::vector<GLuint> newIndices = {
			count, count + 2, count + 1,
			count + 2, count + 3, count + 1
		};

		data.indices.insert(data.indices.end(), newIndices.begin(), newIndices.end());
	}
}
