#pragma once

#include "Graphics.h"
#include "Location.h"

#include <random>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
	void DrawContents();
	int GetContents(const Location& loc)const;
	void ConsumeContents(const Location& loc);
	void SpawnContents(std::mt19937& rng, const class Snake& snake, int type);

private:
	static constexpr int x = 50;
	static constexpr int y = 50;
	static constexpr int borderPadding = 3;
	static constexpr int borderWidth = 3;

	int spacing = 2;
	static constexpr Color color= Colors::Blue;
	static constexpr Color obstColor = Colors::Gray;
	static constexpr Color foodColor = Colors::Red;
	static constexpr Color poisonColor = { 150,10,150 };
	static constexpr int dimension = 20;
	static constexpr int width = 30;
	static constexpr int height = 25;
	//0 = empty, 1= obstacle, 2= poison
	int contents[width * height] = { 0 };
	Graphics& gfx;
};