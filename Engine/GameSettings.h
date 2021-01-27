#pragma once
#include <string>
#include <fstream>
class GameSettings
{
public:
	GameSettings(const std::string& fileName) {
		std::fstream gameFile(fileName);

		for (std::string line; std::getline(gameFile, line);)
		{	
			if (line == "Tile Size")
				{
				gameFile >> tileSize;
				}
			else if (line == "Board Size")
			{
				gameFile >> boardWidth>>boardHeight;
			}
			else if (line == "Speedup Rate")
			{
				gameFile >> speedRate;
			}
			else if (line == "Poison Amount")
			{
				gameFile >> nPoison;
			}
			else if (line == "Food Amount")
			{
				gameFile >> nFood;
			}
		}
		
	}

	int GetTileSize() const {
		return tileSize;
	}
	int GetBoardWidth() const {
		return boardWidth;
	}
	int GetBoardHeight() const {
		return boardHeight;
	}
	int GetPoison() const {
		return nPoison;
	}
	int GetFood() const {
		return nFood;
	}
	float GetSpeedRate() const {
		return speedRate;
	}
private:
	int tileSize;
	int boardWidth;
	int boardHeight;
	int nPoison;
	int nFood;
	float speedRate;

};