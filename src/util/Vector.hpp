#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

/*
 * A simple vector class for managing conversions between
 * glm and sfml vectors
  */

class Vec3
{
public:
	Vec3(float _x, float _y, float _z);
	Vec3();

	float mod();

	operator glm::vec3() const;
	operator sf::Vector3i() const;

	Vec3 operator + (const Vec3& other) const;
	Vec3 operator - (const Vec3& other) const;
	Vec3 operator * (float scale) const;
	bool operator ==(const Vec3& other) const;

	float x, y, z;
};

class Vec2
{
public:
	Vec2(float _x, float _y);
	Vec2();

	float mod();

	operator glm::vec2() const;
	operator sf::Vector2i() const;

	Vec2 operator + (const Vec2& other) const;
	Vec2 operator - (const Vec2& other) const;
	Vec2 operator * (float scale) const;
	bool operator ==(const Vec2& other) const;

	float x, y;
};
