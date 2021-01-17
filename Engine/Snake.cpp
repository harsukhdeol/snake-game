#include "Snake.h"
#include <assert.h>


Snake::Snake(const Location& loc)
{
	constexpr int nBodyColors = 4;
	static constexpr Color bodyColors[nBodyColors]=
	{
		{10,100,255},
		{10,130,255}, 
		{18,160,255}, 
		{10,100,255}
	};

	for (int i = 0; i < nSegMax; ++i) {
		segments[i].InitBody(bodyColors[i % nBodyColors]);

	}
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSeg - 1; i > 0; --i) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSeg < nSegMax) {
		nSeg++;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSeg; i++) {
		segments[i].Draw(brd);
	}
}

Location Snake::GetNextHeadLoc(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::isInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSeg-1; i++) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}
bool Snake::isInTile(const Location& target) const
{
	for (int i = 0; i < nSeg; i++) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}


void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color c_in)
{
	c = c_in;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location Snake::Segment::GetLocation() const
{
	return loc;
}
