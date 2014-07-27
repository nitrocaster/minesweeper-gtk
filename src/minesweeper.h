#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "tile.h"

#include <vector>
#include <unordered_set>
#include <queue>

typedef struct
{
	Tile* t;
	int loc;
}tile_loc;

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

	std::unordered_set<int> corners;
	std::unordered_set<int> left_row;
	std::unordered_set<int> right_row;
	std::unordered_set<int> top_row;
	std::unordered_set<int> bottom_row;

	static int countBombs(MinesweeperGame& game, int num, ...);
	void addAdjacent(std::queue<tile_loc>& q, int num, ...);

public:
	int getHeight();
	int getWidth();
	int getNumMines();
	int getNumOpen();
	
	bool isLive();
	std::vector<Tile*> getBoard();
	
	MinesweeperGame();
        MinesweeperGame(int w, int h, int m);
	static MinesweeperGame init(int diff);
	static void swap(std::vector<int>& a, int i, int j);
	void printTrueBoard();
	void printGameBoard();
	void exit();
	int click(int r, int c);
	void mark(int r, int c);

};


#endif
