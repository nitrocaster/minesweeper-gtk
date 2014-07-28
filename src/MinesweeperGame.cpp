#include <random>
#include "MinesweeperGame.hpp"

struct GameParams
{
    Size size;
    int mine_count;
    GameDifficulty difficulty;

    GameParams(Size size, int mine_count)
    {
        this->size = size;
        this->mine_count = mine_count;
        std::pair<Size, int> key = std::make_pair(size, mine_count);
        static std::pair<Size, int> param_index[] =
        {
            {{ 9,  9}, 10},
            {{16, 16}, 40},
            {{30, 16}, 99}
        };
        static GameDifficulty diff_index[] =
        {
            GameDifficulty::Easy,
            GameDifficulty::Normal,
            GameDifficulty::Hard
        };
        for (size_t i = 0; i < countof(param_index); i++)
        {
            if (key == param_index[i])
            {
                difficulty = diff_index[i];
                return;
            }
        }
        this->difficulty = GameDifficulty::Custom;
    }

    GameParams(GameDifficulty difficulty)
    {
        this->difficulty = difficulty;
        switch (difficulty)
        {
            default:
            case GameDifficulty::Easy:
                size = {9, 9};
				mine_count = 10;
                break;

            case GameDifficulty::Normal:
                size = {16, 16};
				mine_count = 40;
                break;

            case GameDifficulty::Hard:
                size = {30, 16};
				mine_count = 99;
                break;
        }
    }
};

MinesweeperGame::MinesweeperGame(NoInit)
{
    initialized = false;
}

MinesweeperGame::MinesweeperGame(GameDifficulty difficulty)
{
    initialized = false;
    initialize(difficulty);
}

MinesweeperGame::~MinesweeperGame()
{
    destroy();
}

void MinesweeperGame::initialize(GameDifficulty difficulty)
{
    GameParams params(difficulty);
    int mine_count = params.mine_count;
    destroy();
    auto &game = *this;
    int w = params.size.width, h = params.size.height;
    int a = params.size.area();
    game.board.resize(a);
    game.difficulty   = difficulty;
    game.size         = params.size;
    game.mined_tiles  = mine_count;
    game.unsafe_tiles = a-mine_count;
    game.game_over    = false;
    for (int i = 0; i < a; i++)
    {
        game.board[i] = new Tile();
    }
    game.corners.emplace(0);
    game.corners.emplace(a-1);
    game.corners.emplace(w-1);
    game.corners.emplace(a-w);
    for (int i = 1; i < size.width - 1; i++)
    {
        game.top_row.emplace(i);
    }
    for (int i = w; i < a-w; i += w)
    {
        game.left_row.emplace(i);
    }
    for (int i = w*2-1; i < a-1; i += w)
    {
        game.right_row.emplace(i);
    }
    for (int i = a-w+1; i < a-1; i++)
    {
        game.bottom_row.emplace(i);
    }
    std::vector<int> positions(a);
    for (int i = 0; i < a; i++)
    {
        positions[i] = i;
    }
    std::random_device rd;
    std::default_random_engine rd_engine(rd());
    int last = a-1;
    for (int i = mine_count; i > 0; i--)
    {
        std::uniform_int_distribution<int> distribution(0, last);
        int r_index = distribution(rd_engine);
        int r_value = positions[r_index];
        game.get_board()[r_value]->set_value(-1);
		// shrink sampling range to exclude position duplicates
        std::swap(positions[r_index], positions[last--]);
    }
	// calculate unsafe tile values
    for (int i = 0; i < a; i++)
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
    initialized = true;
}

void MinesweeperGame::destroy()
{
    if (!initialized)
    {
        return;
    }
    for (auto &tile : board)
    {
        delete tile;
        tile = nullptr;
    }
    initialized = false;
}

Size MinesweeperGame::get_size() const
{
    return size;
}

std::vector<Tile*> &MinesweeperGame::get_board()
{
    return board;
}

int MinesweeperGame::get_mined_tile_count() const
{
    return mined_tiles;
}

int MinesweeperGame::get_unsafe_tile_count() const
{
    return unsafe_tiles;
}

bool MinesweeperGame::is_over() const
{
    return game_over;
}

GameDifficulty MinesweeperGame::get_game_difficulty() const
{
    return difficulty;
}

GameWindow* MinesweeperGame::get_window()
{
    return window;
}

void MinesweeperGame::set_window(GameWindow& window)
{
    this->window = &window;
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
        if (board[loc]->is_swept() || board[loc]->is_marked())
        {
            continue;
        }
        q.push({board[loc], loc});
    }
}

void MinesweeperGame::mark_tile(int row, int column)
{
	int w = size.width, h = size.height;
    if (row < 0 || column < 0 || row >= h || column >= w)
    {
        return;
    }
    auto tile = board[w*row+column];
    if (tile->is_swept())
    {
        return;
    }
    tile->set_marked(!tile->get_value());
}

bool MinesweeperGame::sweep_tile(int row, int column)
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
            if (temp_t->is_marked())
            {
                continue;
            }
            if (!temp_t->is_swept())
            {
                temp_t->sweep();
                unsafe_tiles--;
            }
            if (unsafe_tiles == 0)
            {
                // all safe tiles swept => win
                game_over = true;
            }
            if (temp_t->get_value() != 0)
            {
                continue;
            }
            int i = itile.index;
            // tile position: 9 cases (4 sides + 4 corners + internal)
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
    else // try to sweep nonzero tile
    {
        bool safe = board[w*row+column]->sweep();
        unsafe_tiles--;
        if (!safe || unsafe_tiles == 0)
        {
            game_over = true;
        }
    }
    return true;
}
