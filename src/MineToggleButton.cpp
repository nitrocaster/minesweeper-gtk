#include <iostream>
#include <string>
#include <sstream>
#include "MineToggleButton.hpp"

bool MineToggleButton::on_button_press_event(GdkEventButton *event)
{
}

bool MineToggleButton::on_button_release_event(GdkEventButton *event)
{
  if(this->get_active())
    return true;
  if(event->button == 3)
  {
    delete this->get_image();
    Gtk::Image* temp = clickFlag ? new Gtk::Image("res/0.png") : new Gtk::Image("res/flag.png");
    this->set_image(*temp);
    temp->show();
    clickFlag = ~clickFlag;
    return true;
  }
  if(event->button == 1 && clickFlag)
    return true;
  this->set_active(1);
  delete this->get_image();
  clickFlag = game->click(row,col);
  int i = row;
  int j = col;
  int w = game->getWidth();
  int h = game->getHeight();
  int v = game->getBoard().at(w*i+j)->getValue();
  Gtk::Image* temp;
  if(v == BOMB)
    temp = new Gtk::Image("res/mine.png");
  else
  {
    std::string image_path;
    std::ostringstream convert;
    convert << v;
  image_path = "res/" + convert.str() + ".png";
    temp = new Gtk::Image(image_path);
  }
  this->set_image(*temp);
  (temp)->show();
  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < w; j++)
    {
      int loc = w*i+j;
      if(game->getBoard().at(loc)->isClicked())
      {
        if(!tiles->at(loc)->get_active())
        {
          tiles->at(loc)->set_active(1);
          delete tiles->at(loc)->get_image();
          v = game->getBoard().at(loc)->getValue();
          if(v == BOMB)
            temp = new Gtk::Image("res/mine.png");
          else
          {
            std::string image_path;
            std::ostringstream convert;
            convert << v;
            image_path = "res/" + convert.str() + ".png";
            temp = new Gtk::Image(image_path);
          }
          tiles->at(loc)->set_image(*temp);
          (temp)->show();
        }
      }
    }
  }
  if(!game->isLive())
  {
    std::string msg = game->getNumOpen() ? "You lose =(" : "You win!";
    Gtk::MessageDialog dialog(msg, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_NONE);
    dialog.run();
    Gtk::Main::quit();
  }
}
