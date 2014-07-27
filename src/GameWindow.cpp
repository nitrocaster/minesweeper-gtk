#include <string>
#include "GameWindow.hpp"
#include "MineToggleButton.hpp"

GameWindow::GameWindow(GameDifficulty difficulty)
{
    game = MinesweeperGame::initialize(difficulty);
    int w = game.get_width(), h = game.get_height();
    int a = w*h;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            auto btn = new MineToggleButton();
            btn->set_row(i);
            btn->set_column(j);
            btn->set_game(&game);
            btn->set_tiles(&tiles);
            tiles.push_back(btn);
        }
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int v = game.get_board()[w*i+j]->get_value();
            auto img = new Gtk::Image("res/0.png");
            tiles[w*i+j]->set_image(*img);
            img->show();
            grid.attach(*tiles[w*i+j], j, j+1, i, i+1);
            tiles[w*i+j]->show();
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
    for (int i = 0; i < game.get_width() * game.get_height(); i++)
    {
        delete tiles[i]->get_image();
        delete tiles[i];
    }
}
