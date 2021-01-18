#pragma once
class Vec2
{
public:
	Vec2() = default;// default do nothign contructor
	Vec2(float x_in, float y_in);
	Vec2 operator+ (const Vec2& rhs) const;
	Vec2& operator+= (const Vec2& rhs) ; //should return lhs - modifing it so cant be constant
	Vec2 operator*(float rhs) const; // vector on lhs, float on rhs
	Vec2& operator *= (float rhs);

public:
	float x;
	float y;
};