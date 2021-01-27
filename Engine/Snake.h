#pragma once
#include "Board.h"
#include <vector>

class Snake
{
private:
	class Segment
	{
	public:
		Segment (const Location& in_loc);
		Segment (Color c_in);
		void MoveBy(const Location& delta_loc, float speed);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		const Location GetLocation()const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd ) const;
	Location GetNextHeadLoc(const Location& delta_loc) const;
	bool isInTileExceptEnd(const Location& target) const;
	bool isInTile(const Location& target) const;
	void SetSpeed(float newSpeed);
	int GetLength()const {
		return segments.size();
	}
private:
	float speed = 0.025f;
	static constexpr Color headColor = Colors::Yellow;
	std::vector<Segment> segments;
	static constexpr int nBodyColors = 4;
	static constexpr Color bodyColors[nBodyColors] =
	{
		{10,100,0},
		{10,130,0},
		{18,160,0},
		{10,100,0}
	};
};