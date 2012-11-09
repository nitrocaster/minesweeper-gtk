#include "minesweeper.h"
#include <random>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <array>
#include <string>

int DEBUG = false;

MinesweeperGame::MinesweeperGame(int w, int h, int m) :
width(w), height(h), num_mines(m), board(w*h), time_remaining(0), live(true),
num_open(w*h)
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
int MinesweeperGame::getNumMines()
{
	return num_mines;
}
bool MinesweeperGame::isLive()
{
	return live;
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

void MinesweeperGame::printTrueBoard()
{
	std::cout << "   ";
	for(int i = 0 ; i < width ; i++)
		std::cout << (i/10);
	std::cout << std::endl;
	std::cout << "   ";
	for(int i = 0; i < width; i++)
		std::cout << (i%10);
	std::cout << std::endl;

	std::cout << "  " ;
	for(int i = 0 ; i < width+2; i++)
		std::cout << "#" ;
	std::cout << std::endl;
	for(int i = 0; i < height; i++)
	{
		if(i < 10)
			std::cout << "0";
		std::cout << i ;
		std::cout << "#";
		for(int j = 0 ; j < width; j++)
		{
			int v = board.at(width*i+j)->getValue();
			if(v == BOMB)
				std::cout << "B";
			else if(v == 0)
				std::cout << " ";
			else
				std::cout << v;
		}
		std::cout << "#" << std::endl;
	}
	std::cout << "  ";
	for(int i = 0 ; i < width+2; i++)
		std::cout << "#" ;
	std::cout << std::endl;
}

void MinesweeperGame::printGameBoard()
{
	std::cout << "   ";
	for(int i = 0 ; i < width ; i++)
		std::cout << (i/10);
	std::cout << std::endl;
	std::cout << "   ";
	for(int i = 0; i < width; i++)
		std::cout << (i%10);
	std::cout << std::endl;

	std::cout << "  " ;
	for(int i = 0 ; i < width+2; i++)
		std::cout << "#" ;
	std::cout << std::endl;
	for(int i = 0; i < height; i++)
	{
		if(i < 10)
			std::cout << "0";
		std::cout << i ;
		std::cout << "#";
		for(int j = 0 ; j < width; j++)
		{
			if(!board.at(width*i+j)->isClicked())
				std::cout << "_";
			else
			{
				int temp = board.at(width*i+j)->getValue();
				if(temp == 0)
					std::cout << " ";
				else
					std::cout << temp;
			}
				
		}
		std::cout << "#" << std::endl;
	}
	std::cout << "  ";
	for(int i = 0 ; i < width+2; i++)
		std::cout << "#" ;
	std::cout << std::endl;
}


int MinesweeperGame::countBombs(MinesweeperGame& game, int num, ...)
{
	std::vector<int> t(num);
	va_list arguments; 
	va_start(arguments, num);
	for(int i = 0 ; i < num; i++)
		t.at(i) = game.getBoard().at(va_arg(arguments, int))->getValue();
	va_end(arguments);
	return (int)std::count_if(t.begin(), t.end(), [](int tt){return tt == BOMB;});
}

void print_set(std::string s, std::unordered_set<int> set)
{
	std::cout << s << ": " ;
	for(std::unordered_set<int>::iterator iter = set.begin(); iter != set.end(); iter++)
		std::cout << (*iter) << " ";
	std::cout << std::endl;
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
			w = 30; h = 16; m = 99;
		break;

		default:
		case NORMAL:
			w = 16; h = 16; m = 40;
	}
	MinesweeperGame game(w,h,m);
	if(DEBUG)
		printf("weight: %d, height: %d, mines: %d\n", game.getWidth(), game.getHeight(), game.getNumMines());

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
	if(DEBUG)
		print_set("corners", corners);

	std::unordered_set<int> top_row;
	for(int i = 1; i < w-1; i++)
		top_row.emplace(i);
	if(DEBUG)
		print_set("top_row", top_row);

	std::unordered_set<int> left_row;
	for(int i = w; i < w*h-w; i += w)
		left_row.emplace(i);
	if(DEBUG)
		print_set("left_row", left_row);

	std::unordered_set<int> right_row;
	for(int i = w*2 - 1; i < w*h-1; i+= w)
		right_row.emplace(i);
	if(DEBUG)
		print_set("right_row", right_row);

	std::unordered_set<int> bottom_row;
	for(int i = w*h-w+1; i < w*h-1; i++)
		bottom_row.emplace(i);
	if(DEBUG)
		print_set("bottom_row", bottom_row);
	
	for(int i = 0 ; i < w*h; i++)
	{
		if(game.getBoard().at(i)->getValue() == BOMB)
			continue;
		int val = 0;
		if(left_row.find(i) != left_row.end())
			val = countBombs(game, 5, i-w, i-w+1, i+1, i+w, i+w+1);
		else if(right_row.find(i) != right_row.end())
			val = countBombs(game, 5, i-w, i-w-1, i-1, i+w, i+w-1);
		else if(top_row.find(i) != top_row.end())
			val = countBombs(game, 5, i-1, i+1, i+w, i+w-1, i+w+1);
		else if(bottom_row.find(i) != bottom_row.end())
			val = countBombs(game, 5, i-1, i+1, i-w, i-w-1, i-w+1);
		else if(corners.find(i) != corners.end())
		{
			if(i == 0)
				val = countBombs(game, 3, i+1, i+w, i+w+1);
			else if(i == w-1)
				val = countBombs(game, 3, i-1, i+w-1, i+w);
			else if(i == w*h-w)
				val = countBombs(game, 3, i-w, i-w+1, i+1);
			else
				val = countBombs(game, 3, i-w, i-w-1, i-1);
		}
		else
			val = countBombs(game, 8, i-w-1, i-w, i-w+1, i-1, i+1, i+w-1, i+w, i+w+1);
		game.getBoard().at(i)->setValue(val);
	}
	return game;

}

void MinesweeperGame::exit()
{
	for(int i = 0; i < width*height; i++)
		delete board.at(i);
}

int MinesweeperGame::click(int r, int c)
{
	if(r < 0 || c < 0 || r >= height || c >= width)
		return 0;
	int safe = board.at(width*r+c)->click();
	num_open--;
	if(!safe || num_open == 0)
		live = false;
	return 1;
}





