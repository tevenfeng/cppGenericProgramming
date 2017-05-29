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
	Chess chessInfo;

	string toJson();
};