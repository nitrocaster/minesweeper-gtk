#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

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

class GameWindow;

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
    std::vector<Tile*> board;
    int mined_tiles;
    int unsafe_tiles;
    bool game_over;
    bool initialized;

    GameDifficulty difficulty = GameDifficulty::Custom;
    GameWindow *window = nullptr;

    std::unordered_set<int> corners;
    std::unordered_set<int> left_row;
    std::unordered_set<int> right_row;
    std::unordered_set<int> top_row;
    std::unordered_set<int> bottom_row;

    int get_mine_count(std::initializer_list<int> indices);
    void add_adjacent(std::queue<IndexedTile> &qu, std::initializer_list<int> indices);
    void initialize(Size size, int mine_count);
    void destroy();

public:
    MinesweeperGame(NoInit);
    explicit MinesweeperGame(GameDifficulty difficulty);
    ~MinesweeperGame();

    Size get_size() const;
    std::vector<Tile*> &get_board();
    int get_mined_tile_count() const;
    int get_unsafe_tile_count() const;
    bool is_over() const;
    GameDifficulty get_game_difficulty() const;
    GameWindow* get_window();
    void set_window(GameWindow& window);
    void initialize(GameDifficulty difficulty);
    bool sweep_tile(int row, int column);
    void mark_tile(int row, int column);
};

#endif
