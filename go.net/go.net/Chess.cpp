#include "chess.h"

Chess::Chess()
{

}

int Chess::getX()
{
	return this->x;
}

int Chess::getY()
{
	return this->y;
}

void Chess::setX(int x)
{
	this->x = x;
}

void Chess::setY(int y)
{
	this->y = y;
}

Owner Chess::getOwner()
{
	return this->owner;
}

void Chess::setOwner(Owner owner)
{
	this->owner = owner;
}
