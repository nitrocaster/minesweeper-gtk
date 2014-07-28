#ifndef TILE_HPP
#define TILE_HPP

class Tile
{
private:
    int  value;
    bool marked;
    bool swept;

public:
    Tile();
    Tile(int value);
    int  get_value();
    bool is_marked();
    bool is_swept();
    void set_value(int value);
    void set_marked(bool state);
    // sets swept to mined == marked and returns its value
    bool sweep();
};

#endif
