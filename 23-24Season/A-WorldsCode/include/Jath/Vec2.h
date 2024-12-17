#pragma once

#include <string>
#include <cmath>

namespace Jath
{

	struct Vec2
	{
		float x;
		float y;

		const float magnitude();
		const float direction();

		void normalize();

		const float distTo(Vec2 target);
		const float angleTo(Vec2 target);

		const Vec2 operator+(Vec2 const &obj);
		const Vec2 operator-(Vec2 const &obj);
		const Vec2 operator*(float const &scale);

		Vec2();
	};

	Vec2 XandY(float x, float y);
	Vec2 dirAndMag(float dir, float mag);

}