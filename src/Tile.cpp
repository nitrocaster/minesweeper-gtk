#include "Tile.hpp"

Tile::Tile() :
    value(0), marked(false), swept(false)
{
}

Tile::Tile(int value) :
    value(value), marked(false), swept(false)
{
}

int Tile::get_value()
{
    return value;
}

bool Tile::is_marked()
{
    return marked;
}

bool Tile::is_swept()
{
    return swept;
}

void Tile::set_marked(bool state)
{
    marked = state;
    sweep();
}

void Tile::set_value(int value)
{
    this->value = value;
}

bool Tile::sweep()
{
    swept = value < 0 == marked;
    return swept;
}
