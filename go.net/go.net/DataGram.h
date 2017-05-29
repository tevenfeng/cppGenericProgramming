#pragma once

#include <string>
#include "MessageType.h"
#include "JsonParser.h"
#include "Owner.h"
#include "Chess.h"
using std::string;

class DataGram
{
public:
	int messageType;
	string fromIp;
	string toIp;
	bool chessType;			// true for go game, false for five-in-a-row game
	Chess chessInfo;

	string toJson();
};