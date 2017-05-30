#pragma once
#include <QObject>
#include <QtNetwork>
#include <string>
#include "JsonParser.h"

class DataReceiver : public QObject
{
	Q_OBJECT
public slots:
	void read();

signals:
	void dataReady(std::string str);
	void chessDataReady(std::string str);
public:
	DataReceiver(QObject *parent, quint16 port);
	~DataReceiver();
	void listenToBroadcast();
	void listenToSpecificRemote(std::string remoteIp);
private:
	QObject *parent;
	QUdpSocket *socket;
	QHostAddress *host;
	quint16 port;
};