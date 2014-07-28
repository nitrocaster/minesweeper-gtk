#include <string>
#include "GameWindow.hpp"
#include "MineToggleButton.hpp"

GameWindow::GameWindow(GameDifficulty difficulty)
{
    game = MinesweeperGame::initialize(difficulty);
    Size sz = game.get_size();
    int a = sz.area();
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
    set_border_width(25);
    container.attach(grid, 0, 1, 0, 1, Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);
    add(container);
    container.show();
    grid.show();
    set_title("Minesweeper");
}

GameWindow::~GameWindow()
{
    int tile_count = game.get_size().area();
    for (int i = 0; i < tile_count; i++)
    {
        delete tiles[i]->get_image();
        delete tiles[i];
    }
}
