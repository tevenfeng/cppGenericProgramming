#include "GoChecker.h"

GoChecker::GoChecker(Owner field[19][19])
{
	for (int row = 0; row < 19; row++)
	{
		for (int col = 0; col < 19; col++)
		{
			this->field[row][col].isVisited = false;
			this->field[row][col].owner = field[row][col];
			this->field[row][col].row = row;
			this->field[row][col].col = col;
		}
	}

	this->removeChesses = new vector<QueueChess>();
}

// True: alive, False: Dead(including boundary)
bool GoChecker::checkStatus(int row, int col, Owner owner)
{
	Owner chessColorToFind;
	if (owner == BLACK)
	{
		chessColorToFind = WHITE;
	}
	else if (owner == WHITE)
	{
		chessColorToFind = BLACK;
	}

	if (isBound(row, col))
	{
		return false;
	}

	if (this->field[row][col].owner == EMPTY)
	{
		return true;
	}

	// if visited, return dead
	if (this->field[row][col].isVisited)
	{
		return false;
	}

	if (this->field[row][col].owner == chessColorToFind)
	{
		this->removeChesses->push_back(this->field[row][col]);
		this->field[row][col].isVisited = true;

		return (checkStatus(row - 1, col, owner)
			|| checkStatus(row + 1, col, owner)
			|| checkStatus(row, col - 1, owner)
			|| checkStatus(row, col + 1, owner));
	}
	else
	{
		return false;
	}
}

bool GoChecker::isBound(int row, int col)
{
	if (row < 0)
	{
		return true;
	}
	if (col < 0)
	{
		return true;
	}
	if (row > 18)
	{
		return true;
	}
	if (col > 18)
	{
		return true;
	}

	return false;
}

vector<QueueChess>* GoChecker::getAllDeadChesses(int row, int col, Owner owner)
{
	if (field[row - 1][col].owner != owner && field[row - 1][col].owner != EMPTY)
	{
		if (!checkStatus(row - 1, col, owner))
		{
			this->removeChesses->push_back(this->field[row - 1][col]);
		}
		else 
		{
			this->removeChesses->clear();
		}
	}
	if (field[row + 1][col].owner != owner && field[row + 1][col].owner != EMPTY)
	{
		if (!checkStatus(row + 1, col, owner))
		{
			this->removeChesses->push_back(this->field[row + 1][col]);
		}
		else
		{
			this->removeChesses->clear();
		}
	}
	if (field[row][col - 1].owner != owner && field[row][col - 1].owner != EMPTY)
	{
		if (!checkStatus(row, col - 1, owner))
		{
			this->removeChesses->push_back(this->field[row][col - 1]);
		}
		else
		{
			this->removeChesses->clear();
		}
	}
	if (field[row][col + 1].owner != owner && field[row][col + 1].owner != EMPTY)
	{
		if (!checkStatus(row, col + 1, owner))
		{
			this->removeChesses->push_back(this->field[row][col + 1]);
		}
		else
		{
			this->removeChesses->clear();
		}
	}

	return this->removeChesses;
}
