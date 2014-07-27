#include "GameWindow.hpp"
#include <gtkmm/main.h>

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);
  GameWindow mgui (GameDifficulty::Easy);
  Gtk::Main::run(mgui);
  return 0;
}
