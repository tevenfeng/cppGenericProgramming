#pragma once

#include <QWidget>
#include "ui_GameWindow.h"

class GameWindow : public QWidget
{
	Q_OBJECT

public:
	GameWindow(QWidget *parent = Q_NULLPTR);
	~GameWindow();

private:
	Ui::GameWindow ui;
};
