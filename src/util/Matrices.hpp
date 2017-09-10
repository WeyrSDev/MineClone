#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

namespace MatrixUtil
{
	glm::mat4 getViewMatrix(const Camera& camera);
	glm::mat4 getProjectionMatrix(const Camera& camera);
	glm::mat4 getSkyboxViewMatrix(const Camera& camera);
}
