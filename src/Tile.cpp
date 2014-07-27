#include "Tile.hpp"

Tile::Tile(int val) :
    value(val), marked(false), swept(false)
{
}

Tile::Tile() :
    value(0), marked(false), swept(false)
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

void Tile::mark()
{
	marked = !marked;
}

void Tile::set_value(int value)
{
	this->value = value;
}

bool Tile::sweep()
{
	swept = true;
	return value >= 0;
}
