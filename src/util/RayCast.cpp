#include "RayCast.hpp"

#include <math.h>

auto radians(auto angle)
{
	return angle * 3.14159f / 180;
}

RayCast::RayCast(Vec3 rotation, Vec3 position):
	m_position(position)
{
	m_direction.x = -cos(radians(rotation.y + 90));	
	m_direction.z = sin(radians(rotation.y + 90));	
	m_direction.y = tan(radians(rotation.x));

	m_direction = m_direction * (1.f / m_direction.mod());
}

Vec3 RayCast::step()
{
	m_position = m_position + m_direction;
	return m_direction;
}
