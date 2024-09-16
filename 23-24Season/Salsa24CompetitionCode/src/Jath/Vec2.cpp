#include "Jath/Vec2.h"

namespace Jath
{

	Vec2::Vec2() : x(0.0), y(0.0) {}

	const double Vec2::magnitude()
	{
		return std::sqrt(pow(x, 2) + pow(y, 2));
	}

	const double Vec2::direction()
	{
		double angle = 0;
		angle = atan2(x, y);
		return angle;
	}

	const Vec2 Vec2::normalize()
	{
		double scale = 1.f / magnitude();
		Vec2 out = *this * scale;
		return out;
	}

	const double Vec2::distTo(Vec2 target)
	{
		Vec2 dist = target - *this;
		return dist.magnitude();
	}

	const double Vec2::angleTo(Vec2 target)
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

	const Vec2 Vec2::operator*(double const& scale)
	{
		Vec2 output = XandY(this->x * scale, this->y * scale);
		return output;
	}

	const double Vec2::operator*(Vec2 const& other)
	{
		return  x*other.x + y*other.y ;
	}

	Vec2& Vec2::operator+=(Vec2 const& obj)
	{
		this->x += obj.x;
		this->y += obj.y;
		return *this;
	}

	Vec2& Vec2::operator-=(Vec2 const& obj)
	{
		this->x -= obj.x;
		this->y -= obj.y;
		return *this;
	}

	Vec2& Vec2::operator*=(double const& scale)
	{
		this->x *= scale;
		this->y *= scale;
		return *this;
	}

	Vec2 Vec2::XandY(double x, double y)
	{
		Vec2 output;
		output.x = x;
		output.y = y;
		return output;
	}

	Vec2 Vec2::dirAndMag(double dir, double mag)
	{
		Vec2 output;
		output.x = mag * sin(dir);
		output.y = mag * cos(dir);
		return output;
	}
}