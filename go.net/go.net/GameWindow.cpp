#include "GameWindow.h"

void GameWindow::restartGame()
{
	this->reset();
}

void GameWindow::exitGame()
{
	this->close();
}

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

	drawDisplayer();

	this->isGameOver = false;

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

	// draw field grids
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

	// draw a chess in the display area to show whose turn it is
	showTurn();

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

// click mouse and get the position of the cursor
// and then calculate the x and y of the chess
// then send these information to the remote player
void GameWindow::mousePressEvent(QMouseEvent * e)
{
	int row = 0;
	int column = 0;

	int tmpX = e->x();
	int tmpY = e->y();

	// if it is 'my' turn
	// else do nothing
	if (this->isGameOver == false && this->localChessOwner == this->currentTurn)
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
			chessDataGram->chessInfo.setOwner(this->currentTurn);

			string tmpStr = chessDataGram->toJson();

			Owner tmpOwner = this->currentTurn;

			DataSender *dataSender;
			dataSender = new DataSender(this);
			//dataSender->sendToSpecificClient(QString::fromStdString(this->remoteIp), this->port, tmpStr.c_str(), tmpStr.length());
			dataSender->broadcast(this->port, tmpStr.c_str(), tmpStr.length());

			// Turn to the other player
			changeTurn();

			// repaint
			this->repaint();

			// codes for checking win-or-lose in five-in-a-row game
			if (this->chessType == false)
			{
				// false means five-in-a-row
				if (isFiveSuccess(row, column, tmpOwner))
				{
					this->isGameOver = true;
					ResultNotification *resultWindow = new ResultNotification(tmpOwner, this->localChessOwner);
					resultWindow->show();

					QObject::connect(resultWindow, &ResultNotification::restartGame, this, &GameWindow::restartGame);
					QObject::connect(resultWindow, &ResultNotification::exitGame, this, &GameWindow::exitGame);
				}
			}

		} // if click position not inside the field, do nothing
	}
}

// function to draw a single chess on the field 
// according to chess info
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

// change the turn between the two players
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

// function to draw a chess in the display area to show whose turn it is
void GameWindow::showTurn()
{
	if (localChessOwner == BLACK)
	{
		if (currentTurn == BLACK)
		{
			this->paint->setBrush(QBrush(Qt::black, Qt::SolidPattern));
			this->paint->drawEllipse(FIELD_RIGHT_BOUND + 40, FIELD_BOTTOM_BOUND - 70, CHESS_RADIUS, CHESS_RADIUS);
		}
		else
		{
			this->paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));
			this->paint->drawEllipse(FIELD_RIGHT_BOUND + 40, 100, CHESS_RADIUS, CHESS_RADIUS);
		}
	}
	else
	{
		if (currentTurn == BLACK)
		{
			this->paint->setBrush(QBrush(Qt::black, Qt::SolidPattern));
			this->paint->drawEllipse(FIELD_RIGHT_BOUND + 40, 100, CHESS_RADIUS, CHESS_RADIUS);
		}
		else
		{
			this->paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));
			this->paint->drawEllipse(FIELD_RIGHT_BOUND + 40, FIELD_BOTTOM_BOUND - 70, CHESS_RADIUS, CHESS_RADIUS);
		}
	}
}

// restart the game
// means clearing all things
void GameWindow::reset()
{
	memset(this->field, 0, sizeof(this->field));
	this->allChesses->clear();
	this->isGameOver = false;
}

// emit signal that game window has been closed 
void GameWindow::closeEvent(QCloseEvent * event)
{
	emit gameWindowClose();
}

// action after receiving chess info from remote
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

// receive chess info
// draw the chess
// change the turn
void GameWindow::receiveChess(Object result)
{
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

		changeTurn();
		this->repaint();

		// codes for checking win-or-lose in five-in-a-row game
		if (this->chessType == false)
		{
			// false means five-in-a-row
			if (isFiveSuccess(result["position"]["y"].toInt(), result["position"]["x"].toInt(), (Owner)result["owner"].toInt()))
			{
				this->isGameOver = true;

				ResultNotification *resultWindow = new ResultNotification((Owner)result["owner"].toInt(), this->localChessOwner);
				resultWindow->show();

				QObject::connect(resultWindow, &ResultNotification::restartGame, this, &GameWindow::restartGame);
				QObject::connect(resultWindow, &ResultNotification::exitGame, this, &GameWindow::exitGame);
			}
		}
	}
}

void GameWindow::drawDisplayer()
{
	this->localPlayerLabel = new QLabel("Me: ", this);
	this->localIpLabel = new QLabel(QString::fromStdString(this->localIp), this);
	this->remotePlayerLabel = new QLabel("Remote: ", this);
	this->remoteIpLabel = new QLabel(QString::fromStdString(this->remoteIp), this);

	QFont myFont = QFont("Arial", QFont::Bold);
	myFont.setPointSize(16);
	this->remotePlayerLabel->setGeometry(QRect(FIELD_RIGHT_BOUND + 20, 40, 300, 30));
	this->remoteIpLabel->setGeometry(QRect(FIELD_RIGHT_BOUND + 20, 70, 300, 30));
	this->remotePlayerLabel->setFont(myFont);
	this->remoteIpLabel->setFont(myFont);

	this->localPlayerLabel->setGeometry(QRect(FIELD_RIGHT_BOUND + 20, FIELD_BOTTOM_BOUND - 130, 400, 30));
	this->localIpLabel->setGeometry(QRect(FIELD_RIGHT_BOUND + 20, FIELD_BOTTOM_BOUND - 100, 400, 30));
	this->localPlayerLabel->setFont(myFont);
	this->localIpLabel->setFont(myFont);
}

bool GameWindow::isFiveSuccess(int row, int col, Owner owner)
{
	int TempRow, TempCol;
	int count = 1;
	for (int direct = 0; direct <= 3; direct++) {
		for (int i = -4; i <= 4; i++) {
			if (i == 0)
				continue;
			switch (direct) {
			case 0:
				TempRow = row + i;
				TempCol = col;
				break;
			case 1:
				TempRow = row;
				TempCol = col + i;
				break;
			case 2:
				TempRow = row + i;
				TempCol = col - i;
				break;
			case 3:
				TempRow = row - i;
				TempCol = col - i;
				break;
			}
			if (isInField(TempRow, TempCol) && field[TempRow][TempCol] != EMPTY && field[TempRow][TempCol] == owner)
				count++;
			else
				count = 1;
			if (count == 5)
				return true;
		}
	}
	return false;
}

bool GameWindow::isInField(int row, int col)
{
	return (row >= 0 && row <= FIELD_GRID_NUMBER && col >= 0 && col < FIELD_GRID_NUMBER);
}
