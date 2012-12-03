#include "minegui.h"
#include <iostream>
#include <gtkmm/main.h>

void usage()
{
  std::cout << "usage: ./main -l {1, 2, 3} (1=easy, 2=normal, 3=hard)" << std::endl;
  exit(1);
}

int main (int argc, char *argv[])
{
  /*
  if(argc != 3)
    usage();
  int diff = 0;
  if(std::string(argv[1]) == "-l")
    diff = atoi(argv[2]);		
  else
    usage();
  */
  Gtk::Main kit(argc, argv);
  MineGui mgui (1);
  Gtk::Main::run(mgui);
  return 0;
}

