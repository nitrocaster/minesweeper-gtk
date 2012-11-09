#include "minesweeper.h"
#include "tile.h"

#include <iostream>
#include <cassert>
#include <random>
#include <string>
#include <sstream>

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
	for(int i = 0 ; i < 10; i++ )
	{
		int dice_roll = distribution(generator);
		std::cout << dice_roll << " " ;
	}
	std::cout << std::endl;
}

void usage()
{
	std::cout << "usage: ./main {EASY, NORMAL, HARD}" << std::endl;
	exit(1);
}

using std::cout; using std::endl;

void playGame(MinesweeperGame& game)
{
	std::string s ;
	int r = 0, c = 0;
	while(game.isLive())
	{
		game.printGameBoard();
		cout << "Enter row: ";
		getline(std::cin, s);
		if(s == "exit") break;
		std::stringstream(s) >> r;
		cout << "Enter column: ";
		getline(std::cin, s);
		if(s == "exit") break;
		std::stringstream(s) >> c;
		int ok = game.click(r, c);
		if(!ok)
			printf("(%d, %d) is not a valid point.\n", r, c);




	}
	std::cout << "Thanks for playing!" << std::endl;
	game.exit();
}

int main(int argc, char* argv[])
{
	if(argc != 3)
		usage();
	int diff = 0;
	if(std::string(argv[1]) == "-l")
		diff = atoi(argv[2]);
	else
		usage();
	std::cout << "Welcome to Minesweeper! (exit) to quit the game" << std::endl;
	MinesweeperGame game = MinesweeperGame::init(diff);
	// game.printTrueBoard();
	// game.printGameBoard();
	// game.exit();
	playGame(game);
	return 1;
}



