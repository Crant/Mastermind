#include "MasterMind.h"


MasterMind::MasterMind()
{
	this ->answer = Board();
	this ->guess = Board();
	this ->nrOfRounds = 0;
}
void MasterMind::makeGuess(string color, int position)
{
	this ->guess.createMarble(color, position, this->nrOfRounds);
}
void MasterMind::createAnswer()
{
	this ->answer.generateRandomColor();
}
string MasterMind::getGuess(int position, int round)const
{
	return this ->guess.getMarble(position, round);
	
}
int MasterMind::getNrOfRounds()const
{
	return this ->nrOfRounds;
}
void MasterMind::clear()
{
	this ->answer.clear();
	this ->guess.clear();
	this ->nrOfRounds = 0;

}
int MasterMind::checkAmountExist()const
{
	string color = "";
	int amount = 0;
	int tempArray[6];
	for(int n = 0; n < 6; n++)
	{
		tempArray[n] = answer.getNrOfMarbles(n);
	}
	for(int i = 0; i < 5; i++)
	{
		color = this->guess.getMarble(i, this->getNrOfRounds());
		if (this ->answer.checkExist(color) == true)
		{
			if(color == "Blue")
			{
				if(tempArray[2] > 0)
				{
					tempArray[2]--;
					amount++;
				}
			}
			else if(color == "White")
			{
				if(tempArray[3] > 0)
				{
					tempArray[3]--;
					amount++;
				}	
			}
			else if(color == "Orange")
			{
				if(tempArray[5] > 0)
				{
					tempArray[5]--;
					amount++;
				}	
			}
			else if(color == "Green")
			{
				if(tempArray[1] > 0)
				{
					tempArray[1]--;
					amount++;
				}
			}
			else if(color == "Red")
			{
				if(tempArray[0] > 0)
				{
					tempArray[0]--;
					amount++;
				}	
			}
			else if(color == "Black")
			{
				if(tempArray[4] > 0)
				{
					tempArray[4]--;
					amount++;
				}
			}
			
		}
	}
	return amount;
}
int MasterMind::checkCorrectPos()const
{
	string color = "Unknown";
	int amount = 0;
	int tempArray[6];
	for(int i = 0; i < 6; i++)
	{
		tempArray[i] = answer.getNrOfMarbles(i);
	}
	for(int i = 0; i < 5; i++)
	{
		color = this ->guess.getMarble(i,this->nrOfRounds);
		if(this ->answer.checkCorrectPos(color, i) == true)
		{
			if(color == "Blue")
			{
				if(tempArray[2] > 0)
				{
					tempArray[2]--;
					amount++;
				}
			}
			else if(color == "White")
			{
				if(tempArray[3] > 0)
				{
					tempArray[3]--;
					amount++;
				}	
			}
			else if(color == "Orange")
			{
				if(tempArray[5] > 0)
				{
					tempArray[5]--;
					amount++;
				}	
			}
			else if(color == "Green")
			{
				if(tempArray[1] > 0)
				{
					tempArray[1]--;
					amount++;
				}
			}
			else if(color == "Red")
			{
				if(tempArray[0] > 0)
				{
					tempArray[0]--;
					amount++;
				}	
			}
			else if(color == "Black")
			{
				if(tempArray[4] > 0)
				{
					tempArray[4]--;
					amount++;
				}
			}
		}
	}
	return amount;
}
void MasterMind::setNrOfRounds(int nrOfRounds)
{
	this ->nrOfRounds = nrOfRounds;
}
string MasterMind::getAnswer(int position)const
{
	return this->answer.getMarble(position, 0);
}