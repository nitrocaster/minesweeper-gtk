#include "GameWindow.hpp"
#include <iostream>
#include <gtkmm/main.h>

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);
  GameWindow mgui (1);
  Gtk::Main::run(mgui);
  return 0;
}
