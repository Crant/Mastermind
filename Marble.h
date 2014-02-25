#ifndef MARBLE_H
#define MARBLE_H
#include <string>

using namespace std;
class Marble
{
private:
	string color;


public:
	Marble(string color);
	Marble();
	string getColor()const;
	void setColor(string color);




};


#endif