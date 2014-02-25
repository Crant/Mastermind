#include "Board.h"
#include <ctime>
using namespace std;

Board::Board()
{
	for(int i = 0; i < 10; i++)
	{
		for(int n = 0; n < 5; n++)
		{
			this ->marbles[i][n] = Marble();
		}
	}
	for(int n = 0; n < 6; n++)
	{
		this ->nrOfMarbles[n] = 0;
	}
}
void Board::createMarble(string color, int position, int round)
{
	this ->marbles[round][position] = Marble(color);
	
}
void Board::generateRandomColor()
{
	srand((unsigned)(time(0)));
	int random = 0;
	string color[6] = {"Red","Green","Blue","White","Black","Orange"};

	for(int i = 0; i < 5; i++)
	{
		random = rand()%6;
		this ->marbles[0][i] = Marble(color[random]);
		this->nrOfMarbles[random]++;

	}
}
bool Board::checkExist(string color)const
{
	bool exist = false;

	for(int n = 0; n < 5; n++)
	{
		if(this ->marbles[0][n].getColor() == color)
		{
			exist = true;
			
		}
		else
		{

		}
	}
	
	return exist;
}
bool Board::checkCorrectPos(string color, int position)const
{
	bool exist = false;

	if(this ->marbles[0][position].getColor() == color)
	{
		exist = true;
	}
	else
	{
		exist = false;
	}
	return exist;
	
}
string Board::getMarble(int position, int round)const
{
	return this ->marbles[round][position].getColor();

}
void Board::clear()
{
	for(int i = 0; i < 10; i++)
	{
		for(int n = 0; n < 5; n++)
		{
			this ->marbles[i][n] = Marble();
		}
	}
	for(int n = 0; n < 6; n++)
	{
		this ->nrOfMarbles[n] = 0;
	}

}
int Board::getNrOfMarbles(int position)const
{
	return this ->nrOfMarbles[position];

}