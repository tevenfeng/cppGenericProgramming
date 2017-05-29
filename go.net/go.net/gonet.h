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
#include "GameWindow.h"
#include "Object.h"
#include "JsonParser.h"
#include "DataSender.h"
#include "DataReceiver.h"
#include "DataGram.h"

class gonet : public QMainWindow
{
	Q_OBJECT
signals:

public slots:
	void itemClicked(QModelIndex index);

public:
	gonet(QWidget *parent = Q_NULLPTR);

private:
	Ui::gonetClass ui;
	QWidget *centralWidget;
	QPushButton *goBtn;
	QPushButton *fiveBtn;
	QGridLayout *layout;

	quint16 port = 10086;
	string localIp;
	string remoteIp;

	QListView *lanListView;
	QStandardItemModel *standardItemModel;

	std::set<string> *lanList;

	GameWindow *mainWindow;

	string getLocalIp();

	void setOnline();

	void setOffline();

	void broadCasting();

	void Action(string data);

	void sendChessInfo();

	void updateLanListView();
	
protected:
	void closeEvent(QCloseEvent *event);
};
