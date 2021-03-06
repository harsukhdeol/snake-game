/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
#include <chrono>
#include "FrameTimer.h"
#include <fstream>
#include <iostream>
#include <string>
 
//using namespace std;
Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx, settings),
	rng(std::random_device()()),
	snake({ 2,2 }),
	nPoison(settings.GetPoison()),
	nFood(settings.GetFood()),
	speedFac(settings.GetSpeedRate())
{
		
	//spawn all this stuff first
	for (int i = 0; i < nPoison; i++)
	{
		brd.SpawnContents(rng, snake, Board::CellContents::Poison);
	}
	for (int i = 0; i < nFood; i++)
	{
		brd.SpawnContents(rng, snake, Board::CellContents::Food);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	if (!isDed) {

		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
		const Location	new_delta_loc = { 0,-1 };
		if (delta_loc != -new_delta_loc || snake.GetLength()<=2) {
			delta_loc = new_delta_loc;
		}
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			const Location	new_delta_loc = { 0,1 };
			if (delta_loc != -new_delta_loc || snake.GetLength() <= 2) {
				delta_loc = new_delta_loc;
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			const Location	new_delta_loc = { -1,0 };
			if (delta_loc != -new_delta_loc || snake.GetLength() <= 2) {
				delta_loc = new_delta_loc;
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			const Location	new_delta_loc = { 1,0 };
			if (delta_loc != -new_delta_loc || snake.GetLength() <= 2) {
				delta_loc = new_delta_loc;
			}
		}
		
	}
	float newSnakeMovePeriod = snakePeriod;

	if (wnd.kbd.KeyIsPressed(VK_CONTROL))
	{
		newSnakeMovePeriod = std::min(snakePeriod, snakeSpeedUp);
	}

	snakeMoveCounter+=dt;
	if (snakeMoveCounter >= newSnakeMovePeriod) {
		snakeMoveCounter -=newSnakeMovePeriod;
		const Location next = snake.GetNextHeadLoc(delta_loc);
		const Board::CellContents contents = brd.IsInsideBoard(next) ? brd.GetContents(next): Board::CellContents::Empty;

		if (!brd.IsInsideBoard(next) || snake.isInTileExceptEnd(next) || contents == Board::CellContents::Obstacle)
		{
			isDed = true;
		}
		else if (contents == Board::CellContents::Food){
			snake.Grow();
			snake.MoveBy(delta_loc);
			brd.ConsumeContents(next);
				brd.SpawnContents(rng, snake, Board::CellContents::Obstacle);
				brd.SpawnContents(rng, snake, Board::CellContents::Food);
		}
		else if (contents == Board::CellContents::Poison)
		{
			snake.MoveBy(delta_loc);
			brd.ConsumeContents(next);
			brd.SpawnContents(rng, snake, Board::CellContents::Poison);
			snakePeriod = std::max(snakePeriod *speedFac, minPeriod);
		}
		else {
			snake.MoveBy(delta_loc);
		}
		snakePeriod = std::max(snakePeriod - dt * speedFac, minPeriod);
	}
}

void Game::ComposeFrame()
{
	
	if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
		playing = true;
	}
	if (playing) {
		brd.DrawBorder();
		brd.DrawContents();
		snake.Draw(brd);

	if (isDed) {
		SpriteCodex::DrawGameOver(300, 250, gfx);
	}
	}
	else {
		SpriteCodex::DrawTitle(300, 200, gfx);
	}
	

	//gfx.DrawCircle(300, 200, 50, Colors::Red);
}
