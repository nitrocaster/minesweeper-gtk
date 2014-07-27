#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "Tile.hpp"

typedef struct
{
	Tile* t;
	int loc;
} tile_loc;

enum struct GameDifficulty
{
    Easy    = 1,
    Normal  = 2,
    Hard    = 3,
    Custom  = 0
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
	static MinesweeperGame init(GameDifficulty difficulty);
	static void swap(std::vector<int>& a, int i, int j);
	void exit();
	int click(int r, int c);
	void mark(int r, int c);

};

#endif
