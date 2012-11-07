#include "minesweeper.h"
#include <random>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <array>

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
			if(v == BOMB)
			{
				b_count++;
				std::cout << "B";
			}
			else if(v == 0)
				std::cout << " ";
			else
				std::cout << v;
		}
		std::cout << "#" << std::endl;
	}
	for(int i = 0 ; i < width+2; i++)
		std::cout << "#" ;
	std::cout << std::endl;
	// std::cout << "bomb count: " << b_count << std::endl;

}

int MinesweeperGame::countBombs(MinesweeperGame& game, int num, ...)
{
	std::vector<int> t(num);
	va_list arguments; 
	va_start(arguments, num);
	for(int i = 0 ; i < num; i++)
		t.at(i) = game.getBoard().at(va_arg(arguments, int))->getValue();
	va_end(arguments);
	int val = (int)std::count_if(t.begin(), t.end(), [](int tt){return tt == BOMB;});
	return val;
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
	}

	std::unordered_set<int> corners;
	corners.emplace(0);
	corners.emplace(w*h-1);
	corners.emplace(w-1);
	corners.emplace(w*h-w);

	std::unordered_set<int> top_row;
	for(int i = 1; i < w-1; i++)
		top_row.emplace(i);


	std::unordered_set<int> left_row;
	for(int i = w; i < w*h-w; i += h)
		left_row.emplace(i);

	std::unordered_set<int> right_row;
	for(int i = w*2 - 1; i < w*h-1; i+= h)
		right_row.emplace(i);

	std::unordered_set<int> bottom_row;
	for(int i = w*h-w+1; i < w*h-1; i++)
		bottom_row.emplace(i);
	
	for(int i = 0 ; i < w*h; i++)
	{
		if(game.getBoard().at(i)->getValue() == BOMB)
			continue;
		if(left_row.find(i) != left_row.end())
		{
			int val = countBombs(game, 5, i-w, i-w+1, i+1, i+w, i+w+1);
			game.getBoard().at(i)->setValue(val);
		}
		else if(right_row.find(i) != right_row.end())
		{
			int val = countBombs(game, 5, i-w, i-w-1, i-1, i+w, i+w-1);
			game.getBoard().at(i)->setValue(val);
		}
		else if(top_row.find(i) != top_row.end())
		{
			int val = countBombs(game, 5, i-1, i+1, i+w, i+w-1, i+w+1);
			game.getBoard().at(i)->setValue(val);
		}
		else if(bottom_row.find(i) != bottom_row.end())
		{
			int val = countBombs(game, 5, i-1, i+1, i-w, i-w-1, i-w+1);
			game.getBoard().at(i)->setValue(val);
		}
		else if(corners.find(i) != corners.end())
		{
			int val = 0;
			if(i == 0)
				val = countBombs(game, 3, i+1, i+w, i+w+1);
			else if(i == w-1)
				val = countBombs(game, 3, i-1, i+w-1, i+w);
			else if(i == w*h-w)
				val = countBombs(game, 3, i-w, i-w+1, i+1);
			else
				val = countBombs(game, 3, i-w, i-w-1, i-1);
			game.getBoard().at(i)->setValue(val);
		}
		else
		{
			int val = countBombs(game, 8, i-w-1, i-w, i-w+1, i-1, i+1, i+w-1, i+w, i+w+1);
			game.getBoard().at(i)->setValue(val);	
		}
	}

	return game;

}





