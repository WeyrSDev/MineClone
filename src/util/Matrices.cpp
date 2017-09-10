#include "Matrices.hpp"
namespace MatrixUtil
{
	glm::mat4 getProjectionMatrix(const Camera& camera)
	{
		return glm::perspective(glm::radians(90.f), camera.aspectRatio, 0.1f, 2000.f);
	}

	glm::mat4 getViewMatrix(const Camera& camera)
	{
		glm::mat4 matrix;
		matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), {1, 0, 0});
		matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), {0, 1, 0});
		matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), {0, 0, 1});

		matrix = glm::translate(matrix, -((glm::vec3)camera.position));

		return matrix;
	}

	glm::mat4 getSkyboxViewMatrix(const Camera& camera)
	{
		glm::mat4 matrix;
		matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), {1, 0, 0});
		matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), {0, 1, 0});
		matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), {0, 0, 1});

		return matrix;
	}
}
