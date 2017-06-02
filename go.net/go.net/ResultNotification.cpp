#include "ResultNotification.h"

ResultNotification::ResultNotification(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->setFixedSize(300, 240);
}

ResultNotification::ResultNotification(Owner winner, Owner localChessOwner, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->winner = winner;
	this->localChessOwner = localChessOwner;

	this->setFixedSize(300, 240);

	string tmpWinnerStr = "";
	if (this->winner == localChessOwner)
	{
		tmpWinnerStr = " won! Do you want to restart or quit?";
	}
	else
	{
		tmpWinnerStr = " lost! Do you want to restart or quit?";
	}

	this->resultLabel = new QLabel(QString::fromStdString("You have" + tmpWinnerStr), this);
	this->resultLabel->setWordWrap(true);
	this->restartBtn = new QPushButton("Restart", this);
	this->exitBtn = new QPushButton("Exit", this);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(resultLabel, 0, 0, 1, 2);
	layout->addWidget(restartBtn, 1, 0, 1, 1);
	layout->addWidget(exitBtn, 1, 1, 1, 1);

	QObject::connect(restartBtn, &QPushButton::clicked, this, &ResultNotification::restartSlot);
	QObject::connect(exitBtn, &QPushButton::clicked, this, &ResultNotification::exitSlot);
}


void ResultNotification::exitSlot()
{
	emit exitGame();

	this->close();
}

void ResultNotification::restartSlot()
{
	emit restartGame();

	this->close();
}

ResultNotification::~ResultNotification()
{
}
