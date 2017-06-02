#pragma once

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <string>
#include "ui_ResultNotification.h"
#include "Owner.h"

using std::string;

class ResultNotification : public QDialog
{
	Q_OBJECT
		signals :

	void restartGame();

	void exitGame();

	public slots :

	void restartSlot();

	void exitSlot();

public:
	ResultNotification(QWidget *parent = Q_NULLPTR);
	ResultNotification(Owner winner, Owner localChessOwner, QWidget *parent = Q_NULLPTR);
	~ResultNotification();

private:
	Ui::ResultNotification ui;

	Owner winner, localChessOwner;

	QLabel *resultLabel;
	QPushButton *restartBtn, *exitBtn;
};
