#pragma once
#include "Board.h"

class Snake
{
public:
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color c_in);
		void MoveBy(const Location& delta_loc);
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
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nSegMax = 100;
	Segment segments[nSegMax];
	int nSeg = 1;
};