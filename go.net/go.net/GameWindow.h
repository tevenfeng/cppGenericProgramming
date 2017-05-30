#pragma once

#include <string>
#include <vector>
#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include "ui_GameWindow.h"
#include "Owner.h"
#include "Chess.h"
#include "DataSender.h"
#include "DataReceiver.h"
#include "Object.h"
#include "JsonParser.h"
#include "DataGram.h"

using std::string;

class GameWindow : public QDialog
{
	Q_OBJECT
signals :
	void gameWindowClose();
public slots:
	void chessAction(string data);

public:
	GameWindow(QWidget *parent = Q_NULLPTR);
	GameWindow(string localIp, string remoteIp, bool chessType, Owner localChessOwner, QWidget *parent = Q_NULLPTR);
	~GameWindow();

private:
	Ui::GameWindow ui;
	QPainter *paint;

	//DataSender *dataSender;
	//DataReceiver *dataReceiver;

	static const int WINDOW_WIDTH = 960;
	static const int WINDOW_HEIGHT = 688;

	// some basic parameters for the field
	static const int FIELD_GRID_NUMBER = 18;
	static const int FIELD_GRID_WIDTH = 36;
	static const int FIELD_OFFSET_X = 20, FIELD_OFFSET_Y = 20;
	static const int FIELD_LEFT_BOUND = FIELD_OFFSET_X;
	static const int FIELD_RIGHT_BOUND = FIELD_OFFSET_X * 2 + FIELD_GRID_NUMBER * FIELD_GRID_WIDTH;
	static const int FIELD_TOP_BOUND = FIELD_OFFSET_Y;
	static const int FIELD_BOTTOM_BOUND = FIELD_OFFSET_Y * 2 + FIELD_GRID_NUMBER * FIELD_GRID_WIDTH;

	static const int CHESS_RADIUS = (FIELD_GRID_WIDTH / 2 - 3) * 2;

	std::vector<Chess> *allChesses;
	Owner field[FIELD_GRID_NUMBER + 1][FIELD_GRID_NUMBER + 1];

	bool chessType;
	Owner currentTurn = BLACK;
	Owner localChessOwner;

	string localIp;
	string remoteIp;
	quint16 port = 10087;

	void paintEvent(QPaintEvent *e);				// function to paint the go field
	void drawStarPoints();							// function to draw the nine star points
	void mousePressEvent(QMouseEvent *e);			// function to handle the pressing event of mouse 
	void drawSingleChess(Chess tmpChess);           // function to draw a single chess on the field

	void changeTurn();								// change the turn between the two candidates

	void reset();									// restart the game

	void receiveChess(Object result);

protected:
	void closeEvent(QCloseEvent *event);
};
