#include "Vector.hpp"

#include <math.h>

Vec3::Vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vec3::Vec3():
	x(0), y(0), z(0)
{
}

float Vec3::mod()
{
	return sqrt(x * x + y * y + z * z);
}

Vec3::operator glm::vec3() const
{
	return glm::vec3(x, y ,z);
}

Vec3::operator sf::Vector3i() const
{
	return sf::Vector3i(x, y, z);
}

Vec3 Vec3::operator + (const Vec3& other) const
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator - (const Vec3& other) const
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator * (float scale) const
{
	return Vec3(x * scale, y * scale, z * scale);
}

bool Vec3::operator == (const Vec3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

Vec2::Vec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vec2::Vec2():
	x(0), y(0)
{
}

float Vec2::mod()
{
	return sqrt(x * x + y * y);
}

Vec2::operator glm::vec2() const
{
	return glm::vec2(x, y);
}

Vec2::operator sf::Vector2i() const
{
	return sf::Vector2i(x, y);
}

Vec2 Vec2::operator + (const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator - (const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator * (float scale) const
{
	return Vec2(x * scale, y * scale);
}

bool Vec2::operator == (const Vec2& other) const
{
	return x == other.x && y == other.y;
}
