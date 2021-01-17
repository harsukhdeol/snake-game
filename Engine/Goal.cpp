#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution <int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution <int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;

	do {
		newLoc = { xDist(rng), yDist(rng) };
	} while (snake.isInTile(newLoc));
	loc = newLoc;
}

void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location Goal::GetLocation() const
{
	return loc;
}
