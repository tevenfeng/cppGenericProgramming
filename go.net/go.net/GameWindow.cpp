#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	this->allChesses = new std::vector<Chess>();
	this->reset();
}

GameWindow::GameWindow(string localIp, string remoteIp, bool chessType, Owner localChessOwner, QWidget *parent)
{
	ui.setupUi(this);
	this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	this->allChesses = new std::vector<Chess>();
	this->reset();
	this->currentTurn = BLACK;

	this->localIp = localIp;
	this->remoteIp = remoteIp;
	this->localChessOwner = localChessOwner;
	this->chessType = chessType;
	this->port = 10087;

	DataReceiver *dataReceiver;
	dataReceiver = new DataReceiver(this, this->port);
	//dataReceiver->listenToSpecificRemote(this->remoteIp);
	dataReceiver->listenToBroadcast();

	QObject::connect(dataReceiver, &DataReceiver::chessDataReady, this, &GameWindow::chessAction);
}

GameWindow::~GameWindow()
{
}

void GameWindow::paintEvent(QPaintEvent * e)
{
	this->paint = new QPainter();

	this->paint->begin(this);

	// draw the field

	// draw the background
	paint->setBrush(QBrush(QColor(251, 196, 116)));
	int field_length = FIELD_OFFSET_X + FIELD_GRID_NUMBER * FIELD_GRID_WIDTH;
	paint->drawRect(FIELD_OFFSET_X / 2, FIELD_OFFSET_Y / 2, field_length, field_length);

	// draw lines
	this->paint->setPen(QPen(Qt::black, 2, Qt::SolidLine));
	for (int i = 0; i < FIELD_GRID_NUMBER + 1; i++)
	{
		this->paint->drawLine(FIELD_OFFSET_X, FIELD_OFFSET_Y + FIELD_GRID_WIDTH*i, FIELD_OFFSET_X + FIELD_GRID_WIDTH*(FIELD_GRID_NUMBER), FIELD_OFFSET_Y + FIELD_GRID_WIDTH*i);
	}
	for (int i = 0; i < FIELD_GRID_NUMBER + 1; i++)
	{
		this->paint->drawLine(FIELD_OFFSET_X + FIELD_GRID_WIDTH*i, FIELD_OFFSET_Y, FIELD_OFFSET_X + FIELD_GRID_WIDTH*i, FIELD_OFFSET_Y + FIELD_GRID_WIDTH*(FIELD_GRID_NUMBER));
	}

	// draw the nine star points
	drawStarPoints();

	// draw all chesses
	for (auto itr = this->allChesses->begin(); itr != this->allChesses->end(); itr++)
	{
		drawSingleChess(*itr);
	}

	this->paint->end();
}

void GameWindow::drawStarPoints()
{
	this->paint->setBrush(QBrush(Qt::black, Qt::SolidPattern));
	this->paint->drawEllipse(FIELD_OFFSET_X + 3 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 3 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 9 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 3 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 15 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 3 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 3 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 9 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 9 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 9 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 15 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 9 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 3 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 15 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 9 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 15 * FIELD_GRID_WIDTH - 5, 10, 10);
	this->paint->drawEllipse(FIELD_OFFSET_X + 15 * FIELD_GRID_WIDTH - 5, FIELD_OFFSET_X + 15 * FIELD_GRID_WIDTH - 5, 10, 10);
}

void GameWindow::mousePressEvent(QMouseEvent * e)
{
	int row = 0;
	int column = 0;

	int tmpX = e->x();
	int tmpY = e->y();

	if (this->localChessOwner == this->currentTurn)
	{
		// calculate the row and column of the chess
		if (tmpX >= FIELD_LEFT_BOUND && tmpX <= FIELD_RIGHT_BOUND && tmpY >= FIELD_TOP_BOUND && tmpY <= FIELD_BOTTOM_BOUND)
		{
			// Click position is inside the go field, so calculate
			row = tmpY / FIELD_GRID_WIDTH;
			column = tmpX / FIELD_GRID_WIDTH;

			if (this->field[row][column] != EMPTY)
			{
				return;
			}

			// Store the chess to currentChessToDraw
			Chess currentChessToDraw = Chess();
			currentChessToDraw.setX(column);
			currentChessToDraw.setY(row);
			currentChessToDraw.setOwner(currentTurn);

			// add the currentChessToDraw to the queue of all chesses
			// and set the position to unclickable
			this->allChesses->push_back(currentChessToDraw);
			this->field[row][column] = currentTurn;

			// send this chessInfo to the remote player
			DataGram *chessDataGram = new DataGram();
			chessDataGram->messageType = CHESS;
			chessDataGram->fromIp = this->localIp;
			chessDataGram->toIp = this->remoteIp;
			chessDataGram->chessInfo = Chess();
			chessDataGram->chessInfo.setX(column);
			chessDataGram->chessInfo.setY(row);
			chessDataGram->chessInfo.setOwner(currentTurn);

			string tmpStr = chessDataGram->toJson();

			DataSender *dataSender;
			dataSender = new DataSender(this);
			//dataSender->sendToSpecificClient(QString::fromStdString(this->remoteIp), this->port, tmpStr.c_str(), tmpStr.length());
			dataSender->broadcast(this->port, tmpStr.c_str(), tmpStr.length());

			// repaint
			this->repaint();

			// Turn to the other candidate
			changeTurn();

		} // if click position not inside the field, do nothing
	}
}

void GameWindow::drawSingleChess(Chess tmpChess)
{

	if (tmpChess.getOwner() == WHITE)
	{
		this->paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));
	}
	else
	{
		this->paint->setBrush(QBrush(Qt::black, Qt::SolidPattern));
	}

	int chessLocationX = FIELD_OFFSET_X + tmpChess.getX() * FIELD_GRID_WIDTH - CHESS_RADIUS / 2;
	int chessLocationY = FIELD_OFFSET_Y + tmpChess.getY() * FIELD_GRID_WIDTH - CHESS_RADIUS / 2;
	this->paint->drawEllipse(chessLocationX, chessLocationY, CHESS_RADIUS, CHESS_RADIUS);
}

void GameWindow::changeTurn()
{
	if (this->currentTurn == WHITE)
	{
		this->currentTurn = BLACK;
	}
	else
	{
		this->currentTurn = WHITE;
	}
}

void GameWindow::reset()
{
	memset(this->field, 0, sizeof(this->field));

	this->allChesses->clear();
}

void GameWindow::closeEvent(QCloseEvent * event)
{
	emit gameWindowClose();
}

void GameWindow::chessAction(string data)
{
	JsonParser *tmpParser = new JsonParser();
	int p = 0;
	Object result = tmpParser->readObject(data, p);

	if (result["fromIp"].toString() == this->remoteIp && result["toIp"].toString() == this->localIp)
	{
		switch (result["messageType"].toInt())
		{
		case MessageType::CHESS:
			receiveChess(result);
			break;
		default:
			break;
		}
	}
}

void GameWindow::receiveChess(Object result)
{
	// receive chess
	// draw the chess
	// change the turn
	if ((Owner)result["owner"].toInt() == currentTurn)
	{
		Chess currentChessToDraw = Chess();
		currentChessToDraw.setX(result["position"]["x"].toInt());
		currentChessToDraw.setY(result["position"]["y"].toInt());
		currentChessToDraw.setOwner((Owner)result["owner"].toInt());

		// add the currentChessToDraw to the queue of all chesses
		// and set the position to unclickable
		this->allChesses->push_back(currentChessToDraw);
		this->field[result["position"]["y"].toInt()][result["position"]["x"].toInt()] = currentTurn;

		this->repaint();

		changeTurn();
	}
}
