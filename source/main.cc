#include "minesweeper.h"
#include "tile.h"

#include <iostream>
#include <cassert>
#include <random>

void tileTest()
{
	Tile t1(1);
	Tile t2(2);
	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	assert(t1.getValue() == 1);
	assert(t2.getValue() == 2);
	assert(t1.isMarked() == false);
	assert(t2.isMarked() == false);
	t1.mark();
	assert(t1.isMarked());
	t1.mark();
	assert(!t1.isMarked());
	t2.mark();
	assert(t2.isMarked());
	assert(!t1.isClicked());
	assert(t1.click());
	assert(t1.isClicked());
	assert(t2.click());
	Tile tb(BOMB);
	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	std::cout << tb << std::endl;
	assert(!tb.isClicked());
	assert(!tb.click());


}

void randTest()
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1,6);
	for(int i = 0 ; i < 100; i++ ) {
	int dice_roll = distribution(generator);
	std::cout << dice_roll << std::endl;	}
}



int main()
{
	MinesweeperGame game = MinesweeperGame::init(EASY);
	
	return 1;
}



