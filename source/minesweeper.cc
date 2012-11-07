#include "minesweeper.h"
#include <random>
#include <iostream>
#include <unordered_set>


MinesweeperGame::MinesweeperGame(int w, int h) :
width(w), height(h), board(w*h)
{
	for(int i = 0 ; i < w*h; i++)
		board.at(i) = new Tile();
}

int MinesweeperGame::getHeight()
{
	return height;
}
int MinesweeperGame::getWidth()
{
	return width;
}

void MinesweeperGame::swap(std::vector<int>& a, int i, int j)
{
	int temp = a.at(i);
	a.at(i) = a.at(j);
	a.at(j) = temp;
}

std::vector<Tile*> MinesweeperGame::getBoard()
{
	return board;
}

void MinesweeperGame::printBoard()
{
	int b_count = 0;
	for(int i = 0 ; i < width+2; i++)
		std::cout << "#" ;
	std::cout << std::endl;
	for(int i = 0; i < height; i++)
	{
		std::cout << "#";
		for(int j = 0 ; j < width; j++)
		{
			int v = board.at(height*i+j)->getValue();
			char c = v == BOMB ? 'B' : v;
			if(v == BOMB)
				b_count++;
			if(v == 0) c = ' ';
			std::cout << c;
		}
		std::cout << "#" << std::endl;
	}
	for(int i = 0 ; i < width+2; i++)
		std::cout << "#" ;
	std::cout << std::endl;
	std::cout << "bomb count: " << b_count << std::endl;

}

MinesweeperGame MinesweeperGame::init(int diff)
{
	int w = 0, h = 0, m = 0;
	switch(diff)
	{
		case EASY:
			w = 9; h = 9; m = 10;
		break;
		
		case HARD:
			w = 30; h = 16; m = 40;
		break;

		default:
		case NORMAL:
			w = 16; h = 16; m = 99;
	}
	MinesweeperGame game(w,h);

	std::vector<int> positions(w*h);
	for(int i = 0 ; i < w*h ; i++)
		positions.at(i) = i;
	std::random_device rd;
	std::default_random_engine generator(rd());
	int last = w*h - 1;
	for(int i = m; i > 0; i--)
	{
		std::uniform_int_distribution<int> distribution(0,last);
		int r_index = distribution(generator);
		int r_value = positions.at(r_index);
		game.getBoard().at(r_value)->setValue(BOMB);
		swap(positions, r_index, last--);
		// int temp = positions.at(r_index);
		// positions.at(r_index) = positions.at(last);
		// positions.at(last) = temp;
		// last--;
	}

	std::unordered_set<int> corners;
	corners.emplace(0);
	corners.emplace(w*h-1);
	corners.emplace(w-1);
	corners.emplace(w*h-w);

	std::cout << "corners\n\t";
	std::cout << 0 << " " << w*h-1 << " " << w-1 << " " << w*h-w << std::endl;

	std::unordered_set<int> top_row;
	std::cout << "top_row\n\t";
	for(int i = 1; i < w-1; i++)
	{
		top_row.emplace(i);
		std::cout << i << " " ;
	}
	std::cout << std::endl;


	std::unordered_set<int> left_row;
	std::cout << "left_row\n\t";
	for(int i = w; i < w*h-w; i += h)
	{
		left_row.emplace(i);
		std::cout << i << " " ;
	}
	std::cout << std::endl ;

	std::unordered_set<int> right_row;
	std::cout << "right_row\n\t";
	for(int i = w*2 - 1; i < w*h-1; i+= h)
	{
		right_row.emplace(i);
		std::cout << i << " " ;
	}
	std::cout << std::endl;

	std::unordered_set<int> bottom_row;
	std::cout << "bottom_row\n\t";
	for(int i = w*h-w+1; i < w*h-1; i++)
	{
		bottom_row.emplace(i);
		std::cout << i << " " ;			
	}
	std::cout << std::endl;
		
	return game;

}





