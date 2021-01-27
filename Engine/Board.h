#pragma once

#include "Graphics.h"
#include "Location.h"
#include "GameSettings.h"
#include <random>
#include <vector>

class Board
{

public:

	enum class CellContents{Empty,Obstacle,Food,Poison};

	Board(Graphics& gfx, const GameSettings& settings);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
	void DrawContents();
	CellContents GetContents(const Location& loc)const;
	void ConsumeContents(const Location& loc);
	void SpawnContents(std::mt19937& rng, const class Snake& snake, CellContents type);

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
	 int dimension;
	 int width;
	 int height;
	std::vector<CellContents> contents;
	Graphics& gfx;
};