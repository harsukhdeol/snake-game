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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	goal(rng,brd,snake)
{
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
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}
	}
	
	snakeMoveCounter+=dt;
	if (snakeMoveCounter >= snakePeriod) {
		snakeMoveCounter = 0.0f;
		const Location next = snake.GetNextHeadLoc(delta_loc);
		if (!brd.IsInsideBoard(next) || snake.isInTileExceptEnd(next) || brd.CheckForObstacle(next) )
		{
			isDed = true;
		}
		else {
			bool eating = next == goal.GetLocation();
			if (eating) {
				snake.Grow();
			}
			snake.MoveBy(delta_loc);
			if (eating) {
				goal.Respawn(rng, brd, snake);
				brd.SpawnObstacle(rng, snake, goal);
			}
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
		brd.DrawObstacles();
	snake.Draw(brd);
	goal.Draw(brd);

	if (isDed) {
		SpriteCodex::DrawGameOver(300, 250, gfx);
	}
	}
	else {
		SpriteCodex::DrawTitle(300, 200, gfx);
	}
	

	//gfx.DrawCircle(300, 200, 50, Colors::Red);
}
