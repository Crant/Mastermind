#ifndef MASTER_MIND_H
#define MASTER_MIND_H
#include "Board.h"

class MasterMind
{
private:
	Board answer;
	Board guess;
	int nrOfRounds;

public:
	MasterMind();
	string getGuess(int position, int round)const;
	string getAnswer(int position)const;
	int getNrOfRounds()const;
	void setNrOfRounds(int nrOfRounds);
	void makeGuess(string color, int position); 
	void createAnswer(); //skapar 5 slumpade färger som svar
	void clear(); // tar bort allt
	int checkAmountExist()const; //kollar hur många av gissningarna som finns i svaret
	int checkCorrectPos()const; //kollar hur många av gissningarna som ligger på rätt plats

};

#endif