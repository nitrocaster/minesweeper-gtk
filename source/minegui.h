#ifndef MINE_GUI_H
#define MINE_GUI_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

#include "tile.h"
#include "minesweeper.h"
#include "MineToggleButton.h"
#include <vector>

typedef Gtk::Button Button;
typedef Gtk::ToggleButton ToggleButton;

class MineGui : public Gtk::Window
{

public:
  MineGui(int);
  virtual ~MineGui();

protected:
  int width;
  int height;
  //Signal handlers:
  void on_button_clicked();

  MinesweeperGame game;//(int,int,int);

  //Member widgets:
  std::vector<MineToggleButton*> b_tiles;
  Gtk::Table grid;
  Gtk::Table container;
  
};

#endif 


