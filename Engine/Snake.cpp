#include "Snake.h"
#include <assert.h>


Snake::Snake(const Location& loc)
{
	
	segments.emplace_back(loc);// can just pass the param and the segment will contruct itself
}

void Snake::MoveBy(const Location& delta_loc)
{

	for (int i = segments.size() - 1; i > 0; --i) {
		segments.at(i).Follow(segments[i - 1]);
	}
	segments.front().MoveBy(delta_loc, speed);
}

void Snake::Grow()
{
	segments.emplace_back(bodyColors[segments.size() % nBodyColors]);
}

void Snake::Draw(Board& brd) const
{
	for (const auto& s: segments) {
		s.Draw(brd);
	}
}

Location Snake::GetNextHeadLoc(const Location& delta_loc) const
{
	Location l(segments.front().GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::isInTileExceptEnd(const Location& target) const
{
	for (size_t i = 0; i<segments.size()-1; i++) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}
bool Snake::isInTile(const Location& target) const
{
	for (const auto& s : segments) {
		if (s.GetLocation() == target) {
			return true;
		}
	}
	return false;
}

void Snake::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}


 Snake::Segment::Segment(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

 Snake::Segment::Segment(Color c_in)
{
	c = c_in;
}

void Snake::Segment::MoveBy(const Location& delta_loc, float speed)
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
