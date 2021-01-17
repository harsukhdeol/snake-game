#pragma once

#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
private:
	static constexpr int x = 50;
	static constexpr int y = 50;
	static constexpr int borderPadding = 3;
	static constexpr int borderWidth = 3;

	int spacing = 2;
	static constexpr Color color= Colors::Blue;
	static constexpr int dimension = 20;
	static constexpr int width = 30;
	static constexpr int height = 25;
	Graphics& gfx;
};