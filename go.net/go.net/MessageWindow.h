#pragma once

#include <string>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "ui_MessageWindow.h"
#include "MessageType.h"
#include "DataGram.h"
#include "DataSender.h"

using std::string;

class MessageWindow : public QDialog
{
	Q_OBJECT
public slots:
	void refuseBtnClicked(bool arg);

	void agreeBtnClicked(bool arg);

public:
	MessageWindow(QWidget *parent = Q_NULLPTR);

	MessageWindow(int type, bool chessType, string fromIp, string localIp, quint16 port, QWidget *parent = Q_NULLPTR);

	~MessageWindow();

	void generateRequestedWindow();

	void generateRefuseWindow();

private:
	Ui::MessageWindow ui;

	string fromIp;
	string localIp;
	quint16 port;
	int messageType;
	bool chessType;
};
