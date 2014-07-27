#ifndef TILE_H
#define TILE_H

#define BOMB -1

class Tile
{
private:
	int value;
	bool marked;
	bool clicked;

public:
	Tile(int val);
	Tile();

	int getValue();
	bool isMarked();
	bool isClicked();
	void setValue(int v);
	void mark();
	int click();
};

#endif
