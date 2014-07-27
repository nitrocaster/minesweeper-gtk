#include <string>
#include "GameWindow.hpp"
#include "MineToggleButton.hpp"

GameWindow::GameWindow(GameDifficulty difficulty)
{
  game = MinesweeperGame::init(difficulty);
  int w = game.getWidth();
  int h = game.getHeight();
  int a = w*h;

  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < w; j++)
    {
      MineToggleButton* temp = new MineToggleButton();
      temp->setRow(i);
      temp->setCol(j);
      temp->setGame(&game);
      temp->setTiles(&b_tiles);
      temp->signal_clicked().connect(sigc::mem_fun(*this, &GameWindow::on_button_clicked));
      b_tiles.push_back(temp);
    }
  }
  set_border_width(25);
  
  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < w; j++)
    {
      int v = game.getBoard().at(w*i+j)->getValue();
      Gtk::Image* temp = new Gtk::Image("res/0.png");
      b_tiles.at(w*i+j)->set_image(*temp);
      (temp)->show();
      grid.attach(*b_tiles.at(w*i+j), j, j+1, i, i+1);
      b_tiles.at(w*i+j)->show();
    }
  }

  container.attach(grid, 0, 1, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::SHRINK);
  
  add(container);
  container.show();
  grid.show();
  set_title("Minesweeper");
}

GameWindow::~GameWindow()
{
  for(int i = 0 ; i < game.getWidth()*game.getHeight(); i++)
  {
    delete b_tiles.at(i)->get_image();
    delete b_tiles.at(i);
  }
}
