#ifndef MINE_BUTTON
#define MINE_BUTTON

#include "gtkmm/togglebutton.h"
#include "gtkmm.h"
#include "MinesweeperGame.hpp"

#include <vector>

class MineToggleButton : public Gtk::ToggleButton
{
  private:
    int row;
    int col;
    MinesweeperGame *game;
    std::vector<MineToggleButton*> * tiles;
    int clickFlag = 0;
  public:
    void setRow(int r) { row = r; }
    void setCol(int c) { col = c; }
    void setGame(MinesweeperGame *g) { game = g; }
    void setTiles(std::vector<MineToggleButton*> *t) { tiles = t; }
    int getRow() { return row; }
    int getCol() { return col; }
    int click() { return clickFlag; }
    MinesweeperGame *getGame() { return game; }
    
    virtual bool on_button_press_event(GdkEventButton *event);
    virtual bool on_button_release_event(GdkEventButton *event);
};

#endif



