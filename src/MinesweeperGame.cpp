#include <random>
#include <algorithm>
#include <array>
#include <string>
#include <cstdarg>
#include "MinesweeperGame.hpp"

MinesweeperGame::MinesweeperGame()
{
}

MinesweeperGame::MinesweeperGame(int w, int h, int m)
{
    width = w;
    height = h;
    mined_tiles = m;
    time_remaining = 0;
    game_over = false;
    unsafe_tiles = w*h-m;
    board.resize(w*h);
    for (int i = 0; i < w*h; i++)
    {
        board[i] = new Tile();
    }
    corners.emplace(0);
    corners.emplace(w*h-1);
    corners.emplace(w-1);
    corners.emplace(w*h-w);
    for (int i = 1; i < w-1; i++)
    {
        top_row.emplace(i);
    }
    for (int i = w; i < w*h-w; i += w)
    {
        left_row.emplace(i);
    }
    for (int i = w*2-1; i < w*h-1; i += w)
    {
        right_row.emplace(i);
    }
    for (int i = w*h-w+1; i < w*h-1; i++)
    {
        bottom_row.emplace(i);
    }
}

int MinesweeperGame::get_height()
{
    return height;
}

int MinesweeperGame::get_width()
{
    return width;
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

int MinesweeperGame::get_mine_count(MinesweeperGame& game, int num, ...)
{
    std::vector<int> t(num);
    va_list arguments;
    va_start(arguments, num);
    for (int i = 0; i < num; i++)
    {
        t[i] = game.get_board()[va_arg(arguments, int)]->get_value();
    }
	va_end(arguments);
    return (int)std::count_if(t.begin(), t.end(), [](int val){ return val < 0; });
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
            val = get_mine_count(game, 5, i-w, i-w+1, i+1, i+w, i+w+1);
        }
        else if (game.right_row.find(i) != game.right_row.end())
        {
            val = get_mine_count(game, 5, i-w, i-w-1, i-1, i+w, i+w-1);
        }
        else if (game.top_row.find(i) != game.top_row.end())
        {
            val = get_mine_count(game, 5, i-1, i+1, i+w, i+w-1, i+w+1);
        }
        else if (game.bottom_row.find(i) != game.bottom_row.end())
        {
            val = get_mine_count(game, 5, i-1, i+1, i-w, i-w-1, i-w+1);
        }
        else if (game.corners.find(i) != game.corners.end())
        {
            if (i == 0)
            {
                val = get_mine_count(game, 3, i+1, i+w, i+w+1);
            }
            else if (i == w-1)
            {
                val = get_mine_count(game, 3, i-1, i+w-1, i+w);
            }
            else if (i == w*h-w)
            {
                val = get_mine_count(game, 3, i-w, i-w+1, i+1);
            }
            else
            {
                val = get_mine_count(game, 3, i-w, i-w-1, i-1);
            }
        }
        else
        {
            val = get_mine_count(game, 8, i-w-1, i-w, i-w+1, i-1, i+1, i+w-1, i+w, i+w+1);
        }
        game.get_board()[i]->set_value(val);
    }
    return game;
}

void MinesweeperGame::exit()
{
    for (int i = 0; i < width*height; i++)
    {
        delete board[i];
    }
}

void MinesweeperGame::add_adjacent(std::queue<IndexedTile>& q, int num, ...)
{
    va_list arguments;
    va_start(arguments, num);
    for (int i = 0; i < num; i++)
    {
        int index = va_arg(arguments, int);
        if (board[index]->is_swept())
        {
            continue;
        }
        q.push({board[index], index});
    }
    va_end(arguments);
}

void MinesweeperGame::mark_tile(int r, int c)
{
    if (r < 0 || c < 0 || r >= height || c >= width)
    {
        return;
    }
    if (board[width*r+c]->is_swept())
    {
        return;
    }
    board[width*r+c]->mark();
}

bool MinesweeperGame::click(int r, int c)
{
    if (r < 0 || c < 0 || r >= height || c >= width)
    {
        return false;
    }
    if (board[width*r+c]->get_value() == 0)
    {
        std::queue<IndexedTile> tile_queue;
        tile_queue.push({board[width*r+c], width*r+c});
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
            int w = width, h = height;
            if (left_row.find(i) != left_row.end())
            {
                add_adjacent(tile_queue, 5, i-w, i-w+1, i+1, i+w, i+w+1);
            }
            else if (right_row.find(i) != right_row.end())
            {
                add_adjacent(tile_queue, 5, i-w, i-w-1, i-1, i+w, i+w-1);
            }
            else if (top_row.find(i) != top_row.end())
            {
                add_adjacent(tile_queue, 5, i-1, i+1, i+w, i+w-1, i+w+1);
            }
            else if (bottom_row.find(i) != bottom_row.end())
            {
                add_adjacent(tile_queue, 5, i-1, i+1, i-w, i-w-1, i-w+1);
            }
            else if (corners.find(i) != corners.end())
            {
                if (i == 0)
                {
                    add_adjacent(tile_queue, 3, i+1, i+w, i+w+1);
                }
                else if (i == w-1)
                {
                    add_adjacent(tile_queue, 3, i-1, i+w-1, i+w);
                }
                else if (i == w*h-w)
                {
                    add_adjacent(tile_queue, 3, i-w, i-w+1, i+1);
                }
                else
                {
                    add_adjacent(tile_queue, 3, i-w, i-w-1, i-1);
                }
            }
            else
            {
                add_adjacent(tile_queue, 8, i-w-1, i-w, i-w+1, i-1, i+1, i+w-1, i+w, i+w+1);
            }
        }
    }
    else
    {
        int safe = board[width*r+c]->sweep();
        unsafe_tiles--;
        if (!safe || unsafe_tiles == 0)
        {
            game_over = true;
        }
    }
    return true;
}
