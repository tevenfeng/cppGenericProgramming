#pragma once
#include <QObject>
#include <QtNetwork>

class DataSender : QObject
{
	Q_OBJECT
public:
	DataSender(QObject *parent);
	~DataSender();
	int sendToSpecificClient(QString host, quint16 port, const char * p, int len);
	int broadcast(quint16 port, const char * p, int len);

private:
	QObject *parent;
	QUdpSocket *socket;
	QHostAddress *host;
	quint16 port;
};