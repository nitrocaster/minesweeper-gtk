#include <random>
#include <string>
#include "MinesweeperGame.hpp"

MinesweeperGame::MinesweeperGame()
{
}

MinesweeperGame::MinesweeperGame(int w, int h, int m)
{
    mined_tiles = m;
    time_remaining = 0;
    game_over = false;
    size = Size(w, h);
    int a = size.area();
    unsafe_tiles = a-m;
    board.resize(a);
    for (int i = 0; i < a; i++)
    {
        board[i] = new Tile();
    }
    corners.emplace(0);
    corners.emplace(a-1);
    corners.emplace(w-1);
    corners.emplace(a-w);
    for (int i = 1; i < w-1; i++)
    {
        top_row.emplace(i);
    }
    for (int i = w; i < a-w; i += w)
    {
        left_row.emplace(i);
    }
    for (int i = w*2-1; i < a-1; i += w)
    {
        right_row.emplace(i);
    }
    for (int i = a-w+1; i < a-1; i++)
    {
        bottom_row.emplace(i);
    }
}

Size MinesweeperGame::get_size() const
{
    return size;
}

int MinesweeperGame::get_mined_tile_count()
{
    return mined_tiles;
}

bool MinesweeperGame::is_over()
{
    return game_over;
}

int MinesweeperGame::get_unsafe_tile_count()
{
    return unsafe_tiles;
}

std::vector<Tile*> MinesweeperGame::get_board()
{
    return board;
}

int MinesweeperGame::get_mine_count(std::initializer_list<int> indices)
{
    int mines = 0;
    for (int loc : indices)
    {
        if (board[loc]->get_value() < 0)
        {
            mines++;
        }
    }
    return mines;
}

void MinesweeperGame::add_adjacent(std::queue<IndexedTile> &q, std::initializer_list<int> indices)
{
    for (int loc : indices)
    {
        if (board[loc]->is_swept())
        {
            continue;
        }
        q.push({board[loc], loc});
    }
}

MinesweeperGame MinesweeperGame::initialize(GameDifficulty difficulty)
{
    int w = 0, h = 0, m = 0;
    switch (difficulty)
    {
    case GameDifficulty::Easy:
        w = 9;
        h = 9;
        m = 10;
        break;
        
    case GameDifficulty::Hard:
        w = 30;
        h = 16;
        m = 99;
        break;
        
    default:
    case GameDifficulty::Normal:
        w = 16;
        h = 16;
        m = 40;
    }
    MinesweeperGame game(w, h, m);
    std::vector<int> positions(w*h);
    for (int i = 0; i < w*h; i++)
    {
        positions[i] = i;
    }
    std::random_device rd;
    std::default_random_engine generator(rd());
    int last = w*h-1;
    for (int i = m; i > 0; i--)
    {
        std::uniform_int_distribution<int> distribution(0, last);
        int r_index = distribution(generator);
        int r_value = positions[r_index];
        game.get_board()[r_value]->set_value(-1);
        std::swap(positions[r_index], positions[last--]);
    }
    for (int i = 0; i < w*h; i++)
    {
        if (game.get_board()[i]->get_value() < 0)
        {
            continue;
        }
        int val = 0;
        if (game.left_row.find(i) != game.left_row.end())
        {
            val = game.get_mine_count({i-w, i-w+1, i+1, i+w, i+w+1});
        }
        else if (game.right_row.find(i) != game.right_row.end())
        {
            val = game.get_mine_count({i-w, i-w-1, i-1, i+w, i+w-1});
        }
        else if (game.top_row.find(i) != game.top_row.end())
        {
            val = game.get_mine_count({i-1, i+1, i+w, i+w-1, i+w+1});
        }
        else if (game.bottom_row.find(i) != game.bottom_row.end())
        {
            val = game.get_mine_count({i-1, i+1, i-w, i-w-1, i-w+1});
        }
        else if (game.corners.find(i) != game.corners.end())
        {
            if (i == 0)
            {
                val = game.get_mine_count({i+1, i+w, i+w+1});
            }
            else if (i == w-1)
            {
                val = game.get_mine_count({i-1, i+w-1, i+w});
            }
            else if (i == w*h-w)
            {
                val = game.get_mine_count({i-w, i-w+1, i+1});
            }
            else
            {
                val = game.get_mine_count({i-w, i-w-1, i-1});
            }
        }
        else
        {
            val = game.get_mine_count({i-w-1, i-w, i-w+1, i-1, i+1, i+w-1, i+w, i+w+1});
        }
        game.get_board()[i]->set_value(val);
    }
    return game;
}

void MinesweeperGame::exit()
{
    for (int i = 0; i < size.area(); i++)
    {
        delete board[i];
    }
}

void MinesweeperGame::mark_tile(int row, int column)
{
    int w = size.width, h = size.height;
    if (row < 0 || column < 0 || row >= h || column >= w)
    {
        return;
    }
    if (board[w*row+column]->is_swept())
    {
        return;
    }
    board[w*row+column]->mark();
}

bool MinesweeperGame::click(int row, int column)
{
    int w = size.width, h = size.height;
    if (row < 0 || column < 0 || row >= h || column >= w)
    {
        return false;
    }
    if (board[w*row+column]->get_value() == 0)
    {
        std::queue<IndexedTile> tile_queue;
        tile_queue.push({board[w*row+column], w*row+column});
        while (!tile_queue.empty())
        {
            IndexedTile itile = tile_queue.front();
            tile_queue.pop();
            Tile *temp_t = itile.tile;
            if (!temp_t->is_swept())
            {
                temp_t->sweep();
                unsafe_tiles--;
            }
            if (unsafe_tiles == 0)
            {
                game_over = true;
            }
            if (temp_t->get_value() != 0)
            {
                continue;
            }
            int i = itile.index;
            if (left_row.find(i) != left_row.end())
            {
                add_adjacent(tile_queue, {i-w, i-w+1, i+1, i+w, i+w+1});
            }
            else if (right_row.find(i) != right_row.end())
            {
                add_adjacent(tile_queue, {i-w, i-w-1, i-1, i+w, i+w-1});
            }
            else if (top_row.find(i) != top_row.end())
            {
                add_adjacent(tile_queue, {i-1, i+1, i+w, i+w-1, i+w+1});
            }
            else if (bottom_row.find(i) != bottom_row.end())
            {
                add_adjacent(tile_queue, {i-1, i+1, i-w, i-w-1, i-w+1});
            }
            else if (corners.find(i) != corners.end())
            {
                if (i == 0)
                {
                    add_adjacent(tile_queue, {i+1, i+w, i+w+1});
                }
                else if (i == w-1)
                {
                    add_adjacent(tile_queue, {i-1, i+w-1, i+w});
                }
                else if (i == w*h-w)
                {
                    add_adjacent(tile_queue, {i-w, i-w+1, i+1});
                }
                else
                {
                    add_adjacent(tile_queue, {i-w, i-w-1, i-1});
                }
            }
            else
            {
                add_adjacent(tile_queue, {i-w-1, i-w, i-w+1, i-1, i+1, i+w-1, i+w, i+w+1});
            }
        }
    }
    else
    {
        int safe = board[w*row+column]->sweep();
        unsafe_tiles--;
        if (!safe || unsafe_tiles == 0)
        {
            game_over = true;
        }
    }
    return true;
}
