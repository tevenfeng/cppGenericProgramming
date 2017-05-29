#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QCloseEvent>
#include <QLabel>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QWidget>
#include <QLayout>
#include <set>
#include "ui_gonet.h"
#include "Object.h"
#include "JsonParser.h"
#include "DataSender.h"
#include "DataReceiver.h"
#include "DataGram.h"
#include "GameWindow.h"
#include "MessageWindow.h"

class gonet : public QMainWindow
{
	Q_OBJECT
signals:

public slots:
	void itemClicked(QModelIndex index);

	void goBtnClicked(bool arg);

	void fiveBtnClicked(bool arg);

public:
	gonet(QWidget *parent = Q_NULLPTR);

private:
	Ui::gonetClass ui;
	QWidget *centralWidget;
	QPushButton *goBtn;
	QPushButton *fiveBtn;
	QGridLayout *layout;

	GameWindow *gameWindow;

	quint16 port = 10086;
	string localIp;
	string remoteIp;

	QListView *lanListView;
	QStandardItemModel *standardItemModel;

	std::set<string> *lanList;

	string getLocalIp();

	void setOnline();

	void setOffline();

	void broadCasting();

	void Action(string data);

	void sendChessInfo();

	void updateLanListView();

	void receiveOnlineMessage(Object result);
	void receiveOfflineMessage(Object result);
	void receiveRequestMessage(Object result);
	void receiveAgreeMessage(Object result);
	void receiveRefuseMessage(Object result);
	
protected:
	void closeEvent(QCloseEvent *event);
};
