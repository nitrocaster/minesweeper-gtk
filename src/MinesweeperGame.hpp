#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <unordered_set>
#include <queue>
#include "Common.hpp"
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

	Size size;
	int mined_tiles;
	int unsafe_tiles;
	std::vector<Tile*> board;
	bool game_over;

	std::unordered_set<int> corners;
	std::unordered_set<int> left_row;
	std::unordered_set<int> right_row;
	std::unordered_set<int> top_row;
	std::unordered_set<int> bottom_row;

	int get_mine_count(std::initializer_list<int> indices);
	void add_adjacent(std::queue<IndexedTile>& q, std::initializer_list<int> indices);

public:
    MinesweeperGame();
    MinesweeperGame(int w, int h, int m);
    static MinesweeperGame initialize(GameDifficulty difficulty);

    Size get_size() const;
	int get_mined_tile_count();
	int get_unsafe_tile_count();
	bool is_over();
	std::vector<Tile*> get_board();
	void exit();
	bool click(int row, int column);
	void mark_tile(int row, int column);
};

#endif
