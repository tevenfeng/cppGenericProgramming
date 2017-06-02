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
	int messageType;        // MessageType enumeration
	string fromIp;			// this datagram comes from this ip
	string toIp;			// this datagram is meant to be sent to this ip
	bool chessType;			// true for go game, false for five-in-a-row game
	Chess chessInfo;		// chess info, including x, y, and black or white info

	string toJson();		// convert to json string using JsonParser
};