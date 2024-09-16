#include "x/Vec2.h"

namespace x{

	Vec2::Vec2() : x(0.0), y(0.0){}

	const float Vec2::magnitude()
	{
		return std::sqrt( pow(x, 2) + pow(y, 2) );
	}

	const float Vec2::direction()
	{
		float angle = 0;
		angle = atan2(x, y);
		return angle;
	}

	void Vec2::normalize()
	{
		float scale = 1.f / magnitude();
		*this = *this * scale;
	}

	const float Vec2::distTo(Vec2 target)
	{
		Vec2 dist = target - *this;
		return dist.magnitude();
	}

	const float Vec2::angleTo(Vec2 target)
	{
		Vec2 dist = target - *this;
		return dist.direction();
	}

	const Vec2 Vec2::operator+(Vec2 const& obj)
	{
		Vec2 output = XandY(this->x + obj.x, this->y + obj.y);
		return output;
	}

	const Vec2 Vec2::operator-(Vec2 const& obj)
	{
		Vec2 output = XandY(this->x - obj.x, this->y - obj.y);
		return output;
	}

	const Vec2 Vec2::operator *(float const& scale)
	{
		Vec2 output = XandY(this->x * scale, this->y * scale);
		return output;
	}

	Vec2 XandY(float x, float y)
	{
		Vec2 output;
		output.x = x;
		output.y = y;
		return output;
	}

	Vec2 dirAndMag(float dir, float mag)
	{
		Vec2 output;
		output.x = mag * sin(dir);
		output.y = mag * cos(dir);
		return output;
	}
}