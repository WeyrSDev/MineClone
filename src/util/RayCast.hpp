#pragma once

#include "Vector.hpp"

class RayCast {
public:
	RayCast(Vec3 rotation, Vec3 position);

	Vec3 step(float d);
private:
	Vec3 m_position, m_direction;
};
