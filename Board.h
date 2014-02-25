#ifndef BOARD_H
#define BOARD_H
#include "Marble.h"

class Board
{
private:
	Marble marbles[10][5];
	int nrOfMarbles[6];
public:
	Board();
	void createMarble(string color, int position, int round);
	string getMarble(int position, int round)const;
	int getNrOfMarbles(int position)const;
	void generateRandomColor(); //Genererar en slumpad färg
	bool checkExist(string color)const;  //returnerar antalet som finns på rätt plats
	bool checkCorrectPos(string color, int position)const; //returnerar true om den färgen finns i svaret
	void clear();  //rensar arrayen och "Skapar en ny omgång"


};

#endif