#ifndef MINE_TOGGLE_BUTTON_HPP
#define MINE_TOGGLE_BUTTON_HPP

#include "gtkmm.h"
#include "gtkmm/togglebutton.h"
#include <vector>
#include "MinesweeperGame.hpp"

class MineToggleButton: public Gtk::ToggleButton
{
private:
    int row;
    int column;
    MinesweeperGame *game;
    std::vector<MineToggleButton*> *tiles;

public:
    void set_row(int row)
    {
        this->row = row;
    }

    void set_column(int column)
    {
        this->column = column;
    }

    void set_game(MinesweeperGame *game)
    {
        this->game = game;
    }

    void set_tiles(std::vector<MineToggleButton*> *tiles)
    {
        this->tiles = tiles;
    }

    int get_row()
    {
        return row;
    }

    int get_column()
    {
        return column;
    }

    bool is_swept()
    {
        return game->get_board()[game->get_size().width*row+column]->is_swept();
    }

    void sweep()
    {
        game->get_board()[game->get_size().width*row+column]->sweep();
    }

    MinesweeperGame *get_game()
    {
        return game;
    }

    // Gtk::Widget
    virtual bool on_button_press_event(GdkEventButton *event) override;
    virtual bool on_button_release_event(GdkEventButton *event) override;
    // ~Gtk::Widget
};

#endif
