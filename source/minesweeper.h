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
	int num_mines;
	std::vector<Tile*> board;
	int time_remaining;
	bool live;
	int num_open;
	MinesweeperGame(int w, int h, int m);
	static int countBombs(MinesweeperGame& game, int num, ...);

public:
	int getHeight();
	int getWidth();
	int getNumMines();
	bool isLive();
	std::vector<Tile*> getBoard();

	static MinesweeperGame init(int diff);
	static void swap(std::vector<int>& a, int i, int j);
	void printTrueBoard();
	void printGameBoard();
	void exit();
	int click(int r, int c);

};


#endif
