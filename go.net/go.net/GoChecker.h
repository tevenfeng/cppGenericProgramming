#pragma once
#include <queue>
#include <vector>
#include "Owner.h"
using std::queue;
using std::vector;

class QueueChess {
public:
	Owner owner;
	int row, col;
	bool isVisited = false;
};

class GoChecker {
private:
	QueueChess field[19][19];

	vector<QueueChess> *removeChesses;

	queue<QueueChess> *BFSCheckerChessQueue;			// Queue used in BFS to check chess status

	vector<QueueChess> *chessesToRemove;				// Vector used to store the chesses that should be removed

	bool checkStatus(int row, int col, Owner owner);		// Check the status of a specific stone, whether it's dead or alive

	bool isBound(int row, int col);							// Check whether a specific (x, y) is the bound itself

public:
	vector<QueueChess>* getAllDeadChesses(int row, int col, Owner owner);			// Get a vector of chesses that should be removed

	GoChecker(Owner field[19][19]);
};