#include <gtkmm/main.h>
#include "GameWindow.hpp"

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);
    GameWindow window(GameDifficulty::Easy);
    Gtk::Main::run(window);
    return 0;
}
