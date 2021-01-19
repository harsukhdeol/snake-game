#include "Board.h"
#include <assert.h>
#include "Snake.h"
#include "Goal.h"

Board::Board(Graphics& gfx)
	: gfx(gfx)
{}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.y >= 0);
	assert(loc.x < width);
	assert(loc.y < height);
	const int offX = x + borderWidth + borderPadding;
	const int offY = y + borderWidth + borderPadding;
	gfx.DrawRectDim(offX+loc.x * dimension+spacing, offY+loc.y * dimension+spacing,
		dimension-spacing, dimension-spacing, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width&&
		loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	gfx.DrawRect(left, top, right, top + borderWidth, color);
	gfx.DrawRect(left, top, left+borderWidth, bottom -borderWidth, color);
	gfx.DrawRect(right-borderWidth, top, right, bottom -borderWidth, color);
	gfx.DrawRect(left, bottom -borderWidth, right, bottom, color);
}

void Board::DrawObstacles()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (CheckForObstacle({ x,y }))
			{
				DrawCell({ x,y }, obstColor);
			}
		}
	}
}

bool Board::CheckForObstacle(const Location& loc) const
{
	return hasObstacle[loc.y*width+loc.x];
}

void Board::SpawnObstacle(std::mt19937& rng, const Snake& snake, const Goal& goal)
{
	std::uniform_int_distribution <int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution <int> yDist(0, GetGridHeight() - 1);

	Location newLoc;

	do {
		newLoc = { xDist(rng), yDist(rng) };
	} while (snake.isInTile(newLoc) ||CheckForObstacle(newLoc) ||goal.GetLocation()== newLoc); // while any of these are true, keep looping
	
	hasObstacle[newLoc.y * width + newLoc.x] = true;
}
