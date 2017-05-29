#pragma once
#include "Owner.h"

class Chess {
public:
	Chess();

	// Get column of the chess
	int getX();

	// Get row of the chess
	int getY();

	// Set column of the chess
	void setX(int x);

	// Set row of the chess
	void setY(int x);

	// Get the owner of the chess
	Owner getOwner();

	// Set the owner of the chess
	void setOwner(Owner owner);

private:
	int x;
	int y;
	Owner owner;
};