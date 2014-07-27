#include "minegui.h"
#include <iostream>
#include <gtkmm/main.h>

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);
  MineGui mgui (1);
  Gtk::Main::run(mgui);
  return 0;
}
