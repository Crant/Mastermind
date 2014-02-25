#include "Marble.h"

using namespace std;

Marble::Marble()
{
	this ->color = "Unknown";
}
Marble::Marble(string color)
{
	this ->color = color;
}
string Marble::getColor()const
{
	return this ->color;
}
void Marble::setColor(string color)
{
	this ->color = color;
}