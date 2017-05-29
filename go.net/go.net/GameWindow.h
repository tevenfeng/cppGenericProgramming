#pragma once

#include <string>
#include <QDialog>
#include "ui_GameWindow.h"
#include "Owner.h"

using std::string;

class GameWindow : public QDialog
{
	Q_OBJECT

public:
	GameWindow(QWidget *parent = Q_NULLPTR);
	GameWindow(string localIp, string remoteIp, Owner localChessOwner, QWidget *parent = Q_NULLPTR);
	~GameWindow();

private:
	Ui::GameWindow ui;

	Owner localChessOwner;

	string localIp;
	string remoteIp;
};
