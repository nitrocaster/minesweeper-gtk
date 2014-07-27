#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include <vector>
#include "Tile.hpp"
#include "MinesweeperGame.hpp"
#include "MineToggleButton.hpp"

class GameWindow : public Gtk::Window
{
public:
    GameWindow(GameDifficulty difficulty);
    virtual ~GameWindow();

protected:
    int width;
    int height;
    MinesweeperGame game;
    std::vector<MineToggleButton*> tiles;

    Gtk::Table grid;
    Gtk::Table container;
};

#endif
