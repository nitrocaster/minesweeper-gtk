#ifndef TILE_HPP
#define TILE_HPP

class Tile
{
private:
	int value;
	bool marked;
	bool swept;

public:
	Tile(int value);
	Tile();

	int get_value();
	bool is_marked();
	bool is_swept();
	void set_value(int value);
	void mark();
	bool sweep();
};

#endif
