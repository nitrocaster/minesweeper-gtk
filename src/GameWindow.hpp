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
private:
    bool initialized = false;
    Size size;
    MinesweeperGame game;
    std::vector<MineToggleButton*> tiles;
    Gtk::Table grid;
    Gtk::Table table;

public:
    GameWindow(GameDifficulty difficulty);
    virtual ~GameWindow();
    void reset(GameDifficulty difficulty);

private:
    void initialize(GameDifficulty difficulty);
    void destroy();
};

#endif
