#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

GameWindow::GameWindow(string localIp, string remoteIp, Owner localChessOwner, QWidget *parent)
{
	ui.setupUi(this);

	this->localIp = localIp;
	this->remoteIp = remoteIp;
	this->localChessOwner = localChessOwner;
}

GameWindow::~GameWindow()
{
}
