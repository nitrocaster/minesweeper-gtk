#include <string>
#include "GameWindow.hpp"
#include "MineToggleButton.hpp"

GameWindow::GameWindow(GameDifficulty difficulty) :
    game(NoInit::Dummy)
{
    initialized = false;
    initialize(difficulty);
    set_border_width(25);
    table.attach(grid, 0, 1, 0, 1, Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);
    add(table);
    table.show();
    grid.show();
    set_title("Minesweeper");
    property_resizable() = false;
}

GameWindow::~GameWindow()
{
    destroy();
}

void GameWindow::reset(GameDifficulty difficulty)
{
    destroy();
    initialize(difficulty);
}

void GameWindow::initialize(GameDifficulty difficulty)
{
    game.initialize(difficulty);
    game.set_window(*this);
    Size sz = game.get_size();
    tiles.reserve(sz.area());
    for (int i = 0; i < sz.height; i++)
    {
        for (int j = 0; j < sz.width; j++)
        {
            auto btn = new MineToggleButton();
            btn->set_row(i);
            btn->set_column(j);
            btn->set_game(&game);
            btn->set_tiles(&tiles);
            tiles.push_back(btn);
        }
    }
    for (int i = 0; i < sz.height; i++)
    {
        for (int j = 0; j < sz.width; j++)
        {
            int v = game.get_board()[sz.width*i+j]->get_value();
            auto img = new Gtk::Image("res/0.png");
            tiles[sz.width*i+j]->set_image(*img);
            img->show();
            grid.attach(*tiles[sz.width*i+j], j, j+1, i, i+1);
            tiles[sz.width*i+j]->show();
        }
    }
    initialized = true;
}

void GameWindow::destroy()
{
    if (!initialized)
    {
        return;
    }
    for (auto tile : tiles)
    {
        grid.remove(*tile);
        delete tile->get_image();
        delete tile;
    }
    tiles.clear();
    initialized = false;
}
