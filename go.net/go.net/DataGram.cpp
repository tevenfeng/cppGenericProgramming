#include "DataGram.h"

string DataGram::toJson()
{
	Object tmpObject;

	tmpObject["messageType"] = this->messageType;
	tmpObject["fromIp"] = this->fromIp;
	tmpObject["toIp"] = this->toIp;

	if (this->messageType == MessageType::REQUEST || this->messageType==MessageType::AGREE)
	{
		tmpObject["chessType"] = this->chessType;
	}

	if (this->messageType == CHESS)
	{
		//tmpObject["owner"] = this->chessInfo.getOwner();
		tmpObject["position"] = Object();
		tmpObject["position"]["x"] = this->chessInfo.getX();
		tmpObject["position"]["y"] = this->chessInfo.getY();

		//if (this->chessInfo.getOwner() == BLACK)
		//{
		//	tmpObject["owner"] = "BLACK";
		//}
		//else
		//{
		//	tmpObject["owner"] = "WHITE";
		//}

		tmpObject["owner"] = this->chessInfo.getOwner();
	}

	string tmpResult = tmpObject.toJson();

	return tmpResult;
}
