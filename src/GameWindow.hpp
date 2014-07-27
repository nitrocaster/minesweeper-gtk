#ifndef MINE_GUI_H
#define MINE_GUI_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

#include "Tile.hpp"
#include "MinesweeperGame.hpp"
#include "MineToggleButton.hpp"
#include <vector>

typedef Gtk::Button Button;
typedef Gtk::ToggleButton ToggleButton;

class GameWindow : public Gtk::Window
{

public:
  GameWindow(int);
  virtual ~GameWindow();

protected:
  int width;
  int height;
  MinesweeperGame game;
  std::vector<MineToggleButton*> b_tiles;
  //Signal handlers:
  void on_button_clicked();
  
  //Member widgets:
  Gtk::Table grid;
  Gtk::Table container;
  
};

#endif 


