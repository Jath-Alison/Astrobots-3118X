#pragma once

#include <string>
#include <cmath>

namespace Jath
{

	struct Vec2
{
	double x;
	double y;

	const double magnitude();
	const double direction();

	const Vec2 normalize();

	const double distTo(Vec2 target);
	const double angleTo(Vec2 target);

	const Vec2 operator+(Vec2 const& obj);
	const Vec2 operator-(Vec2 const& obj);
	const Vec2 operator*(double const& scale);

	const double operator*(Vec2 const& other);

	Vec2& operator+=(Vec2 const& obj);
	Vec2& operator-=(Vec2 const& obj);
	Vec2& operator*=(double const& scale);

	Vec2();

	static Vec2 XandY(double x, double y);
	static Vec2 dirAndMag(double dir, double mag);
};

}