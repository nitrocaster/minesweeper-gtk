#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "Tile.hpp"

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
    // for adjacent tiles search
    struct IndexedTile
    {
        Tile *tile;
        int index;
    };

	int width;
	int height;
	int mined_tiles;
	int unsafe_tiles;
	std::vector<Tile*> board;
	int time_remaining;
	bool game_over;

	std::unordered_set<int> corners;
	std::unordered_set<int> left_row;
	std::unordered_set<int> right_row;
	std::unordered_set<int> top_row;
	std::unordered_set<int> bottom_row;

	static int get_mine_count(MinesweeperGame& game, int num, ...);
	void add_adjacent(std::queue<IndexedTile>& q, int num, ...);

public:
    MinesweeperGame();
    MinesweeperGame(int w, int h, int m);
    static MinesweeperGame initialize(GameDifficulty difficulty);

	int get_height();
	int get_width();
	int get_mined_tile_count();
	int get_unsafe_tile_count();
	bool is_over();
	std::vector<Tile*> get_board();
	void exit();
	bool click(int r, int c);
	void mark_tile(int r, int c);
};

#endif
