#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "tile.h"

#include <vector>

enum DIFFICULTY
{
	EASY = 1, 
	NORMAL = 2,
	HARD = 3
};

class MinesweeperGame
{
private:
	int width;
	int height;
	std::vector<Tile*> board;
	int time_remaining;
	MinesweeperGame(int w, int h);
	static int countBombs(MinesweeperGame& game, int num, ...);
public:
	int getHeight();
	int getWidth();
	std::vector<Tile*> getBoard();

	static MinesweeperGame init(int diff);
	static void swap(std::vector<int>& a, int i, int j);
	void printBoard();

};


#endif
