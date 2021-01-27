#pragma once
class Location
{
public:
	int x; 
	int y;
	void Add(const Location& val)
	{
		x += val .x;
		y += val.y;
	}
	bool operator==(const Location& rhs)const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Location& rhs)const
	{
		return !(*this == rhs);
	}
	Location operator-()const
	{
		return { -x,-y };
	}

	/*Location operator *(const float n) const
	{
		return Location{ x * n, y * n };
	}*/
};
