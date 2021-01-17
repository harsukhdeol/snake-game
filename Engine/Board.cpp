#include "Board.h"

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
