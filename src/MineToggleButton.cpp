#include <string>
#include "MineToggleButton.hpp"

bool MineToggleButton::on_button_press_event(GdkEventButton *event)
{
    return true;
}

bool MineToggleButton::on_button_release_event(GdkEventButton *event)
{
    if (get_active())
    {
        return true;
    }
    if (event->button == 3)
    {
        // RMB click => toggle flag
        delete get_image();
        auto img = new Gtk::Image(marked ? "res/0.png" : "res/flag.png");
        set_image(*img);
        img->show();
        marked = !marked;
        return true;
    }
    if (event->button == 1 && marked)
    {
        // LMB click on flagged tile => ignore
        return true;
    }
    set_active(true);
    delete get_image();
    marked = game->click(row, column);
    Size sz = game->get_size();
    int val = game->get_board()[sz.width*row+column]->get_value();
    std::string img_path;
    if (val < 0)
    {
        img_path = "res/mine_e.png";
    }
    else
    {
        std::ostringstream convert;
        convert << val;
        img_path = "res/" + convert.str() + ".png";
    }
    auto img = new Gtk::Image(img_path);
    set_image(*img);
    img->show();
    // update all the rest of tiles
    for (int i = 0; i < sz.height; i++)
    {
        for (int j = 0; j < sz.width; j++)
        {
            int loc = sz.width*i+j;
            if (tiles->at(loc) == this)
            {
                continue;
            }
            Tile *board_tile = game->get_board()[loc];
            if (game->is_over() || (!board_tile->is_marked() &&
                board_tile->is_swept() && !tiles->at(loc)->get_active()))
            {
                if (!game->is_over())
                {
                    tiles->at(loc)->set_active(true);
                }
                delete tiles->at(loc)->get_image();
                val = board_tile->get_value();
                if (val < 0)
                {
                    img_path = "res/mine.png";
                }
                else
                {
                    std::ostringstream convert;
                    convert << val;
                    img_path = "res/" + convert.str() + ".png";
                }
                img = new Gtk::Image(img_path);
                tiles->at(loc)->set_image(*img);
                img->show();
            }
        }
    }
    if (game->is_over())
    {
        std::string msg = game->get_unsafe_tile_count() == 0 ? "You win!" : "You lose.";
        Gtk::MessageDialog dialog(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        dialog.run();
        Gtk::Main::quit();
    }
}
